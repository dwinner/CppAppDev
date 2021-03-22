#include <stdlib.h>
#include "sm-utils.h"

int rand_lim(int limit)
{
   const int divisor = RAND_MAX / (limit + 1);
   int ret_val = 0;

   do
   {
      ret_val = rand() / divisor;
   }
   while (ret_val > limit);

   return ret_val;
}

char *state_code_to_str(const StateReturnCodeT state_code)
{
   switch (state_code)
   {
      case ok_code:
         return "Ok";

      case fail_code:
         return "Fail";

      case repeat_code:
         return "Repeat";

      case invalid_code:
         return "Invalid";

      default:
         return "Missing";
   }
}

char *state_to_str(const StateT state)
{
   switch (state)
   {
      case entry_state:
         return "Entry state";

      case foo_state:
         return "Foo state";

      case bar_state:
         return "Bar state";

      case end_state:
         return "End state";

      case invalid_state:
         return "Invalid state";

      default:
         return "Missing state";
   }
}
