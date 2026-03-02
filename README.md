# Connect M

A command-line implementation of the Connect M game with an AI opponent using alpha-beta pruning.

## Compilation

Run `make` to build the executable `connectM` and all test programs.

## Usage

./connectM N M H
text


- `N` : size of the quadratic board (3‑10)
- `M` : number of disks to connect contiguously (2‑N)
- `H` : 1 if the human moves first, 0 if the computer moves first

Example:

./connectM 5 4 1
text


The human player uses `X`, the AI uses `O`. Columns are numbered from 1 to N.

## Testing

Run `make test` to execute all unit tests (board, game state, AI, controller, integration).