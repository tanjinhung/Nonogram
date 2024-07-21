#ifndef NONOGRAM_SOLVER_H
#define NONOGRAM_SOLVER_H

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class NonogramSolver
{
public:
    NonogramSolver(const std::vector<std::vector<int>> &rowHints, const std::vector<std::vector<int>> &colHints)
        : rowHints(rowHints), colHints(colHints), rows(rowHints.size()), cols(colHints.size())
    {
        grid.resize(rows, std::vector<int>(cols, -1)); // -1 indicates unfilled cells
    }

    bool solve()
    {
        return solveRow(0);
    }

    std::string toStr() const
    {
        std::ostringstream oss;
        for (const auto &row : grid)
        {
            for (int cell : row)
            {
                if (cell == 1)
                    oss << '#';
                else if (cell == 0)
                    oss << '.';
                else
                    oss << '?'; // Unfilled cells
            }
            oss << "\n";
        }
        return oss.str();
    }

private:
    const std::vector<std::vector<int>> rowHints;
    const std::vector<std::vector<int>> colHints;
    std::vector<std::vector<int>> grid;
    int rows;
    int cols;

    bool solveRow(int row)
    {
        if (row == rows)
        {
            return checkCols();
        }

        std::vector<int> hint = rowHints[row];
        std::vector<std::vector<int>> combinations;
        generateCombinations(hint, cols, combinations);

        for (const auto &comb : combinations)
        {
            std::copy(comb.begin(), comb.end(), grid[row].begin());
            if (solveRow(row + 1))
            {
                return true;
            }
        }

        return false;
    }

    bool checkCols() const
    {
        for (int col = 0; col < cols; ++col)
        {
            std::vector<int> colValues(rows);
            for (int row = 0; row < rows; ++row)
            {
                colValues[row] = grid[row][col];
            }
            if (!checkHint(colHints[col], colValues))
            {
                return false;
            }
        }
        return true;
    }

    bool checkHint(const std::vector<int> &hint, const std::vector<int> &values) const
    {
        size_t hintIndex = 0;
        int count = 0;
        for (int value : values)
        {
            if (value == 1)
            {
                ++count;
            }
            else
            {
                if (count > 0)
                {
                    if (hintIndex >= hint.size() || hint[hintIndex] != count)
                    {
                        return false;
                    }
                    ++hintIndex;
                    count = 0;
                }
            }
        }
        if (count > 0)
        {
            if (hintIndex >= hint.size() || hint[hintIndex] != count)
            {
                return false;
            }
            ++hintIndex;
        }
        return hintIndex == hint.size();
    }

    void generateCombinations(const std::vector<int> &hint, size_t length, std::vector<std::vector<int>> &combinations, std::vector<int> comb = {}, size_t index = 0)
    {
        if (index == hint.size())
        {
            if (comb.size() + hint.size() - 1 == length)
            {
                std::vector<int> fullComb(length, 0);
                int pos = 0;
                for (size_t i = 0; i < hint.size(); ++i)
                {
                    std::fill(fullComb.begin() + pos, fullComb.begin() + pos + hint[i], 1);
                    pos += hint[i];
                    if (i < hint.size() - 1)
                    {
                        ++pos;
                    }
                }
                combinations.push_back(fullComb);
            }
            return;
        }

        for (size_t i = 0; i <= length - (comb.size() + hint.size() - index); ++i)
        {
            std::vector<int> newComb = comb;
            newComb.insert(newComb.end(), i, 0);
            newComb.insert(newComb.end(), hint[index], 1);
            generateCombinations(hint, length, combinations, newComb, index + 1);
        }
    }
};

#endif // NONOGRAM_SOLVER_H
