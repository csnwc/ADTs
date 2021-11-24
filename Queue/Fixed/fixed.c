#include "../queue.h"
#include "specific.h"

void _inc(queuetype* p);

queue* queue_init(void)
{
   queue* q = (queue*) ncalloc(1, sizeof(queue));
   return q;
}


void queue_enqueue(queue* q, queuetype d)
{
   if(q){
      q->a[q->end] = d;
      _inc(&q->end);
      if(q->end == q->front){
         on_error("Queue too large");
      }
   }
}

bool queue_dequeue(queue* q, queuetype* d)
{
   if((q==NULL) || (q->front==q->end)){
      return false;
   }
   *d = q->a[q->front];
   _inc(&q->front);
   return true;
}

void queue_tostring(queue* q, char* str)
{
   char tmp[ELEMSIZE];
   str[0] = '\0';
   if((q==NULL) || (queue_size(q)==0)){
      return;
   }
   for(int i=q->front; i != q->end;){
      sprintf(tmp, FORMATSTR, q->a[i]); 
      strcat(str, tmp);
      strcat(str, "|");
      _inc(&i);
   }
   str[strlen(str)-1] = '\0';
}

int queue_size(queue* q)
{
   if(q==NULL){
      return 0;
   }
   if(q->end >= q->front){
      return q->end-q->front;
   }
   return q->end + BOUNDED - q->front;
}

bool queue_free(queue* q)
{
   free(q);
   return true;
}

void _inc(queuetype* p)
{
   *p = (*p + 1) % BOUNDED;
}

































void queue_todot(queue* s, char* fname)
{
   char tmp[DOTFILE];
   char str[DOTFILE];
   FILE* fp;
   queue_tostring(s, str);
   sprintf(tmp, "digraph structs\n{\n rankdir = TB;\n node [shape=record];\n Queue [label=\"");
   strcat(tmp, str);
   strcat(tmp, "|\"];\n}\n");
   sprintf(str, "%s%s", QUEUETYPE, fname);
   fp = nfopen(str, "wt");
   fprintf(fp, "%s\n", tmp);
   fclose(fp);
}
