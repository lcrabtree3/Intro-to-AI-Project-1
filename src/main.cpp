/*
 * Author: Katarina Kruse
 * Last modified: March 1, 2026
 *
 * Description:
 *   Main entry point for the Connect M game. Parses command-line arguments,
 *   validates them, creates a Game instance, and runs the game loop.
 *
 * Notes:
 *   - Expects exactly three arguments: N (grid size), M (win condition), H (who starts).
 *   - Exits with usage message if arguments are incorrect.
 *   - Catches and displays any exceptions thrown during game execution.
 */

#include "Game.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: connectM N M H\n"
                  << "  N: grid size (3‑10)\n"
                  << "  M: number of disks to connect (2‑N)\n"
                  << "  H: 1 if human first, 0 if computer first\n";
        return 1;
    }

    int N = std::atoi(argv[1]);
    int M = std::atoi(argv[2]);
    int H = std::atoi(argv[3]);

    try {
        Game game(N, M, H);
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}