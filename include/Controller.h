#ifndef CONTROLLER_H
#define CONTROLLER_H

/*
 * Author: Katarina Kruse
 * Last modified: March 1, 2026
 *
 * Description:
 *   The Controller class is responsible for validating and applying moves
 *   to the game state. It acts as the intermediary between the game logic
 *   and the board state, ensuring that only legal moves are executed.
 *
 * Notes:
 *   - The controller holds a reference to the GameState and is the only
 *     component that directly mutates it.
 *   - applyMove returns true if the move was successfully applied; false otherwise.
 *   - isValidMove checks whether a move would be legal without applying it.
 */

#include "GameState.h"

class Controller {
private:
    GameState& gameState;

public:
    Controller(GameState& state);
    ~Controller() = default;

    bool applyMove(int column);        // 1‑based, returns true if successful
    bool isValidMove(int column) const; // 1‑based
};

#endif