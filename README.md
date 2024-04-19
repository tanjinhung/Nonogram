# Nonogram Game (ピクロス)


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

#### Functions
* User profie
* Level generator
* Level solver
* Level editor
* Create Level from Image
* Level Solve Speed

## The Game
1. Have a start screen that shows a Play button, Level editor, and Setting button.
2. Pressing the Play button shows 3 profile select screen.
   1. Shows the player name.
   2. Shows the Level completed.
   3. Shows the Lowest Time to complete a puzzle.
3. Upon selecting a profile, A choice of difficulty can be chosen.
   1. Easy (5x5)
   2. Normal (10x10)
   3. Hard (15x15)
   4. Extreme (20x20)
   5. Hell (30x30)
   6. Custom (NxN)
   7. Highscore
4. Selecting a difficulty will put user into the play screen.
   1. There will be buttons for Exit, Clear, Reset(Regenerate the game), and Finish.
   2. The center will be the the Play area.
5. When the user thinks that they have completed the game, the finish button is to be pressed.
   1. Verify the user-inputted solution with internal solutions
   2. Shows a winning screen if the user-inputted solution is correct.
      1. The winning screen consist of:
         * the difficulty of the level
         * the time taken to complete the puzzle
         * a button for retry, reset, and quit.
6. The level editor is the opposite of the level select.
   1. Have a color selector, Save button, and Exit button.
   2. Puts user into the a play screen that have no hints.
   3. When user adds a block to the board, the hint is updated to the current state of the board.
   4. Save the user-edited play screen.
7. The highscore is the speed at which that the user have solve each level including custom level with the custom grid.