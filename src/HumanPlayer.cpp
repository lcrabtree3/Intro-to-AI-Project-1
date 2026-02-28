#include "HumanPlayer.h"
#include "GameState.h"
#include <iostream>
#include <string>

/*
 * Author: Katarina Kruse
 * Created: February 27, 2026
 * Last Modified: February 27, 2026
 *
 * Description:
 * Implementation of HumanPlayer::chooseMove.
 *
 * Notes:
 * This function prompts the user for a column number (1 to N),
 * validates numeric input, ensures the column is within range,
 * and returns the zero-based column index.
 *
 * It does not mutate GameState. It only reads the game state
 * (when GameState provides accessors) and returns a decision.
 *
 * The loop continues until valid input is received.
 */

int HumanPlayer::chooseMove(const GameState& state) const {
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

        /*
         * GameState must provide getWidth() (or equivalent) to report
         * board dimensions. This allows us to validate the column
         * against the game configuration instead of hardcoding values.
         */
        int maxCol = state.getWidth();

        if (col < 1 || col > maxCol) {
            std::cout << "out of range" << std::endl;
            continue;
        }

        int columnIndex = col - 1;
        return columnIndex;
    }
}