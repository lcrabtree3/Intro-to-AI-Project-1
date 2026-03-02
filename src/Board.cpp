#include "Board.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>

Board::Board(int n) : size(n) {
    if (n < 3 || n > 10) {
        throw std::invalid_argument("Board size must be between 3 and 10");
    }
    
    // Initialize grid with empty spaces
    // Row 0 is BOTTOM, row size-1 is TOP
    grid.resize(size, std::vector<char>(size, ' '));
}

Board::Board(const Board& other) : grid(other.grid), size(other.size) {}

bool Board::placeDisk(int col, char player) {
    // Validate column index
    if (!isValidColumn(col)) {
        return false;
    }
    
    // Validate player symbol
    if (player != 'X' && player != 'O') {
        return false;
    }
    
    // Check if column is full
    if (isColumnFull(col)) {
        return false;
    }
    
    // Find the lowest empty row in this column
    // Since row 0 is BOTTOM, we start from row 0 and go up until we find an empty space
    for (int row = 0; row < size; row++) {
        if (grid[row][col] == ' ') {
            grid[row][col] = player;
            return true;
        }
    }
    
    return false; // Should never reach here if column isn't full
}

bool Board::isColumnFull(int col) const {
    if (!isValidColumn(col)) {
        return true; // Invalid columns are considered full
    }
    
    // Column is full if the TOP cell (row size-1) is occupied
    // But actually, column is full if the BOTTOM cell (row 0) is occupied? No, that's wrong.
    // Let's think: In a 3-row board:
    // Row 2 (top) - if this is filled, column is full
    // So we should check the topmost row (size-1)
    return grid[size - 1][col] != ' ';
}

int Board::getTopRow(int col) const {
    if (!isValidColumn(col)) {
        return -1;
    }
    
    // Find the highest row that has a disk in this column
    // This tells us how many disks are in the column
    for (int row = 0; row < size; row++) {
        if (grid[row][col] == ' ') {
            return row; // Return the first empty row from bottom
        }
    }
    
    return -1; // Column is full (no empty rows)
}

char Board::getCell(int row, int col) const {
    if (row < 0 || row >= size || col < 0 || col >= size) {
        return ' '; // Return empty for out of bounds
    }
    return grid[row][col];
}

bool Board::isFull() const {
    for (int col = 0; col < size; col++) {
        if (!isColumnFull(col)) {
            return false;
        }
    }
    return true;
}

void Board::clear() {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            grid[row][col] = ' ';
        }
    }
}

std::string Board::toString() const {
    std::stringstream ss;
    
    // Draw the board from TOP to BOTTOM for display
    // So we iterate from size-1 down to 0
    for (int row = size - 1; row >= 0; row--) {
        ss << "|";
        for (int col = 0; col < size; col++) {
            char cell = grid[row][col];
            if (cell == ' ') {
                ss << " |";
            } else {
                ss << cell << "|";
            }
        }
        ss << "\n";
    }
    
    // Add column numbers at the bottom
    ss << " ";
    for (int col = 1; col <= size; col++) {
        ss << col << " ";
    }
    ss << "\n";
    
    return ss.str();
}

std::string Board::toDebugString() const {
    std::stringstream ss;
    
    ss << "Board State (size=" << size << "):\n";
    ss << "    ";
    for (int col = 0; col < size; col++) {
        ss << " c" << col;
    }
    ss << "\n";
    
    for (int row = size - 1; row >= 0; row--) {
        ss << "r" << std::setw(2) << row << ":";
        for (int col = 0; col < size; col++) {
            char cell = grid[row][col];
            if (cell == ' ') {
                ss << " .";
            } else {
                ss << " " << cell;
            }
        }
        ss << "\n";
    }
    
    // Column heights
    ss << "Heights:";
    for (int col = 0; col < size; col++) {
        ss << " " << getColumnHeight(col);
    }
    ss << "\n";
    
    // Column full status
    ss << "Full:    ";
    for (int col = 0; col < size; col++) {
        ss << " " << (isColumnFull(col) ? "Y" : "N");
    }
    ss << "\n";
    
    return ss.str();
}

bool Board::isValidColumn(int col) const {
    return col >= 0 && col < size;
}

int Board::getColumnHeight(int col) const {
    if (!isValidColumn(col)) {
        return 0;
    }
    
    int height = 0;
    for (int row = 0; row < size; row++) {
        if (grid[row][col] != ' ') {
            height++;
        }
    }
    return height;
}