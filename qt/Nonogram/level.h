#ifndef LEVEL_H
#define LEVEL_H

#include <QString>
#include <vector>

class Level
{
public:
    Level(
        const std::vector<std::vector<int>> solutionGrid,
        const std::vector<std::vector<int>> currentGrid,
        const std::vector<std::vector<int>> rowHint,
        const std::vector<std::vector<int>> colHint,
        const QString &difficulty,
        int size
        );

    const std::vector<std::vector<int>>& getSolutionGrid() const;
    void setSolutionGrid(const std::vector<std::vector<int>> &newSolutionGrid);

    const std::vector<std::vector<int>>& getCurrentGrid() const;
    void setCurrentTile(int row, int col, int val);

    const std::vector<std::vector<int>>& getRowHint() const;
    void setRowHint(const std::vector<std::vector<int>> &newRowHint);

    const std::vector<std::vector<int>>& getColHint() const;
    void setColHint(const std::vector<std::vector<int>> &newColHint);

    QString getDifficulty() const;
    void setDifficulty(const QString &newDifficulty);

    int getSize() const;
    void setSize(int newSize);

    // debug
    void printCurrentGrid() const;
    void printSolutionGrid() const;
    void printRowHint() const;
    void printColHint() const;

private:
    std::vector<std::vector<int>> solutionGrid;
    std::vector<std::vector<int>> currentGrid;
    std::vector<std::vector<int>> rowHint;
    std::vector<std::vector<int>> colHint;
    QString difficulty;
    int size;
};

#endif // LEVEL_H
