#include "Board.hpp"
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;
Board::Board(int n)
{
    cols = new int[n];
    assert(cols != nullptr);
    size = n;
    queensInRow = new int[n];
    assert(queensInRow != nullptr);
    queensInMainDiagonal = new int[2 * n - 1];
    assert(queensInMainDiagonal != nullptr);
    queensInSecondaryDiagonal = new int[2 * n - 1];
    assert(queensInSecondaryDiagonal != nullptr);
    shuffle();
}
Board::~Board()
{
    clearAllDynamic();
}
Board::Board(const Board& b)
{
    copy(b);
}
Board& Board::operator=(const Board& b)
{
    if (this != &b)
    {
        clearAllDynamic();
        copy(b);
    }
    return *this;
}
void Board::copy(const Board& b)
{
    size = b.size;
    cols = new int[b.size];
    assert(cols != nullptr);
    queensInRow = new int[b.size];
    assert(queensInRow != nullptr);
    for (int i = 0; i < size; i++)
    {
        cols[i] = b.cols[i];
        queensInRow[i] = b.queensInRow[i];
    }
    queensInMainDiagonal = new int[2 * b.size - 1];
    assert(queensInMainDiagonal != nullptr);
    queensInSecondaryDiagonal = new int[2 * b.size - 1];
    assert(queensInSecondaryDiagonal != nullptr);
    for (int i = 0; i < size; i++)
    {
        queensInMainDiagonal[i] = b.queensInMainDiagonal[i];
        queensInSecondaryDiagonal[i] = b.queensInSecondaryDiagonal[i];
    }
}
void Board::clearAllDynamic()
{
    delete[] cols;
    delete[] queensInRow;
    delete[] queensInMainDiagonal;
    delete[] queensInSecondaryDiagonal;
}
void Board::shuffle()
{
    for (int i = 0; i < 2 * size - 1; i++)
    {
        queensInMainDiagonal[i] = 0;
        queensInSecondaryDiagonal[i] = 0;

        if (i < size)
        {
            queensInRow[i] = 0;
        }
    }
    for (int i = 0; i < size; i++)
    {
        cols[i] = rand() % size;//Random integer in the interval [0,size)
        queensInRow[cols[i]] += 1;
        addToMainDiagonal(cols[i], i, 1);
        addToSecondaryDiagonal(cols[i], i, 1);
    }
}
void Board::addToMainDiagonal(int row, int col, int value)
{
    if (row <= col)
    {
        queensInMainDiagonal[(size - 1) - abs(row - col)] += value;
    }
    else
    {
        queensInMainDiagonal[(size - 1) + abs(row - col)] += value;
    }
}
void Board::addToSecondaryDiagonal(int row, int col, int value)
{
    queensInSecondaryDiagonal[row + col] += value;
}
int Board::numberOfConflicts(int row, int col) const
{
    int fix = 0;
    if (isPositionOccupiedByQueen(row, col))
    {
        fix = 3;
    }
    int mainDiagonalIndex;
    if (row <= col)
    {
        mainDiagonalIndex = (size - 1) - abs(row - col);
    }
    else
    {
        mainDiagonalIndex = (size - 1) + abs(row - col);
    }
    int secondaryDiagonalIndex = row + col;
    return queensInRow[row] + queensInMainDiagonal[mainDiagonalIndex] + queensInSecondaryDiagonal[secondaryDiagonalIndex] - fix;
}
void Board::solve() {
    int moves = 0;
    vector<int> candidates;
    while (true)
    {
        int maxConflicts = 0;
        candidates.clear();
        for (int col = 0; col < size; col++)
        {
            int numberOfConflicts = Board::numberOfConflicts(cols[col], col);
            if (numberOfConflicts == maxConflicts)
            {
                candidates.push_back(col);
            }
            else if (numberOfConflicts > maxConflicts)
            {
                maxConflicts = numberOfConflicts;
                candidates.clear();
                candidates.push_back(col);
            }
        }
        if (maxConflicts == 0)
        {
            return;
        }
        int worstQueenColumn = candidates[rand() % candidates.size()];//Random integer in the interval [0,candidates.size())
        candidates.clear();
        int minNumberOfConflicts = size;
        for (int row = 0; row < size; row++)
        {
            int numberOfConflicts = Board::numberOfConflicts(row, worstQueenColumn);
            if (numberOfConflicts == minNumberOfConflicts)
            {
                candidates.push_back(row);
            }
            else if (numberOfConflicts < minNumberOfConflicts)
            {
                minNumberOfConflicts = numberOfConflicts;
                candidates.clear();
                candidates.push_back(row);
            }
        }
        if (!candidates.empty())
        {
            int oldRow = cols[worstQueenColumn];
            int newRow = candidates[rand() % candidates.size()];
            if (newRow != oldRow)
            {
                cols[worstQueenColumn] = newRow;
                queensInRow[oldRow] -= 1;
                queensInRow[newRow] += 1;
                addToMainDiagonal(oldRow, worstQueenColumn, -1);
                addToMainDiagonal(newRow, worstQueenColumn, 1);
                addToSecondaryDiagonal(oldRow, worstQueenColumn, -1);
                addToSecondaryDiagonal(newRow, worstQueenColumn, 1);
            }
        }
        moves++;
        if (moves == size * 2)
        {
            shuffle();
            moves = 0;
        }
    }
}
bool Board::isPositionOccupiedByQueen(int row, int col) const
{
    return cols[col] == row;
}
void Board::Print() const
{
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (isPositionOccupiedByQueen(row, col))
            {
                cout << " Q ";
            }
            else
            {
                cout << " # ";
            }
        }
        cout << '\n';
    }
}
bool Board::isSolved() const
{
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            int numConflicts = numberOfConflicts(row, col);
            if (isPositionOccupiedByQueen(row, col) && numConflicts > 0)
            {
                return false;
            }
        }
    }
    return true;
}