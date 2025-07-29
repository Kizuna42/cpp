#ifndef MODULERULES_HPP
#define MODULERULES_HPP

#include <string>
#include <vector>
#include <map>

/**
 * @brief Contains rules and requirements specific to each C++ module
 * 
 * This structure defines the learning objectives, forbidden features,
 * required patterns, and specific checks for each module (cpp00-cpp04).
 */
struct ModuleRules {
    std::vector<std::string> requiredConcepts;
    std::vector<std::string> forbiddenFeatures;
    std::vector<std::string> requiredPatterns;
    std::map<std::string, std::string> specificChecks;
    std::vector<std::string> learningObjectives;
    
    ModuleRules() {}
    
    /**
     * @brief Constructor with basic parameters
     * @param concepts Required concepts for this module
     * @param forbidden Features forbidden in this module
     * @param patterns Required design patterns
     */
    ModuleRules(const std::vector<std::string>& concepts,
                const std::vector<std::string>& forbidden,
                const std::vector<std::string>& patterns)
        : requiredConcepts(concepts), forbiddenFeatures(forbidden), requiredPatterns(patterns) {}
    
    /**
     * @brief Add a required concept to the module
     * @param concept The concept name
     */
    void addRequiredConcept(const std::string& concept) {
        requiredConcepts.push_back(concept);
    }
    
    /**
     * @brief Add a forbidden feature to the module
     * @param feature The forbidden feature name
     */
    void addForbiddenFeature(const std::string& feature) {
        forbiddenFeatures.push_back(feature);
    }
    
    /**
     * @brief Add a required pattern to the module
     * @param pattern The pattern name
     */
    void addRequiredPattern(const std::string& pattern) {
        requiredPatterns.push_back(pattern);
    }
    
    /**
     * @brief Add a specific check rule
     * @param checkName The name of the check
     * @param checkDescription Description of what to check
     */
    void addSpecificCheck(const std::string& checkName, const std::string& checkDescription) {
        specificChecks[checkName] = checkDescription;
    }
    
    /**
     * @brief Add a learning objective
     * @param objective The learning objective description
     */
    void addLearningObjective(const std::string& objective) {
        learningObjectives.push_back(objective);
    }
    
    /**
     * @brief Check if a feature is forbidden in this module
     * @param feature The feature to check
     * @return true if the feature is forbidden
     */
    bool isForbidden(const std::string& feature) const {
        for (std::vector<std::string>::const_iterator it = forbiddenFeatures.begin();
             it != forbiddenFeatures.end(); ++it) {
            if (*it == feature) {
                return true;
            }
        }
        return false;
    }
    
    /**
     * @brief Check if a concept is required in this module
     * @param concept The concept to check
     * @return true if the concept is required
     */
    bool isRequired(const std::string& concept) const {
        for (std::vector<std::string>::const_iterator it = requiredConcepts.begin();
             it != requiredConcepts.end(); ++it) {
            if (*it == concept) {
                return true;
            }
        }
        return false;
    }
    
    /**
     * @brief Get the number of learning objectives
     * @return Number of learning objectives
     */
    size_t getLearningObjectiveCount() const {
        return learningObjectives.size();
    }
    
    /**
     * @brief Get the number of forbidden features
     * @return Number of forbidden features
     */
    size_t getForbiddenFeatureCount() const {
        return forbiddenFeatures.size();
    }
    
    /**
     * @brief Check if module has specific check
     * @param checkName The check name to look for
     * @return true if the check exists
     */
    bool hasSpecificCheck(const std::string& checkName) const {
        return specificChecks.find(checkName) != specificChecks.end();
    }
    
    /**
     * @brief Get description of a specific check
     * @param checkName The check name
     * @return Description of the check, empty string if not found
     */
    std::string getSpecificCheckDescription(const std::string& checkName) const {
        std::map<std::string, std::string>::const_iterator it = specificChecks.find(checkName);
        if (it != specificChecks.end()) {
            return it->second;
        }
        return "";
    }
};

/**
 * @brief Factory class for creating module-specific rules
 */
class ModuleRulesFactory {
public:
    /**
     * @brief Create rules for cpp00 module
     * @return ModuleRules configured for cpp00
     */
    static ModuleRules createCpp00Rules() {
        ModuleRules rules;
        
        // Required concepts for cpp00
        rules.addRequiredConcept("namespaces");
        rules.addRequiredConcept("classes");
        rules.addRequiredConcept("member_functions");
        rules.addRequiredConcept("stdio_streams");
        rules.addRequiredConcept("initialization_lists");
        
        // Forbidden features in cpp00
        rules.addForbiddenFeature("using_namespace_std");
        rules.addForbiddenFeature("friend_functions");
        rules.addForbiddenFeature("stl_containers");
        rules.addForbiddenFeature("cpp11_features");
        
        // Required patterns
        rules.addRequiredPattern("class_definition");
        rules.addRequiredPattern("member_function_implementation");
        
        // Specific checks
        rules.addSpecificCheck("namespace_usage", "Check proper namespace usage without 'using namespace std'");
        rules.addSpecificCheck("class_structure", "Verify proper class structure with public/private sections");
        
        // Learning objectives
        rules.addLearningObjective("Understand C++ namespaces and their proper usage");
        rules.addLearningObjective("Learn basic class definition and member functions");
        rules.addLearningObjective("Master iostream usage without using namespace std");
        
        return rules;
    }
    
