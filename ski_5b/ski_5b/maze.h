//
//  maze.h
//  ski_5a
//
//  Created by Taylor Skilling on 11/8/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>

#include "d_except.h"
#include "d_matrix.h"
#include <boost/graph/adjacency_list.hpp>

#define LargeValue 99999999

using namespace std;
using namespace boost;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

struct VertexProperties
{
    pair<int,int> cell; // maze cell (x,y) value
    Graph::vertex_descriptor pred; // predecessor node
    int weight;
    bool visited;
    bool marked;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
    int weight;
    bool visited;
    bool marked;
};

class maze
{
private:
    int rows; // number of rows in the maze
    int cols; // number of columns in the maze
    matrix<Graph::vertex_descriptor> vertex; // stores nodes
    matrix<bool> value;
    stack<Graph::vertex_descriptor> currStack;
public:
    // 5_a
    maze(ifstream &fin);
    void print(int, int, int, int);
    bool isLegal(int, int);
    void mapMazeToGraph(Graph &g);
    void printPath(Graph::vertex_descriptor end, stack<Graph::vertex_descriptor> &s, Graph g);
    int numRows(){return rows;};
    int numCols(){return cols;};
    Graph::vertex_descriptor getVertex(int i, int j){return vertex[i][j];};
    // 5_b
    bool findPathDFSRecursive(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &moves);
    bool findPathDFSRecursive2(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &moves);
    bool findPathDFSStack(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &moves);
    bool findShortestPathDFS(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &moves);
    void findShortestPathDFS2(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &moves);
    bool findShortestPathBFS(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &moves);
    void clearStack(stack<Graph::vertex_descriptor> &moves);
};

void clearVisited(Graph &g)
// Mark all nodes in g as not visited
{
    // Get a pair containing iterators pointing the beginning and end of the list of nodes
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    // Loop over all nodes in the graph
    for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        g[*vItr].visited = false;
    }
}

void setNodeWeights(Graph &g, int w)
// Set all node weights to w
{
    // Get a pair containing iterators pointing the beginning and end of the
    // list of edges
    pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
    // Loop over all edges in the graph
    for (Graph::edge_iterator eItr= eItrRange.first; eItr != eItrRange.second; ++eItr)
    {
        g[*eItr].weight = w;
    }
}

void clearMarked(Graph &g)
// Unmark all nodes
{
    // Get a pair containing iterators pointing the beginning and end of the list of nodes
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    // Loop over all nodes in the graph
    for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        g[*vItr].marked = false;
    }
}


void clearStack(stack<Graph::vertex_descriptor> &moves)
{
    while (!moves.empty())
    {
        moves.pop();
    }
}

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
    fin >> rows;
    fin >> cols;
    
    char x;
    
    value.resize(rows,cols);
    for (int i = 0; i <= rows-1; i++)
        for (int j = 0; j <= cols-1; j++)
        {
            fin >> x;
            if (x == 'O')
                value[i][j] = true;
            else
                value[i][j] = false;
        }
    
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
    cout << endl;
    
    if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
        throw rangeError("Bad value in maze::print");
    
    if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
        throw rangeError("Bad value in maze::print");
    
    for (int i = 0; i <= rows-1; i++)
    {
        for (int j = 0; j <= cols-1; j++)
        {
            if (i == goalI && j == goalJ)
                cout << "*";
            else
                if (i == currI && j == currJ)
                    cout << "+";
                else
                    if (value[i][j])
                        cout << " ";
                    else
                        cout << "X";
        }
        cout << endl;
    }
    cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze, indicating
// whether it is legal to go to cell (i,j).
{
    if (i < 0 || i > rows || j < 0 || j > cols)
        throw rangeError("Bad value in maze::isLegal");
    
    return value[i][j];
}

