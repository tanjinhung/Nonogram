# Event Flow

### Usecase 1 : Creating a user
---------------------------------
**actor**            : player  
**pre-ops**          : "Profile Selection" screen  
**post-ops**         : System records entry  
**Basic flow**       :   
1. Player press "create profile" button.
2. System overlays "profile creation" screen.
3. Player inputs username and selects profile picture.
4. System overlays "confirmation" screen.
5. Player confirms creation.
**Alternate flow**   :  
3a. If username input is blank, 
   3a1. System alerts player for empty input.
   3a2. Go to *basic flow 2*.
3b. If username is a duplicate,
   3b1. System alerts player for duplicated input.
   3b2. Go to *basic flow 2*.
**Exception flow**   :  
5a. Canceling puts player back to "Profile Selection" screen.

### Usecase 2 : Deleting a user
---------------------------------
**actor**            : player  
**pre-ops**          : "Profile Selection" screen  
**post-ops**         : System deletes entry    
**flow**             : 
1. Player presses "delete profile" button.
2. System overlays "confirmation" screen.
3. Player confirms deletion.
4. System searches for entry.
**Exception flow**   :  
3a. Cenceling puts player back to "Profile Selection" screen.

### Usecase 3 : Creating play screen
------------------------------------
**actor**            : player  
**pre-ops**          : "difficulty selection" screen  
**post-ops**         : System switches screen to Play screen  
**flow**             :  
1. Player selects a difficulty.
2. System sets the size of the grid to the difficulty.
3. System generates a puzzle that fits to the size of the grid.
4. System verifies the solvability of the puzzle.
5. System starts a timer to record the time.
**Alternate flow**   :  
4a. If unsolvable,
   4a1. go to *basic flow 2*.
 
### Usecase 4 : Finishing a Game
----------------------------------
**actor**            : player  
**pre-ops**          : "play" screen  
**post-ops**         : System records time taken to complete the puzzle  
**flow**             :   
1. Player presses "finish" button.
2. System pauses the timer.
3. System solves the puzzle and store solution in memory.
4. System verify the user-input solution to the solution in memory.
5. System shows the result and score of the puzzle.

### Usecase 5 : Creating a Level
---------------------------------
**actor**            : player  
**pre-ops**          : Main Menu  
**post-ops**         : System stores the hints  
**flow**             :  
1. Player presses "Level Editor" button
2. Player determines a size of the grid.
3. System displays the grid to the specified size.
4. Player presses "publish" button.
5. System calculates the hints for the grid.
**Exception flow**   :  
3a. Player presses "exit" button.
3b. System switches screen to "Main Menu" without storing.

### Usecase 6 : Coloring a square
-----------------------------------
**actor**            : player  
**pre-ops**          : "play" screen  
**post-ops**         : System colors the selected square  
**flow**             :  
1. Player left clicks a square.
**alternate flow**   :
1a. If placeholder exists on the square
   1a1. system remove placeholder.
   1a2. go to *basic flow 1*.

### Usecase 7 : Decoloring a square
------------------------------------
**actor**            : player  
**pre-ops**          : "play" screen  
**post-ops**         : System decolors the selected square  
**flow**             :  
1. Player right clicks a square.
**alternate flow**   :
1a. If placeholder exists on the square
   1a1. system remove placeholder.
   1a2. go to *basic flow 1*.

### Usecase 8 : Marking a square
------------------------------------
**actor**            : player  
**pre-ops**          : "play" screen  
**post-ops**         : System marks the selected square with a placeholder  
**flow**             :  
1. Player middle clicks a square.
**exception flow**   :
1a. If the square is colored, placeholder cannot be placed.
