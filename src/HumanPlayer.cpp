/*
 * Author: Katarina Kruse
 * Last modified: March 1, 2026
 *
 * Description:
 *   Implementation of the HumanPlayer class. Prompts the user for a column number,
 *   validates input, and returns the chosen column (1‑based). Handles invalid
 *   input (non‑numeric or out of range) by re‑prompting.
 *
 * Notes:
 *   - getMove() blocks until valid input is received.
 *   - Input is read as a string to avoid issues with non‑numeric characters.
 *   - The function relies on GameState::getWidth() to know the board size.
 */

#include "HumanPlayer.h"
#include "GameState.h"
#include <iostream>
#include <string>

HumanPlayer::HumanPlayer(char id) : Player(id) {}

int HumanPlayer::getMove(const GameState& state) const {
    while (true) {
        std::string input;
        std::cout << "Enter column number to drop puck into: ";
        std::cin >> input;

        int col;
        try {
            col = std::stoi(input);
        } catch (...) {
            std::cout << "invalid input" << std::endl;
            continue;
        }

        int maxCol = state.getWidth();
        if (col < 1 || col > maxCol) {
            std::cout << "out of range" << std::endl;
            continue;
        }

        return col;   // 1‑based column
    }
}