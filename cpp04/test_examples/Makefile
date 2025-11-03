CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# Colors
GREEN = \033[0;32m
BLUE = \033[0;34m
RED = \033[0;31m
NC = \033[0m

all:
	@echo "$(BLUE)Available tests:$(NC)"
	@echo "  $(GREEN)make test_constructor$(NC)  - Test constructor/destructor order (Ex00)"
	@echo "  $(GREEN)make test_scope$(NC)        - Test deep copy with scope (Ex01)"
	@echo "  $(GREEN)make test_address$(NC)      - Test Brain address comparison (Ex01)"
	@echo "  $(GREEN)make test_destructor$(NC)   - Test virtual destructor (Ex01)"
	@echo "  $(GREEN)make test_assignment$(NC)   - Test self-assignment (Ex03)"
	@echo "  $(GREEN)make run_all$(NC)           - Run all tests"

test_constructor: test_constructor_order.cpp
	@echo "$(BLUE)Compiling constructor order test...$(NC)"
	@$(CXX) $(CXXFLAGS) test_constructor_order.cpp \
		../ex00/Animal.cpp ../ex00/Dog.cpp -o test_constructor
	@echo "$(GREEN)Running test:$(NC)"
	@./test_constructor
	@rm -f test_constructor

test_scope: test_deep_copy_scope.cpp
	@echo "$(BLUE)Compiling scope test...$(NC)"
	@$(CXX) $(CXXFLAGS) test_deep_copy_scope.cpp \
		../ex01/Animal.cpp ../ex01/Dog.cpp ../ex01/Brain.cpp -o test_scope
	@echo "$(GREEN)Running test:$(NC)"
	@./test_scope
	@rm -f test_scope

test_address: test_brain_address.cpp
	@echo "$(BLUE)Compiling address comparison test...$(NC)"
	@$(CXX) $(CXXFLAGS) test_brain_address.cpp \
		../ex01/Animal.cpp ../ex01/Dog.cpp ../ex01/Cat.cpp ../ex01/Brain.cpp -o test_address
	@echo "$(GREEN)Running test:$(NC)"
	@./test_address
	@rm -f test_address

test_destructor: test_virtual_destructor.cpp
	@echo "$(BLUE)Compiling virtual destructor test...$(NC)"
	@$(CXX) $(CXXFLAGS) test_virtual_destructor.cpp \
		../ex01/Animal.cpp ../ex01/Dog.cpp ../ex01/Brain.cpp -o test_destructor
	@echo "$(GREEN)Running test:$(NC)"
	@./test_destructor
	@rm -f test_destructor

test_assignment: test_self_assignment.cpp
	@echo "$(BLUE)Compiling self-assignment test...$(NC)"
	@$(CXX) $(CXXFLAGS) test_self_assignment.cpp \
		../ex03/AMateria.cpp ../ex03/Ice.cpp ../ex03/Cure.cpp \
		../ex03/Character.cpp -o test_assignment
	@echo "$(GREEN)Running test:$(NC)"
	@./test_assignment
	@rm -f test_assignment

run_all: test_constructor test_scope test_address test_destructor test_assignment
	@echo "$(GREEN)All tests completed!$(NC)"

clean:
	@rm -f test_constructor test_scope test_address test_destructor test_assignment

.PHONY: all test_constructor test_scope test_address test_destructor test_assignment run_all clean

