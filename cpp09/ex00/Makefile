NAME = btc

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = .
OBJDIR = obj

SOURCES = main.cpp BitcoinExchange.cpp
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
	@echo "Running bitcoin exchange tests..."
	@echo "Test 1: No arguments"
	@./$(NAME) || true
	@echo "\nTest 2: Valid input file"
	@./$(NAME) input.txt || true
	@echo "\nTest 3: Non-existent file"
	@./$(NAME) nonexistent.txt || true

.PHONY: all clean fclean re test




