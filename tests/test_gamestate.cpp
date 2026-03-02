/*
 * Description:
 *   Unit tests for the GameState class. Verifies initial state, move application,
 *   win detection (horizontal, vertical), and draw detection.
 *
 * Notes:
 *   - Tests use 5x5 boards with M=4 for win scenarios and a 3x3 board with M=3 for draw.
 *   - applyMove is expected to update the board and switch players correctly.
 *   - Win detection is tested by constructing specific winning configurations.
 *   - Draw test ensures a full board with no winner is correctly identified.
 */

#include "GameState.h"
#include <cassert>
#include <iostream>

void testInitialState() {
    GameState state(5, 4, 'X');
    assert(state.getCurrentPlayer() == 'X');
    assert(state.isGameOver() == false);
    assert(state.getWinner() == '\0');
    assert(state.getWidth() == 5);
    assert(state.getMToWin() == 4);
    std::cout << "testInitialState passed\n";
}

void testApplyMove() {
    GameState state(5, 4, 'X');
    assert(state.applyMove(1) == true); // column 1
    assert(state.getCurrentPlayer() == 'O'); // switched
    assert(state.getBoard().getCell(0,0) == 'X'); // row0 col0
    // Invalid move: same column full? not yet, but we can apply another
    assert(state.applyMove(1) == true); // O in col1
    assert(state.getBoard().getCell(1,0) == 'O');
    // Now try invalid move: column out of range
    assert(state.applyMove(6) == false);
    std::cout << "testApplyMove passed\n";
}

void testWinDetectionHorizontal() {
    GameState state(5, 4, 'X');
    // Place X in columns 1,2,3,4 (bottom row)
    state.applyMove(1); // X
    state.applyMove(5); // O dummy
    state.applyMove(2); // X
    state.applyMove(5); // O dummy
    state.applyMove(3); // X
    state.applyMove(5); // O dummy
    state.applyMove(4); // X
    // Now X should have won
    assert(state.checkWin() == true);
    assert(state.isGameOver() == true);
    assert(state.getWinner() == 'X');
    std::cout << "testWinDetectionHorizontal passed\n";
}

void testWinDetectionVertical() {
    GameState state(5, 4, 'X');
    // Place X in column 1 four times
    for (int i = 0; i < 4; ++i) {
        state.applyMove(1); // X
        if (i < 3) state.applyMove(5); // O dummy to switch back
    }
    assert(state.checkWin() == true);
    assert(state.getWinner() == 'X');
    std::cout << "testWinDetectionVertical passed\n";
}

void testDraw() {
    GameState state(3, 3, 'X');
    // Build a draw configuration (no winner)
    // Moves: X col2, O col1, X col3, O col2, X col1, O col3, X col2, O col1, X col3
    state.applyMove(2); // X at (0,1)
    state.applyMove(1); // O at (0,0)
    state.applyMove(3); // X at (0,2)
    state.applyMove(2); // O at (1,1)
    state.applyMove(1); // X at (1,0)
    state.applyMove(3); // O at (1,2)
    state.applyMove(2); // X at (2,1)
    state.applyMove(1); // O at (2,0)
    state.applyMove(3); // X at (2,2)

    // Final board should be full and no winner
    assert(state.checkDraw() == true);
    assert(state.isGameOver() == true);
    assert(state.getWinner() == '\0');
    std::cout << "testDraw passed\n";
}

int main() {
    testInitialState();
    testApplyMove();
    testWinDetectionHorizontal();
    testWinDetectionVertical();
    testDraw();
    std::cout << "All GameState tests passed!\n";
    return 0;
}