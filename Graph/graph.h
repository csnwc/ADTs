#include "../General/general.h"
#include "specific.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#define INF (INT_MAX)

typedef enum bool {false, true} bool;

/* Initialise an empty graph */
graph* graph_init(void);

/* Add new vertex */
bool graph_addVert(graph* g, char* label);

/* Add new edge between two Vertices */
bool graph_addEdge(graph* g,  int from, int to, edge weight);

/* Clear all memory associated with graph */
bool graph_free(graph* g);

/* Optional ? */

/* Use Graphviz via a .dot file */
void graph_todot(graph* g, char* dotname);
