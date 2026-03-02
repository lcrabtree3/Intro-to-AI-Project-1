/*
 * Author: Katarina Kruse
 * Last modified: March 1, 2026
 *
 * Description:
 *   Implementation of the AIPlayer class. Implements minimax with alpha-beta pruning
 *   and a heuristic evaluation function based on sliding windows.
 *
 * Notes:
 *   - getMove returns the best column (1‑based) according to the search.
 *   - The evaluation function rewards long sequences for the AI and penalizes opponent threats.
 */

#include "AIPlayer.h"
#include <algorithm>
#include <cmath>

AIPlayer::AIPlayer(char player, int depth) : Player(player), maxDepth(depth) {}

AIPlayer::~AIPlayer() = default;

std::vector<int> AIPlayer::getLegalMoves(const GameState& s) const {
    std::vector<int> moves;
    int N = s.getBoard().getSize();
    for (int col = 1; col <= N; ++col) {
        if (s.isValidMove(col)) {
            moves.push_back(col);
        }
    }
    return moves;
}

int AIPlayer::getMove(const GameState& s) const {
    std::vector<int> moves = getLegalMoves(s);
    if (moves.empty()) return -1;

    double bestValue = -INF;
    int bestMove = moves[0];

    for (int col : moves) {
        GameState nextState = s;
        nextState.applyMove(col);

        double value = minValue(nextState, -INF, INF, 1);

        if (value > bestValue) {
            bestValue = value;
            bestMove = col;
        }
    }
    return bestMove;
}

double AIPlayer::maxValue(const GameState& s, double alpha, double beta, int depth) const {
    if (depth >= maxDepth || s.checkDraw() || s.checkWin()) {
        return evaluate(s);
    }

    double V = -INF;
    std::vector<int> moves = getLegalMoves(s);

    for (int col : moves) {
        GameState nextState = s;
        nextState.applyMove(col);

        double v_prime = minValue(nextState, alpha, beta, depth + 1);

        V = std::max(V, v_prime);

        if (V >= beta) return V;
        alpha = std::max(alpha, V);
    }
    return V;
}

double AIPlayer::minValue(const GameState& s, double alpha, double beta, int depth) const {
    if (depth >= maxDepth || s.checkDraw() || s.checkWin()) {
        return evaluate(s);
    }

    double V = INF;
    std::vector<int> moves = getLegalMoves(s);

    for (int col : moves) {
        GameState nextState = s;
        nextState.applyMove(col);

        double v_prime = maxValue(nextState, alpha, beta, depth + 1);

        V = std::min(V, v_prime);

        if (V <= alpha) return V;
        beta = std::min(beta, V);
    }
    return V;
}

double AIPlayer::evaluate(const GameState& s) const {
    char ai = getPlayerId();
    char opponent = (ai == 'X') ? 'O' : 'X';

    int N = s.getBoard().getSize();
    int M = s.getMToWin();

    double score = 0.0;

    // Horizontal windows
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col <= N - M; ++col) {
            score += evaluateWindow(s, row, col, 0, 1, M, ai, opponent);
        }
    }

    // Vertical windows
    for (int row = 0; row <= N - M; ++row) {
        for (int col = 0; col < N; ++col) {
            score += evaluateWindow(s, row, col, 1, 0, M, ai, opponent);
        }
    }

    // Diagonal down-right
    for (int row = 0; row <= N - M; ++row) {
        for (int col = 0; col <= N - M; ++col) {
            score += evaluateWindow(s, row, col, 1, 1, M, ai, opponent);
        }
    }

    // Diagonal up-right
    for (int row = M - 1; row < N; ++row) {
        for (int col = 0; col <= N - M; ++col) {
            score += evaluateWindow(s, row, col, -1, 1, M, ai, opponent);
        }
    }

    return score;
}

double AIPlayer::evaluateWindow(const GameState& s,
                                int row, int col,
                                int dr, int dc,
                                int M,
                                char ai, char opponent) const {
    int aiCount = 0;
    int oppCount = 0;

    for (int i = 0; i < M; ++i) {
        int r = row + i * dr;
        int c = col + i * dc;
        char cell = s.getBoard().getCell(r, c);

        if (cell == ai) aiCount++;
        else if (cell == opponent) oppCount++;
    }

    if (aiCount > 0 && oppCount > 0) return 0.0;
    if (aiCount > 0) return std::pow(10.0, aiCount);
    if (oppCount > 0) return -std::pow(10.0, oppCount);
    return 0.0;
}