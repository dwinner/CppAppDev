/**
 * Simple stub for FSM
 */

#include <stdio.h>
#include <stdlib.h>
#include "stub_fsm.h"

#define EXIT_STATE   end
#define ENTRY_STATE  entry

// TODO: Avoid external decl there
extern state_return_code_t (*p_state_func[])(void);

int main()
{
   state_t cur_state = ENTRY_STATE;

   for (;;)
   {
      // TODO: introduce typedef for function pointer
      state_return_code_t (*state_fun)(void) = p_state_func[cur_state];
      const state_return_code_t return_code = state_fun();
      if (cur_state == EXIT_STATE)
      {
         break;
      }

      cur_state = lookup_transitions(cur_state, return_code);
   }

   return EXIT_SUCCESS;
}
