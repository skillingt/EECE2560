//
//  main.cpp
//  ski_6a
//
//  Created by Taylor Skilling on 12/6/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
// Created and Compiled on Mac OS X using XCode
// Note: Be sure to update filePath variable in main()
// This script finds the shortest path in a given graph using Bellman-Ford algorithm and Dijkstra’s algorithm
// Gets a graph file name from keyboard, reads the graph, checks if it has cycles, checks if it is connected, finds a spanning forest (not necessarily with minimum cost)

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>

#include "d_except.h"
#include "heapV.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

#define LargeValue 999999999

using namespace std;
using namespace boost;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

struct VertexProperties
{
    Graph::vertex_descriptor pred; // predecessor node
    int weight;
    int key;
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

void initializeGraph(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end, ifstream &fin)
// Initialize g using data from fin.  Set start and end equal to the start and end nodes.
{
    EdgeProperties e;
    
    int n, i, j;
    int startId, endId;
    fin >> n;
    startId = 0;
    endId = n - 1;
    Graph::vertex_descriptor v;
    
    // Add nodes.
    for (int i = 0; i < n; i++)
    {
        v = add_vertex(g);
        if (i == startId)
            start = v;
        if (i == endId)
            end = v;
    }
    
    while (fin.peek() != '.')
    {
        fin >> i >> j >> e.weight;
        pair<Graph::edge_descriptor, bool> checkEdge = edge(i, j, g);
        // If an edge doesn't already exist
		if (!checkEdge.second)
			add_edge(i, j, e, g);
        // The edge exists but the newly discovered edge has a lower weight
		else if (g[checkEdge.first].weight < e.weight)
			g[checkEdge.first].weight = e.weight;
		else
			continue;
    }
}

// Mark all nodes in g as not visited
void clearVisited(Graph &g)
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		g[*vItr].visited = false;
}

// Set all node weights to w
void setNodeWeights(Graph &g, int w)
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		g[*vItr].weight = w;
}

// Set all node marks to false
void clearMarked(Graph &g)
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		g[*vItr].marked = false;
}


void init_single_source(Graph &g, Graph::vertex_descriptor &source)
{
    
    // Get a pair containing iterators pointing the beginning and end of the list of nodes
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    // Loop over all nodes in the graph
    for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        g[*vItr].weight = LargeValue;
        g[*vItr].pred = NULL;
    }
    
    // Set the source weight to zero
    g[source].weight = 0;
}

bool isConnected(Graph &g, Graph::vertex_descriptor start)
// Returns true if the graph is connected, meaning there exists a path between every pair of nodes. Traverse the graph and if by the end all nodes were visited, the graph is connected
{
    // Clear visited property from nodes
    clearVisited(g);
    
    // Initialize variables
    queue<Graph::vertex_descriptor> q;
    
    // Push the first vertex into the stack
    q.push(start);
    // While the stack isn't empty
    while (!q.empty())
    {
        // Retrieve the vertex at the front of the queue
        Graph::vertex_descriptor u = q.front();
        // Pop the vertex out
        q.pop();
        if (!g[u].visited)
        {
            // Mark that we've visited the node
            g[u].visited = true;
            // Get a pair containing iterators pointing to the start and all adjacent nodes
            pair<Graph::adjacency_iterator, Graph::adjacency_iterator> aItrRange = boost::adjacent_vertices(u, g);
            // Loop over all adjacent nodes
            for (Graph::adjacency_iterator aItr = aItrRange.first; aItr != aItrRange.second; ++aItr)
            {
                // If the node hasn't been visited, mark it as such
                if (!g[*aItr].visited)
                {
                    // Add the node to the queue
                    q.push(*aItr);
                }
            } // end adjacent node for loop
        } // end if !visited
    } // end while loop
    
    // Check to see if we've visited all the nodes
    // Get a pair containing iterators pointing the beginning and end of the list of nodes
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    // Loop over all nodes in the graph
    for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        // If a node hasn't been visited, the graph is not connected
        if (!g[*vItr].visited)
        {
            return false;
        }
    }
    return true;
} // end isConnected()

