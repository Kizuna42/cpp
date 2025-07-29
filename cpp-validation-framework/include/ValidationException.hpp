#ifndef VALIDATIONEXCEPTION_HPP
#define VALIDATIONEXCEPTION_HPP

#include <exception>
#include <string>

/**
 * @brief Enumeration of error codes for different types of validation errors
 */
enum ErrorCode {
    // File system errors
    FILE_NOT_FOUND = 1000,
    FILE_ACCESS_DENIED = 1001,
    DIRECTORY_NOT_FOUND = 1002,
    INVALID_FILE_PATH = 1003,
    
    // Compilation errors
    COMPILATION_FAILED = 2000,
    COMPILER_NOT_FOUND = 2001,
    INVALID_COMPILER_FLAGS = 2002,
    LINKING_FAILED = 2003,
    
    // Memory analysis errors
    MEMORY_TOOL_ERROR = 3000,
    ADDRESSSANITIZER_FAILED = 3001,
    VALGRIND_FAILED = 3002,
    MEMORY_TOOL_NOT_AVAILABLE = 3003,
    
    // Configuration errors
    INVALID_MODULE_CONFIG = 4000,
    MISSING_MODULE_RULES = 4001,
    INVALID_PLATFORM_CONFIG = 4002,
    CONFIGURATION_PARSE_ERROR = 4003,
    
    // External tool errors
    EXTERNAL_TOOL_UNAVAILABLE = 5000,
    EXTERNAL_TOOL_TIMEOUT = 5001,
    EXTERNAL_TOOL_CRASH = 5002,
    EXTERNAL_TOOL_INVALID_OUTPUT = 5003,
    
    // Validation logic errors
    INVALID_VALIDATION_CONTEXT = 6000,
    VALIDATOR_INITIALIZATION_FAILED = 6001,
    VALIDATION_LOGIC_ERROR = 6002,
    UNSUPPORTED_OPERATION = 6003,
    
    // System errors
    INSUFFICIENT_PERMISSIONS = 7000,
    INSUFFICIENT_MEMORY = 7001,
    SYSTEM_RESOURCE_UNAVAILABLE = 7002,
    PLATFORM_NOT_SUPPORTED = 7003,
    
    // Unknown error
    UNKNOWN_ERROR = 9999
};

/**
 * @brief Custom exception class for validation framework errors
 * 
 * This exception class provides detailed error information including
 * error codes, messages, and context information for debugging.
 */
class ValidationException : public std::exception {
private:
    std::string message_;
    std::string messageJa_;  // Japanese message
    ErrorCode errorCode_;
    std::string context_;
    std::string suggestion_;
    std::string suggestionJa_;  // Japanese suggestion
    
public:
    /**
     * @brief Constructor with message and error code
     * @param message Error message in English
     * @param code Error code
     */
    ValidationException(const std::string& message, ErrorCode code)
        : message_(message), errorCode_(code) {}
    
    /**
     * @brief Constructor with bilingual messages and error code
     * @param message Error message in English
     * @param messageJa Error message in Japanese
     * @param code Error code
     */
    ValidationException(const std::string& message, const std::string& messageJa, ErrorCode code)
        : message_(message), messageJa_(messageJa), errorCode_(code) {}
    
    /**
     * @brief Constructor with full error information
     * @param message Error message in English
     * @param messageJa Error message in Japanese
     * @param code Error code
     * @param context Additional context information
     * @param suggestion Suggested solution in English
     * @param suggestionJa Suggested solution in Japanese
     */
    ValidationException(const std::string& message, const std::string& messageJa,
                       ErrorCode code, const std::string& context,
                       const std::string& suggestion, const std::string& suggestionJa)
        : message_(message), messageJa_(messageJa), errorCode_(code),
          context_(context), suggestion_(suggestion), suggestionJa_(suggestionJa) {}
    
    /**
     * @brief Destructor
     */
    virtual ~ValidationException() throw() {}
    
    /**
     * @brief Get the error message
     * @return Error message string
     */
    virtual const char* what() const throw() {
        return message_.c_str();
    }
    
    /**
     * @brief Get the error code
     * @return ErrorCode enumeration value
     */
    ErrorCode getErrorCode() const {
        return errorCode_;
    }
    
    /**
     * @brief Get the English error message
     * @return English error message
     */
    const std::string& getMessage() const {
        return message_;
    }
    
    /**
     * @brief Get the Japanese error message
     * @return Japanese error message
     */
    const std::string& getMessageJa() const {
        return messageJa_;
    }
    
    /**
     * @brief Get the context information
     * @return Context string
     */
    const std::string& getContext() const {
        return context_;
    }
    
