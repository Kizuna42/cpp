NAME = RPN

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = .
OBJDIR = obj

SOURCES = main.cpp RPN.cpp
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
	@echo "$(GREEN)Running RPN calculator tests...$(NC)"
	@echo "Test 1: Basic calculation"
	@./$(NAME) "8 9 * 9 - 9 - 9 - 4 - 1 +"
	@echo "\nTest 2: Simple arithmetic"
	@./$(NAME) "7 7 * 7 -"
	@echo "\nTest 3: Multiple operations"
	@./$(NAME) "1 2 * 2 / 2 * 2 4 - +"
	@echo "\nTest 4: Error case - division by zero"
	@./$(NAME) "1 0 /" || true
	@echo "\nTest 5: Error case - insufficient operands"
	@./$(NAME) "1 +" || true

.PHONY: all clean fclean re test




