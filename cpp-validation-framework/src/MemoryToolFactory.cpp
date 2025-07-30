#include "MemoryToolFactory.hpp"
#include "AddressSanitizerTool.hpp"
#include "ValgrindTool.hpp"
#include "PlatformDetector.hpp"
#include <algorithm>

IMemoryTool* MemoryToolFactory::createBestAvailableTool() {
    Platform currentPlatform = PlatformDetector::detectPlatform();
    return createBestAvailableTool(currentPlatform);
}

IMemoryTool* MemoryToolFactory::createBestAvailableTool(Platform platform) {
    std::vector<IMemoryTool*> tools = getAllAvailableTools(platform);
    
    if (!tools.empty()) {
        // Return the highest priority tool (first in sorted vector)
        IMemoryTool* bestTool = tools[0];
        
        // Clean up the rest
        for (size_t i = 1; i < tools.size(); ++i) {
            delete tools[i];
        }
        
        return bestTool;
    }
    
    return NULL;
}

std::vector<IMemoryTool*> MemoryToolFactory::getAllAvailableTools() {
    Platform currentPlatform = PlatformDetector::detectPlatform();
    return getAllAvailableTools(currentPlatform);
}

std::vector<IMemoryTool*> MemoryToolFactory::getAllAvailableTools(Platform platform) {
    std::vector<IMemoryTool*> availableTools;
    
    // Try AddressSanitizer
    IMemoryTool* asanTool = createAddressSanitizerTool();
    if (asanTool && asanTool->isAvailable()) {
        availableTools.push_back(asanTool);
    } else if (asanTool) {
        delete asanTool;
    }
    
    // Try Valgrind (placeholder for future implementation)
    // Note: Valgrind is primarily for Linux platforms
    if (platform == UBUNTU || platform == LINUX_GENERIC) {
        IMemoryTool* valgrindTool = createValgrindTool();
        if (valgrindTool && valgrindTool->isAvailable()) {
            availableTools.push_back(valgrindTool);
        } else if (valgrindTool) {
            delete valgrindTool;
        }
    }
    
    // Sort by priority (highest first)
    sortToolsByPriority(availableTools);
    
    return availableTools;
}

bool MemoryToolFactory::hasAvailableTools() {
    Platform currentPlatform = PlatformDetector::detectPlatform();
    return hasAvailableTools(currentPlatform);
}

bool MemoryToolFactory::hasAvailableTools(Platform platform) {
    std::vector<IMemoryTool*> tools = getAllAvailableTools(platform);
    bool hasTools = !tools.empty();
    
    // Clean up
    for (size_t i = 0; i < tools.size(); ++i) {
        delete tools[i];
    }
    
    return hasTools;
}

std::vector<std::string> MemoryToolFactory::getAvailableToolNames() {
    Platform currentPlatform = PlatformDetector::detectPlatform();
    return getAvailableToolNames(currentPlatform);
}

std::vector<std::string> MemoryToolFactory::getAvailableToolNames(Platform platform) {
    std::vector<std::string> names;
    std::vector<IMemoryTool*> tools = getAllAvailableTools(platform);
    
    for (size_t i = 0; i < tools.size(); ++i) {
        names.push_back(tools[i]->getName());
        delete tools[i];
    }
    
    return names;
}

IMemoryTool* MemoryToolFactory::createAddressSanitizerTool() {
    return new AddressSanitizerTool();
}

IMemoryTool* MemoryToolFactory::createValgrindTool() {
    return new ValgrindTool();
}

void MemoryToolFactory::sortToolsByPriority(std::vector<IMemoryTool*>& tools) {
    std::sort(tools.begin(), tools.end(), comparePriority);
}

bool MemoryToolFactory::comparePriority(IMemoryTool* a, IMemoryTool* b) {
    return a->getPriority() > b->getPriority();
}