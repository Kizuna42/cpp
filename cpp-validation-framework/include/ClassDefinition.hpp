#ifndef CLASSDEFINITION_HPP
#define CLASSDEFINITION_HPP

#include <string>
#include <vector>

/**
 * @brief Enumeration of access specifiers
 */
enum AccessSpecifier {
    ACCESS_PRIVATE,
    ACCESS_PROTECTED,
    ACCESS_PUBLIC,
    ACCESS_UNKNOWN
};

/**
 * @brief Enumeration of member types
 */
enum MemberType {
    MEMBER_VARIABLE,
    MEMBER_FUNCTION,
    CONSTRUCTOR,
    DESTRUCTOR,
    COPY_CONSTRUCTOR,
    ASSIGNMENT_OPERATOR
};

/**
 * @brief Structure representing a class member
 */
struct ClassMember {
    std::string name;
    std::string type;
    MemberType memberType;
    AccessSpecifier access;
    bool isStatic;
    bool isConst;
    bool isVirtual;
    int lineNumber;
    std::string signature;  // Full function signature for functions
    
    ClassMember() 
        : memberType(MEMBER_VARIABLE), access(ACCESS_PRIVATE), 
          isStatic(false), isConst(false), isVirtual(false), lineNumber(0) {}
    
    ClassMember(const std::string& n, const std::string& t, MemberType mt, AccessSpecifier acc, int line)
        : name(n), type(t), memberType(mt), access(acc), 
          isStatic(false), isConst(false), isVirtual(false), lineNumber(line) {}
    
    /**
     * @brief Check if this member is a constructor
     * @return True if this is any type of constructor
     */
    bool isConstructor() const {
        return memberType == CONSTRUCTOR || memberType == COPY_CONSTRUCTOR;
    }
    
    /**
     * @brief Check if this member is a function (including constructors/destructors)
     * @return True if this is a function-type member
     */
    bool isFunction() const {
        return memberType == MEMBER_FUNCTION || memberType == CONSTRUCTOR || 
               memberType == DESTRUCTOR || memberType == COPY_CONSTRUCTOR || 
               memberType == ASSIGNMENT_OPERATOR;
    }
    
    /**
     * @brief Get access specifier as string
     * @return String representation of access specifier
     */
    std::string getAccessString() const {
        switch (access) {
            case ACCESS_PRIVATE: return "private";
            case ACCESS_PROTECTED: return "protected";
            case ACCESS_PUBLIC: return "public";
            default: return "unknown";
        }
    }
    
    /**
     * @brief Get member type as string
     * @return String representation of member type
     */
    std::string getMemberTypeString() const {
        switch (memberType) {
            case MEMBER_VARIABLE: return "variable";
            case MEMBER_FUNCTION: return "function";
            case CONSTRUCTOR: return "constructor";
            case DESTRUCTOR: return "destructor";
            case COPY_CONSTRUCTOR: return "copy_constructor";
            case ASSIGNMENT_OPERATOR: return "assignment_operator";
            default: return "unknown";
        }
    }
};

/**
 * @brief Structure representing a complete class definition
 */
struct ClassDefinition {
    std::string name;
    std::string fileName;
    int startLine;
    int endLine;
    std::vector<ClassMember> members;
    std::vector<std::string> baseClasses;
    bool isAbstract;
    
    ClassDefinition() : startLine(0), endLine(0), isAbstract(false) {}
    
    ClassDefinition(const std::string& n, const std::string& file, int start)
        : name(n), fileName(file), startLine(start), endLine(0), isAbstract(false) {}
    
    /**
     * @brief Add a member to this class
     * @param member The member to add
     */
    void addMember(const ClassMember& member) {
        members.push_back(member);
    }
    
    /**
     * @brief Get all members of a specific type
     * @param type The member type to filter by
     * @return Vector of members matching the type
     */
    std::vector<ClassMember> getMembersByType(MemberType type) const {
        std::vector<ClassMember> result;
        for (size_t i = 0; i < members.size(); ++i) {
            if (members[i].memberType == type) {
                result.push_back(members[i]);
            }
        }
        return result;
    }
    
    /**
     * @brief Get all members with a specific access level
     * @param access The access level to filter by
     * @return Vector of members with the specified access level
     */
    std::vector<ClassMember> getMembersByAccess(AccessSpecifier access) const {
        std::vector<ClassMember> result;
        for (size_t i = 0; i < members.size(); ++i) {
            if (members[i].access == access) {
                result.push_back(members[i]);
            }
        }
        return result;
    }
    
    /**
     * @brief Check if class has a default constructor
     * @return True if class has a default constructor
     */
    bool hasDefaultConstructor() const {
        std::vector<ClassMember> constructors = getMembersByType(CONSTRUCTOR);
        for (size_t i = 0; i < constructors.size(); ++i) {
            // Check if constructor has no parameters (default constructor)
            if (constructors[i].signature.find("()") != std::string::npos) {
                return true;
            }
        }
        return false;
    }
    
    /**
     * @brief Check if class has a copy constructor
     * @return True if class has a copy constructor
     */
    bool hasCopyConstructor() const {
        return !getMembersByType(COPY_CONSTRUCTOR).empty();
    }
    
    /**
     * @brief Check if class has an assignment operator
     * @return True if class has an assignment operator
     */
    bool hasAssignmentOperator() const {
        return !getMembersByType(ASSIGNMENT_OPERATOR).empty();
    }
    
    /**
     * @brief Check if class has a destructor
     * @return True if class has a destructor
     */
    bool hasDestructor() const {
        return !getMembersByType(DESTRUCTOR).empty();
    }
    
    /**
     * @brief Get the number of constructors
     * @return Number of constructors (including copy constructor)
     */
    size_t getConstructorCount() const {
        return getMembersByType(CONSTRUCTOR).size() + getMembersByType(COPY_CONSTRUCTOR).size();
    }
    
    /**
     * @brief Get the number of member variables
     * @return Number of member variables
     */
    size_t getMemberVariableCount() const {
        return getMembersByType(MEMBER_VARIABLE).size();
    }
    
    /**
     * @brief Get the number of member functions
     * @return Number of member functions
     */
    size_t getMemberFunctionCount() const {
        return getMembersByType(MEMBER_FUNCTION).size();
    }
};

#endif // CLASSDEFINITION_HPP