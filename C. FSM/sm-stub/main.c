/**
 * Simple stub for FSM
 */

#include <stdio.h>
#include <stdlib.h>
#include "sm-utils.h"
#include "stub_fsm.h"

#define EXIT_STATE   end_state
#define ENTRY_STATE  entry_state

int main()
{
   StateT current_state = ENTRY_STATE;

   for (;;)
   {
      const StateFuncT state_func = state_functions[current_state];
      const StateReturnCodeT return_code = state_func();

      if (current_state == EXIT_STATE)
      {
         break;
      }

      const StateT previous_state = current_state;
      current_state = lookup_transitions(current_state, return_code);

#ifdef _DEBUG
      printf("Current state '%s' went into state '%s' with action result '%s'\n",
             state_to_str(previous_state),
             state_to_str(current_state),
             state_code_to_str(return_code));
#endif
   }

   return EXIT_SUCCESS;
}
