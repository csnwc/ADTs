#define GRAPHTYPE "Linked"

#define INITSIZE 8
#define SCALEFACTOR 2

#define TMPSTR 1000

#define NO_VERT -1

typedef unsigned int edge;

struct vertex {
   char* label;
   struct vertex* nextv;
   void* firste;
   int num;
};
typedef struct vertex vertex;

struct edge {
   edge weight;
   vertex* v;
   struct edge* nexte;
};
typedef struct edge edgel;

struct graph {
   vertex* firstv;
   vertex* endv;
   int size;
};
typedef struct graph graph;
