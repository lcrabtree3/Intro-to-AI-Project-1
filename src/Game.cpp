#include "Game.h"
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>

Game::Game(int n, int m, int h) 
    : boardSize(n)
    , mToWin(m)
    , humanFirst(h == 1)
    , moveCount(0) {
    
    // Validate inputs
    if (n < 3 || n > 10) {
        throw std::invalid_argument("Grid size must be between 3 and 10");
    }
    if (m <= 1 || m > n) {
        throw std::invalid_argument("M must be between 2 and N");
    }
    
    // Determine first player
    char firstPlayer = (humanFirst) ? 'X' : 'O';
    
    // Create game state
    gameState = std::make_unique<GameState>(n, m, firstPlayer);
    
    // Create controller
    controller = std::make_unique<Controller>(*gameState);
    
    // Initialize players
    initializePlayers(humanFirst);
}

void Game::initializePlayers(bool humanMovesFirst) {
    // Create players
    humanPlayer = std::make_unique<HumanPlayer>('X');
    aiPlayer = std::make_unique<AIPlayer>('O', boardSize, mToWin);
    
    // Set current player based on who moves first
    if (humanMovesFirst) {
        currentPlayer = humanPlayer.get();
    } else {
        currentPlayer = aiPlayer.get();
    }
}

char Game::getPlayerSymbol(const Player* player) const {
    if (player == humanPlayer.get()) {
        return 'X';
    } else {
        return 'O';
    }
}

void Game::displayWelcome() const {
    std::cout << "\n";
    std::cout << "=====================================\n";
    std::cout << "         CONNECT " << mToWin << "\n";
    std::cout << "=====================================\n";
    std::cout << "Board size: " << boardSize << "x" << boardSize << "\n";
    std::cout << "Need to connect " << mToWin << " disks to win\n";
    std::cout << "Human: X  |  AI: O\n";
    
    if (humanFirst) {
        std::cout << "Human (X) goes first!\n";
    } else {
        std::cout << "AI (O) goes first!\n";
    }
    std::cout << "=====================================\n";
}

void Game::displayBoard() const {
    std::cout << "\n";
    std::cout << gameState->getBoard().toString();
    std::cout << "\n";
}

void Game::displayTurn() const {
    char symbol = getPlayerSymbol(currentPlayer);
    std::cout << "-------------------------------------\n";
    std::cout << "Turn " << (moveCount + 1) << " | ";
    
    if (currentPlayer == humanPlayer.get()) {
        std::cout << "Human (X)";
    } else {
        std::cout << "AI (O)";
    }
    std::cout << "'s turn\n";
    std::cout << "-------------------------------------\n";
}

void Game::displayResult() const {
    std::cout << "\n";
    std::cout << "=====================================\n";
    std::cout << "         GAME OVER\n";
    std::cout << "=====================================\n";
    
    char winner = gameState->getWinner();
    if (winner == 'X') {
        std::cout << " Human (X) wins! \n";
    } else if (winner == 'O') {
        std::cout << " AI (O) wins! \n";
    } else {
        std::cout << " Game ended in a draw! \n";
    }
    
    std::cout << "Total moves: " << moveCount << "\n";
    std::cout << "=====================================\n";
    
    std::cout << "\nFinal board:\n";
    displayBoard();
}

bool Game::processMove(int column) {
    bool moveApplied = controller->applyMove(column);
    
    if (moveApplied) {
        moveCount++;
        return true;
    }
    
    return false;
}

bool Game::checkGameOver() {
    if (gameState->isGameOver()) {
        displayResult();
        return true;
    }
    return false;
}

void Game::run() {
    // Display welcome message
    displayWelcome();
    
    // Display initial empty board
    displayBoard();
    
    // Main game loop
    while (!gameState->isGameOver()) {
        // Display whose turn it is
        displayTurn();
        
        int column = -1;
        bool validMove = false;
        
        // Get move from current player
        if (currentPlayer == humanPlayer.get()) {
            // Human player - loop until valid move
            while (!validMove) {
                column = currentPlayer->getMove(*gameState);
                
                if (column < 1 || column > boardSize) {
                    std::cout << " Invalid column! Please enter a number between 1 and " << boardSize << ".\n";
                    continue;
                }
                
                validMove = processMove(column);
                
                if (!validMove) {
                    std::cout << " Column " << column << " is full! Please choose another column.\n";
                }
            }
        } else {
            // AI player - add a small delay to make it feel more natural
            std::cout << "AI is thinking";
            std::cout.flush();
            
            // Simple thinking animation
            for (int i = 0; i < 3; i++) {
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                std::cout << ".";
                std::cout.flush();
            }
            std::cout << "\n";
            
            // Get AI move
            column = currentPlayer->getMove(*gameState);
            validMove = processMove(column);
            
            // AI should always return a valid move, but just in case
            if (!validMove) {
                std::cout << "  AI returned an invalid move. Finding a valid column...\n";
                
                // Fallback: find first valid column
                for (int c = 1; c <= boardSize; c++) {
                    if (gameState->isValidMove(c)) {
                        column = c;
                        validMove = processMove(column);
                        break;
                    }
                }
            }
            
            std::cout << "AI chose column " << column << "\n";
        }
        
        // Display updated board
        displayBoard();
        
        // Check if game ended
        if (checkGameOver()) {
            break;
        }
        
        // Switch player for next turn
        if (currentPlayer == humanPlayer.get()) {
            currentPlayer = aiPlayer.get();
        } else {
            currentPlayer = humanPlayer.get();
        }
    }
}