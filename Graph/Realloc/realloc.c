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
         /* It's not clear if weight[j][]j should be 0 or not */
         g->adjMat[j][i] = INF;
      }
   }
   return g;
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

int graph_addVert(graph* g, char* label)
{

   if(g==NULL){
      return NO_VERT;
   }
   if(graph_getVertNum(g, label) != NO_VERT){
      return NO_VERT;
   }
   /* Resize */
   if(g->size >= g->capacity){
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
            fprintf(fp, "   %s -> %s[label=\"%d\"];\n", g->labels[f],
                   g->labels[t], g->adjMat[f][t]);
         }
      }
   }
   fprintf(fp, "}\n");
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
