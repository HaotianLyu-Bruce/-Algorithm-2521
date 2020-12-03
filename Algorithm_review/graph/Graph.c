// Implementation of the undirected weighted graph ADT

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "Queue.h"



////////////////////////////////////////////////////////////////////////////////

/**
 * Creates a new graph with `nV` vertices and no edges
 */
Graph GraphNew(int nV) {
    assert(nV > 0);
    Graph new = malloc(sizeof(struct GraphRep));

    assert(new != NULL);
    new->nV = nV;
    new->nE = 0;

    new->edges = calloc(nV, sizeof(int *));
    assert(new->edges != NULL);
    //calloc the matrix and initialise 0
    //notice: calloc will initialise 0, but malloc not
    for (int i = 0; i < nV; i++) {
        new->edges[i] = calloc(nV, sizeof(int));
        assert(new->edges[i] != 0);
    }
    return new;
}

/**
 * Frees all resources associated with the given graph
 */
void  GraphFree(Graph g) {
    assert(g != NULL);
    for (int i = 0; i < g->nV; i++) {
        free(g->edges[i]);
    }
    free(g->edges);
    free(g);
}

/**
 * Inserts  an  edge  between  `v`  and  `w` with the given weight. Does
 * nothing if there is already an edge between `v` and `w`.
 */
void  GraphInsertEdge(Graph g, Vertex v, Vertex w, int weight) {
    assert(g != NULL);
    assert(v >= 0 && v < g->nV);
    assert(w >= 0 && w < g->nV);
    if (g->edges[v][w] == 0 && g->edges[w][v] == 0) {
        g->edges[v][w] = weight;
        g->edges[w][v] = weight;
        g->nE++;
    }
}
void  GraphInsertDirectEdge(Graph g, Vertex v, Vertex w, int weight) {
    assert(g != NULL);
    assert(v >= 0 && v < g->nV);
    assert(w >= 0 && w < g->nV);
    if (g->edges[v][w] == 0) {
        g->edges[v][w] = weight;
        g->edges[w][v] = 0;
        g->nE++;
    }
}

/**
 * Removes an edge between `v` and `w`. Does nothing if there is no edge
 * between `v` and `w`.
 */
void  GraphRemoveEdge(Graph g, Vertex v, Vertex w) {
    assert(g != NULL);
    assert(v >= 0 && v < g->nV);
    assert(w >= 0 && w < g->nV);
    if (g->edges[v][w] != 0 && g->edges[w][v] != 0) {
        g->edges[v][w] = 0;
        g->edges[w][v] = 0;
        g->nE--;
    }
}

/**
 * show the graph's number of edges vertexs and edges with weight
 */
void showGraph(Graph g) {
    assert(g != NULL);
    int i, j;
    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    for (i = 0; i < g->nV; i++) {
        for (j = i+1; j < g->nV; j++) {
            if (g->edges[i][j] != 0){
                printf("Edge %d - %d: %d\n", i, j, g->edges[i][j]);
            }    
        }
    }	    
}


Vertex *visited;
/**
 * Use depth first search to find the path from "src" to "dest"
 * print them form dest to src
 */
void dfsPathFind(Graph g, Vertex src, Vertex dest) {
    visited = calloc(g->nV, sizeof(int));
    printf("dfs path form %d to %d:\n", src, dest);
    for (int i = 0; i < g->nV; i++) {
        visited[i] = -1;
    }
    visited[src] = src;
    if (dfsPathCheck(g,src,dest)) {
        Vertex v = dest;
        while (v != src) {
            printf("%d->", v);
            v = visited[v];
        }
        printf("%d\n", src);
    } else {
        printf("No path from %d to %d\n", src, dest);
    }
    free(visited);
}

/**
 * Use depth first search to find the path from "src" to "dest"
 * return ture if has path
 */
bool dfsPathCheck(Graph g, Vertex src, Vertex dest) {
    Vertex w;
    for (w = 0; w < g->nV; w++) {
        if (g->edges[src][w] != 0) {
            if (visited[w] == -1) {
                visited[w] = src;
                if (w == dest) {
                    return true;
                } else if (dfsPathCheck(g,w,dest)) {
                    return true;
                }
            }   
        }
    }
    return false;
}

/**
 * Use beneth first search to find the path from "src" to "dest".
 * print them form dest to src.
 * notice: it is the shortest path on edges.
 */
void bfsPathFind(Graph g, Vertex src, Vertex dest) {
    visited = calloc(g->nV, sizeof(int));
    printf("bfs path form %d to %d:\n", src, dest);
    for (int i = 0; i < g->nV; i++) {
        visited[i] = -1;
    }
    bool found = false;
    visited[src] = src;
    Queue q = QueueNew();

    QueueEnqueue(q, src);
    while (!found && !QueueIsEmpty(q)) {
        int curr = QueueDequeue(q);
        if (curr == dest) {
            found = true;
        } else {
            Vertex w;
            for (w = 0; w < g->nV; w++) {
                if (g->edges[curr][w] != 0 && visited[w] == -1) {
                    visited[w] = curr;
                    QueueEnqueue(q, w);
                }
            }
        }
    }
    QueueFree(q);
    if (found) {
        Vertex v = dest;
        while (v != src) {
            printf("%d->", v);
            v = visited[v];
        }
        printf("%d\n", src);
    } else {
        printf("No path from %d to %d\n", src, dest);
    }
    free(visited);
}


