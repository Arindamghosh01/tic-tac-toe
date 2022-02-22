# tic-tac-toe
The classic Tic-Tac-Toe game (also called Noughts and Crosses) or Xs and Os in which two players seek in alternate turns to complete a row, a column, or a diagonal with either three O's or three X's drawn in the spaces of a grid of nine squares.

## Combinatorics
When considering only the state of the board, and after taking into account board symmetries (i.e. rotations and reflections), there are only 138 terminal board positions. A combinatorics study of the game shows that when "X" makes the first move every time, the game outcomes are as follows:[14]

- 91 distinct positions are won by (X)
- 44 distinct positions are won by (O)
- 3 distinct positions are drawn (often called a "cat's game")

## Minimax Algorithm
In this code, I've used minimax algorithm to help the computer where to go for the next move and win the puzzle.

Minimax is a kind of backtracking algorithm that is used in decision making and game theory to find the optimal move for a player, assuming that your opponent also plays optimally.

I took reference from [this](https://www.youtube.com/watch?v=l-hh51ncgDI) wonderful video resource for implementing minimax algorithm.

## Installation
### For Windows
If you have make utility installed then compile it with
~~~~
make
~~~~

Or simply compile it with
~~~~
g++ main.cpp -o main.exe
~~~~

For Running it use
~~~~
main.exe
~~~~

### For Linux and Mac
Use
~~~~
make && ./main
~~~~
