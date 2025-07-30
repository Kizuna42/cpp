#include "PlatformDetector.hpp"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>

#ifdef __APPLE__
#include <sys/utsname.h>
#include <unistd.h>
#elif __linux__
#include <sys/utsname.h>
#include <unistd.h>
#endif

Platform PlatformDetector::detectPlatform() {
#ifdef __APPLE__
    return MACOS;
#elif __linux__
    // Check if it's Ubuntu by looking for Ubuntu-specific files
    if (fileExists("/etc/lsb-release")) {
        std::string lsbContent = executeCommand("cat /etc/lsb-release 2>/dev/null");
        if (lsbContent.find("Ubuntu") != std::string::npos) {
            return UBUNTU;
        }
    }
    
    // Check /etc/os-release for Ubuntu
    if (fileExists("/etc/os-release")) {
        std::string osContent = executeCommand("cat /etc/os-release 2>/dev/null");
        if (osContent.find("Ubuntu") != std::string::npos) {
            return UBUNTU;
        }
    }
    
    // Generic Linux
    return LINUX_GENERIC;
#else
    return PLATFORM_UNKNOWN;
#endif
}

bool PlatformDetector::isMacOS() {
#ifdef __APPLE__
    return true;
#else
    return false;
#endif
}

bool PlatformDetector::isUbuntu() {
    return detectPlatform() == UBUNTU;
}

bool PlatformDetector::isLinux() {
#ifdef __linux__
    return true;
#else
    return false;
#endif
}

std::string PlatformDetector::getPlatformDetails() {
    std::ostringstream details;
    
#if defined(__APPLE__) || defined(__linux__)
    struct utsname unameData;
    if (uname(&unameData) == 0) {
        details << "System: " << unameData.sysname << " "
                << unameData.release << " "
                << unameData.machine;
    }
#endif
    
    Platform platform = detectPlatform();
    details << " (Detected: " << getPlatformName(platform) << ")";
    
    return details.str();
}

std::string PlatformDetector::getPlatformName(Platform platform) {
    switch (platform) {
        case MACOS:
            return "macOS";
        case UBUNTU:
            return "Ubuntu";
        case LINUX_GENERIC:
            return "Linux";
        case PLATFORM_UNKNOWN:
        default:
            return "Unknown";
    }
}

bool PlatformDetector::isCommandAvailable(const std::string& command) {
    std::string checkCommand = "which " + command + " >/dev/null 2>&1";
    int result = std::system(checkCommand.c_str());
    return result == 0;
}

int PlatformDetector::getCpuCoreCount() {
#if defined(__APPLE__) || defined(__linux__)
    long cores = sysconf(_SC_NPROCESSORS_ONLN);
    return (cores > 0) ? static_cast<int>(cores) : 1;
#else
    return 1;
#endif
}

std::string PlatformDetector::executeCommand(const std::string& command) {
    std::string result;
    FILE* pipe = popen(command.c_str(), "r");
    
    if (pipe) {
        char buffer[128];
        while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
            result += buffer;
        }
        pclose(pipe);
    }
    
    return result;
}

bool PlatformDetector::fileExists(const std::string& filePath) {
    std::ifstream file(filePath.c_str());
    return file.good();
}