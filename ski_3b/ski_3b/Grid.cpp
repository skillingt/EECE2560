//
//  Grid.cpp
//  ski_3b
//
//  Created by Taylor Skilling on 10/18/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//

#include "Grid.h"

using namespace std;

char Grid::ReadGrid(string grid_name)
{
    // Initialize variables
    string path_name;
    // NOTE: This must be updated when running on a different system
    path_name = "/Users/TaylorSkilling/Documents/Junior NU/Fund. of Algorithims/ski_3a/ski_3a/" + grid_name;
    ifstream myfile (path_name);
    // Attempt to open the file
    if (myfile.is_open())
    {
        // Read number of rows in grid
        myfile >> rows;
        // Read number of columns in grid
        myfile >> cols;
        // Set matrix size
        grid.resize(rows,cols);
        // Store grid in data-member matrix
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                myfile >> grid[i][j];
            }
        }
        // Close the file
        myfile.close();
    }
    // Improvement: Use try/catch
    else cout << "Unable to open file" << endl;
    
    return 0;
}

// Returns the number of rows in a given matrix
int Grid::GetNumRows(){
    return rows;
}

// Returns the number of columns in a given matrix
int Grid::GetNumCols(){
    return cols;
}

// Returns a character given the number of rows and columns in a given matrix
char Grid::GetChar(int i, int j, int m, int k){
    // Initialize variables
    int up, down, left, right;
    char letter;
    // Create directions for moving through matrix
    down = i + k;
    up = i - k;
    left = j - k;
    right = j + k;
    // Check Edge Conditions
    // Right is larger than columns in matrix, wrap around to other side of matrix
    if (right >= cols)
        right = right - cols;
    // Left is negative, wrap around to other side of matrix
    if ( left < 0 )
        left = cols + left;
    // Down is larger than rows in matrix, wrap around to other side of matrix
    if ( down >= rows)
        down = down - rows;
    // Up is negative, wrap around to other side of matrix
    if ( up < 0 )
        up = rows + up;
    
    // Calculate the character given the direction and string length
    switch (m) {
        // East
        case 0:
            letter = grid[i][right];
            break;
        // North
        case 1:
            letter = grid[up][j];
            break;
        // South
        case 2:
            letter = grid[down][j];
            break;
        // West
        case 3:
            letter = grid[i][left];
            break;
        // North East
        case 4:
            letter = grid[up][right];
            break;
        // North West
        case 5:
            letter = grid[up][left];
            break;
        // South West
        case 6:
            letter = grid[down][left];
            break;
        // South East
        case 7:
            letter = grid[down][right];
            break;
        default:
            throw rangeError("Switch case takes an integer 0 to 7");
            break;
            
    }
    return letter;
}
