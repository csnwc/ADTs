#include "specific.h"
#include "../bst.h"

void _freeframes(dataframe* frame);
bool _insert(bst* b, datatype d, int c);
bool _isin(bst* b, datatype d, int c);
int _size(bst* b, int c);
int _leftchild(int c);
int _rightchild(int c);
void _safewrite(bst* b, datatype d, int c);
bool _safeisvalid(bst* b, int c);

bst* bst_init(void)
{
   bst* b = (bst*) ncalloc(1, sizeof(bst));
   b->capacity = INITSIZE;
   b->a = (dataframe*) ncalloc(b->capacity, sizeof(dataframe));
   return b;
}

int bst_size(bst* b)
{
   if(b==NULL){
      return 0;
   }
   return _size(b, 0);
}

bool bst_insert(bst* b, datatype d)
{
   if(b==NULL){
      return false;
   }
   return _insert(b, d, 0);
}

bool bst_isin(bst* b, datatype d)
{
   if(b==NULL){
      return false;
   }
   return _isin(b, d, 0);
}

bool bst_insertarray(bst* b, datatype* a, int n)
{
   int i;
   if((b==NULL) || (a==NULL) || (n<=0)){
      return false;
   }
   for(i=0; i<n; i++){
      bst_insert(b, a[i]);
   }
   return true;
}

bool bst_free(bst* b)
{
   if(b==NULL){ 
      return false;
   }
   free(b->a);
   free(b);
   return true;
}

/******************************************************************/
/*                      Auxiliary Functions                       */
/******************************************************************/

/* Based on geekforgeeks.org */
bool _insert(bst* b, datatype d, int c)
{
    datatype i;
    if (!_safeisvalid(b, c)){
       _safewrite(b, d, c);
       return true;
    }
    /* Otherwise, recurs down the tree */
    i = b->a[c].d;
    if (i < d){
        return _insert(b, d, _leftchild(c));
    }
    if(i > d){
       return _insert(b, d, _rightchild(c));
    }
    /* Must be the same, ignore */
    return true;
}

bool _isin(bst* b, datatype d, int c)
{
   datatype i;
   if (!_safeisvalid(b, c)){
      return false;
   }
   i = b->a[c].d;
   if(i == d){
      return true;
   }
   if(i < d){
      return _isin(b, d, _leftchild(c));
   }
   else{
      return _isin(b, d, _rightchild(c));
   }
   return false;
}

int _size(bst* b, int c)
{
   if(!_safeisvalid(b, c)){
      return 0;
   }
   return 1 + _size(b, _leftchild(c)) + _size(b, _rightchild(c));
}

int _leftchild(int c)
{
   return (2*c)+1;
}

int _rightchild(int c)
{
   return 2*(c+1);
}

void _safewrite(bst* b, datatype d, int c)
{
   int newsz;
   /* Resize, but how much ? */
   while(c >= b->capacity){
      newsz = (b->capacity+1)*SCALEFACTOR-1;
      b->a = nrecalloc(b->a, b->capacity*sizeof(dataframe), newsz*sizeof(dataframe));
      b->capacity = newsz;
   }
   b->a[c].d = d;
   b->a[c].isvalid = true;
}

bool _safeisvalid(bst* b, int c)
{
   if(c >= b->capacity){
      return false;
   }
   return b->a[c].isvalid;
}
