#define GRAPHTYPE "Realloc"

#define INITSIZE 8
#define SCALEFACTOR 2

#define TMPSTR 1000

#define NO_VERT -1

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
