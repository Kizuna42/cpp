#include "ValidationEngine.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

#if defined(__unix__) || defined(__APPLE__)
#include <dirent.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>
#elif defined(_WIN32)
#include <windows.h>
#endif

// Helper comparator for sorting validators by priority
struct ValidatorPriorityComparator {
    bool operator()(const IValidator* a, const IValidator* b) const {
        return a->getPriority() > b->getPriority();
    }
};

// Structure to hold validator task information
struct ValidatorTask {
    IValidator* validator;
    const ValidationContext* context;
    ValidationResult* result;
    bool completed;
    std::string error;
    
    ValidatorTask() : validator(NULL), context(NULL), result(NULL), completed(false) {}
};

#if defined(__unix__) || defined(__APPLE__)
// Thread function for executing validator
void* executeValidatorThread(void* arg) {
    ValidatorTask* task = static_cast<ValidatorTask*>(arg);
    
    try {
        *(task->result) = task->validator->validate(*(task->context));
        task->completed = true;
    } catch (const std::exception& e) {
        task->error = e.what();
        task->completed = true;
    } catch (...) {
        task->error = "Unknown exception";
        task->completed = true;
    }
    
    return NULL;
}
#endif

ValidationEngine::ValidationEngine() : enableParallelProcessing_(true), maxThreads_(0) {
}

ValidationEngine::~ValidationEngine() {
    clearValidators();
}

ValidationResult ValidationEngine::validate(const std::string& submissionPath, ModuleType moduleType) {
    ValidationContext context = createContext(submissionPath, moduleType);
    return validate(context);
}

ValidationResult ValidationEngine::validate(const ValidationContext& context) {
    // Validate context before proceeding
    ValidationResult aggregatedResult("ValidationEngine");
    
    if (context.submissionPath.empty()) {
        Issue issue(Issue::CRITICAL, "INVALID_CONTEXT", 
                   "Submission path is empty");
        issue.messageJa = "提出パスが空です";
        aggregatedResult.addIssue(issue);
        return aggregatedResult;
    }
    
    if (validators_.empty()) {
        Issue issue(Issue::MAJOR, "NO_VALIDATORS", 
                   "No validators registered");
        issue.messageJa = "検証器が登録されていません";
        aggregatedResult.addIssue(issue);
        return aggregatedResult;
    }
    
    // Sort validators by priority before execution
    const_cast<ValidationEngine*>(this)->sortValidatorsByPriority();
    
    // Add context information to metrics
    aggregatedResult.addMetric("submission_path", context.submissionPath);
    aggregatedResult.addMetric("module_type", context.getModuleTypeString());
    aggregatedResult.addMetric("platform", context.getPlatformString());
    
    std::ostringstream validatorCount;
    validatorCount << validators_.size();
    aggregatedResult.addMetric("validator_count", validatorCount.str());
    
    // Choose execution method based on settings
    if (enableParallelProcessing_ && validators_.size() > 1) {
        return executeValidatorsParallel(context);
    } else {
        return executeValidatorsSequential(context);
    }
}

void ValidationEngine::addValidator(IValidator* validator) {
    if (validator != NULL) {
        validators_.push_back(validator);
    }
}

void ValidationEngine::clearValidators() {
    for (std::vector<IValidator*>::iterator it = validators_.begin();
         it != validators_.end(); ++it) {
        delete *it;
    }
    validators_.clear();
}

size_t ValidationEngine::getValidatorCount() const {
    return validators_.size();
}

std::vector<std::string> ValidationEngine::getValidatorNames() const {
    std::vector<std::string> names;
    for (std::vector<IValidator*>::const_iterator it = validators_.begin();
         it != validators_.end(); ++it) {
        names.push_back((*it)->getName());
    }
    return names;
}

void ValidationEngine::setParallelProcessing(bool enable) {
    enableParallelProcessing_ = enable;
}

void ValidationEngine::setMaxThreads(int maxThreads) {
    maxThreads_ = maxThreads;
}

bool ValidationEngine::isParallelProcessingEnabled() const {
    return enableParallelProcessing_;
}

