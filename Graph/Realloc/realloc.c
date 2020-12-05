#include "../graph.h" 

#define MAXLABEL 100

bool _isedge(graph* g, int f, int t);
int _countedges(graph* g);

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
         /* It's not clear if weight[j][j] should be 0 or INF */
         g->adjMat[j][i] = INF;
      }
   }
   return g;
}

edge graph_getEdgeWeight(graph* g, int from, int to)
{
   if((g==NULL) || (from >= g->size) || (to >= g->size)){
      return INF;
   }
   return g->adjMat[from][to];
}


int graph_numVerts(graph* g)
{
   if(g==NULL){
      return 0;
   }
   return g->size;
}

bool graph_free(graph* g)
{
   n2dfree((void**)g->adjMat, g->capacity);
   n2dfree((void**)g->labels, g->capacity);
   free(g);
   return true;
}

edge graph_dijkstra(graph* g, int from, int to)
{

   bool* unvis;
   edge* dist;
   edge e, cst;
   int v;
   int curr;

   if((g==NULL) || (from >= g->size) || (to >= g->size)){
      return INF;
   }
   unvis = (bool*)ncalloc(g->size, sizeof(bool));
   dist  = (edge*)ncalloc(g->size, sizeof(edge));
   for(v=0; v<g->size; v++){
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

int graph_addVert(graph* g, char* label)
{

   int i, j;
   if(g==NULL){
      return NO_VERT;
   }
   if(graph_getVertNum(g, label) != NO_VERT){
      return NO_VERT;
   }
   /* Resize */
   if(g->size >= g->capacity){
      g->adjMat = (edge**) n2drecalloc((void**)g->adjMat, g->capacity, g->capacity*SCALEFACTOR, g->capacity, g->capacity*SCALEFACTOR, sizeof(edge));
      g->labels = (char**) n2drecalloc((void**)g->labels, g->capacity, g->capacity*SCALEFACTOR, MAXLABEL+1, MAXLABEL+1,  1);
      for(j=0; j<g->capacity*SCALEFACTOR; j++){
         for(i=0; i<g->capacity*SCALEFACTOR; i++){
            if((i>=g->capacity)||(j>=g->capacity)){
               g->adjMat[j][i] = INF;
            }
         }
      }
      g->capacity = g->capacity*SCALEFACTOR;
   }
   strcpy(g->labels[g->size], label);
   g->size = g->size + 1;
   return g->size-1;
}

bool graph_addEdge(graph* g, int from, int to, edge w)
{
   if((g==NULL) || (g->size == 0)){
      return false;
   }
   if((from >= g->size) || (to >= g->size)){
      return false;
   }
   g->adjMat[from][to] = w;
   return true;
}

void graph_todot(graph* g, char* dotname)
{
   int f, t;
   char* fname;
   FILE* fp;
   fname = ncalloc(1,strlen(dotname)+strlen(GRAPHTYPE)+1);
   sprintf(fname, "%s%s", GRAPHTYPE, dotname);
   fp = nfopen(fname, "wt");
   fprintf(fp,"digraph {\n");
   for(f=0; f<g->size; f++){
      for(t=0; t<g->size; t++){
         if(_isedge(g, f, t)){
            fprintf(fp, "   %s -> %s[label=\"%d\"];\n",
               g->labels[f], g->labels[t], g->adjMat[f][t]);
         }
      }
   }
   fprintf(fp, "}\n");
   fclose(fp);
   free(fname);
}

int graph_getVertNum(graph* g, char* label)
{
   int f;
   for(f=0; f<g->size; f++){
      if(strcmp(g->labels[f], label)==0){
         return f;
      }
   }
   return NO_VERT;

}

void graph_tostring(graph* g, char* str)
{
   int f, t;
   char tmp[1000];
   str[0] = '\0';
   if(g==NULL){
      return;
   }
   for(f=0; f<g->size; f++){
      sprintf(tmp, "%s ", g->labels[f]);
      strcat(str, tmp);
   }
   for(f=0; f<g->size; f++){
      for(t=0; t<g->size; t++){
         if(_isedge(g,f,t)){
            sprintf(tmp, "%d->%d %d ",
                    f, t, g->adjMat[f][t]);
            strcat(str, tmp);
         }
      }
   }
}

/************************************************************************/
/*                       Auxiliary Functions                            */
/************************************************************************/

bool _isedge(graph* g, int f, int t)
{
   return (g->adjMat[f][t] == INF) ? false : true;
}

int _countedges(graph* g)
{
   int f, t;
   int cnt = 0;
   for(f=0; f<g->size; f++){
      for(t=0; t<g->size; t++){
         cnt += _isedge(g, f, t);
      }
   }
   return cnt;
}
