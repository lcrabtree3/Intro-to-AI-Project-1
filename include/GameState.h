#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Board.h"  // Add this include
#include <memory>

/**
 * @class GameState
 * @brief Manages the state of the Connect M game
 * 
 * The GameState class is responsible for maintaining the current state of the game,
 * including the board configuration, current player, and game rules. It enforces
 * all game rules including valid moves, win detection, and draw detection.
 */
class GameState {
private:
    std::unique_ptr<Board> board;  // This now knows about Board
    char currentPlayer;
    int mToWin;  // M: number of disks needed to win
    bool gameOver;
    char winner;

public:
    /**
     * @brief Constructor for GameState
     * @param n Size of the N x N grid
     * @param m Number of disks needed to connect contiguously to win
     * @param firstPlayer Character representing the first player ('X' or 'O')
     */
    GameState(int n, int m, char firstPlayer);
    
    /**
     * @brief Copy constructor for GameState
     * @param other GameState to copy from
     */
    GameState(const GameState& other);
    
    /**
     * @brief Apply a move to the game state
     * @param column Column number (1-based indexing) to place disk
     * @return true if move was valid and applied, false otherwise
     */
    bool applyMove(int column);
    
    /**
     * @brief Check if a move is valid
     * @param column Column number (1-based indexing) to check
     * @return true if move is valid, false otherwise
     */
    bool isValidMove(int column) const;
    
    /**
     * @brief Get the current player
     * @return Character representing current player ('X' or 'O')
     */
    char getCurrentPlayer() const { return currentPlayer; }
    
    /**
     * @brief Get the board
     * @return Const reference to the board
     */
    const Board& getBoard() const { return *board; }
    
    /**
     * @brief Check if the game is over
     * @return true if game is over (win or draw), false otherwise
     */
    bool isGameOver() const { return gameOver; }
    
    /**
     * @brief Get the winner
     * @return Character representing winner ('X', 'O', or '\0' if no winner/draw)
     */
    char getWinner() const { return winner; }
    
    /**
     * @brief Get the number of disks needed to win
     * @return M value
     */
    int getMToWin() const { return mToWin; }
    
    /**
     * @brief Switch to the next player
     */
    void switchPlayer();
    
    /**
     * @brief Check if the current player has won
     * @return true if current player has won, false otherwise
     */
    bool checkWin() const;
    
    /**
     * @brief Check if the game is a draw (board full)
     * @return true if board is full, false otherwise
     */
    bool checkDraw() const;

private:
    /**
     * @brief Check for horizontal win
     * @param row Row to check
     * @param col Column to check
     * @param player Player to check for
     * @return true if player has M in a row horizontally
     */
    bool checkHorizontal(int row, int col, char player) const;
    
    /**
     * @brief Check for vertical win
     * @param row Row to check
     * @param col Column to check
     * @param player Player to check for
     * @return true if player has M in a row vertically
     */
    bool checkVertical(int row, int col, char player) const;
    
    /**
     * @brief Check for diagonal win (top-left to bottom-right)
     * @param row Row to check
     * @param col Column to check
     * @param player Player to check for
     * @return true if player has M in a row diagonally
     */
    bool checkDiagonalDown(int row, int col, char player) const;
    
    /**
     * @brief Check for diagonal win (top-right to bottom-left)
     * @param row Row to check
     * @param col Column to check
     * @param player Player to check for
     * @return true if player has M in a row diagonally
     */
    bool checkDiagonalUp(int row, int col, char player) const;
};

#endif // GAMESTATE_H