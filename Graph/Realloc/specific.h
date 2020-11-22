#define GRAPHTYPE "Realloc"

#define INITSIZE 8
#define SCALEFACTOR 2

typedef unsigned int edge;

struct graph {
   edge** adjMat;
   char** labels;
   /* Actual number of verts */
   int size;
   /* Max verts before realloc() */
   int capacity;
};
typedef struct graph graph;
