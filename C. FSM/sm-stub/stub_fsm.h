#ifndef SM_STUB_STUB_FSM_H
#define SM_STUB_STUB_FSM_H

#define TRANSITION_COUNT 11

/**
 * @brief Return value (from state)
 */
typedef enum state_return_code
{
   ok_code,
   fail_code,
   repeat_code,
   invalid_code
} StateReturnCodeT;

/**
 * @brief State code
 */
typedef enum state
{
   entry_state,
   foo_state,
   bar_state,
   end_state,
   invalid_state
} StateT;

/**
 * @brief Transition
 */
typedef struct
{
   StateT src_state;
   StateReturnCodeT ret_code;
   StateT dst_state;
} TransitionT;

/**
 * @brief State function pointer
 */
typedef StateReturnCodeT (*StateFuncT)(void);

/**
 * @brief Entry state action
 * @return Return code
 */
StateReturnCodeT entry_state_action(void);

/**
 * @brief Foo state action
 * @return Return code
 */
StateReturnCodeT foo_state_action(void);

/**
 * @brief Bar state action
 * @return Return code
 */
StateReturnCodeT bar_state_action(void);

/**
 * @brief Exit state action
 * @return Return code
 */
StateReturnCodeT exit_state_action(void);

/**
 * @brief Invalid state action
 * @return Return code
 */
StateReturnCodeT invalid_state_action(void);

/**
 * @brief Find the destination state
 * @param source_state Source state
 * @param return_code State status
 * @return Destination state or invalid_state state
 */
StateT lookup_transitions(StateT source_state, StateReturnCodeT return_code);

extern StateFuncT state_functions[];

#endif //SM_STUB_STUB_FSM_H
