// Interface  to  the  undirected weighted graph ADT, where vertices are
// identified by an integer between 0 and N - 1, where N is  the  number
// of vertices.

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct GraphRep *Graph;

typedef int Vertex;

typedef struct ShortestPaths *SPath;

struct ShortestPaths {
	int numNodes;    // The number of vertices in the graph.
	
	int **dist;      //2d array of distance.
	                 
	int **pred;      //2d array of pred node.
};

// graph representation (adjacency matrix)
struct GraphRep {
	int nV;      // #vertices
	int nE;      // #edges
	int **edges; // matrix of weights (0 == no edge)
};

////////////////////////////////////////////////////////////////////////////////

/**
 * Creates a new graph with `nV` vertices and no edges
 */
Graph GraphNew(int nV);

/**
 * Frees all resources associated with the given graph
 */
void  GraphFree(Graph g);

/**
 * Inserts  an  edge  between  `v`  and  `w` with the given weight. Does
 * nothing if there is already an edge between `v` and `w`.
 */
void  GraphInsertEdge(Graph g, Vertex v, Vertex w, int weight);
void  GraphInsertDirectEdge(Graph g, Vertex v, Vertex w, int weight);

/**
 * Removes an edge between `v` and `w`. Does nothing if there is no edge
 * between `v` and `w`.
 */
void  GraphRemoveEdge(Graph g, Vertex v, Vertex w);

/**
 * Show the graph's number of edges vertexs and edges with weight
 */
void showGraph(Graph g);

/**
 * Use depth first search to find the path from "src" to "dest"
 * print them form dest to src
 */
void dfsPathFind(Graph g, Vertex src, Vertex dest);

/**
 * Use depth first search to find the path from "src" to "dest"
 * return ture if has path
 */
bool dfsPathCheck(Graph g, Vertex src, Vertex dest);

/**
 * Use beneth first search to find the path from "src" to "dest".
 * print them form dest to src.
 * notice: it is the shortest path on edges.
 */
void bfsPathFind(Graph g, Vertex src, Vertex dest);

/**
 * Use dfs circle check to find whether there are circle in graph g.
 * notice: dfs circle can only check one component.
 */
bool hasCycle(Graph g);

/**
 * Check are there Hamiltonian path from src to dest.
 * use help function hamiltonR() 
 */
bool hasHamiltonianPath(Graph g, Vertex src, Vertex dest);

/**
 * Check are there euler path from src to dest.
 * use help function degree() 
 */
bool hasEulerPath(Graph g, Vertex v, Vertex w);

SPath floydAPSP(Graph g);
#endif