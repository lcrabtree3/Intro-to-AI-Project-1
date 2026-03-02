# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g -pthread
INCLUDES = -Iinclude

# Directories
SRC_DIR = src
TEST_DIR = tests

# Common source files (excluding main)
COMMON_SRCS = $(SRC_DIR)/Board.cpp $(SRC_DIR)/GameState.cpp $(SRC_DIR)/HumanPlayer.cpp \
              $(SRC_DIR)/AIPlayer.cpp $(SRC_DIR)/Controller.cpp $(SRC_DIR)/Game.cpp

# Main executable
MAIN_SRCS = $(COMMON_SRCS) $(SRC_DIR)/main.cpp
MAIN_EXEC = connectM

# Test executables
TEST_BOARD_SRCS = $(TEST_DIR)/test_board.cpp $(SRC_DIR)/Board.cpp
TEST_BOARD_EXEC = test_board

TEST_GAMESTATE_SRCS = $(TEST_DIR)/test_gamestate.cpp $(SRC_DIR)/GameState.cpp $(SRC_DIR)/Board.cpp
TEST_GAMESTATE_EXEC = test_gamestate

TEST_AI_SRCS = $(TEST_DIR)/test_ai.cpp $(SRC_DIR)/AIPlayer.cpp $(SRC_DIR)/GameState.cpp $(SRC_DIR)/Board.cpp
TEST_AI_EXEC = test_ai

TEST_CONTROLLER_SRCS = $(TEST_DIR)/test_controller.cpp $(SRC_DIR)/Controller.cpp $(SRC_DIR)/GameState.cpp $(SRC_DIR)/Board.cpp
TEST_CONTROLLER_EXEC = test_controller

TEST_INTEGRATION_SRCS = $(TEST_DIR)/test_integration.cpp $(SRC_DIR)/GameState.cpp $(SRC_DIR)/Board.cpp $(SRC_DIR)/Controller.cpp
TEST_INTEGRATION_EXEC = test_integration

TEST_FULL_GAME_SRCS = $(TEST_DIR)/test_full_game.cpp $(COMMON_SRCS)
TEST_FULL_GAME_EXEC = test_full_game

# All test executables list
TEST_EXECS = $(TEST_BOARD_EXEC) $(TEST_GAMESTATE_EXEC) $(TEST_AI_EXEC) \
             $(TEST_CONTROLLER_EXEC) $(TEST_INTEGRATION_EXEC) $(TEST_FULL_GAME_EXEC)

# Default target: build only the main game
all: game
game: $(MAIN_EXEC)

# Build all test executables
tests: $(TEST_EXECS)

# Main executable rule
$(MAIN_EXEC): $(MAIN_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

# Test executable rules
$(TEST_BOARD_EXEC): $(TEST_BOARD_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

$(TEST_GAMESTATE_EXEC): $(TEST_GAMESTATE_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

$(TEST_AI_EXEC): $(TEST_AI_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

$(TEST_CONTROLLER_EXEC): $(TEST_CONTROLLER_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

$(TEST_INTEGRATION_EXEC): $(TEST_INTEGRATION_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

$(TEST_FULL_GAME_EXEC): $(TEST_FULL_GAME_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

# Run tests (builds them first if needed)
test: tests
	@echo "Running board tests..."
	./$(TEST_BOARD_EXEC)
	@echo "Running GameState tests..."
	./$(TEST_GAMESTATE_EXEC)
	@echo "Running AI tests..."
	./$(TEST_AI_EXEC)
	@echo "Running Controller tests..."
	./$(TEST_CONTROLLER_EXEC)
	@echo "Running integration tests..."
	./$(TEST_INTEGRATION_EXEC)
	@echo "Running full game tests..."
	./$(TEST_FULL_GAME_EXEC)
	@echo "All tests passed!"

# Run the main game (usage: make run ARGS="N M H")
run: $(MAIN_EXEC)
	./$(MAIN_EXEC) $(ARGS)

# Clean
clean:
	rm -f $(MAIN_EXEC) $(TEST_EXECS)

.PHONY: all game tests test run clean