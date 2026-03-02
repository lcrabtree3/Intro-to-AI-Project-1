#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include <iomanip>
#include <exception>
#include "../include/Board.h"

// Helper function to print test results
void printTestResult(const std::string& testName, bool passed) {
    if (passed) {
        std::cout << "  ✓ " << testName << " passed" << std::endl;
    } else {
        std::cout << "  ✗ " << testName << " FAILED" << std::endl;
    }
}

void testInitialization() {
    std::cout << "\n--- Testing Board Initialization ---" << std::endl;
    
    try {
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
        std::cout << "  Valid sizes 3-10: OK" << std::endl;
        
        // Test invalid sizes
        bool caughtException = false;
        try {
            Board board(2);
        } catch (const std::invalid_argument& e) {
            caughtException = true;
            std::cout << "  Size 2 correctly rejected: " << e.what() << std::endl;
        }
        assert(caughtException);
        
        caughtException = false;
        try {
            Board board(11);
        } catch (const std::invalid_argument& e) {
            caughtException = true;
            std::cout << "  Size 11 correctly rejected: " << e.what() << std::endl;
        }
        assert(caughtException);
        
        printTestResult("Initialization", true);
    } catch (const std::exception& e) {
        std::cout << "  Exception: " << e.what() << std::endl;
        printTestResult("Initialization", false);
        throw;
    }
}

void testPlaceDisk() {
    std::cout << "\n--- Testing Disk Placement ---" << std::endl;
    
    try {
        Board board(5);
        std::cout << "  Created 5x5 board" << std::endl;
        
        // Test valid placement
        std::cout << "  Placing X at col 0..." << std::endl;
        assert(board.placeDisk(0, 'X'));
        assert(board.getCell(0, 0) == 'X');
        std::cout << "    Row 0, Col 0 = " << board.getCell(0, 0) << std::endl;
        
        std::cout << "  Placing O at col 0..." << std::endl;
        assert(board.placeDisk(0, 'O'));
        assert(board.getCell(1, 0) == 'O');
        std::cout << "    Row 1, Col 0 = " << board.getCell(1, 0) << std::endl;
        
        std::cout << "  Placing X at col 2..." << std::endl;
        assert(board.placeDisk(2, 'X'));
        assert(board.getCell(0, 2) == 'X');
        std::cout << "    Row 0, Col 2 = " << board.getCell(0, 2) << std::endl;
        
        // Test invalid column
        std::cout << "  Testing invalid column 5..." << std::endl;
        assert(!board.placeDisk(5, 'X'));
        std::cout << "    Correctly rejected" << std::endl;
        
        std::cout << "  Testing invalid column -1..." << std::endl;
        assert(!board.placeDisk(-1, 'X'));
        std::cout << "    Correctly rejected" << std::endl;
        
        // Test invalid player
        std::cout << "  Testing invalid player 'A'..." << std::endl;
        assert(!board.placeDisk(1, 'A'));
        std::cout << "    Correctly rejected" << std::endl;
        
        printTestResult("Disk Placement", true);
    } catch (const std::exception& e) {
        std::cout << "  Exception: " << e.what() << std::endl;
        printTestResult("Disk Placement", false);
        throw;
    }
}

