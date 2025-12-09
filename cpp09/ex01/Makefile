NAME = RPN

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = .
OBJDIR = obj

SOURCES = main.cpp RPN.cpp
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

test: $(NAME)
	@echo "Running RPN calculator tests..."
	@echo "Test 1: Subject example 1"
	@./$(NAME) "8 9 * 9 - 9 - 9 - 4 - 1 +"
	@echo "\nTest 2: Subject example 2"
	@./$(NAME) "7 7 * 7 -"
	@echo "\nTest 3: Subject example 3"
	@./$(NAME) "1 2 * 2 / 2 * 2 4 - +"
	@echo "\nTest 4: Error case - brackets (should fail)"
	@./$(NAME) "(1 + 1)" || true
	@echo "\nTest 5: Error case - division by zero"
	@./$(NAME) "1 0 /" || true
	@echo "\nTest 6: Error case - insufficient operands"
	@./$(NAME) "1 +" || true
	@echo "\nTest 7: Error case - number >= 10"
	@./$(NAME) "10 2 +" || true
	@echo "\nTest 8: Error case - empty expression"
	@./$(NAME) "" || true
	@echo "\nTest 9: Error case - no arguments"
	@./$(NAME) || true
	@echo "\nTest 10: Complex expression"
	@./$(NAME) "9 8 * 7 + 6 - 5 * 4 / 3 + 2 - 1 +"

.PHONY: all clean fclean re test




