/**
 * Simple stub for FSM
 */

#include <stdio.h>
#include <stdlib.h>
#include "stub_fsm.h"

#define EXIT_STATE   end
#define ENTRY_STATE  entry

// TODO: Avoid external decl there
extern StateFuncT state_functions[];

int main()
{
   StateT cur_state = ENTRY_STATE;

   for (;;)
   {
      // TODO: introduce typedef for function pointer
      const StateFuncT state_func = state_functions[cur_state];
      const StateReturnCodeT return_code = state_func();

#ifdef _DEBUG
      printf("Current state %d return %d\n",
         cur_state,
         return_code);
#endif

      if (cur_state == EXIT_STATE)
      {
         break;
      }

      cur_state = lookup_transitions(cur_state, return_code);
   }

   return EXIT_SUCCESS;
}
