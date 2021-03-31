/* EasyCASE V6.5 02/25/2014 12:22:04 */
/* EasyCASE O
If=vertical
LevelNumbers=no
LineNumbers=yes
Colors=16777215,0,12582912,12632256,0,0,0,16711680,8388736,0,33023,32768,0,0,0,0,0,32768,12632256,255,65280,255,255,16711935
ScreenFont=Courier New,Standard,100,4,-14,0,400,0,0,0,0,0,0,3,2,1,49,96,96
PrinterFont=Courier New,,80,4,-66,0,400,0,0,0,0,0,0,3,2,1,49,600,600
LastLevelId=139 */
/* EasyCASE ( 1
   sbwwci.h */
/* EasyCASE ( 2
   FILE HEADER */
/***************************************************************************
*================= Copyright by SiemensVDO Automotive AG ===================
****************************************************************************
* Titel        : SBW - Seatbelt Warnung
*
* Description  : Die Aufgabe des SBW-Moduls ist eine baureihen�bergreifende
*                Warnerfassung und Anmeldung der Gurtwarnung. Von SBW werden
*                nur die Gurtwarnung Akustik und die Gurtwarnung Lampe nach
*                Euro-NCAP bedient.
*
* Environment  : FJ-16 und FJ-32
*
* Responsible  : Joachim Pieper, Siemens VDO Automotive AG
*
* Guidelines   : SMK
*
* Template name: SWMODxCI.H, Revision 1.0
*
* CASE-Tool    : EasyCASE(C++), Version 6.32
*
* $Revision: 1.2 $
*
* Revision List: (Will be filled by PVCS)
* Archive: $Log: sbw1ci.h  $
* Archive: Revision 1.2 2014/03/25 11:33:32CET Olenici-EXT, Alexandru (uidw5408)
* Archive: Updated after MR39407.
* Archive: Revision 1.1 2012/11/16 15:13:42CET Lacko-EXT, Jan (uidu0305)
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/sbw/adapt/project.pj
* Archive: Revision 1.2 2012/11/16 15:13:41CET Lacko Jan (uidu0305) (uidu0305)
* Archive: Update header of file.
*
*    Rev 1.6   Jul 22 2011 14:53:14   Jan.Cavojsky-EXT
* Update after MRs 22334
*
*    Rev 1.5   Apr 14 2011 18:15:12   Nicolae.Gavrila
* DC MRs:
* 21685: BR222 SBW: counting 30sec only when Warning in display -LP2440
* 21684: BR222 SBW: new Condition instead of car_running -LP2439
*
*    Rev 1.4   Mar 04 2011 16:09:54   Nicolae.Gavrila
* DC MR 21513: BR222 AC: Seatbeltwarning front Phase 3
*
*    Rev 1.3   Dec 03 2010 15:07:32   Nicolae.Gavrila
* DC MR 21384: BR222: two warnings for seatbeltwarning
*
*    Rev 1.2   Nov 19 2010 10:32:10   Nicolae.Gavrila
* DC MR 21117: Correction SBW
*
*    Rev 1.1   Sep 02 2010 14:27:12   Nicolae.Gavrila
* Update for CAN Signals name change
*
*    Rev 1.0   Aug 27 2010 16:38:28   Nicolae.Gavrila
* Initial revision.
*
*    Rev 1.5   May 15 2009 09:39:22   Nicolae.Gavrila
* DC MR 19791: -LP2149: Change of speed Limit for Acoustic Rearseatbelt warning
*
*    Rev 1.4   Dec 09 2008 17:30:00   Nicolae.Gavrila
* DC MR 19344: rear seatbelt warning follow up MR
*
*    Rev 1.3   Oct 10 2008 17:43:10   Nicolae.Gavrila
* DC MR 18453 Change of display layout
*
*    Rev 1.2   Aug 22 2008 09:46:34   Radu.Teaha
* DC MR 18905
*
*    Rev 1.1   Jun 20 2008 09:55:44   Radu.Teaha
* DP MR: 18185
*
*    Rev 1.0   Mar 04 2008 14:13:40   Gaertner
* Initial revision.
*
*    Rev 1.3   Jan 16 2008 08:56:38   Nicusor.Bordinc
* DC MR 17428 Update of NCAP warning
*
*    Rev 1.2   Feb 09 2007 16:10:56   Radu.Teaha
* DC MR 15537
*
*    Rev 1.1   Apr 27 2006 12:52:06   Radu.Teaha
* MR 14145
*
*    Rev 1.0   Jan 16 2006 10:33:58   Toth.Zoltan
* Initial revision. Copied from revision 1.4 of file "Sbwmci.h".
*
*
****************************************************************************/

