typedef int queuetype;
#define FORMATSTR "%d"
#define ELEMSIZE 20

#define QUEUETYPE "Fixed"

#define BOUNDED 5000

struct queue {
   /* Underlying array */
   queuetype a[BOUNDED];
   int front;
   int end;
};

#define DOTFILE 5000
