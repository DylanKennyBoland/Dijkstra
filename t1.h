#define T1_H_INCLUDED
#ifndef T2_H_
#define T2_H_

#define MAX 7 // You can assume that the graph has at most 10 vertex
typedef struct Graph{
  int vertices;
  int** adjMatrix;
} Graph;

Graph* create_graph(int num_nodes); // Creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
void add_edge(Graph *g, int from, int to, int weight); // adds an undirected weighted edge between from and to

void Dijkstra(Graph* g, int origin); // Implements the Dijkstra algorithm and prints the order in which the nodes are made permanent,
// and the length of the shortest path between the origin node and all the other nodes
void delete_graph(Graph* g);
#endif
