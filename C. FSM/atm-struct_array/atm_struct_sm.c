#include "atm_struct_sm.h"

e_system_state amount_dispatch_handler(void)
{
   return idle_state;
}

e_system_state enter_amount_handler(void)
{
   return amount_entered_state;
}

e_system_state option_selection_handler(void)
{
   return option_selected_state;
}

e_system_state enter_pin_handler(void)
{
   return pin_entered_state;
}

e_system_state insert_card_handler(void)
{
   return card_inserted_state;
}

/**
 * Initialize array of structure with states and event with proper handler
 */
s_state_machine as_state_machine[] =
{
   {idle_state, card_insert_event, insert_card_handler},
   {card_inserted_state, pin_enter_event, enter_pin_handler},
   {pin_entered_state, option_selection_event, option_selection_handler},
   {option_selected_state, amount_enter_event, enter_amount_handler},
   {amount_entered_state, amount_dispatch_event, amount_dispatch_handler}
};
