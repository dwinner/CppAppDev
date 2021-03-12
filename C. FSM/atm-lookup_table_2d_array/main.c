/**
 * Using the lookup table
 * A state machine in c using a 2D array
 */

#include <stdio.h>
#include <stdbool.h>
#include "atm_sm_lookup.h"

static volatile bool bo_continue = true;

e_system_event read_event(void);

int main()
{
   e_system_state e_next_state = idle_state;

   // Table to define valid states and event of finite state machine
   static af_event_handler state_machine =
   {
      [idle_state] = {[card_insert_event] = insert_card_handler},
      [card_inserted_state] = {[pin_enter_event] = enter_pin_handler},
      [pin_entered_state] = {[option_selection_event] = option_selection_handler},
      [option_selected_state] = {[amount_enter_event] = enter_amount_handler},
      [amount_entered_state] = {[amount_dispatch_event] = amount_dispatch_handler},
   };

   while (bo_continue)
   {
      // assume api to read the next event
      const e_system_event e_new_event = read_event();

      // Check NULL pointer and array boundary
      if (e_next_state < last_state && e_new_event < last_event && state_machine[e_next_state][e_new_event] != NULL)
      {
         // function call as per the state and event and return the next state of the finite state machine
         e_next_state = (*state_machine[e_next_state][e_new_event])();
      }
      else
      {
         //Invalid
      }
   }

   return 0;
}

e_system_event read_event(void)
{
   return last_event;
}
