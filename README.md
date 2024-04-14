# Nonogram GUI Generator and Solver


```
Problem:                            Answer:
. . . . . . . . . . 5 1 2           # # # # # . # . # # 5 1 2
. . . . . . . . . . 10              # # # # # # # # # # 10
. . . . . . . . . . 2 6             # # . # # # # # # . 2 6
. . . . . . . . . . 1 4             # . . . # # # # . . 1 4
. . . . . . . . . . 3 1             . . . . # # # . . # 3 1
. . . . . . . . . . 1 1 2           . . # . . # . . # # 1 1 2
. . . . . . . . . . 3 3             . # # # . . . # # # 3 3
. . . . . . . . . . 3 4             . # # # . . # # # # 3 4
. . . . . . . . . . 1 5             . . # . . # # # # # 1 5
. . . . . . . . . . 6               . . . . # # # # # # 6
4 3 2 3 5 5 5 3 3 2                 4 3 2 3 5 5 5 3 3 2
  2 4 2   2 3 4 5 6                   2 4 2   2 3 4 5 6
```

### Create a Nonogram Generator and Solver.

##### Game Logic generator
1. Select a square grid that can be set by the user. (Hardness Level)
2. Generate a random set that is able to fit into a grid space.
3. The problem can be written into sets that denotes the X and y axis.
4. This can be further compose into a set of sets.
5. Rendering first in an ASCII format.
6. Pressing a space results in the toggling between a '.' and a '#'.
8. Proceed to create a GUI for the game.

##### GUI
1. Select between Sizable and Fixed window.
2. Have a button that onPress regenerate the game.
3. Have a grid of turntables that onPress flip into a colored block.
4. Have a winning screen that denotes when the game is complete.
5. Winning screen close button is a regenerate.
6. Have a Level select and a Custom Level.
7. Generate Pixel art puzzle.

##### Solver
1. Reference others' code.
2. Attempt to solve using own logic.
3. Store the solution such that it can be parsed.
4. Parsed the solution to determine the user input is correct.
5. Link to GUI to show winning screen. 