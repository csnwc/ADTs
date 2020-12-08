#include "../graph.h" 

#define MAXLABEL 100

bool _isedge(graph* g, int f, int t);
int _countedges(graph* g);
bool _addEdge(vertex* f, vertex* t, edge w);

graph* graph_init(void)
{
   graph* g = (graph*) ncalloc(sizeof(graph), 1);
   return g;
}

edge graph_getEdgeWeight(graph* g, int from, int to)
{
   int i;
   vertex *v;
   edgel* e;
   if((g==NULL) || (from >= g->size) || (to >= g->size)){
      return INF;
   }
   v = g->firstv;
   for(i=0; i<from; i++){
      v = v->nextv;
   }
   if((v==NULL) || (v->num != from)){
      return INF;
   }
   e = v->firste;
   while(e != NULL){
      if(e->v->num == to){
         return e->weight;
      }
      e = e->nexte;
   }
   return INF;
}

int graph_numVerts(graph* g)
{
    if(g==NULL||(g->endv==NULL)) {
        return 0;
    }
    return g->endv->num+1;
}

bool graph_free(graph* g)
{
   vertex* v, *tv;
   edgel* e, *te;
   if(g==NULL){
      return false;
   }
   v = g->firstv;
   while(v != NULL){
      e = v->firste;
      while(e != NULL){
         te = e->nexte;
         free(e);
         e = te;
      }
      tv = v->nextv;
      free(v->label);
      free(v);
      v = tv;
   }
   free(g);
   return true;
}

int graph_addVert(graph* g, char* label)
{

   vertex* n;
   if(g==NULL){
      return NO_VERT;
   }
   if(graph_getVertNum(g, label) != NO_VERT){
      return NO_VERT;
   }

   n = ncalloc(sizeof(vertex), 1);
   n->label = ncalloc(strlen(label)+1, 1);
   strcpy(n->label, label);
   if(g->firstv == NULL){
      /* Put in front */
      g->firstv = n;
   }
   else{
      /* Add to end */
      n->num = g->endv->num + 1;
      g->endv->nextv = n;
   }
   g->endv = n;
   g->size = g->size + 1;
   return g->size-1;
}

bool graph_addEdge(graph* g, int from, int to, edge w)
{
   vertex* f;
   vertex* t;
   int i;
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
   t = g->firstv;
   for(i=0; i<to; i++){
      t = t->nextv;
   }
   return _addEdge(f, t, w);
}

void graph_todot(graph* g, char* dotname)
{
   vertex* v;
   edgel* e;
   char* fname;
   FILE* fp;
   fname = ncalloc(1,strlen(dotname)+strlen(GRAPHTYPE)+1);
   sprintf(fname, "%s%s", GRAPHTYPE, dotname);
   fp = nfopen(fname, "wt");
   fprintf(fp,"digraph {\n");

   v = g->firstv;
   /* Edge Weights */
   while(v != NULL){
      e = v->firste;
      while(e != NULL){
         fprintf(fp, "   %s -> %s[label=\"%d\"];\n",
            v->label, e->v->label, e->weight);
         e = e->nexte;
      }
      v = v->nextv;
   }
   fprintf(fp, "}\n");
   fclose(fp);
   free(fname);
}

char* graph_getLabel(graph* g, int vtx)
{

   vertex* v;
   int i;
   if((g==NULL) || (vtx >= g->size)){
      return NULL;
   }
   v = g->firstv;
   for(i=0; i<vtx; i++){
      v = v->nextv;
   }
   return v->label;
}

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

void graph_tostring(graph* g, char* str)
{
   vertex* v;
   edgel* e;
   char tmp[TMPSTR];
   str[0] = '\0';
   if(g==NULL){
      return;
   }
   v = g->firstv;
   while(v != NULL){
      sprintf(tmp, "%s ", v->label);
      strcat(str, tmp);
      v = v->nextv;
   }
   v = g->firstv;
   /* Edge Weights */
   while(v != NULL){
      e = v->firste;
      while(e != NULL){
         sprintf(tmp, "%d->%d %d ", v->num, e->v->num, e->weight);
         strcat(str, tmp);
         e = e->nexte;
      }
      v = v->nextv;
   }
}

/************************************************************************/
/*                       Auxiliary Functions                            */
/************************************************************************/

bool _addEdge(vertex* f, vertex* t, edge w)
{

   edgel* e;
   edgel* b;
   if(f->firste ==NULL){
      /* 1st */
      e = ncalloc(sizeof(edgel), 1);
      f->firste = e;
      e->v = t;
      e->weight = w;
      return true;
   }
   e = f->firste;
   while(e != NULL){
      /* Already got it */
      if(e->v == t){
         return false;
      }
      b = e;
      e = e->nexte;
   }
   /* Add to end */
   b->nexte = ncalloc(sizeof(edgel), 1);
   b->nexte->v = t;
   b->nexte->weight = w;
   return true;
}
