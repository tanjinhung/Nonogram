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
#### Play button
1. Pressing the Play button shows profiles of players. Profiles consist of:
   1. Profile Name
   2. Profile Image
   3. the Level Completed
   4. the Fastest Time to complete a puzzle
   5. the Total Time Played
   6. delete button
   7. select button
2. Upon selecting a profile, A choice of difficulty can be chosen.
   1. Easy (5x5)
   2. Normal (10x10)
   3. Hard (15x15)
   4. Extreme (20x20)
   5. Hell (30x30)
   6. Custom
   7. Highscore
3. Selecting a difficulty will put user into the play screen.
   1. There will be buttons for Exit, Clear, Reset(Regenerate the game), and Finish.
   2. The center will be the the Play area.
4. When the user thinks that they have completed the game, the finish button is to be pressed.
   1. Verify the user-input solution with internal solutions which is found by the solver
   2. Shows a winning screen if the user-input solution is correct.
   3. The winning screen consists of:
      * the difficulty of the level
      * the time taken to complete the puzzle
      * a button for retry, reset, and quit.
5. The highscore is the speed at which that the user have solve each level including custom level with the custom grid.

#### Level editor
1. The level editor allows the user to craete their own problems.
   1. Have a Clear button, Resize button, Publish button, and Exit button.
   2. Puts user into the editor screen.
   3. When user adds a block to the grid, the hint is updated to the current state of the grid.
   4. Save the user-edited play screen.

#### Control Scheme
| Controls | Function |
| :---: | :--- |
| `LMB` | Place a block on a square |
| `RMB` | Remove a (placeholder) block on a square |
| `MMB` | Place a placeholder block on a square |
