#ifndef ATM_STRUCT_ARRAY_ATM_STRUCT_SM_H
#define ATM_STRUCT_ARRAY_ATM_STRUCT_SM_H

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
 * typedef of function pointer
 */
typedef e_system_state (*pf_event_handler)(void);

/**
 * structure of state and event with event handler
 */
typedef struct
{
   e_system_state e_state_machine;
   e_system_event e_state_machine_event;
   pf_event_handler pf_state_machine_event_handler;
} s_state_machine;

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

#endif //ATM_STRUCT_ARRAY_ATM_STRUCT_SM_H
