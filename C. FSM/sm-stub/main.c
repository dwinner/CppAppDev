/**
 * Simple stub for FSM
 */

#include <stdio.h>
#include <stdlib.h>
#include "stub_fsm.h"

#define EXIT_STATE   end
#define ENTRY_STATE  entry

// TODO: Avoid external decl there
extern StateReturnCodeT (*p_state_func[])(void);

int main()
{
   StateT cur_state = ENTRY_STATE;

   for (;;)
   {
      // TODO: introduce typedef for function pointer
      StateReturnCodeT (*state_fun)(void) = p_state_func[cur_state];
      const StateReturnCodeT return_code = state_fun();

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
