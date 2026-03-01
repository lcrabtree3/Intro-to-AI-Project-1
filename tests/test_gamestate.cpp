// tests/test_gamestate.cpp
#include <iostream>
#include <cassert>
#include <memory>
#include <vector>

// Minimal Board stub class - defined before including GameState
class Board {
private:
    std::vector<std::vector<char>> grid;
    int size;

public:
    Board(int n) : size(n) {
        grid.resize(size, std::vector<char>(size, ' '));
    }
    
    Board(const Board& other) : size(other.size), grid(other.grid) {}
    
    bool placeDisk(int col, char player) {
        if (col < 0 || col >= size || isColumnFull(col)) {
            return false;
        }
        int row = getTopRow(col);
        if (row >= 0) {
            grid[row][col] = player;
            return true;
        }
        return false;
    }
    
    bool isColumnFull(int col) const {
        return grid[0][col] != ' ';
    }
    
    int getTopRow(int col) const {
        for (int row = size - 1; row >= 0; row--) {
            if (grid[row][col] == ' ') {
                return row;
            }
        }
        return -1;
    }
    
    char getCell(int row, int col) const {
        if (row < 0 || row >= size || col < 0 || col >= size) {
            return ' ';
        }
        return grid[row][col];
    }
    
    int getSize() const { return size; }
    
    bool isFull() const {
        for (int col = 0; col < size; col++) {
            if (!isColumnFull(col)) {
                return false;
            }
        }
        return true;
    }
};

// Now include GameState
#include "../include/GameState.h"

void testInitialization() {
    std::cout << "Testing GameState initialization..." << std::endl;
    
    // Test valid initialization
    GameState state(5, 4, 'X');
    assert(state.getCurrentPlayer() == 'X');
    assert(state.getMToWin() == 4);
    assert(!state.isGameOver());
    assert(state.getWinner() == '\0');
    
    std::cout << "✓ Initialization tests passed" << std::endl;
}

void testValidMoves() {
    std::cout << "Testing valid move detection..." << std::endl;
    
    GameState state(5, 4, 'X');
    
    // Test valid column range
    assert(state.isValidMove(1));
    assert(state.isValidMove(5));
    assert(!state.isValidMove(0));
    assert(!state.isValidMove(6));
    
    // Test applying valid move
    assert(state.applyMove(3));
    assert(state.getCurrentPlayer() == 'O'); // Should switch to O
    
    std::cout << "✓ Valid move tests passed" << std::endl;
}

void testColumnCapacity() {
    std::cout << "Testing column capacity rules..." << std::endl;
    
    GameState state(3, 3, 'X');
    
    // Fill column 2 completely (3 rows)
    assert(state.applyMove(2)); // X
    assert(state.applyMove(2)); // O
    assert(state.applyMove(2)); // X
    
    // Column should now be full
    assert(!state.isValidMove(2));
    assert(!state.applyMove(2));
    
    std::cout << "✓ Column capacity tests passed" << std::endl;
}

void testWinDetectionHorizontal() {
    std::cout << "Testing horizontal win detection..." << std::endl;
    
    GameState state(5, 4, 'X');
    
    // Create horizontal win for X in bottom row (row 0)
    state.applyMove(1); // X in row 0, col 0
    state.applyMove(5); // O elsewhere
    state.applyMove(2); // X in row 0, col 1
    state.applyMove(5); // O elsewhere
    state.applyMove(3); // X in row 0, col 2
    state.applyMove(5); // O elsewhere
    state.applyMove(4); // X in row 0, col 3 - This should win
    
    assert(state.isGameOver());
    assert(state.getWinner() == 'X');
    
    std::cout << "✓ Horizontal win detection passed" << std::endl;
}

