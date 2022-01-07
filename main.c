#include <stdlib.h>
#include <stdio.h>
#include "t1.h"
#define INFINITY 1000 // A sufficiently large number is as good as infinity for this task...

int ** create_2D_array(int size) {
  int ** ptr = (int **) malloc(sizeof(int *) *size);
  for(int i=0; i<size; i++) {
    ptr[i] = (int *) malloc(sizeof(int)*size);
    for (int j=0; j<size; j++){
        ptr[i][j] = 0;
    }
  }
  return ptr;
}

Graph* create_graph(int num_nodes) {
  Graph *graph = malloc(sizeof(Graph));
  graph->vertices = num_nodes;

  graph->adjMatrix = create_2D_array(num_nodes);
  return graph;
}

// Add edges
void add_edge(Graph *g, int from, int to, int weight) {
  g->adjMatrix[from][to] = weight;
  g->adjMatrix[to][from] = weight;
}

// Print the matrix
void printAdjMatrix(Graph *g) {
  int i, j;
  for (i = 0; i < g->vertices; i++) {
    for (j = 0; j < g->vertices; j++) {
      printf("%d", g->adjMatrix[i][j]);
    }
    printf("\n");
  }
}

// Converts an upper-case character (A-Z) to a numerical value (between 0 and 25)
static int char2val ( char c ) {
	if ( c < 'A' || c > 'Z' ) {
		return -1;
	}
	return c-'A';
}

void Dijkstra(Graph *g, int origin) {
  int cost[MAX][MAX], distance[MAX], prevNode[MAX];
  int visited[MAX], minDistance, i, j;
  char nodeLables[7] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

  // Creating the cost matrix
  for (i = 0; i < g->vertices; i++) {
    for (j = 0; j < g->vertices; j++) {
      if ((g->adjMatrix[i][j] == 0) && (i == j)) {
            cost[i][j] = 0;
      }
      else if (g->adjMatrix[i][j] == 0) {
            cost[i][j] = INFINITY; // 'INFINITY' is defined at the top...
      }
      else {
            cost[i][j] = g->adjMatrix[i][j];
      }
    }
  }

  for(i = 0; i < g->vertices; i++) {
    printf("%c maps to %d\n", nodeLables[i], char2val(nodeLables[i]));
  }

  for(i = 0; i < g->vertices; i++) {
    for(j = 0; j < g->vertices; j++) {
        printf("(%c to %c) = %d\n", nodeLables[i], nodeLables[j], cost[i][j]);
    }
  }

  int numVisited = 0; // The number of nodes visited (0 initially)

  // Initialising the vector or array showing which vertexes have been visited:
  for(i = 0; i < g->vertices; i++) {
    prevNode[i] = 0;
    visited[i] = 0;
  }

  // Loading in the values for the distances between all nodes (vertexes) and 'A' (including itself):
  distance[0] = 0;
  for(i = 1; i < g->vertices; i++) {
    distance[i] = INFINITY;
    printf("Element %d of the distance vector is %d.\n\n", i, distance[i]);
  }

  // Useful print out to have:
  for (i = 0; i < g->vertices; i++) {
    printf("Visited status of %c is: %d\n", nodeLables[i], visited[i]);
  }

  int nodeOrder[7];

  while(numVisited != g->vertices) { // While we have yet to visit all the nodes...
    int k; // A temporary variable which will be useful...
    minDistance = INFINITY;

    // Find the closest neighbour which has NOT been visited:
    for(i = 0; i < g->vertices; i++) {
        if((distance[i] < minDistance) && (!visited[i])) {
            minDistance = distance[i];
            k = i; // Index of closest neighbour...
        }
    }

    for(j = 0; j < g->vertices; j++) {
        if(distance[k] + cost[k][j] < distance[j]) { // The condition for which the distance[] vector should be updated...
            distance[j] = distance[k] + cost[k][j];
            prevNode[j] = k; // From what node 'k' do we come from before reaching node 'J'...
        }
    }
    nodeOrder[numVisited] = k;
    visited[k] = 1; // This is to ensure that we do not visit node 'k' again...
    numVisited++; // And we increment the number of visited nodes by 1...
  }


  // Printing the distance between A and each node, as well as the second last
  // node passed through on the path between A and each node...
  for (i = 0; i < g->vertices; i++) {
      printf("\nShortest path between %c and %c: %d\n", origin+'A', i+'A', distance[i]);
      printf("Node %c is reached via %c.", i+'A', nodeLables[prevNode[i]]);
  }
  printf("\n\nThe order in which the nodes were visited is: ");
  for (i = 0; i < g->vertices; i++) {
    printf("\n%c", nodeLables[nodeOrder[i]]);
  }
}

int main() {
    int num_nodes = 7;
    Graph *graph = create_graph(num_nodes);
    add_edge(graph, char2val('A'), char2val('B'), 1);
    add_edge(graph, char2val('A'), char2val('C'), 3);
    add_edge(graph, char2val('A'), char2val('F'), 10);
    add_edge(graph, char2val('B'), char2val('G'), 2);
    add_edge(graph, char2val('B'), char2val('D'), 7);
    add_edge(graph, char2val('B'), char2val('E'), 5);
    add_edge(graph, char2val('B'), char2val('C'), 1);
    add_edge(graph, char2val('C'), char2val('D'), 9);
    add_edge(graph, char2val('C'), char2val('E'), 3);
    add_edge(graph, char2val('D'), char2val('G'), 12);
    add_edge(graph, char2val('D'), char2val('F'), 1);
    add_edge(graph, char2val('D'), char2val('E'), 2);
    add_edge(graph, char2val('E'), char2val('F'), 2);
    // And now we will call our Dijkstra function...
    Dijkstra(graph, char2val('A')); // We pass in our graph, and specify 'A' as the origin point...
    return 0;
}
