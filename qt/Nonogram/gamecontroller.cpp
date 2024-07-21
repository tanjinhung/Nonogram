#include "csvleveldao.h"
#include "csvscoredao.h"
#include "editorlevel.h"
#include "gamecontroller.h"
#include <QRandomGenerator>
#include <QDebug>

GameController::GameController(QObject *parent)
    : QObject(parent), currentDifficulty(Difficulty::Easy),
    newLevel(
          std::vector<std::vector<int>>(),
          std::vector<std::vector<int>>(),
          std::vector<std::vector<int>>(),
          std::vector<std::vector<int>>(),
          "", 0),
    elapsedPausedTime(0),
    isTimerRunning(false),
    currentUser(0, "", 0, 0, 0, 0)
{
}

void GameController::handleDifficulty(Difficulty difficulty)
{
    switch (flag) {
    case Flag::DEFAULT:
        currentDifficulty = difficulty;
        if (currentDifficulty != Difficulty::Custom) {
            generateLevel();
        } else {
            emit showCustomLevel();
        }
        break;
    case Flag::EDITING:
        createLevelEditor(difficulty);
        break;
    default:
        break;
    }
}

void GameController::generateLevel()
{
    newLevel = generatePuzzle(currentDifficulty);
    elapsedPausedTime = 0;

    newLevel.printSolutionGrid();
    emit levelCreated(newLevel);
    playTimer.start();
    isTimerRunning = true;
}

void GameController::createLevelEditor(Difficulty difficulty)
{
    int size = static_cast<int>(difficulty);
    std::vector<std::vector<int>> emptyGrid(size, std::vector<int>(size, 0));
    editorLevel = new EditorLevel(
        emptyGrid, emptyGrid, {}, {},
        difficultyToString(difficulty), size, "untitled");
    emit levelEditorCreated(*editorLevel);
}

void GameController::printAllLevels() const {
    CSVLevelDAO levelDAO("level.csv");
    std::vector<EditorLevel> levels = levelDAO.getAllLevels();

    for (const EditorLevel &level : levels) {
        qDebug() << "Level Name:" << level.getLevelName()
                 << "Difficulty:" << level.getDifficulty();

        qDebug() << "Row Hints:";
        for (const auto &rowHint : level.getRowHint()) {
            QString hintStr;
            for (int hint : rowHint) {
                hintStr += QString::number(hint) + " ";
            }
            qDebug() << hintStr.trimmed();
        }

        qDebug() << "Column Hints:";
        for (const auto &colHint : level.getColHint()) {
            QString hintStr;
            for (int hint : colHint) {
                hintStr += QString::number(hint) + " ";
            }
            qDebug() << hintStr.trimmed();
        }
    }
}

void GameController::registerScore(int userId)
{
    CSVScoreDAO scoreDAO("score.csv");
    int newScoreId = scoreDAO.getNextScoreId();
    emit getCurrentUser(userId);
    Score newScore(newScoreId, currentUser.getName(), elapsedPausedTime, difficultyToString(currentDifficulty));
    scoreDAO.insert(newScore);
}

void GameController::handleReturnUser(User user)
{
    currentUser = user;
}

void GameController::createLevelEditor(Flag newFlag)
{
    flag = newFlag;
    createLevelEditor(Difficulty::Easy);
}

void GameController::handleUpdateFlag(Flag newflag)
{
    flag = newflag;
}

void GameController::handlePublishLevel()
{
    editorLevel->finalizeHint();
    CSVLevelDAO levelDAO("level.csv");

    QString levelName = editorLevel->getLevelName();

    if (levelName.isEmpty()) {
        levelName = "untitled";
        levelName = levelDAO.generateUniqueLevelName(levelName);
        editorLevel->setLevelName(levelName);
    }
    if (levelDAO.levelNameExists(levelName)) {
        levelName = levelDAO.generateUniqueLevelName(levelName);
        editorLevel->setLevelName(levelName);
    }

    levelDAO.insert(*editorLevel);
}

void GameController::handleLevelName(QString levelName)
{
    editorLevel->setLevelName(levelName);
}