void testWinDetectionVertical() {
    std::cout << "Testing vertical win detection..." << std::endl;
    
    GameState state(5, 4, 'X');
    
    // Create vertical win for X in column 3
    state.applyMove(3); // X in row 0, col 2
    state.applyMove(4); // O elsewhere
    state.applyMove(3); // X in row 1, col 2
    state.applyMove(4); // O elsewhere
    state.applyMove(3); // X in row 2, col 2
    state.applyMove(4); // O elsewhere
    state.applyMove(3); // X in row 3, col 2 - This should win
    
    assert(state.isGameOver());
    assert(state.getWinner() == 'X');
    
    std::cout << "✓ Vertical win detection passed" << std::endl;
}

void testWinDetectionDiagonal() {
    std::cout << "Testing diagonal win detection..." << std::endl;
    
    GameState state(5, 4, 'X');
    
    // Create diagonal win (bottom-left to top-right)
    state.applyMove(1); // X at (0,0)
    state.applyMove(5); // O elsewhere
    state.applyMove(2); // X at (0,1)
    state.applyMove(5); // O elsewhere
    state.applyMove(2); // X at (1,1)
    state.applyMove(5); // O elsewhere
    state.applyMove(3); // X at (0,2)
    state.applyMove(5); // O elsewhere
    state.applyMove(3); // O at (1,2)
    state.applyMove(5); // O elsewhere
    state.applyMove(3); // X at (2,2)
    state.applyMove(5); // O elsewhere
    state.applyMove(4); // X at (0,3)
    state.applyMove(5); // O elsewhere
    state.applyMove(4); // O at (1,3)
    state.applyMove(5); // O elsewhere
    state.applyMove(4); // O at (2,3)
    state.applyMove(5); // O elsewhere
    state.applyMove(4); // X at (3,3) - This should create diagonal of 4 X's
    
    assert(state.isGameOver());
    assert(state.getWinner() == 'X');
    
    std::cout << "✓ Diagonal win detection passed" << std::endl;
}

void testDrawDetection() {
    std::cout << "Testing draw detection..." << std::endl;
    
    GameState state(3, 3, 'X'); // Small 3x3 board
    
    // Fill the board completely
    for (int i = 0; i < 9; i++) {
        int col = (i % 3) + 1;
        state.applyMove(col);
    }
    
    assert(state.isGameOver());
    assert(state.getWinner() == '\0');
    
    std::cout << "✓ Draw detection passed" << std::endl;
}

void testCopyConstructor() {
    std::cout << "Testing copy constructor..." << std::endl;
    
    GameState original(5, 4, 'X');
    original.applyMove(3);
    
    GameState copy(original);
    
    assert(copy.getCurrentPlayer() == original.getCurrentPlayer());
    assert(copy.getMToWin() == original.getMToWin());
    assert(copy.isGameOver() == original.isGameOver());
    
    // Modify original, copy should remain unchanged
    original.applyMove(4);
    assert(copy.getCurrentPlayer() != original.getCurrentPlayer());
    
    std::cout << "✓ Copy constructor passed" << std::endl;
}

void testNoIllegalMutations() {
    std::cout << "Testing that game state prevents illegal mutations..." << std::endl;
    
    GameState state(5, 4, 'X');
    
    // Try invalid column
    assert(!state.applyMove(6));
    
    // Try move after game over
    state.applyMove(1);
    state.applyMove(2);
    state.applyMove(1);
    state.applyMove(2);
    state.applyMove(1);
    state.applyMove(2);
    state.applyMove(1); // X wins vertically in col 1
    
    assert(state.isGameOver());
    assert(!state.applyMove(3)); // Should reject move
    
    std::cout << "✓ Illegal mutation prevention passed" << std::endl;
}

int main() {
    std::cout << "=== Running GameState Tests ===\n" << std::endl;
    
    testInitialization();
    testValidMoves();
    testColumnCapacity();
    testWinDetectionHorizontal();
    testWinDetectionVertical();
    testWinDetectionDiagonal();
    testDrawDetection();
    testCopyConstructor();
    testNoIllegalMutations();
    
    std::cout << "\n✓ All GameState tests passed!" << std::endl;
    return 0;
}