//
// Created by den on 3/12/2021.
//

#ifndef ATM_CONDITIONAL_ATM_SM_H
#define ATM_CONDITIONAL_ATM_SM_H

/**
 * Different state of ATM machine
 */
typedef enum
{
   idle_state,
   card_inserted_state,
   pin_entered_state,
   option_selected_state,
   amount_entered_state
} e_system_state;

/**
 * Different type events
 */
typedef enum
{
   card_inserted_event,
   pin_enter_event,
   option_selection_event,
   amount_enter_event,
   amount_dispatch_event
} e_system_event;

// Prototype of event handlers

e_system_state amount_dispatch_handler(void);

e_system_state enter_amount_handler(void);

e_system_state option_selection_handler(void);

e_system_state enter_pin_handler(void);

e_system_state insert_card_handler(void);

#endif //ATM_CONDITIONAL_ATM_SM_H