void GameController::handleTileClicked(int button, CustomTile *tile)
{
    int row = tile->getRow();
    int col = tile->getCol();

    int val = 0;
    switch (button) {
    case 0: // LMB
        val = 1;
        tile->setColor(Qt::black);
        break;
    case 1: // RMB
        val = 0;
        tile->setColor(Qt::white);
        break;
    case 2: // MMB
        val = -1;
        tile->drawX();
        break;
    default:
        val = 0;
    }

    switch (flag) {
    case Flag::DEFAULT:
        newLevel.setCurrentTile(row, col, val);
        break;
    case Flag::EDITING:
        editorLevel->setSolutionTile(row, col, val);
        break;
    default:
        break;
    }
}

void GameController::handleFinishGame()
{
    bool isFinished = true;
    const std::vector<std::vector<int>> &currentGrid = newLevel.getCurrentGrid();
    const std::vector<std::vector<int>> &solutionGrid = newLevel.getSolutionGrid();

    if (currentGrid.size() != solutionGrid.size()) {
        qDebug() << "Size is not the same!";
        isFinished = false;
    } else {
        for (size_t i = 0; i < currentGrid.size(); ++i) {
            for (size_t j = 0; j < currentGrid[i].size(); ++j) {
                int currentValue = (currentGrid[i][j] == -1) ? 0 : currentGrid[i][j];
                if (currentValue != solutionGrid[i][j]) {
                    isFinished = false;
                    break;
                }
            }
            if (!isFinished) break;
        }
    }

    // Stop the timer and calculate the elapsed time
    if (isTimerRunning) {
        elapsedPausedTime += playTimer.elapsed();
        isTimerRunning = false;
    }

    emit levelChecked(isFinished);
}

void GameController::handleClearGrid()
{
    const std::vector<std::vector<int>> &currentGrid = newLevel.getCurrentGrid();
    const std::vector<std::vector<int>> &solutionGrid = editorLevel->getSolutionGrid();

    switch (flag) {
    case Flag::DEFAULT:
        for (size_t i = 0; i < currentGrid.size(); ++i) {
            for (size_t j = 0; j < currentGrid[i].size(); ++j) {
                newLevel.setCurrentTile(i, j, 0);
            }
        }
        break;
    case Flag::EDITING:
        for (size_t i = 0; i < solutionGrid.size(); ++i) {
            for (size_t j = 0; j < solutionGrid[i].size(); ++j) {
                editorLevel->setSolutionTile(i, j, 0);
            }
        }
        break;
    default:
        break;
    }
}

void GameController::resumeTimer()
{
    if (!isTimerRunning) {
        playTimer.start(); // Restart the timer
        isTimerRunning = true; // Set the timer running flag to true
    }
}

Level GameController::generatePuzzle(Difficulty difficulty)
{
    int size = static_cast<int>(difficulty);
    std::vector<std::vector<int>> solutionGrid(size, std::vector<int>(size, 0));
    std::vector<std::vector<int>> currentGrid(size, std::vector<int>(size, 0));
    std::vector<std::vector<int>> rowHints(size);
    std::vector<std::vector<int>> colHints(size);

    // Randomly generate the solution grid
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            solutionGrid[i][j] = QRandomGenerator::global()->bounded(100) < 70 ? 1 : 0;
        }
    }

    // Calculate row hints
    for (int i = 0; i < size; ++i) {
        int count = 0;
        for (int j = 0; j < size; ++j) {
            if (solutionGrid[i][j] == 1) {
                count++;
            } else {
                if (count > 0) {
                    rowHints[i].push_back(count);
                    count = 0;
                }
            }
        }
        if (count > 0) {
            rowHints[i].push_back(count);
        }
    }

    // Calculate column hints
    for (int j = 0; j < size; ++j) {
        int count = 0;
        for (int i = 0; i < size; ++i) {
            if (solutionGrid[i][j] == 1) {
                count++;
            } else {
                if (count > 0) {
                    colHints[j].push_back(count);
                    count = 0;
                }
            }
        }
        if (count > 0) {
            colHints[j].push_back(count);
        }
    }

    QString difficultyStr = difficultyToString(difficulty);
    return Level(solutionGrid, currentGrid, rowHints, colHints, difficultyStr, size);
}
