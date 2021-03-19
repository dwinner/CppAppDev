#ifndef ATM_LOOKUP_TABLE_2D_ARRAY_ATM_SM_LOOKUP_H
#define ATM_LOOKUP_TABLE_2D_ARRAY_ATM_SM_LOOKUP_H

/**
 * Different state of ATM machine
 */
typedef enum
{
   idle_state,
   card_inserted_state,
   pin_entered_state,
   option_selected_state,
   amount_entered_state,
   last_state
} e_system_state;

/**
 * Different type events
 */
typedef enum
{
   card_insert_event,
   pin_enter_event,
   option_selection_event,
   amount_enter_event,
   amount_dispatch_event,
   last_event
} e_system_event;

/**
 * typedef of 2d array
 */
typedef e_system_state (*const af_event_handler[last_state][last_event])(void);

/**
 * typedef of function pointer
 */
typedef e_system_state (*pf_event_handler)(void);

/**
 * function call to dispatch the amount and return the ideal state
 * @return state
 */
e_system_state amount_dispatch_handler(void);

/**
 * function call to Enter amount and return amount entered state
 * @return state
 */
e_system_state enter_amount_handler(void);

/**
 * function call to option select and return the option selected state
 * @return state
 */
e_system_state option_selection_handler(void);

/**
 * function call to enter the pin and return pin entered state
 * @return state
 */
e_system_state enter_pin_handler(void);

/**
 * function call to processing track data and return card inserted state
 * @return state
 */
e_system_state insert_card_handler(void);

#endif //ATM_LOOKUP_TABLE_2D_ARRAY_ATM_SM_LOOKUP_H
