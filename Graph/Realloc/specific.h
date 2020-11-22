#define GRAPHTYPE "Realloc"

#define INITSIZE 8
#define SCALEFACTOR 2

typedef enum bool {false, true} bool;

struct bst {
   edge** adjMat;
   char** labels;
   int size;
   int capacity;
   /* Data element size, in bytes */
};
typedef struct bst bst;
