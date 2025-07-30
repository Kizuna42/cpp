# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a 42 School C++ curriculum project implementing C++ modules 00-04. The codebase follows strict C++98 standards and educational constraints designed to teach object-oriented programming fundamentals to beginners.

**Repository Structure**: Single Git repository with module-based branch strategy
**Target Audience**: C++ beginners learning OOP fundamentals
**Quality Priority**: Technical precision and code accuracy over explanatory verbosity

## Build System

Each exercise uses a standard Makefile with consistent structure:

```bash
# Navigate to specific exercise (e.g., cpp00/ex00, cpp01/ex00)
cd cpp01/ex00/

# Build the project
make

# Clean build artifacts
make clean    # Remove .o files
make fclean   # Remove all generated files
make re       # Clean rebuild
```

**Standard compiler flags**: `-Wall -Wextra -Werror -std=c++98`

## Development Environment

### macOS Development
- Primary development environment
- No valgrind support (use alternative tools listed below)
- All code must compile and run correctly on macOS

### Ubuntu Testing Environment
- Used for valgrind memory leak detection
- Access via GitHub Actions or virtual environment
- Final validation environment before submission

### Recommended Development Tools

**Static Analysis (macOS compatible):**
- `cppcheck`: Static analysis for C/C++
- `clang-static-analyzer`: Clang's built-in static analyzer
- `pc-lint-plus`: Professional static analysis (if available)

**Memory Debugging (Ubuntu):**
- `valgrind --tool=memcheck`: Memory leak detection
- `valgrind --tool=helgrind`: Thread error detection
- `AddressSanitizer`: Compile with `-fsanitize=address`

**Code Quality:**
- `clang-format`: Code formatting consistency
- `iwyu` (include-what-you-use): Header dependency optimization

## Development Constraints

**Forbidden C++ features:**
- C++11+ features (auto, range-based for, lambda, etc.)
- STL containers (until Module 08)
- `using namespace` statements (grade penalty: -42)
- `printf()` - use `std::cout` instead
- Dynamic memory functions: `malloc()`, `free()`, `*alloc()`
- `friend` keyword (grade penalty: -42)

**Required practices:**
- Zero warnings compilation
- C++98 standard compliance only
- Orthodox Canonical Form for classes (from Module 02)
- RAII principles adherence
- No memory leaks
- Include guards in all headers
- Independent header compilation

## Git Workflow Strategy

### Branch Structure
```
main
├── feature/cpp01-implementation
├── feature/cpp02-implementation
├── feature/cpp03-implementation
├── feature/cpp04-implementation
└── docs/enhance-cpp00-documentation
```

### Parallel Implementation Workflow

**Phase 1: Parallel Development**
1. Create feature branches for each module simultaneously
2. Implement all modules in parallel for efficiency
3. Focus on core functionality first, optimization later

**Phase 2: Consolidated Testing**
1. Merge completed modules to testing branch
2. Run comprehensive test suite across all modules
3. Memory leak testing via GitHub Actions (Ubuntu environment)

**Phase 3: Documentation & Review**
1. Create detailed learning documentation for all modules
2. Comprehensive code review with detailed feedback
3. Merge to main after all quality gates pass

## Architecture

### Module Progression
- `cpp00/`: Namespaces, classes, member functions, stdio streams
  - `ex00/`: String manipulation and command-line arguments
  - `ex01/`: Class design with PhoneBook and Contact
  - `ex02/`: Static member management with Account class

- `cpp01/`: Memory allocation, pointers to members, references, switch
- `cpp02/`: Ad-hoc polymorphism, operator overloading, Orthodox Canonical Form
- `cpp03/`: Inheritance concepts and virtual functions
- `cpp04/`: Subtype polymorphism, abstract classes, interfaces

### Class Design Patterns
- **Encapsulation**: Private data with controlled public access
- **RAII**: Resource Acquisition Is Initialization
- **Orthodox Canonical Form**: Default constructor, copy constructor, assignment operator, destructor
- **Static member management**: Class-level state and operations
- **Progressive complexity**: From simple classes to inheritance hierarchies

## Testing Strategy

### Manual Testing (Primary)
- **Functional testing**: All requirements verification
- **Boundary testing**: Edge cases and limits
- **Error handling**: Invalid input and error conditions
- **Interactive testing**: CLI programs like PhoneBook
- **Cross-platform**: macOS development, Ubuntu validation

### Automated Validation (Ubuntu via GitHub)
```bash
# Memory leak detection
valgrind --leak-check=full --show-leak-kinds=all ./program

# Static analysis
cppcheck --enable=all --std=c++98 src/

# Compilation validation
g++ -Wall -Wextra -Werror -std=c++98 -fsanitize=address
```

## Documentation Standards

### Code Documentation Requirements


**Detailed Code Comments (for learning):**
```cpp
// Constructor: Initializes PhoneBook with empty contact array
// Parameters: None
// Learning Point: Default constructor implementation in C++98
PhoneBook::PhoneBook() {
    // Initialize contact count to 0
    // C++98 Note: No member initializer lists for simple types
    this->_contactCount = 0;
    
    // Initialize oldest index for circular buffer behavior
    // Design Decision: Use circular buffer to replace oldest contact
    this->_oldestContactIndex = 0;
}
```

