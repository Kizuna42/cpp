#ifndef COMPLIANCECHECKER_HPP
#define COMPLIANCECHECKER_HPP

#include "IValidator.hpp"
#include "ForbiddenFeatureDetector.hpp"
#include "CompilationValidator.hpp"
#include <memory>

/**
 * @brief Comprehensive C++98 compliance checker
 * 
 * This class integrates ForbiddenFeatureDetector and CompilationValidator
 * to provide a complete C++98 standard compliance check. It detects
 * forbidden features and validates compilation with strict flags.
 */
class ComplianceChecker : public IValidator {
public:
    ComplianceChecker();
    virtual ~ComplianceChecker();
    
    // IValidator interface implementation
    virtual ValidationResult validate(const ValidationContext& context);
    virtual std::string getName() const;
    virtual Priority getPriority() const;
    
    /**
     * @brief Check C++98 compliance of source code
     * @param context The validation context containing source files
     * @return true if code is fully C++98 compliant
     */
    bool checkCpp98Compliance(const ValidationContext& context);
    
    /**
     * @brief Get the forbidden feature detector
     * @return Reference to the forbidden feature detector
     */
    ForbiddenFeatureDetector& getForbiddenFeatureDetector();
    
    /**
     * @brief Get the compilation validator
     * @return Reference to the compilation validator
     */
    CompilationValidator& getCompilationValidator();

private:
    ForbiddenFeatureDetector forbiddenDetector_;
    CompilationValidator compilationValidator_;
    
    /**
     * @brief Merge validation results from multiple validators
     * @param results Vector of validation results to merge
     * @return Merged validation result
     */
    ValidationResult mergeResults(const std::vector<ValidationResult>& results);
    
    /**
     * @brief Add localized messages to issues
     * @param result The validation result to localize
     */
    void localizeMessages(ValidationResult& result);
    
    /**
     * @brief Prioritize issues by severity and type
     * @param result The validation result to prioritize
     */
    void prioritizeIssues(ValidationResult& result);
    
    /**
     * @brief Add compliance summary metrics
     * @param result The validation result to add metrics to
     * @param context The validation context
     */
    void addComplianceMetrics(ValidationResult& result, const ValidationContext& context);
};

#endif // COMPLIANCECHECKER_HPP