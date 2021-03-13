#include "stub_fsm.h"

/**
 * @brief Array and enum below must be in sync!
 */
state_return_code_t (*p_state_func[])(void) =
{
   entry_state,
   foo_state,
   bar_state,
   exit_state
};

/**
 * @brief Transition table
 * @note transitions from end state aren't needed
 */
transition_t state_transitions[] =
{
   {entry, ok, foo},
   {entry, fail, end},
   {foo, ok, bar},
   {foo, fail, end},
   {foo, repeat, foo},
   {bar, ok, end},
   {bar, fail, end},
   {bar, repeat, foo}
};

state_return_code_t entry_state(void)
{
   return ok;
}

state_return_code_t foo_state(void)
{
   return ok;
}

state_return_code_t bar_state(void)
{
   return ok;
}

state_return_code_t exit_state(void)
{
   return ok;
}

state_t lookup_transitions(state_t source_state, state_return_code_t return_code)
{
   return bar;
}