bool isCyclic(Graph &g)
// Returns true if the graph g contains a cycle.  During traversal, if we can see an already visited neighbor (other than predecessor), we know there must be a cycle
{
    // Clear all visited nodes
    clearVisited(g);
    
    // Initialize variables
    stack<Graph::vertex_descriptor> s;
    bool debug(false);
    
    // Iterate over all nodes to ensure that we are checking all trees in a forest
    // Get a pair containing iterators pointing the beginning and end of the list of nodes
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    // Loop over all nodes in the graph
    for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        // Push the vertex into the queue if we haven't visited it yet - this ensures we hit all trees in a forest
        if (!g[*vItr].visited)
        {
            if (debug)
                cout << endl << "Putting node " << *vItr << " into the stack" << endl;
            s.push(*vItr);
        }
        // While the queue isn't empty
        while (!s.empty())
        {
            // Retrieve the vertex at the front of the queue
            Graph::vertex_descriptor u = s.top();
            // Pop the vertex out
            s.pop();
            if (debug)
                cout << "Retrieving node " << u << " from the stack" << endl;
            // Get a pair containing iterators pointing to the start and all adjacent nodes
            pair<Graph::adjacency_iterator, Graph::adjacency_iterator> aItrRange = boost::adjacent_vertices(u, g);
            // Loop over all adjacent nodes
            for (Graph::adjacency_iterator aItr = aItrRange.first; aItr != aItrRange.second; ++aItr)
            {
                if (debug)
                    cout << "Got adjacent node " << *aItr << endl;
                // Check to see if we've already visited the node if it's not the predecessor
                if (g[*aItr].visited && *aItr != g[u].pred)
                {
                    if (debug)
                        cout << "Node " << *aItr << " has been visited and does not have predecessor " << u << " but does have predecessor " << g[*aItr].pred << endl;
                    return true;
                }
                else
                {
                    if (debug)
                        cout << "Visiting node " << *aItr << " and marking its predecessor as " << u << endl;
                    // Add the node to the queue
                    if (!g[*aItr].visited)
                        s.push(*aItr);
                    // Mark that we've visited the node
                    g[*aItr].visited = true;
                    // Update the predecessor
                    g[*aItr].pred = u;
                }
            } // end adjacent node for loop
        } // end while loop
    } // end all node iteration
    // No cycles detected, so return false
    return false;
} // end isCyclic()

void findSpanningForest(Graph &g, Graph &sf)
// Create a graph sf that contains a spanning forest on the graph g
{
    // Clear all visited nodes
    clearVisited(g);
    clearVisited(sf);
    
    // Initialize variables
    stack<Graph::vertex_descriptor> s;
    bool debug(false);
    
    // Iterate over all nodes to ensure that we are checking all trees in a forest
    // Get a pair containing iterators pointing the beginning and end of the list of nodes
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    // Loop over all nodes in the graph
    for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        // Push the vertex into the queue if we haven't visited it yet - this ensures we hit all trees in a forest
        if (!g[*vItr].visited)
        {
            if (debug)
                cout << endl << "Putting node " << *vItr << " into the stack" << endl;
            s.push(*vItr);
        }
        // While the queue isn't empty
        while (!s.empty())
        {
            // Retrieve the vertex at the front of the queue
            Graph::vertex_descriptor u = s.top();
            // Pop the vertex out
            s.pop();
            if (debug)
                cout << "Retrieving node " << u << " from the stack" << endl;
            // Get a pair containing iterators pointing to the start and all adjacent nodes
            pair<Graph::adjacency_iterator, Graph::adjacency_iterator> aItrRange = boost::adjacent_vertices(u, g);
            // Loop over all adjacent nodes
            for (Graph::adjacency_iterator aItr = aItrRange.first; aItr != aItrRange.second; ++aItr)
            {
                // If we haven't visited a node yet, update the pred and mark it visited
                if (!g[*aItr].visited) {
                    if (debug)
                        cout << "Marking node " << *aItr << " visited" << endl;
                    // Mark that we've visited the node
                    g[*aItr].visited = true;
                    // Update the predecessor
                    g[*aItr].pred = u;
                    // Add the node to the stack
                    s.push(*aItr);
                }
                // If adding an edge creates a cycle, remove the edge
                if (isCyclic(sf))
                {
                    if (debug)
                        cout << "Node " << *aItr << " created a cycle, removing the edge beteween it and " << u << endl;
                    // If edge (u,v) exists, checkEdge.first is that edge and checkEdge.second is true.
                    // Otherwise checkEdge.second is false.
                    pair<Graph::edge_descriptor, bool> checkEdge = edge(u, *aItr, sf);
                    if (checkEdge.second == true)
                        remove_edge(*aItr, u, sf);
                    // Remove the predecessor
                    g[*aItr].pred = NULL;
                }
            } // end adjacent node for loop
        } // end while loop
    } // end all node iteration
} // end findSpanningForest

