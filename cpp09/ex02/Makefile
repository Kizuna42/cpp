NAME = PmergeMe

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = .
OBJDIR = obj

SOURCES = main.cpp PmergeMe.cpp
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
	@echo "Running PmergeMe tests..."
	@echo "Test 1: Subject example"
	@./$(NAME) 3 5 9 7 4
	@echo "\nTest 2: Already sorted"
	@./$(NAME) 1 2 3 4 5
	@echo "\nTest 3: Reverse sorted"
	@./$(NAME) 5 4 3 2 1
	@echo "\nTest 4: Single element"
	@./$(NAME) 42
	@echo "\nTest 5: Duplicate values"
	@./$(NAME) 5 3 5 1 3 2 5
	@echo "\nTest 6: Error case - no arguments"
	@./$(NAME) || true
	@echo "\nTest 7: Error case - negative number"
	@./$(NAME) 1 2 -3 4 || true
	@echo "\nTest 8: Error case - invalid input"
	@./$(NAME) 1 2 abc 4 || true

test-large: $(NAME)
	@echo "Running large dataset test (3000 elements)..."
	@seq 1 3000 | shuf | head -3000 | tr '\n' ' ' | xargs ./$(NAME)

.PHONY: all clean fclean re test test-large




