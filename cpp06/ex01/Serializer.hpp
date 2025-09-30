#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <iostream>
#include <stdint.h>

struct Data {
    int value;
    std::string message;
    double price;
    bool isValid;
    
    // Constructor for easy initialization
    Data(int v = 0, const std::string& msg = "", double p = 0.0, bool valid = false);
    
    // Display function for testing
    void display(void) const;
    
    // Comparison operator for testing
    bool operator==(const Data& other) const;
};

class Serializer {
private:
    // Private constructor to prevent instantiation
    Serializer(void);
    Serializer(const Serializer& other);
    Serializer& operator=(const Serializer& other);
    ~Serializer(void);

public:
    // Serialization functions
    static uintptr_t serialize(Data* ptr);
    static Data* deserialize(uintptr_t raw);
};

#endif




