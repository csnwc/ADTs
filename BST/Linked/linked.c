#include "specific.h"
#include "../bst.h"

#define NODELINE 100

void _freeframes(dataframe* frame);
dataframe* _insert(dataframe* t, datatype d);
bool _isin(dataframe* t, datatype d);
int _size(dataframe* b);
char* _printlisp(dataframe* t);
void _todot(dataframe* t, char* nodes, dataframe* parent, char plr);

bst* bst_init(void)
{
   bst* b = (bst*) ncalloc(1, sizeof(bst));
   return b;
}

int bst_size(bst* b)
{
   if(b==NULL){
      return 0;
   }
   return _size(b->top);
}

bool bst_insert(bst* b, datatype d)
{
   if(b==NULL){
      return false;
   }
   if(b->top == NULL){
      b->top = _insert(b->top, d);
      return true;
   }
   _insert(b->top, d);
   return true;
}

bool bst_isin(bst* b, datatype d)
{
   if(b==NULL){
      return false;
   }
   return _isin(b->top, d);
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

char* bst_printlisp(bst* b)
{
   char* str;
   if(b==NULL){ 
      str = ncalloc(1,1);
      str[0] = '\0';
      return str;
   }
   return _printlisp(b->top);
}

bool bst_free(bst* b)
{
   if(b==NULL){ 
      return false;
   }
   _freeframes(b->top);
   free(b);
   return true;
}

void bst_todot(bst* b, char* fname)
{

   FILE* fp;
   char* str;
   char* opname;
   if(b==NULL){
      return;
   }
   str = ncalloc(1, (ELEMSIZE+NODELINE)*bst_size(b));
   sprintf(str, "digraph G {\n   node [shape=record, height=0.1];\n");
   _todot(b->top, str, NULL, 'X');
   strcat(str, "}\n");
   opname = ncalloc(1, strlen(fname)+strlen(BSTTYPE)+1);
   sprintf(opname, "%s%s", BSTTYPE, fname);
   fp = nfopen(opname, "wt"); 
   fprintf(fp, "%s", str);
   fclose(fp);
   free(str);
   free(opname);

}


/*****************************************************************/
/*                      Auxiliary Functions                       */
/*****************************************************************/

/* Based on geekforgeeks.org */
dataframe* _insert(dataframe* t, datatype d)
{
    dataframe* f;
    /* If the tree is empty, return a new frame */
    if (t == NULL){
       f = ncalloc(sizeof(dataframe), 1);
       f->d = d;
       return f;
    }
    /* Otherwise, recurs down the tree */
    if (d < t->d){
        t->left = _insert(t->left, d);
    }
    else if(d > t->d){
       t->right = _insert(t->right, d);
    }
    /* return the (unchanged) dataframe pointer */
    return t;
}

bool _isin(dataframe* t, datatype d)
{
   if(t==NULL){
      return false;
   }
   if(t->d == d){
      return true;
   }
   if(d < t->d){
      return _isin(t->left,  d);
   }
   else{
      return _isin(t->right, d);
   }
   return false;
}

void _freeframes(dataframe* t)
{
   if(t== NULL){
      return;
   }
   _freeframes(t->left);
   _freeframes(t->right);
   free(t);
}

int _size(dataframe* t)
{
   if(t==NULL){
      return 0;
   }
   return 1 + _size(t->left) + _size(t->right);
}

char* _printlisp(dataframe* t)
{
   char tmp[ELEMSIZE];
   char *s1, *s2, *p;
   
   if(t==NULL){
      /*  \0 string */
      p = ncalloc(1,1);
      return p;
   }
   sprintf(tmp, FORMATSTR, t->d);
   s1 = _printlisp(t->left);
   s2 = _printlisp(t->right);
   p = ncalloc(strlen(s1)+strlen(s2)+strlen(tmp)+strlen("()() "), 1);
   sprintf(p, "%s(%s)(%s)", tmp, s1, s2);
   free(s1);
   free(s2);
   return p;
}

void _todot(dataframe* t, char* nodes, dataframe* parent, char plr)
{
   char tmp[1000];
   char fstr[1000];
   if(t==NULL){
      return;
   }
   sprintf(fstr, FORMATSTR, t->d);
   sprintf(tmp, "   node%p [label = \"<l> | <m> %s | <r>\"];\n", (void*)t, fstr);
   strcat(nodes, tmp);
   if(parent != NULL){
      sprintf(tmp, "   node%p:%c -> node%p:m;\n", (void*)parent, plr, (void*)t);
      strcat(nodes, tmp);
   }
   _todot(t->left,  nodes, t, 'l');
   _todot(t->right, nodes, t, 'r');

}
