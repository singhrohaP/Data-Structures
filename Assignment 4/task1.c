#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "t1.h"

struct node *head = NULL;

char val2char(int c){
    char y = c+'A';
    return y ;
}

struct queue* createQueue() {
  struct queue* q = malloc(sizeof(struct queue));
  q->front = -1;
  q->rear = -1;
  return q;
}

int isEmpty(struct queue* q) {
  if (q->rear == -1)
    return 1;
  else
    return 0;
}

void enqueue(struct queue* q, int value) {
  if (q->rear == SIZE - 1)
    printf("\nQueue is Full!!");
  else {
    if (q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
  }
}

int dequeue(struct queue* q) {
  int item;
  if (isEmpty(q)) {
    printf("Queue is empty");
    item = -1;
  } else {
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
      //printf("Resetting queue ");
      q->front = q->rear = -1;
    }
  }
  return item;
}

Graph* create_graph(int num_nodes){
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = num_nodes;

      graph->adjLists = malloc(num_nodes * sizeof(struct node*));
      graph->visited = malloc(num_nodes * sizeof(int));

      int i;
      for (i = 0; i < num_nodes; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
      }

      return graph;
}

struct node* createNode(int v) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    if (head == NULL){
        head = newNode;
        newNode->nextc = NULL;
    }
    else{
        newNode->nextc = head;
        head = newNode;
    }
    return newNode;
}

void add_edge(Graph *g, int from, int to){
    struct node* newNode = createNode(to);
    newNode->next = g->adjLists[from];
    g->adjLists[from] = newNode;
}


void bfs(Graph* g, int origin){
    struct queue* q = createQueue();
    int i;
    for (i = 0; i < g->numVertices; i++) {
            g->visited[i] = 0;
          }
    g->visited[origin] = 1;
      
    enqueue(q, origin);
    printf("BFS ");
    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        printf(" %c ", val2char(currentVertex));

        struct node* temp = g->adjLists[currentVertex];

        while (temp) {
          int adjVertex = temp->vertex;

          if (g->visited[adjVertex] == 0) {
            g->visited[adjVertex] = 1;
            enqueue(q, adjVertex);
          }
          temp = temp->next;
        }
      }
    printf("\n");
    free(q);
}
void dfs_helper(Graph* g, int origin){
    struct node* adjList = g->adjLists[origin];
    struct node* temp = adjList;
    g->visited[origin] = 1;
    printf(" %c ", val2char(origin));

    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (g->visited[connectedVertex] == 0) {
          dfs_helper(g, connectedVertex);
        }
        temp = temp->next;
      }
}
void dfs(Graph* g, int origin){
    printf("DFS:");
    dfs_helper(g, origin);
    printf("\n");
}
void delete_graph(Graph* g){
    assert(g != NULL);
    struct node *p = head;
    while(head != NULL){
        head = head->nextc;
        free(p);
        p = head;
    }
    free(g->adjLists);
    free(g->visited);
    free(g);
}
/*
static int char2val ( char c ) {
    if ( c < 'A' || c > 'Z' ) {
        return -1;
    }

    return c-'A';
}

int main(){
    int num_nodes = 6;
    Graph *graph = create_graph(num_nodes);
   
    add_edge(graph, char2val('A'), char2val('E'));
    add_edge(graph, char2val('B'), char2val('D'));
    add_edge(graph, char2val('A'), char2val('D'));
    add_edge(graph, char2val('A'), char2val('B'));
    add_edge(graph, char2val('B'), char2val('C'));
    add_edge(graph, char2val('C'), char2val('B'));
    add_edge(graph, char2val('E'), char2val('D'));
    add_edge(graph, char2val('D'), char2val('F'));
    add_edge(graph, char2val('F'), char2val('C'));
    add_edge(graph, char2val('C'), char2val('D'));

    dfs(graph, char2val('A'));
    
    bfs(graph, char2val('A'));

    delete_graph(graph);

}*/

