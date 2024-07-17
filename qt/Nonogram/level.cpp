#include "level.h"
#include <QDebug>

Level::Level(const std::vector<std::vector<int> > solutionGrid,
             const std::vector<std::vector<int> > currentGrid,
             const std::vector<std::vector<int>> rowHint,
             const std::vector<std::vector<int>> colHint,
             const QString &difficulty,
             int size
             )
    : solutionGrid(std::move(solutionGrid)),
    currentGrid(std::move(currentGrid)),
    rowHint(std::move(rowHint)),
    colHint(std::move(colHint)),
    difficulty(difficulty),
    size(size)
{
}

const std::vector<std::vector<int>>& Level::getSolutionGrid() const
{
    return solutionGrid;
}

void Level::setSolutionGrid(const std::vector<std::vector<int>> &newSolutionGrid)
{
    solutionGrid = newSolutionGrid;
}

const std::vector<std::vector<int>>& Level::getCurrentGrid() const
{
    return currentGrid;
}

void Level::setCurrentTile(int row, int col, int val)
{
    if (row >= 0 && row < size && col >= 0 && col < size)
    {
        currentGrid[row][col] = val;
    }
}

const std::vector<std::vector<int>>& Level::getRowHint() const
{
    return rowHint;
}

void Level::setRowHint(const std::vector<std::vector<int>> &newRowHint)
{
    rowHint = newRowHint;
}

const std::vector<std::vector<int>>& Level::getColHint() const
{
    return colHint;
}

void Level::setColHint(const std::vector<std::vector<int>> &newColHint)
{
    colHint = newColHint;
}

QString Level::getDifficulty() const
{
    return difficulty;
}

void Level::setDifficulty(const QString &newDifficulty)
{
    difficulty = newDifficulty;
}

int Level::getSize() const
{
    return size;
}

void Level::setSize(int newSize)
{
    size = newSize;
}

void Level::printCurrentGrid() const
{
    qDebug() << "Current Grid:";
    for (const auto &row : currentGrid)
    {
        QString rowStr;
        for (int cell : row)
        {
            rowStr += QString::number(cell) + " ";
        }
        qDebug() << rowStr.trimmed();
    }
}

void Level::printSolutionGrid() const
{
    qDebug() << "Solution Grid:";
    for (const auto &row : solutionGrid)
    {
        QString rowStr;
        for (int cell : row)
        {
            rowStr += QString::number(cell) + " ";
        }
        qDebug() << rowStr.trimmed();
    }
}

void Level::printRowHint() const
{
    qDebug() << "Row Hints:";
    for (const auto &hints : rowHint)
    {
        QString hintStr;
        for (int hint : hints)
        {
            hintStr += QString::number(hint) + " ";
        }
        qDebug() << hintStr.trimmed();
    }
}

void Level::printColHint() const
{
    qDebug() << "Column Hints:";
    for (const auto &hints : colHint)
    {
        QString hintStr;
        for (int hint : hints)
        {
            hintStr += QString::number(hint) + " ";
        }
        qDebug() << hintStr.trimmed();
    }
}
