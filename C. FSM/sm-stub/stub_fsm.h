#ifndef SM_STUB_STUB_FSM_H
#define SM_STUB_STUB_FSM_H

#define TRANSITION_COUNT 8

/**
 * @brief Return value (from state)
 */
typedef enum state_return_code
{
   ok,
   fail,
   repeat
} StateReturnCodeT;

/**
 * @brief State code
 */
typedef enum state
{
   entry,
   foo,
   bar,
   end,
   invalid
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
typedef StateReturnCodeT(*StateFuncT)(void);

/**
 * @brief Entry state action
 * @return Return code
 */
StateReturnCodeT entry_state(void);

/**
 * @brief Foo state action
 * @return Return code
 */
StateReturnCodeT foo_state(void);

/**
 * @brief Bar state action
 * @return Return code
 */
StateReturnCodeT bar_state(void);

/**
 * @brief Exit state action
 * @return Return code
 */
StateReturnCodeT exit_state(void);

/**
 * @brief Invalid state action
 * @return Return code
 */
StateReturnCodeT invalid_state(void);

/**
 * @brief Find the destination state
 * @param source_state Source state
 * @param return_code State status
 * @return Destination state or invalid state
 */
StateT lookup_transitions(StateT source_state, StateReturnCodeT return_code);

#endif //SM_STUB_STUB_FSM_H
