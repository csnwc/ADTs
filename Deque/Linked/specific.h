#pragma once

#define FORMATSTR "%d"
#define ELEMSIZE 20

#define DEQUETYPE "Linked"

struct dataframe {
   dequetype d;
   struct dataframe* next;
   struct dataframe* prev;
};
typedef struct dataframe dataframe;

struct deque {
   /* Underlying array */
   dataframe* front;
   dataframe* end;
   int size;
};












#define DOTFILE 5000
