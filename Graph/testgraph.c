#include "graph.h"

int main(void)
{

   graph* g;
   char str[1000];

   printf("Test Graph (%s) Start ... ", GRAPHTYPE);

   assert(graph_addVert(NULL, "A")==NO_VERT);
   assert(graph_numVerts(NULL) == 0);
   assert(graph_getEdgeWeight(NULL, 0, 0) == INF);
   g = graph_init();
   assert(graph_addVert(g, "A")==0);
   assert(graph_numVerts(g) == 1);
   assert(!graph_addEdge(g, 0, 1, 01));
   assert(graph_getEdgeWeight(NULL, 1, 0) == INF);
   graph_tostring(g, str);
   assert(strcmp(str, "A ")==0);
   assert(graph_addVert(g, "A")==NO_VERT);
   assert(graph_addVert(g, "B")==1);
   assert(graph_addEdge(g, 0, 1, 01));
   assert(graph_getEdgeWeight(g, 0, 1)==1);
   graph_tostring(g, str);
   assert(strcmp(str, "A B 0->1 1 ")==0);
   assert(graph_numVerts(g) == 2);
   assert(graph_addVert(g, "C")==2);
   assert(graph_numVerts(g) == 3);
   assert(graph_addEdge(g, 1, 2, 12));
   assert(graph_getEdgeWeight(g, 1, 2)==12);
   assert(graph_addEdge(g, 2, 0, 20));
   assert(graph_getEdgeWeight(g, 2, 0)==20);
   assert(graph_addVert(g, "D")==3);
   assert(graph_addEdge(g, 2, 3, 23));
   assert(graph_getEdgeWeight(g, 2, 3)==23);
   assert(graph_numVerts(g)==4);
   assert(graph_addEdge(g, 0, 3, 03));
   assert(graph_getEdgeWeight(g, 0, 3)==3);
   graph_tostring(g, str);
   assert(strcmp(str, "A B C D 0->1 1 0->3 3 1->2 12 2->0 20 2->3 23 ")==0);
   assert(graph_addVert(g, "E")==4);
   assert(graph_addVert(g, "F")==5);
   assert(graph_addVert(g, "G")==6);
   assert(graph_addVert(g, "H")==7);
   assert(graph_addVert(g, "I")==8);
   
   graph_todot(g, "g.dot");

   assert(graph_free(g));
   printf("End\n");
   return 0;

}
