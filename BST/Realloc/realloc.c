#include "specific.h"
#include "../bst.h"

#define NODELINE 30

void _freeframes(dataframe* frame);
bool _insert(bst* b, treetype d, int c);
bool _isin(bst* b, treetype d, int c);
int _size(bst* b, int c);
int _leftchild(int c);
int _rightchild(int c);
int _parent(int c);
void _write(bst* b, treetype d, int c);
bool _isvalid(bst* b, int c);
char* _printlisp(bst* b, int c);
void _todot(bst* b, int c, char* nodes);
char* _preorder(bst*b, int n);

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

bool bst_insert(bst* b, treetype d)
{
   if(b==NULL){
      return false;
   }
   return _insert(b, d, 0);
}

bool bst_isin(bst* b, treetype d)
{
   if(b==NULL){
      return false;
   }
   return _isin(b, d, 0);
}

bool bst_insertarray(bst* b, treetype* a, int n)
{
   if((b==NULL) || (a==NULL) || (n<=0)){
      return false;
   }
   for(int i=0; i<n; i++){
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

void bst_printlevel(bst* b)
{
   treetype n;
   if((b==NULL) || (! _isvalid(b, 0))){
      return;
   }
   /* Make a queue of cell indices */
   queue* q = queue_init();
   queue_enqueue(q, 0);
   while(queue_dequeue(q, &n) && _isvalid(b, (int)n)){
      printf(FORMATSTR, b->a[n].d);
      putchar(' ');
      queue_enqueue(q, _leftchild((int)n));
      queue_enqueue(q, _rightchild((int)n));
   }
}

char* bst_preorder(bst* b)
{
   char* p;
   if(b==NULL){
      p = ncalloc(1,1);
      return p;
   }
   return _preorder(b, 0);
}


char* bst_printlisp(bst* b)
{
   char* str;
   if((b==NULL) || (bst_size(b)<1)){
      str = ncalloc(1,1);
      return str;
   }
   return _printlisp(b, 0);
}

void bst_todot(bst* b, char* fname)
{

   if(b==NULL){
      return;
   }
   char* str = ncalloc(1, (ELEMSIZE+NODELINE)*b->capacity);
   sprintf(str, "digraph G {\n   node [shape=record, height=0.1];\n");
   _todot(b, 0, str);
   strcat(str, "}\n");
   char* opname = ncalloc(1, strlen(fname)+strlen(BSTTYPE)+1);
   sprintf(opname, "%s%s", BSTTYPE, fname);
   FILE* fp = nfopen(opname, "wt"); 
   fprintf(fp, "%s", str);
   fclose(fp);
   free(str);
   free(opname);

}


/******************************************************************/
/*                      Auxiliary Functions                       */
/******************************************************************/

/* Based on geekforgeeks.org */
bool _insert(bst* b, treetype d, int c)
{
    if (!_isvalid(b, c)){
       _write(b, d, c);
       return true;
    }
    /* Otherwise, recurs down the tree */
    treetype i = b->a[c].d;
    if (d < i){
        return _insert(b, d, _leftchild(c));
    }
    if(d > i){
       return _insert(b, d, _rightchild(c));
    }
    /* Must be the same, ignore */
    return true;
}

bool _isin(bst* b, treetype d, int c)
{
   if (!_isvalid(b, c)){
      return false;
   }
   treetype i = b->a[c].d;
   if(i == d){
      return true;
   }
   if(d < i){
      return _isin(b, d, _leftchild(c));
   }
   else{
      return _isin(b, d, _rightchild(c));
   }
   return false;
}

int _size(bst* b, int c)
{
   if(!_isvalid(b, c)){
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

int _parent(int c)
{
   return (c+1)/2 - 1;
}

void _write(bst* b, treetype d, int c)
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

bool _isvalid(bst* b, int c)
{
   if(c >= b->capacity){
      return false;
   }
   return b->a[c].isvalid;
}

char* _printlisp(bst* b, int c)
{
   char* p;
   if(! _isvalid(b, c)){
      /*  \0 string */
      p = ncalloc(1,1);
      return p;
   }
   char tmp[ELEMSIZE];
   sprintf(tmp, FORMATSTR, b->a[c].d);
   char* s1 = _printlisp(b,  _leftchild(c));
   char* s2 = _printlisp(b, _rightchild(c));
   p = ncalloc(strlen(s1)+strlen(s2)+strlen(tmp)+strlen("()() "), 1);
   sprintf(p, "%s(%s)(%s)", tmp, s1, s2);
   free(s1);
   free(s2);
   return p;
}

void _todot(bst* b, int c, char* nodes)
{
   int p;
   char tmp[1000];
   char fstr[500];
   if(! _isvalid(b, c)){
      return;
   }
   sprintf(fstr, FORMATSTR, b->a[c].d);
   sprintf(tmp, "   node%i [label = \"<l> | <m> %s | <r>\"];\n", c, fstr);
   strcat(nodes, tmp);
   /* Not top of tree */
   if(c>0){
      p = _parent(c);
      sprintf(tmp, "   node%i:%c -> node%i:m;\n", p, (c%2)?'l':'r', c);
      strcat(nodes, tmp);
   }
   _todot(b,  _leftchild(c), nodes);
   _todot(b, _rightchild(c), nodes);

}

char* _preorder(bst*b, int n)
{
   char tmp[ELEMSIZE];
   char *s1, *s2, *p;
   
   if(! _isvalid(b, n)){
      /*  \0 string */
      p = ncalloc(1,1);
      return p;
   }
   sprintf(tmp, FORMATSTR, b->a[n].d);
   s1 = _preorder(b,  _leftchild(n));
   s2 = _preorder(b, _rightchild(n));
   p = ncalloc(strlen(s1)+strlen(s2)+strlen(tmp)+strlen("   "), 1);
   strcpy(p, tmp);
   if(strlen(s1)){
      strcat(p, " ");
      strcat(p, s1);
   }
   if(strlen(s2)){
      strcat(p, " ");
      strcat(p, s2);
   }
   free(s1);
   free(s2);
   return p;

}
