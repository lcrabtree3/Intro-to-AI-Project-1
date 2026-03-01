#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <memory>

/**
 * @class Board
 * @brief Manages the game board grid for Connect M
 * 
 * The Board class is responsible for storing the game grid,
 * handling disk placement, checking column capacity, and
 * providing access to cell information. It does not contain
 * any game logic like win detection.
 */
class Board {
private:
    std::vector<std::vector<char>> grid;  // 2D grid representation
    int size;  // N x N grid size

public:
    /**
     * @brief Constructor for Board
     * @param n Size of the N x N grid (must be between 3 and 10)
     */
    Board(int n);
    
    /**
     * @brief Copy constructor
     * @param other Board to copy from
     */
    Board(const Board& other);
    
    /**
     * @brief Place a disk in the specified column
     * @param col Column index (0-based) to place the disk
     * @param player Character representing the player ('X' or 'O')
     * @return true if disk was placed successfully, false if column is full or invalid
     */
    bool placeDisk(int col, char player);
    
    /**
     * @brief Check if a column is full
     * @param col Column index (0-based) to check
     * @return true if column has no empty spaces, false otherwise
     */
    bool isColumnFull(int col) const;
    
    /**
     * @brief Get the topmost empty row in a column
     * @param col Column index (0-based) to check
     * @return Row index of the topmost empty space, or -1 if column is full
     */
    int getTopRow(int col) const;
    
    /**
     * @brief Get the cell value at a specific position
     * @param row Row index (0-based, 0 is bottom)
     * @param col Column index (0-based)
     * @return Character at the position ('X', 'O', or ' ' for empty)
     */
    char getCell(int row, int col) const;
    
    /**
     * @brief Get the size of the board
     * @return N (board is N x N)
     */
    int getSize() const { return size; }
    
    /**
     * @brief Check if the board is completely full
     * @return true if all cells are occupied, false otherwise
     */
    bool isFull() const;
    
    /**
     * @brief Clear the board (set all cells to empty)
     */
    void clear();
    
    /**
     * @brief Get a string representation of the board for display
     * @return ASCII representation of the board
     */
    std::string toString() const;
    
    /**
     * @brief Get a string representation with row numbers
     * @return ASCII representation with row indices
     */
    std::string toDebugString() const;
    
    /**
     * @brief Check if a column index is valid
     * @param col Column index to check
     * @return true if column is within board bounds
     */
    bool isValidColumn(int col) const;
    
    /**
     * @brief Get the number of disks in a column
     * @param col Column index to check
     * @return Number of disks in the column
     */
    int getColumnHeight(int col) const;
};

#endif // BOARD_H