//
//  main.cpp
//  ski_5a
//
//  Created by Taylor Skilling on 11/8/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
// Created and Compiled on Mac OS X using XCode
// Note: Be sure to update filePath variable below
// This script prints a given maze

#include "maze.h"

int main()
{
    try
    {
        ifstream fin;
        string filePath = "/Users/TaylorSkilling/Documents/Junior NU/Fund. of Algorithims/ski_5a/ski_5a/";
        string mazeName = "maze1.txt";
        
        // Read the maze from the file.
        string fileName = filePath + mazeName;
        
        fin.open(fileName.c_str());
        if (!fin)
        {
            cerr << "Cannot open " << fileName << endl;
            exit(1);
        }
        
        maze m(fin);
        fin.close();
        
        m.print(m.numRows()-1,m.numCols()-1,0,0);
        
        Graph g;
        m.mapMazeToGraph(g);
        
        cout << g << endl;
    }
    catch(indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
}
