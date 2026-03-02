/*
 * Description:
 *   Integration tests for the game logic. Verifies that a full game ends correctly
 *   with a win or a draw using the Controller and GameState classes.
 *
 * Notes:
 *   - Uses a 5x5 board with M=4 for win test, and a 3x3 board with M=3 for draw test.
 *   - The win test constructs a horizontal win for X.
 *   - The draw test uses a predefined move sequence that fills the board without a winner.
 */

#include "GameState.h"
#include "Controller.h"
#include <cassert>
#include <iostream>

void testGameEndsOnWin() {
    GameState state(5, 4, 'X');
    Controller ctrl(state);
    // X plays columns 1,2,3,4 in order with O playing in column 5 each time
    ctrl.applyMove(1); // X
    ctrl.applyMove(5); // O
    ctrl.applyMove(2); // X
    ctrl.applyMove(5); // O
    ctrl.applyMove(3); // X
    ctrl.applyMove(5); // O
    ctrl.applyMove(4); // X
    assert(state.isGameOver() == true);
    assert(state.getWinner() == 'X');
    std::cout << "testGameEndsOnWin passed\n";
}

void testGameEndsOnDraw() {
    GameState state(3, 3, 'X');
    Controller ctrl(state);
    // Build a draw configuration on 3x3 board with M=3
    // Sequence (1-based columns) that results in no winner:
    // 3,2,1,2,1,3,3,1,2
    int columns[] = {3, 2, 1, 2, 1, 3, 3, 1, 2};
    for (int i = 0; i < 9; ++i) {
        ctrl.applyMove(columns[i]);
    }
    assert(state.isGameOver() == true);
    assert(state.getWinner() == '\0');
    // Also verify board is full
    assert(state.getBoard().isFull() == true);
    std::cout << "testGameEndsOnDraw passed\n";
}

int main() {
    testGameEndsOnWin();
    testGameEndsOnDraw();
    std::cout << "All integration tests passed!\n";
    return 0;
}