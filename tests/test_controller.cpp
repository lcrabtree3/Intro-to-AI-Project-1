/*
 * Description:
 *   Unit tests for the Controller class. Verifies that the controller correctly
 *   applies valid moves, rejects invalid moves, and checks move legality.
 *
 * Notes:
 *   - Tests use a 5x5 board with win condition M=4.
 *   - applyMove is expected to return true for valid moves and false otherwise.
 *   - isValidMove should reflect the legality without modifying state.
 */

#include "Controller.h"
#include "GameState.h"
#include <cassert>
#include <iostream>

void testApplyValidMove() {
    GameState state(5, 4, 'X');
    Controller ctrl(state);
    assert(ctrl.applyMove(1) == true);
    assert(state.getCurrentPlayer() == 'O');
    assert(state.getBoard().getCell(0,0) == 'X');
    std::cout << "testApplyValidMove passed\n";
}

void testApplyInvalidMove() {
    GameState state(5, 4, 'X');
    Controller ctrl(state);
    // Fill column 1
    for (int i = 0; i < 5; ++i) {
        state.applyMove(1);
        if (i < 4) state.applyMove(2);
    }
    assert(ctrl.applyMove(1) == false);
    assert(ctrl.applyMove(6) == false);
    std::cout << "testApplyInvalidMove passed\n";
}

void testIsValidMove() {
    GameState state(5, 4, 'X');
    Controller ctrl(state);
    assert(ctrl.isValidMove(1) == true);
    assert(ctrl.isValidMove(5) == true);
    assert(ctrl.isValidMove(6) == false);
    // Fill column 1
    for (int i = 0; i < 5; ++i) {
        state.applyMove(1);
        if (i < 4) state.applyMove(2);
    }
    assert(ctrl.isValidMove(1) == false);
    std::cout << "testIsValidMove passed\n";
}

int main() {
    testApplyValidMove();
    testApplyInvalidMove();
    testIsValidMove();
    std::cout << "All Controller tests passed!\n";
    return 0;
}