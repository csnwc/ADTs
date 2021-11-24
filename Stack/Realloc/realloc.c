#include "../stack.h"
#include "specific.h"

#define DOTFILE 5000

stack* stack_init(void)
{
   stack *s = (stack*) ncalloc(1, sizeof(stack));
   /* Some implementations would allow you to pass
      a hint about the initial size of the stack */
   s->a = (stacktype*) ncalloc(FIXEDSIZE, sizeof(stacktype));
   s->size = 0;
   s->capacity= FIXEDSIZE;
   return s;
}

void stack_push(stack* s, stacktype d)
{
   if(s==NULL){
       return;
   }
   if(s->size >= s->capacity){
      s->a = (stacktype*) nremalloc(s->a,
             sizeof(stacktype)*s->capacity*SCALEFACTOR);
      s->capacity = s->capacity*SCALEFACTOR;
   }
   s->a[s->size] = d;
   s->size = s->size + 1;
}

bool stack_pop(stack* s, stacktype* d)
{
   if((s == NULL) || (s->size < 1)){
      return false;
   }
   s->size = s->size - 1;
   *d = s->a[s->size];
   return true;
}

bool stack_peek(stack* s, stacktype* d)
{
   if((s==NULL) || (s->size <= 0)){
      /* Stack is Empty */
      return false;
   }
   *d = s->a[s->size-1];
   return true;
}

void stack_tostring(stack* s, char* str)
{
   char tmp[ELEMSIZE];
   str[0] = '\0';
   if((s==NULL) || (s->size <1)){
      return;
   }
   for(int i=s->size-1; i>=0; i--){
      sprintf(tmp, FORMATSTR, s->a[i]); 
      strcat(str, tmp);
      strcat(str, "|");
   }
   str[strlen(str)-1] = '\0';
}

bool stack_free(stack* s)
{
   if(s==NULL){
      return true;
   }
   free(s->a);
   free(s);
   return true;
}





























 
 
void stack_todot(stack* s, char* fname)
{
   char tmp[DOTFILE];
   char str[DOTFILE];
   FILE* fp;
   stack_tostring(s, str);
   sprintf(tmp, "digraph structs\n{\n rankdir = LR;\n node [shape=record];\n stack [label=\"");
   strcat(tmp, str);
   strcat(tmp, "\"];\n}\n");
   sprintf(str, "%s%s", STACKTYPE, fname);
   fp = nfopen(str, "wt");
   fprintf(fp, "%s\n", tmp);
   fclose(fp);
}