    /**
     * @brief Get the English suggestion
     * @return English suggestion string
     */
    const std::string& getSuggestion() const {
        return suggestion_;
    }
    
    /**
     * @brief Get the Japanese suggestion
     * @return Japanese suggestion string
     */
    const std::string& getSuggestionJa() const {
        return suggestionJa_;
    }
    
    /**
     * @brief Set context information
     * @param context Context string
     */
    void setContext(const std::string& context) {
        context_ = context;
    }
    
    /**
     * @brief Set suggestion in both languages
     * @param suggestion English suggestion
     * @param suggestionJa Japanese suggestion
     */
    void setSuggestion(const std::string& suggestion, const std::string& suggestionJa) {
        suggestion_ = suggestion;
        suggestionJa_ = suggestionJa;
    }
    
    /**
     * @brief Check if this is a critical error
     * @return true if the error is critical
     */
    bool isCritical() const {
        return errorCode_ >= COMPILATION_FAILED && errorCode_ < INVALID_MODULE_CONFIG;
    }
    
    /**
     * @brief Check if this is a system error
     * @return true if the error is system-related
     */
    bool isSystemError() const {
        return errorCode_ >= INSUFFICIENT_PERMISSIONS && errorCode_ < UNKNOWN_ERROR;
    }
    
    /**
     * @brief Check if this is a configuration error
     * @return true if the error is configuration-related
     */
    bool isConfigurationError() const {
        return errorCode_ >= INVALID_MODULE_CONFIG && errorCode_ < EXTERNAL_TOOL_UNAVAILABLE;
    }
    
    /**
     * @brief Get error category as string
     * @return String representation of error category
     */
    std::string getErrorCategory() const {
        if (errorCode_ >= FILE_NOT_FOUND && errorCode_ < COMPILATION_FAILED) {
            return "FILE_SYSTEM";
        } else if (errorCode_ >= COMPILATION_FAILED && errorCode_ < MEMORY_TOOL_ERROR) {
            return "COMPILATION";
        } else if (errorCode_ >= MEMORY_TOOL_ERROR && errorCode_ < INVALID_MODULE_CONFIG) {
            return "MEMORY_ANALYSIS";
        } else if (errorCode_ >= INVALID_MODULE_CONFIG && errorCode_ < EXTERNAL_TOOL_UNAVAILABLE) {
            return "CONFIGURATION";
        } else if (errorCode_ >= EXTERNAL_TOOL_UNAVAILABLE && errorCode_ < INVALID_VALIDATION_CONTEXT) {
            return "EXTERNAL_TOOL";
        } else if (errorCode_ >= INVALID_VALIDATION_CONTEXT && errorCode_ < INSUFFICIENT_PERMISSIONS) {
            return "VALIDATION_LOGIC";
        } else if (errorCode_ >= INSUFFICIENT_PERMISSIONS && errorCode_ < UNKNOWN_ERROR) {
            return "SYSTEM";
        } else {
            return "UNKNOWN";
        }
    }
    
    /**
     * @brief Get formatted error message with all details
     * @return Formatted error message
     */
    std::string getFormattedMessage() const {
        std::string formatted = "[" + getErrorCategory() + ":" + 
                               getErrorCodeString() + "] " + message_;
        
        if (!context_.empty()) {
            formatted += " (Context: " + context_ + ")";
        }
        
        if (!suggestion_.empty()) {
            formatted += " Suggestion: " + suggestion_;
        }
        
        return formatted;
    }
    
