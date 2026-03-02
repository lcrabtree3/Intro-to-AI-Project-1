#include "Board.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <algorithm>

Board::Board(int n) : size(n) {
    if (n < 3 || n > 10) {
        throw std::invalid_argument("Board size must be between 3 and 10");
    }
    
    // Initialize grid with empty spaces
    // Row 0 is bottom, row size-1 is top
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
    // Since row 0 is bottom, we start from row 0 and go up
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
    
    // Column is full if the top cell (row size-1) is occupied
    return grid[size - 1][col] != ' ';
}

int Board::getTopRow(int col) const {
    if (!isValidColumn(col)) {
        return -1;
    }
    
    // Find the highest empty row in this column
    for (int row = 0; row < size; row++) {
        if (grid[row][col] == ' ') {
            return row;
        }
    }
    
    return -1; // Column is full
}

char Board::getCell(int row, int col) const {
    if (row < 0 || row >= size || col < 0 || col >= size) {
        return ' ';
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

std::string Board::getColumnHeader() const {
    std::stringstream ss;
    ss << "   ";
    for (int col = 1; col <= size; col++) {
        ss << " " << col << "  ";
    }
    ss << "\n";
    return ss.str();
}

std::string Board::getColumnHeightsString() const {
    std::stringstream ss;
    ss << "H: ";
    for (int col = 0; col < size; col++) {
        ss << " " << getColumnHeight(col) << "  ";
    }
    return ss.str();
}

std::string Board::getFooter() const {
    std::stringstream ss;
    ss << "Board: " << size << "x" << size << " | ";
    ss << "Full: " << (isFull() ? "Yes" : "No");
    return ss.str();
}

std::string Board::toString() const {
    std::stringstream ss;
    
    // Add top border
    ss << "   +";
    for (int col = 0; col < size; col++) {
        ss << "---+";
    }
    ss << "\n";
    
    // Draw the board from top to bottom
    for (int row = size - 1; row >= 0; row--) {
        ss << " " << (row + 1) << " |";
        for (int col = 0; col < size; col++) {
            char cell = grid[row][col];
            if (cell == ' ') {
                ss << "   |";
            } else {
                ss << " " << cell << " |";
            }
        }
        ss << "\n";
        
        // Add horizontal line between rows
        ss << "   +";
        for (int col = 0; col < size; col++) {
            ss << "---+";
        }
        ss << "\n";
    }
    
    // Add column numbers at the bottom
    ss << "     ";
    for (int col = 1; col <= size; col++) {
        ss << col << "   ";
    }
    ss << "\n";
    
    return ss.str();
}

std::string Board::toSimpleString() const {
    std::stringstream ss;
    
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
    
    ss << " ";
    for (int col = 1; col <= size; col++) {
        ss << col << " ";
    }
    ss << "\n";
    
    return ss.str();
}

std::string Board::toFancyString() const {
    std::stringstream ss;
    
    // Top border with double line
    ss << "   ╔";
    for (int col = 0; col < size; col++) {
        ss << "═══╤";
    }
    ss.seekp(-1, std::ios_base::end); // Remove last '╤'
    ss << "╗\n";
    
    for (int row = size - 1; row >= 0; row--) {
        ss << " " << (row + 1) << " ║";
        for (int col = 0; col < size; col++) {
            char cell = grid[row][col];
            if (cell == ' ') {
                ss << "   │";
            } else {
                ss << " " << cell << " │";
            }
        }
        ss.seekp(-1, std::ios_base::end); // Remove last '│'
        ss << "║\n";
        
        if (row > 0) {
            ss << "   ╟";
            for (int col = 0; col < size; col++) {
                ss << "───┼";
            }
            ss.seekp(-1, std::ios_base::end); // Remove last '┼'
            ss << "╢\n";
        }
    }
    
    // Bottom border
    ss << "   ╚";
    for (int col = 0; col < size; col++) {
        ss << "═══╧";
    }
    ss.seekp(-1, std::ios_base::end); // Remove last '╧'
    ss << "╝\n";
    
    // Column numbers
    ss << "     ";
    for (int col = 1; col <= size; col++) {
        ss << col << "   ";
    }
    ss << "\n";
    
    return ss.str();
}

std::string Board::toCompactString() const {
    std::stringstream ss;
    
    for (int row = size - 1; row >= 0; row--) {
        for (int col = 0; col < size; col++) {
            char cell = grid[row][col];
            if (cell == ' ') {
                ss << "·";
            } else {
                ss << cell;
            }
            if (col < size - 1) ss << " ";
        }
        ss << "\n";
    }
    
    ss << "\n";
    for (int col = 1; col <= size; col++) {
        ss << col << " ";
    }
    ss << "\n";
    
    return ss.str();
}

std::string Board::toGuidedString() const {
    std::stringstream ss;
    
    // Add column guides at the top
    ss << "   ";
    for (int col = 1; col <= size; col++) {
        ss << "  " << col << "  ";
    }
    ss << "\n";
    
    ss << "   +";
    for (int col = 0; col < size; col++) {
        ss << "-----+";
    }
    ss << "\n";
    
    for (int row = size - 1; row >= 0; row--) {
        ss << " " << (row + 1) << " |";
        for (int col = 0; col < size; col++) {
            char cell = grid[row][col];
            if (cell == ' ') {
                ss << "  .  |";
            } else {
                ss << "  " << cell << "  |";
            }
        }
        ss << "\n";
        
        ss << "   +";
        for (int col = 0; col < size; col++) {
            ss << "-----+";
        }
        ss << "\n";
    }
    
    return ss.str();
}

std::string Board::toStripedString() const {
    std::stringstream ss;
    
    ss << "   ";
    for (int col = 1; col <= size; col++) {
        ss << "  " << col << "  ";
    }
    ss << "\n";
    
    for (int row = size - 1; row >= 0; row--) {
        // Alternate row background (simulated with different border characters)
        if (row % 2 == 0) {
            ss << "   +";
            for (int col = 0; col < size; col++) {
                ss << "=====+";
            }
            ss << "\n";
            ss << " " << (row + 1) << " ‖";
        } else {
            ss << "   +";
            for (int col = 0; col < size; col++) {
                ss << "-----+";
            }
            ss << "\n";
            ss << " " << (row + 1) << " |";
        }
        
        for (int col = 0; col < size; col++) {
            char cell = grid[row][col];
            if (cell == ' ') {
                ss << "  .  ";
            } else {
                ss << "  " << cell << "  ";
            }
            if (row % 2 == 0) {
                ss << "‖";
            } else {
                ss << "|";
            }
        }
        ss << "\n";
    }
    
    // Bottom border
    ss << "   +";
    for (int col = 0; col < size; col++) {
        ss << "-----+";
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
    
    ss << getColumnHeightsString() << "\n";
    
    ss << "Full:    ";
    for (int col = 0; col < size; col++) {
        ss << " " << (isColumnFull(col) ? "Y" : "N");
    }
    ss << "\n";
    
    return ss.str();
}