### Learning Documentation Structure

**Module Learning Report Template (`docs/cpp0X-learning-report.md`):**
```markdown
# C++ Module 0X Learning Report

## Learning Objectives
- [Specific C++ concepts introduced]
- [OOP principles demonstrated]
- [42 School curriculum goals]

## Technical Concepts Covered
### [Concept 1]
- **Definition**: [Clear explanation]
- **Implementation**: [Code examples with detailed comments]
- **Common Pitfalls**: [What beginners should avoid]
- **Best Practices**: [Recommended approaches]

## Implementation Challenges
### [Challenge 1]
- **Problem**: [Description of the challenge]
- **Solution**: [How it was resolved]
- **Learning**: [What was learned from this]

## Code Review Checklist
- [ ] [Specific review points for this module]
- [ ] [Technical requirements verification]
- [ ] [42 School compliance checks]

## Advanced Topics for Further Study
- [Related concepts to explore later]
- [Connections to future modules]
```

## Code Review Guidelines

### Self-Review Checklist

**Compilation & Basic Functionality:**
- [ ] Compiles with `-Wall -Wextra -Werror -std=c++98`
- [ ] No runtime errors or crashes
- [ ] All required functionality implemented
- [ ] Program produces expected output

**Memory Management:**
- [ ] No memory leaks (verified with valgrind on Ubuntu)
- [ ] No use of forbidden allocation functions
- [ ] Proper RAII implementation
- [ ] Stack-based memory management where possible

**C++98 Compliance:**
- [ ] No C++11+ features used
- [ ] No forbidden STL containers
- [ ] No `using namespace` statements
- [ ] No `friend` keyword usage

**Code Quality:**
- [ ] Clear, readable variable and function names
- [ ] Consistent coding style
- [ ] Appropriate comments for learning purposes
- [ ] Logical code organization

### Third-Party Review Focus Areas

**Architecture Review:**
- [ ] **Class Design**: Appropriate encapsulation and data hiding
- [ ] **Interface Design**: Clean public interfaces, minimal coupling
- [ ] **SOLID Principles**: Single responsibility, appropriate abstractions
- [ ] **Error Handling**: Robust error detection and reporting

**Implementation Review:**
- [ ] **Orthodox Canonical Form**: Proper implementation when required
- [ ] **Resource Management**: Correct constructor/destructor pairs
- [ ] **Exception Safety**: Basic exception safety guarantees
- [ ] **Performance**: Efficient algorithms and data structures

**Educational Value Review:**
- [ ] **Learning Progression**: Appropriate complexity for module level
- [ ] **Concept Demonstration**: Clear examples of required concepts
- [ ] **Code Comments**: Helpful explanations for beginners
- [ ] **Documentation Quality**: Complete and accurate learning materials

### Review Severity Levels

**Critical (Must Fix):**
- Compilation failures
- Memory leaks
- Forbidden feature usage
- Incorrect program behavior

**Major (Should Fix):**
- Poor error handling
- Inefficient implementations
- Missing Orthodox Canonical Form
- Inadequate documentation

**Minor (Consider Fixing):**
- Style inconsistencies
- Non-optimal but working solutions
- Missing advanced optimizations

## File Organization

```
cpp/
├── cpp00/                  # Module 00 (implemented)
│   ├── ex00/              # Exercise directories
│   ├── ex01/
│   ├── ex02/
│   └── docs/              # Enhanced documentation
├── cpp01/                  # Module 01 (to implement)
│   ├── ex00/
│   ├── ex01/
│   ├── docs/
│   └── cpp01.pdf
├── cpp02/                  # Module 02 (to implement)
├── cpp03/                  # Module 03 (to implement)
├── cpp04/                  # Module 04 (to implement)
├── .gitignore             # Build artifacts, IDE files
├── README.md              # Project overview
└── CLAUDE.md              # This file
```

**File Naming Conventions:**
- Classes: `ClassName.hpp`, `ClassName.cpp`
- Executables: Descriptive names (e.g., `phonebook`, `megaphone`)
- Documentation: Module-specific in `docs/` subdirectories

## Quality Assurance Commands

### Development Commands (macOS)
```bash
# Static analysis
cppcheck --enable=all --std=c++98 --suppress=missingIncludeSystem src/

# Compilation with additional checks
clang++ -Wall -Wextra -Werror -std=c++98 -Weverything -Wno-c++98-compat-pedantic

# Code formatting
clang-format -i -style="{BasedOnStyle: Google, IndentWidth: 4, TabWidth: 4}" *.cpp *.hpp
```

### Validation Commands (Ubuntu)
```bash
# Memory leak detection
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program

# Thread safety (if applicable)
valgrind --tool=helgrind ./program

# Address sanitizer compilation
g++ -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g -O1
```

## Success Criteria

**Technical Requirements:**
- Zero compilation warnings
- Zero memory leaks
- 100% functional requirement compliance
- C++98 standard adherence

**Educational Requirements:**
- Comprehensive learning documentation
- Detailed code comments for beginners
- Progressive skill demonstration
- Clear concept explanation

**Process Requirements:**
- Proper Git workflow adherence
- Thorough self and peer review
- Complete testing on both platforms
- Professional documentation standards