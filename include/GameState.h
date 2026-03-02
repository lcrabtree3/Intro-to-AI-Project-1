#ifndef GAMESTATE_H
#define GAMESTATE_H

/*
 * Author: Louis Crabtree
 * Last modified: March 1, 2026
 *
 * Description:
 *   The GameState class manages the current state of a Connect M game.
 *   It owns the Board, tracks the current player, enforces game rules
 *   (valid moves, win detection, draw detection), and handles state
 *   transitions. All rule enforcement is contained here.
 *
 * Notes:
 *   - applyMove() expects a 1‑based column number.
 *   - After a move, it automatically checks for win/draw and updates
 *     gameOver and winner.
 *   - The class is copyable and movable, enabling simulation for AI.
 */

#include "Board.h"
#include <memory>
#include <string>

class GameState {
private:
    std::unique_ptr<Board> board;
    char currentPlayer;
    int mToWin;
    bool gameOver;
    char winner;

    bool checkHorizontal(int row, int col, char player) const;
    bool checkVertical(int row, int col, char player) const;
    bool checkDiagonalDown(int row, int col, char player) const;
    bool checkDiagonalUp(int row, int col, char player) const;
    bool checkAllDirections(int row, int col, char player) const;
    void switchPlayer();

public:
    GameState(int n, int m, char firstPlayer);
    ~GameState();

    GameState(const GameState& other);
    GameState(GameState&& other) noexcept;
    GameState& operator=(const GameState& other);
    GameState& operator=(GameState&& other) noexcept;

    bool applyMove(int column);      // 1‑based
    bool isValidMove(int column) const; // 1‑based

    bool checkWin() const;
    bool checkDraw() const;
    bool isGameOver() const { return gameOver; }
    char getWinner() const { return winner; }

    char getCurrentPlayer() const { return currentPlayer; }
    const Board& getBoard() const { return *board; }
    int getMToWin() const { return mToWin; }
    int getWidth() const { return board->getSize(); }

    std::string getWinDescription() const;
};

#endif 