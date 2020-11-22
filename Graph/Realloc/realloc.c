#include "graph.h" 

#define MAXLABEL 100

graph* graph_init(void)
{
   graph* g = (graph*) ncalloc(1, sizeof(graph));
   g->capacity = INITSIZE;
   g->adjMat = (edge**) n2dcalloc(sizeof(edge), g->capacity, g->capacity);
   g->labels = (char**) n2dcalloc(sizeof(char), g->capacity, MAXLABEL+1);
   return g;
}
