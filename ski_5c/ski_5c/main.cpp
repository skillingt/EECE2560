//
//  main.cpp
//  ski_5c
//
//  Created by Taylor Skilling on 11/28/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
// Created and Compiled on Mac OS X using XCode
// Note: Be sure to update filePath variable in main() 
// This script finds the shortest path in a given graph using Bellman-Ford algorithm and Dijkstra’s algorithm

#include "heapV.h"
#include <boost/graph/adjacency_list.hpp>

using namespace std;
using namespace boost;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

struct VertexProperties
{
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

void initializeGraph(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end, ifstream &fin)
// Initialize g using data from fin.  Set start and end equal to the start and end nodes.
{
    EdgeProperties e;
    
    int n, i, j;
    int startId, endId;
    fin >> n;
    fin >> startId >> endId;
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
void clearVisited(Graph &g) {
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		g[*vItr].visited = false;
}

// Set all node weights to w
void setNodeWeights(Graph &g, int w) {
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		g[*vItr].weight = w;
}

// Set all node marks to false
void clearMarked(Graph &g) {
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


void relax(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v)
{
    // Get the edge between u and v
    pair<Graph::edge_descriptor, bool> checkEdge = edge(u, v, g);
    
    // Ensure that the edge exists
    if (checkEdge.second != true) {
        cout << "The edge does not exist!" << endl;
    }
    
    // Relax
    if (g[v].weight > g[u].weight + g[checkEdge.first].weight)
    {
        g[v].weight = g[u].weight + g[checkEdge.first].weight;
        g[v].pred = u;
    }
}

bool bellmanFord(Graph &g, Graph::vertex_descriptor s){
    // Initialize all the vertices to very large weight
    init_single_source(g, s);
    
    // Relax
    // Initialize variables
    bool debug(false);
    unsigned long numV = num_vertices(g);
    Graph::vertex_descriptor u, v;
    // Get a pair containing iterators pointing the beginning and end of the list of edges
    pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
    // Iterate as many times as there are nodes in the graph
	for (int i = 1; i < numV; i++) {
        // Loop over all edges in the graph
        for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr)
        {
            u = source(*eItr, g);
            v = target(*eItr, g);
            relax(g, u, v);
        }
	}
    
    // Check for negative cycles
    // Loop over all edges in the graph, checking for negative edges
    for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr)
    {
        // Returns the target vertex of edge eItr
        Graph::vertex_descriptor u = source(*eItr, g);
        // Returns the source vertex of edge eItr
        Graph::vertex_descriptor v = target(*eItr, g);
        if (debug)
        {
            cout << "Done relaxing! Here's the weight of v: " << g[v].weight << " and u: " << g[u].weight << endl;
            cout << "And here's the weight of the edge: " << g[*eItr].weight << endl;
        }
        // Check if there is a negative cycle
        if (g[v].weight > g[u].weight + g[*eItr].weight)
        {
            return false;
        }
    } // end edge iteration, checking for negative weights
    return true;
} // end bellmanFord

bool dijkstra(Graph &g, Graph::vertex_descriptor s) {
	//Initialization
    vector<Graph::vertex_descriptor> vList;
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) {
		g[*vItr].weight = LargeValue;
		g[*vItr].pred = NULL;
		vList.push_back(*vItr);
	}
	g[s].weight = 0;
    
    // Instantiate Min Heap
	heapV<Graph::vertex_descriptor, Graph&> minHeap;
    
	//Initialize Min Heap with source node as root 
	minHeap.initializeMinHeap(vList, g);
    
    // Djikstra Algorithm
	Graph::vertex_descriptor u;
	Graph::vertex_descriptor v;
	int index;
	while (minHeap.size() != 0) {
        // Get the node with the minimum weight
		u = minHeap.extractMinHeapMinimum(g);
        // Check if it's an unreachable node, if so, return false
		if (g[u].weight == LargeValue)
        {
			return false;
        }
		pair<Graph::adjacency_iterator, Graph::adjacency_iterator> aItrRange = adjacent_vertices(u, g);
		for (Graph::adjacency_iterator aItr = aItrRange.first; aItr != aItrRange.second; ++aItr)
        {
            // Dereference adjacency iterator
			v = *aItr;
			// Ensure the edge has a positive weight, if not, throw an error
			pair<Graph::edge_descriptor, bool> checkEdge = edge(u, v, g);
			if (g[checkEdge.first].weight < 0)
				throw rangeError("Dijkstra Algorithm cannot handle graphs with negative weights");
			// Check if v is in min heap
			try {
				index = minHeap.getIndex(v);
                // Vertex v exists, call relax
				relax(g, u, v);
                // Update estimates for node v
				minHeap.minHeapDecreaseKey(index, g);
			}
            // If v isn't in the heap
			catch(const rangeError)
            {
				continue; 
			}
		}
	}
	return true;
}


ostream &operator<<(ostream &ostr, const Graph &g)
{
    // Output operator for the Graph class. Prints out all nodes and their properties, and all edges and their properties.
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


int main()
{
    try
    {
        ifstream fin;
        int number;
        cout << "Welcome to Graph Solver!" << endl << "Please enter a number between 1 and 10 to select a maze:" << endl;
        cin >> number;
        if (number < 1 || number > 10)
        {
            throw rangeError("Error: number must be between 1 and 10");
        }
        string filePath = "/Users/TaylorSkilling/Documents/Junior NU/Fund. of Algorithims/ski_5c/ski_5c/";
        string graphName = "graph" + to_string(number) + ".txt";
        
        // Read the maze from the file.
        string fileName = filePath + graphName;
        
        fin.open(fileName.c_str());
        if (!fin)
        {
            throw fileOpenError(fileName);
        }
        
        // Instantiate a graph object and two vertex descriptors
        Graph g;
        Graph::vertex_descriptor start, end;
        
        // Initialize the graph and clear visited and marked nodes
        initializeGraph(g, start, end, fin);
        fin.close();
        clearMarked(g);
		clearVisited(g);
        
        // Bellman-Ford
		if (bellmanFord(g, start)) {
			//cout << g << endl;
			cout << "Bellman-Ford Algorithm: ";
			printPath(g, start, end);
		}
		else
			cout << "Bellman-Ford Algoritm: Negative cycle detected" << endl;
        
        // Dijkstra
		if (dijkstra(g, start)) {
			cout << "Dijkstra's Algorithm: ";
			printPath(g, start, end);
		}
		else {
			cout << "Dijkstra's Algorithm: No path exists to end node" << endl;
	    }
        
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
