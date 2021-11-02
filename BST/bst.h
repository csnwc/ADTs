#include "../General/general.h"
#include "../Queue/queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

bst* bst_init(void);

/* Insert 1 item into the tree */
bool bst_insert(bst* b, treetype d);

/* Return number of treetypes in tree */
int bst_size(bst* b);

/* Whether the data d is stored in the tree */
bool bst_isin(bst* b, treetype d);

/* Bulk insert n items from an array a into an initialised tree */
bool bst_insertarray(bst* b, treetype* a, int n);

/* Clear all memory associated with tree, & set pointer to NULL */
bool bst_free(bst* b);

/* Optional ? */

char* bst_preorder(bst* b);

void bst_printlevel(bst* b);

/* Create string with tree as ((head)(left)(right)) */
char* bst_printlisp(bst* b);

/* Use Graphviz via a .dot file */
void bst_todot(bst* b, char* dotname);