/*
* Check if information are already included
*/
#ifndef SBW_CI_H
#define SBW_CI_H


/***************************************************************************
* HEADER-FILES (Only those that are needed in this file)
****************************************************************************/
/* System-headerfiles */
#include  <cdef.h>                      /* General definitions and types   */

/* Own headerfiles */
#include "SBW__AcousticPlayer.h"

/* Foreign headerfiles */
#include  "eed_c1.h"                    /* Eeprom configuration            */
#include  "VEL_C1.H"                    /* Velocity module                 */
#include  "WIM_c1.h"                    /* Warnings manager                */
#include  "STAT_Api.h"                  /* Status module                    */

/* EasyCASE ) */
/* EasyCASE ( 120
   IMPORT CONFIGURATION */
/***************************************************************************
* SYNONYM ADAPTATION
*
* In this section
* - adapt external symbols to internally used names if necessary. This
*   synonym adaptation is unknown for other modules
****************************************************************************/
#define SBW__nFreqStatic                    SFG_nFreq8StaticHi
/* EasyCASE ( 121
   CODAS: configuration data */
/* Sitzgurtwarnung Master-Konfiguration */
#define SBW__bEeprom_SeatBelt               EEH_biGetStaticSeatBelt()

#define SBW__nEeprom_SeatBeltConfigBits     (0)
#define SBW__nEeprom_SeatBeltNcapEce        (1)
#define SBW__nEeprom_SeatBeltNcapAdvanced   (2)
#define SBW__nEeprom_SeatBeltReserve        (3)

#define SBW__nStaticSeatBeltOff             (0x03)

/* Sitzgurtwarnune Akustik */
#define SBW__boEeprom_SeatBeltBuz           EEH_boGetStaticSeatbeltAcoustics()
#define SBW__u8Eeprom_SeatBeltBuzInactive   EEH_biGetStaticBeltWarningSoundInactive()
#define SBW__nNoSoundFront                  (0x00)
#define SBW__nNoSoundRear                   (0x01)

/* Rear seatbelt warnings configuration bit */
#define SBW__boEeprom_RearSeatbeltWrn()     EEH_boGetStaticSeatBeltFond()

/* Rear seatbelt warnings mat configuration bit */
#define SBW__boEeprom_RearSeatMat()             EEH_boGetRear_Seat_Mat()
#define SBW__nRearSeatMatDisabled               (0x00)

#define SBW__nShiftToSeatMatsRow2LeftBitPos     (2)
#define SBW__nShiftToSeatMatsRow2MiddleBitPos   (4)
#define SBW__nShiftToSeatMatsRow2RightBitPos    (6)
#define SBW__nShiftToSeatMatsRow3LeftBitPos     (8)
#define SBW__nShiftToSeatMatsRow3RightBitPos    (10)
#define SBW__nNumberof3SeatMats                 (1)
#define SBW__nNumberof5SeatMats                 (2)

/* Rear seatbelt warnings Slacks configuration bit */
#define SBW__boEeprom_RearSeatSlacks()     EEH_boGetBelt_Warning_Back_SLACKs()
#define SBW__nSlackDisabled                (0x00)
#define SBW__nSlackEnabled                 (0x01)


/* Vehicle Line configuration bit */
#define SBW__u8Eeprom_VehLine()             EEH_biGetStaticVehLine()
#define SBW__nVehLineBR447                  (38)
#define SBW__nVehLineBR464                  (37) 

/* define for High Line project type */
#if (HMI_MODEL == MODEL_COLOR)
#define SBW__HL
#else
#define SBW__LL
#endif

/* Left hand drive */
#define SBW__u8GetStaticLeftHandDrive()     EEH_biGetStaticLeftHandDrive()
#define SBW__nLeftHandDriving               (1)
#define SBW__nRightHandDriving              (2)
/* EasyCASE ) */
/* EasyCASE ( 122
   VEL: velocity macros */
#define SBW__vGetVelocity                   VEL_vGetVelocity
/* EasyCASE - */
#define SBW_nUnitKm                         VEL_nUnitKm

