/* Own headerfiles */
#include "sbw_ci.h"                    /* Import interface and local cfg. */
#include "SBW__AcousticPlayer.h"

/** Returns ID of acoustic which is already registered **/
static uint32 SBW__u32GetRegisteredWarning(void);
/** Handles requests to WIM **/
static bool SBW__boSoundOutputControl(uint32 u32NewWarningId, bool enPlay, bool boRear);
/** EEPROM Configuration **/
static byte SBW__bEeprom_SeatBeltConfig;

extern SBW__tstNcapWarn SBW__stNcapWarn;
extern SBW__tstWarnRequest SBW__stWarnRequest;
extern SBW__tstNcapWarnRear SBW__stNcapWarnRear;
extern SBW__tstWarnRequest SBW__stWarnRequestRear;

/** Current acoustic state **/
static struct
{
    /** Current warning phase of the front seatbelt warning **/
    tenWarnPhaseBuzzer enFront;
    /** Current warning phase of the rear seatbelt warning **/
    tenWarnPhaseBuzzer enRear;
} SBW__stAcousticRequests;

enum AcousticSource {
    enFront,
    enRear,
    enNone
};

static enum AcousticSource enSBWCurrentSource = enNone;
static tenWarnPhaseBuzzer enSBWCurrentAcousticPhase = nNoBuzzerWarning;

/** Initialize initial states of the player **/
void SBW__vInitializePlayer(byte bEeprom_SeatBeltConfig)
{
    SBW__stAcousticRequests.enFront = nNoBuzzerWarning;
    SBW__stAcousticRequests.enRear = nNoBuzzerWarning;
    SBW__bEeprom_SeatBeltConfig = bEeprom_SeatBeltConfig;
}

/*check if front sound is inactive*/
static bool SBW__boFrontSoundInactive(void)
{
    return (False == SBW__boEeprom_SeatBeltBuz && SBW__nNoSoundFront == SBW__u8Eeprom_SeatBeltBuzInactive);
}

/*check if rear sound is inactive*/
static bool SBW__boRearSoundInactive(void)
{
    return (False == SBW__boEeprom_SeatBeltBuz && SBW__nNoSoundRear == SBW__u8Eeprom_SeatBeltBuzInactive);
}

/** Decide which acoustics should be played **/
static enum AcousticSource SBW__enPriorizeAcoustics(tenWarnPhaseBuzzer enFrontPhase, tenWarnPhaseBuzzer enRearPhase)
{
    switch (enSBWCurrentAcousticPhase)
    {
    case nBuzzerNcapPhase3:
        if (((nBuzzerNcapPhase3 == enRearPhase) && (enSBWCurrentSource == enFront)) || (nBuzzerNcapPhase4 == enFrontPhase))
        {
            if (True == SBW__boFrontSoundInactive())
            {
                enSBWCurrentSource = enRear;
            }
            else
            {
                enSBWCurrentSource = enFront;
            }
        }
        else if (((nBuzzerNcapPhase3 == enFrontPhase) && (enSBWCurrentSource == enRear)) || (nBuzzerNcapPhase4 == enRearPhase))
        {
            if (True == SBW__boRearSoundInactive())
            {
                enSBWCurrentSource = enFront;
            }
            else
            {
                enSBWCurrentSource = enRear;
            }
        }
        break;
    case nBuzzerNcapPhase4:
        if (((nBuzzerNcapPhase4 == enRearPhase) && (enSBWCurrentSource == enFront)) || (nBuzzerNcapPhase3 == enRearPhase))
        {
            if (True == SBW__boFrontSoundInactive())
            {
                enSBWCurrentSource = enRear;
            }
            else
            {
                enSBWCurrentSource = enFront;
            }
            
        }
        else if (((nBuzzerNcapPhase4 == enFrontPhase) && (enSBWCurrentSource == enRear)) || (nBuzzerNcapPhase3 == enFrontPhase))
        {
            if (True == SBW__boRearSoundInactive())
            {
                enSBWCurrentSource = enFront;
            }
            else
            {
                enSBWCurrentSource = enRear;
            }
        }
        break;
    default:
        if (enFrontPhase == nNoBuzzerWarning)
        {
            if (True == SBW__boRearSoundInactive())
            {
                enSBWCurrentSource = enFront;
            }
            else
            {
                enSBWCurrentSource = enRear;
            }
        }
        else
        {
            if (True == SBW__boFrontSoundInactive())
            {
                enSBWCurrentSource = enRear;
            }
            else
            {
                enSBWCurrentSource = enFront;
            }

        }
        break;
    }
    return enSBWCurrentSource;
}

/** Synchronizes acoustic counters of the rear or front SBW **/
void SBW__vSyncFrontRearAcoustic(bool boRear)
{
    if (enSBWCurrentAcousticPhase != nNoBuzzerWarning)
    {
        if (boRear == False)
        {
            // called from front
            if (enSBWCurrentSource == enRear)
            {
                SBW__stNcapWarn.wCounterPhase = SBW__stNcapWarnRear.wCounterPhaseRear;
                SBW__stNcapWarn.wCounterPreStartTime = SBW__stNcapWarnRear.wCounterPreStartTimeRear;
                SBW__stNcapWarn.wCounterStartTime = SBW__stNcapWarnRear.wCounterStartTimeRear;
                SBW__stNcapWarn.wCounterWarnTime = SBW__stNcapWarnRear.wCounterWarnTimeRear;
                SBW__stWarnRequest.enNewWarnRequestBuzzer = enSBWCurrentAcousticPhase;
                SBW__stWarnRequest.boDisableBuzzer = SBW__stWarnRequestRear.boDisableBuzzer;
            }
        }
        else
        {
            // called from rear
            if (enSBWCurrentSource == enFront)
            {
                SBW__stNcapWarnRear.wCounterPhaseRear = SBW__stNcapWarn.wCounterPhase;
                SBW__stNcapWarnRear.wCounterPreStartTimeRear = SBW__stNcapWarn.wCounterPreStartTime;
                SBW__stNcapWarnRear.wCounterStartTimeRear = SBW__stNcapWarn.wCounterStartTime;
                SBW__stNcapWarnRear.wCounterWarnTimeRear = SBW__stNcapWarn.wCounterWarnTime;
                SBW__stWarnRequestRear.enNewWarnRequestBuzzer = enSBWCurrentAcousticPhase;
                SBW__stWarnRequestRear.boDisableBuzzer = SBW__stWarnRequest.boDisableBuzzer;
            }
        }
    }
}

