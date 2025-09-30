#include "MutantStack.hpp"
#include <list>
#include <vector>
#include <string>

int main(void) {
    std::cout << "=== CPP08 ex02: MutantStack (Iterable Stack) ===" << std::endl;
    
    // Test 1: Basic functionality (from subject)
    std::cout << "\n--- Test 1: Basic functionality (from subject) ---" << std::endl;
    {
        MutantStack<int> mstack;
        
        mstack.push(5);
        mstack.push(17);
        
        std::cout << "Top element: " << mstack.top() << std::endl;
        
        mstack.pop();
        
        std::cout << "Size after pop: " << mstack.size() << std::endl;
        
        mstack.push(3);
        mstack.push(5);
        mstack.push(737);
        mstack.push(0);
        
        std::cout << "Final stack contents:" << std::endl;
        mstack.display();
        
        MutantStack<int>::iterator it = mstack.begin();
        MutantStack<int>::iterator ite = mstack.end();
        
        ++it;
        --it;
        
        std::cout << "Iterating through MutantStack:" << std::endl;
        while (it != ite) {
            std::cout << *it << " ";
            ++it;
        }
        std::cout << std::endl;
    }
    
    // Test 2: Comparison with std::list (same operations)
    std::cout << "\n--- Test 2: Comparison with std::list ---" << std::endl;
    {
        std::cout << "std::list with same operations:" << std::endl;
        std::list<int> lst;
        
        lst.push_back(5);
        lst.push_back(17);
        
        std::cout << "Back element: " << lst.back() << std::endl;
        
        lst.pop_back();
        
        std::cout << "Size after pop: " << lst.size() << std::endl;
        
        lst.push_back(3);
        lst.push_back(5);
        lst.push_back(737);
        lst.push_back(0);
        
        std::cout << "List contents: ";
        for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    
    // Test 3: Copy constructor and assignment
    std::cout << "\n--- Test 3: Copy constructor and assignment ---" << std::endl;
    {
        MutantStack<int> original;
        original.push(1);
        original.push(2);
        original.push(3);
        
        std::cout << "Original stack: ";
        original.display();
        
        // Copy constructor
        MutantStack<int> copied(original);
        std::cout << "Copied stack: ";
        copied.display();
        
        // Assignment operator
        MutantStack<int> assigned;
        assigned = original;
        std::cout << "Assigned stack: ";
        assigned.display();
        
        // Test independence
        original.push(999);
        std::cout << "After pushing 999 to original:" << std::endl;
        std::cout << "Original: ";
        original.display();
        std::cout << "Copied: ";
        copied.display();
        std::cout << "Assigned: ";
        assigned.display();
    }
    
    // Test 4: String MutantStack
    std::cout << "\n--- Test 4: String MutantStack ---" << std::endl;
    {
        MutantStack<std::string> stringStack;
        
        stringStack.push("First");
        stringStack.push("Second");
        stringStack.push("Third");
        stringStack.push("Fourth");
        
        std::cout << "String stack: ";
        stringStack.display();
        
        std::cout << "Iterating through string stack:" << std::endl;
        for (MutantStack<std::string>::iterator it = stringStack.begin(); 
             it != stringStack.end(); ++it) {
            std::cout << "\"" << *it << "\" ";
        }
        std::cout << std::endl;
    }
    
    // Test 5: Reverse iteration
    std::cout << "\n--- Test 5: Reverse iteration ---" << std::endl;
    {
        MutantStack<int> reverseStack;
        for (int i = 1; i <= 5; i++) {
            reverseStack.push(i * 10);
        }
        
        std::cout << "Stack (bottom to top): ";
        reverseStack.display();
        
        std::cout << "Stack (top to bottom): ";
        reverseStack.displayReverse();
        
        std::cout << "Manual reverse iteration: ";
        for (MutantStack<int>::reverse_iterator rit = reverseStack.rbegin(); 
             rit != reverseStack.rend(); ++rit) {
            std::cout << *rit << " ";
        }
        std::cout << std::endl;
    }
    
    // Test 6: Const iterators
    std::cout << "\n--- Test 6: Const iterators ---" << std::endl;
    {
        MutantStack<int> normalStack;
        normalStack.push(100);
        normalStack.push(200);
        normalStack.push(300);
        
        const MutantStack<int> constStack(normalStack);
        
        std::cout << "Const stack iteration: ";
        for (MutantStack<int>::const_iterator cit = constStack.begin(); 
             cit != constStack.end(); ++cit) {
            std::cout << *cit << " ";
        }
        std::cout << std::endl;
        
        std::cout << "Const reverse iteration: ";
        for (MutantStack<int>::const_reverse_iterator crit = constStack.rbegin(); 
             crit != constStack.rend(); ++crit) {
            std::cout << *crit << " ";
        }
        std::cout << std::endl;
    }
    
    // Test 7: Different underlying container (vector)
    std::cout << "\n--- Test 7: Different underlying container (vector) ---" << std::endl;
    {
        MutantStack<int, std::vector<int> > vectorStack;
        
        vectorStack.push(11);
        vectorStack.push(22);
        vectorStack.push(33);
        vectorStack.push(44);
        
        std::cout << "MutantStack with vector container: ";
        vectorStack.display();
        
        std::cout << "Vector-based stack iteration: ";
        for (MutantStack<int, std::vector<int> >::iterator it = vectorStack.begin(); 
             it != vectorStack.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    
    // Test 8: Empty stack iteration
    std::cout << "\n--- Test 8: Empty stack iteration ---" << std::endl;
    {
        MutantStack<int> emptyStack;
        
        std::cout << "Empty stack size: " << emptyStack.size() << std::endl;
        std::cout << "Empty stack is empty: " << (emptyStack.empty() ? "true" : "false") << std::endl;
        
        std::cout << "Iterating empty stack: ";
        for (MutantStack<int>::iterator it = emptyStack.begin(); 
             it != emptyStack.end(); ++it) {
            std::cout << *it << " ";  // Should not execute
        }
        std::cout << "(no elements)" << std::endl;
    }
    
    // Test 9: Large stack
    std::cout << "\n--- Test 9: Large stack ---" << std::endl;
    {
        MutantStack<int> largeStack;
        
        // Push many elements
        for (int i = 0; i < 100; i++) {
            largeStack.push(i);
        }
        
        std::cout << "Large stack size: " << largeStack.size() << std::endl;
        std::cout << "Top element: " << largeStack.top() << std::endl;
        
        // Sample some elements using iteration
        std::cout << "Every 10th element: ";
        int count = 0;
        for (MutantStack<int>::iterator it = largeStack.begin(); 
             it != largeStack.end(); ++it, ++count) {
            if (count % 10 == 0) {
                std::cout << *it << " ";
            }
        }
        std::cout << std::endl;
    }
    
    // Test 10: Stack operations with iteration
    std::cout << "\n--- Test 10: Stack operations with iteration ---" << std::endl;
    {
        MutantStack<int> operationStack;
        
        // Push some elements
        for (int i = 1; i <= 5; i++) {
            operationStack.push(i);
            std::cout << "After pushing " << i << ": ";
            operationStack.display();
        }
        
        // Pop some elements
        while (!operationStack.empty() && operationStack.size() > 2) {
            std::cout << "Popping " << operationStack.top() << std::endl;
            operationStack.pop();
            std::cout << "After pop: ";
            operationStack.display();
        }
        
        std::cout << "Final iteration: ";
        for (MutantStack<int>::iterator it = operationStack.begin(); 
             it != operationStack.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << "\n=== End of tests ===" << std::endl;
    
    return 0;
}




