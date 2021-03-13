#include "stub_fsm.h"

/**
 * @brief Array and enum below must be in sync!
 * @return status code
 */
int (*state[])(void) =
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
struct transition state_transitions[] =
    {
        {entry, ok,     foo},
        {entry, fail,   end},
        {foo,   ok,     bar},
        {foo,   fail,   end},
        {foo,   repeat, foo},
        {bar,   ok,     end},
        {bar,   fail,   end},
        {bar,   repeat, foo}
    };

int entry_state(void)
{
   return 0;
}

int foo_state(void)
{
   return 0;
}

int bar_state(void)
{
   return 0;
}

int exit_state(void)
{
   return 0;
}
