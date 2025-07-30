#ifndef IMEMORYTOOL_HPP
#define IMEMORYTOOL_HPP

#include <string>
#include <vector>

/**
 * @brief Structure to hold memory leak information
 */
struct MemoryLeak {
    std::string fileName;
    int lineNumber;
    size_t size;
    std::string description;
    
    MemoryLeak() : lineNumber(0), size(0) {}
    MemoryLeak(const std::string& file, int line, size_t sz, const std::string& desc)
        : fileName(file), lineNumber(line), size(sz), description(desc) {}
};

/**
 * @brief Structure to hold memory analysis results
 */
struct MemoryAnalysisResult {
    bool hasMemoryLeaks;
    bool hasMemoryErrors;
    std::vector<MemoryLeak> leaks;
    std::vector<std::string> errors;
    std::string toolOutput;
    int exitCode;
    
    MemoryAnalysisResult() : hasMemoryLeaks(false), hasMemoryErrors(false), exitCode(0) {}
    
    /**
     * @brief Check if memory analysis passed (no leaks or errors)
     * @return True if no memory issues detected
     */
    bool isPassed() const {
        return !hasMemoryLeaks && !hasMemoryErrors;
    }
    
    /**
     * @brief Get total number of memory issues
     * @return Total count of leaks and errors
     */
    size_t getTotalIssueCount() const {
        return leaks.size() + errors.size();
    }
    
    /**
     * @brief Get total leaked memory size
     * @return Total size of leaked memory in bytes
     */
    size_t getTotalLeakedSize() const {
        size_t total = 0;
        for (std::vector<MemoryLeak>::const_iterator it = leaks.begin(); it != leaks.end(); ++it) {
            total += it->size;
        }
        return total;
    }
};

/**
 * @brief Interface for memory analysis tools
 * 
 * This interface abstracts different memory analysis tools like
 * AddressSanitizer and Valgrind, allowing the system to use
 * the appropriate tool based on platform availability.
 */
class IMemoryTool {
public:
    virtual ~IMemoryTool() {}
    
    /**
     * @brief Get the name of this memory tool
     * @return String identifier for this tool
     */
    virtual std::string getName() const = 0;
    
    /**
     * @brief Check if this tool is available on the current system
     * @return True if the tool can be used
     */
    virtual bool isAvailable() const = 0;
    
    /**
     * @brief Analyze memory usage of an executable
     * @param executablePath Path to the compiled executable
     * @param arguments Command line arguments to pass to the executable
     * @return Memory analysis results
     */
    virtual MemoryAnalysisResult analyze(const std::string& executablePath, 
                                       const std::vector<std::string>& arguments = std::vector<std::string>()) = 0;
    
    /**
     * @brief Get compilation flags needed for this tool
     * @return Vector of compiler flags required
     */
    virtual std::vector<std::string> getRequiredCompilerFlags() const = 0;
    
    /**
     * @brief Get the priority of this tool (higher is preferred)
     * @return Priority value for tool selection
     */
    virtual int getPriority() const = 0;
};

#endif // IMEMORYTOOL_HPP