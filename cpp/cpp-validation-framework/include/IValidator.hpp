#ifndef IVALIDATOR_HPP
#define IVALIDATOR_HPP

#include "ValidationResult.hpp"
#include "ValidationContext.hpp"
#include <string>

/**
 * @brief Interface for all validation components
 * 
 * This interface defines the contract that all validators must implement.
 * Each validator is responsible for a specific aspect of code validation
 * (compliance, memory, class design, etc.)
 */
class IValidator {
public:
    enum Priority {
        LOW = 1,
        MEDIUM = 2,
        HIGH = 3,
        CRITICAL = 4
    };

    virtual ~IValidator() {}
    
    /**
     * @brief Perform validation on the given context
     * @param context The validation context containing code and metadata
     * @return ValidationResult containing validation outcome and issues
     */
    virtual ValidationResult validate(const ValidationContext& context) = 0;
    
    /**
     * @brief Get the name of this validator
     * @return String identifier for this validator
     */
    virtual std::string getName() const = 0;
    
    /**
     * @brief Get the priority of this validator
     * @return Priority level for execution ordering
     */
    virtual Priority getPriority() const = 0;
};

#endif // IVALIDATOR_HPP