#ifndef VALIDATIONCONTEXT_HPP
#define VALIDATIONCONTEXT_HPP

#include <string>
#include <vector>
#include <map>

/**
 * @brief Enumeration of supported module types
 */
enum ModuleType {
    CPP00 = 0,
    CPP01 = 1,
    CPP02 = 2,
    CPP03 = 3,
    CPP04 = 4,
    UNKNOWN = -1
};

/**
 * @brief Enumeration of target platforms
 */
enum Platform {
    MACOS,
    UBUNTU,
    LINUX_GENERIC,
    PLATFORM_UNKNOWN
};

/**
 * @brief Compiler configuration settings
 */
struct CompilerConfig {
    std::string compiler;
    std::vector<std::string> flags;
    std::string standard;
    
    CompilerConfig() : compiler("c++"), standard("c++98") {
        flags.push_back("-Wall");
        flags.push_back("-Wextra");
        flags.push_back("-Werror");
        flags.push_back("-std=c++98");
    }
};

/**
 * @brief Contains all context information needed for validation
 * 
 * This structure holds all the information that validators need to
 * perform their checks, including file paths, module information,
 * and platform-specific settings.
 */
struct ValidationContext {
    std::string submissionPath;
    ModuleType moduleType;
    Platform targetPlatform;
    std::vector<std::string> sourceFiles;
    std::vector<std::string> headerFiles;
    CompilerConfig compilerConfig;
    std::map<std::string, std::string> metadata;
    
    ValidationContext() : moduleType(UNKNOWN), targetPlatform(PLATFORM_UNKNOWN) {}
    
    /**
     * @brief Constructor with basic parameters
     * @param path Path to the submission directory
     * @param module The module type being validated
     */
    ValidationContext(const std::string& path, ModuleType module)
        : submissionPath(path), moduleType(module), targetPlatform(PLATFORM_UNKNOWN) {}
    
    /**
     * @brief Add a source file to the context
     * @param filePath Path to the source file
     */
    void addSourceFile(const std::string& filePath) {
        sourceFiles.push_back(filePath);
    }
    
    /**
     * @brief Add a header file to the context
     * @param filePath Path to the header file
     */
    void addHeaderFile(const std::string& filePath) {
        headerFiles.push_back(filePath);
    }
    
    /**
     * @brief Add metadata to the context
     * @param key The metadata key
     * @param value The metadata value
     */
    void addMetadata(const std::string& key, const std::string& value) {
        metadata[key] = value;
    }
    
    /**
     * @brief Get module type as string
     * @return String representation of module type
     */
    std::string getModuleTypeString() const {
        switch (moduleType) {
            case CPP00: return "cpp00";
            case CPP01: return "cpp01";
            case CPP02: return "cpp02";
            case CPP03: return "cpp03";
            case CPP04: return "cpp04";
            default: return "unknown";
        }
    }
    
    /**
     * @brief Get platform as string
     * @return String representation of platform
     */
    std::string getPlatformString() const {
        switch (targetPlatform) {
            case MACOS: return "macOS";
            case UBUNTU: return "Ubuntu";
            case LINUX_GENERIC: return "Linux";
            default: return "Unknown";
        }
    }
};

#endif // VALIDATIONCONTEXT_HPP