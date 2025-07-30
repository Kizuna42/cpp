#ifndef COMPILATIONVALIDATOR_HPP
#define COMPILATIONVALIDATOR_HPP

#include "IValidator.hpp"
#include <string>
#include <vector>

/**
 * @brief Represents a compilation error
 */
struct CompilationError {
    std::string fileName;
    int lineNumber;
    int columnNumber;
    std::string errorType;
    std::string message;
    std::string suggestion;
    std::string suggestionJa;
    
    CompilationError() : lineNumber(-1), columnNumber(-1) {}
    
    CompilationError(const std::string& file, int line, int col, 
                    const std::string& type, const std::string& msg)
        : fileName(file), lineNumber(line), columnNumber(col), 
          errorType(type), message(msg) {}
};

/**
 * @brief Validates C++98 compilation with strict flags
 * 
 * This class compiles source code using -Wall -Wextra -Werror -std=c++98
 * flags and analyzes compilation errors to provide detailed feedback.
 */
class CompilationValidator : public IValidator {
public:
    CompilationValidator();
    virtual ~CompilationValidator();
    
    // IValidator interface implementation
    virtual ValidationResult validate(const ValidationContext& context);
    virtual std::string getName() const;
    virtual Priority getPriority() const;
    
    /**
     * @brief Compile source files with C++98 strict flags
     * @param context The validation context containing files and config
     * @return true if compilation succeeds, false otherwise
     */
    bool compileWithStrictFlags(const ValidationContext& context);
    
    /**
     * @brief Parse compilation errors from compiler output
     * @param compilerOutput The raw output from the compiler
     * @return Vector of parsed compilation errors
     */
    std::vector<CompilationError> parseCompilationErrors(const std::string& compilerOutput);
    
    /**
     * @brief Build compilation command from context (public for testing)
     * @param context The validation context
     * @param outputFile The output executable name
     * @return Complete compilation command string
     */
    std::string buildCompilationCommand(const ValidationContext& context, 
                                       const std::string& outputFile);
    
    /**
     * @brief Parse a single error line from compiler output (public for testing)
     * @param errorLine The error line to parse
     * @return CompilationError object, or empty if parsing fails
     */
    CompilationError parseErrorLine(const std::string& errorLine);
    
    /**
     * @brief Check if error is related to C++11+ features (public for testing)
     * @param message The error message
     * @return true if it's a C++11+ related error
     */
    bool isCpp11Error(const std::string& message);
    
    /**
     * @brief Generate suggestion for common compilation errors (public for testing)
     * @param errorType The type of compilation error
     * @param message The error message
     * @return Pair of English and Japanese suggestions
     */
    std::pair<std::string, std::string> generateSuggestion(const std::string& errorType, 
                                                           const std::string& message);

private:
    /**
     * @brief Execute compilation command and capture output
     * @param command The compilation command to execute
     * @param output Reference to store the compiler output
     * @return Exit code of the compilation process
     */
    int executeCompilation(const std::string& command, std::string& output);
    

    
    /**
     * @brief Create an issue from a compilation error
     * @param error The compilation error
     * @return Issue object for the validation result
     */
    Issue createIssueFromError(const CompilationError& error);
    
    /**
     * @brief Clean up temporary files created during compilation
     * @param outputFile The output file to clean up
     */
    void cleanupTempFiles(const std::string& outputFile);
    
    /**
     * @brief Extract file path from compiler error message
     * @param errorLine The error line from compiler
     * @return Extracted file path
     */
    std::string extractFilePath(const std::string& errorLine);
    
    /**
     * @brief Extract line and column numbers from error message
     * @param errorLine The error line from compiler
     * @param lineNumber Reference to store line number
     * @param columnNumber Reference to store column number
     * @return true if extraction was successful
     */
    bool extractLineAndColumn(const std::string& errorLine, int& lineNumber, int& columnNumber);
};

#endif // COMPILATIONVALIDATOR_HPP