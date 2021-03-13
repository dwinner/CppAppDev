#ifndef SM_STUB_STUB_FSM_H
#define SM_STUB_STUB_FSM_H

/**
 * @brief Return value (from state)
 */
typedef enum state_return_code
{
   ok,
   fail,
   repeat
} state_return_code_t;

/**
 * @brief State code
 */
typedef enum state
{
   entry,
   foo,
   bar,
   end
} state_t;// TODO: there must be also invalid state

/**
 * @brief Transition
 */
typedef struct
{
   state_t src_state;
   state_return_code_t ret_code;
   state_t dst_state;
} transition_t;

/**
 * Entry state action
 * @return Return code
 */
state_return_code_t entry_state(void);

/**
 * Foo state action
 * @return Return code
 */
state_return_code_t foo_state(void);

/**
 * Bar state action
 * @return Return code
 */
state_return_code_t bar_state(void);

/**
 * Exit state action
 * @return Return code
 */
state_return_code_t exit_state(void);

/**
 * @brief Find the destination state
 * @param source_state Source state
 * @param return_code State status
 * @return Destination state or invalid state
 */
state_t lookup_transitions(state_t source_state, state_return_code_t return_code);

#endif //SM_STUB_STUB_FSM_H
