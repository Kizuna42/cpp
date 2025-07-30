#include "Harl.hpp"

int main(void) {
    Harl harl;
    
    std::cout << "\n=== Harl Complaint Testing ===" << std::endl;
    
    harl.complain("DEBUG");
    harl.complain("INFO");
    harl.complain("WARNING");
    harl.complain("ERROR");
    
    std::cout << "\n=== Testing invalid level ===" << std::endl;
    harl.complain("INVALID");
    harl.complain("");
    
    std::cout << "\n=== Multiple complaints ===" << std::endl;
    harl.complain("ERROR");
    harl.complain("DEBUG");
    harl.complain("WARNING");
    
    return 0;
}