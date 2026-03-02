#ifndef PLAYER_H
#define PLAYER_H

/*
 * Author: Katarina Kruse
 * Last modified: March 1, 2026
 *
 * Description:
 *   Player is an abstract base class defining the interface for all players
 *   (human or AI). It stores a player identifier ('X' or 'O') and requires
 *   derived classes to implement getMove(), which returns the chosen column.
 *
 * Notes:
 *   - getMove() returns a 1‑based column number.
 *   - The class does not hold any game state; it only defines the interface.
 *   - GameState is forward declared to avoid circular includes.
 */

class GameState;   // forward declaration

class Player {
protected:
    char playerId;
public:
    Player(char id) : playerId(id) {}
    virtual ~Player() = default;
    virtual int getMove(const GameState& state) const = 0;   // returns 1‑based column
    virtual char getPlayerId() const { return playerId; }
};

#endif 