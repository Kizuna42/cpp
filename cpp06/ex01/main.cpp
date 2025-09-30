#include "Serializer.hpp"

int main(void) {
    std::cout << "=== CPP06 ex01: Serialization and Deserialization ===" << std::endl;
    
    // Test 1: Basic serialization and deserialization
    std::cout << "\n--- Test 1: Basic serialization/deserialization ---" << std::endl;
    
    Data originalData(42, "Hello, World!", 3.14159, true);
    std::cout << "Original data:" << std::endl;
    originalData.display();
    
    // Serialize the data
    uintptr_t serialized = Serializer::serialize(&originalData);
    std::cout << "\nSerialized value: " << serialized << " (hex: 0x" << std::hex << serialized << std::dec << ")" << std::endl;
    
    // Deserialize the data
    Data* deserializedPtr = Serializer::deserialize(serialized);
    std::cout << "\nDeserialized data:" << std::endl;
    deserializedPtr->display();
    
    // Verify pointer equality
    std::cout << "\nPointer comparison:" << std::endl;
    std::cout << "Original pointer:    " << &originalData << std::endl;
    std::cout << "Deserialized pointer: " << deserializedPtr << std::endl;
    std::cout << "Pointers equal: " << (&originalData == deserializedPtr ? "YES" : "NO") << std::endl;
    
    // Verify data equality
    std::cout << "Data content equal: " << (originalData == *deserializedPtr ? "YES" : "NO") << std::endl;
    
    // Test 2: Multiple objects
    std::cout << "\n--- Test 2: Multiple objects ---" << std::endl;
    
    Data data1(100, "First object", 1.23, true);
    Data data2(200, "Second object", 4.56, false);
    Data data3(300, "Third object", 7.89, true);
    
    Data* objects[] = {&data1, &data2, &data3};
    uintptr_t serializedValues[3];
    
    // Serialize all objects
    for (int i = 0; i < 3; i++) {
        serializedValues[i] = Serializer::serialize(objects[i]);
        std::cout << "Object " << i + 1 << " serialized to: " << serializedValues[i] << std::endl;
    }
    
    std::cout << "\nDeserializing and verifying..." << std::endl;
    
    // Deserialize and verify all objects
    for (int i = 0; i < 3; i++) {
        Data* deserializedPtr = Serializer::deserialize(serializedValues[i]);
        std::cout << "\nObject " << i + 1 << ":" << std::endl;
        std::cout << "Original pointer:     " << objects[i] << std::endl;
        std::cout << "Deserialized pointer: " << deserializedPtr << std::endl;
        std::cout << "Pointers match: " << (objects[i] == deserializedPtr ? "YES" : "NO") << std::endl;
        std::cout << "Data matches: " << (*objects[i] == *deserializedPtr ? "YES" : "NO") << std::endl;
    }
    
    // Test 3: Modifying data through deserialized pointer
    std::cout << "\n--- Test 3: Modifying through deserialized pointer ---" << std::endl;
    
    Data testData(999, "Original message", 99.99, false);
    std::cout << "Before modification:" << std::endl;
    testData.display();
    
    uintptr_t testSerialized = Serializer::serialize(&testData);
    Data* testPtr = Serializer::deserialize(testSerialized);
    
    // Modify through deserialized pointer
    testPtr->value = 123;
    testPtr->message = "Modified message";
    testPtr->price = 12.34;
    testPtr->isValid = true;
    
    std::cout << "\nAfter modification through deserialized pointer:" << std::endl;
    testData.display();  // Original object should be modified
    
    // Test 4: NULL pointer handling
    std::cout << "\n--- Test 4: NULL pointer handling ---" << std::endl;
    
    Data* nullPtr = NULL;
    uintptr_t serializedNull = Serializer::serialize(nullPtr);
    Data* deserializedNull = Serializer::deserialize(serializedNull);
    
    std::cout << "NULL pointer serialized to: " << serializedNull << std::endl;
    std::cout << "Deserialized NULL pointer: " << deserializedNull << std::endl;
    std::cout << "NULL pointers match: " << (nullPtr == deserializedNull ? "YES" : "NO") << std::endl;
    
    // Test 5: Stack vs Heap objects
    std::cout << "\n--- Test 5: Stack vs Heap objects ---" << std::endl;
    
    // Stack object
    Data stackData(555, "Stack object", 55.55, true);
    uintptr_t stackSerialized = Serializer::serialize(&stackData);
    Data* stackDeserialized = Serializer::deserialize(stackSerialized);
    
    std::cout << "Stack object:" << std::endl;
    std::cout << "Original:     " << &stackData << std::endl;
    std::cout << "Deserialized: " << stackDeserialized << std::endl;
    std::cout << "Match: " << (&stackData == stackDeserialized ? "YES" : "NO") << std::endl;
    
    // Heap object
    Data* heapData = new Data(777, "Heap object", 77.77, false);
    uintptr_t heapSerialized = Serializer::serialize(heapData);
    Data* heapDeserialized = Serializer::deserialize(heapSerialized);
    
    std::cout << "\nHeap object:" << std::endl;
    std::cout << "Original:     " << heapData << std::endl;
    std::cout << "Deserialized: " << heapDeserialized << std::endl;
    std::cout << "Match: " << (heapData == heapDeserialized ? "YES" : "NO") << std::endl;
    
    // Clean up heap memory
    delete heapData;
    
    std::cout << "\n=== End of tests ===" << std::endl;
    
    return 0;
}




