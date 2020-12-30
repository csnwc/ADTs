#include "../General/general.h"
#include "../General/bool.h"
typedef struct queue queue;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Create an empty queue */
queue* queue_init(void);
/* Add element on end */
void queue_enqueue(queue* q, queuetype v);
/* Take element off front */
bool queue_dequeue(queue* q, queuetype* d);
/* Return size of queue */
int queue_size(queue* q);
/* Clears all space used */
bool queue_free(queue* q);

/* Helps with visualisation & testing */
void queue_tostring(queue* q, char* str);


























/* Write to Graphvis .dot file, later  use:
   cat q.dot | dot -Tpdf -o q.pdf
*/
void queue_todot(queue* s, char* fname);