#define SBW__u8Eeprom_RearSeatLayout        EEH_biGetStaticRearSeatLayout()
#define SBW__nNoWarn                        (0xFF)
#define SBW__nRear2Seats                    (0x00)
#define SBW__nRear3Seats                    (0x01)
#define SBW__nRear4Seats                    (0x02)
#define SBW__nRear5Seats                    (0x03)

#define SBW__nRearSeatInvisibleMaskForHil       (uint32)(0x00)
#define SBW__nRearSeatNotFastenedMaskForHil     (uint32)(0x01)
#define SBW__nRearSeatFastenedMaskForHil        (uint32)(0x02)
#define SBW__nRearSeatNumberofRowsForHil        (uint32)(0x01)

#define SBW__nRearSeatFastened             (uint16)(0x01)
#define SBW__nRearSeatBlinking             (uint16)(0x02)

#define SBW__nRearSeatFastenedStat         (uint16)(0x01)
#define SBW__nRearSeatUnFastenedStat       (uint16)(0x02)
#define SBW__nRearSeatBlinkingStat         (uint16)(0x03)

#define SBW__nBodyStyleSedan                (0x00)
#define SBW__nBodyStyleWagon                (0x03)
#define SBW__nBodyStyleSportsUtilityTourer  (0x0D)

#define SBW__nShiftToByte1                  (8)

#define SBW__nNoSoundWarn                   (0x20042000)
#define SBW__nSoundWarnNCAP2018             (0x20066600)
#define SBW__nNoSoundBlinkingWarn           (0x20072B00)

/* EasyCASE ) */
/* EasyCASE ( 123
   WIM: warnings adaptations */
/* EasyCASE ) */
/* EasyCASE ( 139
   CST: system state */
/* Motor On check */
#define SBW__nMotorOn                       CST_boGetStatus(CST_nenLampTestSuppressed)
/* EasyCASE ) */
/* NCAP phase 4 ON subphase period */
#define SBW__NCAPPhase4OnSubphase           (5)
/* NCAP Phase4ON subphase period (in hundreds of ms) */
static const uint8 SBW__u8NcapPhase4OnSubphasePeriod = SBW__NCAPPhase4OnSubphase;
/* EEPROM coding for legal seatbelt warning timer */
#define SBW__wNormalSeatBeltWarnTimeMax     EEH_u8GetSeatbeltInitialWarningTime()
#define SBW__wNormalSeatBeltWarnTimeMaxsec  SBW__wNormalSeatBeltWarnTimeMax*10

/* EEPROM coding for counter delay between Normal Warning and NCAP-USA warning */
#define SBW__wNormalSeatBeltDelayTimeMax    EEH_u8GetSeatbeltWarningPause()
#define SBW__wNormalSeatBeltDelayTimeMaxsec SBW__wNormalSeatBeltDelayTimeMax*10

/* EEPROM label coding for Rear seat belt timer value for NCAP2018 */
#define SBW__nRsbwTimerNCAP2018             EEH_u8GetSeatbeltWarningDisplayTime()

/* Register DPOOL data receiving event */
#define SBW__vRegReceiveEvent()      EVHD_vRegister(EV_DPOOL_OnChange_STAT_u8SbwAnyIconBlinking_SBW__vEventHandler, True); \
                                     EVHD_vRegister(EV_TIM_SBW_IconBlinkTimer_SBW__vEventHandler, True);    

/* De-register DPOOL data receiving event */
#define SBW__vDeregReceiveEvent()    EVHD_vDeregister(EV_DPOOL_OnChange_STAT_u8SbwAnyIconBlinking_SBW__vEventHandler); \
                                     EVHD_vDeregister(EV_TIM_SBW_IconBlinkTimer_SBW__vEventHandler); 

/*
* Description: Event which is received if any rear seatbelt icon is blinking
*/
/* EasyCASE - */
#define SBW__Icon_Blink_Event        EV_DPOOL_OnChange_STAT_u8SbwAnyIconBlinking_SBW__vEventHandler

/*
* Description: Event which is received if the rear seatbelt icon blinking timer has expired
*/
/* EasyCASE - */
#define SBW__Icon_Blink_Timer        EV_TIM_SBW_IconBlinkTimer_SBW__vEventHandler

/* Number of a 250ms timer counts */
#define SBW__en250msTimerCounts      (2)

/* Sbw icon blink off request */
#define SBW__nSbwIconBlinkOff        STAT_nSbwIconBlinkOff

