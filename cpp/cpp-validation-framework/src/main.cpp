#include "ValidationEngine.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <submission_path> [module_type]" << std::endl;
        std::cout << "Module types: cpp00, cpp01, cpp02, cpp03, cpp04" << std::endl;
        return 1;
    }
    
    std::string submissionPath = argv[1];
    ModuleType moduleType = CPP00; // default
    
    if (argc >= 3) {
        std::string moduleStr = argv[2];
        if (moduleStr == "cpp00") moduleType = CPP00;
        else if (moduleStr == "cpp01") moduleType = CPP01;
        else if (moduleStr == "cpp02") moduleType = CPP02;
        else if (moduleStr == "cpp03") moduleType = CPP03;
        else if (moduleStr == "cpp04") moduleType = CPP04;
        else {
            std::cout << "Unknown module type: " << moduleStr << std::endl;
            return 1;
        }
    }
    
    ValidationEngine engine;
    
    std::cout << "C++ Validation Framework" << std::endl;
    std::cout << "========================" << std::endl;
    std::cout << "Submission Path: " << submissionPath << std::endl;
    std::cout << "Module Type: " << (moduleType == CPP00 ? "cpp00" :
                                    moduleType == CPP01 ? "cpp01" :
                                    moduleType == CPP02 ? "cpp02" :
                                    moduleType == CPP03 ? "cpp03" :
                                    moduleType == CPP04 ? "cpp04" : "unknown") << std::endl;
    std::cout << std::endl;
    
    ValidationResult result = engine.validate(submissionPath, moduleType);
    
    std::cout << "Validation Result: " << (result.isValid ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Issues found: " << result.issues.size() << std::endl;
    
    if (!result.issues.empty()) {
        std::cout << std::endl << "Issues:" << std::endl;
        for (std::vector<Issue>::const_iterator it = result.issues.begin();
             it != result.issues.end(); ++it) {
            std::cout << "- [" << (it->severity == Issue::CRITICAL ? "CRITICAL" :
                                   it->severity == Issue::MAJOR ? "MAJOR" : "MINOR")
                      << "] " << it->category << ": " << it->message << std::endl;
        }
    }
    
    return result.isValid ? 0 : 1;
}