void testColumnFull() {
    std::cout << "\n--- Testing Column Full Detection ---" << std::endl;
    
    try {
        Board board(3);
        std::cout << "  Created 3x3 board" << std::endl;
        
        // Column 0 should start empty
        std::cout << "  Initial state - Column 0 empty?" << std::endl;
        assert(!board.isColumnFull(0));
        assert(board.getTopRow(0) == 0);
        std::cout << "    isColumnFull(0) = " << (board.isColumnFull(0) ? "true" : "false") << std::endl;
        std::cout << "    getTopRow(0) = " << board.getTopRow(0) << std::endl;
        
        // Fill column 0 completely
        std::cout << "  Placing X at col 0 (1/3)..." << std::endl;
        assert(board.placeDisk(0, 'X'));
        std::cout << "  Placing O at col 0 (2/3)..." << std::endl;
        assert(board.placeDisk(0, 'O'));
        std::cout << "  Placing X at col 0 (3/3)..." << std::endl;
        assert(board.placeDisk(0, 'X'));
        
        // Column should now be full
        std::cout << "  Column 0 full now?" << std::endl;
        assert(board.isColumnFull(0));
        assert(board.getTopRow(0) == -1);
        assert(!board.placeDisk(0, 'O'));
        std::cout << "    isColumnFull(0) = " << (board.isColumnFull(0) ? "true" : "false") << std::endl;
        std::cout << "    getTopRow(0) = " << board.getTopRow(0) << std::endl;
        
        // Check column 1 is still empty
        std::cout << "  Column 1 should still be empty" << std::endl;
        assert(!board.isColumnFull(1));
        assert(board.getTopRow(1) == 0);
        
        printTestResult("Column Full Detection", true);
    } catch (const std::exception& e) {
        std::cout << "  Exception: " << e.what() << std::endl;
        printTestResult("Column Full Detection", false);
        throw;
    }
}

void testBoardFull() {
    std::cout << "\n--- Testing Board Full Detection ---" << std::endl;
    
    try {
        Board board3(3);
        
        assert(!board3.isFull());
        std::cout << "  Initial board not full: OK" << std::endl;
        
        // Fill the board completely
        for (int col = 0; col < 3; col++) {
            for (int i = 0; i < 3; i++) {
                board3.placeDisk(col, (i % 2 == 0) ? 'X' : 'O');
            }
        }
        
        assert(board3.isFull());
        std::cout << "  Board full after filling: OK" << std::endl;
        
        // Try to place another disk
        assert(!board3.placeDisk(0, 'X'));
        std::cout << "  Cannot place disk in full board: OK" << std::endl;
        
        printTestResult("Board Full Detection", true);
    } catch (const std::exception& e) {
        std::cout << "  Exception: " << e.what() << std::endl;
        printTestResult("Board Full Detection", false);
        throw;
    }
}

void testCopyConstructor() {
    std::cout << "\n--- Testing Copy Constructor ---" << std::endl;
    
    try {
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
        std::cout << "  Copy matches original: OK" << std::endl;
        
        // Modify original, copy should remain unchanged
        original.placeDisk(2, 'O');
        assert(copy.getCell(0, 2) == ' ');
        assert(original.getCell(0, 2) == 'O');
        std::cout << "  Copy independent from original: OK" << std::endl;
        
        printTestResult("Copy Constructor", true);
    } catch (const std::exception& e) {
        std::cout << "  Exception: " << e.what() << std::endl;
        printTestResult("Copy Constructor", false);
        throw;
    }
}

void testClear() {
    std::cout << "\n--- Testing Board Clear ---" << std::endl;
    
    try {
        Board board(3);
        
        // Fill some cells
        board.placeDisk(0, 'X');
        board.placeDisk(0, 'O');
        board.placeDisk(1, 'X');
        
        assert(board.getCell(0, 0) != ' ');
        std::cout << "  Board has disks: OK" << std::endl;
        
        // Clear the board
        board.clear();
        
        // Verify all cells are empty
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                assert(board.getCell(row, col) == ' ');
            }
        }
        std::cout << "  Board cleared: OK" << std::endl;
        
        printTestResult("Board Clear", true);
    } catch (const std::exception& e) {
        std::cout << "  Exception: " << e.what() << std::endl;
        printTestResult("Board Clear", false);
        throw;
    }
}

