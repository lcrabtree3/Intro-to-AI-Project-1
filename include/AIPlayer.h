#ifndef AIPLAYER_H
#define AIPLAYER_H

/*
 * Author: Katarina Kruse
 * Last modified: March 1, 2026
 *
 * Description:
 *   AIPlayer class implements an AI player using minimax with alpha-beta pruning.
 *   It evaluates board positions using a heuristic function based on sliding windows.
 *
 * Notes:
 *   - The AI never mutates the actual game state; it works on copies.
 *   - getMove returns a 1‑based column index.
 *   - The evaluation function rewards long sequences and penalizes opponent threats.
 */

#include "Player.h"
#include "GameState.h"
#include <vector>

class AIPlayer : public Player {
private:
    int maxDepth;
    static constexpr double INF = 1e9;

    std::vector<int> getLegalMoves(const GameState& s) const;

    double maxValue(const GameState& s, double alpha, double beta, int depth) const;
    double minValue(const GameState& s, double alpha, double beta, int depth) const;

    double evaluate(const GameState& s) const;
    double evaluateWindow(const GameState& s, int row, int col, int dr, int dc, int M, char ai, char opponent) const;

public:
    AIPlayer(char player, int depth);
    virtual ~AIPlayer();
    int getMove(const GameState& s) const override;   // returns 1‑based column
};

#endif