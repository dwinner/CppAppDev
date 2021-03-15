#include "stub_fsm.h"

/**
 * @brief Array and enum below must be in sync!
 */
StateFuncT state_functions[] =
{
   entry_state,
   foo_state,
   bar_state,
   exit_state,
   invalid_state
};

/**
 * @brief Transition table
 * @details transitions from end state aren't needed
 */
TransitionT state_transitions[TRANSITION_COUNT] =
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

StateReturnCodeT entry_state(void)
{
   return ok;
}

StateReturnCodeT foo_state(void)
{
   return ok;
}

StateReturnCodeT bar_state(void)
{
   return ok;
}

StateReturnCodeT exit_state(void)
{
   return ok;
}

StateReturnCodeT invalid_state()
{
   return fail;
}

StateT lookup_transitions(const StateT source_state, const StateReturnCodeT return_code)
{
   StateT dst_state = invalid;

   for (int i = 0; i < TRANSITION_COUNT; ++i)
   {
      const StateT src_state = state_transitions[i].src_state;
      const StateReturnCodeT ret_code = state_transitions[i].ret_code;
      if (source_state == src_state && return_code == ret_code)
      {
         dst_state = state_transitions[i].dst_state;
         break;
      }
   }

   return dst_state;
}
