#ifndef VALIDATIONENGINE_HPP
#define VALIDATIONENGINE_HPP

#include "IValidator.hpp"
#include "ValidationResult.hpp"
#include "ValidationContext.hpp"
#include <vector>
#include <string>

// Forward declarations for threading
struct ValidatorTask;
struct ThreadPool;

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
    bool enableParallelProcessing_;
    int maxThreads_;
    
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
    
    /**
     * @brief Get list of validator names
     * @return Vector of validator names
     */
    std::vector<std::string> getValidatorNames() const;
    
    /**
     * @brief Enable or disable parallel processing
     * @param enable True to enable parallel processing
     */
    void setParallelProcessing(bool enable);
    
    /**
     * @brief Set maximum number of threads for parallel processing
     * @param maxThreads Maximum number of threads (0 = auto-detect)
     */
    void setMaxThreads(int maxThreads);
    
    /**
     * @brief Get current parallel processing setting
     * @return True if parallel processing is enabled
     */
    bool isParallelProcessingEnabled() const;

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
    
    /**
     * @brief Scan directory for C++ source and header files
     * @param directory Directory to scan
     * @param context Context to populate with discovered files
     */
    void scanDirectory(const std::string& directory, ValidationContext& context);
    
    /**
     * @brief Execute validators in parallel
     * @param context The validation context
     * @return Aggregated validation result
     */
    ValidationResult executeValidatorsParallel(const ValidationContext& context);
    
    /**
     * @brief Execute validators sequentially
     * @param context The validation context
     * @return Aggregated validation result
     */
    ValidationResult executeValidatorsSequential(const ValidationContext& context);
    
    /**
     * @brief Get optimal number of threads for current system
     * @return Number of threads to use
     */
    int getOptimalThreadCount() const;
};

#endif // VALIDATIONENGINE_HPP