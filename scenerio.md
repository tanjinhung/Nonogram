Scenerio

*Scene 1:*
In the "play screen", Alex sees a 5x5 grid as he had selected the easy difficulty. 
He sees along the row and column of the grid there exist hints of 1 3, 2, 3, 4, 5 for the row and 1 1, 3, 5, 5, 1 2 for the column
Alex had click on the square on row 5 column 5, making the square turn black from white.
The game is still ongoing so the system records the progress as ONGOING flag.
As Alex continues to click on the square on row 5 column 4, the system records them in a 2d matrix for the current grid.
While generating the puzzle, the system also had recorded down the solution's 2d matrix, which is then used to compare with the current 2d matrix.

*Scene 2:*
Alex decided to create a level. 
When Alex press the level editor button, the system prompted Alex for the name of the level that he is going to create.
After Alex named the level 'house', he is then prompted to select the grid size and difficulty of the level in which he selected the easy difficulty of a 5x5 grid.
After which Alex is greeted with the selected grid size without any hints.
This game is for editing so the system records the progress as EDITING flag.
Alex then proceed to click on the square on row 3 column 3 in which the system responses by first turning the square black and updating the hints on the row and column.
The hints on row becomes [ , , 1, , ] and the hints on column becomes [ , , 1, , ].
The system also updates the current grid's 2d matrix for later storage.

*Scene 3:*
In the "difficulty selection screen", Alex decided to choose the highscorce to display the best level that he had completed.
The system pulls the data fro m a file containing all the level that had completed and sorts it based on the completed times in ascending order group by the difficulty.
