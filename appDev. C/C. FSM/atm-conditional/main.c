/**
 * ATM state machine: using the conditional statement
 */

#include <stdio.h>
#include <stdbool.h>
#include "atm_sm.h"

static volatile bool bo_keep_running = true;

e_system_event read_event(void);

int main()
{
   e_system_state e_next_state = idle_state;

   while (bo_keep_running)
   {
      // Reading system events
      const e_system_event e_new_event = read_event();

      switch (e_next_state)
      {
      case idle_state:
         if (e_new_event == card_inserted_event)
         {
            e_next_state = insert_card_handler();
         }
         break;

      case card_inserted_state:
         if (e_new_event == pin_enter_event)
         {
            e_next_state = enter_pin_handler();
         }
         break;

      case pin_entered_state:
         if (e_new_event == option_selection_event)
         {
            e_next_state = option_selection_handler();
         }
         break;

      case option_selected_state:
         if (e_new_event == amount_enter_event)
         {
            e_next_state = enter_amount_handler();
         }
         break;

      case amount_entered_state:
         if (e_new_event == amount_dispatch_event)
         {
            e_next_state = amount_dispatch_handler();
         }
         break;

      default:
         break;
      }
   }
}

e_system_event read_event(void)
{
   return card_inserted_event;
}
