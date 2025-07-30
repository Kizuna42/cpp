#include "ForbiddenFeatureDetector.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>

ForbiddenFeatureDetector::ForbiddenFeatureDetector() {
    initializeForbiddenFeatures();
}

ForbiddenFeatureDetector::~ForbiddenFeatureDetector() {
}

ValidationResult ForbiddenFeatureDetector::validate(const ValidationContext& context) {
    ValidationResult result("ForbiddenFeatureDetector");
    
    // Check all source files
    for (std::vector<std::string>::const_iterator it = context.sourceFiles.begin();
         it != context.sourceFiles.end(); ++it) {
        
        std::ifstream file(it->c_str());
        if (!file.is_open()) {
            Issue issue(Issue::CRITICAL, "FILE_ACCESS_ERROR", 
                       "Could not open file: " + *it);
            issue.messageJa = "ファイルを開けませんでした: " + *it;
            issue.fileName = *it;
            result.addIssue(issue);
            continue;
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string sourceCode = buffer.str();
        file.close();
        
        std::vector<Issue> issues = detectForbiddenFeatures(sourceCode, *it);
        for (std::vector<Issue>::const_iterator issueIt = issues.begin();
             issueIt != issues.end(); ++issueIt) {
            result.addIssue(*issueIt);
        }
    }
    
    // Check header files as well
    for (std::vector<std::string>::const_iterator it = context.headerFiles.begin();
         it != context.headerFiles.end(); ++it) {
        
        std::ifstream file(it->c_str());
        if (!file.is_open()) {
            Issue issue(Issue::CRITICAL, "FILE_ACCESS_ERROR", 
                       "Could not open file: " + *it);
            issue.messageJa = "ファイルを開けませんでした: " + *it;
            issue.fileName = *it;
            result.addIssue(issue);
            continue;
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string sourceCode = buffer.str();
        file.close();
        
        std::vector<Issue> issues = detectForbiddenFeatures(sourceCode, *it);
        for (std::vector<Issue>::const_iterator issueIt = issues.begin();
             issueIt != issues.end(); ++issueIt) {
            result.addIssue(*issueIt);
        }
    }
    
    result.addMetric("files_checked", 
                    std::to_string(context.sourceFiles.size() + context.headerFiles.size()));
    result.addMetric("forbidden_features_found", std::to_string(result.issues.size()));
    
    return result;
}

std::string ForbiddenFeatureDetector::getName() const {
    return "ForbiddenFeatureDetector";
}

IValidator::Priority ForbiddenFeatureDetector::getPriority() const {
    return HIGH;
}

std::vector<Issue> ForbiddenFeatureDetector::detectForbiddenFeatures(
    const std::string& sourceCode, const std::string& fileName) {
    
    std::vector<Issue> issues;
    std::istringstream stream(sourceCode);
    std::string line;
    int lineNumber = 0;
    bool inBlockComment = false;
    
    while (std::getline(stream, line)) {
        lineNumber++;
        
        // Skip commented lines
        if (isCommentedOut(line, inBlockComment)) {
            continue;
        }
        
        // Remove string literals to avoid false positives
        std::string processedLine = removeStringLiterals(line);
        
        // Check each forbidden feature
        for (std::vector<ForbiddenFeature>::const_iterator it = forbiddenFeatures_.begin();
             it != forbiddenFeatures_.end(); ++it) {
            
            if (matchesPattern(processedLine, *it)) {
                Issue issue = createIssue(*it, fileName, lineNumber, line);
                issues.push_back(issue);
            }
        }
    }
    
    return issues;
}

void ForbiddenFeatureDetector::initializeForbiddenFeatures() {
    // C++11+ auto keyword
    forbiddenFeatures_.push_back(ForbiddenFeature(
        "auto", "\\bauto\\b",
        "C++11 'auto' keyword is not allowed in C++98",
        "C++11の'auto'キーワードはC++98では使用できません",
        Issue::MAJOR
    ));
    
    // C++11+ nullptr
    forbiddenFeatures_.push_back(ForbiddenFeature(
        "nullptr", "\\bnullptr\\b",
        "C++11 'nullptr' is not allowed in C++98, use NULL instead",
        "C++11の'nullptr'はC++98では使用できません。NULLを使用してください",
        Issue::MAJOR
    ));
    
    // C++11+ range-based for loops
    forbiddenFeatures_.push_back(ForbiddenFeature(
        "range_for", "for\\s*\\(.*:\\s*.*\\)",
        "C++11 range-based for loops are not allowed in C++98",
        "C++11の範囲ベースforループはC++98では使用できません",
        Issue::MAJOR
    ));
    
    // using namespace (42 School specific)
    forbiddenFeatures_.push_back(ForbiddenFeature(
        "using_namespace", "using\\s+namespace\\s+\\w+",
        "using namespace is forbidden in 42 School exercises",
        "using namespaceは42スクールの課題では禁止されています",
        Issue::CRITICAL
    ));
    
    // friend keyword (42 School specific)
    forbiddenFeatures_.push_back(ForbiddenFeature(
        "friend", "\\bfriend\\b",
        "friend keyword is forbidden in 42 School exercises",
        "friendキーワードは42スクールの課題では禁止されています",
        Issue::CRITICAL
    ));
    
    // STL containers
    forbiddenFeatures_.push_back(ForbiddenFeature(
        "std_vector", "std::vector|#include\\s*<vector>",
        "STL containers like std::vector are forbidden in 42 School exercises",
        "std::vectorなどのSTLコンテナは42スクールの課題では禁止されています",
        Issue::CRITICAL
    ));
    
    forbiddenFeatures_.push_back(ForbiddenFeature(
        "std_list", "std::list|#include\\s*<list>",
        "STL containers like std::list are forbidden in 42 School exercises",
        "std::listなどのSTLコンテナは42スクールの課題では禁止されています",
        Issue::CRITICAL
    ));
    
    forbiddenFeatures_.push_back(ForbiddenFeature(
        "std_map", "std::map|#include\\s*<map>",
        "STL containers like std::map are forbidden in 42 School exercises",
        "std::mapなどのSTLコンテナは42スクールの課題では禁止されています",
        Issue::CRITICAL
    ));
    
    forbiddenFeatures_.push_back(ForbiddenFeature(
        "std_set", "std::set|#include\\s*<set>",
        "STL containers like std::set are forbidden in 42 School exercises",
        "std::setなどのSTLコンテナは42スクールの課題では禁止されています",
        Issue::CRITICAL
    ));
    
    // C++11+ lambda expressions
    forbiddenFeatures_.push_back(ForbiddenFeature(
        "lambda", "\\[.*\\]\\s*\\(.*\\)\\s*\\{",
        "C++11 lambda expressions are not allowed in C++98",
        "C++11のラムダ式はC++98では使用できません",
        Issue::MAJOR
    ));
    
    // C++11+ initializer lists
    forbiddenFeatures_.push_back(ForbiddenFeature(
        "initializer_list", "\\{.*,.*\\}\\s*;",
        "C++11 initializer lists are not allowed in C++98",
        "C++11の初期化リストはC++98では使用できません",
        Issue::MAJOR
    ));
    
    // C++11+ decltype
    forbiddenFeatures_.push_back(ForbiddenFeature(
        "decltype", "\\bdecltype\\b",
        "C++11 'decltype' is not allowed in C++98",
        "C++11の'decltype'はC++98では使用できません",
        Issue::MAJOR
    ));
}

bool ForbiddenFeatureDetector::matchesPattern(const std::string& line, 
                                             const ForbiddenFeature& feature) {
    try {
        std::regex pattern(feature.pattern);
        return std::regex_search(line, pattern);
    } catch (const std::regex_error&) {
        // If regex fails, fall back to simple string search
        return line.find(feature.featureName) != std::string::npos;
    }
}

Issue ForbiddenFeatureDetector::createIssue(const ForbiddenFeature& feature,
                                           const std::string& fileName,
                                           int lineNumber, const std::string& /* line */) {
    Issue issue;
    issue.severity = feature.severity;
    issue.category = "FORBIDDEN_FEATURE_" + feature.featureName;
    issue.message = feature.description;
    issue.messageJa = feature.descriptionJa;
    issue.fileName = fileName;
    issue.lineNumber = lineNumber;
    
    // Create suggestions based on the feature type
    if (feature.featureName == "auto") {
        issue.suggestion = "Replace 'auto' with explicit type declaration";
        issue.suggestionJa = "'auto'を明示的な型宣言に置き換えてください";
    } else if (feature.featureName == "nullptr") {
        issue.suggestion = "Replace 'nullptr' with 'NULL'";
        issue.suggestionJa = "'nullptr'を'NULL'に置き換えてください";
    } else if (feature.featureName == "using_namespace") {
        issue.suggestion = "Remove 'using namespace' and use fully qualified names";
        issue.suggestionJa = "'using namespace'を削除し、完全修飾名を使用してください";
    } else if (feature.featureName == "friend") {
        issue.suggestion = "Remove 'friend' keyword and redesign class interface";
        issue.suggestionJa = "'friend'キーワードを削除し、クラスインターフェースを再設計してください";
    } else if (feature.featureName.find("std_") == 0) {
        issue.suggestion = "Implement your own data structure instead of using STL containers";
        issue.suggestionJa = "STLコンテナの代わりに独自のデータ構造を実装してください";
    } else {
        issue.suggestion = "Use C++98 compatible alternatives";
        issue.suggestionJa = "C++98互換の代替手段を使用してください";
    }
    
    // Add learning resources
    issue.learningResources.push_back("https://www.cplusplus.com/doc/tutorial/");
    issue.learningResources.push_back("https://isocpp.org/std/the-standard");
    
    return issue;
}

bool ForbiddenFeatureDetector::isCommentedOut(const std::string& line, bool& inBlockComment) {
    // If we're already in a block comment, check if it ends on this line
    if (inBlockComment) {
        size_t blockEnd = line.find("*/");
        if (blockEnd != std::string::npos) {
            inBlockComment = false;
            // Check if there's meaningful content after the block comment end
            std::string remaining = line.substr(blockEnd + 2);
            size_t nonWhitespace = remaining.find_first_not_of(" \t");
            if (nonWhitespace != std::string::npos) {
                // There's content after the comment, check if it's commented too
                bool tempBlockComment = false;
                return isCommentedOut(remaining, tempBlockComment);
            }
        }
        return true; // Still in block comment or nothing after comment end
    }
    
    // Remove leading whitespace
    size_t start = line.find_first_not_of(" \t");
    if (start == std::string::npos) {
        return false; // Empty line
    }
    
    std::string trimmed = line.substr(start);
    
    // Check for line comments first
    if (trimmed.length() >= 2 && trimmed.substr(0, 2) == "//") {
        return true;
    }
    
    // Handle block comments
    size_t blockStart = trimmed.find("/*");
    if (blockStart != std::string::npos) {
        // Check if there's meaningful content before the block comment
        std::string before = trimmed.substr(0, blockStart);
        size_t beforeNonWhitespace = before.find_first_not_of(" \t");
        
        size_t blockEnd = trimmed.find("*/", blockStart + 2);
        if (blockEnd != std::string::npos) {
            // Complete block comment on same line
            std::string after = trimmed.substr(blockEnd + 2);
            size_t afterNonWhitespace = after.find_first_not_of(" \t");
            
            // If there's content before or after, it's not fully commented
            if (beforeNonWhitespace != std::string::npos || afterNonWhitespace != std::string::npos) {
                return false;
            }
            return true; // Only block comment on this line
        } else {
            // Block comment starts but doesn't end on this line
            inBlockComment = true;
            // If there's content before the comment, it's not fully commented
            return beforeNonWhitespace == std::string::npos;
        }
    }
    
    return false; // No comments found
}

std::string ForbiddenFeatureDetector::removeStringLiterals(const std::string& line) {
    std::string result = line;
    bool inString = false;
    bool escaped = false;
    
    for (size_t i = 0; i < result.length(); ++i) {
        if (escaped) {
            escaped = false;
            continue;
        }
        
        if (result[i] == '\\' && inString) {
            escaped = true;
            continue;
        }
        
        if (result[i] == '"') {
            if (inString) {
                inString = false;
                result[i] = ' '; // Replace with space
            } else {
                inString = true;
                result[i] = ' '; // Replace with space
            }
        } else if (inString) {
            result[i] = ' '; // Replace string content with spaces
        }
    }
    
    return result;
}