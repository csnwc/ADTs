#include "../General/general.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned double edge;
/* Initialise an empty graph */
graph* graph_init(void);

/* Add new vertex */
bool graph_addVert(graph* g, char* label)

/* Add new edge between two Vertices */
int graph_addEdge(graph* g,  char* from, char* to, edge weight);

/* Clear all memory associated with graph */
bool graph_free(graph* g);

/* Optional ? */

/* Use Graphviz via a .dot file */
void graph_todot(graph* g, char* dotname);
