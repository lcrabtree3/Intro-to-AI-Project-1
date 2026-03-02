/*
 * Description:
 *   Unit tests for the AIPlayer class. Verifies that the AI returns valid moves,
 *   blocks opponent wins, takes winning moves, and handles a full board.
 *
 * Notes:
 *   - Tests use small boards (5x5 and 3x3) with appropriate win conditions (M=4 or M=3).
 *   - Each test constructs a specific board state and checks the AI's chosen column.
 *   - Assertions are used to verify expected behavior.
 */

#include "AIPlayer.h"
#include "GameState.h"
#include <cassert>
#include <iostream>

void testAIReturnsValidMove() {
    GameState state(5, 4, 'X');
    AIPlayer ai('X', 4);
    int move = ai.getMove(state);
    assert(move >= 1 && move <= 5);
    std::cout << "testAIReturnsValidMove passed\n";
}

void testAIBlocksOpponentWin() {
    GameState state(5, 4, 'O');
    // O threatens horizontally at row0, cols 1-3
    state.applyMove(1); // O at (0,0)
    state.applyMove(5); // X dummy
    state.applyMove(2); // O at (0,1)
    state.applyMove(5); // X dummy
    state.applyMove(3); // O at (0,2)
    // X must block at col4
    AIPlayer ai('X', 4);
    int move = ai.getMove(state);
    assert(move == 4);
    std::cout << "testAIBlocksOpponentWin passed\n";
}

void testAIWinsIfPossible() {
    GameState state(5, 4, 'X');
    // X has three in a row horizontally at row0, cols 1-3
    state.applyMove(1); // X at (0,0)
    state.applyMove(5); // O dummy
    state.applyMove(2); // X at (0,1)
    state.applyMove(5); // O dummy
    state.applyMove(3); // X at (0,2)
    state.applyMove(5); // O dummy
    // X can win by playing col4
    AIPlayer ai('X', 4);
    int move = ai.getMove(state);
    assert(move == 4);
    std::cout << "testAIWinsIfPossible passed\n";
}

void testAIBlocksVerticalWin() {
    GameState state(5, 4, 'O');
    // O has three in a column (col1, rows 0-2)
    state.applyMove(1); // O at (0,0)
    state.applyMove(5); // X dummy
    state.applyMove(1); // O at (1,0)
    state.applyMove(5); // X dummy
    state.applyMove(1); // O at (2,0)
    // X must block at col1
    AIPlayer ai('X', 4);
    int move = ai.getMove(state);
    assert(move == 1);
    std::cout << "testAIBlocksVerticalWin passed\n";
}

void testAIReturnsMinusOneIfNoMoves() {
    GameState state(3, 3, 'X');
    // Fill board completely
    for (int i = 0; i < 3; ++i) {
        state.applyMove(1);
        state.applyMove(2);
        state.applyMove(3);
    }
    AIPlayer ai('X', 4);
    int move = ai.getMove(state);
    assert(move == -1);
    std::cout << "testAIReturnsMinusOneIfNoMoves passed\n";
}

int main() {
    testAIReturnsValidMove();
    testAIBlocksOpponentWin();
    testAIWinsIfPossible();
    testAIBlocksVerticalWin();
    testAIReturnsMinusOneIfNoMoves();
    std::cout << "All AI tests passed!\n";
    return 0;
}