#ifndef FORBIDDENFEATUREDETECTOR_HPP
#define FORBIDDENFEATUREDETECTOR_HPP

#include "IValidator.hpp"
#include <string>
#include <vector>
#include <map>

/**
 * @brief Represents a forbidden feature found in code
 */
struct ForbiddenFeature {
    std::string featureName;
    std::string pattern;
    std::string description;
    std::string descriptionJa;
    Issue::Severity severity;
    
    ForbiddenFeature(const std::string& name, const std::string& pat, 
                    const std::string& desc, const std::string& descJa,
                    Issue::Severity sev = Issue::MAJOR)
        : featureName(name), pattern(pat), description(desc), 
          descriptionJa(descJa), severity(sev) {}
};

/**
 * @brief Detects forbidden C++11+ features and 42 School specific restrictions
 * 
 * This class implements detection of features that are not allowed in 42 School
 * C++ exercises, including C++11+ features, STL containers, using namespace, etc.
 */
class ForbiddenFeatureDetector : public IValidator {
public:
    ForbiddenFeatureDetector();
    virtual ~ForbiddenFeatureDetector();
    
    // IValidator interface implementation
    virtual ValidationResult validate(const ValidationContext& context);
    virtual std::string getName() const;
    virtual Priority getPriority() const;
    
    /**
     * @brief Detect forbidden features in source code
     * @param sourceCode The source code to analyze
     * @param fileName The name of the file being analyzed
     * @return Vector of detected forbidden features with line numbers
     */
    std::vector<Issue> detectForbiddenFeatures(const std::string& sourceCode, 
                                              const std::string& fileName);

private:
    std::vector<ForbiddenFeature> forbiddenFeatures_;
    
    /**
     * @brief Initialize the list of forbidden features with their patterns
     */
    void initializeForbiddenFeatures();
    
    /**
     * @brief Check if a line contains a forbidden feature
     * @param line The line of code to check
     * @param feature The forbidden feature to check for
     * @return true if the feature is found
     */
    bool matchesPattern(const std::string& line, const ForbiddenFeature& feature);
    
    /**
     * @brief Create an issue for a detected forbidden feature
     * @param feature The detected forbidden feature
     * @param fileName The file where it was found
     * @param lineNumber The line number where it was found
     * @param line The actual line of code
     * @return Issue object representing the problem
     */
    Issue createIssue(const ForbiddenFeature& feature, const std::string& fileName,
                     int lineNumber, const std::string& line);
    
    /**
     * @brief Check if line is inside a comment
     * @param line The line to check
     * @param inBlockComment Reference to track block comment state
     * @return true if the line is commented out
     */
    bool isCommentedOut(const std::string& line, bool& inBlockComment);
    
    /**
     * @brief Remove string literals from line to avoid false positives
     * @param line The line to process
     * @return Line with string literals removed
     */
    std::string removeStringLiterals(const std::string& line);
};

#endif // FORBIDDENFEATUREDETECTOR_HPP