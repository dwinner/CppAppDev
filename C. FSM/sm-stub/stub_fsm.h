#ifndef SM_STUB_STUB_FSM_H
#define SM_STUB_STUB_FSM_H

/**
 * Entry state action
 * @return Return code
 */
int entry_state(void);

/**
 * Foo state action
 * @return Return code
 */
int foo_state(void);

/**
 * Bar state action
 * @return Return code
 */
int bar_state(void);

/**
 * Exit state action
 * @return Return code
 */
int exit_state(void);

/**
 * @brief State code
 */
enum state_codes
{
   entry,
   foo,
   bar,
   end
};

/**
 * @brief Return value
 */
enum ret_codes
{
   ok,
   fail,
   repeat
};

/**
 * @brief Transition
 */
struct transition
{
   enum state_codes src_state;
   enum ret_codes ret_code;
   enum state_codes dst_state;
};

#endif //SM_STUB_STUB_FSM_H
