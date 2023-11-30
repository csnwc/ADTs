#pragma once

#define FORMATSTR "%d"
#define ELEMSIZE 20

#define DEQUETYPE "Fixed"

#define BOUNDED 5000

struct deque {
   /* Underlying array */
   dequetype a[BOUNDED];
   int front;
   int end;
   int size;
};

#define DOTFILE 5000
