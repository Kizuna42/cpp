#include "AddressSanitizerTool.hpp"
#include "PlatformDetector.hpp"
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <sys/wait.h>

AddressSanitizerTool::AddressSanitizerTool() {
}

AddressSanitizerTool::~AddressSanitizerTool() {
}

std::string AddressSanitizerTool::getName() const {
    return "AddressSanitizer";
}

bool AddressSanitizerTool::isAvailable() const {
    // AddressSanitizer is available if:
    // 1. We have a compiler that supports it
    // 2. The platform supports it (primarily macOS and Linux)
    
    if (!PlatformDetector::isMacOS() && !PlatformDetector::isLinux()) {
        return false;
    }
    
    return isAsanSupported();
}

MemoryAnalysisResult AddressSanitizerTool::analyze(const std::string& executablePath, 
                                                 const std::vector<std::string>& arguments) {
    MemoryAnalysisResult result;
    
    if (!isAvailable()) {
        result.hasMemoryErrors = true;
        result.errors.push_back("AddressSanitizer is not available on this system");
        result.exitCode = -1;
        return result;
    }
    
    // Build command to run the executable
    std::ostringstream command;
    
    // Set environment variables for better error reporting
    // Note: detect_leaks may not be supported on all platforms (e.g., macOS)
    if (PlatformDetector::isLinux()) {
        command << "ASAN_OPTIONS=detect_leaks=1:abort_on_error=1 ";
    } else {
        command << "ASAN_OPTIONS=abort_on_error=1 ";
    }
    command << executablePath;
    
    // Add arguments
    for (std::vector<std::string>::const_iterator it = arguments.begin(); it != arguments.end(); ++it) {
        command << " \"" << *it << "\"";
    }
    
    // Redirect stderr to stdout to capture ASan output
    command << " 2>&1";
    
    // Execute the command
    int exitCode;
    std::string output = executeCommand(command.str(), exitCode);
    
    // Parse the output
    result = parseAsanOutput(output, exitCode);
    result.toolOutput = output;
    
    return result;
}

std::vector<std::string> AddressSanitizerTool::getRequiredCompilerFlags() const {
    std::vector<std::string> flags;
    flags.push_back("-fsanitize=address");
    flags.push_back("-g");  // Debug information for better stack traces
    flags.push_back("-O1"); // Optimize for better performance while keeping debugging info
    return flags;
}

int AddressSanitizerTool::getPriority() const {
    // Higher priority on macOS, medium on Linux
    if (PlatformDetector::isMacOS()) {
        return 10;
    } else if (PlatformDetector::isLinux()) {
        return 7;
    }
    return 0;
}

MemoryAnalysisResult AddressSanitizerTool::parseAsanOutput(const std::string& output, int exitCode) {
    MemoryAnalysisResult result;
    result.exitCode = exitCode;
    
    // Check for memory leaks
    if (output.find("LeakSanitizer") != std::string::npos || 
        output.find("detected memory leaks") != std::string::npos ||
        output.find("Direct leak of") != std::string::npos ||
        output.find("Indirect leak of") != std::string::npos) {
        result.hasMemoryLeaks = true;
        result.leaks = extractLeaks(output);
    }
    
    // Check for memory errors
    if (output.find("AddressSanitizer") != std::string::npos ||
        output.find("heap-buffer-overflow") != std::string::npos ||
        output.find("heap-use-after-free") != std::string::npos ||
        output.find("stack-buffer-overflow") != std::string::npos ||
        output.find("use-after-free") != std::string::npos) {
        result.hasMemoryErrors = true;
        result.errors = extractErrors(output);
    }
    
    return result;
}

std::vector<MemoryLeak> AddressSanitizerTool::extractLeaks(const std::string& output) {
    std::vector<MemoryLeak> leaks;
    
    // Parse output line by line to find leak information
    // Example: "Direct leak of 24 byte(s) in 1 object(s) allocated from:"
    std::istringstream stream(output);
    std::string line;
    
    while (std::getline(stream, line)) {
        // Look for leak pattern
        size_t leakPos = line.find("Direct leak of ");
        if (leakPos != std::string::npos) {
            // Extract size
            size_t sizeStart = leakPos + 15; // length of "Direct leak of "
            size_t sizeEnd = line.find(" byte(s)", sizeStart);
            
            if (sizeEnd != std::string::npos) {
                std::string sizeStr = line.substr(sizeStart, sizeEnd - sizeStart);
                size_t size = static_cast<size_t>(std::atol(sizeStr.c_str()));
                
                // Look for location information in subsequent lines
                std::string fileName = "unknown";
                int lineNumber = 0;
                
                // Read a few more lines to find location
                for (int i = 0; i < 10 && std::getline(stream, line); ++i) {
                    size_t hashPos = line.find("#");
                    size_t colonPos = line.find_last_of(':');
                    
                    if (hashPos != std::string::npos && colonPos != std::string::npos && colonPos > hashPos) {
                        // Try to extract filename and line number
                        size_t spaceBeforeFile = line.find_last_of(' ', colonPos);
                        if (spaceBeforeFile != std::string::npos && spaceBeforeFile < colonPos) {
                            fileName = line.substr(spaceBeforeFile + 1, colonPos - spaceBeforeFile - 1);
                            std::string lineStr = line.substr(colonPos + 1);
                            lineNumber = std::atoi(lineStr.c_str());
                            break;
                        }
                    }
                }
                
                MemoryLeak leak(fileName, lineNumber, size, "Memory leak detected by AddressSanitizer");
                leaks.push_back(leak);
            }
        }
    }
    
    return leaks;
}

std::vector<std::string> AddressSanitizerTool::extractErrors(const std::string& output) {
    std::vector<std::string> errors;
    
    // Split output into lines and look for error patterns
    std::istringstream stream(output);
    std::string line;
    
    while (std::getline(stream, line)) {
        if (line.find("ERROR: AddressSanitizer") != std::string::npos ||
            line.find("heap-buffer-overflow") != std::string::npos ||
            line.find("heap-use-after-free") != std::string::npos ||
            line.find("stack-buffer-overflow") != std::string::npos ||
            line.find("use-after-free") != std::string::npos) {
            errors.push_back(line);
        }
    }
    
    return errors;
}

std::string AddressSanitizerTool::executeCommand(const std::string& command, int& exitCode) {
    std::string result;
    FILE* pipe = popen(command.c_str(), "r");
    
    if (pipe) {
        char buffer[128];
        while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
            result += buffer;
        }
        exitCode = pclose(pipe);
        // pclose returns the exit status in the format returned by waitpid()
        // We need to extract the actual exit code
        if (WIFEXITED(exitCode)) {
            exitCode = WEXITSTATUS(exitCode);
        }
    } else {
        exitCode = -1;
    }
    
    return result;
}

bool AddressSanitizerTool::isAsanSupported() const {
    // Test if the compiler supports AddressSanitizer by trying to compile a simple program
    std::string testCommand = "echo 'int main(){return 0;}' | c++ -fsanitize=address -x c++ - -o /tmp/asan_test 2>/dev/null && rm -f /tmp/asan_test";
    int result = std::system(testCommand.c_str());
    return result == 0;
}