/* Sbw icon and lamp blink on request */
#define SBW__nSbwIconAndLampBlinkOn  STAT_nSbwIconAndLampBlinkOn

/* Register SBW debouce events */
#define SBW_vRegSBWdebouceEvent()       EVHD_vRegister(EV_TIM_SBW_DebounceTimer_RL_SBW__vEventHandler, False); \
                                        EVHD_vRegister(EV_TIM_SBW_DebounceTimer_RR_SBW__vEventHandler, False); \
                                        EVHD_vRegister(EV_TIM_SBW_DebounceTimer_RM_SBW__vEventHandler, False); \
                                        EVHD_vRegister(EV_TIM_SBW_DebounceTimer_3RL_SBW__vEventHandler, False); \
                                        EVHD_vRegister(EV_TIM_SBW_DebounceTimer_3RR_SBW__vEventHandler, False); 

/* Deregister SBW debouce events */
#define SBW_vDeRegSBWdebouceEvent()     EVHD_vDeregister(EV_TIM_SBW_DebounceTimer_RL_SBW__vEventHandler); \
                                        EVHD_vDeregister(EV_TIM_SBW_DebounceTimer_RR_SBW__vEventHandler); \
                                        EVHD_vDeregister(EV_TIM_SBW_DebounceTimer_RM_SBW__vEventHandler); \
                                        EVHD_vDeregister(EV_TIM_SBW_DebounceTimer_3RL_SBW__vEventHandler); \
                                        EVHD_vDeregister(EV_TIM_SBW_DebounceTimer_3RR_SBW__vEventHandler); 


/* debouce seatmat presence time */
#define SBW__nDebounceTime  			(15) 														


/* EasyCASE ) */
/* EasyCASE ( 124
   MODULE CONFIGURATION */
/***************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants and macros to configure your module. These constants are
*   unknown for other modules
****************************************************************************/
/* EasyCASE ( 125
   SBW__tunBeltState */
/* EasyCASE < */
/* Typdefinition fuer den Gurtstatus der einzelnen Passagiere */

typedef union {
    byte  bAll;                                    /* irgendein Passagier nicht angegurtet             */
    struct {
        byte  biDriver : 1;                           /* Fahrer nicht angegurtet                          */
        byte  biCoDriver : 1;                         /* Beifahrer nicht angegurtet                       */
        byte  biMidPassenger : 1;
    } stBelt;
} SBW__tunBeltState;

typedef union {
    byte  bAllRear;
    struct {
        byte  biRight : 1;
        byte  biMiddle : 1;
        byte  biLeft : 1;
        byte  bi3RowRight : 1;
        byte  bi3RowLeft : 1;
    } stBeltRear;
} SBW__tunBeltStateRear;
/*NCAP-Warning Status */
/* EasyCASE C */
typedef struct
{
    word        wCounterWarnTime;              /* Warning time counter */
    word        wCounterPhase;                 /* Phase interval counter  */
    word        wCounterStartTime;             /* Warning count since start */
    word        wCounterPreStartTime;          /* Count since "strapped in vehicle is running" */
    SBW__tunBeltState  unOldBeltState;         /* Status of the belts in during last check */
} SBW__tstNcapWarn;

typedef struct
{
    word        wCounterWarnTimeRear;              /* Warning time counter */
    word        wCounterPhaseRear;                 /* Phase interval counter  */
    word        wCounterStartTimeRear;             /* Warning count since start */
    word        wCounterPreStartTimeRear;          /* Count since "strapped in vehicle is running" */
} SBW__tstNcapWarnRear;

/* Lampen */
typedef enum {
    nLampStatic,
    nLampFlash,
    nNoLampWarning
} tenWarnPhaseLamp;

/* Warning request status */
/* EasyCASE C */
typedef struct
{
    tenWarnPhaseLamp   enNewWarnRequestLamp;        /* new warning phase (lamp)  */
    tenWarnPhaseLamp   enAktWarnRequestLamp;        /* current warning phase (lamp) */
    tenWarnPhaseBuzzer enNewWarnRequestBuzzer;      /* new warning phase (acoustic) */
    bool               boDisableBuzzer;             /* Disable acoustic warning  */
    bool               boShortPhase;                /* Short phases 1-3  */
} SBW__tstWarnRequest;

