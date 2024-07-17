#include "editorlevel.h"

EditorLevel::EditorLevel(
    const std::vector<std::vector<int> > &solutionGrid,
    const std::vector<std::vector<int> > &currentGrid,
    const std::vector<std::vector<int> > &rowHint,
    const std::vector<std::vector<int> > &colHint,
    const QString &difficulty,
    int size
) : Level(solutionGrid, currentGrid, rowHint, colHint, difficulty, size)
{

}

void EditorLevel::setSolutionTile(int row, int col, int val)
{
    if (row >= 0 && row < getSize() && col >= 0 && col < getSize()) {
        std::vector<std::vector<int>> &tempSolutionGrid = const_cast<std::vector<std::vector<int>>&>(getSolutionGrid());
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
                ++count;
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
                ++count;
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
