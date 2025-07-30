#include "ComplianceChecker.hpp"
#include <algorithm>
#include <sstream>

ComplianceChecker::ComplianceChecker() {
}

ComplianceChecker::~ComplianceChecker() {
}

ValidationResult ComplianceChecker::validate(const ValidationContext& context) {
    std::vector<ValidationResult> results;
    
    // Check if we have source files to validate
    if (context.sourceFiles.empty()) {
        ValidationResult errorResult(getName());
        Issue noSourceFiles;
        noSourceFiles.severity = Issue::CRITICAL;
        noSourceFiles.category = "NO_SOURCE_FILES";
        noSourceFiles.message = "No source files provided for validation";
        noSourceFiles.messageJa = "検証用のソースファイルが提供されていません";
        noSourceFiles.suggestion = "Provide at least one C++ source file for validation";
        noSourceFiles.suggestionJa = "検証のために少なくとも1つのC++ソースファイルを提供してください";
        noSourceFiles.fileName = "";
        noSourceFiles.lineNumber = 0;
        noSourceFiles.learningResources.push_back("https://www.cplusplus.com/doc/tutorial/");
        errorResult.addIssue(noSourceFiles);
        errorResult.isValid = false;
        return errorResult;
    }
    
    try {
        // Run forbidden feature detection first
        ValidationResult forbiddenResult = forbiddenDetector_.validate(context);
        results.push_back(forbiddenResult);
        
        // Run compilation validation
        ValidationResult compilationResult = compilationValidator_.validate(context);
        results.push_back(compilationResult);
        
        // Merge results
        ValidationResult mergedResult = mergeResults(results);
        mergedResult.validatorName = getName();
        
        // Add localized messages
        localizeMessages(mergedResult);
        
        // Prioritize issues
        prioritizeIssues(mergedResult);
        
        // Add compliance metrics
        addComplianceMetrics(mergedResult, context);
        
        return mergedResult;
        
    } catch (const std::exception& e) {
        // Handle validation errors gracefully
        ValidationResult errorResult(getName());
        Issue validationError;
        validationError.severity = Issue::CRITICAL;
        validationError.category = "VALIDATION_ERROR";
        validationError.message = std::string("Validation failed: ") + e.what();
        validationError.messageJa = std::string("検証に失敗しました: ") + e.what();
        validationError.suggestion = "Check file permissions and content validity";
        validationError.suggestionJa = "ファイルの権限と内容の有効性を確認してください";
        validationError.fileName = "";
        validationError.lineNumber = 0;
        validationError.learningResources.push_back("https://www.cplusplus.com/doc/tutorial/");
        errorResult.addIssue(validationError);
        errorResult.isValid = false;
        return errorResult;
    }
}

std::string ComplianceChecker::getName() const {
    return "ComplianceChecker";
}

IValidator::Priority ComplianceChecker::getPriority() const {
    return CRITICAL;
}

bool ComplianceChecker::checkCpp98Compliance(const ValidationContext& context) {
    ValidationResult result = validate(context);
    
    // Check if there are any critical or major issues
    for (std::vector<Issue>::const_iterator it = result.issues.begin();
         it != result.issues.end(); ++it) {
        if (it->severity == Issue::CRITICAL || it->severity == Issue::MAJOR) {
            return false;
        }
    }
    
    return true;
}

ForbiddenFeatureDetector& ComplianceChecker::getForbiddenFeatureDetector() {
    return forbiddenDetector_;
}

CompilationValidator& ComplianceChecker::getCompilationValidator() {
    return compilationValidator_;
}

ValidationResult ComplianceChecker::mergeResults(const std::vector<ValidationResult>& results) {
    ValidationResult merged("ComplianceChecker");
    
    bool overallValid = true;
    
    for (std::vector<ValidationResult>::const_iterator it = results.begin();
         it != results.end(); ++it) {
        
        // Merge issues
        for (std::vector<Issue>::const_iterator issueIt = it->issues.begin();
             issueIt != it->issues.end(); ++issueIt) {
            merged.addIssue(*issueIt);
        }
        
        // Merge metrics with prefixes to avoid conflicts
        for (std::map<std::string, std::string>::const_iterator metricIt = it->metrics.begin();
             metricIt != it->metrics.end(); ++metricIt) {
            
            std::string prefixedKey = it->validatorName + "_" + metricIt->first;
            merged.addMetric(prefixedKey, metricIt->second);
        }
        
        // Update overall validity
        if (!it->isValid) {
            overallValid = false;
        }
    }
    
    merged.isValid = overallValid;
    
    return merged;
}