void maze::mapMazeToGraph(Graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
    // Resize the vertex to the size of the input matrix
    vertex.resize(rows,cols);
    // Loop through all cells in the matrix
    for (int i = 0; i <= rows-1; i++)
    {
        for (int j = 0; j <= cols-1; j++)
        {
            // Check if the location is valid
            if(isLegal(i, j))
            {
                // Create a vertex descriptor to hold the node and keep track of the node that corresponds to the maze cell (i,j)
                vertex[i][j] = add_vertex(g);
                // Set the predecessor of the node to NULL
                g[vertex[i][j]].pred = -1;
                // Keep track of the maze cell (i,j) using the cell property of a node to store the pair, hard coding in the first node
                g[vertex[i][j]].cell = make_pair(i,j);
                //g[vertex[i][j]].pred = NULL;
            }
            else
            {
                // Cannot place a valid node, don't check left or up
                continue;
            }
            // Starting at the top left corner and aiming for the bottom right, only need to check up and right due to bidirectional edges
            // Check Up
            if (i > 0)
            {
                if(isLegal(i-1, j))
                {
                    // Retrieve the vertex one to the left of our current position and connect the two nodes (in both directions)
                    add_edge(vertex[i-1][j], vertex[i][j], g);
                    add_edge(vertex[i][j], vertex[i-1][j], g);
                }
            }
            // Check Left
            if (j > 0)
            {
                if(isLegal(i, j-1))
                {
                    // Retrieve the vertex one to the left of our current position and connect the two nodes (in both directions)
                    add_edge(vertex[i][j-1], vertex[i][j], g);
                    add_edge(vertex[i][j], vertex[i][j-1], g);
                }
            }
        } // end j for loop
    } // end i for loop
} // end function

void maze::printPath(Graph::vertex_descriptor end,
                     stack<Graph::vertex_descriptor> &s,
                     Graph g)
// Prints the path represented by the vertices in stack s. Repeatedly
// calls print() to show each step of the path.
{
    // Initialize a pair to store values while iterating through the stack
    pair<int,int> curr;
    // Retrieve the end of the matrix
    pair<int,int> goal = g[end].cell;
    if (s.empty()) {
        cout << "The stack is empty - could not find a solution!" << endl;
    }
    while (!s.empty()) {
        curr = g[s.top()].cell;
        print(goal.first,goal.second,curr.first,curr.second);
        s.pop();
    }
}

bool maze::findPathDFSRecursive2(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &moves)
//  Looks for a path from the start cell to the goal cell using depth-first search
{
    // Return if we've reached the goal
    if (start == goal)
    {
        return true;
    }
    else
    {
        // Mark that we've visited the node
        g[start].visited = true;
        // Initialize variables
        bool found = false;
        // Get a pair containing iterators pointing to the start and all adjacent nodes
        pair<Graph::adjacency_iterator, Graph::adjacency_iterator> aItrRange = adjacent_vertices(start, g);
        for (Graph::adjacency_iterator aItr = aItrRange.first; aItr != aItrRange.second; ++aItr)
        {
            if (found)
            {
                break;
            }
            // If we haven't visited the node before, call findPathDFSRecursive2 again
            if (g[*aItr].visited == false)
            {
                found = findPathDFSRecursive2(g,*aItr,goal,moves);
                // If we've already identified this node, continue to the next iteration
            }
        }
        // If the node is part of the path to the goal, push it to the stack
        if (found)
        {
            moves.push(start);
        }
        return found;
    } // end else
} // end findPathDFSRecursive2

bool maze::findPathDFSRecursive(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &moves)
// Depth First Recursive: Looks for a path from the start cell to the goal cell using depth-first search
{
    clearVisited(g);
    moves.push(goal);
    return(findPathDFSRecursive2(g,start,goal,moves));
}

