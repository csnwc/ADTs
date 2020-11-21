#include "specific.h"
#include "bst.h"

#define ARRSIZE 18

int main(void)
{

   bst* b;
   datatype arr[ARRSIZE] = {1,50,2,49,3,48,4,47,5,46,6,45,7,44,8,43,9,42};

   printf("Test BST (%s) Start ... ", BSTTYPE);

   assert(bst_size(NULL)==0);
   assert(!bst_insert(NULL, 10));
   assert(!bst_isin(NULL, 50));
   b = bst_init();
   assert(!bst_isin(NULL, 50));
   assert(bst_size(b)==0);
   assert(bst_insert(b, 50));
   assert(bst_size(b)==1);
   assert(bst_isin(b, 50));
   assert(bst_insert(b, 10));
   assert(bst_size(b)==2);
   assert(bst_isin(b, 10));
   assert(bst_insert(b, 90));
   assert(bst_size(b)==3);
   assert(bst_isin(b, 90));
   assert(bst_free(b));

   b = bst_init();
   bst_insertarray(b, arr, ARRSIZE);
   assert(bst_size(b)==ARRSIZE);

   assert(bst_free(b));
   printf("END\n");
   return 0;

}
