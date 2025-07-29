#include "ModuleRules.hpp"
#include "ValidationException.hpp"
#include <iostream>
#include <cassert>
#include <string>

void testModuleRulesBasicFunctionality() {
    std::cout << "Testing ModuleRules basic functionality..." << std::endl;
    
    // Test default constructor
    ModuleRules defaultRules;
    assert(defaultRules.requiredConcepts.empty());
    assert(defaultRules.forbiddenFeatures.empty());
    assert(defaultRules.requiredPatterns.empty());
    assert(defaultRules.specificChecks.empty());
    assert(defaultRules.learningObjectives.empty());
    
    // Test parameterized constructor
    std::vector<std::string> concepts;
    concepts.push_back("namespaces");
    concepts.push_back("classes");
    
    std::vector<std::string> forbidden;
    forbidden.push_back("using_namespace_std");
    forbidden.push_back("friend_functions");
    
    std::vector<std::string> patterns;
    patterns.push_back("class_definition");
    
    ModuleRules rules(concepts, forbidden, patterns);
    assert(rules.requiredConcepts.size() == 2);
    assert(rules.forbiddenFeatures.size() == 2);
    assert(rules.requiredPatterns.size() == 1);
    assert(rules.requiredConcepts[0] == "namespaces");
    assert(rules.forbiddenFeatures[0] == "using_namespace_std");
    assert(rules.requiredPatterns[0] == "class_definition");
    
    std::cout << "ModuleRules basic functionality tests passed!" << std::endl;
}

void testModuleRulesAddMethods() {
    std::cout << "Testing ModuleRules add methods..." << std::endl;
    
    ModuleRules rules;
    
    // Test adding required concepts
    rules.addRequiredConcept("inheritance");
    rules.addRequiredConcept("polymorphism");
    assert(rules.requiredConcepts.size() == 2);
    assert(rules.requiredConcepts[0] == "inheritance");
    assert(rules.requiredConcepts[1] == "polymorphism");
    
    // Test adding forbidden features
    rules.addForbiddenFeature("stl_containers");
    rules.addForbiddenFeature("cpp11_features");
    assert(rules.forbiddenFeatures.size() == 2);
    assert(rules.forbiddenFeatures[0] == "stl_containers");
    assert(rules.forbiddenFeatures[1] == "cpp11_features");
    
    // Test adding required patterns
    rules.addRequiredPattern("virtual_functions");
    rules.addRequiredPattern("abstract_classes");
    assert(rules.requiredPatterns.size() == 2);
    assert(rules.requiredPatterns[0] == "virtual_functions");
    assert(rules.requiredPatterns[1] == "abstract_classes");
    
    // Test adding specific checks
    rules.addSpecificCheck("virtual_destructor", "Check for virtual destructor in base classes");
    rules.addSpecificCheck("pure_virtual", "Check for pure virtual functions");
    assert(rules.specificChecks.size() == 2);
    assert(rules.specificChecks["virtual_destructor"] == "Check for virtual destructor in base classes");
    assert(rules.specificChecks["pure_virtual"] == "Check for pure virtual functions");
    
    // Test adding learning objectives
    rules.addLearningObjective("Master inheritance concepts");
    rules.addLearningObjective("Understand polymorphism");
    assert(rules.learningObjectives.size() == 2);
    assert(rules.learningObjectives[0] == "Master inheritance concepts");
    assert(rules.learningObjectives[1] == "Understand polymorphism");
    
    std::cout << "ModuleRules add methods tests passed!" << std::endl;
}

void testModuleRulesQueryMethods() {
    std::cout << "Testing ModuleRules query methods..." << std::endl;
    
    ModuleRules rules;
    rules.addRequiredConcept("classes");
    rules.addRequiredConcept("namespaces");
    rules.addForbiddenFeature("using_namespace_std");
    rules.addForbiddenFeature("friend_functions");
    rules.addSpecificCheck("class_structure", "Check proper class structure");
    rules.addLearningObjective("Learn C++ basics");
    
    // Test isForbidden method
    assert(rules.isForbidden("using_namespace_std") == true);
    assert(rules.isForbidden("friend_functions") == true);
    assert(rules.isForbidden("stl_containers") == false);
    assert(rules.isForbidden("nonexistent") == false);
    
    // Test isRequired method
    assert(rules.isRequired("classes") == true);
    assert(rules.isRequired("namespaces") == true);
    assert(rules.isRequired("inheritance") == false);
    assert(rules.isRequired("nonexistent") == false);
    
    // Test count methods
    assert(rules.getLearningObjectiveCount() == 1);
    assert(rules.getForbiddenFeatureCount() == 2);
    
    // Test hasSpecificCheck method
    assert(rules.hasSpecificCheck("class_structure") == true);
    assert(rules.hasSpecificCheck("nonexistent") == false);
    
    // Test getSpecificCheckDescription method
    assert(rules.getSpecificCheckDescription("class_structure") == "Check proper class structure");
    assert(rules.getSpecificCheckDescription("nonexistent") == "");
    
    std::cout << "ModuleRules query methods tests passed!" << std::endl;
}