bool maze::findPathDFSStack(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &moves)
// Depth First Stack: Looks for a path from the start cell to the goal cell using depth-first search, but using a stack and not recursion.
{
    // Clear visited nodes
    clearVisited(g);
    
    // Initialize variables
    Graph::vertex_descriptor curr;
    bool found = false;
    
    // Return if we've reached the goal
    if (start == goal)
    {
        return true;
    }
    
    // Push the first vertex into the stack
    moves.push(start);
    // While the stack isn't empty
    while (!moves.empty())
    {
        // Retrieve the vertex at the top of the stack
        Graph::vertex_descriptor u = moves.top();
        // Pop the vertex out
        moves.pop();
        // If we've reached the goal, set the found flag to true
        if (u == goal)
        {
            found = true;
        }
        if (!g[u].visited)
        {
            // Mark that we've visited the node and that we haven't found a solution yet
            g[u].visited = true;
            // Get a pair containing iterators pointing to the start and all adjacent nodes
            pair<Graph::adjacency_iterator, Graph::adjacency_iterator> aItrRange = boost::adjacent_vertices(u, g);
            // Loop over all adjacent nodes
            for (Graph::adjacency_iterator aItr = aItrRange.first; aItr != aItrRange.second; ++aItr)
            {
                // If the node is part of the path to the goal, push it to the stack and update its predecessor
                if (!g[*aItr].visited)
                {
                    moves.push(*aItr);
                    g[*aItr].pred = u;
                }
            } // end adjacent node for loop
        } // end if !visited
    } // end while loop
    curr = goal;
    // Build the stack using the vertex predecessors
    while (curr != -1)
    {
        moves.push(curr);
        curr = g[curr].pred;
    }
    if (!found)
    {
        cout << "Unable to find a path to the goal" << endl;
        return false;
    }
    else
    {
        return true;
    }
}

// Failed Iterative Try at Shortest Path DFS
//bool maze::findShortestPathDFS(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &moves)
//{
//    // Clear visited nodes
//    clearVisited(g);
//
//    // Initialize variables
//    Graph::vertex_descriptor curr;
//
//    // Return if we are passing the start as the goal
//    if (start == goal)
//    {
//        return true;
//    }
//    // Push the first vertex into the stack
//    moves.push(start);
//    // While the stack isn't empty
//    while (!moves.empty())
//    {
//        // Retrieve the vertex at the top of the stack
//        Graph::vertex_descriptor u = moves.top();
//        // Pop the vertex out
//        moves.pop();
//        if (!g[u].visited)
//        {
//            // Mark that we've visited the node and that we haven't found a solution yet
//            g[u].visited = true;
//            // Get a pair containing iterators pointing to the start and all adjacent nodes
//            pair<Graph::adjacency_iterator, Graph::adjacency_iterator> aItrRange = boost::adjacent_vertices(u, g);
//            // Loop over all adjacent nodes
//            for (Graph::adjacency_iterator aItr = aItrRange.first; aItr != aItrRange.second; ++aItr)
//            {
//                // If the node is part of the path to the goal, push it to the stack and update its predecessor
//                if (!g[*aItr].visited)
//                {
//                    moves.push(*aItr);
//                    g[*aItr].pred = u;
//                }
//            } // end adjacent node for loop
//            // If we've reached the goal, update the returned stack to the smallest one and clear the temporary one
//                if (moves.top() == goal)
//                {
//                    if (currStack.size() < moves.size())
//                    {
//                        moves = currStack;
//                        cout << "Changing moves to reflect the smaller, newly created stack" << endl;
//                        // Reset the temporary stack
//                        while (!currStack.empty())
//                        {
//                            currStack.pop();
//                        }
//                        // Add in the starting vertex again
//                        currStack.push(start);
//                    }
//        } // end if !visited
//    } // end while loop
//    curr = goal;
//    // Build the stack using the vertex predecessors
//    while (curr != -1)
//    {
//        moves.push(curr);
//        curr = g[curr].pred;
//    }
//    return true;
//}

void maze::findShortestPathDFS2(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &moves)
//  Looks for a path from the start cell to the goal cell using depth-first search
{
    // Mark that we've visited the node
    g[start].visited = true;
    currStack.push(start);
    
    if (start == goal)
    {
        if ((moves.empty()) || currStack.size() < moves.size())
        {
            moves = currStack;
        }
    }
    
    // Get a pair containing iterators pointing to the start and all adjacent nodes
    pair<Graph::adjacency_iterator, Graph::adjacency_iterator> aItrRange = adjacent_vertices(start, g);
    for (Graph::adjacency_iterator aItr = aItrRange.first; aItr != aItrRange.second; ++aItr)
    {
        // If we haven't visited the node before, call findShortestPathDFS2 again
        if (!g[*aItr].visited)
        {
            findShortestPathDFS2(g, *aItr, goal, moves);
        }
    }
    
    currStack.pop();
    g[start].visited = false;
} // end findPathDFSRecursive2

