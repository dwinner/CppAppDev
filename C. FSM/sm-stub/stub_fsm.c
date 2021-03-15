#include "stub_fsm.h"
#include "sm-utils.h"

/**
 * @brief Array and enum below must be in sync!
 */
StateFuncT state_functions[] =
{
    entry_state_action,
    foo_state_action,
    bar_state_action,
    exit_state_action,
    invalid_state_action
};

/**
 * @brief Transition table
 * @details transitions from end_state state aren't needed
 */
TransitionT state_transitions[TRANSITION_COUNT] =
{
   {entry_state, ok_code,      foo_state},
   {entry_state, fail_code,    end_state},
   {entry_state, invalid_code, entry_state},
   {foo_state,   ok_code,      bar_state},
   {foo_state,   fail_code,    end_state},
   {foo_state,   repeat_code,  foo_state},
   {foo_state,   invalid_code, foo_state},
   {bar_state,   ok_code,      end_state},
   {bar_state,   fail_code,    end_state},
   {bar_state,   repeat_code,  foo_state},
   {bar_state,   invalid_code, bar_state}
};

StateReturnCodeT entry_state_action(void)
{
   const StateReturnCodeT return_code = (StateReturnCodeT)rand_lim((int)invalid_code);
   return return_code;
}

StateReturnCodeT foo_state_action(void)
{
   const StateReturnCodeT return_code = (StateReturnCodeT)rand_lim((int)invalid_code);
   return return_code;
}

StateReturnCodeT bar_state_action(void)
{
   const StateReturnCodeT return_code = (StateReturnCodeT)rand_lim((int)invalid_code);
   return return_code;
}

StateReturnCodeT exit_state_action(void)
{
   const StateReturnCodeT return_code = (StateReturnCodeT)rand_lim((int)invalid_code);
   return return_code;
}

StateReturnCodeT invalid_state_action()
{
   const StateReturnCodeT return_code = (StateReturnCodeT)rand_lim((int)invalid_code);
   return return_code;
}

StateT lookup_transitions(const StateT source_state, const StateReturnCodeT return_code)
{
   StateT dst_state = invalid_state;

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