/**
 * Use dfs circle check to find whether there are circle in graph g.
 * notice: dfs circle can only check one component.
 */
bool dfsCycleCheck(Graph g, Vertex v, Vertex u);

bool hasCycle(Graph g) {
	// TODO
	bool result = false;
	visited = calloc(g->nV, sizeof(int));
	for (Vertex v = 0; v < g->nV; v++) {
		for(int i = 0; i < g->nV; i++) {
			visited[i] = -1;
		}
		if (dfsCycleCheck(g, v, v)) {
			result = true;
			break;
		}
	}
	free(visited);
	return result;
}

bool dfsCycleCheck(Graph g, Vertex v, Vertex u) {
	visited[v] = u;
	for (Vertex w = 0; w < g->nV; w++) {
		if (g->edges[v][w] != 0) {
			if (visited[w] == -1) {
				if (dfsCycleCheck(g, w, v)){
					return true;
				}
			} else if (w != u) {
				return true;
			}
		}
	}
	return false;
}
/**
 * Check are there Hamiltonian path from src to dest.
 * use help function hamiltonR
 */
bool hamiltonR(Graph g, Vertex v, Vertex dest, int d);

bool hasHamiltonianPath(Graph g, Vertex src, Vertex dest) {
    visited = calloc(g->nV, sizeof(int));
    printf("Check hamiltonian Path form %d to %d:\n", src, dest);
    for (int i = 0; i < g->nV; i++) {
        visited[i] = 0;
    }
    return hamiltonR(g, src, dest, (g->nV - 1));
}

bool hamiltonR(Graph g, Vertex v, Vertex dest, int d) {
    Vertex w;
    if (v == dest) {
        if (d == 0) {
            return true;
        } else {
            return false;
        }
    } else {
        visited[v] = 1;
        for (w = 0; w < g->nV; w++) {
            if (g->edges[v][w] != 0 && visited[w] == 0) {
                if (hamiltonR(g, w, dest, d - 1)) {
                    return true;
                }
            }
        }
    }
    visited[v] = 0;
    return false;
}

/**
 * Check are there euler path from src to dest.
 * use help function degree() 
 */
int degree(Graph g, Vertex v);

bool hasEulerPath(Graph g, Vertex v, Vertex w) {
    printf("Check Euler Path form %d to %d:\n", v, w);
    if (v != w) {
        if (degree(g, v) % 2 == 0 || degree(g, w) % 2 == 0) {
            return false;
        }
    } else {
        if (degree(g, v) % 2 != 0) {
            return false;
        }
    }
    Vertex x;
    for (x = 0; x < g->nV; x++) {
        if (x != v && x != w && degree(g, x) % 2 != 0) {
            return false;
        }
    }
    return true;
}

int degree(Graph g, Vertex v) {
    int deg = 0;
    Vertex w;
    for (w = 0; w < g->nV; w++) {
        if (g->edges[v][w] != 0) {
            deg++;
        }
    }
    return deg;
}

////////////////////////////////////////////////////////////////////////////////
#define infinity 99999



SPath floydAPSP(Graph g) {
    SPath new = malloc(sizeof(struct ShortestPaths));
    
    assert(new != NULL);
    new->numNodes = g->nV;

    new->dist = calloc(g->nV, sizeof(int *));
    new->pred = calloc(g->nV, sizeof(int *));
    for (int i = 0; i < g->nV; i++) {
        new->dist[i] = calloc(g->nV, sizeof(int));
        new->pred[i] = calloc(g->nV, sizeof(int));
        assert(new->dist[i] != 0);
        assert(new->pred[i] != 0);
        for (int j = 0; j < g->nV; j++) {
            // if (g->edges[i][j] != 0) {
            //     new->dist[i][j] = g->edges[i][j];
            //     new->pred[i][j] = j;
            // } else if (i == j) {
            //     new->dist[i][j] = 0;
            //     new->pred[i][j] = -1;
            // } else {
            //     new->dist[i][j] = infinity;
            //     new->pred[i][j] = -1;
            // }
            if (i == j) {
                new->dist[i][j] = 0;
            } else {
                if (g->edges[i][j] > 0) {
                    new->dist[i][j] = g->edges[i][j];
                    new->pred[i][j] = j;
                } else {
                    new->dist[i][j] = infinity;
                    new->pred[i][j] = -1;
                }
            }
        }
    }
    for (int i = 0; i < g->nV; i++) {
        for (int s = 0; s < g->nV; s++) {
            for (int t = 0; t < g->nV; t++) {
                if (new->dist[s][i] + new->dist[i][t] < new->dist[s][t]) {
                    new->dist[s][t] = new->dist[s][i] + new->dist[i][t];
                    new->pred[s][t] = new->pred[s][i];
                }
            }
        }
    }
    return new;
}
