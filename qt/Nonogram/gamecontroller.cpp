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
          "",
          0
          ),
    elapsedPausedTime(0),
    isTimerRunning(false),
    currentUser(0, "", 0, 0, 0, 0)
{
}

void GameController::handleDifficulty(Difficulty difficulty, Flag flag)
{
    switch (flag) {
    case Flag::DEFAULT:
        currentDifficulty = difficulty;
        generateLevel();
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
        difficultyToString(difficulty), size);
    emit levelEditorCreated(editorLevel);
}

void GameController::registerScore(int userId)
{
    qDebug() << "registerScore called";
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

void GameController::createLevelEditor()
{
    createLevelEditor(Difficulty::Easy);
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

    newLevel.setCurrentTile(row, col, val);
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
    for (size_t i = 0; i < currentGrid.size(); ++i) {
        for (size_t j = 0; j < currentGrid[i].size(); ++j) {
            newLevel.setCurrentTile(i, j, 0);
        }
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
