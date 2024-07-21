#include "editorlevel.h"
#include "difficulty.h"
#include "qdebug.h"
#include "nonogramsolver.h"

EditorLevel::EditorLevel(
    const std::vector<std::vector<int> > &solutionGrid,
    const std::vector<std::vector<int> > &currentGrid,
    const std::vector<std::vector<int> > &rowHint,
    const std::vector<std::vector<int> > &colHint,
    const QString &difficulty,
    int size,
    const QString &levelName
    ) : Level(solutionGrid, currentGrid, rowHint, colHint, difficulty, size), levelName(levelName)
{

}

void EditorLevel::setSolutionTile(int row, int col, int val)
{
    if (row >= 0 && row < getSize() && col >= 0 && col < getSize()) {
        std::vector<std::vector<int>> &tempSolutionGrid
            = const_cast<std::vector<std::vector<int>>&>(getSolutionGrid());
        tempSolutionGrid[row][col] = val;
    }
}

void EditorLevel::finalizeHint()
{
    const std::vector<std::vector<int>> tempSolutionGrid = getSolutionGrid();
    std::vector<std::vector<int>> tempRowHint(getSize());
    std::vector<std::vector<int>> tempColHint(getSize());

    // Calculate row hints
    for (int i = 0; i < getSize(); ++i)
    {
        int count = 0;
        for (int j = 0; j < getSize(); ++j)
        {
            if (tempSolutionGrid[i][j] == 1)
            {
                count++;
            }
            else if (count > 0)
            {
                tempRowHint[i].push_back(count);
                count = 0;
            }
        }
        if (count > 0)
        {
            tempRowHint[i].push_back(count);
        }
    }

    // Calculate column hints
    for (int j = 0; j < getSize(); ++j)
    {
        int count = 0;
        for (int i = 0; i < getSize(); ++i)
        {
            if (tempSolutionGrid[i][j] == 1)
            {
                count++;
            }
            else if (count > 0)
            {
                tempColHint[j].push_back(count);
                count = 0;
            }
        }
        if (count > 0)
        {
            tempColHint[j].push_back(count);
        }
    }

    setRowHint(tempRowHint);
    setColHint(tempColHint);
}

QString EditorLevel::getLevelName() const
{
    return levelName;
}

void EditorLevel::setLevelName(const QString &newLevelName)
{
    levelName = newLevelName;
}

Level EditorLevel::toLevel() const
{
    qDebug() << "Starting toLevel conversion";
    const int size = static_cast<int>(stringToDifficulty(getDifficulty()));
    std::vector<std::vector<int>> emptyGrid(size, std::vector<int>(size, 0));

    std::vector<std::vector<int>> rowHints = getRowHint();
    std::vector<std::vector<int>> colHints = getColHint();
    std::vector<std::vector<int>> solutionGrid = emptyGrid;

    try {
        NonogramSolver nonogramSolver(rowHints, colHints);

        qDebug() << "Nonogram solver initialized";

        if (nonogramSolver.solve()) {
            qDebug() << "Nonogram solved successfully";
            std::string solvedPuzzle = nonogramSolver.toStr();

            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    solutionGrid[i][j] = (solvedPuzzle[i * (size + 1) + j] == '#') ? 1 : 0;
                }
            }
        } else {
            qDebug() << "Nonogram solver failed to solve the puzzle";
        }
    } catch (const std::exception &e) {
        qDebug() << "Exception caught in Nonogram solver:" << e.what();
    }

    return Level(solutionGrid, emptyGrid, rowHints, colHints, getDifficulty(), size);
}
