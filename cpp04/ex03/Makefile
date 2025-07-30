NAME = materia

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = .
OBJDIR = obj

SOURCES = main.cpp AMateria.cpp Ice.cpp Cure.cpp Character.cpp MateriaSource.cpp
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
	@echo "$(GREEN)Running Materia system tests...$(NC)"
	@./$(NAME)

.PHONY: all clean fclean re test