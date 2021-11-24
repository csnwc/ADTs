#include "../coll.h"
#include "specific.h"

coll* coll_init(void)
{
   coll* c = (coll*) ncalloc(1, sizeof(coll));
   c->a = (colltype*) ncalloc(FIXEDSIZE, sizeof(colltype));
   c->size = 0;
   c->capacity= FIXEDSIZE;
   return c;
}

void coll_add(coll* c, colltype d)
{
   if(c){
      if(c->size >= c->capacity){
         c->a = (colltype*) nremalloc(c->a,
                sizeof(colltype)*c->capacity*SCALEFACTOR);
         c->capacity = c->capacity*SCALEFACTOR;
      }
      c->a[c->size] = d;
      c->size = c->size + 1;
   }
}

int coll_size(coll* c)
{
   if(c==NULL){
      return 0;
   }
   return c->size;
}

bool coll_isin(coll* c, colltype d)
{
   for(int i=0; i<coll_size(c); i++){
      if(c->a[i] == d){ 
          return true;
      }
   }
   return false;
}


bool coll_remove(coll* c, colltype d)
{
   bool found = false;
   for(int i=0; i<coll_size(c); i++){
      if(c->a[i] == d){ 
         // Shuffle end of array left one :-(
         c->size = c->size - 1;
         for(int j=i; j<coll_size(c); j++){
            c->a[j] = c->a[j+1];
         }
         found = true;
      }
   }
   return found;
}

bool coll_free(coll* c)
{
   if(c==NULL){
      return true;
   }
   free(c->a);
   free(c);
   return true;
}
