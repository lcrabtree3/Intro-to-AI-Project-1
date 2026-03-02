#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include <iomanip>
#include "../include/Board.h"

void testInitialization() {
    std::cout << "Testing Board initialization..." << std::endl;
    
    // Test valid sizes
    for (int size = 3; size <= 10; size++) {
        Board board(size);
        assert(board.getSize() == size);
        
        // Check that board is empty
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                assert(board.getCell(row, col) == ' ');
            }
        }
    }
    
    // Test invalid sizes
    try {
        Board board(2);
        assert(false); // Should not reach here
    } catch (const std::invalid_argument& e) {
        // Expected
    }
    
    try {
        Board board(11);
        assert(false); // Should not reach here
    } catch (const std::invalid_argument& e) {
        // Expected
    }
    
    std::cout << "✓ Initialization tests passed" << std::endl;
}

void testPlaceDisk() {
    std::cout << "Testing disk placement..." << std::endl;
    
    Board board(5);
    
    // Test valid placement
    assert(board.placeDisk(0, 'X'));
    assert(board.getCell(0, 0) == 'X'); // Bottom row (row 0) should have X
    
    assert(board.placeDisk(0, 'O'));
    assert(board.getCell(1, 0) == 'O'); // Next row up
    
    assert(board.placeDisk(2, 'X'));
    assert(board.getCell(0, 2) == 'X');
    
    // Test invalid column
    assert(!board.placeDisk(5, 'X'));
    assert(!board.placeDisk(-1, 'X'));
    
    // Test invalid player
    assert(!board.placeDisk(1, 'A'));
    
    std::cout << "✓ Disk placement tests passed" << std::endl;
}

void testColumnFull() {
    std::cout << "Testing column full detection..." << std::endl;
    
    Board board(3); // 3x3 board
    
    // Column 0 should start empty
    assert(!board.isColumnFull(0));
    assert(board.getTopRow(0) == 0); // Bottom row is empty
    
    // Fill column 0 completely
    assert(board.placeDisk(0, 'X')); // Goes to row 0 (bottom)
    assert(board.placeDisk(0, 'O')); // Goes to row 1
    assert(board.placeDisk(0, 'X')); // Goes to row 2 (top)
    
    // Column should now be full
    assert(board.isColumnFull(0));
    assert(board.getTopRow(0) == -1);
    assert(!board.placeDisk(0, 'O'));
    
    // Check column 1 is still empty
    assert(!board.isColumnFull(1));
    assert(board.getTopRow(1) == 0);
    
    std::cout << "✓ Column full detection passed" << std::endl;
}

void testBoardFull() {
    std::cout << "Testing board full detection..." << std::endl;
    
    Board board3(3);
    
    assert(!board3.isFull());
    
    // Fill the board completely
    for (int col = 0; col < 3; col++) {
        for (int i = 0; i < 3; i++) {
            board3.placeDisk(col, (i % 2 == 0) ? 'X' : 'O');
        }
    }
    
    assert(board3.isFull());
    
    // Try to place another disk
    assert(!board3.placeDisk(0, 'X'));
    
    std::cout << "✓ Board full detection passed" << std::endl;
}

void testCopyConstructor() {
    std::cout << "Testing copy constructor..." << std::endl;
    
    Board original(4);
    
    // Make some moves
    original.placeDisk(0, 'X');
    original.placeDisk(0, 'O');
    original.placeDisk(1, 'X');
    
    // Create copy
    Board copy(original);
    
    // Verify copy matches original
    assert(copy.getSize() == original.getSize());
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            assert(copy.getCell(row, col) == original.getCell(row, col));
        }
    }
    
    // Modify original, copy should remain unchanged
    original.placeDisk(2, 'O');
    assert(copy.getCell(0, 2) == ' ');
    assert(original.getCell(0, 2) == 'O');
    
    std::cout << "✓ Copy constructor passed" << std::endl;
}

void testClear() {
    std::cout << "Testing board clear..." << std::endl;
    
    Board board(3);
    
    // Fill some cells
    board.placeDisk(0, 'X');
    board.placeDisk(0, 'O');
    board.placeDisk(1, 'X');
    
    assert(board.getCell(0, 0) != ' ');
    
    // Clear the board
    board.clear();
    
    // Verify all cells are empty
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            assert(board.getCell(row, col) == ' ');
        }
    }
    
    std::cout << "✓ Board clear passed" << std::endl;
}

void testColumnHeight() {
    std::cout << "Testing column height..." << std::endl;
    
    Board board(5);
    
    assert(board.getColumnHeight(0) == 0);
    assert(board.getColumnHeight(1) == 0);
    
    board.placeDisk(0, 'X');
    assert(board.getColumnHeight(0) == 1);
    
    board.placeDisk(0, 'O');
    assert(board.getColumnHeight(0) == 2);
    
    board.placeDisk(2, 'X');
    assert(board.getColumnHeight(2) == 1);
    assert(board.getColumnHeight(0) == 2);
    
    // Invalid column
    assert(board.getColumnHeight(5) == 0);
    
    std::cout << "✓ Column height passed" << std::endl;
}

void testToString() {
    std::cout << "Testing string representation..." << std::endl;
    
    Board board(3);
    
    // Empty board
    std::string emptyStr = board.toString();
    std::cout << "Empty board (3x3):\n" << emptyStr << std::endl;
    
    // Add some disks
    board.placeDisk(0, 'X');
    board.placeDisk(0, 'O');
    board.placeDisk(1, 'X');
    
    std::string filledStr = board.toString();
    std::cout << "Board after moves:\n" << filledStr << std::endl;
    
    // Test debug string
    std::string debugStr = board.toDebugString();
    std::cout << "Debug representation:\n" << debugStr << std::endl;
    
    // We can't easily assert the exact string, but we can check it's not empty
    assert(!emptyStr.empty());
    assert(!filledStr.empty());
    
    std::cout << "✓ String representation test passed (visual check)" << std::endl;
}

void testEdgeCases() {
    std::cout << "Testing edge cases..." << std::endl;
    
    Board board(3);
    
    // Try to place disk in invalid column
    assert(!board.placeDisk(3, 'X'));
    assert(!board.placeDisk(-1, 'X'));
    
    // Try to get cell out of bounds
    assert(board.getCell(-1, 0) == ' ');
    assert(board.getCell(3, 0) == ' ');
    assert(board.getCell(0, -1) == ' ');
    assert(board.getCell(0, 3) == ' ');
    
    // Check invalid column full (should return true)
    assert(board.isColumnFull(3) == true);
    
    std::cout << "✓ Edge cases passed" << std::endl;
}

int main() {
    std::cout << "=== Running Board Tests ===\n" << std::endl;
    
    testInitialization();
    testPlaceDisk();
    testColumnFull();
    testBoardFull();
    testCopyConstructor();
    testClear();
    testColumnHeight();
    testToString();
    testEdgeCases();
    
    std::cout << "\n✓ All Board tests passed!" << std::endl;
    return 0;
}