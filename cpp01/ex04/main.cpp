#include <string>
#include <iostream>
#include <fstream>

std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
    if (from.empty()) return str;
    
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
        return 1;
    }
    
    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];
    
    if (s1.empty()) {
        std::cout << "Error: s1 cannot be empty" << std::endl;
        return 1;
    }
    
    std::ifstream inputFile(filename.c_str());
    if (!inputFile.is_open()) {
        std::cout << "Error: Could not open file " << filename << std::endl;
        return 1;
    }
    
    std::string content;
    std::string line;
    while (std::getline(inputFile, line)) {
        content += line;
        if (!inputFile.eof()) {
            content += "\n";
        }
    }
    inputFile.close();
    
    std::string result = replaceAll(content, s1, s2);
    
    std::string outputFilename = filename + ".replace";
    std::ofstream outputFile(outputFilename.c_str());
    if (!outputFile.is_open()) {
        std::cout << "Error: Could not create output file " << outputFilename << std::endl;
        return 1;
    }
    
    outputFile << result;
    outputFile.close();
    
    std::cout << "File processed successfully. Output: " << outputFilename << std::endl;
    return 0;
}