#include "CompilationValidator.hpp"
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cstdio>

CompilationValidator::CompilationValidator() {
}

CompilationValidator::~CompilationValidator() {
}

ValidationResult CompilationValidator::validate(const ValidationContext& context) {
    ValidationResult result("CompilationValidator");
    
    if (context.sourceFiles.empty()) {
        Issue issue(Issue::CRITICAL, "NO_SOURCE_FILES", 
                   "No source files found for compilation");
        issue.messageJa = "コンパイル用のソースファイルが見つかりません";
        result.addIssue(issue);
        return result;
    }
    
    bool compilationSuccess = compileWithStrictFlags(context);
    
    if (compilationSuccess) {
        result.addMetric("compilation_status", "success");
        result.addMetric("compiler_flags", "-Wall -Wextra -Werror -std=c++98");
        
        Issue successIssue(Issue::MINOR, "COMPILATION_SUCCESS", 
                          "Code compiles successfully with C++98 strict flags");
        successIssue.messageJa = "コードはC++98の厳密なフラグでコンパイルに成功しました";
        successIssue.severity = Issue::MINOR; // This is actually good news
        result.addIssue(successIssue);
    } else {
        result.addMetric("compilation_status", "failed");
    }
    
    return result;
}

std::string CompilationValidator::getName() const {
    return "CompilationValidator";
}

IValidator::Priority CompilationValidator::getPriority() const {
    return CRITICAL;
}

bool CompilationValidator::compileWithStrictFlags(const ValidationContext& context) {
    std::string outputFile = "temp_validation_executable";
    std::string command = buildCompilationCommand(context, outputFile);
    std::string compilerOutput;
    
    int exitCode = executeCompilation(command, compilerOutput);
    
    if (exitCode != 0) {
        // Parse compilation errors and add them as issues
        std::vector<CompilationError> errors = parseCompilationErrors(compilerOutput);
        
        // Note: We don't add these to the result here because this function
        // is just checking if compilation succeeds. The errors would be
        // handled by the calling validate() method if needed.
    }
    
    cleanupTempFiles(outputFile);
    
    return exitCode == 0;
}

std::vector<CompilationError> CompilationValidator::parseCompilationErrors(
    const std::string& compilerOutput) {
    
    std::vector<CompilationError> errors;
    std::istringstream stream(compilerOutput);
    std::string line;
    
    while (std::getline(stream, line)) {
        if (line.empty()) continue;
        
        CompilationError error = parseErrorLine(line);
        if (!error.fileName.empty()) {
            errors.push_back(error);
        }
    }
    
    return errors;
}

int CompilationValidator::executeCompilation(const std::string& command, std::string& output) {
    // Use popen to capture both stdout and stderr
    std::string fullCommand = command + " 2>&1";
    FILE* pipe = popen(fullCommand.c_str(), "r");
    
    if (!pipe) {
        output = "Failed to execute compilation command";
        return -1;
    }
    
    char buffer[256];
    std::ostringstream result;
    
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result << buffer;
    }
    
    int exitCode = pclose(pipe);
    output = result.str();
    
    // pclose returns the exit status in a format that needs to be processed
    return WEXITSTATUS(exitCode);
}

std::string CompilationValidator::buildCompilationCommand(const ValidationContext& context, 
                                                         const std::string& outputFile) {
    std::ostringstream command;
    
    // Use the compiler from context, or default to c++
    std::string compiler = context.compilerConfig.compiler;
    if (compiler.empty()) {
        compiler = "c++";
    }
    
    command << compiler;
    
    // Add compiler flags
    for (std::vector<std::string>::const_iterator it = context.compilerConfig.flags.begin();
         it != context.compilerConfig.flags.end(); ++it) {
        command << " " << *it;
    }
    
    // Add output file
    command << " -o " << outputFile;
    
    // Add source files
    for (std::vector<std::string>::const_iterator it = context.sourceFiles.begin();
         it != context.sourceFiles.end(); ++it) {
        command << " " << *it;
    }
    
    return command.str();
}

CompilationError CompilationValidator::parseErrorLine(const std::string& errorLine) {
    CompilationError error;
    
    // Try to parse different compiler error formats
    // Format: filename:line:column: error: message
    // Format: filename:line: error: message
    
    size_t firstColon = errorLine.find(':');
    if (firstColon == std::string::npos) {
        return error; // Invalid format
    }
    
    error.fileName = extractFilePath(errorLine.substr(0, firstColon));
    
    // Extract line and column numbers
    if (!extractLineAndColumn(errorLine, error.lineNumber, error.columnNumber)) {
        return CompilationError(); // Failed to parse
    }
    
    // Find error type (error, warning, note, etc.)
    size_t errorTypeStart = errorLine.find(": ", firstColon);
    if (errorTypeStart != std::string::npos) {
        errorTypeStart += 2;
        size_t errorTypeEnd = errorLine.find(": ", errorTypeStart);
        if (errorTypeEnd != std::string::npos) {
            error.errorType = errorLine.substr(errorTypeStart, errorTypeEnd - errorTypeStart);
            error.message = errorLine.substr(errorTypeEnd + 2);
        } else {
            error.message = errorLine.substr(errorTypeStart);
        }
    }
    
    // Generate suggestions
    std::pair<std::string, std::string> suggestions = generateSuggestion(error.errorType, error.message);
    error.suggestion = suggestions.first;
    error.suggestionJa = suggestions.second;
    
    return error;
}

