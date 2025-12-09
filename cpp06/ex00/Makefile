NAME = convert

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = .
OBJDIR = obj

SOURCES = main.cpp ScalarConverter.cpp
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
	@echo "Running scalar conversion tests..."
	@echo "Testing character: 'a'"
	@./$(NAME) "'a'"
	@echo "\nTesting integer: 42"
	@./$(NAME) "42"
	@echo "\nTesting int boundary: INT_MIN"
	@./$(NAME) "-2147483648"
	@echo "\nTesting int boundary: INT_MAX"
	@./$(NAME) "2147483647"
	@echo "\nTesting non-displayable char via int 31"
	@./$(NAME) "31"
	@echo "\nTesting float: 42.42f"
	@./$(NAME) "42.42f"
	@echo "\nTesting double: 42.42"
	@./$(NAME) "42.42"
	@echo "\nTesting special: nan"
	@./$(NAME) "nan"
	@echo "\nTesting special: +inff"
	@./$(NAME) "+inff"
	@echo "\nTesting overflow int -> invalid literal"
	@./$(NAME) "999999999999999999999"
	@echo "\nTesting invalid format"
	@./$(NAME) "abc123"

.PHONY: all clean fclean re test




