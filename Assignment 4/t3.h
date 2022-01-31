
#ifndef T3_H_
#define T3_H_
#define MAX_BUFFER 100
#define MAX_NB 8000
#define INFINITY 99999

typedef struct edges edges;
struct edges{
    int from,to,weight;
};

typedef struct stop stop;
struct stop {
    int id;
    float lat,lont;
    char title[MAX_BUFFER];
};

stop* arr[MAX_NB];

typedef struct Graph{
    int vertices;
} Graph;


int load_edges ( char *fname ); //loads the edges from the CSV file of name fname
int load_vertices ( char *fname );  //loads the vertices from the CSV file of name fname
void shortest_path(int startNode, int endNode); // prints the shortest path between startNode and endNode, if there is any
void free_memory ( void ) ; // frees any memory that was used

#endif