void ComplianceChecker::localizeMessages(ValidationResult& result) {
    for (std::vector<Issue>::iterator it = result.issues.begin();
         it != result.issues.end(); ++it) {
        
        // Add Japanese translations if not already present
        if (it->messageJa.empty()) {
            if (it->category.find("FORBIDDEN_FEATURE") != std::string::npos) {
                // More specific translations based on the forbidden feature type
                if (it->category.find("using_namespace") != std::string::npos) {
                    it->messageJa = "using namespaceは42スクールの課題では禁止されています";
                } else if (it->category.find("auto") != std::string::npos) {
                    it->messageJa = "C++11の'auto'キーワードはC++98では使用できません";
                } else if (it->category.find("std_vector") != std::string::npos ||
                          it->category.find("std_map") != std::string::npos ||
                          it->category.find("std_set") != std::string::npos) {
                    it->messageJa = "STLコンテナは42スクールの課題では禁止されています";
                } else if (it->category.find("friend") != std::string::npos) {
                    it->messageJa = "friendキーワードは42スクールの課題では禁止されています";
                } else {
                    it->messageJa = "禁止された機能が検出されました: " + it->message;
                }
            } else if (it->category == "COMPILATION_ERROR") {
                it->messageJa = "コンパイルエラー: " + it->message;
            } else if (it->category == "COMPILATION_SUCCESS") {
                it->messageJa = "コンパイル成功: C++98準拠";
            } else if (it->category == "NO_SOURCE_FILES") {
                it->messageJa = "検証用のソースファイルが提供されていません";
            } else if (it->category == "VALIDATION_ERROR") {
                it->messageJa = "検証エラー: " + it->message;
            } else {
                it->messageJa = "問題が検出されました: " + it->message;
            }
        }
        
        // Add Japanese suggestions if not already present
        if (it->suggestionJa.empty() && !it->suggestion.empty()) {
            if (it->category.find("FORBIDDEN_FEATURE") != std::string::npos) {
                if (it->category.find("using_namespace") != std::string::npos) {
                    it->suggestionJa = "'using namespace'を削除し、完全修飾名を使用してください";
                } else if (it->category.find("auto") != std::string::npos) {
                    it->suggestionJa = "'auto'を明示的な型宣言に置き換えてください";
                } else if (it->category.find("std_") != std::string::npos) {
                    it->suggestionJa = "STLコンテナの代わりに独自のデータ構造を実装してください";
                } else if (it->category.find("friend") != std::string::npos) {
                    it->suggestionJa = "friendキーワードを使用せずに設計を見直してください";
                } else {
                    it->suggestionJa = "C++98互換の代替手段を使用してください";
                }
            } else if (it->category == "COMPILATION_ERROR") {
                it->suggestionJa = "コンパイルエラーを修正してください";
            } else if (it->category == "NO_SOURCE_FILES") {
                it->suggestionJa = "検証のために少なくとも1つのC++ソースファイルを提供してください";
            } else {
                it->suggestionJa = "問題を修正してください";
            }
        }
        
        // Add learning resources if not present
        if (it->learningResources.empty()) {
            it->learningResources.push_back("https://www.cplusplus.com/doc/tutorial/");
            it->learningResources.push_back("https://en.cppreference.com/w/cpp/98");
            it->learningResources.push_back("https://isocpp.org/std/the-standard");
            
            // Add specific resources based on issue type
            if (it->category.find("FORBIDDEN_FEATURE") != std::string::npos) {
                it->learningResources.push_back("https://42.fr/en/curriculum/");
                it->learningResources.push_back("https://stackoverflow.com/questions/tagged/c%2b%2b98");
            }
            if (it->category == "COMPILATION_ERROR") {
                it->learningResources.push_back("https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html");
            }
        }
    }
}

// Helper function for sorting issues
bool compareIssues(const Issue& a, const Issue& b) {
    if (a.severity != b.severity) {
        return a.severity < b.severity; // CRITICAL=0, MAJOR=1, MINOR=2
    }
    // If same severity, sort by category
    return a.category < b.category;
}

void ComplianceChecker::prioritizeIssues(ValidationResult& result) {
    // Sort issues by severity (CRITICAL first, then MAJOR, then MINOR)
    std::sort(result.issues.begin(), result.issues.end(), compareIssues);
}

void ComplianceChecker::addComplianceMetrics(ValidationResult& result, const ValidationContext& context) {
    // Count issues by severity
    int criticalCount = 0;
    int majorCount = 0;
    int minorCount = 0;
    
    for (std::vector<Issue>::const_iterator it = result.issues.begin();
         it != result.issues.end(); ++it) {
        switch (it->severity) {
            case Issue::CRITICAL:
                criticalCount++;
                break;
            case Issue::MAJOR:
                majorCount++;
                break;
            case Issue::MINOR:
                minorCount++;
                break;
        }
    }
    
    result.addMetric("critical_issues", std::to_string(criticalCount));
    result.addMetric("major_issues", std::to_string(majorCount));
    result.addMetric("minor_issues", std::to_string(minorCount));
    result.addMetric("total_issues", std::to_string(result.issues.size()));
    
    // Add compliance status
    if (criticalCount == 0 && majorCount == 0) {
        result.addMetric("compliance_status", "COMPLIANT");
        result.addMetric("compliance_level", "FULL");
    } else if (criticalCount == 0) {
        result.addMetric("compliance_status", "PARTIAL");
        result.addMetric("compliance_level", "MAJOR_ISSUES_ONLY");
    } else {
        result.addMetric("compliance_status", "NON_COMPLIANT");
        result.addMetric("compliance_level", "CRITICAL_ISSUES");
    }
    
    // Add module information
    result.addMetric("module_type", context.getModuleTypeString());
    result.addMetric("target_platform", context.getPlatformString());
    
    // Add file count metrics
    result.addMetric("source_files_count", std::to_string(context.sourceFiles.size()));
    result.addMetric("header_files_count", std::to_string(context.headerFiles.size()));
    
    // Add compiler information
    result.addMetric("compiler", context.compilerConfig.compiler);
    result.addMetric("cpp_standard", context.compilerConfig.standard);
    
    // Build flags string
    std::ostringstream flagsStream;
    for (std::vector<std::string>::const_iterator it = context.compilerConfig.flags.begin();
         it != context.compilerConfig.flags.end(); ++it) {
        if (it != context.compilerConfig.flags.begin()) {
            flagsStream << " ";
        }
        flagsStream << *it;
    }
    result.addMetric("compiler_flags", flagsStream.str());
}