/* EasyCASE > */
/* EasyCASE ) */
/* EasyCASE ( 126
   Compiler Switches */
#define SBW__CFG_SwiIndividualSeat Off
/*
*
* Description        : handling of SeatBkRst_RL_Stat and SeatBkRst_RR_Stat
* Val. range / Coding: On  (For any other project different than W204)
*                      Off (Section will not be compiled)
*/
#define SBW__CFG_SwiDebugTimeMeasurement Off
/*
*
* Description        : Debugschalter fuer Zeitmessung der Interruptsperre
* Val. range / Coding: On  (Section will be compiled)
*                      Off (Section will not be compiled)
*/

#define SBW__CFG_EnumWimId Off  
/*
 *
 * Description        : What type does the warning ID have
 * Val. range / Coding: On  Warning ID is of type WIM_tenMsg
 *                      Off Warning ID is of type uint32
 */

#define SBW__CFG_CanLampState On  
/*
 *
 * Description        : If the state of the warning lamp needs
 *                      to be sent on CAN or not. Only BR213 uses this
 * Val. range / Coding: On  Message is sent on CAN
 *                      Off Message is not sent
 */
/* EasyCASE ( 127
   Compilerwarnung erzeugen, falls Debugschalter eingeschaltet ist */
#if SBW__CFG_SwiDebugTimeMeasurement
/* EasyCASE - */
static const word TimeMeasurement = 0;
/* EasyCASE - */
#endif
/* EasyCASE ) */
/* EasyCASE ) */
/* EasyCASE ( 128
   Timer */
static mediumconst word SBW__wBuzzerPhaseNCAPTime = 930; /* 93 Sekunden
*
* Description: Zaehler fuer die Laenge der NCAP-Warnung (Phase 4)
*
* Values     : 0 - 65535
*/
/* EasyCASE > */
/* EasyCASE ) */
/* EasyCASE ( 130
   Summer */
/* EasyCASE < */
typedef struct {
    word            wStartTime;
    word            wStartTimeSh;
    word            wOnTime;
    word            wOffTime;
    uint32          enLogDevice;
} SBW__tstBuzzer;
/* EasyCASE > */
/* EasyCASE - */
/* EasyCASE < */

/* Warnphasen */

static uint8 SBW__StatusIconRequest;
static mediumconst word SBW__wCounterFinish = 0xFFFF;
/* EasyCASE > */
/* EasyCASE - */
/* EasyCASE < */
static mediumconst SBW__tstBuzzer SBW__stBuzzer[nNoBuzzerWarning + 1] = {
    /* wStartTime  wStartTimeSh  wOnTime  wOffTime  enLogDevice                    wFrequency */
    { 0, 0, 0, 0, 0x20037200 },  /* loud buzzer, frequency 2 Hz (additional seatbelt warning)   */
    { 0, 0, 10, 30, 0x20037200 },  /* quiet gong, frequency 0,25 Hz                             */
    { 200, 100, 10, 10, 0x20037200 },  /* quiet gong, frequency 0,5 Hz                              */
    { 400, 200, 9, 1, 0x20037200 },  /* quiet gong, frequency 1 Hz                                */
    { 600, 300, 50, 30, 0x20037100 },  /* loud buzzer, interval 5 sec. / 3 sec., frequency 0.125 Hz */
    { 0, 0, 0, 0, 0x00000000 }   /* DUMMY line to avoid any warnings from QAC */
};
/* Threshold for rear SBW */
#define SBW__nSpeedThreshold                 (25)
/* Description: Speed treshold in km/h */
/* Description: SeatBelt_Threshold from EEPROM - for front SBW and rear seat mat*/
#define SBW__nEepromSpeedThreshold          EEH_u8GetSeatBelt_Threshold()
/* Car stands */
#define SBW__boCarStands                    (CST_boGetStatus(CST_nenStatusVelStop))

/**
 * EEProm value for Rear seat belt init time (in ms)
 */
#define SBW__u8RearSeatBeltInitTimeMs       ((1000) * (EEH_biGetBelt_Warning_Back_Init_Time()))

/* EasyCASE ) */
/* EasyCASE ) */
/* EasyCASE ( 6
   EOF */
/*
* End of check if information are already included
*/
#endif                                  /* ifndef SBW_CI_H */


/***************************************************************************
* EOF: sbwwci.h
****************************************************************************/
/* EasyCASE ) */
/* EasyCASE ) */
