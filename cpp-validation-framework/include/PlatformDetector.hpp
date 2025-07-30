#ifndef PLATFORMDETECTOR_HPP
#define PLATFORMDETECTOR_HPP

#include "ValidationContext.hpp"
#include <string>

/**
 * @brief Utility class for detecting the current platform
 * 
 * This class provides methods to automatically detect the operating
 * system and environment, which is crucial for selecting the appropriate
 * memory analysis tools.
 */
class PlatformDetector {
public:
    /**
     * @brief Detect the current platform automatically
     * @return Detected platform type
     */
    static Platform detectPlatform();
    
    /**
     * @brief Check if running on macOS
     * @return True if current platform is macOS
     */
    static bool isMacOS();
    
    /**
     * @brief Check if running on Ubuntu
     * @return True if current platform is Ubuntu
     */
    static bool isUbuntu();
    
    /**
     * @brief Check if running on generic Linux
     * @return True if current platform is Linux (non-Ubuntu)
     */
    static bool isLinux();
    
    /**
     * @brief Get detailed platform information
     * @return String with detailed platform information
     */
    static std::string getPlatformDetails();
    
    /**
     * @brief Get the platform name as string
     * @param platform Platform enum value
     * @return Human-readable platform name
     */
    static std::string getPlatformName(Platform platform);
    
    /**
     * @brief Check if a command is available in the system PATH
     * @param command Command name to check
     * @return True if command is available
     */
    static bool isCommandAvailable(const std::string& command);
    
    /**
     * @brief Get the number of CPU cores available
     * @return Number of CPU cores, or 1 if detection fails
     */
    static int getCpuCoreCount();

private:
    /**
     * @brief Execute a system command and get its output
     * @param command Command to execute
     * @return Command output as string
     */
    static std::string executeCommand(const std::string& command);
    
    /**
     * @brief Check if a file exists
     * @param filePath Path to check
     * @return True if file exists
     */
    static bool fileExists(const std::string& filePath);
};

#endif // PLATFORMDETECTOR_HPP