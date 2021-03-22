/**
 * State machine using an array of structure
 */

#include <stdio.h>
#include <stdbool.h>
#include "atm_struct_sm.h"

static volatile bool bo_keep_doing = true;

extern s_state_machine as_state_machine[];

e_system_event read_event(void);

int main()
{
   e_system_state e_next_state = idle_state;

   while (bo_keep_doing)
   {
      // Api read the event
      const e_system_event e_new_event = read_event();

      if (e_next_state < last_state && e_new_event < last_event
         && as_state_machine[e_next_state].e_state_machine_event == e_new_event
         && as_state_machine[e_next_state].pf_state_machine_event_handler != NULL)
      {
         // function call as per the state and event and return the next state of the finite state machine
         e_next_state = (*as_state_machine[e_next_state].pf_state_machine_event_handler)();
      }
      else
      {
         // Invalid
      }
   }

   return 0;
}

e_system_event read_event(void)
{
   return last_event;
}
