#ifndef VALIDATIONRESULT_HPP
#define VALIDATIONRESULT_HPP

#include <string>
#include <vector>
#include <map>

/**
 * @brief Represents an issue found during validation
 */
struct Issue {
    enum Severity {
        CRITICAL = 0,
        MAJOR = 1,
        MINOR = 2
    };

    Severity severity;
    std::string category;
    std::string message;
    std::string messageJa;        // Japanese message
    std::string fileName;
    int lineNumber;
    std::string suggestion;
    std::string suggestionJa;     // Japanese suggestion
    std::vector<std::string> learningResources;

    Issue() : severity(MINOR), lineNumber(-1) {}
    
    Issue(Severity sev, const std::string& cat, const std::string& msg)
        : severity(sev), category(cat), message(msg), lineNumber(-1) {}
};

/**
 * @brief Contains the result of a validation operation
 */
struct ValidationResult {
    bool isValid;
    std::vector<Issue> issues;
    std::map<std::string, std::string> metrics;
    std::string validatorName;
    
    ValidationResult() : isValid(true) {}
    
    explicit ValidationResult(const std::string& validator) 
        : isValid(true), validatorName(validator) {}
    
    /**
     * @brief Add an issue to the result
     * @param issue The issue to add
     */
    void addIssue(const Issue& issue) {
        issues.push_back(issue);
        if (issue.severity == Issue::CRITICAL || issue.severity == Issue::MAJOR) {
            isValid = false;
        }
    }
    
    /**
     * @brief Add a metric to the result
     * @param key The metric name
     * @param value The metric value
     */
    void addMetric(const std::string& key, const std::string& value) {
        metrics[key] = value;
    }
    
    /**
     * @brief Check if result has critical issues
     * @return true if any critical issues exist
     */
    bool hasCriticalIssues() const {
        for (std::vector<Issue>::const_iterator it = issues.begin(); 
             it != issues.end(); ++it) {
            if (it->severity == Issue::CRITICAL) {
                return true;
            }
        }
        return false;
    }
};

#endif // VALIDATIONRESULT_HPP