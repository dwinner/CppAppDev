/**
 * Simple stub for FSM
 */

#include <stdio.h>
#include <stdlib.h>
#include "stub_fsm.h"

#define EXIT_STATE end
#define ENTRY_STATE entry

extern int (*state[])(void);

enum state_codes lookup_transitions(enum state_codes codes, enum ret_codes codes1);

int main()
{
   enum state_codes cur_state = ENTRY_STATE;
   enum ret_codes rc;
   int (*state_fun)(void);

   for (;;)
   {
      state_fun = state[cur_state];
      rc = state_fun();
      if (EXIT_STATE == cur_state)
      {
         break;
      }

      cur_state = lookup_transitions(cur_state, rc);
   }

   return EXIT_SUCCESS;
}

enum state_codes lookup_transitions(enum state_codes codes, enum ret_codes codes1)
{
   return bar;
}
