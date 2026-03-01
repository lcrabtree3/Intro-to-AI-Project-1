#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
/*
 * Author: Katarina Kruse
 * Created: February 27, 2026
 * Last Modified: February 27, 2026
 *
 * Description:
 * Defines a human-controlled player that requests input and returns
 * a column choice. This class overrides the Player interface.
 *
 * Notes:
 * HumanPlayer inherits from Player and must implement chooseMove.
 * The function prompts the user for input (implementation in .cpp).
 *
 * A forward declaration of GameState is used because only the type
 * needs to be known here — not its definition.
 *
 * The destructor is defaulted since no special resource management
 * is required.
 */
class GameState;

#include "Player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer() = default;
    ~HumanPlayer() = default;

    HumanPlayer(const HumanPlayer&) = delete;
    HumanPlayer& operator=(const HumanPlayer&) = delete;

    int chooseMove(const GameState& state) const override;
};

#endif