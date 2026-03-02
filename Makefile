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
GAME_STATE_SRCS = $(SRC_DIR)/GameState.cpp $(SRC_DIR)/Board.cpp

# Test files
TEST_BOARD_SRCS = $(TEST_DIR)/test_board.cpp $(SRC_DIR)/Board.cpp
TEST_GAMESTATE_SRCS = $(TEST_DIR)/test_gamestate.cpp $(SRC_DIR)/GameState.cpp $(SRC_DIR)/Board.cpp

# Executables
TEST_BOARD_EXEC = test_board
TEST_GAMESTATE_EXEC = test_gamestate

# Default target
all: $(TEST_BOARD_EXEC) $(TEST_GAMESTATE_EXEC)

# Test executables
$(TEST_BOARD_EXEC): $(TEST_BOARD_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(TEST_BOARD_SRCS)

$(TEST_GAMESTATE_EXEC): $(TEST_GAMESTATE_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(TEST_GAMESTATE_SRCS)

# Run the tests
test: test-board test-gamestate

test-board: $(TEST_BOARD_EXEC)
	./$(TEST_BOARD_EXEC)

test-gamestate: $(TEST_GAMESTATE_EXEC)
	./$(TEST_GAMESTATE_EXEC)

# Clean
clean:
	rm -f $(TEST_BOARD_EXEC) $(TEST_GAMESTATE_EXEC)

# Phony targets
.PHONY: all test test-board test-gamestate clean