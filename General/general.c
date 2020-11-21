#include "general.h"

void on_error(const char* s)
{
   fprintf(stderr, "%s\n", s);
   exit(EXIT_FAILURE);
}

void* ncalloc(int n, size_t size)
{
   void* v = calloc(n, size);
   if(v==NULL){
      on_error("Cannot calloc() space");
   }
   return v;
}

void* nrecalloc(void* p, int oldbytes, int newbytes)
{
   void* n = calloc(newbytes, 1);
   if(n==NULL){
      on_error("Cannot calloc() space");
   }
   memcpy(n, p, oldbytes);
   free(p);
   return n;
}

void* nrealloc(void* p, int n)
{
   void* v = realloc(p, n);
   if(v==NULL){
      on_error("Cannot calloc() space");
   }
   return v;
}

void* nfopen(char* fname, char* mode)
{
   FILE* fp;
   fp = fopen(fname, mode);
   if(!fp){
      on_error("Cannot open file");
   }
   return fp;
}
