/*
 * Author: Katarina Kruse
 * Last modified: March 1, 2026
 *
 * Description:
 *   Implementation of the Controller class. The controller acts as an intermediary
 *   between game logic and the game state, validating and applying moves.
 *
 * Notes:
 *   - The controller holds a reference to a GameState and applies moves via applyMove.
 *   - isValidMove checks move legality without modifying state.
 */

#include "Controller.h"

Controller::Controller(GameState& state) : gameState(state) {}

bool Controller::applyMove(int column) {
    return gameState.applyMove(column);
}

bool Controller::isValidMove(int column) const {
    return gameState.isValidMove(column);
}