//
//  Board.cpp
//  ski_4a
//
//  Created by Taylor Skilling on 10/25/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
//  Defines member functions of the Board Class

#include "Board.h"

using namespace std;

Board::Board(int sqSize)
: value(boardSize+1,boardSize+1)
// Board constructor
{
    // Resize conflict matricies
    row_con.resize(10,10);
    col_con.resize(10,10);
    square_con.resize(10,10);
}

ostream &operator<<(ostream &ostr, const vector<bool> &v)
// Overloaded output operator for vector class.
{
    for (int i = 1; i < v.size(); i++)
        ostr << v.at(i) << " ";
    ostr << endl;
    return ostr;
}

void Board::Initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
    char ch;
    
    Clear();
    for (int i = 1; i <= boardSize; i++)
        for (int j = 1; j <= boardSize; j++)
        {
            fin >> ch;
            
            // If the read char is not Blank
            if (ch != '.')
            {
                SetCell(i,j,ch-'0');   // Convert char to int
            }
            else
            {
                SetCell(i,j,blank); // Set the cell as blank
            }
        }
}

void Board::Clear()
// Clear the entire board and conflict lists
{
    for (int i = 1; i <= boardSize; i++)
    {
        for (int j = 1; j <= boardSize; j++)
        {
            // Reset board
            SetCell(i, j, -1);
            // Reset conflict lists
            row_con[i][j] = false;
            col_con[i][j] = false;
            square_con[i][j] = false;
        }
    }
}

void Board::Print()
// Prints the current board.
{
    for (int i = 1; i <= boardSize; i++)
    {
        if ((i-1) % squareSize == 0)
        {
            cout << " -";
            for (int j = 1; j <= boardSize; j++)
                cout << "---";
            cout << "-";
            cout << endl;
        }
        for (int j = 1; j <= boardSize; j++)
        {
            if ((j-1) % squareSize == 0)
            {
                cout << "|";
            }
            if (!IsBlank(i,j))
            {
                cout << " " << GetCell(i,j) << " ";
            }
            else
            {
                cout << "   ";
            }
        }
        cout << "|";
        cout << endl;
    }
    
    cout << " -";
    for (int j = 1; j <= boardSize; j++)
        cout << "---";
    cout << "-";
    cout << endl;
}

void Board::PrintConflicts()
{
    cout << "Row Conflicts: " << endl;
    for (int i= 1; i <= boardSize; i++) {
        cout << row_con[i];
    }
    cout << "Column Conflicts: " << endl;
    for (int i= 1; i <= boardSize; i++) {
        cout << col_con[i];
    }
    cout << "Square Conflicts: " << endl;
    for (int i= 1; i <= boardSize; i++) {
        cout << square_con[i];
    }
}

void Board::CheckConflicts()
// Check whether a value causes conflicts when placed in a cell
{
    // Initialize variables
    int index(0), square(0);
    for (int i = 1; i <= boardSize; i++)
    {
        for (int j = 1; j <= boardSize; j++)
        {
            if (i >= 1 && i <= boardSize && j >= 1 && j <= boardSize)
            {
                // Return the value in the cell
                index = GetCell(i,j);
                // Return what square the current index is in
                square = SquareNumber(i,j);
                // If the cell isn't blank, update the conflict vectors
                if (index != blank) {
                    row_con[i][index] = true;
                    col_con[j][index] = true;
                    square_con[square][index] = true;
                }
            }
            else
            {
                throw rangeError("bad value in GetCell");
            }
        }
    }
    // Print the conflicts to the screen
    PrintConflicts();
} // end CheckConflicts

void  Board::SetCell(int i,int j, ValueType val)
// set cell i,j to val and update conflicts
{
    if (i >= 1 && i <= boardSize && j >= 1 && j <= boardSize)
        value[i][j] = val;
    else
        throw rangeError("bad value in GetCell");
}

ValueType Board::GetCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
    if (i >= 1 && i <= boardSize && j >= 1 && j <= boardSize)
        return value[i][j];
    else
        throw rangeError("bad value in GetCell");
}

bool Board::IsSolved()
// Returns true if all conflict vectors are false and all spaces are filed in
{
    // Initialize variables
    int index(0), square(0);
    // Check if vectors contain all zeros
    for (int i = 1; i <= boardSize; i++)
    {
        for (int j = 1; j <= boardSize; j++)
        {
            if (i >= 1 && i <= boardSize && j >= 1 && j <= boardSize)
            {
                // Return the value in the cell
                index = GetCell(i,j);
                // Return what square the current index is in
                square = SquareNumber(i,j);
                // If the cell is false, then there is still a conflict somewhere, return false
                if (row_con[i][j] == false || col_con[i][j] == false || square_con[i][j] == false)
                {
                    return false;
                }
                // If the cell is not filled up, return false, we have more values to place
                if (GetCell(i,j) == blank) {
                    return false;
                }
            }
            else
            {
                throw rangeError("bad value in GetCell");
            }
        }
    }
    // Passes all checks
    return true;
} // end IsSolved()

bool Board::IsBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
    // Check for errors
    if (i < 1 || i > boardSize || j < 1 || j > boardSize)
        throw rangeError("bad value in SetCell");
    // Check if the cell is blank
    if (GetCell(i,j) == blank)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Board::SquareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
    // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
    // coordinates of the square that i,j is in.
    return squareSize * ((i-1)/squareSize) + (j-1)/squareSize + 1;
}
