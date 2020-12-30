#pragma once

#define COLLTYPE "Linked"

struct dataframe {
   colltype i;
   struct dataframe* next;
};
typedef struct dataframe dataframe;

struct coll {
   /* Underlying array */
   dataframe* start;
   int size;
};
