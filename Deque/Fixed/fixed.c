#include "../deque.h"
#include "specific.h"

void _move(int* p, int n);
bool _add(deque* d, dequetype n, int* counter, int offset);
bool _remove(deque* d, dequetype* n, int* counter, int offset);

deque* deque_init(void)
{
   deque* d = (deque*) ncalloc(1, sizeof(deque));
   d->front = d->end = BOUNDED/2;
   return d;
}

bool deque_addfront(deque* d, dequetype n)
{
   return _add(d, n, &d->front, -1);
}

bool deque_addend(deque* d, dequetype n)
{
   return _add(d, n, &d->end, +1);
}

bool deque_removefront(deque* d, dequetype* n)
{
   return _remove(d, n, &d->front, +1);
}

bool deque_removeend(deque* d, dequetype* n)
{
   return _remove(d, n, &d->end, -1);
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
   int f = d->front;
   for(int i=0; i<deque_size(d); i++){
      //printf("Here >%d<\n", d->a[f]);
      sprintf(tmp, FORMATSTR, d->a[f]); 
      strcat(str, tmp);
      strcat(str, "|");
      _move(&f, +1);
   }
   str[strlen(str)-1] = '\0';
}

int deque_size(deque* d)
{
   if(d==NULL){
      return 0;
   }
   return d->size;
}

bool deque_free(deque* d)
{
   free(d);
   return true;
}

// Wrap index around array to keep it in-bounds
void _move(int* p, int n)
{
   *p = ((*p + n) + BOUNDED) % BOUNDED;
}

// counter pointer to d->front or d->end
// offset moves front/end +1/-1 depending on context
bool _add(deque* d, dequetype n, int* counter, int offset)
{
   int sz = deque_size(d);
   if((d==NULL) || (sz==BOUNDED) || (counter==NULL)){
      return false;
   }
   // 1st insertion doesn't change front/end counter
   if(sz>0){
      _move(counter, offset);
   }
   d->a[*counter] = n;
   d->size = d->size + 1;
   return true;
}

bool _remove(deque* d, dequetype* n, int* counter, int offset)
{
   int sz = deque_size(d);
   if((d==NULL) || (sz==0) || (counter==NULL)){
      return false;
   }
   *n = d->a[*counter];
   // d->front/end same for size==0 and size==1
   if(sz>1){
      _move(counter, offset);
   }
   d->size = d->size - 1;
   return true;
}
























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
