#include "../graph.h" 

#define TMPSTR 1000

edge graph_salesman(graph* g, int from, char* str)
{
   bool* unvis;
   int curr, ncurr, nvs;
   edge cst, bcst, e;

   nvs = graph_numVerts(g);
   if((g==NULL) || (from >= nvs) || (str==NULL)){
      return INF;
   }
   unvis = (bool*)ncalloc(nvs, sizeof(bool));
   for(int v=0; v<nvs; v++){
      unvis[v] = true;
   }
   curr = from;
   bcst = 0;
   strcpy(str, graph_getLabel(g, from));
   do{
      unvis[curr] = false;
      cst = INF;
      ncurr = NO_VERT;
      /* Look at neighbours of curr */
      for(int v=0; v<nvs; v++){
         e = graph_getEdgeWeight(g, curr, v);
         if((v!=curr) && unvis[v] && (e!=INF)){
            if(e < cst){
               cst = e;
               ncurr = v;
            }
         }
      }
      /* Add in cost to go to closest */
      if(cst < INF){
         bcst += cst;
         curr = ncurr;
         strcat(str, " ");
         strcat(str, graph_getLabel(g, ncurr));
      }
   }while((cst < INF) && (curr != NO_VERT));
   free(unvis);
   return bcst;
}
   
/* Not efficient : Should use a min heap instead */
edge graph_dijkstra(graph* g, int from, int to)
{
   bool* unvis;
   edge* dist;
   edge e, cst;
   int v, curr, nvs;
   
   nvs = graph_numVerts(g);
   if((g==NULL) || (from >= nvs) 
      || (to >= nvs)){
      return INF;
   }
   unvis = (bool*)ncalloc(nvs, sizeof(bool));
   dist  = (edge*)ncalloc(nvs, sizeof(edge));
   for(v=0; v<nvs; v++){
      unvis[v] = true;
      dist[v] = INF;
   }
   dist[from] = 0; 
   curr = from;
   do{
      /* Look at neighbours of curr */
      unvis[curr] = false;
      for(v=0; v<g->size; v++){
         e = graph_getEdgeWeight(g, curr, v);
         if((v!=curr) && unvis[v] && (e!=INF)){
            cst = dist[curr] + e;
            if(cst < dist[v]){
               dist[v] = cst;
            }
         }
      }
      /* Have we found the answer */
      if(!unvis[to]){
         e = dist[to];
         free(dist); free(unvis);
         return e;
      }
      curr = -1;
      e = INF;
      /* Best unvisited node */
      for(v=0; v<g->size; v++){
         if(unvis[v] && (dist[v] < e)){
            curr = v;
            e = dist[v];
         }
      }
   }while(curr >= 0);
   /* No route */
   free(dist); free(unvis);
   return INF;
}
