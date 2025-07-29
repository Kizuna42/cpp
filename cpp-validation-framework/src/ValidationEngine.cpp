#include "ValidationEngine.hpp"
#include <algorithm>
#include <iostream>

// Helper comparator for sorting validators by priority
struct ValidatorPriorityComparator {
    bool operator()(const IValidator* a, const IValidator* b) const {
        return a->getPriority() > b->getPriority();
    }
};

ValidationEngine::ValidationEngine() {
}

ValidationEngine::~ValidationEngine() {
    clearValidators();
}

ValidationResult ValidationEngine::validate(const std::string& submissionPath, ModuleType moduleType) {
    ValidationContext context = createContext(submissionPath, moduleType);
    return validate(context);
}

ValidationResult ValidationEngine::validate(const ValidationContext& context) {
    ValidationResult aggregatedResult("ValidationEngine");
    
    // Sort validators by priority before execution
    const_cast<ValidationEngine*>(this)->sortValidatorsByPriority();
    
    // Execute each validator
    for (std::vector<IValidator*>::const_iterator it = validators_.begin();
         it != validators_.end(); ++it) {
        
        IValidator* validator = *it;
        try {
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
            
        } catch (const std::exception& e) {
            // Handle validator exceptions gracefully
            Issue issue(Issue::CRITICAL, "VALIDATOR_ERROR", 
                       "Validator " + validator->getName() + " failed: " + e.what());
            aggregatedResult.addIssue(issue);
        }
    }
    
    return aggregatedResult;
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

ValidationContext ValidationEngine::createContext(const std::string& submissionPath, ModuleType moduleType) {
    ValidationContext context(submissionPath, moduleType);
    context.targetPlatform = detectPlatform();
    
    // Discover files in the submission
    discoverFiles(context);
    
    return context;
}

void ValidationEngine::discoverFiles(ValidationContext& context) {
    // This is a simplified implementation
    // In a real implementation, we would scan the directory for .cpp and .hpp files
    
    // For now, add some common file patterns based on module type
    std::string basePath = context.submissionPath;
    if (!basePath.empty() && basePath[basePath.length() - 1] != '/') {
        basePath += "/";
    }
    
    // Add metadata about discovery
    context.addMetadata("discovery_method", "automatic");
    context.addMetadata("base_path", basePath);
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