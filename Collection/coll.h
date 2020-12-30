#include "../General/general.h"
#include "../General/bool.h"

typedef int colltype;

typedef struct coll coll;

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Create an empty coll */
coll* coll_init(void);
/* Add element onto top */
void coll_add(coll* c, colltype i);
/* Take element out */
bool coll_remove(coll* c, colltype d);
/* Does this exist ? */
bool coll_isin(coll* c, colltype i);
/* Return size of coll */
int coll_size(coll* c);
/* Clears all space used */
bool coll_free(coll* c);
