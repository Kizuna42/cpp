#include "Zombie.hpp"

int main(void) {
    std::cout << "=== Testing heap allocation (newZombie) ===" << std::endl;
    Zombie* heapZombie = newZombie("HeapWalker");
    heapZombie->announce();
    delete heapZombie;
    
    std::cout << "\n=== Testing stack allocation (randomChump) ===" << std::endl;
    randomChump("StackShambler");
    
    std::cout << "\n=== Additional stack vs heap demonstration ===" << std::endl;
    std::cout << "Creating stack zombie..." << std::endl;
    {
        Zombie stackZombie("LocalUndead");
        stackZombie.announce();
    }
    std::cout << "Stack zombie automatically destroyed when leaving scope\n" << std::endl;
    
    std::cout << "Creating heap zombie..." << std::endl;
    Zombie* anotherHeapZombie = newZombie("PersistentGhoul");
    anotherHeapZombie->announce();
    std::cout << "Heap zombie must be manually deleted..." << std::endl;
    delete anotherHeapZombie;
    
    return 0;
}