#ifndef BOARD_H
#define BOARD_H

/*
 * Author: Louis Crabtree
 * Last modified: March 1, 2026
 *
 * Description:
 *   The Board class manages the N x N game grid for Connect M.
 *   It handles disk placement, column capacity, and provides read‑only
 *   access to cell data. It does not implement win detection.
 *
 * Notes:
 *   - Row 0 is the bottom, row size-1 is the top.
 *   - Columns are 0‑based internally, but user input is 1‑based.
 *   - The board is stored as a 2D vector of characters ('X', 'O', or ' ').
 */

#include <vector>
#include <string>

class Board {
private:
    std::vector<std::vector<char>> grid;
    int size;

public:
    Board(int n);
    Board(const Board& other);

    bool placeDisk(int col, char player);
    bool isColumnFull(int col) const;
    int getTopRow(int col) const;
    char getCell(int row, int col) const;
    int getSize() const { return size; }
    bool isFull() const;
    void clear();
    bool isValidColumn(int col) const;
    int getColumnHeight(int col) const;

    std::string getColumnHeader() const;
    std::string getColumnHeightsString() const;
    std::string getFooter() const;
    std::string toString() const;
    std::string toSimpleString() const;
    std::string toFancyString() const;
    std::string toCompactString() const;
    std::string toGuidedString() const;
    std::string toStripedString() const;
    std::string toDebugString() const;
};

#endif