ostream &operator<<(ostream &ostr, const Graph &g)
// Output operator for the Graph class. Prints out all nodes and their properties, and all edges and their properties.
{
    // Get a pair containing iterators pointing the beginning and end of the list of nodes
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    // Loop over all nodes in the graph
    for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
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
        ostr << "Weight: " << g[*eItr].weight << endl;
        ostr << "Visited: " << g[*eItr].visited << endl;
        ostr << "Marked: " << g[*eItr].marked << endl << endl;
    }
    return ostr;
}

void printPath(Graph &g, Graph::vertex_descriptor start, Graph::vertex_descriptor end)
{
    // Initialize variables
    stack<Graph::vertex_descriptor> s;
    Graph::vertex_descriptor curr;
    
    curr = end;
    
    if (g[curr].weight == LargeValue)
    {
        cout << "No path exists to end node" << endl;
    }
    else
    {
        // Build the stack using the vertex predecessors
        while (curr != NULL)
        {
            s.push(curr);
            curr = g[curr].pred;
        }
        s.push(0); // Push in the first node
        
        cout << "The nodes to the shortest path are: " << endl;
        // Print the shortest path by popping nodes out of the stack
        while (!s.empty()) {
            curr = s.top();
            cout << curr;
            // If we've reached the last node, print the total weight instead of the the arrow
            if (s.size() == 1)
            {
                cout << endl << "The total weight of the path is: " << g[curr].weight << endl;
            }
            else
            {
                cout << " -> ";
            }
            s.pop();
        }
    }
}

int main(int argc, const char * argv[])
{
    try
    {
        ifstream fin;
        int number;
        cout << "Welcome to Spanning Tree Checker!" << endl << "Please enter a number between 1 and 5 to select a graph:" << endl;
        cin >> number;
        if (number < 1 || number > 5)
        {
            throw rangeError("Error: number must be between 1 and 5");
        }
        string filePath = "/Users/TaylorSkilling/Documents/Junior NU/Fund. of Algorithims/ski_6a/ski_6a/";
        string graphName = "graph" + to_string(number) + ".txt";
        
        // Read the maze from the file.
        string fileName = filePath + graphName;
        
        fin.open(fileName.c_str());
        if (!fin)
        {
            throw fileOpenError(fileName);
        }
        
        // Instantiate a graph object and two vertex descriptors
        Graph g, sf;
        Graph::vertex_descriptor start, end;
        
        // Initialize the graph and clear visited and marked nodes
        initializeGraph(g, start, end, fin);
        fin.close();
        clearMarked(g);
		clearVisited(g);
        
        // Check if the graph is connected
        if (isConnected(g, start))
        {
            cout << "The graph is connected and ";
        }
        else
        {
            cout << "The graph is disconnected and ";
        }
        
        // Check if the graph contains cycles
        if (isCyclic(g))
        {
            cout << "cyclic" << endl;
        }
        else
        {
            cout << "acyclic" << endl;
        }
        
        // Initialize new graph
        sf = g;
        
        // Find a Spanning Forest
        findSpanningForest(g, sf);
        
        // Perform the same checks on this new graph
        // Check if the graph is connected
        if (isConnected(sf, start))
        {
            cout << "The spanning forest is connected and ";
        }
        else
        {
            cout << "The spanning forest is disconnected and ";
        }
        
        // Check if the spanning forest contains cycles
        if (isCyclic(sf))
        {
            cout << "cyclic" << endl;
        }
        else
        {
            cout << "acyclic" << endl;
        }
        
        // Print out the edges in the spanning forest, the total cost, and the number of connected components
        Graph::vertex_descriptor src, targ;
		int edge_weight(0), total_weight(0);
		pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(sf);
		for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr) {
			src = source(*eItr, sf);
			targ = target(*eItr, sf);
			edge_weight = g[*eItr].weight;
			cout << "The edge between node " << src << " and node " << targ << " has weight " << edge_weight << endl;
			total_weight += edge_weight;
		}
        // Print out the total weight, which is half the calculated weight due to the graph being directed
		cout << "Total Cost: " << total_weight / 2 << endl;
		// Get the number of connected components through the boost function
		std::vector<int> component(num_vertices(sf));
		int conn_comp = connected_components(sf, &component[0]);
		cout << "The spanning forest has " << conn_comp << " connected components" << endl;
    }
    // File I/O Error Handling
    catch (const fileOpenError &re)
    {
		cerr << re.what() << endl;
	}
    // Out of Range Error Handling
    catch(rangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
}

