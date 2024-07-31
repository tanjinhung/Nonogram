# Nonogram Game

![Main Image](img/Nonogram.png)

## Introduction
Nonogram Puzzle Game is a logic-based number puzzle game. The objective is to fill in cells in a grid based on the provided hints for each row and column. The game also includes a level editor, allowing users to create their own puzzles.

## Features
- **Gameplay**: Solve Nonogram puzzles of various difficulties.
- **Level Editor**: Create and publish custom puzzles.
- **Profile Management**: Create and manage user profiles.
- **Highscores**: View and compare scores.
- **Persistence**: Load created puzzles from csv files.

## Getting Started
### Prerequisites
- Qt framework [>install here](https://www.qt.io/download-qt-installer-oss)

### Building the project
1. Clone the Repository.
```bash
    git clone https://github.com/tanjinhung/Nonogram.git
```
2. Open the project in Qt Creator.
3. Build and Run the project.

## Project Structure
```
Nonogram/
�   .gitignore
�   checksheet.xlsx
�   event_flow.md
�   Nonogram.zip
�   README.md
�   scenerio.md
�   spec_sheet.md
�   tree.txt
�   
����diagram
�   �   activity_diagram.drawio
�   �   class.drawio
�   �   class_bce.drawio
�   �   class_design.drawio
�   �   class_design_re.drawio
�   �   communication.drawio
�   �   diagram.drawio
�   �   diagram_flow.drawio
�   �   Scene_1.drawio
�   �   Scene_2.drawio
�   �   Scene_3.drawio
�   �   sequence_diagram.drawio
�   �   sequence_diagram_re.drawio
�   �   usecase_diagram.drawio
�   �   
�   ����img
�           activity_diagram.png
�           class_design_re.png
�           communication.png
�           diagram.png
�           diagram_flow.png
�           Scene_1.png
�           Scene_2.png
�           Scene_3.png
�           sequence_diagram_re.png
�           usecase_diagram.png
�           
����img
�       Nonogram.png
�       
����qt
    ����Nonogram
            .gitignore
            1.png
            10.png
            2.png
            3.png
            4.png
            5.png
            6.png
            7.png
            8.png
            9.png
            clickablelabel.cpp
            clickablelabel.h
            csvleveldao.cpp
            csvleveldao.h
            csvscoredao.cpp
            csvscoredao.h
            csvuserdao.cpp
            csvuserdao.h
            customscrollarea.cpp
            customscrollarea.h
            customtile.cpp
            customtile.h
            difficulty.h
            editorflag.h
            editorlevel.cpp
            editorlevel.h
            frame.cpp
            frame.h
            gamecontroller.cpp
            gamecontroller.h
            level.cpp
            level.h
            leveldao.h
            main.cpp
            Nonogram.pro
            Nonogram.pro.user
            Nonogram.pro.user.06ca88e
            nonogramsolver.h
            profilecontroller.cpp
            profilecontroller.h
            resource.qrc
            score.cpp
            score.h
            scoredao.h
            user.cpp
            user.h
            userdao.h
            useritemwidget.cpp
            useritemwidget.h
```