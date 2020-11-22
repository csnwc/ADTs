#include "../graph.h" 

#define MAXLABEL 100

graph* graph_init(void)
{
   int h, w;
   int i, j;
   graph* g = (graph*) ncalloc(sizeof(graph), 1);
   h = INITSIZE;
   w = h;
   g->capacity = h;
   g->adjMat = (edge**) n2dcalloc(h, w, sizeof(edge));
   g->labels = (char**) n2dcalloc(h, MAXLABEL+1, sizeof(char));
   for(j=0; j<h; j++){
      for(i=0; i<w; i++){
         g->adjMat[j][i] = (i==j) ? 0 : INF;
      }
   }
   return g;
}

bool graph_free(graph* g)
{
   n2dfree((void**)g->adjMat, g->capacity);
   n2dfree((void**)g->labels, g->capacity);
   free(g);
   return true;
}

bool graph_addVert(graph* g, char* label)
{

   if(g==NULL){
      return false;
   }
   /* Resize */
   if(g->size >= g->capacity){
   }
   strcpy(g->labels[g->size], label);
   g->size = g->size + 1;
   return true;
}

bool graph_addEdge(graph* g, int from, int to, edge w)
{
   if((g==NULL) || (g->size == 0)){
      return false;
   }
   g->adjMat[from][to] = w;
   return true;
}
