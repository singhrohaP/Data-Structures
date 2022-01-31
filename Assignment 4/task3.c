#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t3.h"

int visited[MAX_NB];
int adjMat[MAX_NB][MAX_NB];

int next_field( FILE *f, char *buf, int max ) { //from assignment 0
    int i=0, end=0, quoted=0;
    
    for(;;) {
        // fetch the next character from file
        buf[i] = fgetc(f);
        // if we encounter quotes then flip our state and immediately fetch next char
        if(buf[i]=='"') { quoted=!quoted; buf[i] = fgetc(f); }
        // end of field on comma if we're not inside quotes
        if(buf[i]==',' && !quoted) { break; }
        // end record on newline or end of file
        if(feof(f) || buf[i]=='\n') { end=1; break; }
        // truncate fields that would overflow the buffer
        if( i<max-1 ) { ++i; }
    }

    buf[i] = 0;
    return end;
}

void getStops (  FILE *csv, struct stop *p) {
    char buf[MAX_BUFFER];
    
    next_field( csv, buf, MAX_BUFFER );
    p->id = atoi(buf);
    next_field( csv, p->title, MAX_BUFFER );
    next_field( csv, buf, MAX_BUFFER );
    p->lat = atof(buf);
    next_field( csv, buf, MAX_BUFFER );
    p->lont = atof(buf);
}

Graph* create_graph(int num_nodes){
    Graph* g = (Graph *)malloc(sizeof(struct Graph));
    g->vertices=num_nodes;

    int i,j;
    for(i=0;i<num_nodes;i++){
        for(j=0;j<num_nodes;j++){
            adjMat[i][j]=0;
        }
    }
    int n=num_nodes;
    return g;
}
Graph *graph;

int load_vertices(char *fname){
    FILE *f;
    struct stop pArray[MAX_NB];
    struct stop p;
    f=fopen(fname,"r");
    if(!f) {
        printf("unable to open file\n");
        return 0;
    }
    getStops( f, &p );
    int ngames = 0;
    int fr;
    while(!feof(f)) {
        getStops( f, &pArray[ngames]);
        fr=pArray[ngames].id;
        arr[fr]=&pArray[ngames];
        ngames++;
    }
    printf("Loaded %d vertices\n",ngames);
    fclose(f);
    graph = create_graph(ngames);
    
    return 1;
}


void getEdges (  FILE *csv, struct edges *p) {
    char buf[MAX_BUFFER];
    next_field( csv, buf, MAX_BUFFER );
    p->from = atoi(buf);
    next_field( csv, buf, MAX_BUFFER );
    p->to = atoi(buf);
    next_field( csv, buf, MAX_BUFFER );
    p->weight = atoi(buf);
}

void add_edge(int from, int to, int weight){
    adjMat[from][to]=weight;
    adjMat[to][from]=weight;
}

int load_edges(char *fname){
    FILE *f;
    struct edges pArray[MAX_NB];
    struct edges p;
    f=fopen(fname,"r");
    if(!f) {
        printf("unable to open file\n");
        return 0;
    }
    getEdges( f, &p );
    int nedges = 0;
    while(!feof(f)) {
    getEdges( f, &pArray[nedges]);
    nedges++;
    }
    int i;
    for(i=0;i<nedges;i++){
    add_edge(pArray[i].from,pArray[i].to,pArray[i].weight);
    }
    printf("Loaded %d edges\n",nedges);
    fclose(f);
    return 1;
}

void pathPrint(int p[], int q){
    if (p[q] == - 1)
        return;
    pathPrint(p, p[q]);
    printf("%d %s\n",arr[q]->id, arr[q]->title);
}

void shortest_path(int startNode, int endNode){
    int distance[MAX_NB];
    int pre[MAX_NB];
    int count,minDistance,nextNode,i,j;
    pre[startNode]=-1;
    int n=MAX_NB;
    
    
    for (i = 0; i < n; i++){
    for (j = 0; j < n; j++){
      if (adjMat[i][j] == 0)
        adjMat[i][j] = INFINITY;
        }
    }

    for (i = 0; i <n; i++) {
    distance[i] = INFINITY;
  }

    distance[startNode] = 0;
    count = 1;

    while (count < n-1) {
        minDistance = INFINITY;
        for (i = 0; i < n; i++){
              if ((distance[i] < minDistance) && (visited[i])!=1) {
                minDistance = distance[i];
                nextNode = i;
              }}
        
        visited[nextNode] = 1;
    
        for (i = 0; i < n; i++)
              if (!(visited[i]))
                if (minDistance + adjMat[nextNode][i] < distance[i]) {
                  distance[i] = minDistance + adjMat[nextNode][i];
                  pre[i]=nextNode;
                }
        count++;
    }
    printf("%d %s\n",arr[startNode]->id, arr[startNode]->title);
    pathPrint(pre,endNode);
}

void delete_graph(Graph* g){
    free(g);
}

void free_memory(void){
    delete_graph(graph);
}

