#define GRAPHTYPE "Realloc"

#define INITSIZE 8
#define SCALEFACTOR 2

#define NO_VERT -1

typedef unsigned int edge;

struct vertex {
   char* label;
   struct vertex* nextv;
   void* edgelist;
};
typedef struct vertex vertex;

struct edge {
   edge weight;
   vertex* v;
   vertex* nexte;
};
typedef struct edge edgel;

struct graph {
   vertex* firstv;
   vertex* endv;
   int size;
};
typedef struct graph graph;
