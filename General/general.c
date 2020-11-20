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

void* nrecalloc(void* p, int oldsz, int newsz)
{
   void* v = calloc(newsz, 1);
   if(v==NULL){
      on_error("Cannot calloc() space");
   }
   memcpy(v, p, oldsz);
   free(p);
   return v;
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
