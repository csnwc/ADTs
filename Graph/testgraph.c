#include "graph.h"

int main(void)
{

   graph* g;

   printf("Test Graph (%s) Start ... ", GRAPHTYPE);

   assert(!graph_addVert(NULL, "A"));
   g = graph_init();
   assert(graph_addVert(g, "A"));
   assert(graph_addVert(g, "B"));
   assert(graph_addVert(g, "C"));
   assert(graph_addEdge(g, 0, 1, 100));
   assert(graph_addEdge(g, 1, 2, 75));
   assert(graph_addEdge(g, 2, 0, 30));
   graph_todot(g, "g.dot");

   assert(graph_free(g));
   printf("End\n");
   return 0;

}
