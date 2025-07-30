#ifndef VALGRINDTOOL_HPP
#define VALGRINDTOOL_HPP

#include "IMemoryTool.hpp"

/**
 * @brief Valgrind memory analysis tool implementation
 * 
 * This class implements memory analysis using Valgrind,
 * which is particularly well-suited for Linux environments and provides
 * comprehensive memory error and leak detection capabilities.
 */
class ValgrindTool : public IMemoryTool {
public:
    ValgrindTool();
    virtual ~ValgrindTool();
    
    // IMemoryTool interface implementation
    std::string getName() const;
    bool isAvailable() const;
    MemoryAnalysisResult analyze(const std::string& executablePath, 
                               const std::vector<std::string>& arguments = std::vector<std::string>());
    std::vector<std::string> getRequiredCompilerFlags() const;
    int getPriority() const;

private:
    /**
     * @brief Parse Valgrind output for memory leaks and errors
     * @param output Raw output from Valgrind
     * @param exitCode Exit code from Valgrind execution
     * @return Parsed memory analysis result
     */
    MemoryAnalysisResult parseValgrindOutput(const std::string& output, int exitCode);
    
    /**
     * @brief Extract memory leak information from Valgrind output
     * @param output Valgrind output text
     * @return Vector of detected memory leaks
     */
    std::vector<MemoryLeak> extractLeaks(const std::string& output);
    
    /**
     * @brief Extract memory errors from Valgrind output
     * @param output Valgrind output text
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
     * @brief Check if Valgrind is installed and available
     * @return True if Valgrind is available
     */
    bool isValgrindInstalled() const;
    
    /**
     * @brief Build Valgrind command with appropriate options
     * @param executablePath Path to executable
     * @param arguments Program arguments
     * @return Complete Valgrind command string
     */
    std::string buildValgrindCommand(const std::string& executablePath, 
                                   const std::vector<std::string>& arguments);
};

#endif // VALGRINDTOOL_HPP