void testModuleRulesFactory() {
    std::cout << "Testing ModuleRulesFactory..." << std::endl;
    
    // Test cpp00 rules
    ModuleRules cpp00Rules = ModuleRulesFactory::createCpp00Rules();
    assert(cpp00Rules.isRequired("namespaces") == true);
    assert(cpp00Rules.isRequired("classes") == true);
    assert(cpp00Rules.isForbidden("using_namespace_std") == true);
    assert(cpp00Rules.isForbidden("stl_containers") == true);
    assert(cpp00Rules.hasSpecificCheck("namespace_usage") == true);
    assert(cpp00Rules.getLearningObjectiveCount() > 0);
    
    // Test cpp01 rules
    ModuleRules cpp01Rules = ModuleRulesFactory::createCpp01Rules();
    assert(cpp01Rules.isRequired("memory_allocation") == true);
    assert(cpp01Rules.isRequired("pointers") == true);
    assert(cpp01Rules.isRequired("references") == true);
    assert(cpp01Rules.isForbidden("using_namespace_std") == true);
    assert(cpp01Rules.hasSpecificCheck("memory_leaks") == true);
    assert(cpp01Rules.hasSpecificCheck("pointer_safety") == true);
    
    // Test cpp02 rules
    ModuleRules cpp02Rules = ModuleRulesFactory::createCpp02Rules();
    assert(cpp02Rules.isRequired("orthodox_canonical_form") == true);
    assert(cpp02Rules.isRequired("operator_overloading") == true);
    assert(cpp02Rules.hasSpecificCheck("ocf_compliance") == true);
    assert(cpp02Rules.hasSpecificCheck("operator_overloading") == true);
    
    // Test cpp03 rules
    ModuleRules cpp03Rules = ModuleRulesFactory::createCpp03Rules();
    assert(cpp03Rules.isRequired("inheritance") == true);
    assert(cpp03Rules.isRequired("polymorphism") == true);
    assert(cpp03Rules.isRequired("virtual_functions") == true);
    assert(cpp03Rules.hasSpecificCheck("inheritance_design") == true);
    assert(cpp03Rules.hasSpecificCheck("virtual_destructor") == true);
    
    // Test cpp04 rules
    ModuleRules cpp04Rules = ModuleRulesFactory::createCpp04Rules();
    assert(cpp04Rules.isRequired("abstract_classes") == true);
    assert(cpp04Rules.isRequired("interfaces") == true);
    assert(cpp04Rules.hasSpecificCheck("abstract_design") == true);
    assert(cpp04Rules.hasSpecificCheck("interface_compliance") == true);
    
    // Test createRulesForModule method
    ModuleRules moduleRules0 = ModuleRulesFactory::createRulesForModule(0);
    assert(moduleRules0.isRequired("namespaces") == true);
    
    ModuleRules moduleRules1 = ModuleRulesFactory::createRulesForModule(1);
    assert(moduleRules1.isRequired("memory_allocation") == true);
    
    ModuleRules moduleRules2 = ModuleRulesFactory::createRulesForModule(2);
    assert(moduleRules2.isRequired("orthodox_canonical_form") == true);
    
    ModuleRules moduleRules3 = ModuleRulesFactory::createRulesForModule(3);
    assert(moduleRules3.isRequired("inheritance") == true);
    
    ModuleRules moduleRules4 = ModuleRulesFactory::createRulesForModule(4);
    assert(moduleRules4.isRequired("abstract_classes") == true);
    
    // Test unknown module
    ModuleRules unknownRules = ModuleRulesFactory::createRulesForModule(99);
    assert(unknownRules.requiredConcepts.empty());
    assert(unknownRules.forbiddenFeatures.empty());
    
    std::cout << "ModuleRulesFactory tests passed!" << std::endl;
}

