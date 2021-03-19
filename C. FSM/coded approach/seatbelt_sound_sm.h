#ifndef CODED_APPROACH_SEATBELT_SOUND_SM_H
#define CODED_APPROACH_SEATBELT_SOUND_SM_H

typedef enum
{
   lamp_off,
   static_on_wait,
   static_on,
   blinking_wait,
   blinking
} sbw_sound_state_t;

typedef enum
{
   seq_active,   
   seq_not_active,
   on_beep,
} sbw_sound_return_status_t;

sbw_sound_state_t lamp_off_state(void);

sbw_sound_state_t static_on_wait_state(void);

sbw_sound_state_t static_on_state(void);

sbw_sound_state_t blinking_wait_state(void);

sbw_sound_state_t blinking_state(void);

sbw_sound_state_t(*sbw_sound_st[])(void) =
{
   lamp_off_state,
   static_on_wait_state,
   static_on_state,
   blinking_wait_state,
   blinking_state
};

typedef struct
{
   sbw_sound_state_t source_state;

   sbw_sound_return_status_t return_status_return_code;

   sbw_sound_state_t destination_state;
} sbw_transition_t;

#endif //CODED_APPROACH_SEATBELT_SOUND_SM_H
