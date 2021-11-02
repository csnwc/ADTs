#pragma once

#define COLLTYPE "Realloc"

#define FIXEDSIZE 16
#define SCALEFACTOR 2
struct coll {
   // Underlying array
   colltype* a;
   int size;
   int capacity;
};