void testValidationExceptionBasicFunctionality() {
    std::cout << "Testing ValidationException basic functionality..." << std::endl;
    
    // Test basic constructor
    ValidationException basicEx("Test error message", FILE_NOT_FOUND);
    assert(std::string(basicEx.what()) == "Test error message");
    assert(basicEx.getErrorCode() == FILE_NOT_FOUND);
    assert(basicEx.getMessage() == "Test error message");
    assert(basicEx.getMessageJa().empty());
    assert(basicEx.getContext().empty());
    assert(basicEx.getSuggestion().empty());
    
    // Test bilingual constructor
    ValidationException bilingualEx("File not found", "ファイルが見つかりません", FILE_NOT_FOUND);
    assert(bilingualEx.getMessage() == "File not found");
    assert(bilingualEx.getMessageJa() == "ファイルが見つかりません");
    assert(bilingualEx.getErrorCode() == FILE_NOT_FOUND);
    
    // Test full constructor
    ValidationException fullEx(
        "Compilation failed",
        "コンパイルに失敗しました",
        COMPILATION_FAILED,
        "g++ -Wall -Wextra -Werror main.cpp",
        "Check syntax errors",
        "構文エラーを確認してください"
    );
    assert(fullEx.getMessage() == "Compilation failed");
    assert(fullEx.getMessageJa() == "コンパイルに失敗しました");
    assert(fullEx.getErrorCode() == COMPILATION_FAILED);
    assert(fullEx.getContext() == "g++ -Wall -Wextra -Werror main.cpp");
    assert(fullEx.getSuggestion() == "Check syntax errors");
    assert(fullEx.getSuggestionJa() == "構文エラーを確認してください");
    
    std::cout << "ValidationException basic functionality tests passed!" << std::endl;
}

void testValidationExceptionSetters() {
    std::cout << "Testing ValidationException setters..." << std::endl;
    
    ValidationException ex("Test message", MEMORY_TOOL_ERROR);
    
    // Test setContext
    ex.setContext("Running valgrind on executable");
    assert(ex.getContext() == "Running valgrind on executable");
    
    // Test setSuggestion
    ex.setSuggestion("Install valgrind", "valgrindをインストールしてください");
    assert(ex.getSuggestion() == "Install valgrind");
    assert(ex.getSuggestionJa() == "valgrindをインストールしてください");
    
    std::cout << "ValidationException setters tests passed!" << std::endl;
}

void testValidationExceptionClassification() {
    std::cout << "Testing ValidationException classification..." << std::endl;
    
    // Test critical errors
    ValidationException compileEx("Compile error", COMPILATION_FAILED);
    assert(compileEx.isCritical() == true);
    assert(compileEx.isSystemError() == false);
    assert(compileEx.isConfigurationError() == false);
    
    ValidationException memoryEx("Memory error", MEMORY_TOOL_ERROR);
    assert(memoryEx.isCritical() == true);
    
    // Test system errors
    ValidationException permEx("Permission denied", INSUFFICIENT_PERMISSIONS);
    assert(permEx.isCritical() == false);
    assert(permEx.isSystemError() == true);
    assert(permEx.isConfigurationError() == false);
    
    ValidationException memoryLimitEx("Out of memory", INSUFFICIENT_MEMORY);
    assert(memoryLimitEx.isSystemError() == true);
    
    // Test configuration errors
    ValidationException configEx("Invalid config", INVALID_MODULE_CONFIG);
    assert(configEx.isCritical() == false);
    assert(configEx.isSystemError() == false);
    assert(configEx.isConfigurationError() == true);
    
    ValidationException rulesEx("Missing rules", MISSING_MODULE_RULES);
    assert(rulesEx.isConfigurationError() == true);
    
    // Test file system errors (not critical, not system, not config)
    ValidationException fileEx("File not found", FILE_NOT_FOUND);
    assert(fileEx.isCritical() == false);
    assert(fileEx.isSystemError() == false);
    assert(fileEx.isConfigurationError() == false);
    
    std::cout << "ValidationException classification tests passed!" << std::endl;
}