/** Sets current phase of the rear or front SBW acoustics **/
void SBW__vSetPhase(tenWarnPhaseBuzzer enPhase, bool boRear)
{
    if (boRear == True)
    {
        SBW__stAcousticRequests.enRear = enPhase;
    }
    else
    {
        SBW__stAcousticRequests.enFront = enPhase;
    }
}

/** Returns current phase of the rear or front SBW acoustics **/
tenWarnPhaseBuzzer SBW__enGetPhase(bool boRear)
{
    return boRear ? SBW__stAcousticRequests.enRear : SBW__stAcousticRequests.enFront;
}

/** Handles sound output of the rear or front SBW acoustics **/
void SBW__vProcessAcoustics(bool enPlay, bool boRear)
{
    enum AcousticSource enSource = SBW__enPriorizeAcoustics(SBW__stAcousticRequests.enFront, SBW__stAcousticRequests.enRear);
    if ((boRear == True) == (enSource == enRear))
    {
        tenWarnPhaseBuzzer enWarnPhaseBuzzer = enSource == enRear ? SBW__stAcousticRequests.enRear : SBW__stAcousticRequests.enFront;
        SBW__boSoundOutputControl(SBW__stBuzzer[enWarnPhaseBuzzer].enLogDevice, enPlay, enSource == enRear);
        enSBWCurrentAcousticPhase = enWarnPhaseBuzzer;
    }
}

/** Returns ID of acoustic which is already registered **/
static uint32 SBW__u32GetRegisteredWarning(void)
{
    /***************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local variables (auto and static)
    ****************************************************************************/
    uint32 u32RegisteredWarning = 0;
    uint8 i = 0;
    /***************************************************************************
    * FUNCTION CODE
    ****************************************************************************/
    for (i = 0; i < nNoBuzzerWarning; i++)
    {
        if (WIM_boIsRegistered(SBW__stBuzzer[i].enLogDevice))
        {
            u32RegisteredWarning = SBW__stBuzzer[i].enLogDevice;
        }
        else
        {
            /* Acoustic warning is not registered */
        }
    }
    return u32RegisteredWarning;
}

/** Handles requests to WIM **/
static bool SBW__boSoundOutputControl(uint32 u32NewWarningId, bool enPlay, bool boRear)
{
    /***************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local variables (auto and static)
    ****************************************************************************/
    bool boBuzInactive = boRear ? (SBW__nNoSoundFront == SBW__u8Eeprom_SeatBeltBuzInactive) : (SBW__nNoSoundRear == SBW__u8Eeprom_SeatBeltBuzInactive);
    bool boResult = False;
    uint32 u32RegisteredWarning = SBW__u32GetRegisteredWarning(); /* Check if warning is registered */
    /* EasyCASE - */
    /***************************************************************************
    * FUNCTION CODE
    ****************************************************************************/
    if (/* Already registered warning */
        (u32RegisteredWarning == u32NewWarningId) &&
        /* Valid warning requested */
        (u32NewWarningId != 0))
    {
        /* Sound warning has been already registered */
        if ((True == enPlay)
            &&
            ((SBW__nEeprom_SeatBeltNcapEce == SBW__bEeprom_SeatBeltConfig) || (SBW__nEeprom_SeatBeltNcapAdvanced == SBW__bEeprom_SeatBeltConfig))
            &&
            ((True == SBW__boEeprom_SeatBeltBuz) || boBuzInactive))
        {
            /* Sound retrigger only for ECE or NCAP USA when acoustics are not disabled from EEPROM for front seats */
            WIM_vRetriggerSound(u32RegisteredWarning);
        }
        else
        {
            /* Sound stop */
            WIM_vStopSound(u32RegisteredWarning);
        }
        boResult = True;
    }
    else
    {
        /* New sound warning request */
        if (/* A previously registered warning */
            0 != u32RegisteredWarning)
        {
            WIM_vRelIntEvent(u32RegisteredWarning); /* Release the old warning first */
        }
        else
        {
            /* Nothing to do, no warning has been registered */
        }

        if ((True == enPlay)
            &&
            ((SBW__nEeprom_SeatBeltNcapEce == SBW__bEeprom_SeatBeltConfig) || (SBW__nEeprom_SeatBeltNcapAdvanced == SBW__bEeprom_SeatBeltConfig))
            &&
            ((True == SBW__boEeprom_SeatBeltBuz) || boBuzInactive))
        {
            /* Sound warning registering only for ECE or NCAP USA when acoustics are not disabled from EEPROM for front seats*/
            WIM_vSetIntEvent(u32NewWarningId);
            boResult = True;
        }
        else
        {
            /* Can not stop a not registered sound warning */
        }
    }
    return boResult;
}