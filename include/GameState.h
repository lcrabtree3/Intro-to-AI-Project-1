#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Board.h"
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
    std::unique_ptr<Board> board;
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
     * @brief Destructor
     */
    ~GameState();
    
    /**
     * @brief Copy constructor
     * @param other GameState to copy from
     */
    GameState(const GameState& other);
    
    /**
     * @brief Move constructor
     * @param other GameState to move from
     */
    GameState(GameState&& other) noexcept;
    
    /**
     * @brief Copy assignment operator
     * @param other GameState to copy from
     * @return Reference to this GameState
     */
    GameState& operator=(const GameState& other);
    
    /**
     * @brief Move assignment operator
     * @param other GameState to move from
     * @return Reference to this GameState
     */
    GameState& operator=(GameState&& other) noexcept;
    
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

    // ============= WIN DETECTION METHODS =============
    
    /**
     * @brief Check for a win horizontally
     * @param row Row to check
     * @param col Column to check
     * @param player Player to check for
     * @return true if player has M in a row horizontally
     */
    bool checkHorizontal(int row, int col, char player) const;
    
    /**
     * @brief Check for a win vertically
     * @param row Row to check
     * @param col Column to check
     * @param player Player to check for
     * @return true if player has M in a row vertically
     */
    bool checkVertical(int row, int col, char player) const;
    
    /**
     * @brief Check for a win diagonally (down-right direction)
     * @param row Row to check
     * @param col Column to check
     * @param player Player to check for
     * @return true if player has M in a row diagonally
     */
    bool checkDiagonalDown(int row, int col, char player) const;
    
    /**
     * @brief Check for a win diagonally (up-right direction)
     * @param row Row to check
     * @param col Column to check
     * @param player Player to check for
     * @return true if player has M in a row diagonally
     */
    bool checkDiagonalUp(int row, int col, char player) const;
    
    /**
     * @brief Check all four directions from a starting cell
     * @param row Row to check
     * @param col Column to check
     * @param player Player to check for
     * @return true if any direction has M in a row
     */
    bool checkAllDirections(int row, int col, char player) const;
    
    /**
     * @brief Get a description of the win (for debugging)
     * @return String describing the win type and location
     */
    std::string getWinDescription() const;
};

#endif // GAMESTATE_H