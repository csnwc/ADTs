typedef int stacktype;
#define FORMATSTR "%d"
#define ELEMSIZE 20
#define STACKTYPE "Linked"

struct dataframe {
   stacktype i;
   struct dataframe* next;
};
typedef struct dataframe dataframe;

struct stack {
   /* Underlying array */
   dataframe* start;
   int size;
};
