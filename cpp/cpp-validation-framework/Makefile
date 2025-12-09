# C++98 Validation Framework Makefile

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = cpp_validator

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
TESTDIR = tests

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Header files
HEADERS = $(wildcard $(INCDIR)/*.hpp)

# Test files
TEST_SOURCES = $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJECTS = $(TEST_SOURCES:$(TESTDIR)/%.cpp=$(OBJDIR)/test_%.o)
TEST_NAME = test_runner

.PHONY: all clean fclean re test

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/test_%.o: $(TESTDIR)/%.cpp $(HEADERS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

test: $(TEST_NAME)

$(TEST_NAME): $(filter-out $(OBJDIR)/main.o, $(OBJECTS)) $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all

# Development targets
debug: CXXFLAGS += -g -DDEBUG
debug: $(NAME)

release: CXXFLAGS += -O2 -DNDEBUG
release: $(NAME)