#include "graph.h"

#define BIGSTR 1000

int main(void)
{

   graph* g;
   char str[BIGSTR];

   printf("Test Graph (%s) Start ... ", GRAPHTYPE);

   assert(graph_addVert(NULL, "A")==NO_VERT);
   assert(graph_numVerts(NULL) == 0);
   assert(graph_getEdgeWeight(NULL, 0, 0) == INF);
   g = graph_init();
   assert(graph_addVert(g, "A")==0);
   assert(graph_numVerts(g) == 1);
   assert(!graph_addEdge(g, 0, 1, 01));
   assert(graph_getEdgeWeight(NULL, 1, 0) == INF);
   assert(strcmp(graph_getLabel(g, 0), "A")==0);
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
   assert(graph_addEdge(g, 0, 3, 30));
   assert(graph_getEdgeWeight(g, 0, 3)==30);
   graph_tostring(g, str);
   assert(strcmp(str, "A B C D 0->1 1 0->3 30 1->2 12 2->0 20 2->3 23 ")==0);
   assert(graph_addVert(g, "E")==4);
   assert(graph_addVert(g, "F")==5);
   assert(graph_addVert(g, "G")==6);
   assert(graph_addVert(g, "H")==7);
   assert(graph_addVert(g, "I")==8);
   assert(strcmp(graph_getLabel(g, 8), "I")==0);
   assert(graph_addVert(g, "J")==9);
   assert(graph_addEdge(g, 0, 8, 8));
   assert(graph_addEdge(g, 0, 9, 9));

   /* Minimum Cost */
   assert(graph_addEdge(g, 8, 3, 10));
   assert(graph_addEdge(g, 9, 3, 10));
   /* A -> I -> D */
   assert(graph_dijkstra(g, 0, 3)==18);
   assert(graph_dijkstra(g, 3, 0)==INF);
   assert(graph_dijkstra(g, 2, 1)==21);

   /* Travelling Salesman */
   assert(graph_addEdge(g, 3, 9, 4));
   assert(graph_addEdge(g, 1, 8, 20));
   assert(graph_addEdge(g, 9, 8, 1));
   assert(graph_addEdge(g, 1, 4, 21));
   assert(graph_addEdge(g, 4, 5, 9));
   assert(graph_addEdge(g, 5, 6, 6));
   assert(graph_addEdge(g, 8, 1, 18));
   assert(graph_addEdge(g, 8, 4, 2));
   /* Total cost & then path */
   assert(graph_salesman(g, 0, str)==58);
   assert(strcmp(str,"A B C D J I E F G ")==0);
   
   
   graph_todot(g, "g.dot");

   assert(graph_free(g));
   printf("End\n");
   return 0;

}
