#include "ValgrindTool.hpp"
#include "PlatformDetector.hpp"
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <sys/wait.h>

ValgrindTool::ValgrindTool() {
}

ValgrindTool::~ValgrindTool() {
}

std::string ValgrindTool::getName() const {
    return "Valgrind";
}

bool ValgrindTool::isAvailable() const {
    // Valgrind is primarily available on Linux systems
    if (!PlatformDetector::isLinux()) {
        return false;
    }
    
    return isValgrindInstalled();
}

MemoryAnalysisResult ValgrindTool::analyze(const std::string& executablePath, 
                                         const std::vector<std::string>& arguments) {
    MemoryAnalysisResult result;
    
    if (!isAvailable()) {
        result.hasMemoryErrors = true;
        result.errors.push_back("Valgrind is not available on this system");
        result.exitCode = -1;
        return result;
    }
    
    // Build Valgrind command
    std::string command = buildValgrindCommand(executablePath, arguments);
    
    // Execute the command
    int exitCode;
    std::string output = executeCommand(command, exitCode);
    
    // Parse the output
    result = parseValgrindOutput(output, exitCode);
    result.toolOutput = output;
    
    return result;
}

std::vector<std::string> ValgrindTool::getRequiredCompilerFlags() const {
    std::vector<std::string> flags;
    flags.push_back("-g");  // Debug information for better stack traces
    return flags;
}

int ValgrindTool::getPriority() const {
    // Higher priority on Ubuntu, medium on generic Linux
    if (PlatformDetector::isUbuntu()) {
        return 8;
    } else if (PlatformDetector::isLinux()) {
        return 6;
    }
    return 0;
}

MemoryAnalysisResult ValgrindTool::parseValgrindOutput(const std::string& output, int exitCode) {
    MemoryAnalysisResult result;
    result.exitCode = exitCode;
    
    // Check for memory leaks
    if (output.find("definitely lost:") != std::string::npos || 
        output.find("possibly lost:") != std::string::npos ||
        output.find("still reachable:") != std::string::npos) {
        
        // Parse leak summary to determine if there are actual leaks
        if (output.find("definitely lost: 0 bytes") == std::string::npos ||
            output.find("possibly lost: 0 bytes") == std::string::npos) {
            result.hasMemoryLeaks = true;
            result.leaks = extractLeaks(output);
        }
    }
    
    // Check for memory errors
    if (output.find("Invalid read") != std::string::npos ||
        output.find("Invalid write") != std::string::npos ||
        output.find("Invalid free") != std::string::npos ||
        output.find("Mismatched free") != std::string::npos ||
        output.find("Use of uninitialised value") != std::string::npos) {
        result.hasMemoryErrors = true;
        result.errors = extractErrors(output);
    }
    
    return result;
}

std::vector<MemoryLeak> ValgrindTool::extractLeaks(const std::string& output) {
    std::vector<MemoryLeak> leaks;
    
    // Parse output line by line to find leak information
    std::istringstream stream(output);
    std::string line;
    
    while (std::getline(stream, line)) {
        // Look for leak patterns like "definitely lost: 24 bytes in 1 blocks"
        size_t lostPos = line.find("definitely lost:");
        if (lostPos == std::string::npos) {
            lostPos = line.find("possibly lost:");
        }
        
        if (lostPos != std::string::npos) {
            // Extract size
            size_t bytesPos = line.find(" bytes", lostPos);
            if (bytesPos != std::string::npos) {
                // Find the number before " bytes"
                size_t numStart = lostPos;
                while (numStart < bytesPos && !std::isdigit(line[numStart])) {
                    numStart++;
                }
                
                if (numStart < bytesPos) {
                    size_t numEnd = numStart;
                    while (numEnd < bytesPos && std::isdigit(line[numEnd])) {
                        numEnd++;
                    }
                    
                    std::string sizeStr = line.substr(numStart, numEnd - numStart);
                    size_t size = static_cast<size_t>(std::atol(sizeStr.c_str()));
                    
                    if (size > 0) {
                        // Look for location information in subsequent lines
                        std::string fileName = "unknown";
                        int lineNumber = 0;
                        
                        // Read a few more lines to find location
                        for (int i = 0; i < 10 && std::getline(stream, line); ++i) {
                            size_t atPos = line.find(" at ");
                            size_t colonPos = line.find_last_of(':');
                            
                            if (atPos != std::string::npos && colonPos != std::string::npos && colonPos > atPos) {
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
                        
                        MemoryLeak leak(fileName, lineNumber, size, "Memory leak detected by Valgrind");
                        leaks.push_back(leak);
                    }
                }
            }
        }
    }
    
    return leaks;
}

std::vector<std::string> ValgrindTool::extractErrors(const std::string& output) {
    std::vector<std::string> errors;
    
    // Split output into lines and look for error patterns
    std::istringstream stream(output);
    std::string line;
    
    while (std::getline(stream, line)) {
        if (line.find("Invalid read") != std::string::npos ||
            line.find("Invalid write") != std::string::npos ||
            line.find("Invalid free") != std::string::npos ||
            line.find("Mismatched free") != std::string::npos ||
            line.find("Use of uninitialised value") != std::string::npos) {
            errors.push_back(line);
        }
    }
    
    return errors;
}

std::string ValgrindTool::executeCommand(const std::string& command, int& exitCode) {
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

bool ValgrindTool::isValgrindInstalled() const {
    return PlatformDetector::isCommandAvailable("valgrind");
}

std::string ValgrindTool::buildValgrindCommand(const std::string& executablePath, 
                                             const std::vector<std::string>& arguments) {
    std::ostringstream command;
    
    // Basic Valgrind command with memory leak detection
    command << "valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all "
            << "--track-origins=yes --verbose --error-exitcode=1 ";
    
    // Add the executable
    command << executablePath;
    
    // Add arguments
    for (std::vector<std::string>::const_iterator it = arguments.begin(); it != arguments.end(); ++it) {
        command << " \"" << *it << "\"";
    }
    
    // Redirect stderr to stdout to capture Valgrind output
    command << " 2>&1";
    
    return command.str();
}