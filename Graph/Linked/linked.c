#include "../graph.h" 

#define MAXLABEL 100

bool _isedge(graph* g, int f, int t);
int _countedges(graph* g);

graph* graph_init(void)
{
   graph* g = (graph*) ncalloc(sizeof(graph), 1);
   return g;
}

/*
edge graph_getEdgeWeight(graph* g, int from, int to)
{
   if((g==NULL) || (from >= g->size) || (to >= g->size)){
      return INF;
   }
   return g->adjMat[from][to];
}
*/


int graph_numVerts(graph* g)
{
   vertex* v;
   int cnt = 0;
   if(g==NULL){
      return 0;
   }
   v = g->firstv;
   while(v != NULL){
      cnt++;
      v = v->nextv;
   }
   return cnt;
}

bool graph_free(graph* g)
{
   if(g==NULL){
      return false;
   }
   free(g);
   return true;
}

int graph_addVert(graph* g, char* label)
{

   vertex* n;
   if(g==NULL){
      printf("addVert NULL\n");
      return NO_VERT;
   }
   if(graph_getVertNum(g, label) != NO_VERT){
      printf("Already got it\n");
      return NO_VERT;
   }

   printf("Doof\n");
   n = ncalloc(sizeof(vertex), 1);
   n->label = ncalloc(strlen(label)+1, 1);
   strcpy(n->label, label);
   if(g->firstv == NULL){
      printf("addVert front\n");
      /* Put in front */
      g->firstv = n;
   }
   else{
      /* Add to end */
      g->endv->nextv = n;
   }
   g->endv = n;
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
   f = g->firstv;
   for(i=0; i<from; i++){
      f = f->nextv;
   }
   t = t->firstv;
   for(i=0; i<to; i++){
      t = t->nextv;
   }
   return _addEdge(f, t, w);
}

/*
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
*/

int graph_getVertNum(graph* g, char* label)
{
   int cnt = 0;
   vertex* v;
   v = g->firstv;
   while(v != NULL){
      if(strcmp(v->label, label)==0){
         return cnt;
      }
      v = v->nextv;
      cnt++;
   }
   return NO_VERT;
}

/*
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
*/

/************************************************************************/
/*                       Auxiliary Functions                            */
/************************************************************************/

bool _addEdge(vertex* f, vertex* t, edge w)
{

   edgel* e;
   if(f->firste ==NULL){
      /* 1st */
      f->nexte = ncalloc((sizeof)edgel, 1);
      f->nexte->v = t;
   }


}

/*
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
*/
