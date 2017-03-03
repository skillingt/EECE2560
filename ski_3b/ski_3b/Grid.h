//
//  Grid.h
//  ski_3b
//
//  Created by Taylor Skilling on 10/18/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//

#ifndef __ski_3b__Grid__
#define __ski_3b__Grid__

#include <iostream>
#include <fstream>
#include <vector>
#include "d_matrix.h"

using namespace std;

class Grid
{
private:
    matrix<char> grid;
    int rows;
    int cols;
public:
    char ReadGrid(string grid_name);
    int GetNumRows();
    int GetNumCols();
    char GetChar(int row, int col, int direction, int size);
};



#endif /* defined(__ski_3b__Grid__) */