    /**
     * @brief Get error code as string
     * @return String representation of error code
     */
    std::string getErrorCodeString() const {
        switch (errorCode_) {
            case FILE_NOT_FOUND: return "FILE_NOT_FOUND";
            case FILE_ACCESS_DENIED: return "FILE_ACCESS_DENIED";
            case DIRECTORY_NOT_FOUND: return "DIRECTORY_NOT_FOUND";
            case INVALID_FILE_PATH: return "INVALID_FILE_PATH";
            case COMPILATION_FAILED: return "COMPILATION_FAILED";
            case COMPILER_NOT_FOUND: return "COMPILER_NOT_FOUND";
            case INVALID_COMPILER_FLAGS: return "INVALID_COMPILER_FLAGS";
            case LINKING_FAILED: return "LINKING_FAILED";
            case MEMORY_TOOL_ERROR: return "MEMORY_TOOL_ERROR";
            case ADDRESSSANITIZER_FAILED: return "ADDRESSSANITIZER_FAILED";
            case VALGRIND_FAILED: return "VALGRIND_FAILED";
            case MEMORY_TOOL_NOT_AVAILABLE: return "MEMORY_TOOL_NOT_AVAILABLE";
            case INVALID_MODULE_CONFIG: return "INVALID_MODULE_CONFIG";
            case MISSING_MODULE_RULES: return "MISSING_MODULE_RULES";
            case INVALID_PLATFORM_CONFIG: return "INVALID_PLATFORM_CONFIG";
            case CONFIGURATION_PARSE_ERROR: return "CONFIGURATION_PARSE_ERROR";
            case EXTERNAL_TOOL_UNAVAILABLE: return "EXTERNAL_TOOL_UNAVAILABLE";
            case EXTERNAL_TOOL_TIMEOUT: return "EXTERNAL_TOOL_TIMEOUT";
            case EXTERNAL_TOOL_CRASH: return "EXTERNAL_TOOL_CRASH";
            case EXTERNAL_TOOL_INVALID_OUTPUT: return "EXTERNAL_TOOL_INVALID_OUTPUT";
            case INVALID_VALIDATION_CONTEXT: return "INVALID_VALIDATION_CONTEXT";
            case VALIDATOR_INITIALIZATION_FAILED: return "VALIDATOR_INITIALIZATION_FAILED";
            case VALIDATION_LOGIC_ERROR: return "VALIDATION_LOGIC_ERROR";
            case UNSUPPORTED_OPERATION: return "UNSUPPORTED_OPERATION";
            case INSUFFICIENT_PERMISSIONS: return "INSUFFICIENT_PERMISSIONS";
            case INSUFFICIENT_MEMORY: return "INSUFFICIENT_MEMORY";
            case SYSTEM_RESOURCE_UNAVAILABLE: return "SYSTEM_RESOURCE_UNAVAILABLE";
            case PLATFORM_NOT_SUPPORTED: return "PLATFORM_NOT_SUPPORTED";
            default: return "UNKNOWN_ERROR";
        }
    }
};

/**
 * @brief Factory class for creating common validation exceptions
 */
class ValidationExceptionFactory {
public:
    /**
     * @brief Create file not found exception
     * @param filePath The path of the missing file
     * @return ValidationException for file not found
     */
    static ValidationException createFileNotFound(const std::string& filePath) {
        ValidationException ex(
            "File not found: " + filePath,
            "ファイルが見つかりません: " + filePath,
            FILE_NOT_FOUND
        );
        ex.setContext("File path: " + filePath);
        ex.setSuggestion(
            "Check if the file exists and the path is correct",
            "ファイルが存在し、パスが正しいことを確認してください"
        );
        return ex;
    }
    
    /**
     * @brief Create compilation failed exception
     * @param compilerOutput The compiler error output
     * @return ValidationException for compilation failure
     */
    static ValidationException createCompilationFailed(const std::string& compilerOutput) {
        ValidationException ex(
            "Compilation failed",
            "コンパイルに失敗しました",
            COMPILATION_FAILED
        );
        ex.setContext("Compiler output: " + compilerOutput);
        ex.setSuggestion(
            "Fix the compilation errors shown in the output",
            "出力に表示されているコンパイルエラーを修正してください"
        );
        return ex;
    }
    
    /**
     * @brief Create memory tool error exception
     * @param toolName The name of the memory analysis tool
     * @param errorMessage The error message from the tool
     * @return ValidationException for memory tool error
     */
    static ValidationException createMemoryToolError(const std::string& toolName, 
                                                    const std::string& errorMessage) {
        ValidationException ex(
            "Memory analysis tool error: " + toolName,
            "メモリ解析ツールエラー: " + toolName,
            MEMORY_TOOL_ERROR
        );
        ex.setContext("Tool: " + toolName + ", Error: " + errorMessage);
        ex.setSuggestion(
            "Check if the memory analysis tool is properly installed",
            "メモリ解析ツールが正しくインストールされているか確認してください"
        );
        return ex;
    }
    
    /**
     * @brief Create invalid module configuration exception
     * @param moduleName The name of the invalid module
     * @return ValidationException for invalid module configuration
     */
    static ValidationException createInvalidModuleConfig(const std::string& moduleName) {
        ValidationException ex(
            "Invalid module configuration: " + moduleName,
            "無効なモジュール設定: " + moduleName,
            INVALID_MODULE_CONFIG
        );
        ex.setContext("Module: " + moduleName);
        ex.setSuggestion(
            "Check the module configuration and ensure it's valid",
            "モジュール設定を確認し、有効であることを確認してください"
        );
        return ex;
    }
};

#endif // VALIDATIONEXCEPTION_HPP