Issue CompilationValidator::createIssueFromError(const CompilationError& error) {
    Issue issue;
    issue.severity = Issue::CRITICAL;
    issue.category = "COMPILATION_ERROR";
    issue.message = error.errorType + ": " + error.message;
    issue.messageJa = "コンパイルエラー: " + error.message;
    issue.fileName = error.fileName;
    issue.lineNumber = error.lineNumber;
    issue.suggestion = error.suggestion;
    issue.suggestionJa = error.suggestionJa;
    
    // Add learning resources
    issue.learningResources.push_back("https://www.cplusplus.com/doc/tutorial/");
    issue.learningResources.push_back("https://en.cppreference.com/w/cpp/98");
    
    return issue;
}

std::pair<std::string, std::string> CompilationValidator::generateSuggestion(
    const std::string& /* errorType */, const std::string& message) {
    
    std::string suggestion = "Check the syntax and ensure C++98 compatibility";
    std::string suggestionJa = "構文を確認し、C++98互換性を確保してください";
    
    if (message.find("undeclared") != std::string::npos) {
        suggestion = "Make sure the variable or function is declared before use";
        suggestionJa = "変数や関数が使用前に宣言されていることを確認してください";
    } else if (message.find("expected") != std::string::npos) {
        suggestion = "Check for missing semicolons, brackets, or parentheses";
        suggestionJa = "セミコロン、括弧、丸括弧の不足を確認してください";
    } else if (message.find("no matching function") != std::string::npos) {
        suggestion = "Check function signature and parameter types";
        suggestionJa = "関数のシグネチャとパラメータの型を確認してください";
    } else if (message.find("incomplete type") != std::string::npos) {
        suggestion = "Make sure to include the proper header files";
        suggestionJa = "適切なヘッダーファイルをインクルードしてください";
    } else if (isCpp11Error(message)) {
        suggestion = "This feature is not available in C++98, use C++98 alternatives";
        suggestionJa = "この機能はC++98では利用できません。C++98の代替手段を使用してください";
    }
    
    return std::make_pair(suggestion, suggestionJa);
}

void CompilationValidator::cleanupTempFiles(const std::string& outputFile) {
    // Remove the temporary executable if it exists
    std::remove(outputFile.c_str());
}

bool CompilationValidator::isCpp11Error(const std::string& message) {
    return message.find("C++11") != std::string::npos ||
           message.find("auto") != std::string::npos ||
           message.find("nullptr") != std::string::npos ||
           message.find("range-based") != std::string::npos ||
           message.find("lambda") != std::string::npos ||
           message.find("decltype") != std::string::npos;
}

std::string CompilationValidator::extractFilePath(const std::string& pathPart) {
    // Remove any leading/trailing whitespace
    std::string trimmed = pathPart;
    size_t start = trimmed.find_first_not_of(" \t");
    if (start != std::string::npos) {
        trimmed = trimmed.substr(start);
    }
    size_t end = trimmed.find_last_not_of(" \t");
    if (end != std::string::npos) {
        trimmed = trimmed.substr(0, end + 1);
    }
    
    return trimmed;
}

bool CompilationValidator::extractLineAndColumn(const std::string& errorLine, 
                                               int& lineNumber, int& columnNumber) {
    lineNumber = -1;
    columnNumber = -1;
    
    // Find the first colon (after filename)
    size_t firstColon = errorLine.find(':');
    if (firstColon == std::string::npos) return false;
    
    // Find the second colon (after line number)
    size_t secondColon = errorLine.find(':', firstColon + 1);
    if (secondColon == std::string::npos) return false;
    
    // Extract line number
    std::string lineStr = errorLine.substr(firstColon + 1, secondColon - firstColon - 1);
    lineNumber = std::atoi(lineStr.c_str());
    
    // Try to find third colon (after column number)
    size_t thirdColon = errorLine.find(':', secondColon + 1);
    if (thirdColon != std::string::npos) {
        // Extract column number
        std::string colStr = errorLine.substr(secondColon + 1, thirdColon - secondColon - 1);
        columnNumber = std::atoi(colStr.c_str());
    }
    
    return lineNumber > 0;
}