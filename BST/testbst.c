#include "specific.h"
#include "bst.h"

#define ARRSIZE 15

int main(void)
{

   bst* b;
   char* str;
   datatype arr[ARRSIZE] = {50, 75, 25, 20, 30, 70, 80, 19, 21, 29, 31, 69, 71, 79, 81};

   printf("Test BST (%s) Start ... ", BSTTYPE);

   assert(bst_size(NULL)==0);
   assert(!bst_insert(NULL, 10));
   assert(!bst_isin(NULL, 50));
   b = bst_init();
   assert(!bst_isin(NULL, 50));
   assert(bst_size(b)==0);
   assert(bst_insert(b, 50));
   assert(bst_size(b)==1);
   str = bst_printlisp(b);
   assert(strcmp(str, "50()()")==0); free(str);
   assert(bst_isin(b, 50));
   assert(bst_insert(b, 10));
   assert(bst_size(b)==2);
   assert(bst_isin(b, 10));
   assert(bst_insert(b, 90));
   assert(bst_size(b)==3);
   assert(bst_isin(b, 90));
   str = bst_printlisp(b);
   assert(strcmp(str, "50(10()())(90()())")==0); free(str);
   str = bst_preorder(b);
   assert(strcmp(str, "50 10 90")==0); free(str);
   assert(bst_free(b));

   b = bst_init();
   bst_insertarray(b, arr, ARRSIZE);
   assert(bst_size(b)==ARRSIZE);
   bst_todot(b, "b.dot");
   str = bst_preorder(b);
   assert(strcmp(str, "50 25 20 19 21 30 29 31 75 70 69 71 80 79 81")==0); free(str);

   assert(bst_free(b));
   printf("END\n");
   return 0;

}