void testColumnHeight() {
    std::cout << "\n--- Testing Column Height ---" << std::endl;
    
    try {
        Board board(5);
        
        assert(board.getColumnHeight(0) == 0);
        assert(board.getColumnHeight(1) == 0);
        std::cout << "  Initial heights: OK" << std::endl;
        
        board.placeDisk(0, 'X');
        assert(board.getColumnHeight(0) == 1);
        std::cout << "  Height 1 after one disk: OK" << std::endl;
        
        board.placeDisk(0, 'O');
        assert(board.getColumnHeight(0) == 2);
        std::cout << "  Height 2 after two disks: OK" << std::endl;
        
        board.placeDisk(2, 'X');
        assert(board.getColumnHeight(2) == 1);
        assert(board.getColumnHeight(0) == 2);
        std::cout << "  Multiple columns: OK" << std::endl;
        
        // Invalid column
        assert(board.getColumnHeight(5) == 0);
        std::cout << "  Invalid column returns 0: OK" << std::endl;
        
        printTestResult("Column Height", true);
    } catch (const std::exception& e) {
        std::cout << "  Exception: " << e.what() << std::endl;
        printTestResult("Column Height", false);
        throw;
    }
}

void testEdgeCases() {
    std::cout << "\n--- Testing Edge Cases ---" << std::endl;
    
    try {
        Board board(3);
        
        // Try to place disk in invalid column
        assert(!board.placeDisk(3, 'X'));
        assert(!board.placeDisk(-1, 'X'));
        std::cout << "  Invalid columns rejected: OK" << std::endl;
        
        // Try to get cell out of bounds
        assert(board.getCell(-1, 0) == ' ');
        assert(board.getCell(3, 0) == ' ');
        assert(board.getCell(0, -1) == ' ');
        assert(board.getCell(0, 3) == ' ');
        std::cout << "  Out of bounds returns empty: OK" << std::endl;
        
        // Check invalid column full (should return true)
        assert(board.isColumnFull(3) == true);
        std::cout << "  Invalid column considered full: OK" << std::endl;
        
        printTestResult("Edge Cases", true);
    } catch (const std::exception& e) {
        std::cout << "  Exception: " << e.what() << std::endl;
        printTestResult("Edge Cases", false);
        throw;
    }
}

// ============= VISUALIZATION TESTS =============

void testBasicVisualization() {
    std::cout << "\n--- Testing Basic Visualization (toString) ---" << std::endl;
    
    try {
        Board board(5);
        
        std::cout << "Empty 5x5 board:" << std::endl;
        std::string emptyStr = board.toString();
        std::cout << emptyStr << std::endl;
        assert(!emptyStr.empty());
        assert(emptyStr.find('+') != std::string::npos);
        assert(emptyStr.find('|') != std::string::npos);
        
        // Add some disks
        board.placeDisk(0, 'X');
        board.placeDisk(0, 'O');
        board.placeDisk(1, 'X');
        board.placeDisk(2, 'O');
        board.placeDisk(2, 'X');
        board.placeDisk(3, 'O');
        
        std::cout << "Board after some moves:" << std::endl;
        std::string filledStr = board.toString();
        std::cout << filledStr << std::endl;
        assert(!filledStr.empty());
        assert(filledStr.find('X') != std::string::npos);
        assert(filledStr.find('O') != std::string::npos);
        
        printTestResult("Basic Visualization", true);
    } catch (const std::exception& e) {
        std::cout << "  Exception: " << e.what() << std::endl;
        printTestResult("Basic Visualization", false);
        throw;
    }
}

void testSimpleVisualization() {
    std::cout << "\n--- Testing Simple Visualization (toSimpleString) ---" << std::endl;
    
    try {
        Board board(4);
        
        std::cout << "Empty 4x4 board (simple):" << std::endl;
        std::string emptyStr = board.toSimpleString();
        std::cout << emptyStr << std::endl;
        assert(!emptyStr.empty());
        assert(emptyStr.find('|') != std::string::npos);
        
        // Add some disks
        board.placeDisk(0, 'X');
        board.placeDisk(1, 'O');
        board.placeDisk(2, 'X');
        board.placeDisk(3, 'O');
        
        std::cout << "Board after moves (simple):" << std::endl;
        std::string filledStr = board.toSimpleString();
        std::cout << filledStr << std::endl;
        assert(filledStr.find('X') != std::string::npos);
        assert(filledStr.find('O') != std::string::npos);
        
        printTestResult("Simple Visualization", true);
    } catch (const std::exception& e) {
        std::cout << "  Exception: " << e.what() << std::endl;
        printTestResult("Simple Visualization", false);
        throw;
    }
}

