#include "stack.h"
#include "specific.h"

#define MAXINPUT 1000

int main(void)
{
   char input[MAXINPUT];
   stacktype d, g1, g2;

   stack* s = stack_init();
   while(fgets(input, MAXINPUT, stdin)){
      /* If number push */
      if(sscanf(input, FORMATSTR, &d)==1){
         stack_push(s, d);
      }
      else{
         /* Must be an operator ? */
         assert(stack_pop(s, &g2));
         assert(stack_pop(s, &g1));
         switch(input[0]){
            case '+' :
               d = g1 + g2;
               break;
            case '-' :
               d = g1 - g2;
               break;
            case '*' :
               d = g1 * g2;
               break;
            case '/' :
               d = g1 / g2;
               break;
            default:
               fprintf(stderr, "Can't understand that ? %i\n", input[0]);
               exit(EXIT_FAILURE);
         }
         stack_push(s, d);
      }
   }
   assert(stack_pop(s, &d));
   printf("Answer = ");
   printf(FORMATSTR, d);
   printf("\n");
   
   if(stack_peek(s, &d) == true){
      fprintf(stderr, "Stack still had items on it ?\n");
      exit(EXIT_FAILURE);
   }
   stack_free(s);
   return 0;
}
