NAME = PmergeMe

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = .
OBJDIR = obj

SOURCES = main.cpp PmergeMe.cpp
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
	@echo "$(GREEN)Running PmergeMe tests...$(NC)"
	@echo "Test 1: Small dataset"
	@./$(NAME) 3 5 9 7 4
	@echo "\nTest 2: Already sorted"
	@./$(NAME) 1 2 3 4 5
	@echo "\nTest 3: Reverse sorted"
	@./$(NAME) 5 4 3 2 1
	@echo "\nTest 4: Single element"
	@./$(NAME) 42
	@echo "\nTest 5: Random larger dataset"
	@./$(NAME) 74 59 238 -784 9845 893 543 2 0 78 9 87 54 23 456 789 123 654 987 321

test-large: $(NAME)
	@echo "$(GREEN)Running large dataset test...$(NC)"
	@echo "Generating 1000 random numbers..."
	@seq 1 1000 | shuf | head -1000 | xargs ./$(NAME)

.PHONY: all clean fclean re test test-large




