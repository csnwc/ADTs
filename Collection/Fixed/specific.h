#pragma once

#define COLLTYPE "Fixed"

#define FIXEDSIZE 5000
struct coll {
   /* Underlying array */
   colltype a[FIXEDSIZE];
   int size;
};
