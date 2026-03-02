#include "GameState.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>  // For std::invalid_argument

// Constructor
GameState::GameState(int n, int m, char firstPlayer)
    : board(new Board(n))  // Use new instead of make_unique for C++11
    , currentPlayer(firstPlayer)
    , mToWin(m)
    , gameOver(false)
    , winner('\0') {
    // Validate inputs
    if (n < 3 || n > 10) {
        throw std::invalid_argument("Grid size must be between 3 and 10");
    }
    if (m <= 1 || m > n) {
        throw std::invalid_argument("M must be between 2 and N");
    }
    if (firstPlayer != 'X' && firstPlayer != 'O') {
        throw std::invalid_argument("Player must be 'X' or 'O'");
    }
}

// Destructor - needed for std::unique_ptr with incomplete type
GameState::~GameState() = default;

// Copy constructor
GameState::GameState(const GameState& other)
    : board(new Board(*other.board))  // Use new instead of make_unique
    , currentPlayer(other.currentPlayer)
    , mToWin(other.mToWin)
    , gameOver(other.gameOver)
    , winner(other.winner) {}

// Move constructor (optional but good to have)
GameState::GameState(GameState&& other) noexcept
    : board(std::move(other.board))
    , currentPlayer(other.currentPlayer)
    , mToWin(other.mToWin)
    , gameOver(other.gameOver)
    , winner(other.winner) {}

// Copy assignment operator
GameState& GameState::operator=(const GameState& other) {
    if (this != &other) {
        board.reset(new Board(*other.board));
        currentPlayer = other.currentPlayer;
        mToWin = other.mToWin;
        gameOver = other.gameOver;
        winner = other.winner;
    }
    return *this;
}

// Move assignment operator
GameState& GameState::operator=(GameState&& other) noexcept {
    if (this != &other) {
        board = std::move(other.board);
        currentPlayer = other.currentPlayer;
        mToWin = other.mToWin;
        gameOver = other.gameOver;
        winner = other.winner;
    }
    return *this;
}

bool GameState::applyMove(int column) {
    // Check if game is already over
    if (gameOver) {
        return false;
    }
    
    // Check if move is valid
    if (!isValidMove(column)) {
        return false;
    }
    
    // Convert from 1-based to 0-based indexing
    int colIndex = column - 1;
    
    // Place the disk
    if (!board->placeDisk(colIndex, currentPlayer)) {
        return false;
    }
    
    // Check for win
    if (checkWin()) {
        gameOver = true;
        winner = currentPlayer;
        return true;
    }
    
    // Check for draw (board full)
    if (checkDraw()) {
        gameOver = true;
        winner = '\0';  // No winner in draw
        return true;
    }
    
    // Switch player for next turn
    switchPlayer();
    
    return true;
}

bool GameState::isValidMove(int column) const {
    // Check if game is over
    if (gameOver) {
        return false;
    }
    
    // Check column range (1-based)
    if (column < 1 || column > board->getSize()) {
        return false;
    }
    
    // Check if column has space
    int colIndex = column - 1;
    return board->getTopRow(colIndex) >= 0;
}

void GameState::switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

bool GameState::checkWin() const {
    // Check each cell that contains the current player's piece
    for (int row = 0; row < board->getSize(); row++) {
        for (int col = 0; col < board->getSize(); col++) {
            char cell = board->getCell(row, col);
            if (cell == currentPlayer) {
                // Check all four directions from this cell
                if (checkHorizontal(row, col, currentPlayer) ||
                    checkVertical(row, col, currentPlayer) ||
                    checkDiagonalDown(row, col, currentPlayer) ||
                    checkDiagonalUp(row, col, currentPlayer)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool GameState::checkHorizontal(int row, int col, char player) const {
    int count = 0;
    int size = board->getSize();
    
    // Check to the right
    for (int c = col; c < size && c < col + mToWin; c++) {
        if (board->getCell(row, c) == player) {
            count++;
        } else {
            break;
        }
    }
    
    return count >= mToWin;
}

bool GameState::checkVertical(int row, int col, char player) const {
    int count = 0;
    
    // Check upward (since row 0 is bottom)
    for (int r = row; r >= 0 && r > row - mToWin; r--) {
        if (board->getCell(r, col) == player) {
            count++;
        } else {
            break;
        }
    }
    
    return count >= mToWin;
}

bool GameState::checkDiagonalDown(int row, int col, char player) const {
    int count = 0;
    int size = board->getSize();
    
    // Check diagonal going up-right (increasing row, increasing col)
    // Since row 0 is bottom, increasing row means going UP
    for (int i = 0; i < mToWin; i++) {
        int r = row + i;  // Moving UP
        int c = col + i;  // Moving RIGHT
        if (r < size && c < size) {
            if (board->getCell(r, c) == player) {
                count++;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    
    return count >= mToWin;
}

bool GameState::checkDiagonalUp(int row, int col, char player) const {
    int count = 0;
    int size = board->getSize();
    
    // Check diagonal going down-right (decreasing row, increasing col)
    // Since row 0 is bottom, decreasing row means going DOWN
    for (int i = 0; i < mToWin; i++) {
        int r = row - i;  // Moving DOWN
        int c = col + i;  // Moving RIGHT
        if (r >= 0 && c < size) {
            if (board->getCell(r, c) == player) {
                count++;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    
    return count >= mToWin;
}

bool GameState::checkDraw() const {
    // Simple draw detection: board is full
    return board->isFull();
}