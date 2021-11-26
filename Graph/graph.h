#include "../General/general.h"
#include "specific.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#define INF (INT_MAX)

/* Initialise an empty graph */
graph* graph_init(void);

/* Add new vertex */
int graph_addVert(graph* g, char* label);

/* Add new edge between two Vertices */
bool graph_addEdge(graph* g,  int from,
                   int to, edge weight);

/* Returns NO_VERT if not already a vert   
   else 0 ... (size-1)                   */
int graph_getVertNum(graph* g, char* label);

/* Returns label of vertex v */
char* graph_getLabel(graph* g, int v);

/* Returns edge weight - if none = INF */
edge graph_getEdgeWeight(graph* g, int from, int to);

/* Number of verts */
int graph_numVerts(graph* b);

/* Output edge weights e.g. "0->1 200 2->1 100" */
void graph_tostring(graph* g, char* str);

/* Clear all memory associated with graph */
bool graph_free(graph* g);

/* Optional ? */

/* Min Distance between two nodes */
edge graph_dijkstra(graph* g, int from, int to);
/* Greedy Travelling Salesman */
edge graph_salesman(graph* g, int from, char* str);
/* Use Graphviz via a .dot file */
void graph_todot(graph* g, char* dotname);
