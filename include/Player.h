#ifndef PLAYER_H
#define PLAYER_H
/*
 * Author: Katarina Kruse
 * Created: February 27, 2026
 * Last Modified: February 27, 2026
 *
 * Description:
 * Defines the interface for choosing a move. A Player is an agent that
 * observes a game state, chooses an action, and returns that action without
 * mutating the environment directly — "Given a game state, return a column
 * choice."
 *
 * Notes:
 * The Player does not change the game state. Controller mutates GameState.
 * Player only chooses a move and returns a decision (the column number to drop
 * into). When we pass `const GameState& state`, we are saying this function is
 * not allowed to modify the GameState object.
 *
 * A pure virtual function has no implementation in the base class and must be
 * implemented in derived classes. This makes Player abstract — you cannot
 * instantiate Player directly. Only HumanPlayer or AIPlayer (or similar
 * derivatives) can exist.
 *
 * To reference GameState, we forward declare it because the compiler only
 * needs to know the type exists, not its definition at this point.
 *
 * The destructor is defaulted because Player owns no resources, has no member
 * variables requiring cleanup, and does not allocate memory.
 *
 * Guards are necessary because they prevent the header from being processed
 * multiple times during compilation.
 *
 * Adding `const` after the function declaration applies to the Player object
 * itself — it promises the method will not modify Player’s internal state.
 * Combined with `const GameState&`, it also prevents modification of the game
 * state.
 *
 * Player represents behavior, not stateful data that needs duplication.
 * Copying polymorphic objects can cause slicing, so the game should own Player
 * via pointers or smart pointers rather than copying instances.
 *
 * There is no gameplay reason to duplicate a Player object.
 */
class GameState;

class Player {
public:
    virtual int chooseMove(const GameState& state) const = 0;
    virtual ~Player() = default;

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
};

#endif