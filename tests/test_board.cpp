/*
 * Description:
 *   Unit tests for the Board class. Verifies board initialization, disk placement,
 *   column capacity, invalid column handling, and full board detection.
 *
 * Notes:
 *   - Tests use 5x5 and 3x3 boards to cover different sizes.
 *   - Column indices are 0‑based internally.
 *   - Assertions confirm expected behavior after each operation.
 */

#include "Board.h"
#include <cassert>
#include <iostream>

void testBoardInitialization() {
    Board b(5);
    assert(b.getSize() == 5);
    assert(b.isFull() == false);
    for (int col = 0; col < 5; ++col) {
        assert(b.isColumnFull(col) == false);
        assert(b.getColumnHeight(col) == 0);
        assert(b.getTopRow(col) == 0);
    }
    std::cout << "testBoardInitialization passed\n";
}

void testPlaceDisk() {
    Board b(5);
    // Place X in column 0
    assert(b.placeDisk(0, 'X') == true);
    assert(b.getCell(0, 0) == 'X');
    assert(b.getColumnHeight(0) == 1);
    assert(b.getTopRow(0) == 1); // next empty row is 1

    // Place O in same column
    assert(b.placeDisk(0, 'O') == true);
    assert(b.getCell(1, 0) == 'O');
    assert(b.getColumnHeight(0) == 2);
    assert(b.getTopRow(0) == 2);

    // Fill column
    for (int i = 2; i < 5; ++i) {
        assert(b.placeDisk(0, 'X') == true);
    }
    assert(b.isColumnFull(0) == true);
    assert(b.placeDisk(0, 'O') == false);
    std::cout << "testPlaceDisk passed\n";
}

void testInvalidColumn() {
    Board b(5);
    assert(b.placeDisk(5, 'X') == false); // out of range
    assert(b.isColumnFull(5) == true); // invalid considered full
    assert(b.getTopRow(5) == -1);
    assert(b.getCell(0,5) == ' ');
    std::cout << "testInvalidColumn passed\n";
}

void testFullBoard() {
    Board b(3);
    for (int col = 0; col < 3; ++col) {
        for (int row = 0; row < 3; ++row) {
            b.placeDisk(col, 'X');
        }
    }
    assert(b.isFull() == true);
    std::cout << "testFullBoard passed\n";
}

int main() {
    testBoardInitialization();
    testPlaceDisk();
    testInvalidColumn();
    testFullBoard();
    std::cout << "All board tests passed!\n";
    return 0;
}