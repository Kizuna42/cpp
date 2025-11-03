NAME = abstract

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = .
OBJDIR = obj

SOURCES = main.cpp AAnimal.cpp Dog.cpp Cat.cpp Brain.cpp
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m # No Color

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "$(GREEN)Linking $(NAME)...$(NC)"
	@$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(NC)"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@echo "$(GREEN)Compiling $<...$(NC)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(NC)"
	@rm -f $(NAME)

re: fclean all

test: $(NAME)
	@echo "$(GREEN)Running Abstract Animal tests...$(NC)"
	@./$(NAME)

# Test to verify abstract class cannot be instantiated
test-compilation-error:
	@echo "$(RED)Testing compilation error (this should fail):$(NC)"
	@echo '#include "AAnimal.hpp"\nint main() { AAnimal test; return 0; }' > test_abstract.cpp
	@$(CXX) $(CXXFLAGS) test_abstract.cpp -c -o test_abstract.o 2>&1 || echo "$(GREEN)Good! Abstract class cannot be instantiated.$(NC)"
	@rm -f test_abstract.cpp test_abstract.o

.PHONY: all clean fclean re test test-compilation-error