void testValidationExceptionCategories() {
    std::cout << "Testing ValidationException categories..." << std::endl;
    
    // Test file system category
    ValidationException fileEx("File error", FILE_NOT_FOUND);
    assert(fileEx.getErrorCategory() == "FILE_SYSTEM");
    
    ValidationException accessEx("Access denied", FILE_ACCESS_DENIED);
    assert(accessEx.getErrorCategory() == "FILE_SYSTEM");
    
    // Test compilation category
    ValidationException compileEx("Compile error", COMPILATION_FAILED);
    assert(compileEx.getErrorCategory() == "COMPILATION");
    
    ValidationException linkerEx("Link error", LINKING_FAILED);
    assert(linkerEx.getErrorCategory() == "COMPILATION");
    
    // Test memory analysis category
    ValidationException memoryEx("Memory error", MEMORY_TOOL_ERROR);
    assert(memoryEx.getErrorCategory() == "MEMORY_ANALYSIS");
    
    ValidationException valgrindEx("Valgrind error", VALGRIND_FAILED);
    assert(valgrindEx.getErrorCategory() == "MEMORY_ANALYSIS");
    
    // Test configuration category
    ValidationException configEx("Config error", INVALID_MODULE_CONFIG);
    assert(configEx.getErrorCategory() == "CONFIGURATION");
    
    ValidationException rulesEx("Rules error", MISSING_MODULE_RULES);
    assert(rulesEx.getErrorCategory() == "CONFIGURATION");
    
    // Test external tool category
    ValidationException toolEx("Tool error", EXTERNAL_TOOL_UNAVAILABLE);
    assert(toolEx.getErrorCategory() == "EXTERNAL_TOOL");
    
    ValidationException timeoutEx("Timeout error", EXTERNAL_TOOL_TIMEOUT);
    assert(timeoutEx.getErrorCategory() == "EXTERNAL_TOOL");
    
    // Test validation logic category
    ValidationException validationEx("Validation error", INVALID_VALIDATION_CONTEXT);
    assert(validationEx.getErrorCategory() == "VALIDATION_LOGIC");
    
    ValidationException logicEx("Logic error", VALIDATION_LOGIC_ERROR);
    assert(logicEx.getErrorCategory() == "VALIDATION_LOGIC");
    
    // Test system category
    ValidationException systemEx("System error", INSUFFICIENT_PERMISSIONS);
    assert(systemEx.getErrorCategory() == "SYSTEM");
    
    ValidationException platformEx("Platform error", PLATFORM_NOT_SUPPORTED);
    assert(platformEx.getErrorCategory() == "SYSTEM");
    
    // Test unknown category
    ValidationException unknownEx("Unknown error", UNKNOWN_ERROR);
    assert(unknownEx.getErrorCategory() == "UNKNOWN");
    
    std::cout << "ValidationException categories tests passed!" << std::endl;
}

void testValidationExceptionErrorCodeStrings() {
    std::cout << "Testing ValidationException error code strings..." << std::endl;
    
    // Test a few key error codes
    ValidationException fileEx("File error", FILE_NOT_FOUND);
    assert(fileEx.getErrorCodeString() == "FILE_NOT_FOUND");
    
    ValidationException compileEx("Compile error", COMPILATION_FAILED);
    assert(compileEx.getErrorCodeString() == "COMPILATION_FAILED");
    
    ValidationException memoryEx("Memory error", MEMORY_TOOL_ERROR);
    assert(memoryEx.getErrorCodeString() == "MEMORY_TOOL_ERROR");
    
    ValidationException configEx("Config error", INVALID_MODULE_CONFIG);
    assert(configEx.getErrorCodeString() == "INVALID_MODULE_CONFIG");
    
    ValidationException unknownEx("Unknown error", UNKNOWN_ERROR);
    assert(unknownEx.getErrorCodeString() == "UNKNOWN_ERROR");
    
    std::cout << "ValidationException error code strings tests passed!" << std::endl;
}

void testValidationExceptionFormattedMessage() {
    std::cout << "Testing ValidationException formatted message..." << std::endl;
    
    ValidationException ex("File not found", FILE_NOT_FOUND);
    ex.setContext("/path/to/missing/file.cpp");
    ex.setSuggestion("Check file path", "ファイルパスを確認してください");
    
    std::string formatted = ex.getFormattedMessage();
    assert(formatted.find("[FILE_SYSTEM:FILE_NOT_FOUND]") != std::string::npos);
    assert(formatted.find("File not found") != std::string::npos);
    assert(formatted.find("Context: /path/to/missing/file.cpp") != std::string::npos);
    assert(formatted.find("Suggestion: Check file path") != std::string::npos);
    
    // Test without context and suggestion
    ValidationException simpleEx("Simple error", COMPILATION_FAILED);
    std::string simpleFormatted = simpleEx.getFormattedMessage();
    assert(simpleFormatted.find("[COMPILATION:COMPILATION_FAILED]") != std::string::npos);
    assert(simpleFormatted.find("Simple error") != std::string::npos);
    assert(simpleFormatted.find("Context:") == std::string::npos);
    assert(simpleFormatted.find("Suggestion:") == std::string::npos);
    
    std::cout << "ValidationException formatted message tests passed!" << std::endl;
}

