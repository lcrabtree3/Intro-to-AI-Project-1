# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
INCLUDES = -Iinclude

# Directories
SRC_DIR = src
TEST_DIR = tests
INCLUDE_DIR = include

# Test files - only GameState.cpp, no Board.cpp needed now
TEST_GAMESTATE_SRCS = $(TEST_DIR)/test_gamestate.cpp $(SRC_DIR)/GameState.cpp

# Executable
TEST_GAMESTATE_EXEC = test_gamestate

# Default target
all: $(TEST_GAMESTATE_EXEC)

# Test executable
$(TEST_GAMESTATE_EXEC): $(TEST_GAMESTATE_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

# Run the test
test: $(TEST_GAMESTATE_EXEC)
	./$(TEST_GAMESTATE_EXEC)

# Clean
clean:
	rm -f $(TEST_GAMESTATE_EXEC)

# Phony targets
.PHONY: all test clean