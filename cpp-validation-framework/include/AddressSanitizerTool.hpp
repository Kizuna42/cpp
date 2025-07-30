#ifndef ADDRESSSANITIZERTOOL_HPP
#define ADDRESSSANITIZERTOOL_HPP

#include "IMemoryTool.hpp"

/**
 * @brief AddressSanitizer memory analysis tool implementation
 * 
 * This class implements memory analysis using AddressSanitizer (ASan),
 * which is particularly well-suited for macOS environments and provides
 * excellent memory error detection capabilities.
 */
class AddressSanitizerTool : public IMemoryTool {
public:
    AddressSanitizerTool();
    virtual ~AddressSanitizerTool();
    
    // IMemoryTool interface implementation
    std::string getName() const;
    bool isAvailable() const;
    MemoryAnalysisResult analyze(const std::string& executablePath, 
                               const std::vector<std::string>& arguments = std::vector<std::string>());
    std::vector<std::string> getRequiredCompilerFlags() const;
    int getPriority() const;

private:
    /**
     * @brief Parse AddressSanitizer output for memory leaks
     * @param output Raw output from AddressSanitizer
     * @return Parsed memory analysis result
     */
    MemoryAnalysisResult parseAsanOutput(const std::string& output, int exitCode);
    
    /**
     * @brief Extract memory leak information from ASan output
     * @param output ASan output text
     * @return Vector of detected memory leaks
     */
    std::vector<MemoryLeak> extractLeaks(const std::string& output);
    
    /**
     * @brief Extract memory errors from ASan output
     * @param output ASan output text
     * @return Vector of memory error descriptions
     */
    std::vector<std::string> extractErrors(const std::string& output);
    
    /**
     * @brief Execute a command and capture its output
     * @param command Command to execute
     * @param exitCode Reference to store the exit code
     * @return Command output
     */
    std::string executeCommand(const std::string& command, int& exitCode);
    
    /**
     * @brief Check if the compiler supports AddressSanitizer
     * @return True if ASan is supported
     */
    bool isAsanSupported() const;
};

#endif // ADDRESSSANITIZERTOOL_HPP