bool maze::findShortestPathDFS(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &moves)
{
    // Clear visited nodes
    clearVisited(g);

    // Recursive call
    findShortestPathDFS2(g,start,goal,moves);
    
    // Flip the stack
    stack<Graph::vertex_descriptor> temp;
	while (!moves.empty()) {
		temp.push(moves.top());
		moves.pop();
	}
    moves = temp;
    
    if (moves.empty())
    {
        cout << "Failed to find the shortest path" << endl;
        return false;
    }
    else
    {
        return true;
    }
}


bool maze::findShortestPathBFS(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor goal, stack<Graph::vertex_descriptor> &moves)
// Breath First: Finds a shortest path from the start cell to the goal cell using breadth-first search
{
    // Clear visited nodes
    clearVisited(g);
    
    // Initialize variables
    Graph::vertex_descriptor curr;
    bool found = false;
    queue<Graph::vertex_descriptor> q;
    
    // Return if we've reached the goal
    if (start == goal)
    {
        return true;
    }
    
    // Push the first vertex into the stack
    q.push(start);
    // While the stack isn't empty
    while (!q.empty())
    {
        // Retrieve the vertex at the top of the stack
        Graph::vertex_descriptor u = q.front();
        // Pop the vertex out
        q.pop();
        // If we've reached the goal, set the found flag to true
        if (u == goal)
        {
            found = true;
        }
        if (!g[u].visited)
        {
            // Mark that we've visited the node and that we haven't found a solution yet
            g[u].visited = true;
            // Get a pair containing iterators pointing to the start and all adjacent nodes
            pair<Graph::adjacency_iterator, Graph::adjacency_iterator> aItrRange = boost::adjacent_vertices(u, g);
            // Loop over all adjacent nodes
            for (Graph::adjacency_iterator aItr = aItrRange.first; aItr != aItrRange.second; ++aItr)
            {
                // If the node is part of the path to the goal, push it to the stack and update its predecessor
                if (!g[*aItr].visited)
                {
                    q.push(*aItr);
                    g[*aItr].pred = u;
                }
            } // end adjacent node for loop
        } // end if !visited
    } // end while loop
    curr = goal;
    // Build the stack using the vertex predecessors
    while (curr != -1)
    {
        moves.push(curr);
        curr = g[curr].pred;
    }
    if (!found)
    {
        cout << "Unable to find a path to the goal" << endl;
        return false;
    }
    else
    {
        return true;
    }
}

ostream &operator<<(ostream &ostr, const Graph &g)
{
    // Output operator for the Graph class. Prints out all nodes and their
    // properties, and all edges and their properties.
    // Initialize variables
    Graph::vertex_descriptor src, dest;
    // Get a pair containing iterators pointing the beginning and end of the list of nodes
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    // Loop over all nodes in the graph
    for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        ostr << "Cell: (" << g[*vItr].cell.first << "," << g[*vItr].cell.second << ")" << endl;
        ostr << "Pred: " << g[*vItr].pred << endl;
        ostr << "Weight: " << g[*vItr].weight << endl;
        ostr << "Visited: " << g[*vItr].visited << endl;
        ostr << "Marked: " << g[*vItr].marked << endl << endl;
        }
        
        // Get a pair containing iterators pointing the beginning and end of the list of edges
        pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
        // Loop over all edges in the graph
        for (Graph::edge_iterator eItr= eItrRange.first; eItr != eItrRange.second; ++eItr)
        {
            // Update variables
            src = source(*eItr, g);
            dest = target(*eItr, g);
            pair<int,int> srcIdx = g[src].cell;
            pair<int,int> destIdx = g[dest].cell;
            
            ostr << "Edge from: (" << srcIdx.first << "," << srcIdx.second << ")" << " to " << "(" << destIdx.first << "," << destIdx.second << ")" << endl;
            ostr << "Weight: " << g[*eItr].weight << endl;
            ostr << "Visited: " << g[*eItr].visited << endl;
            ostr << "Marked: " << g[*eItr].marked << endl << endl;
        }
        return ostr;
        }