void testFancyVisualization() {
    std::cout << "\n--- Testing Fancy Visualization (toFancyString) ---" << std::endl;
    
    try {
        Board board(3);
        
        std::cout << "Empty 3x3 board (fancy):" << std::endl;
        std::string emptyStr = board.toFancyString();
        std::cout << emptyStr << std::endl;
        assert(!emptyStr.empty());
        assert(emptyStr.find('╔') != std::string::npos);
        assert(emptyStr.find('╗') != std::string::npos);
        
        // Add some disks
        board.placeDisk(0, 'X');
        board.placeDisk(1, 'O');
        board.placeDisk(2, 'X');
        
        std::cout << "Board after moves (fancy):" << std::endl;
        std::string filledStr = board.toFancyString();
        std::cout << filledStr << std::endl;
        assert(filledStr.find('X') != std::string::npos);
        assert(filledStr.find('O') != std::string::npos);
        
        printTestResult("Fancy Visualization", true);
    } catch (const std::exception& e) {
        std::cout << "  Exception: " << e.what() << std::endl;
        printTestResult("Fancy Visualization", false);
        throw;
    }
}

void testCompactVisualization() {
    std::cout << "\n--- Testing Compact Visualization (toCompactString) ---" << std::endl;
    
    try {
        Board board(6);
        
        std::cout << "Empty 6x6 board (compact):" << std::endl;
        std::string emptyStr = board.toCompactString();
        std::cout << emptyStr << std::endl;
        assert(!emptyStr.empty());
        assert(emptyStr.find('·') != std::string::npos);
        
        // Add some disks
        for (int col = 0; col < 6; col++) {
            board.placeDisk(col, (col % 2 == 0) ? 'X' : 'O');
        }
        
        std::cout << "Board after moves (compact):" << std::endl;
        std::string filledStr = board.toCompactString();
        std::cout << filledStr << std::endl;
        assert(filledStr.find('X') != std::string::npos);
        assert(filledStr.find('O') != std::string::npos);
        
        printTestResult("Compact Visualization", true);
    } catch (const std::exception& e) {
        std::cout << "  Exception: " << e.what() << std::endl;
        printTestResult("Compact Visualization", false);
        throw;
    }
}

void testGuidedVisualization() {
    std::cout << "\n--- Testing Guided Visualization (toGuidedString) ---" << std::endl;
    
    try {
        Board board(4);
        
        std::cout << "Empty 4x4 board (guided):" << std::endl;
        std::string emptyStr = board.toGuidedString();
        std::cout << emptyStr << std::endl;
        assert(!emptyStr.empty());
        assert(emptyStr.find('.') != std::string::npos);
        
        // Fill some columns partially
        board.placeDisk(0, 'X');
        board.placeDisk(0, 'O');
        board.placeDisk(0, 'X');
        
        board.placeDisk(2, 'O');
        board.placeDisk(2, 'X');
        
        board.placeDisk(3, 'O');
        
        std::cout << "Board with varied heights (guided):" << std::endl;
        std::string filledStr = board.toGuidedString();
        std::cout << filledStr << std::endl;
        assert(filledStr.find('X') != std::string::npos);
        assert(filledStr.find('O') != std::string::npos);
        
        printTestResult("Guided Visualization", true);
    } catch (const std::exception& e) {
        std::cout << "  Exception: " << e.what() << std::endl;
        printTestResult("Guided Visualization", false);
        throw;
    }
}

