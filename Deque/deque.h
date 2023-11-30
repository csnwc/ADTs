#pragma once 

#include "../General/general.h"

typedef int dequetype;

typedef struct deque deque;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Create an empty deque */
deque* deque_init(void);

/* Add element to front */
bool deque_addfront(deque* d, dequetype n);
/* Remove element from front */
bool deque_removefront(deque* d, dequetype* n);
/* Add element to end */
bool deque_addend(deque* d, dequetype n);
/* Remove element from end */
bool deque_removeend(deque* d, dequetype* n);


/* Return size of deque */
int deque_size(const deque* d);
/* Clears all space used */
bool deque_free(deque* d);

/* Helps with visualisation & testing */
void deque_tostring(deque* d, char* str);


























/* Write to Graphvis .dot file, later  use:
   cat q.dot | dot -Tpdf -o q.pdf
*/
void deque_todot(deque* s, char* fname);
