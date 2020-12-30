#pragma once

#include "../General/general.h"
#include "../General/bool.h"

typedef int stacktype;

typedef struct stack stack;

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* Create an empty stack */
stack* stack_init(void);
/* Add element to top */
void stack_push(stack* s, stacktype i);
/* Take element from top */
bool stack_pop(stack* s, stacktype* d);
/* Clears all space used */
bool stack_free(stack* s);

/* Optional? */

/* Copy top element into d (but don't pop it) */
bool stack_peek(stack*s,  stacktype* d);
/* Make a string version - keep .dot in mind */
void stack_tostring(stack*, char* str);























/* Output a picture in the GraphViz/.dot format */
void stack_todot(stack*, char* fname);
