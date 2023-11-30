#include "deque.h"
#include "specific.h"

int main(int argc, char* argv[])
{
   char str[1000000];
   dequetype n;
   deque* d;

   printf("Basic Deque (%s) Tests ... Start\n", DEQUETYPE);

   // Front
   deque_tostring(NULL, str); assert(strcmp(str, "")==0);
   d = deque_init();
   assert(d != NULL);
   assert(deque_size(d) == 0);
   deque_tostring(d, str); assert(strcmp(str, "")==0);

   assert(deque_addfront(d, 10));
   assert(deque_size(d) == 1);
   deque_tostring(d, str); assert(strcmp(str, "10")==0);

   assert(deque_addfront(d, 20));
   assert(deque_size(d) == 2);
   deque_tostring(d, str); assert(strcmp(str, "20|10")==0);

   assert(deque_removefront(d, &n));
   assert(n==20);
   assert(deque_size(d) == 1);
   deque_tostring(d, str); assert(strcmp(str, "10")==0);
   assert(deque_removefront(d, &n));
   assert(n==10);
   assert(deque_size(d) == 0);

   assert(deque_removefront(d, &n)==false);

   // End
   assert(deque_addend(d, 10));
   assert(deque_size(d) == 1);
   deque_tostring(d, str); assert(strcmp(str, "10")==0);

   assert(deque_addend(d, 30));
   assert(deque_size(d) == 2);
   deque_tostring(d, str); assert(strcmp(str, "10|30")==0);

   assert(deque_removeend(d, &n));
   assert(n==30);
   assert(deque_size(d) == 1);
   deque_tostring(d, str); assert(strcmp(str, "10")==0);
   assert(deque_removeend(d, &n));
   assert(n==10);
   assert(deque_size(d) == 0);

   assert(deque_removeend(d, &n)==false);


   #ifdef BOUNDED
   // Fill up Deque
   for(int i=0; i<BOUNDED/2; i++){
      assert(deque_addfront(d, -i));
      assert(deque_addend(d, i));
   }
   // One more is too many
   assert(deque_addfront(d, 0)==false);
   assert(deque_addend(d, 0) == false);
   #else
   for(int i=0; i<atoi(argv[1]); i++){
      n = rand()%100;
      bool b;
      switch(rand()%4){
         case 0:
            assert(deque_addfront(d, n));
            printf("Added %d to front\n", n);
            break;
         case 1:
            assert(deque_addend(d, n));
            printf("Added %d to end\n", n);
            break;
         case 2:
            b = deque_removefront(d, &n);
            if(b){
               printf("Removed %d from front\n", n);
            }
            else{
               printf("Can't remove from front\n");
            }
            break;
         case 3:
            b = deque_removeend(d, &n);
            if(b){
               printf("Removed %d from end\n", n);
            }
            else{
               printf("Can't remove from end\n");
            }
            break;
      }
      deque_tostring(d, str);
      //printf("%d : %s\n", deque_size(d), str);
   }
   #endif

/*
   // Front
   deque_tostring(NULL, str); assert(strcmp(str, "")==0);
   d = deque_init();
   assert(d != NULL);
   assert(deque_size(d) == 0);
   deque_tostring(d, str); assert(strcmp(str, "")==0);

   assert(deque_addend(d, 10));
   assert(deque_addend(d, 20));
   assert(deque_removeend(d, &n));
*/
      
   
   deque_free(d);
   printf("Basic Deque (%s) Tests ... End\n", DEQUETYPE);
   return 0;

}
