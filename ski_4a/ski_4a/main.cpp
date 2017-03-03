//
//  main.cpp
//  ski_4a
//
//  Created by Taylor Skilling on 10/25/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
// Created and Compiled on Mac OS X using XCode
// Note: Be sure to update filePath variable below
// This script initializes a Sudoku grid from a file and prints out the board conflicts

#include <iostream>
#include "Board.h"

int main(int argc, const char * argv[])
{
    // Initialize variables
    string filePath, fileName, absPath;
    ifstream fin;
    bool isSolved;
    
    filePath = "/Users/TaylorSkilling/Documents/Junior NU/Fund. of Algorithims/ski_4a/ski_4a";
    fileName = "/sudoku.txt";
    absPath = filePath + fileName;
    
    // Read the sample grid from the file.
    fin.open(absPath.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << absPath << endl;
        exit(1);
    }
    
    try
    {
        Board board(squareSize);
        
        while (fin && fin.peek() != 'Z')
        {
            board.Initialize(fin);
            board.Print();
            board.CheckConflicts();
            isSolved = board.IsSolved();
            if (isSolved == true)
            {
                cout << "The board is solved!" << endl;
            }
            else
            {
                cout << "The board is not solved yet" << endl;
            }
        }
    }
    catch  (indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
}

