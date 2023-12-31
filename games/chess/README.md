# Simple Chess
A minimal example (+-400 lines of code) of implementing a chess game in _C++_.
This program sends the state of the chess board to std::out.

*Simple Chess* automatically draws on threefold repetitions, insufficient material, the fifty move rule and of course, when a player has no legal moves left. It also has an undo function implemented.

When this example is run in a terminal, it makes random moves for every player as an example on how to use this program.
You can easily make a playable chess game with this by changing the random move selection to something of your own (and maybe implementing a better interface than std::out)

## Executing Simple Chess
* Download/clone this git repository
* make
* ./chess
* hit enter to continue generating random moves.