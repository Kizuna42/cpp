#ifndef MEMORYTOOLFACTORY_HPP
#define MEMORYTOOLFACTORY_HPP

#include "IMemoryTool.hpp"
#include "ValidationContext.hpp"
#include <vector>

/**
 * @brief Factory class for creating appropriate memory analysis tools
 * 
 * This factory automatically selects the best available memory analysis
 * tool based on the current platform and tool availability.
 */
class MemoryToolFactory {
public:
    /**
     * @brief Create the best available memory tool for the current platform
     * @return Pointer to the selected memory tool, or NULL if none available
     * @note Caller is responsible for deleting the returned pointer
     */
    static IMemoryTool* createBestAvailableTool();
    
    /**
     * @brief Create the best available memory tool for a specific platform
     * @param platform Target platform
     * @return Pointer to the selected memory tool, or NULL if none available
     * @note Caller is responsible for deleting the returned pointer
     */
    static IMemoryTool* createBestAvailableTool(Platform platform);
    
    /**
     * @brief Get all available memory tools for the current platform
     * @return Vector of available memory tools, sorted by priority (highest first)
     * @note Caller is responsible for deleting all pointers in the vector
     */
    static std::vector<IMemoryTool*> getAllAvailableTools();
    
    /**
     * @brief Get all available memory tools for a specific platform
     * @param platform Target platform
     * @return Vector of available memory tools, sorted by priority (highest first)
     * @note Caller is responsible for deleting all pointers in the vector
     */
    static std::vector<IMemoryTool*> getAllAvailableTools(Platform platform);
    
    /**
     * @brief Check if any memory analysis tools are available
     * @return True if at least one memory tool is available
     */
    static bool hasAvailableTools();
    
    /**
     * @brief Check if any memory analysis tools are available for a platform
     * @param platform Target platform
     * @return True if at least one memory tool is available for the platform
     */
    static bool hasAvailableTools(Platform platform);
    
    /**
     * @brief Get names of all available memory tools
     * @return Vector of tool names
     */
    static std::vector<std::string> getAvailableToolNames();
    
    /**
     * @brief Get names of all available memory tools for a platform
     * @param platform Target platform
     * @return Vector of tool names
     */
    static std::vector<std::string> getAvailableToolNames(Platform platform);

private:
    /**
     * @brief Create an AddressSanitizer tool instance
     * @return Pointer to AddressSanitizer tool
     */
    static IMemoryTool* createAddressSanitizerTool();
    
    /**
     * @brief Create a Valgrind tool instance (placeholder for future implementation)
     * @return Pointer to Valgrind tool
     */
    static IMemoryTool* createValgrindTool();
    
    /**
     * @brief Sort tools by priority (highest first)
     * @param tools Vector of tools to sort
     */
    static void sortToolsByPriority(std::vector<IMemoryTool*>& tools);
    
    /**
     * @brief Comparison function for sorting tools by priority
     * @param a First tool
     * @param b Second tool
     * @return True if a has higher priority than b
     */
    static bool comparePriority(IMemoryTool* a, IMemoryTool* b);
};

#endif // MEMORYTOOLFACTORY_HPP