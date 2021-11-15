#include <string.h>

typedef int treetype;
#define FORMATSTR "%i"
#define ELEMSIZE 20
#define BSTTYPE "Linked"

struct dataframe {
   treetype d;
   struct dataframe* left;
   struct dataframe* right;
};
typedef struct dataframe dataframe;

struct bst {
   dataframe* top;
   /* Data element size, in bytes */
};
typedef struct bst bst;