void testStripedVisualization() {
    std::cout << "\n--- Testing Striped Visualization (toStripedString) ---" << std::endl;
    
    try {
        Board board(5);
        
        std::cout << "Empty 5x5 board (striped):" << std::endl;
        std::string emptyStr = board.toStripedString();
        std::cout << emptyStr << std::endl;
        assert(!emptyStr.empty());
        assert(emptyStr.find('=') != std::string::npos || emptyStr.find('-') != std::string::npos);
        
        // Fill completely
        for (int col = 0; col < 5; col++) {
            for (int i = 0; i < 5; i++) {
                board.placeDisk(col, (i % 2 == 0) ? 'X' : 'O');
            }
        }
        
        std::cout << "Full board (striped):" << std::endl;
        std::string filledStr = board.toStripedString();
        std::cout << filledStr << std::endl;
        
        printTestResult("Striped Visualization", true);
    } catch (const std::exception& e) {
        std::cout << "  Exception: " << e.what() << std::endl;
        printTestResult("Striped Visualization", false);
        throw;
    }
}

void testAllBoardSizes() {
    std::cout << "\n--- Testing All Board Sizes ---" << std::endl;
    
    try {
        for (int size = 3; size <= 8; size++) {
            Board board(size);
            
            // Add a diagonal pattern
            for (int i = 0; i < size; i++) {
                if (i < size) {
                    board.placeDisk(i, 'X');
                }
            }
            
            std::cout << "Board size " << size << "x" << size << ":" << std::endl;
            std::cout << board.toString() << std::endl;
        }
        
        printTestResult("All Board Sizes", true);
    } catch (const std::exception& e) {
        std::cout << "  Exception: " << e.what() << std::endl;
        printTestResult("All Board Sizes", false);
        throw;
    }
}

void testDebugInfo() {
    std::cout << "\n--- Testing Debug Information ---" << std::endl;
    
    try {
        Board board(4);
        
        std::cout << "Initial debug info:" << std::endl;
        std::string debugStr = board.toDebugString();
        std::cout << debugStr << std::endl;
        assert(!debugStr.empty());
        assert(debugStr.find("Board State") != std::string::npos);
        
        // Add some disks
        board.placeDisk(0, 'X');
        board.placeDisk(0, 'O');
        board.placeDisk(1, 'X');
        board.placeDisk(2, 'O');
        board.placeDisk(2, 'X');
        board.placeDisk(2, 'O');
        
        std::cout << "After moves debug info:" << std::endl;
        debugStr = board.toDebugString();
        std::cout << debugStr << std::endl;
        
        // Test column heights string
        std::string heightsStr = board.getColumnHeightsString();
        std::cout << "Column heights: " << heightsStr << std::endl;
        assert(!heightsStr.empty());
        
        // Test column header
        std::string headerStr = board.getColumnHeader();
        std::cout << "Column header: " << headerStr;
        assert(!headerStr.empty());
        
        // Test footer
        std::string footerStr = board.getFooter();
        std::cout << "Footer: " << footerStr << std::endl;
        assert(!footerStr.empty());
        
        printTestResult("Debug Info", true);
    } catch (const std::exception& e) {
        std::cout << "  Exception: " << e.what() << std::endl;
        printTestResult("Debug Info", false);
        throw;
    }
}

// ============= MAIN FUNCTION =============

int main() {
    std::cout << "======================================" << std::endl;
    std::cout << "         BOARD TESTS" << std::endl;
    std::cout << "======================================" << std::endl;
    
    // Core functionality tests
    testInitialization();
    testPlaceDisk();
    testColumnFull();
    testBoardFull();
    testCopyConstructor();
    testClear();
    testColumnHeight();
    testEdgeCases();
    
    // Visualization tests
    std::cout << "\n======================================" << std::endl;
    std::cout << "     VISUALIZATION TESTS" << std::endl;
    std::cout << "======================================" << std::endl;
    
    testBasicVisualization();
    testSimpleVisualization();
    testFancyVisualization();
    testCompactVisualization();
    testGuidedVisualization();
    testStripedVisualization();
    testAllBoardSizes();
    testDebugInfo();
    
    std::cout << "\n======================================" << std::endl;
    std::cout << "✓ ALL TESTS PASSED!" << std::endl;
    std::cout << "======================================" << std::endl;
    
    return 0;
}