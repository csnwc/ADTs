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

void n2dfree(void**p, int h)
{
   for(i=0; i<h; i++){
      free(p[i]);
   }
   free(p);
}

void** n2dcalloc(int h, int w, size_t szelem)
{

   int i;
   void** p;
   p = calloc(h, szelem);
   if(p==NULL){
      on_error("Cannot calloc() space");
   }
   for(i=0; i<h; i++){
      p[i] = calloc(w, szelem);
      if(p[i]==NULL){
         on_error("Cannot calloc() space");
      }
   }
   return p;
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

void* nremalloc(void* p, int bytes)
{
   void* n = realloc(p, bytes);
   if(n==NULL){
      on_error("Cannot malloc() space");
   }
   return n;
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
