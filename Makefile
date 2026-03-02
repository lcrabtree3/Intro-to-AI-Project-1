# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
INCLUDES = -Iinclude

# Directories
SRC_DIR = src
TEST_DIR = tests
INCLUDE_DIR = include

# Source files
BOARD_SRCS = $(SRC_DIR)/Board.cpp

# Test files
TEST_BOARD_SRCS = $(TEST_DIR)/test_board.cpp $(SRC_DIR)/Board.cpp

# Executables
TEST_BOARD_EXEC = test_board

# Default target
all: $(TEST_BOARD_EXEC)

# Run the test
test: test-board

test_board: $(TEST_BOARD_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TEST_BOARD_EXEC) $(TEST_BOARD_SRCS)

test-board: $(TEST_BOARD_EXEC)
	./$(TEST_BOARD_EXEC)

# Clean
clean:
	rm -f $(TEST_BOARD_EXEC)

# Phony targets
.PHONY: all test test-board clean
