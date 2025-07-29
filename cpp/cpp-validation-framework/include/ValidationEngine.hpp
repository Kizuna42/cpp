#ifndef VALIDATIONENGINE_HPP
#define VALIDATIONENGINE_HPP

#include "IValidator.hpp"
#include "ValidationResult.hpp"
#include "ValidationContext.hpp"
#include <vector>
#include <string>

/**
 * @brief Main validation engine that orchestrates all validation processes
 * 
 * The ValidationEngine is responsible for coordinating multiple validators,
 * managing the validation context, and aggregating results from all
 * validation components.
 */
class ValidationEngine {
private:
    std::vector<IValidator*> validators_;
    
public:
    ValidationEngine();
    ~ValidationEngine();
    
    /**
     * @brief Validate a submission using all registered validators
     * @param submissionPath Path to the submission directory
     * @param moduleType The module type being validated
     * @return Aggregated validation result
     */
    ValidationResult validate(const std::string& submissionPath, ModuleType moduleType);
    
    /**
     * @brief Validate using a pre-configured context
     * @param context The validation context
     * @return Aggregated validation result
     */
    ValidationResult validate(const ValidationContext& context);
    
    /**
     * @brief Add a validator to the engine
     * @param validator Pointer to validator (engine takes ownership)
     */
    void addValidator(IValidator* validator);
    
    /**
     * @brief Remove all validators
     */
    void clearValidators();
    
    /**
     * @brief Get the number of registered validators
     * @return Number of validators
     */
    size_t getValidatorCount() const;

private:
    /**
     * @brief Create validation context from submission path
     * @param submissionPath Path to submission
     * @param moduleType Module type
     * @return Configured validation context
     */
    ValidationContext createContext(const std::string& submissionPath, ModuleType moduleType);
    
    /**
     * @brief Discover source and header files in submission
     * @param context Context to populate with file information
     */
    void discoverFiles(ValidationContext& context);
    
    /**
     * @brief Detect platform automatically
     * @return Detected platform
     */
    Platform detectPlatform();
    
    /**
     * @brief Sort validators by priority
     */
    void sortValidatorsByPriority();
};

#endif // VALIDATIONENGINE_HPP