NAME = convert

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = .
OBJDIR = obj

SOURCES = main.cpp ScalarConverter.cpp
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
	@echo "$(GREEN)Running scalar conversion tests...$(NC)"
	@echo "Testing character: 'a'"
	@./$(NAME) "'a'"
	@echo "\nTesting integer: 42"
	@./$(NAME) "42"
	@echo "\nTesting float: 42.42f"
	@./$(NAME) "42.42f"
	@echo "\nTesting double: 42.42"
	@./$(NAME) "42.42"
	@echo "\nTesting special: nan"
	@./$(NAME) "nan"
	@echo "\nTesting special: +inff"
	@./$(NAME) "+inff"

.PHONY: all clean fclean re test




