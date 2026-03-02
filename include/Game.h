#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>
#include "GameState.h"
#include "Controller.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

/**
 * @class Game
 * @brief Orchestrates the entire Connect M game
 * 
 * The Game class is responsible for the main game loop, player turn management,
 * and coordinating between the GameState, Controller, and Player classes.
 * It owns the Controller and both players, and handles the high-level game flow.
 */
class Game {
private:
    std::unique_ptr<GameState> gameState;
    std::unique_ptr<Controller> controller;
    std::unique_ptr<HumanPlayer> humanPlayer;
    std::unique_ptr<AIPlayer> aiPlayer;
    Player* currentPlayer;  // Pointer to either humanPlayer or aiPlayer
    int boardSize;
    int mToWin;
    bool humanFirst;
    int moveCount;
    
    /**
     * @brief Initialize players based on command line arguments
     * @param humanMovesFirst True if human moves first, false if AI moves first
     */
    void initializePlayers(bool humanMovesFirst);
    
    /**
     * @brief Display the welcome message and game info
     */
    void displayWelcome() const;
    
    /**
     * @brief Display the current board state
     */
    void displayBoard() const;
    
    /**
     * @brief Display the game result (win/draw)
     */
    void displayResult() const;
    
    /**
     * @brief Display the current player's turn
     */
    void displayTurn() const;
    
    /**
     * @brief Get the appropriate player symbol for display
     * @param player The player object
     * @return 'X' for human, 'O' for AI
     */
    char getPlayerSymbol(const Player* player) const;
    
    /**
     * @brief Check if the game should end
     * @return true if game is over
     */
    bool checkGameOver();
    
    /**
     * @brief Process a player's move
     * @param column The column chosen by the player
     * @return true if move was valid and processed
     */
    bool processMove(int column);

public:
    /**
     * @brief Constructor for Game
     * @param n Size of the N x N grid
     * @param m Number of disks needed to win
     * @param h Flag indicating who moves first (1 for human, 0 for AI)
     */
    Game(int n, int m, int h);
    
    /**
     * @brief Destructor
     */
    ~Game() = default;
    
    /**
     * @brief Run the main game loop
     */
    void run();
    
    /**
     * @brief Check if the game is over
     * @return true if game is over (win or draw)
     */
    bool isGameOver() const { return gameState->isGameOver(); }
    
    /**
     * @brief Get the winner of the game
     * @return 'X' for human, 'O' for AI, '\0' for draw
     */
    char getWinner() const { return gameState->getWinner(); }
    
    /**
     * @brief Get a string representation of the current board
     * @return ASCII board representation
     */
    std::string getBoardString() const { return gameState->getBoard().toString(); }
    
    /**
     * @brief Get the current player
     * @return 'X' or 'O'
     */
    char getCurrentPlayerSymbol() const { return gameState->getCurrentPlayer(); }
    
    /**
     * @brief Get the number of moves made so far
     * @return Move count
     */
    int getMoveCount() const { return moveCount; }
};

#endif // GAME_H