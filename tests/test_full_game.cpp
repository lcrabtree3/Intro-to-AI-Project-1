/*
 * Description:
 *   Unit tests for the Game class. Verifies that the Game constructor
 *   correctly initializes with valid parameters without throwing exceptions.
 *
 * Notes:
 *   - Only tests constructor success; full game execution is covered by
 *     integration tests.
 *   - Uses a 5x5 board with win condition M=4 and human first (H=1).
 */

#include "Game.h"
#include <cassert>
#include <iostream>

void testGameConstructor() {
    try {
        Game game(5, 4, 1);
        std::cout << "testGameConstructor passed\n";
    } catch (...) {
        assert(false);
    }
}

int main() {
    testGameConstructor();
    std::cout << "All full game tests passed!\n";
    return 0;
}