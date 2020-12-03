#include <stdio.h>
#include "Graph.h"

int main(void) {
    
    printf("====test Graph insert and show=====\n");
    Graph new = GraphNew(10);
    GraphInsertEdge(new, 0, 1, 5);
    GraphInsertEdge(new, 3, 5, 5);
    GraphInsertEdge(new, 5, 4, 3);
    GraphInsertEdge(new, 5, 6, 2);
    GraphInsertEdge(new, 8, 7, 4);
    GraphInsertEdge(new, 0, 2, 1);
    GraphInsertEdge(new, 2, 3, 4);
    GraphInsertEdge(new, 3, 4, 2);
    GraphInsertEdge(new, 4, 7, 3);
    GraphInsertEdge(new, 8, 3, 4);
    GraphInsertEdge(new, 8, 9, 1);
    GraphInsertEdge(new, 1, 5, 4);
    GraphInsertEdge(new, 0, 5, 7);
    GraphInsertEdge(new, 8, 4, 4);
    GraphInsertEdge(new, 9, 7, 4);
    GraphInsertEdge(new, 5, 7, 4);
    showGraph(new);
    printf("\n");

    printf("====test Graph dfs path find=====\n");
    dfsPathFind(new, 0, 7);
    //correct output is 7->4->3->5->1->0
    printf("\n");

    printf("====test Graph bfs path find=====\n");
    bfsPathFind(new, 0, 9);
    //correct output is 9->7->5->0
    printf("\n");
    GraphFree(new);

    printf("====test Graph circle check=====\n");
    Graph g1 = GraphNew(8);
    GraphInsertEdge(g1, 0, 1, 5);
    GraphInsertEdge(g1, 0, 2, 5);
    GraphInsertEdge(g1, 0, 3, 5);
    GraphInsertEdge(g1, 6, 1, 5);
    GraphInsertEdge(g1, 2, 5, 5);
    GraphInsertEdge(g1, 3, 4, 5);
    GraphInsertEdge(g1, 3, 7, 5);
    //no circle
    if (!hasCycle(g1)) {
        printf("Test passed, no circle\n\n");
    } else {
        printf("Test failed\n\n");
    }
    GraphFree(g1);

    printf("====test Hamiltonial path check=====\n");
    Graph g2 = GraphNew(8);
    GraphInsertEdge(g2, 0, 2, 1);
    GraphInsertEdge(g2, 0, 3, 2);
    GraphInsertEdge(g2, 0, 6, 3);
    GraphInsertEdge(g2, 5, 2, 8);
    GraphInsertEdge(g2, 7, 2, 9);
    GraphInsertEdge(g2, 7, 5, 8);
    GraphInsertEdge(g2, 3, 2, 7);
    GraphInsertEdge(g2, 1, 3, 6);
    GraphInsertEdge(g2, 1, 4, 5);
    GraphInsertEdge(g2, 1, 6, 4);
    GraphInsertEdge(g2, 3, 4, 10);
    GraphInsertEdge(g2, 4, 6, 11);
    showGraph(g2);
    int src = 0;
    int dest = 0;
    printf("Enter the start: ");
    scanf("%d", &src);
    printf("Enter the end: ");
    scanf("%d", &dest);
    printf("%d %d\n", src, dest);

    if (hasHamiltonianPath(g2, src, dest)) {
        printf("There are Hamiltonal paths from %d to %d\n\n", src, dest);
    } else {
        printf("There are no Hamiltonal paths from %d to %d\n\n", src, dest);
    }
    GraphFree(g2);

    printf("====test Euler path check=====\n"); 
    Graph g3 = GraphNew(6);
    GraphInsertEdge(g3, 0, 1, 1);
    GraphInsertEdge(g3, 0, 3, 2);
    GraphInsertEdge(g3, 5, 4, 8);
    GraphInsertEdge(g3, 2, 1, 9);
    GraphInsertEdge(g3, 2, 3, 2);
    GraphInsertEdge(g3, 4, 3, 3);
    showGraph(g3);
    printf("Enter the start: ");
    scanf("%d", &src);
    printf("Enter the end: ");
    scanf("%d", &dest);
    printf("%d %d\n", src, dest);
    if (hasEulerPath(g3, src, dest)) {
        printf("There are Euler paths from %d to %d\n\n", src, dest);
    } else {
        printf("There are no Euler paths from %d to %d\n\n", src, dest);
    }
    GraphFree(g3);

    printf("====test floyd find shortest path=====\n");
    Graph g4 = GraphNew(6);
    GraphInsertDirectEdge(g4, 0, 1, 1);
    // GraphInsertEdge(g4, 0, 1, 1);
    GraphInsertEdge(g4, 0, 3, 2);
    GraphInsertEdge(g4, 5, 4, 8);
    GraphInsertEdge(g4, 2, 1, 9);
    GraphInsertEdge(g4, 2, 3, 2);
    GraphInsertEdge(g4, 4, 3, 3);
    showGraph(g4);
    SPath sp = floydAPSP(g4);
    printf("Enter the start: ");
    scanf("%d", &src);
    printf("Enter the end: ");
    scanf("%d", &dest);
    printf("the shortest distance from %d to %d is %d\n", src, dest, sp->dist[src][dest]);
    printf("the path is: ");
    int curr = src;
    while (curr != dest) {
        printf("%d--", curr);
        curr = sp->pred[curr][dest];
    }
    printf("%d\n\n", dest);
}