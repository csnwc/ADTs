#include "../deque.h"
#include "specific.h"

void print(deque* d);
dataframe* _makedataframe(dequetype n);

deque* deque_init(void)
{
   deque* d = (deque*) ncalloc(1, sizeof(deque));
   return d;
}

bool deque_addfront(deque* d, dequetype n)
{
   int sz = deque_size(d);
   if(d==NULL){
      return false;
   }
   dataframe* p = _makedataframe(n);
   if(sz==0){
      d->end = p;
   }
   else{
      d->front->prev = p;
      p->next = d->front;
   }
   d->front = p;
   d->size = sz + 1;
   return true;
}

bool deque_addend(deque* d, dequetype n)
{
   int sz = deque_size(d);
   if(d==NULL){
      return false;
   }
   dataframe* p = _makedataframe(n);
   if(sz==0){
      d->front = p;
   }
   else{
      d->end->next = p;
      p->prev = d->end;
   }
   d->end = p;
   d->size = sz + 1;
   return true;
}

bool deque_removefront(deque* d, dequetype* n)
{
   int sz = deque_size(d);
   if((d==NULL) || (n==NULL) || (sz==0)){
      return false;
   }
   dataframe* p = d->front;
   *n = p->d;
   d->front = p->next;
   d->size = sz - 1;
   if(d->size == 0){
      d->end = NULL;
   }
   else{
      d->front->prev = NULL;
   }
   free(p);
   return true;
}

bool deque_removeend(deque* d, dequetype* n)
{
   int sz = deque_size(d);
   if((d==NULL) || (n==NULL) || (sz==0)){
      return false;
   }
   dataframe* p = d->end;
   *n = p->d;
   d->end = p->prev;
   d->size = sz - 1;
   if(d->size == 0){
      d->front = NULL;
   }
   else{
      d->end->next = NULL;
   }
   free(p);
   return true;
}

void deque_tostring(deque* d, char* str)
{
   char tmp[ELEMSIZE];
   if(!str){
      return;
   }
   str[0] = '\0';
   if((d==NULL) || (deque_size(d)==0) ){
      return;
   }
   dataframe* p = d->front;
   for(int i=0; i<deque_size(d); i++){
      sprintf(tmp, FORMATSTR, p->d); 
      strcat(str, tmp);
      strcat(str, "|");
      p = p->next;
   }
   str[strlen(str)-1] = '\0';
}

int deque_size(const deque* d)
{
   if(d==NULL){
      return 0;
   }
   return d->size;
}

bool deque_free(deque* d)
{
   dataframe* f = d->front;
   while(f){
      dataframe* t = f->next;
      free(f);
      f = t;
   }
   free(d);
   return true;
}








dataframe* _makedataframe(dequetype n)
{
   dataframe* p = (dataframe*) ncalloc(1, sizeof(dataframe));
   p->d = n;
   return p;
}






















/*
void deque_todot(deque* d, char* fname)
{
   char tmp[DOTFILE];
   char str[DOTFILE];
   FILE* fp;
   deque_tostring(d, str);
   sprintf(tmp, "digraph structs\n{\n rankdir = TB;\n node [shape=record];\n Queue [label=\"");
   strcat(tmp, str);
   strcat(tmp, "|\"];\n}\n");
   sprintf(str, "%s%s", DEQUETYPE, fname);
   fp = nfopen(str, "wt");
   fprintf(fp, "%s\n", tmp);
   fclose(fp);
}
*/
