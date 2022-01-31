
//
//  t2.c
//  task2Assignment4
//
//  Created by Prachi Singhroha on 25/11/21.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <assert.h>
#include "t2.h"


char val2char(int c){
    char y = c + 'A';
    return y ;
}
int n;


void add_edge(Graph *g, int from, int to, int weight){
    
    adjMat[from][to]=weight;
    adjMat[to][from]=weight;
}

Graph* create_graph(int num_nodes){
    Graph* g = (Graph *)malloc(sizeof(struct Graph));
    g->numVertices=num_nodes;
    n = num_nodes;
    int i,j;
    for(i=0;i<num_nodes;i++){
        for(j=0;j<num_nodes;j++){
            adjMat[i][j]=0;
        }
    }
    return g;
}

 int minDis(int dist[], bool set[]){
     int min = INT_MAX, minIndex;
     int v;
     for (v = 0; v < n; v++)
         if (set[v] == false && dist[v] < min)
             min = dist[v], minIndex = v;
     return minIndex;
 }
void printSolution(int dist[],int src){
    int i;
    for (i = 0; i < n; i++){
        printf("The length of the shortest path between %c and %c is %d\n",src + 'A',i+ 'A',dist[i]);
        
    }
}

void dijkstra(Graph* graph, int src) {
        int n = graph->numVertices;
        int dist[n];
        bool set[n];
        int i;
        for (i = 0; i < n; i++)
            dist[i] = INT_MAX, set[i] = false;

        dist[src] = 0;
        int count;
        int v;
        for (count = 0; count < n; count++) {
        int p = minDis(dist, set);

        set[p] = true;
        printf("%c ",val2char(p));
            for (v = 0; v < n; v++)
                if (!set[v] && adjMat[p][v] && dist[p] != INT_MAX && dist[p] + adjMat[p][v] < dist[v])
                    dist[v] = dist[p] + adjMat[p][v];
        }
        printf("\n");
        printSolution(dist,src);
    
}

void delete_graph(Graph* g){
    assert(g != NULL);
    free(g);
}

