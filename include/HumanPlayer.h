#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

/*
 * Author: Katarina Kruse
 * Last modified: March 1, 2026
 *
 * Description:
 *   HumanPlayer implements the Player interface for a human user.
 *   It prompts the user for a column number via standard input,
 *   validates that the input is a number within the allowed range,
 *   and returns the chosen column (1‑based). It does not mutate the game state.
 *
 * Notes:
 *   - getMove() blocks until valid input is received.
 *   - Input is read as a string and converted to int; invalid input is rejected.
 *   - The function relies on GameState::getWidth() to know the board size.
 */

#include "Player.h"
#include "GameState.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(char id);
    virtual ~HumanPlayer() = default;
    int getMove(const GameState& state) const override;
};

#endif 