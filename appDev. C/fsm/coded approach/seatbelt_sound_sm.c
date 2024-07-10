#include "seatbelt_sound_sm.h"
#include "stdbool.h"

/**
 * @brief Transition table
 */
sbw_transition_t sbw_state_transitions[] =
{
   /* lamp off transitions */
   {lamp_off, seq_active, static_on},
   {lamp_off, seq_active, blinking_wait},
   /* static on wait transitions */   
};

/* --- Guard conditions --- */

static bool is_blinking(void)
{   
   return true;
}

static bool is_beep(void)
{
   return true;
}

sbw_sound_state_t lamp_off_state(void)
{
   if (is_blinking())
   {
      return blinking_wait;
   }
   else
   {
      return static_on_wait;
   }
}

sbw_sound_state_t static_on_wait_state(void)
{
   if (is_beep())
   {
      return static_on;
   }
   else
   {
      return lamp_off;
   }
}

sbw_sound_state_t static_on_state(void)
{
   return static_on;
}

sbw_sound_state_t blinking_wait_state(void)
{
   return static_on;
}

sbw_sound_state_t blinking_state(void)
{
   return static_on;
}