    /**
     * @brief Create rules for cpp01 module
     * @return ModuleRules configured for cpp01
     */
    static ModuleRules createCpp01Rules() {
        ModuleRules rules;
        
        // Required concepts for cpp01
        rules.addRequiredConcept("memory_allocation");
        rules.addRequiredConcept("pointers");
        rules.addRequiredConcept("references");
        rules.addRequiredConcept("switch_statements");
        
        // Forbidden features in cpp01
        rules.addForbiddenFeature("using_namespace_std");
        rules.addForbiddenFeature("friend_functions");
        rules.addForbiddenFeature("stl_containers");
        rules.addForbiddenFeature("cpp11_features");
        
        // Required patterns
        rules.addRequiredPattern("proper_memory_management");
        rules.addRequiredPattern("pointer_usage");
        rules.addRequiredPattern("reference_usage");
        
        // Specific checks
        rules.addSpecificCheck("memory_leaks", "Check for proper memory allocation and deallocation");
        rules.addSpecificCheck("pointer_safety", "Verify safe pointer usage and null checks");
        
        // Learning objectives
        rules.addLearningObjective("Master dynamic memory allocation with new/delete");
        rules.addLearningObjective("Understand the difference between pointers and references");
        rules.addLearningObjective("Learn proper memory management techniques");
        
        return rules;
    }
    
    /**
     * @brief Create rules for cpp02 module
     * @return ModuleRules configured for cpp02
     */
    static ModuleRules createCpp02Rules() {
        ModuleRules rules;
        
        // Required concepts for cpp02
        rules.addRequiredConcept("orthodox_canonical_form");
        rules.addRequiredConcept("operator_overloading");
        rules.addRequiredConcept("fixed_point_arithmetic");
        
        // Forbidden features in cpp02
        rules.addForbiddenFeature("using_namespace_std");
        rules.addForbiddenFeature("friend_functions");
        rules.addForbiddenFeature("stl_containers");
        rules.addForbiddenFeature("cpp11_features");
        
        // Required patterns
        rules.addRequiredPattern("orthodox_canonical_form");
        rules.addRequiredPattern("operator_overloading");
        
        // Specific checks
        rules.addSpecificCheck("ocf_compliance", "Check Orthodox Canonical Form implementation");
        rules.addSpecificCheck("operator_overloading", "Verify proper operator overloading");
        
        // Learning objectives
        rules.addLearningObjective("Implement Orthodox Canonical Form (Big Four)");
        rules.addLearningObjective("Master operator overloading techniques");
        rules.addLearningObjective("Understand fixed-point arithmetic implementation");
        
        return rules;
    }
    
    /**
     * @brief Create rules for cpp03 module
     * @return ModuleRules configured for cpp03
     */
    static ModuleRules createCpp03Rules() {
        ModuleRules rules;
        
        // Required concepts for cpp03
        rules.addRequiredConcept("inheritance");
        rules.addRequiredConcept("polymorphism");
        rules.addRequiredConcept("virtual_functions");
        
        // Forbidden features in cpp03
        rules.addForbiddenFeature("using_namespace_std");
        rules.addForbiddenFeature("friend_functions");
        rules.addForbiddenFeature("stl_containers");
        rules.addForbiddenFeature("cpp11_features");
        
        // Required patterns
        rules.addRequiredPattern("inheritance_hierarchy");
        rules.addRequiredPattern("virtual_function_usage");
        
        // Specific checks
        rules.addSpecificCheck("inheritance_design", "Check proper inheritance design");
        rules.addSpecificCheck("virtual_destructor", "Verify virtual destructor in base classes");
        
        // Learning objectives
        rules.addLearningObjective("Master inheritance and polymorphism concepts");
        rules.addLearningObjective("Understand virtual function mechanisms");
        rules.addLearningObjective("Learn proper inheritance design patterns");
        
        return rules;
    }
    
    /**
     * @brief Create rules for cpp04 module
     * @return ModuleRules configured for cpp04
     */
    static ModuleRules createCpp04Rules() {
        ModuleRules rules;
        
        // Required concepts for cpp04
        rules.addRequiredConcept("abstract_classes");
        rules.addRequiredConcept("interfaces");
        rules.addRequiredConcept("subtype_polymorphism");
        
        // Forbidden features in cpp04
        rules.addForbiddenFeature("using_namespace_std");
        rules.addForbiddenFeature("friend_functions");
        rules.addForbiddenFeature("stl_containers");
        rules.addForbiddenFeature("cpp11_features");
        
        // Required patterns
        rules.addRequiredPattern("abstract_base_class");
        rules.addRequiredPattern("interface_implementation");
        
        // Specific checks
        rules.addSpecificCheck("abstract_design", "Check proper abstract class design");
        rules.addSpecificCheck("interface_compliance", "Verify interface implementation");
        
        // Learning objectives
        rules.addLearningObjective("Master abstract classes and pure virtual functions");
        rules.addLearningObjective("Understand interface design principles");
        rules.addLearningObjective("Learn advanced polymorphism techniques");
        
        return rules;
    }
    
    /**
     * @brief Create rules based on module type
     * @param moduleType The type of module
     * @return ModuleRules configured for the specified module
     */
    static ModuleRules createRulesForModule(int moduleType) {
        switch (moduleType) {
            case 0: return createCpp00Rules();
            case 1: return createCpp01Rules();
            case 2: return createCpp02Rules();
            case 3: return createCpp03Rules();
            case 4: return createCpp04Rules();
            default: return ModuleRules(); // Empty rules for unknown modules
        }
    }
};

#endif // MODULERULES_HPP