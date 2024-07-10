#include "atm_sm_lookup.h"

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