ValidationResult ValidationEngine::executeValidatorsSequential(const ValidationContext& context) {
    ValidationResult aggregatedResult("ValidationEngine");
    
    // Add context information to metrics
    aggregatedResult.addMetric("submission_path", context.submissionPath);
    aggregatedResult.addMetric("module_type", context.getModuleTypeString());
    aggregatedResult.addMetric("platform", context.getPlatformString());
    aggregatedResult.addMetric("execution_mode", "sequential");
    
    std::ostringstream validatorCount;
    validatorCount << validators_.size();
    aggregatedResult.addMetric("validator_count", validatorCount.str());
    
    // Execute each validator sequentially
    int successfulValidators = 0;
    int failedValidators = 0;
    
    for (std::vector<IValidator*>::const_iterator it = validators_.begin();
         it != validators_.end(); ++it) {
        
        IValidator* validator = *it;
        try {
            std::cout << "Running validator: " << validator->getName() << std::endl;
            
            ValidationResult result = validator->validate(context);
            
            // Merge issues from this validator
            for (std::vector<Issue>::const_iterator issueIt = result.issues.begin();
                 issueIt != result.issues.end(); ++issueIt) {
                aggregatedResult.addIssue(*issueIt);
            }
            
            // Merge metrics
            for (std::map<std::string, std::string>::const_iterator metricIt = result.metrics.begin();
                 metricIt != result.metrics.end(); ++metricIt) {
                std::string key = validator->getName() + "." + metricIt->first;
                aggregatedResult.addMetric(key, metricIt->second);
            }
            
            // If this validator failed and it's critical, mark overall result as invalid
            if (!result.isValid && validator->getPriority() >= IValidator::HIGH) {
                aggregatedResult.isValid = false;
            }
            
            if (result.isValid) {
                successfulValidators++;
            } else {
                failedValidators++;
            }
            
        } catch (const std::exception& e) {
            // Handle validator exceptions gracefully
            failedValidators++;
            Issue issue(Issue::CRITICAL, "VALIDATOR_ERROR", 
                       "Validator " + validator->getName() + " failed: " + e.what());
            issue.messageJa = "検証器 " + validator->getName() + " が失敗しました: " + e.what();
            aggregatedResult.addIssue(issue);
            
            std::cerr << "Validator " << validator->getName() << " threw exception: " << e.what() << std::endl;
        } catch (...) {
            // Handle unknown exceptions
            failedValidators++;
            Issue issue(Issue::CRITICAL, "VALIDATOR_UNKNOWN_ERROR", 
                       "Validator " + validator->getName() + " failed with unknown error");
            issue.messageJa = "検証器 " + validator->getName() + " が不明なエラーで失敗しました";
            aggregatedResult.addIssue(issue);
            
            std::cerr << "Validator " << validator->getName() << " threw unknown exception" << std::endl;
        }
    }
    
    // Add execution statistics
    std::ostringstream successCount, failCount;
    successCount << successfulValidators;
    failCount << failedValidators;
    
    aggregatedResult.addMetric("successful_validators", successCount.str());
    aggregatedResult.addMetric("failed_validators", failCount.str());
    
    return aggregatedResult;
}

ValidationResult ValidationEngine::executeValidatorsParallel(const ValidationContext& context) {
    ValidationResult aggregatedResult("ValidationEngine");
    
    // Add context information to metrics
    aggregatedResult.addMetric("submission_path", context.submissionPath);
    aggregatedResult.addMetric("module_type", context.getModuleTypeString());
    aggregatedResult.addMetric("platform", context.getPlatformString());
    aggregatedResult.addMetric("execution_mode", "parallel");
    
    std::ostringstream validatorCount;
    validatorCount << validators_.size();
    aggregatedResult.addMetric("validator_count", validatorCount.str());

#if defined(__unix__) || defined(__APPLE__)
    // Prepare tasks for parallel execution
    std::vector<ValidatorTask> tasks(validators_.size());
    std::vector<ValidationResult> results(validators_.size());
    std::vector<pthread_t> threads(validators_.size());
    
    // Initialize tasks
    for (size_t i = 0; i < validators_.size(); ++i) {
        tasks[i].validator = validators_[i];
        tasks[i].context = &context;
        tasks[i].result = &results[i];
        results[i] = ValidationResult(validators_[i]->getName());
    }
    
    std::cout << "Running " << validators_.size() << " validators in parallel..." << std::endl;
    
    // Create threads
    for (size_t i = 0; i < validators_.size(); ++i) {
        if (pthread_create(&threads[i], NULL, executeValidatorThread, &tasks[i]) != 0) {
            // If thread creation fails, fall back to sequential execution for this validator
            std::cerr << "Failed to create thread for validator " << validators_[i]->getName() << std::endl;
            tasks[i].error = "Thread creation failed";
            tasks[i].completed = true;
        }
    }
    
    // Wait for all threads to complete
    for (size_t i = 0; i < validators_.size(); ++i) {
        if (tasks[i].error != "Thread creation failed") {
            pthread_join(threads[i], NULL);
        }
    }
    
    // Aggregate results
    int successfulValidators = 0;
    int failedValidators = 0;
    
    for (size_t i = 0; i < validators_.size(); ++i) {
        if (!tasks[i].error.empty()) {
            // Handle thread execution errors
            failedValidators++;
            Issue issue(Issue::CRITICAL, "VALIDATOR_THREAD_ERROR", 
                       "Validator " + validators_[i]->getName() + " thread failed: " + tasks[i].error);
            issue.messageJa = "検証器 " + validators_[i]->getName() + " のスレッドが失敗しました: " + tasks[i].error;
            aggregatedResult.addIssue(issue);
        } else {
            ValidationResult& result = results[i];
            
            // Merge issues from this validator
            for (std::vector<Issue>::const_iterator issueIt = result.issues.begin();
                 issueIt != result.issues.end(); ++issueIt) {
                aggregatedResult.addIssue(*issueIt);
            }
            
            // Merge metrics
            for (std::map<std::string, std::string>::const_iterator metricIt = result.metrics.begin();
                 metricIt != result.metrics.end(); ++metricIt) {
                std::string key = validators_[i]->getName() + "." + metricIt->first;
                aggregatedResult.addMetric(key, metricIt->second);
            }
            
            // If this validator failed and it's critical, mark overall result as invalid
            if (!result.isValid && validators_[i]->getPriority() >= IValidator::HIGH) {
                aggregatedResult.isValid = false;
            }
            
            if (result.isValid) {
                successfulValidators++;
            } else {
                failedValidators++;
            }
        }
    }
    
    // Add execution statistics
    std::ostringstream successCount, failCount;
    successCount << successfulValidators;
    failCount << failedValidators;
    
    aggregatedResult.addMetric("successful_validators", successCount.str());
    aggregatedResult.addMetric("failed_validators", failCount.str());
    
#else
    // Fallback to sequential execution on non-Unix systems
    std::cout << "Parallel processing not available on this platform, falling back to sequential execution" << std::endl;
    return executeValidatorsSequential(context);
#endif
    
    return aggregatedResult;
}