void testValidationExceptionFactory() {
    std::cout << "Testing ValidationExceptionFactory..." << std::endl;
    
    // Test createFileNotFound
    ValidationException fileEx = ValidationExceptionFactory::createFileNotFound("/path/to/file.cpp");
    assert(fileEx.getErrorCode() == FILE_NOT_FOUND);
    assert(fileEx.getMessage().find("File not found") != std::string::npos);
    assert(fileEx.getMessageJa().find("ファイルが見つかりません") != std::string::npos);
    assert(fileEx.getContext().find("/path/to/file.cpp") != std::string::npos);
    assert(!fileEx.getSuggestion().empty());
    assert(!fileEx.getSuggestionJa().empty());
    
    // Test createCompilationFailed
    ValidationException compileEx = ValidationExceptionFactory::createCompilationFailed("error: syntax error");
    assert(compileEx.getErrorCode() == COMPILATION_FAILED);
    assert(compileEx.getMessage() == "Compilation failed");
    assert(compileEx.getMessageJa() == "コンパイルに失敗しました");
    assert(compileEx.getContext().find("error: syntax error") != std::string::npos);
    assert(!compileEx.getSuggestion().empty());
    
    // Test createMemoryToolError
    ValidationException memoryEx = ValidationExceptionFactory::createMemoryToolError("valgrind", "tool not found");
    assert(memoryEx.getErrorCode() == MEMORY_TOOL_ERROR);
    assert(memoryEx.getMessage().find("valgrind") != std::string::npos);
    assert(memoryEx.getMessageJa().find("valgrind") != std::string::npos);
    assert(memoryEx.getContext().find("tool not found") != std::string::npos);
    assert(!memoryEx.getSuggestion().empty());
    
    // Test createInvalidModuleConfig
    ValidationException configEx = ValidationExceptionFactory::createInvalidModuleConfig("cpp99");
    assert(configEx.getErrorCode() == INVALID_MODULE_CONFIG);
    assert(configEx.getMessage().find("cpp99") != std::string::npos);
    assert(configEx.getMessageJa().find("cpp99") != std::string::npos);
    assert(configEx.getContext().find("cpp99") != std::string::npos);
    assert(!configEx.getSuggestion().empty());
    
    std::cout << "ValidationExceptionFactory tests passed!" << std::endl;
}

void testErrorCodeEnumeration() {
    std::cout << "Testing ErrorCode enumeration..." << std::endl;
    
    // Test that error codes have expected values and ranges
    assert(FILE_NOT_FOUND == 1000);
    assert(COMPILATION_FAILED == 2000);
    assert(MEMORY_TOOL_ERROR == 3000);
    assert(INVALID_MODULE_CONFIG == 4000);
    assert(EXTERNAL_TOOL_UNAVAILABLE == 5000);
    assert(INVALID_VALIDATION_CONTEXT == 6000);
    assert(INSUFFICIENT_PERMISSIONS == 7000);
    assert(UNKNOWN_ERROR == 9999);
    
    // Test that error codes are properly categorized
    assert(FILE_NOT_FOUND < COMPILATION_FAILED);
    assert(COMPILATION_FAILED < MEMORY_TOOL_ERROR);
    assert(MEMORY_TOOL_ERROR < INVALID_MODULE_CONFIG);
    assert(INVALID_MODULE_CONFIG < EXTERNAL_TOOL_UNAVAILABLE);
    assert(EXTERNAL_TOOL_UNAVAILABLE < INVALID_VALIDATION_CONTEXT);
    assert(INVALID_VALIDATION_CONTEXT < INSUFFICIENT_PERMISSIONS);
    assert(INSUFFICIENT_PERMISSIONS < UNKNOWN_ERROR);
    
    std::cout << "ErrorCode enumeration tests passed!" << std::endl;
}

int main() {
    std::cout << "Running ModuleRules and ValidationException tests..." << std::endl;
    std::cout << "====================================================" << std::endl;
    
    try {
        // ModuleRules tests
        testModuleRulesBasicFunctionality();
        testModuleRulesAddMethods();
        testModuleRulesQueryMethods();
        testModuleRulesFactory();
        
        // ValidationException tests
        testValidationExceptionBasicFunctionality();
        testValidationExceptionSetters();
        testValidationExceptionClassification();
        testValidationExceptionCategories();
        testValidationExceptionErrorCodeStrings();
        testValidationExceptionFormattedMessage();
        testValidationExceptionFactory();
        
        // ErrorCode tests
        testErrorCodeEnumeration();
        
        std::cout << std::endl << "All ModuleRules and ValidationException tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cout << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Test failed with unknown exception" << std::endl;
        return 1;
    }
}