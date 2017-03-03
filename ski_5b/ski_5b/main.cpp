//
//  main.cpp
//  ski_5b
//
//  Created by Taylor Skilling on 11/17/15.
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
        int number;
        cout << "Welcome to Maze Solver!" << endl << "Please enter a number between 1 and 16 to select a maze:" << endl;
        cin >> number;
        if (number < 1 || number > 16)
        {
            throw rangeError("Error: number must be between 1 and 16");
        }
        string filePath = "/Users/TaylorSkilling/Documents/Junior NU/Fund. of Algorithims/ski_5b/ski_5b/";
        string mazeName = "maze" + to_string(number) + ".txt";
        
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
        setNodeWeights(g,1);
        m.mapMazeToGraph(g);
        
        cout << g << endl;
        
        // Initialize variables
        stack<Graph::vertex_descriptor> moves;
        Graph::vertex_descriptor start, goal;
        start = m.getVertex(0,0);
        goal = m.getVertex(m.numRows()-1,m.numCols()-1);
        unsigned long DFSR(0), DFSI(0),DFSS(0),BFS(0);
        
        cout << "Recursive Depth First Search:" << endl;
        // Recursive Depth First Search
        m.findPathDFSRecursive(g, start, goal, moves);
        DFSR = moves.size();
        // Print
        m.printPath(goal, moves, g);
        // Clear the stack
        clearStack(moves);
        
        cout << "Iterative Depth First Search:" << endl;
        // Iterative Depth First Search
        m.findPathDFSStack(g, start, goal, moves);
        DFSI = moves.size();
        //Print
        m.printPath(goal, moves, g);
        // Clear the stack
        clearStack(moves);
        
        cout << "Shortest Path Depth First Search:" << endl;
        // Breadth First Search
        m.findShortestPathDFS(g, start, goal, moves);
        DFSS = moves.size();
        //Print
        m.printPath(goal, moves, g);
        // Clear the stack
        clearStack(moves);
        
        cout << "Breadth First Search:" << endl;
        // Breadth First Search
        m.findShortestPathBFS(g, start, goal, moves);
        BFS = moves.size();
        //Print
        m.printPath(goal, moves, g);
        // Clear the stack
        clearStack(moves);
        
        // Print the total steps per search
        cout << "Recursive Depth First took " << DFSR << " steps" << endl << endl;
        cout << "Iterative Depth First took " << DFSI << " steps" << endl << endl;
        cout << "Shortest Path DFS took " << DFSS << " steps" << endl << endl;
        cout << "Breadth First Search took " << BFS << " steps" << endl << endl;
        
    }
    catch(rangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
}