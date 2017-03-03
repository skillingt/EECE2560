//
//  Board.h
//  ski_4a
//
//  Created by Taylor Skilling on 10/25/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
//  Declares member functions of the Board Class

#ifndef __ski_4a__Board__
#define __ski_4a__Board__

#include <iostream>
#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include <vector>

using namespace std;

typedef int ValueType; // The type of the value in a cell
const char blank = -1;  // Indicates that a cell is blank

const int squareSize = 3;  //  The number of cells in a small square
//  (usually 3).  The board has
//  SquareSize^2 rows and SquareSize^2
//  columns.

const int boardSize = squareSize * squareSize;

const int minValue = 1;
const int maxValue = 9;

class Board
// Stores the entire Sudoku board
{
private:
    // The following matrices go from 1 to BoardSize in each
    // dimension.  I.e. they are each (BoardSize+1) X (BoardSize+1)
    matrix<ValueType> value;
    // Conflict Vectors (element zero will be ignored for easier indexing)
    matrix<bool> row_con, col_con, square_con;
    int recursive_calls;
public:
    Board(int);
    void Initialize(ifstream &fin); // Initialize Board
    void Clear(); // Clear a cell and update conflicts
    void Print(); // Print Board
    void PrintConflicts(); // Print the conflict vectors
    void CheckConflicts(); // Check whether a value causes conflicts when placed in a cell
    bool SolveBoard(int, int); // Attempts to solve the board given an index, counting the number of recursive calls
    void SetCell(int,int, ValueType); // Add value to a cell and update conflicts
    ValueType GetCell(int, int); // Return the value of a cell 
    bool IsSolved(); // Check to see if it a board has been solved
    bool IsBlank(int, int); // Check to see if a board is blank
    int SquareNumber(int,int); // Returns the square number for the given index
    int GetRecursiveCalls();
    friend ostream &operator<<(ostream &ostr, vector<ValueType> &v); // Overloaded cout
};


#endif /* defined(__ski_4a__Board__) */
