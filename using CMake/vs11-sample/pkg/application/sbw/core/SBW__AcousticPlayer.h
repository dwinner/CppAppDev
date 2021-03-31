#ifndef __SBW_ACOUSTICPLAYER_H
#define __SBW_ACOUSTICPLAYER_H

/***************************************************************************
* HEADER-FILES (Only those that are needed in this file)
****************************************************************************/
/* System-headerfiles */
#include  <cdef.h>                      /* General definitions and types   */

typedef enum {
    nBuzzerNormal,
    nBuzzerNcapPhase1,
    nBuzzerNcapPhase2,
    nBuzzerNcapPhase3,
    nBuzzerNcapPhase4,
    nBuzzerNcapLastPhase = nBuzzerNcapPhase4,
    nNoBuzzerWarning
} tenWarnPhaseBuzzer;

/** Initialize initial states of the player **/
void SBW__vInitializePlayer(byte bEeprom_SeatBeltConfig);
/** Sets current phase of the rear or front SBW acoustics **/
void SBW__vSetPhase(tenWarnPhaseBuzzer enPhase, bool boRear);
/** Returns current phase of the rear or front SBW acoustics **/
tenWarnPhaseBuzzer SBW__enGetPhase(bool boRear);
/** Handles sound output of the rear or front SBW acoustics**/
void SBW__vProcessAcoustics(bool, bool);
/** Synchronizes acoustic counters of the rear or front SBW **/
void SBW__vSyncFrontRearAcoustic(bool);

#endif
