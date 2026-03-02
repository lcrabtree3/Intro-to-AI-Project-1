#ifndef GAME_H
#define GAME_H

/*
 * Author: Louis Crabtree
 * Last modified: March 1, 2026
 *
 * Description:
 *   The Game class orchestrates the entire Connect M game. It owns the GameState,
 *   Controller, and player objects, and manages the main game loop, turn switching,
 *   and board display. It does not implement AI logic.
 *
 * Notes:
 *   - The game alternates turns between human and AI based on the H parameter.
 *   - After each valid move, the board is printed and win/draw conditions are checked.
 *   - The game ends when a player connects M disks or the board is full.
 */

#include <memory>
#include <string>
#include "GameState.h"
#include "Controller.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

class Game {
private:
    int boardSize;
    int mToWin;
    bool humanFirst;
    int moveCount;
    
    std::unique_ptr<GameState> gameState;
    std::unique_ptr<Controller> controller;
    std::unique_ptr<HumanPlayer> humanPlayer;
    std::unique_ptr<AIPlayer> aiPlayer;
    Player* currentPlayer;
    
    void initializePlayers(bool humanMovesFirst);
    void displayWelcome() const;
    void displayBoard() const;
    void displayResult() const;
    void displayTurn() const;
    char getPlayerSymbol(const Player* player) const;
    bool checkGameOver();
    bool processMove(int column);

public:
    Game(int n, int m, int h);
    ~Game() = default;
    
    void run();
    bool isGameOver() const { return gameState->isGameOver(); }
    char getWinner() const { return gameState->getWinner(); }
    std::string getBoardString() const { return gameState->getBoard().toString(); }
    char getCurrentPlayerSymbol() const { return gameState->getCurrentPlayer(); }
    int getMoveCount() const { return moveCount; }
};

#endif