ValidationContext ValidationEngine::createContext(const std::string& submissionPath, ModuleType moduleType) {
    ValidationContext context(submissionPath, moduleType);
    context.targetPlatform = detectPlatform();
    
    // Discover files in the submission
    discoverFiles(context);
    
    return context;
}

void ValidationEngine::discoverFiles(ValidationContext& context) {
    std::string basePath = context.submissionPath;
    if (!basePath.empty() && basePath[basePath.length() - 1] != '/') {
        basePath += "/";
    }
    
    // Scan directory for C++ files
    scanDirectory(basePath, context);
    
    // Add metadata about discovery
    context.addMetadata("discovery_method", "automatic");
    context.addMetadata("base_path", basePath);
    
    std::ostringstream sourceCount, headerCount;
    sourceCount << context.sourceFiles.size();
    headerCount << context.headerFiles.size();
    
    context.addMetadata("source_files_count", sourceCount.str());
    context.addMetadata("header_files_count", headerCount.str());
}

Platform ValidationEngine::detectPlatform() {
    // Simple platform detection based on preprocessor macros
    #ifdef __APPLE__
        return MACOS;
    #elif defined(__ubuntu__)
        return UBUNTU;
    #elif defined(__linux__)
        return LINUX_GENERIC;
    #else
        return PLATFORM_UNKNOWN;
    #endif
}

void ValidationEngine::sortValidatorsByPriority() {
    // Sort validators by priority (highest first)
    std::sort(validators_.begin(), validators_.end(), ValidatorPriorityComparator());
}

void ValidationEngine::scanDirectory(const std::string& directory, ValidationContext& context) {
#if defined(__unix__) || defined(__APPLE__)
    DIR* dir = opendir(directory.c_str());
    if (dir == NULL) {
        return;
    }
    
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        std::string filename = entry->d_name;
        
        // Skip . and .. entries
        if (filename == "." || filename == "..") {
            continue;
        }
        
        std::string fullPath = directory + filename;
        
        // Check if it's a regular file
        struct stat statbuf;
        if (stat(fullPath.c_str(), &statbuf) == 0 && S_ISREG(statbuf.st_mode)) {
            // Check file extension
            size_t dotPos = filename.find_last_of('.');
            if (dotPos != std::string::npos) {
                std::string extension = filename.substr(dotPos);
                
                if (extension == ".cpp" || extension == ".cc" || extension == ".cxx") {
                    context.addSourceFile(fullPath);
                } else if (extension == ".hpp" || extension == ".h" || extension == ".hxx") {
                    context.addHeaderFile(fullPath);
                }
            }
        }
    }
    
    closedir(dir);
#else
    // Fallback for non-Unix systems - basic implementation
    // This would need platform-specific implementation for Windows
    (void)directory;  // Suppress unused parameter warning
    (void)context;    // Suppress unused parameter warning
    std::cerr << "Directory scanning not implemented for this platform" << std::endl;
#endif
}

int ValidationEngine::getOptimalThreadCount() const {
    if (maxThreads_ > 0) {
        return maxThreads_;
    }
    
#if defined(__unix__) || defined(__APPLE__)
    // Get number of CPU cores
    long numCores = sysconf(_SC_NPROCESSORS_ONLN);
    if (numCores > 0) {
        // Use number of cores, but cap at reasonable maximum
        return (numCores > 8) ? 8 : static_cast<int>(numCores);
    }
#endif
    
    // Default fallback
    return 2;
}