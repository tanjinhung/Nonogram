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
1. Have a start screen that shows a Play button, Level editor, Profiles, and Setting button.
#### Play button
1. Pressing the Play button shows profiles of three recent players on a separate screen with a next page button. Profiles consist of:
   1. the player name.
   2. the Level completed.
   3. the Lowest Time to complete a puzzle.
2. Upon selecting a profile, A choice of difficulty can be chosen.
   1. Easy (5x5)
   2. Normal (10x10)
   3. Hard (15x15)
   4. Extreme (20x20)
   5. Hell (30x30)
   6. Custom (NxN)
   7. Highscore
3. Selecting a difficulty will put user into the play screen.
   1. There will be buttons for Exit, Clear, Reset(Regenerate the game), and Finish.
   2. The center will be the the Play area.
4. When the user thinks that they have completed the game, the finish button is to be pressed.
   1. Verify the user-input solution with internal solutions which is found by the solver
   2. Shows a winning screen if the user-input solution is correct.
      1. The winning screen consists of:
         * the difficulty of the level
         * the time taken to complete the puzzle
         * a button for retry, reset, and quit.
5. The highscore is the speed at which that the user have solve each level including custom level with the custom grid.

#### Level editor
1. The level editor allows the user to craete their own problems.
   1. Have a color selector, Save button, and Exit button.
   2. Puts user into the editor screen.
   3. When user adds a block to the grid, the hint is updated to the current state of the grid.
   4. Save the user-edited play screen.

#### Profiles
1. Have a create button.
2. Have a lists of Created users. The listings consists of:
   1. Profile picture
   2. A user name
   3. Time played
   4. Delete button
   5. Edit button