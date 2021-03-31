/* EasyCASE V6.5 01/17/2012 09:18:44 */
/* EasyCASE O
If=vertical
LevelNumbers=no
LineNumbers=yes
Colors=8675151,9600103,12582912,8404992,0,0,0,16777215,8388736,13300724,33023,15457455,0,0,0,0,0,8454016,12632256,255,65280,255,255,16711935
ScreenFont=Courier New,Standard,100,4,-14,0,400,0,0,0,0,0,0,3,2,1,49,96,96
PrinterFont=Courier New,,80,4,-66,0,400,0,0,0,0,0,0,3,2,1,49,600,600
LastLevelId=1185 */
/* EasyCASE ( 66
   SBWwC2.C */
/* EasyCASE ( 99
   FILE HEADER */
/***************************************************************************
*===================== Copyright by SiemensVDO Automotive AG ======================
****************************************************************************
* Titel        : sbwwc2.c
*
* Description  : Die Aufgabe des SBW-Moduls ist eine baureihen�bergreifende
*                Warnerfassung und Anmeldung der Gurtwarnung. Von SBW werden
*                nur die Gurtwarnung Akustik und die Gurtwarnung Lampe nach
*                Euro-NCAP bedient.
*                In SBW_C2 werden die CAN Signale ausgewertet und verknuepft.
*
* Environment  : FJ-16 und FJ-32
*
* Responsible  : Joachim Pieper, Siemens VDO Automotive AG
*
* Guidelines   : SMK
*
* Template name: SWMODxC2.C, Revision 1.0
*
* CASE-Tool    : EasyCASE(C++), Version 6.32
*
* Revision List: (Will be filled by PVCS)
* Archive: $Log: sbw1C2.C  $
* Archive: Revision 1.3 2014/03/14 07:16:05CET Olenici-EXT, Alexandru (uidw5408)
* Archive: Updated after MR38101 and MR38055.
* Archive: Revision 1.2 2013/08/09 09:48:56CEST Lacko-EXT, Jan (uidu0305)
* Archive: Update according to MR34248.
* Archive: Revision 1.1 2012/07/13 17:15:22CEST Lacko-EXT, Jan (uidu0305)
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/sbw/adapt/project.pj
* Archive: Revision 1.1 2012/07/13 17:15:22CEST Lacko Jan (uidu0305) (uidu0305)
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/sbw/adapt/project.pj
*
*    Rev 1.3   Jul 13 2012 17:49:36   Jan.Cavojsky-EXT
* DC MR 27014
*
*    Rev 1.2   May 31 2012 15:28:58   Jan.Cavojsky-EXT
* DC MR 25510
*
*    Rev 1.1   May 18 2012 18:45:10   Jan.Cavojsky-EXT
* DC MR 25587
*
*    Rev 1.0   Jan 17 2012 10:13:04   Jan.Cavojsky-EXT
* Initial revision.
*
*    Rev 1.5   Apr 14 2011 18:15:16   Nicolae.Gavrila
* DC MRs:
* 21685: BR222 SBW: counting 30sec only when Warning in display -LP2440
* 21684: BR222 SBW: new Condition instead of car_running -LP2439
*
*    Rev 1.4   Mar 18 2011 16:16:58   Nicolae.Gavrila
* DC MRs 21660, 21666, 21724
*
*    Rev 1.3   Nov 19 2010 10:32:04   Nicolae.Gavrila
* DC MR 21117: Correction SBW
*
*    Rev 1.2   Sep 17 2010 17:51:46   Nicolae.Gavrila
* DC MR 20908: E002/AC, Startup HIL
*
*    Rev 1.1   Sep 02 2010 14:27:06   Nicolae.Gavrila
* Update for CAN Signals name change
*
*    Rev 1.0   Aug 27 2010 16:38:54   Nicolae.Gavrila
* Initial revision.
*
*    Rev 1.6   May 15 2009 09:39:48   Nicolae.Gavrila
* DC MR 19791: -LP2149: Change of speed Limit for Acoustic Rearseatbelt warning
*
*    Rev 1.5   Mar 13 2009 14:48:48   Nicolae.Gavrila
* DC MR 19611: Vehicle silhouette RSST + Applications, -L2074
*
*    Rev 1.4   Dec 09 2008 17:30:04   Nicolae.Gavrila
* DC MR 19344: rear seatbelt warning follow up MR
*
*    Rev 1.3   Nov 27 2008 09:52:40   Nicolae.Gavrila
* DC MR 19310: New / modified "original" display pictures for SRSC Style Guide
*
*    Rev 1.2   Oct 10 2008 17:43:54   Nicolae.Gavrila
* DC MR 18453 Change of warning layout
*
*    Rev 1.1   Aug 22 2008 09:47:40   Radu.Teaha
* DC MR 18905
*
*    Rev 1.0   Mar 04 2008 14:14:04   Gaertner
* Initial revision.
*
*    Rev 1.5   Apr 23 2007 08:59:46   Horatiu.Tautan
* DC MR 15791 - update
*
*    Rev 1.4   Apr 11 2007 10:59:48   Radu.Teaha
* DC MR 15791
*
*    Rev 1.3   Feb 09 2007 16:10:04   Radu.Teaha
* DC MR 15537
*
*    Rev 1.2   Oct 10 2006 08:32:24   Radu.Teaha
* DC MR 15014
*
*    Rev 1.1   Apr 27 2006 12:53:12   Radu.Teaha
* MR 14145
*
*    Rev 1.0   Jan 16 2006 10:38:38   Toth.Zoltan
* Initial revision. Copied from revision 1.6 of file "Sbwmc2.c".
*
*
****************************************************************************/

/***************************************************************************
* HEADER-FILES (Only those that are needed in this file)
****************************************************************************/
/* System-headerfiles */
#include  <cdef.h>                      /* General definitions and types */

/* Foreign headerfiles */
#include  "wim_c1.h"                    /* Warnings manager interface    */
#include  "cst_c1.h"                    /* Car state information         */
#include  "com.h"
#include  "com_cfg.h"
#include  "irext_c1.h"

/* Own headerfiles */
#include  "sbw_c2.h"                    /* Own interface                 */
#include  "sbw_ci.h"                    /* Module internal configuration */
#include  "sbw_ce.h"
#include "SBW__AcousticPlayer.h"

/* EasyCASE ) */
/* EasyCASE ( 1041
   DEFINITIONS */
/***************************************************************************
* GLOBAL DEFINITIONS
*
* In this section define
* - all global ROM-constants of your module
* - all global variables of your module
****************************************************************************/
/* EasyCASE - */
/* Rear seat belt timer value is set to 5sec for NCAP2018 when all the seat belts are fastened */
#define SBW__nRsbwTimerNCAP2018Fastened 50
/* EasyCASE - */
/***************************************************************************
* FILE LOCAL DEFINITIONS
*
* In this section define
* - all file local macros
* - all file local define-constants
* - all file local ROM-constants (static)
* - all file local type definitions
* - all file local variables (static)
****************************************************************************/

enum enSeatMat{
    SBW_nenSeatMatNotMonitored,
    SBW_nenSeatMatPresent,
    SBW_nenSeatMatAbsent,
    SBW_nenSeatMatUnknown
};
/* SBW__tenGS possible values of seatbelt state */
typedef enum SBW__tenGS {
    SBW_nenGSGesteckt, /*
    *
    * Description  : Inserted Buckle / GS_OK
    *
    * Access rights: r
    *
    * Values       : #00
    */
    SBW_nenGSNichtGesteckt, /*
    *
    * Description  : Buckle not plugged / GS_NOK
    *
    * Access rights: r
    *
    * Values       : #01
    */
    SBW_nenGSFehler, /*
    *
    * Description  : error buckle / GS_FEHLER
    *
    * Access rights: r
    *
    * Values       : #02
    */
    SBW_nenGSSignalNichtVerfuegbar /*
    *
    * Description  : Signal is not available / SNA
    *
    * Access rights: r
    *
    * Values       : #03
    */
} SBW__tenGS;
/* SBW__tenSBE possible values of seat occupancy */
typedef enum SBW__tenSBE {
    SBW_nenSBEOccupantPresent, /*
    *
    * Description  : Occupant Present / OP_PRESENT
    *
    * Access rights: r
    *
    * Values       : #00
    */
    SBW_nenSBEOccupantAbsent, /*
    *
    * Description  : Occupant Absent / OP_ABSENT
    *
    * Access rights: r
    *
    * Values       : #01
    */
    SBW_nenSBEFailure, /*
    *
    * Description  : Failure / OP_FAIL
    *
    * Access rights: r
    *
    * Values       : #02
    */
    SBW_nenSBESignalNotAvailable /*
    *
    * Description  : Signal not available / SNA
    *
    * Access rights: r
    *
    * Values       : #03
    */
} SBW__tenSBE;
/* SBW__tenDoorState possible values of door state */
typedef enum SBW__tenDoorState {
    SBW__nenDoorNotDef, /*
    *
    * Description  : Door state not defined
    *
    * Access rights: r
    *
    * Values       : #00
    */
    SBW__nenDoorClosed, /*
    *
    * Description  : Door closed
    *
    * Access rights: r
    *
    * Values       : #01
    */
    SBW__nenDoorOpen, /*
    *
    * Description  : Door open
    *
    * Access rights: r
    *
    * Values       : #02
    */
    SBW__nenDoorSignalNotAvailable /*
    *
    * Description  : Door signal not available
    *
    * Access rights: r
    *
    * Values       : #03
    */
} SBW__tenDoorState;
/* SBW__tenRearseatState possible values of rear seatbelt state */
typedef enum SBW__tenRearseatState
{
    SBW__nenSeatUnlocked, /*
    *
    * Description  : Rear seat not present
    *
    * Access rights: r
    *
    * Values       : #00
    */
    SBW__nenSeatFolded, /*
    *
    * Description  : Rear seat not present/folded
    *
    * Access rights: r
    *
    * Values       : #01
    */
    SBW__nenSeatPresent, /*
    *
    * Description  : Rear seat present
    *
    * Access rights: r
    *
    * Values       : #02
    */
    SBW__nenSeatSNA /*
    *
    * Description  : Rear seat signal not available
    *
    * Access rights: r
    *
    * Values       : #03
    */
} SBW__tenRearseatState;
/* SBW__tstSeatBeltState used for keep the status of signal for seatbelt module */
typedef struct
{
    uint8 u8State;
    bool boTo;
    bool boFv;
    bool boSo;
} SBW__tstSeatBeltState;
typedef SBW__tstSeatBeltState SBW__tstDoorState;
typedef SBW__tstSeatBeltState SBW__tstSeatState;
typedef SBW__tstSeatBeltState SBW__tstPassengerState;
typedef SBW__tstSeatBeltState SBW__tstSeatStateMat;
/* possible values for rear seats depending of position of the seat */
enum enRearSeat
{
    nenRight,
    nenMiddle,
    nenLeft,
    nen3RowRight,
    nen3RowLeft,
    nenNumberOfSeats
};
/* possible state of the rear seat */
enum enRearSeatState
{
    /** Rear seat is not occupied, no need to blink **/
    nenEmpty,
    /** Rear seat is fastened **/
    nenFastened,
    /** Rear seat is unfastened and blnking **/
    nenBlinking,
    /** Rear seat is unfastened but have not blinked yet **/
    nenWaiting,
    /** Rear seat is unfastened and have already blinked **/
    nenInactive,
    /** Rear seat is in SNA, FAULT or Timeout state **/
    nenError
};
/* possible numbers of the rear rows */
enum enRearRow
{
    nenSecondRow,
    nenThirdRow,
    nenNumberofRows
};
typedef struct SBW__tstRsbwStatNCAP2018Flg
{
    /* Flag for previous state of rear door left  */
    bool boRearDoorLeftWasOpen;
    /* Flag for previous state of rear door right */
    bool boRearDoorRightWasOpen;
    /* Flag for previous state of rear door trunk */
    bool boRearDoorTrunkWasOpen;
    /* Timer for rear seatbelts warnings */
    uint16 u16Timer;
    /* Timer for 0x200666/0x20072B */
    uint16 u16SoundTimer;
    enum enRearSeatState enSeatStates[nenNumberOfSeats];
    enum enSeatMat enSeatPresence[nenNumberOfSeats];
    /* Indicates whether 0x200420 should be displayed (for example, at start) */
    bool boDisplayAtStart;
    /* Indicates that KL15 was switch from OFF to ON */
    bool boKl15SwitchedOn;
    /* Indicates that SBW was in error state */
    bool boErrorStateOld;
    /* Contains number of passengers which are on the rear seats */
    uint8 au8NumberOfPassengers[nenNumberofRows];
} SBW__tstRsbwStatNCAP2018Flg;
#define for_all_seats(__i) for((__i) = nenRight; (__i) < nenNumberOfSeats; (__i)++)
#define for_all_rows(__i) for((__i) = nenSecondRow; (__i) < nenNumberofRows; (__i)++)
typedef struct SBW__tstRsbwSoundFlg
{
    /** Warning which is on the screen or was cancelled **/
    uint32 u32ActiveRsbw;
    /** The warning was cancelled by user, by timer or by door **/
    bool boCancelled;
} SBW__tstRsbwSoundFlg;
/* Variable used by rear seat belt warnings handler NCAP2018 */
static SBW__tstRsbwStatNCAP2018Flg SBW__stStatNCAP2018Flg;
static enum enRearSeatState enOldSeatStates[nenNumberOfSeats];
static SBW__tstRsbwSoundFlg SBW__stStatSoundFlg;
/* variable used to store the number of the active warning in order to remove it
whenever the condition changes (another warning appear or timer expires) */
static bool SBW__boSbwDisplayMaster = False;
/* Front left door */
static SBW__tstDoorState stFLdoor;
/* Front right door */
static SBW__tstDoorState stFRdoor;

/**
 * @brief KL15g ready for rear seat belt turn on delay
 */
static bool SBW__boKL15gReady = False;

/**
 * @brief Rear belt counter to reach the delay
 */
static uint16 SBW__u16RsbwDelayCounterMs = 0;

/**
 * @brief 100ms increment for cyclic per 100ms function
 */
static const uint16 SBW__u16RsbwCyclicIncStepMs = 100;

/**
 * @brief Flag to stop checking KL15g delay for rear seat belt
 */
static bool SBW__boKL15gReadyStopChecking = False;

typedef union {
    byte bAllRear;
    struct stDoorRear {
        byte biLeft : 1;
        byte biRight : 1;
        byte biTrunk : 1;
    } stDoorRear;
} SBW__tunDoorOpenRear;

static struct
{
    SBW__tunDoorOpenRear         unDoorRearOpen;
    bool                     boDriverBeltStateValid;    /* Driver Belt Valid State Information*/
} SBW__stCanRear;

SBW__tstNcapWarnRear SBW__stNcapWarnRear;
SBW__tstWarnRequest SBW__stWarnRequestRear;

static bool boSBW_areSlackDisabled = False;
extern bool SBW__boSoundSupress;
bool SBW__boSoundActivatedRear = False;

/* timers list for each seat*/
static const TIMER_tenTimerName SBW__aenDebounceTimers[nenNumberOfSeats] = {
    TIMER_nSBW_DebounceTimer_RR,
    TIMER_nSBW_DebounceTimer_RM,
    TIMER_nSBW_DebounceTimer_RL,
    TIMER_nSBW_DebounceTimer_3RR,
    TIMER_nSBW_DebounceTimer_3RL
};

/* EasyCASE - */
/******************************************************************************
* FILE LOCAL FUNCTION PROTOTYPES
*
* In this section declare
* - all tasks
* - all file local function prototypes needed for your module (static)
******************************************************************************/

/**
 * @brief Update states for rear seat belt delay handling
 * @param boKl15GReady Set the KL15g ready
 * @param boStopChecking True if there is no point to handle transitions KL15g_Off<->KL15g_NotReady<->KL15g_Ready anymore
 * @param boResetDelayCounter True if counter should be reset
 */
static void SBW__vUpdateRsbwKL15gReadyState(bool boKl15GReady, bool boStopChecking, bool boResetDelayCounter);

/* EasyCASE ( 1046
SBW__vRsbwRegisterNCAP2018 */
/***************************************************************************
* Interface Description: Called from SBW__vRearSeatbeltWrn2018 context with byte
*                        parameter as number of counted fastened rear seatbelts
*
* Implementation       : Using the parameter register the appropiate warning
*
* Return Value         : void
*
* Author               : Alexander Wagner
*
****************************************************************************/
static void SBW__vRsbwRegisterNCAP2018(uint32 u32HilId, bool boForce);

/* EasyCASE ( 1046
SBW__vHandleAcoustic */
/***************************************************************************
* Interface Description: Handle the acoustic part of rear seatbelts
*
* Implementation       :
*
* Return Value         : void
*
* Author               : Alexander Wagner
*
****************************************************************************/
static void SBW__vHandleAcoustic(void);

/* SBW__boAreAcousticsActive */
/***************************************************************************
* Interface Description: Returns True if acoustics are EEPROM enabled, False otherwise
*
* Implementation       :
*
* Return Value         : boolean
*
* Author               :
*
****************************************************************************/
static bool SBW__boAreAcousticsActive(void);

/* SBW__u32GetBlinkingWarning */
/***************************************************************************
* Interface Description: Returns the blinking warning 0x200666 or 0x20072B
*
* Implementation       :
*
* Return Value         : uint32
*
* Author               :
*
****************************************************************************/
static uint32 SBW__u32GetBlinkingWarning(void);

/* SBW__boIsWarningBlinking */
/***************************************************************************
* Interface Description: Returns True if the warning is blinking (0x200666 or 0x20072B)
*
* Implementation       :
*
* Return Value         : boolean
*
* Author               :
*
****************************************************************************/
static bool SBW__boIsWarningBlinking(uint32);

/* SBW__boSeatIsApplicable */
/***************************************************************************
* Interface Description: Returns True if the seat is applicable considering the coding in EEPROM
*
* Implementation       :
*
* Return Value         : boolean
*
* Author               :
*
****************************************************************************/
static bool SBW__boSeatIsApplicable(enum enRearSeat);

/* SBW__enGetSeatRow */
/***************************************************************************
* Interface Description: Return to which row corresponds the seat
*
* Implementation       :
*
* Return Value         : enum
*
* Author               :
*
****************************************************************************/
static enum enRearRow SBW__enGetSeatRow(enum enRearSeat enSeat);

#ifdef SBW__HL
/* SBW__vAbortWarnRearMat */
/***************************************************************************
* Interface Description:
*
* Implementation       :
*
* Return Value         : void
*
* Author               :
*
****************************************************************************/
static void SBW__vAbortWarnRearMat(void);

/* SBW__vRetriggerWarnRearMat */
/***************************************************************************
* Interface Description:
*
* Implementation       :
*
* Return Value         : void
*
* Author               :
*
****************************************************************************/
static void SBW__vRetriggerWarnRearMat(void);

/* SBW__vHandleRearMatWarnStart */
/***************************************************************************
* Interface Description:
*
* Implementation       : -
*
* Return Value         : -
*
* Author               :
*
****************************************************************************/
static void SBW__vHandleRearMatWarnStart(void);

/* SBW__vHandleRearMatWarn */
/***************************************************************************
* Interface Description:
*
* Implementation       : -
*
* Return Value         : -
*
* Author               :
*
****************************************************************************/
static void SBW__vHandleRearMatWarn(void);

/* SBW__vHandleRequestRearMat */
/***************************************************************************
* Interface Description:
*
* Implementation       : -
*
* Return Value         : -
*
* Author               :
*
****************************************************************************/
static void SBW__vHandleRequestRearMat(void);

/*SBW__boIsAcousticOver*/
/***************************************************************************
* Interface Description:
*
* Implementation       : -
*
* Return Value         : -
*
* Author               :
*
****************************************************************************/
static bool SBW__boIsAcousticOver(void);
#endif
/* EasyCASE ) */
/* EasyCASE ) */
/* EasyCASE ( 1085
   DOCUMENT MANAGER */
#ifdef _DOCM_
#include "sbw_c1.dom"
#endif
/* EasyCASE ) */
/* EasyCASE ( 1048
   FILE LOCAL FUNCTIONS */
/** Register a warning with the given HIL ID **/
/* SBW__vSetWarning */
static void SBW__vSetWarning(uint32 u32HilId)
{
    if (u32HilId != SBW__nNoWarn)
    {
        WIM_vRetriggerIntEvent(u32HilId);
    }
    if (SBW__stStatSoundFlg.u32ActiveRsbw != u32HilId)
    {
        if (SBW__stStatSoundFlg.u32ActiveRsbw != SBW__nNoWarn)  /* Previously triggered warning detected */
        {
            WIM_vRelIntEvent(SBW__stStatSoundFlg.u32ActiveRsbw);  /* Remove the current warning */
        }
        SBW__stStatSoundFlg.u32ActiveRsbw = u32HilId;
    }
}
/** Release the currently displayed warning **/
/* SBW__vReleaseWarning */
static void SBW__vReleaseWarning(void)
{
    if (SBW__stStatSoundFlg.boCancelled == False)
    {
        WIM_vRelIntEvent(SBW__stStatSoundFlg.u32ActiveRsbw);
        SBW__stStatSoundFlg.boCancelled = True;
    }
}
/* determine if the seat is applicable or not */
/* SBW__boSeatIsApplicable */
static bool SBW__boSeatIsApplicable(enum enRearSeat enSeat)
{
    static const uint8 u8RearSeat_Right = 1 << nenRight;
    static const uint8 u8RearSeat_Left = 1 << nenLeft;
    static const uint8 u8RearSeat_Middle = 1 << nenMiddle;
    static const uint8 u8RearSeat_3RowRight = 1 << nen3RowRight;
    static const uint8 u8RearSeat_3RowLeft = 1 << nen3RowLeft;
    uint8 u8RearSeat_Configuration = 0;
#ifdef SBW__LL
    if (SBW__u8Eeprom_VehLine() == SBW__nVehLineBR464)
    {
        u8RearSeat_Configuration = (u8RearSeat_Right | u8RearSeat_Left)&(1 << enSeat);
    }
    else
    {
        switch (SBW__u8Eeprom_RearSeatLayout)
        {

        case SBW__nRear2Seats:
        case SBW__nRear4Seats:
        case SBW__nRear3Seats:
            u8RearSeat_Configuration = (u8RearSeat_Right | u8RearSeat_Left | u8RearSeat_Middle)&(1 << enSeat);
            break;
        case SBW__nRear5Seats:
            u8RearSeat_Configuration = (u8RearSeat_Right | u8RearSeat_Left | u8RearSeat_3RowRight | u8RearSeat_3RowLeft | u8RearSeat_Middle)&(1 << enSeat);
            break;
        default:
            break;
        }
    }
#else
    switch (SBW__u8Eeprom_RearSeatLayout)
    {
    case SBW__nRear2Seats:
    case SBW__nRear4Seats:
    case SBW__nRear3Seats:
        u8RearSeat_Configuration = (u8RearSeat_Right | u8RearSeat_Left | u8RearSeat_Middle)&(1 << enSeat);
        break;
    case SBW__nRear5Seats:
        u8RearSeat_Configuration = (u8RearSeat_Right | u8RearSeat_Left | u8RearSeat_3RowRight | u8RearSeat_3RowLeft | u8RearSeat_Middle)&(1 << enSeat);
        break;
    default:
        break;
    }

#endif
    return u8RearSeat_Configuration != 0;
}
/* determine to which row corresponds the seat */
/* SBW__enGetSeatRow */
static enum enRearRow SBW__enGetSeatRow(enum enRearSeat enSeat)
{
    static enum enRearRow enRow;
    switch (enSeat)
    {
    case nenRight:
    case nenLeft:
    case nenMiddle:
        enRow = nenSecondRow;
        break;
    case nen3RowRight:
    case nen3RowLeft:
        enRow = nenThirdRow;
        break;
    }
    return enRow;
}
/** Check the state of Rear Seat **/
/* SBW__boAreAllFastened */
static bool SBW__boAreAllFastened(void)
{
    enum enRearSeat enSeat;
    enum enRearSeatState enRearSeatState;
    bool boResult = True;
    for_all_seats(enSeat)
    {
        if (True == SBW__boSeatIsApplicable(enSeat))
        {
            enRearSeatState = SBW__stStatNCAP2018Flg.enSeatStates[enSeat];
            if (enRearSeatState != nenFastened)
                boResult = False;
        }
        else
        {
            // nothing to do
        }

    }
    return boResult;
}

/* Register warning for RSBW */
/* SBW__vRsbwRegisterNCAP2018 */
static void SBW__vRsbwRegisterNCAP2018(uint32 u32HilId, bool boForce)
{
    bool boRespawnTimer = False;
    uint32 u32CurrentWarning = SBW__stStatSoundFlg.boCancelled ? SBW__nNoWarn : SBW__stStatSoundFlg.u32ActiveRsbw;  /* Force 0x200420 to be shown at start (KL15 on) */
    if (SBW__stStatNCAP2018Flg.boDisplayAtStart)
    {
        SBW__stStatNCAP2018Flg.boDisplayAtStart = False;
        if (u32HilId == SBW__nNoWarn)
        {
            u32HilId = SBW__nNoSoundWarn;
        }
        boForce = True;
    }
    /* Release current warning if needed */
    if ((u32CurrentWarning != SBW__nNoWarn) && (u32CurrentWarning != u32HilId))
    {
        WIM_vRelIntEvent(SBW__stStatSoundFlg.u32ActiveRsbw);
        SBW__stStatSoundFlg.u32ActiveRsbw = SBW__nNoWarn;
        boRespawnTimer = True;
    }
    /* Activate new warning or retrigger existing one */
    if (u32HilId != SBW__nNoWarn)
    {
        bool boStart = False;
        if (u32HilId != SBW__stStatSoundFlg.u32ActiveRsbw)
        {
            WIM_vSetIntEvent(u32HilId);
            SBW__stStatSoundFlg.u32ActiveRsbw = u32HilId;
            boRespawnTimer = True;
            SBW__stStatNCAP2018Flg.u16SoundTimer = 0;
        }
        else if (boForce)
        {
            if (SBW__stStatSoundFlg.boCancelled)
            {
                WIM_vSetIntEvent(u32HilId);
                SBW__stStatSoundFlg.u32ActiveRsbw = u32HilId;
                SBW__stStatNCAP2018Flg.u16SoundTimer = 0;
            }
            else
            {
                WIM_vRetriggerIntEvent(u32HilId);
            }
            boRespawnTimer = True;
        }
        else
        {
            /* do nothing */
        }
    }

    if (boRespawnTimer)
    {
        if (SBW__stStatSoundFlg.u32ActiveRsbw == SBW__nNoWarn)
        {
            SBW__stStatNCAP2018Flg.u16Timer = 0;
        }
        else if (SBW__boAreAllFastened())
        {
            SBW__stStatNCAP2018Flg.u16Timer = SBW__nRsbwTimerNCAP2018Fastened;
        }
        else
        {
            SBW__stStatNCAP2018Flg.u16Timer = SBW__nRsbwTimerNCAP2018 * 10;
        }
        SBW__stStatSoundFlg.boCancelled = False;
    }
}
/** Returns current car speed in km/h **/
/* SBW__u16GetCarSpeed */
static uint16 SBW__u16GetCarSpeed(void)
{
    uint16 u16CarSpeed;
    SBW__vGetVelocity(&u16CarSpeed, SBW_nUnitKm);
    return u16CarSpeed;
}
/** Returns true if car speed is above threshold (25 km/h) **/
/* SBW__boIsSpeedOverThreshold */
static bool SBW__boIsSpeedOverThreshold(void)
{
    bool boSpeedOver;
#ifdef SBW__HL
    boSpeedOver = SBW__boEeprom_RearSeatMat() ? ((SBW__u16GetCarSpeed() >= SBW__nEepromSpeedThreshold) && !(SBW__boCarStands)) : (SBW__u16GetCarSpeed() >= SBW__nSpeedThreshold);
#endif
#ifdef SBW__LL
    boSpeedOver = SBW__u16GetCarSpeed() >= SBW__nSpeedThreshold;
#endif
    return boSpeedOver;
}
/** Returns state of the front doors **/
/* SBW__stGetDoorState */
SBW__tunDoorOpen SBW__stGetDoorState(void)
{
    /***************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local variables (auto and static)
    ****************************************************************************/
    /* EasyCASE - */
    SBW__tunDoorOpen unDoorOpen;
    /* EasyCASE - */
    bool SBW__boLeftHandDriving = False;

    /* EasyCASE - */
    /***************************************************************************
    * FUNCTION CODE
    ****************************************************************************/
    /* EasyCASE - */
    IREXT_vDisableAndSave_Int();
    /* EasyCASE - */
    /* Read CAN signals */
    //CIO_vInDrRLtch_FL_Stat(&stFLdoor);
    Com_ReceiveSignalGroup(Com_Grp_Door_FL_Stat_Pr2);
    Com_ReceiveShadowSignal(Com_DrRLtch_FL_Stat, &stFLdoor.u8State);
    stFLdoor.boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Door_FL_Stat_Pr2) ? True : False);
    stFLdoor.boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Door_FL_Stat_Pr2) ? True : False);
    stFLdoor.boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Door_FL_Stat_Pr2) ? True : False);

    //CIO_vInDrRLtch_FR_Stat(&stFRdoor);
    Com_ReceiveSignalGroup(Com_Grp_Door_FR_Stat_Pr2);
    Com_ReceiveShadowSignal(Com_DrRLtch_FR_Stat, &stFRdoor.u8State);
    stFRdoor.boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Door_FR_Stat_Pr2) ? True : False);
    stFRdoor.boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Door_FR_Stat_Pr2) ? True : False);
    stFRdoor.boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Door_FR_Stat_Pr2) ? True : False);
    /* EasyCASE - */
    IREXT_vRestore_Int();
    /* EasyCASE - */
    unDoorOpen.bAll = 0;
    if ((SBW__u8GetStaticLeftHandDrive() == SBW__nLeftHandDriving) ||
        (SBW__u8GetStaticLeftHandDrive() == SBW__nRightHandDriving))
    {
        if (SBW__u8GetStaticLeftHandDrive() == SBW__nLeftHandDriving)
        {
            SBW__boLeftHandDriving = True;
        }
        else
        {
            SBW__boLeftHandDriving = False;
        }
    }
    if (SBW__boLeftHandDriving != False)
    {
        if (stFLdoor.boSo == True /*It is state on */)
        {
            if (stFLdoor.boTo == False /* and no timeout ocurred */)
            {
                if (stFLdoor.boFv == True /* First values received */)
                {
                    switch (stFLdoor.u8State)
                    {
                    case SBW__nenDoorOpen:
                        unDoorOpen.stDoor.biDriver = 1;
                        break;
                    case SBW__nenDoorClosed:
                        unDoorOpen.stDoor.biDriver = 0;
                        break;
                    case SBW__nenDoorNotDef:
                        unDoorOpen.stDoor.biDriver = 1;
                        break;
                    case SBW__nenDoorSignalNotAvailable:
                        unDoorOpen.stDoor.biDriver = 1;
                        break;

                    }
                }
                else
                {
                    /*Do nothing*/
                }
            }
            else
            {
                /*Signals are not available*/
                unDoorOpen.stDoor.biDriver = 1;
            }
        }
        else
        {
            /*Do nothing*/
        }
        if (stFRdoor.boSo == True /*It is state on */)
        {
            if (stFRdoor.boTo == False /* and no timeout ocurred */)
            {
                if (stFRdoor.boFv == True /* First values received */)
                {
                    switch (stFRdoor.u8State)
                    {
                    case SBW__nenDoorOpen:
                        unDoorOpen.stDoor.biCoDriver = 1;
                        break;
                    case SBW__nenDoorClosed:
                        unDoorOpen.stDoor.biCoDriver = 0;
                        break;
                    case SBW__nenDoorNotDef:
                        unDoorOpen.stDoor.biCoDriver = 1;
                        break;
                    case SBW__nenDoorSignalNotAvailable:
                        unDoorOpen.stDoor.biCoDriver = 1;
                        break;
                    }
                }
                else
                {
                    /*Do nothing*/
                }
            }
            else
            {
                /*Signals are not available*/
                unDoorOpen.stDoor.biCoDriver = 1;
            }
        }
        else
        {
            /*Do nothing*/
        }
    }
    else
    {
        if (stFLdoor.boSo == True /*It is state on */)
        {
            if (stFLdoor.boTo == False /* and no timeout ocurred */)
            {
                if (stFLdoor.boFv == True /* First values received */)
                {
                    switch (stFLdoor.u8State)
                    {
                    case SBW__nenDoorOpen:
                        unDoorOpen.stDoor.biCoDriver = 1;
                        break;
                    case SBW__nenDoorClosed:
                        unDoorOpen.stDoor.biCoDriver = 0;
                        break;
                    case SBW__nenDoorNotDef:
                        unDoorOpen.stDoor.biCoDriver = 1;
                        break;
                    case SBW__nenDoorSignalNotAvailable:
                        unDoorOpen.stDoor.biCoDriver = 1;
                        break;
                    }
                }
                else
                {
                    /*Do nothing*/
                }
            }
            else
            {
                /*Signals are in timeout*/
                unDoorOpen.stDoor.biCoDriver = 1;
            }
        }
        else
        {
            /*Do nothing*/
        }
        if (stFRdoor.boSo == True /*It is state on */)
        {
            if (stFRdoor.boTo == False /* and no timeout ocurred */)
            {
                if (stFRdoor.boFv == True /* First values received */)
                {
                    switch (stFRdoor.u8State)
                    {
                    case SBW__nenDoorOpen:
                        unDoorOpen.stDoor.biDriver = 1;
                        break;
                    case SBW__nenDoorClosed:
                        unDoorOpen.stDoor.biDriver = 0;
                        break;
                    case SBW__nenDoorNotDef:
                        unDoorOpen.stDoor.biDriver = 1;
                        break;
                    case SBW__nenDoorSignalNotAvailable:
                        unDoorOpen.stDoor.biDriver = 1;
                        break;
                    }
                }
                else
                {
                    /*Do nothing*/
                }
            }
            else
            {
                /*Signals are not available*/
                unDoorOpen.stDoor.biDriver = 1;
            }
        }
        else
        {
            /*Do nothing*/
        }
    }
    return unDoorOpen;
}
/** Initialization of Rear Seat parameters  **/
/* SBW__vRsbwInitActive15 */
void SBW__vRsbwInitActive15(void)
{
    /***************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local variables (auto and static)
    ****************************************************************************/
    enum enRearSeat enSeat;
    enum enRearRow enRow;
    /* The old status bit for rear door detection is updated */
    SBW__stStatSoundFlg.u32ActiveRsbw = SBW__nNoWarn;
    SBW__stStatSoundFlg.boCancelled = True;
    /* Initialize variables for previous states of all rear doors */
    SBW__stStatNCAP2018Flg.boRearDoorLeftWasOpen = False;
    SBW__stStatNCAP2018Flg.boRearDoorRightWasOpen = False;
    SBW__stStatNCAP2018Flg.boRearDoorTrunkWasOpen = False;
    SBW__stStatNCAP2018Flg.u16Timer = 0;
    SBW__stStatNCAP2018Flg.u16SoundTimer = 0;
    for_all_seats(enSeat)
    {
        SBW__stStatNCAP2018Flg.enSeatStates[enSeat] = nenFastened;
    }
    SBW__stStatNCAP2018Flg.boDisplayAtStart = True;
    SBW__stStatNCAP2018Flg.boKl15SwitchedOn = True;
    SBW__stStatNCAP2018Flg.boErrorStateOld = False;
    for_all_rows(enRow)
    {
        SBW__stStatNCAP2018Flg.au8NumberOfPassengers[enRow] = 0;
    }
    SBW__boSoundActivatedRear = False;
#ifdef SBW__HL
    /* Cancel alarm / initialize NCAP warning interval */
    SBW__vAbortWarnRearMat();
    /* Initialize NCAP seat belt warning */
    SBW__vRetriggerWarnRearMat();
    /* Handle warning request */
    SBW__vHandleRequestRearMat();

#endif
    /* Register for events */
    SBW__vRegReceiveEvent();

    /* Reset delay for KL15G Ready */
    SBW__vUpdateRsbwKL15gReadyState(False, False, True);
}
/** Remove the old warning at KL15g -> off **/
/*  SBW__vRsbwDeinitActive15  */
void SBW__vRsbwDeinitActive15(void)
{
    /***************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local variables (auto and static)
    ****************************************************************************/

#ifdef SBW__HL

    if (SBW__boEeprom_RearSeatMat())
    {
        if (!SBW__nMotorOn)
        {
            /* Cancel alarm / initialize NCAP warning interval */
            SBW__vAbortWarnRearMat();
            /* Initialize NCAP seat belt warning */
            SBW__vRetriggerWarnRearMat();
            /* EasyCASE - */
            /* Handle Warning requests */
            SBW__vHandleRequestRearMat();
        }
    }
    else
    {
        SBW__vSetWarning(SBW__nNoWarn);
    }
#else
    SBW__vSetWarning(SBW__nNoWarn);
#endif
    /* De-register for events */
    SBW__vDeregReceiveEvent();

    /* Reset delay for KL15G Ready */
    SBW__vUpdateRsbwKL15gReadyState(False, True, True);
}
/** Check transitions of one seat **/
/* SBW__vCheckRearSeat */
static bool SBW__vCheckRearSeat(enum enRearSeatState * penRearSeatState, const SBW__tstSeatBeltState * pstSeatBeltState, bool boSpeedOver25, enum enRearSeat enCurrentSeat)
{
    bool boForceWarning = False; /* a warning should be issued or re-issued */
    enum enRearSeatState enRearSeatState = *penRearSeatState;
    enum enRearSeat enSeat;
    uint8 au8FastenedSeats[nenNumberofRows] = { 0, 0 };

    /* Check state of rear seat belt */
    if ((pstSeatBeltState->boSo == True) && (pstSeatBeltState->boTo == False) && (pstSeatBeltState->boFv == True))
    {
        if (pstSeatBeltState->u8State == SBW_nenGSGesteckt)
        {
            // Check seat state
            switch (enRearSeatState)
            {
            case nenEmpty:
            case nenBlinking:
            case nenWaiting:
            case nenInactive:
                /* This can mean that:
                * - a rear passenger who initially did was not fastened
                *   revealed himself
                * - a rear passenger who decided to change place fastened
                */
                if (nenSecondRow == SBW__enGetSeatRow(enCurrentSeat))
                {
                    au8FastenedSeats[nenSecondRow] = 1;
                }
                else
                {
                    au8FastenedSeats[nenThirdRow] = 1;
                }

                for_all_seats(enSeat)
                {
                    if (True == SBW__boSeatIsApplicable(enSeat))
                    {
                        if (SBW__stStatNCAP2018Flg.enSeatStates[enSeat] == nenFastened)

                            if (nenSecondRow == SBW__enGetSeatRow(enSeat))
                            {
                                au8FastenedSeats[nenSecondRow]++;
                            }
                            else
                            {
                                au8FastenedSeats[nenThirdRow]++;
                            }
                    }
                    else
                    {
                        // nothing to do
                    }
                }
                if ((au8FastenedSeats[nenSecondRow] == SBW__stStatNCAP2018Flg.au8NumberOfPassengers[nenSecondRow]) && (au8FastenedSeats[nenThirdRow] == SBW__stStatNCAP2018Flg.au8NumberOfPassengers[nenThirdRow]))
                {
                    /* All passengers who decided to change seats fastened */
                    for_all_seats(enSeat)
                    {
                        if (True == SBW__boSeatIsApplicable(enSeat) && (nenSecondRow == SBW__enGetSeatRow(enSeat)))
                        {
                            switch (SBW__stStatNCAP2018Flg.enSeatStates[enSeat])
                            {
                            case nenWaiting:
                            case nenBlinking:
                            case nenInactive:
                                SBW__stStatNCAP2018Flg.enSeatStates[enSeat] = nenEmpty;
                                break;
                            }
                        }
                        else
                        {
                            // nothing to do
                        }
                    }
                }
                else if ((au8FastenedSeats[nenSecondRow] > SBW__stStatNCAP2018Flg.au8NumberOfPassengers[nenSecondRow])
                    && (au8FastenedSeats[nenThirdRow] == SBW__stStatNCAP2018Flg.au8NumberOfPassengers[nenThirdRow]))
                {
                    /* A passenger who decided to change seat fastened */
                    SBW__stStatNCAP2018Flg.au8NumberOfPassengers[nenSecondRow]++;
                }
                if ((au8FastenedSeats[nenThirdRow] == SBW__stStatNCAP2018Flg.au8NumberOfPassengers[nenThirdRow]) && (au8FastenedSeats[nenSecondRow] == SBW__stStatNCAP2018Flg.au8NumberOfPassengers[nenSecondRow]))
                {
                    /* All passengers who decided to change seats fastened */
                    for_all_seats(enSeat)
                    {
                        if (True == SBW__boSeatIsApplicable(enSeat) && nenThirdRow == SBW__enGetSeatRow(enSeat))
                        {
                            switch (SBW__stStatNCAP2018Flg.enSeatStates[enSeat])
                            {
                            case nenWaiting:
                            case nenBlinking:
                            case nenInactive:
                                SBW__stStatNCAP2018Flg.enSeatStates[enSeat] = nenEmpty;
                                break;
                            }
                        }
                        else
                        {
                            // nothing to do
                        }
                    }
                }
                else if ((au8FastenedSeats[nenThirdRow] > SBW__stStatNCAP2018Flg.au8NumberOfPassengers[nenThirdRow])
                    && (au8FastenedSeats[nenSecondRow] == SBW__stStatNCAP2018Flg.au8NumberOfPassengers[nenSecondRow]))
                {
                    /* A passenger who decided to change seat fastened */
                    SBW__stStatNCAP2018Flg.au8NumberOfPassengers[nenThirdRow]++;
                }
                enRearSeatState = nenFastened;
                boForceWarning = True;
                break;
            case nenFastened:
                break;
            case nenError:
                // Transition from error state to normal state
                enRearSeatState = nenFastened;
                boForceWarning = True;
                break;
            }
        }
        else if (pstSeatBeltState->u8State == SBW_nenGSNichtGesteckt)
        {
            // Check seat state
            switch (enRearSeatState)
            {
            case nenEmpty:
                break;
            case nenError:
                /* fallthrough */
            case nenFastened:
                if (boSpeedOver25)
                {
                    enRearSeatState = nenBlinking;
                }
                else
                {
                    enRearSeatState = nenWaiting;
                }
                boForceWarning = True;
                break;
            case nenBlinking:
            case nenWaiting:
            case nenInactive:
                // No transition
                break;
            }
        }
        else
        {
            if (enRearSeatState != nenError)
            {
                enRearSeatState = nenError;
                boForceWarning = True;
            }
        }
        // Check if speed has raised over the threshold
        if ((enRearSeatState == nenWaiting) && boSpeedOver25)
        {
            enRearSeatState = nenBlinking;
        }
    }
    else if (pstSeatBeltState->boFv == True)
    {
        enRearSeatState = nenError;
    }
    // Check if state was changed
    if (enRearSeatState != *penRearSeatState)
    {
        *penRearSeatState = enRearSeatState;
    }
    return boForceWarning;
}

/** Return value of the SBW__vCheckRearDoor() is a bitmask **/
enum SBW__enDoorStateBitmask
{
    /** A door is open **/
    nenOpen = 1,
    /** A door was opened recently **/
    nenOpenedRecently = 2,
    /** A door is not closed **/
    nenNotClosed = 4,
    /** A door was closed recently **/
    nenClosedRecently = 8
};
/** Check door state and returns true if reset should be done **/
/*SBW__vCheckRearDoor*/
static uint8 SBW__vCheckRearDoor(const SBW__tstDoorState * pstDoorState, bool * pboDoorWasOpen)
{
    uint8 u8ReturnValue = nenNotClosed;
    if ((pstDoorState->boSo == True) && (pstDoorState->boTo == False) && (pstDoorState->boFv == True))
    {
        if (pstDoorState->u8State == SBW__nenDoorOpen)
        {
            if (*pboDoorWasOpen == False)
            {
                *pboDoorWasOpen = True;
                u8ReturnValue |= nenOpenedRecently;
            }
            u8ReturnValue |= nenOpen;
        }
        else if (pstDoorState->u8State == SBW__nenDoorClosed)
        {
            u8ReturnValue &= ~nenNotClosed;
            if (*pboDoorWasOpen == True)
            {
                *pboDoorWasOpen = False;
                u8ReturnValue |= nenClosedRecently;
            }
        }
    }
    else
    {
        *pboDoorWasOpen = False;
    }
    return u8ReturnValue;
}

/** Returns seat backrest state **/
/*SBW__boGetSeatBackrestState*/
static bool SBW__boGetSeatBackrestState(void)
{
    /* Local variables for rear seats state */
    SBW__tstSeatState stRearseatLeft;
    SBW__tstSeatState stRearseatRight;
    SBW__tstSeatState stRearseatMiddle;
    SBW__tstSeatState st3rdRearseatLeft;
    SBW__tstSeatState st3rdRearseatRight;
    bool boBackrestState = False;

    /* Read the status of the rear seatbelt */
    //CIO_vInSeatBkRst_RL_Stat(&stRearseatLeft);
    Com_ReceiveSignalGroup(Com_Grp_SeatBkRst_Stat);
    stRearseatLeft.boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_SeatBkRst_Stat) ? True : False);
    stRearseatLeft.boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_SeatBkRst_Stat) ? True : False);
    stRearseatLeft.boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_SeatBkRst_Stat) ? True : False);
    Com_ReceiveShadowSignal(Com_SeatBkRst_RL_Stat, &stRearseatLeft.u8State);
    //CIO_vInSeatBkRst_RR_Stat(&stRearseatRight);
    Com_ReceiveSignalGroup(Com_Grp_SeatBkRst_Stat);
    stRearseatRight.boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_SeatBkRst_Stat) ? True : False);
    stRearseatRight.boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_SeatBkRst_Stat) ? True : False);
    stRearseatRight.boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_SeatBkRst_Stat) ? True : False);
    Com_ReceiveShadowSignal(Com_SeatBkRst_RR_Stat, &stRearseatRight.u8State);
    boBackrestState = (stRearseatLeft.boFv == True) && (stRearseatLeft.boTo == False) &&
        (stRearseatRight.boFv == True) && (stRearseatRight.boTo == False) &&
        (stRearseatLeft.u8State == True) && (stRearseatRight.u8State == True);
    switch (SBW__u8Eeprom_RearSeatLayout)
    {
    case SBW__nRear2Seats:
    case SBW__nRear3Seats:
    case SBW__nRear4Seats:
        //CIO_vInSeatBkRst_RM_Stat(&stRearseatMiddle);
        stRearseatMiddle.boSo = (Com_GetRxSigStateOnFlag(Com_SeatBkRst_RM_Stat) ? True : False);
        stRearseatMiddle.boTo = (Com_GetRxSigTimeoutFlag(Com_SeatBkRst_RM_Stat) ? True : False);
        stRearseatMiddle.boFv = (Com_GetRxSigFirstValueFlag(Com_SeatBkRst_RM_Stat) ? True : False);
        Com_ReceiveSignal(Com_SeatBkRst_RM_Stat, &stRearseatMiddle.u8State);
        boBackrestState = (stRearseatLeft.boFv == True) && (stRearseatLeft.boTo == False) &&
            (stRearseatRight.boFv == True) && (stRearseatRight.boTo == False) &&
            (stRearseatMiddle.boFv == True) && (stRearseatMiddle.boTo == False) &&
            (stRearseatLeft.u8State == True) && (stRearseatRight.u8State == True) && (stRearseatMiddle.u8State == True);
        break;
    case SBW__nRear5Seats:
        //CIO_vInSeatBkRst_RM_Stat(&stRearseatMiddle);
        stRearseatMiddle.boSo = (Com_GetRxSigStateOnFlag(Com_SeatBkRst_RM_Stat) ? True : False);
        stRearseatMiddle.boTo = (Com_GetRxSigTimeoutFlag(Com_SeatBkRst_RM_Stat) ? True : False);
        stRearseatMiddle.boFv = (Com_GetRxSigFirstValueFlag(Com_SeatBkRst_RM_Stat) ? True : False);
        Com_ReceiveSignal(Com_SeatBkRst_RM_Stat, &stRearseatMiddle.u8State);
        //CIO_vInSeatBkRst_3R_Stat(&st3rdRearseatRight);
        Com_ReceiveSignalGroup(Com_Grp_SeatBkRst_3_Stat);
        st3rdRearseatRight.boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_SeatBkRst_3_Stat) ? True : False);
        st3rdRearseatRight.boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_SeatBkRst_3_Stat) ? True : False);
        st3rdRearseatRight.boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_SeatBkRst_3_Stat) ? True : False);
        Com_ReceiveShadowSignal(Com_SeatBkRst_3R_Stat, &st3rdRearseatRight.u8State);
        //CIO_vInSeatBkRst_3L_Stat(&st3rdRearseatLeft);
        Com_ReceiveSignalGroup(Com_Grp_SeatBkRst_3_Stat);
        st3rdRearseatLeft.boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_SeatBkRst_3_Stat) ? True : False);
        st3rdRearseatLeft.boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_SeatBkRst_3_Stat) ? True : False);
        st3rdRearseatLeft.boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_SeatBkRst_3_Stat) ? True : False);
        Com_ReceiveShadowSignal(Com_SeatBkRst_3L_Stat, &st3rdRearseatLeft.u8State);
        boBackrestState = (stRearseatLeft.boFv == True) && (stRearseatLeft.boTo == False) &&
            (stRearseatRight.boFv == True) && (stRearseatRight.boTo == False) &&
            (stRearseatMiddle.boFv == True) && (stRearseatMiddle.boTo == False) &&
            (st3rdRearseatRight.boFv == True) && (st3rdRearseatRight.boTo == False) &&
            (st3rdRearseatLeft.boFv == True) && (st3rdRearseatLeft.boTo == False) &&
            (stRearseatLeft.u8State == True) && (stRearseatRight.u8State == True) && (stRearseatMiddle.u8State == True) &&
            (st3rdRearseatRight.u8State == True) && (st3rdRearseatLeft.u8State == True);
        break;
    default:
        break;
    }
    return boBackrestState;
}
/** Returns warning which has to be displayed according to the situation **/
/*SBW__u32GetDemandedWarning*/
static uint32 SBW__u32GetDemandedWarning(bool * boError)
{
    /* Decide which warning should be displayed at the moment */
    enum enRearSeat enSeat;
    bool boBlinking = False, boUnfastened = False;
    uint32 u32HilId = SBW__nNoWarn;

    if (SBW__boGetSeatBackrestState())
    {
        u32HilId = SBW__nNoWarn;
    }
    else
    {
        for_all_seats(enSeat)
        {
            if (True == SBW__boSeatIsApplicable(enSeat))
            {
                switch (SBW__stStatNCAP2018Flg.enSeatStates[enSeat])
                {
                case nenEmpty:
                case nenFastened:
                    /* do nothing */
                    break;
                case nenBlinking:
                    boBlinking = True;
                    /* fallthrough */
                case nenWaiting:
                case nenInactive:
                    boUnfastened = True;
                    break;
                case nenError:
                    *boError = True;
                    break;
                }
            }
            else
            {
                // nothing to do
            }
        }
        if (*boError == True)
        {
            u32HilId = SBW__nNoSoundWarn;
        }
        else if (boBlinking == True)
        {
            u32HilId = SBW__u32GetBlinkingWarning();
        }
        else
        {
            u32HilId = SBW__nNoSoundWarn;
        }
    }
    return u32HilId;
}
/** Rear seatbelts warning handler NCAP 2018  **/
/*SBW__vRearSeatbeltWrn2018 */
void SBW__vRearSeatbeltWrn2018(bool BoShouldDecrement)
{
    /***************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local variables (auto and static)
    ****************************************************************************/
    bool boSpeedOver25 = False;                 /* Speed value higher than 25km/h */
    /* EasyCASE - */
    /* Local variables for rear seatbelt switches */
    SBW__tstSeatBeltState stSeatBeltStates[nenNumberOfSeats];
    /* EasyCASE - */
    /* Local variables for rear doors state */
    SBW__tstDoorState stRearLeftDoor;
    SBW__tstDoorState stRearRightDoor;
    SBW__tstDoorState stRearTrunkDoor;
    enum enRearSeat enSeat;                        /* loop counter */
    enum enRearRow enRow;
    uint8 u8ReturnValue = 0;
    bool boEmitWarning = False;                    /* a warning should be issued or re-issued */
    uint32 u32HilId;
    bool boError = False;                          /* an error state was detected */
    /***************************************************************************
    * FUNCTION CODE
    ****************************************************************************/
    if (SBW__boKL15gReady)
    {
        IREXT_vDisableAndSave_Int();
        /* Read the status of the rear seatbelt */

        //CIO_vInBckl_Sw_RL_Stat_SAM_R(&stSeatBeltStates[nenLeft]);
        Com_ReceiveSignalGroup(Com_Grp_Bckl_Sw_RL_State_SAM_R);
        stSeatBeltStates[nenLeft].boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Bckl_Sw_RL_State_SAM_R) ? True : False);
        stSeatBeltStates[nenLeft].boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Bckl_Sw_RL_State_SAM_R) ? True : False);
        stSeatBeltStates[nenLeft].boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Bckl_Sw_RL_State_SAM_R) ? True : False);
        Com_ReceiveShadowSignal(Com_Bckl_Sw_RL_Stat_SAM_R, &stSeatBeltStates[nenLeft].u8State);
        //CIO_vInBckl_Sw_RR_Stat_SAM_R(&stSeatBeltStates[nenRight]);
        Com_ReceiveSignalGroup(Com_Grp_Bckl_Sw_RR_State_SAM_R);
        stSeatBeltStates[nenRight].boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Bckl_Sw_RR_State_SAM_R) ? True : False);
        stSeatBeltStates[nenRight].boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Bckl_Sw_RR_State_SAM_R) ? True : False);
        stSeatBeltStates[nenRight].boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Bckl_Sw_RR_State_SAM_R) ? True : False);
        Com_ReceiveShadowSignal(Com_Bckl_Sw_RR_Stat_SAM_R, &stSeatBeltStates[nenRight].u8State);

        switch (SBW__u8Eeprom_RearSeatLayout)
        {
        case SBW__nRear2Seats:
        case SBW__nRear4Seats:
        case SBW__nRear3Seats:
            //CIO_vInBckl_Sw_RM_Stat_SAM_R(&stSeatBeltStates[nenMiddle]);
            Com_ReceiveSignalGroup(Com_Grp_Bckl_Sw_RM_State_SAM_R);
            stSeatBeltStates[nenMiddle].boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Bckl_Sw_RM_State_SAM_R) ? True : False);
            stSeatBeltStates[nenMiddle].boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Bckl_Sw_RM_State_SAM_R) ? True : False);
            stSeatBeltStates[nenMiddle].boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Bckl_Sw_RM_State_SAM_R) ? True : False);
            Com_ReceiveShadowSignal(Com_Bckl_Sw_RM_Stat_SAM_R, &stSeatBeltStates[nenMiddle].u8State);
            break;
        case SBW__nRear5Seats:
            //CIO_vInBckl_Sw_RM_Stat_SAM_R(&stSeatBeltStates[nenMiddle]);
            Com_ReceiveSignalGroup(Com_Grp_Bckl_Sw_RM_State_SAM_R);
            stSeatBeltStates[nenMiddle].boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Bckl_Sw_RM_State_SAM_R) ? True : False);
            stSeatBeltStates[nenMiddle].boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Bckl_Sw_RM_State_SAM_R) ? True : False);
            stSeatBeltStates[nenMiddle].boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Bckl_Sw_RM_State_SAM_R) ? True : False);
            Com_ReceiveShadowSignal(Com_Bckl_Sw_RM_Stat_SAM_R, &stSeatBeltStates[nenMiddle].u8State);
            //CIO_vInBckl_Sw_RL_Stat_SAM_R(&stSeatBeltStates[nen3RowLeft]);
            Com_ReceiveSignalGroup(Com_Grp_Bckl_Sw_3L_State_SAM_R);
            stSeatBeltStates[nen3RowLeft].boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Bckl_Sw_3L_State_SAM_R) ? True : False);
            stSeatBeltStates[nen3RowLeft].boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Bckl_Sw_3L_State_SAM_R) ? True : False);
            stSeatBeltStates[nen3RowLeft].boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Bckl_Sw_3L_State_SAM_R) ? True : False);
            Com_ReceiveShadowSignal(Com_Bckl_Sw_3L_Stat_SAM_R, &stSeatBeltStates[nen3RowLeft].u8State);
            //CIO_vInBckl_Sw_RR_Stat_SAM_R(&stSeatBeltStates[nen3RowRight]);
            Com_ReceiveSignalGroup(Com_Grp_Bckl_Sw_3R_State_SAM_R);
            stSeatBeltStates[nen3RowRight].boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Bckl_Sw_3R_State_SAM_R) ? True : False);
            stSeatBeltStates[nen3RowRight].boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Bckl_Sw_3R_State_SAM_R) ? True : False);
            stSeatBeltStates[nen3RowRight].boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Bckl_Sw_3R_State_SAM_R) ? True : False);
            Com_ReceiveShadowSignal(Com_Bckl_Sw_3R_Stat_SAM_R, &stSeatBeltStates[nen3RowRight].u8State);
            break;
        default:
            break;
        }

        IREXT_vRestore_Int();
        /* Check current speed for threshold */
        boSpeedOver25 = SBW__boIsSpeedOverThreshold();
        /* EasyCASE - */
        if (SBW__stStatNCAP2018Flg.boKl15SwitchedOn)
        {
            /* Reset all seatbelt states on KL15 reset */
            SBW__stStatNCAP2018Flg.boKl15SwitchedOn = False;
            for_all_seats(enSeat)
            {
                SBW__stStatNCAP2018Flg.enSeatStates[enSeat] = nenEmpty;
            }
        }
        /* EasyCASE - */
        /* Check rear seat states */
        for_all_seats(enSeat)
        {
            if (True == SBW__boSeatIsApplicable(enSeat))
            {
                boEmitWarning |= SBW__vCheckRearSeat(SBW__stStatNCAP2018Flg.enSeatStates + enSeat, stSeatBeltStates + enSeat, boSpeedOver25, enSeat);
            }
            else
            {
                // nothing to do
            }
        }
        /* EasyCASE - */
        /* Check door states */
        /* 5-door car: rear doors are checked */
        /* Read the status of the back doors */
        //CIO_vInDrRLtch_RL_Stat(&stRearLeftDoor);
        Com_ReceiveSignalGroup(Com_Grp_Door_RL_Stat_Pr2);
        Com_ReceiveShadowSignal(Com_DrRLtch_RL_Stat, &stRearLeftDoor.u8State);
        stRearLeftDoor.boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Door_RL_Stat_Pr2) ? True : False);
        stRearLeftDoor.boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Door_RL_Stat_Pr2) ? True : False);
        stRearLeftDoor.boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Door_RL_Stat_Pr2) ? True : False);
        //CIO_vInDrRLtch_RR_Stat(&stRearRightDoor);
        Com_ReceiveSignalGroup(Com_Grp_Door_RR_Stat_Pr2);
        Com_ReceiveShadowSignal(Com_DrRLtch_RR_Stat, &stRearRightDoor.u8State);
        stRearRightDoor.boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Door_RR_Stat_Pr2) ? True : False);
        stRearRightDoor.boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Door_RR_Stat_Pr2) ? True : False);
        stRearRightDoor.boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Door_RR_Stat_Pr2) ? True : False);
        //CIO_vInDL_RLtch_Stat(&stRearTrunkDoor);
        Com_ReceiveSignalGroup(Com_Grp_DL_Lk_Stat);
        Com_ReceiveShadowSignal(Com_DL_RLtch_Stat, &stRearTrunkDoor.u8State);
        stRearTrunkDoor.boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_DL_Lk_Stat) ? True : False);
        stRearTrunkDoor.boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_DL_Lk_Stat) ? True : False);
        stRearTrunkDoor.boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_DL_Lk_Stat) ? True : False);
        /* EasyCASE - */
        u8ReturnValue |= SBW__vCheckRearDoor(&stRearLeftDoor, &SBW__stStatNCAP2018Flg.boRearDoorLeftWasOpen);
        u8ReturnValue |= SBW__vCheckRearDoor(&stRearRightDoor, &SBW__stStatNCAP2018Flg.boRearDoorRightWasOpen);
        u8ReturnValue |= SBW__vCheckRearDoor(&stRearTrunkDoor, &SBW__stStatNCAP2018Flg.boRearDoorTrunkWasOpen);
        /* EasyCASE - */
        /* This two transitions are valid only if car does not move */
        if (0 == SBW__u16GetCarSpeed())
        {
            /* If at least one door has recently been opened... */
            if (u8ReturnValue & nenOpenedRecently)
            {
                /* ...then warning will be released */
                SBW__vReleaseWarning();
            }
            /* If at least one door was recently closed... */
            if (u8ReturnValue & nenClosedRecently)
            {
                /* ... and both doors are closed now, ... */
                if ((u8ReturnValue & nenNotClosed) == 0)
                {
                    for_all_rows(enRow)
                    {
                        /* ...reset the state and calculate number of the rear passengers */
                        SBW__stStatNCAP2018Flg.au8NumberOfPassengers[enRow] = 0;
                    }
                    for_all_seats(enSeat)
                    {
                        if (True == SBW__boSeatIsApplicable(enSeat))
                        {
                            switch (SBW__stStatNCAP2018Flg.enSeatStates[enSeat])
                            {
                            case nenWaiting:
                            case nenBlinking:
                            case nenInactive:
                                /* If seat is not occupied, it will be considered empty */
                                SBW__stStatNCAP2018Flg.enSeatStates[enSeat] = nenEmpty;
                                break;
                            case nenError:
                                /* The state will stay the same */
                                break;
                            case nenFastened:
                                /* Rear passenger is detected */
                                if (nenSecondRow == SBW__enGetSeatRow(enSeat))
                                {
                                    SBW__stStatNCAP2018Flg.au8NumberOfPassengers[nenSecondRow]++;
                                }
                                else
                                {
                                    SBW__stStatNCAP2018Flg.au8NumberOfPassengers[nenThirdRow]++;
                                }
                                break;
                            }
                        }
                        else
                        {
                            // nothing to do
                        }
                    }
                    /* Launch the 0x200420 */
                    boEmitWarning = True;
                }
            }
        }
        if (True == BoShouldDecrement)
        {
            /* Check whether warning should be hidden after specified time */
            if (SBW__stStatNCAP2018Flg.u16Timer > 0)
            {
                if (SBW__boSbwDisplayMaster != False
                    /* SBW warning on display */)
                {
                    SBW__stStatNCAP2018Flg.u16Timer--;
                    /* Decrease the timer */
                }
                if (SBW__stStatNCAP2018Flg.u16Timer == 0)
                {
                    for_all_seats(enSeat)
                    {
                        if (SBW__stStatNCAP2018Flg.enSeatStates[enSeat] == nenBlinking)
                        {
                            SBW__stStatNCAP2018Flg.enSeatStates[enSeat] = nenInactive;
                            /* Do not allow 0x200420 to show */
                            SBW__vReleaseWarning();
                            SBW__stStatSoundFlg.u32ActiveRsbw = SBW__nNoSoundWarn;
                        }
                    }
                    SBW__vReleaseWarning();
                }
            }
        }
        else
        {
            /* nothing to do */
        }
        /* Register a new warning */
        u32HilId = SBW__u32GetDemandedWarning(&boError);
        if (SBW__stStatNCAP2018Flg.boErrorStateOld != boError)
        {
            /* If error state was changed, then warning should be displayed again */
            SBW__stStatNCAP2018Flg.boErrorStateOld = boError;
            boEmitWarning = True;
        }
        SBW__vRsbwRegisterNCAP2018(u32HilId, boEmitWarning);
        /* EasyCASE - */
        /* Handle acoustic 200666/20072B */
        SBW__vHandleAcoustic();
    }
}

/** Reset Rear Seat Belt Warning **/
/* SBW__vResetRearSeatbeltWrn */
void SBW__vResetRearSeatbeltWrn(void)
{
    if (SBW__boKL15gReady)
    {
#ifdef SBW__HL

        if (SBW__boEeprom_RearSeatMat())
        {
            if (SBW__stWarnRequestRear.enNewWarnRequestBuzzer != nNoBuzzerWarning)
            {
                if ((SBW__boSoundSupress == False) && ((True == SBW__boEeprom_SeatBeltBuz) || (SBW__nNoSoundFront == SBW__u8Eeprom_SeatBeltBuzInactive)))
                {
                    if (False == WIM_boIsRegistered(SBW__stBuzzer[SBW__stWarnRequestRear.enNewWarnRequestBuzzer].enLogDevice))
                    {
                        WIM_vSetIntEvent(SBW__stBuzzer[SBW__stWarnRequestRear.enNewWarnRequestBuzzer].enLogDevice);
                    }
                }
            }
        }
        else
        {
            if (SBW__stStatSoundFlg.u32ActiveRsbw != SBW__nNoWarn)
            { /* Sound stop */
                WIM_vStopSound(SBW__stStatSoundFlg.u32ActiveRsbw);
                SBW__stStatSoundFlg.u32ActiveRsbw = SBW__nNoWarn;
                SBW__stStatNCAP2018Flg.u16SoundTimer = 0;
            }
        }

#else
        if (SBW__stStatSoundFlg.u32ActiveRsbw != SBW__nNoWarn)
        {/* Sound stop */
            WIM_vStopSound(SBW__stStatSoundFlg.u32ActiveRsbw);
            SBW__stStatSoundFlg.u32ActiveRsbw = SBW__nNoWarn;
            SBW__stStatNCAP2018Flg.u16SoundTimer = 0;
        }
#endif
    }
}

/** Release the rear seatbelt warnings**/
/* SBW__vManuQuitWarnRelease */
void SBW__vManuQuitWarnRelease(uint32 u32WarnNumber)
{
    /***************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local variables (auto and static)
    ****************************************************************************/
    switch (u32WarnNumber)
    {
    case SBW__nNoSoundWarn:
    case SBW__nSoundWarnNCAP2018:
    case SBW__nNoSoundBlinkingWarn:
        /* Release the warning using the ID given as parameter by WIM. */
        SBW__vReleaseWarning();
        break;
    default:
        break;
    }
}
/** Get the validity of the driver, codriver and middle passenger seatbelt **/
/* SBW__vGetBeltState */
void SBW__vGetBeltState(SBW__tunBeltState *unBeltState, bool *boBeltStateDriverValid)
{
    /***************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local variables (auto and static)
    ****************************************************************************/
    /* EasyCASE - */
    /***************************************************************************
    * FUNCTION CODE
    ****************************************************************************/
    /* EasyCASE - */
    SBW__tstSeatBeltState   stDriverBelt;
    SBW__tstPassengerState  stPassengerPresent;
    SBW__tstSeatBeltState   stPassengerSeatbelt;
    SBW__tstPassengerState stFrontPassengerMiddlePresent;
    SBW__tstSeatBeltState  stFrontPassengerMiddleSeatbelt;

    /* EasyCASE - */
    /***************************************************************************
    * FUNCTION CODE
    ****************************************************************************/
    /* EasyCASE - */
    *boBeltStateDriverValid = False;
    (*unBeltState).stBelt.biDriver = False;
    (*unBeltState).stBelt.biCoDriver = False;
    (*unBeltState).stBelt.biMidPassenger = False;
    /* EasyCASE - */
    IREXT_vDisableAndSave_Int();
    /* EasyCASE - */
    /* Read CAN signals */
    //CIO_vInBckl_Sw_D_Stat(&stDriverBelt);
    Com_ReceiveSignalGroup(Com_Grp_Bckl_Sw_Ft_Stat_Pr2);
    stDriverBelt.boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Bckl_Sw_Ft_Stat_Pr2) ? True : False);
    stDriverBelt.boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Bckl_Sw_Ft_Stat_Pr2) ? True : False);
    stDriverBelt.boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Bckl_Sw_Ft_Stat_Pr2) ? True : False);
    Com_ReceiveShadowSignal(Com_Bckl_Sw_D_Stat, &stDriverBelt.u8State);

    //CIO_vInOC_P_Fast_ORC(&stPassengerPresent);
    Com_ReceiveSignal(Com_OC_P_Fast_ORC, &stPassengerPresent.u8State);
    stPassengerPresent.boSo = (Com_GetRxSigStateOnFlag(Com_OC_P_Fast_ORC) ? True : False);
    stPassengerPresent.boTo = (Com_GetRxSigTimeoutFlag(Com_OC_P_Fast_ORC) ? True : False);
    stPassengerPresent.boFv = (Com_GetRxSigFirstValueFlag(Com_OC_P_Fast_ORC) ? True : False);

    //CIO_vInBckl_Sw_FP_Stat(&stPassengerSeatbelt);
    Com_ReceiveSignalGroup(Com_Grp_Bckl_Sw_Ft_Stat_Pr2);
    stPassengerSeatbelt.boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Bckl_Sw_Ft_Stat_Pr2) ? True : False);
    stPassengerSeatbelt.boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Bckl_Sw_Ft_Stat_Pr2) ? True : False);
    stPassengerSeatbelt.boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Bckl_Sw_Ft_Stat_Pr2) ? True : False);
    Com_ReceiveShadowSignal(Com_Bckl_Sw_FP_Stat, &stPassengerSeatbelt.u8State);

    //CIO_vInOC_P_Fast_ORC(&stFrontPassengerMiddlePresent);
    Com_ReceiveSignal(Com_OC_PM_Fast_ORC, &stFrontPassengerMiddlePresent.u8State);
    stFrontPassengerMiddlePresent.boSo = (Com_GetRxSigStateOnFlag(Com_OC_PM_Fast_ORC) ? True : False);
    stFrontPassengerMiddlePresent.boTo = (Com_GetRxSigTimeoutFlag(Com_OC_PM_Fast_ORC) ? True : False);
    stFrontPassengerMiddlePresent.boFv = (Com_GetRxSigFirstValueFlag(Com_OC_PM_Fast_ORC) ? True : False);

    //CIO_vInBckl_Sw_FP_Stat(&stFrontPassengerMiddleSeatbelt);
    Com_ReceiveSignalGroup(Com_Grp_Bckl_Sw_Ft_Stat_Pr2);
    stFrontPassengerMiddleSeatbelt.boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Bckl_Sw_Ft_Stat_Pr2) ? True : False);
    stFrontPassengerMiddleSeatbelt.boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Bckl_Sw_Ft_Stat_Pr2) ? True : False);
    stFrontPassengerMiddleSeatbelt.boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Bckl_Sw_Ft_Stat_Pr2) ? True : False);
    Com_ReceiveShadowSignal(Com_Bckl_Sw_FPM_Stat, &stFrontPassengerMiddleSeatbelt.u8State);

    /* EasyCASE - */
    IREXT_vRestore_Int();
    if ((stDriverBelt.boSo == True) /* We have state on */
        &&
        (stDriverBelt.boTo == False) /* and no timeout ocurred */
        &&
        (stDriverBelt.boFv == True) /* First values received */)
    {
        /********** CAN-Signale gueltig **********/
        if ((stDriverBelt.u8State == SBW_nenGSNichtGesteckt)
            ||
            (stDriverBelt.u8State == SBW_nenGSGesteckt))
        {
            /* no error value */
            *boBeltStateDriverValid = True;
        }
        if ((stDriverBelt.u8State == SBW_nenGSNichtGesteckt))
        {
            /* Driver seatbelt not fastened */
            (*unBeltState).stBelt.biDriver = True;
        }
    }
    if ((stPassengerPresent.boSo == True)
        &&
        (stPassengerPresent.boTo == False)
        &&
        (stPassengerPresent.boFv == True)
        &&
        (stPassengerSeatbelt.boSo == True)
        &&
        (stPassengerSeatbelt.boTo == False)
        &&
        (stPassengerSeatbelt.boFv == True))
    {
        /********** CAN-Signale gueltig **********/
        if ((stPassengerSeatbelt.u8State == SBW_nenGSNichtGesteckt)
            /* Passenger seatbelt not fastened */
            &&
            (stPassengerPresent.u8State == SBW_nenSBEOccupantPresent)
            /* and passenger present */)
        {
            /* Beifahrergurt nicht gesteckt */
            /* EasyCASE - */
            (*unBeltState).stBelt.biCoDriver = True;
        }
    }
    if ((stFrontPassengerMiddlePresent.boSo == True)
        &&
        (stFrontPassengerMiddlePresent.boTo == False)
        &&
        (stFrontPassengerMiddlePresent.boFv == True)
        &&
        (stFrontPassengerMiddleSeatbelt.boSo == True)
        &&
        (stFrontPassengerMiddleSeatbelt.boTo == False)
        &&
        (stFrontPassengerMiddleSeatbelt.boFv == True))
    {
        /********** CAN-Signale gueltig **********/
        if ((stFrontPassengerMiddleSeatbelt.u8State == SBW_nenGSNichtGesteckt)
            /* Passenger seatbelt not fastened */
            &&
            (stFrontPassengerMiddlePresent.u8State == SBW_nenSBEOccupantPresent)
            /* and passenger present */)
        {
            /* Beifahrergurt nicht gesteckt */
            /* EasyCASE - */
            (*unBeltState).stBelt.biMidPassenger = True;
        }
    }
}
/** Returns the status of the rear seats seatbelts **/
/* SBW__u16GetRearSeatBeltStatus */
uint16 SBW__u16GetRearSeatBeltStatus(void)
{
    uint16 u16SeatBeltState = 0;
    uint8 au8offsets[nenNumberOfSeats] = { SBW__nShiftToSeatRow2RightBitPos, SBW__nShiftToSeatRow2MiddleBitPos, SBW__nShiftToSeatRow2LeftBitPos, SBW__nShiftToSeatRow3RightBitPos, SBW__nShiftToSeatRow3LeftBitPos };
    enum enRearSeat enSeat;
    bool boErrorState = False;
    /* Workaround for buggy SBWMDL */
    for_all_seats(enSeat)
        if (SBW__stStatNCAP2018Flg.enSeatStates[enSeat] == nenError)
            boErrorState = True;

    for_all_seats(enSeat)
    {
        if (True == SBW__boSeatIsApplicable(enSeat))
        {
            switch (SBW__stStatNCAP2018Flg.enSeatStates[enSeat])
            {
            case nenFastened:
                u16SeatBeltState |= SBW__nRearSeatFastened << au8offsets[enSeat];
                break;
            case nenBlinking:
                if (!boErrorState)
                    u16SeatBeltState |= SBW__nRearSeatBlinking << au8offsets[enSeat];
                break;
            }
        }
        else
        {
            /*Nothing to do*/
        }
    }
    return u16SeatBeltState;
}

/* SBW__vGetSbwHILInfo */
void SBW__vGetSbwHILInfo(uint32 *pu32Value)
{
    enum enRearSeat enSeat;
    uint16 u16SeatBeltState = 0;
    uint32 u32SeatBeltRow = 0;
    uint8 au8offsets[nenNumberOfSeats] = { SBW__nShiftToSeatRow2RightBitPos, SBW__nShiftToSeatRow2MiddleBitPos, SBW__nShiftToSeatRow2LeftBitPos, SBW__nShiftToSeatRow3RightBitPos, SBW__nShiftToSeatRow3LeftBitPos };
    for_all_seats(enSeat)
    {
        if (True == SBW__boSeatIsApplicable(enSeat))
        {
            uint16 u16Offset = au8offsets[enSeat];
            enum enSeatMat enSeatPresent = SBW_nenSeatMatPresent;
#ifdef SBW__HL

            if (SBW__boEeprom_RearSeatMat())
            {
                enSeatPresent = SBW__stStatNCAP2018Flg.enSeatPresence[enSeat];
            }
#endif
            if (SBW_nenSeatMatPresent == enSeatPresent || SBW_nenSeatMatUnknown == enSeatPresent)
            {

                if (SBW__stStatNCAP2018Flg.enSeatStates[enSeat] == nenFastened)
                {
                    u16SeatBeltState |= SBW__nRearSeatFastenedMaskForHil << u16Offset;
                }
                else
                {
                    u16SeatBeltState |= SBW__nRearSeatNotFastenedMaskForHil << u16Offset;
                }
            }
            else
            {
                u16SeatBeltState |= SBW__nRearSeatNotFastenedMaskForHil << u16Offset;
            }
        }
        else
        {
            /*Nothing to do*/
        }
    }
    if ((SBW__nRear5Seats == SBW__u8Eeprom_RearSeatLayout)&&(SBW__u8Eeprom_VehLine() != SBW__nVehLineBR464))
    {
        /*Three rows*/
        u32SeatBeltRow |= SBW__nRearSeatNumberofRowsForHil << 22;
    }
    else
    {
        /*Two rows*/
        u32SeatBeltRow |= 0;

    }
    /* EasyCASE - */
    *pu32Value = u16SeatBeltState | u32SeatBeltRow;

}
/** Callback for display master warning **/
/* SBW__vDisplayChangeCallback */
void SBW__vDisplayChangeCallback(uint32 u32HilId)
{
    switch (u32HilId)
    {
    case SBW__nNoSoundWarn:
    case SBW__nSoundWarnNCAP2018:
    case SBW__nNoSoundBlinkingWarn:
        SBW__boSbwDisplayMaster = True;
        break;
    default:
        SBW__boSbwDisplayMaster = False;
    }
}
/** Handle the acoustic part of rear seatbelts **/
/*SBW__vHandleAcoustic*/
static void SBW__vHandleAcoustic(void)
{
    const uint16 u16SeriesLength = 80;
    const uint16 u16OnPhaseLength = 50;
    const uint16 u16ToneInterval = 5;

    if (SBW__boIsWarningBlinking(SBW__stStatSoundFlg.u32ActiveRsbw))
    {
        uint16 u16Step = SBW__stStatNCAP2018Flg.u16SoundTimer % u16SeriesLength;
        if ((u16Step < u16OnPhaseLength) && (SBW__stStatNCAP2018Flg.u16SoundTimer>0))
        {
            /* On-phase */
            if (u16Step % u16ToneInterval == 0)
            {
                /* Sound retrigger */
                WIM_vRetriggerSound(SBW__stStatSoundFlg.u32ActiveRsbw);
            }
        }
        else
        {
            /* Off-phase: do nothing */
        }
        SBW__stStatNCAP2018Flg.u16SoundTimer++;
    }
    else if (SBW__stStatSoundFlg.u32ActiveRsbw == SBW__nNoSoundWarn || SBW__stStatSoundFlg.u32ActiveRsbw == SBW__nNoWarn)
    {
        /* Sound stop */
        if (SBW__stStatNCAP2018Flg.u16SoundTimer == 0)
        {
            WIM_vStopSound(SBW__stStatSoundFlg.u32ActiveRsbw);
            SBW__stStatNCAP2018Flg.u16SoundTimer++;
        }
    }
}
/** Check if Acoustics is EEPROM enable **/
/* SBW__boAreAcousticsActive */
static bool SBW__boAreAcousticsActive(void)
{
    bool boAcousticsActive;
    if ((True == SBW__boEeprom_SeatBeltBuz) || (SBW__nNoSoundFront == SBW__u8Eeprom_SeatBeltBuzInactive))
    {
        /* Acoustics are not muted */
        boAcousticsActive = True;
    }
    else
    {
        /* Acoustics are muted */
        boAcousticsActive = False;
    }
    return boAcousticsActive;
}
/** Return the blinking warning **/
/* SBW__u32GetBlinkingWarning */
static uint32 SBW__u32GetBlinkingWarning(void)
{
    uint32 u32BlinkingWarn;
    if (False == SBW__boAreAcousticsActive())
    {
        u32BlinkingWarn = SBW__nNoSoundBlinkingWarn;
    }
    else
    {
        u32BlinkingWarn = SBW__nSoundWarnNCAP2018;
    }
    return u32BlinkingWarn;
}
/** Check if warning is blinking **/
/* SBW__boIsWarningBlinking */
static bool SBW__boIsWarningBlinking(uint32 u32HilId)
{
    bool boBlinkingWarn;
    if ((u32HilId == SBW__nSoundWarnNCAP2018) || (u32HilId == SBW__nNoSoundBlinkingWarn))
    {
        boBlinkingWarn = True;
    }
    else
    {
        boBlinkingWarn = False;
    }
    return boBlinkingWarn;
}

#ifdef SBW__HL

/** Check the warning state of Rear Seat Mat**/
/* SBW__boStateSeatsWarning */
static bool SBW__boStateSeatsWarning(void)
{
    enum enRearSeat enSeat;
    enum enRearSeatState enRearSeatState;

    bool boResult = True;
    for_all_seats(enSeat)
    {
        if (True == SBW__boSeatIsApplicable(enSeat) && ((SBW__stStatNCAP2018Flg.enSeatPresence[enSeat] == SBW_nenSeatMatPresent) || (SBW__stStatNCAP2018Flg.enSeatPresence[enSeat] == SBW_nenSeatMatUnknown)))
        {
            enRearSeatState = SBW__stStatNCAP2018Flg.enSeatStates[enSeat];

            boResult &= (enRearSeatState != nenWaiting && enRearSeatState != nenBlinking && enRearSeatState != nenInactive);
        }
    }
    return boResult;
}

/** Check the state of Rear Seat Mat**/
/* SBW__boAreAllFastenedRearMat */
static bool SBW__boAreAllFastenedRearMat(void)
{
    enum enRearSeat enSeat;
    enum enRearSeatState enRearSeatState;

    bool boResult = True;
    for_all_seats(enSeat)
    {
        if (True == SBW__boSeatIsApplicable(enSeat) && ((SBW__stStatNCAP2018Flg.enSeatPresence[enSeat] == SBW_nenSeatMatPresent) || (SBW__stStatNCAP2018Flg.enSeatPresence[enSeat] == SBW_nenSeatMatUnknown)))
        {
            enRearSeatState = SBW__stStatNCAP2018Flg.enSeatStates[enSeat];

            boResult &= (enRearSeatState != nenWaiting && enRearSeatState != nenBlinking);
        }
    }
    return boResult;
}

/** Get the state for each rear seat **/
/* SBW__vGetRearSeatState */
static void SBW__vGetRearSeatState(enum enRearSeatState * penRearSeatState, const SBW__tstSeatBeltState *pstSeatBeltStateMat, const SBW__tstSeatBeltState * pstSeatBeltState, bool boSpeedOverThreshold, enum enRearSeat enSeat)
{
    enum enRearSeatState enRearSeatState = *penRearSeatState;

    /* Check state of rear seat belt */
    if ((pstSeatBeltState->boSo == True) && (pstSeatBeltState->boTo == False) && (pstSeatBeltState->boFv == True) && (pstSeatBeltStateMat->boSo == True) && (pstSeatBeltStateMat->boTo == False) && (pstSeatBeltStateMat->boFv == True))
    {
        if ((pstSeatBeltState->u8State == SBW_nenGSGesteckt) && ((pstSeatBeltStateMat->u8State == SBW_nenSeatMatPresent) || (pstSeatBeltStateMat->u8State == SBW_nenSeatMatUnknown)))
        {
            TIMER_vClear(SBW__aenDebounceTimers[enSeat]);
            // Check seat state
            switch (enRearSeatState)
            {
            case nenFastened:
                break;
            case nenEmpty:
            case nenBlinking:
            case nenWaiting:
            case nenError:
            case nenInactive:
                enRearSeatState = nenFastened;
                break;
            }
        }
        else if ((pstSeatBeltState->u8State == SBW_nenGSNichtGesteckt) && (pstSeatBeltStateMat->u8State == SBW_nenSeatMatPresent))
        {
            TIMER_vClear(SBW__aenDebounceTimers[enSeat]);
            // Check seat state
            switch (enRearSeatState)
            {
            case nenEmpty:
            case nenError:
                /* fallthrough */
            case nenFastened:
                if (boSpeedOverThreshold)
                {
                    enRearSeatState = nenBlinking;
                }
                else
                {
                    enRearSeatState = nenWaiting;
                }
                break;
            case nenBlinking:
                if (SBW__boIsAcousticOver() == True)
                {
                    enRearSeatState = nenInactive;
                }
                if (CST_boGetStatus(CST_nenStatusVelStop) && (SBW__stWarnRequestRear.enNewWarnRequestBuzzer == nNoBuzzerWarning))
                {
                    enRearSeatState = nenWaiting;
                }
                break;
            case nenWaiting:
                break;
            case nenInactive:
                if (CST_boGetStatus(CST_nenStatusVelStop))
                {
                    enRearSeatState = nenWaiting;
                }
                break;
            }
        }
        else if ((pstSeatBeltState->u8State == SBW_nenGSNichtGesteckt) && (pstSeatBeltStateMat->u8State == SBW_nenSeatMatAbsent))
        {
            TIMER_vClear(SBW__aenDebounceTimers[enSeat]);
            enRearSeatState = nenEmpty;

        }
        else if ((pstSeatBeltState->u8State == SBW_nenGSNichtGesteckt) && (pstSeatBeltStateMat->u8State == SBW_nenSeatMatUnknown))
        {
            if ((TIMER_u32Read(SBW__aenDebounceTimers[enSeat]) == 0) && (enRearSeatState != nenError))
            {
                TIMER_vStart(SBW__aenDebounceTimers[enSeat], SBW__nDebounceTime);
            }
        }
        else
        {
            TIMER_vClear(SBW__aenDebounceTimers[enSeat]);
            if (enRearSeatState != nenError)
            {
                enRearSeatState = nenError;
            }
        }
        if ((enRearSeatState == nenWaiting) && boSpeedOverThreshold)
        {
            enRearSeatState = nenBlinking;
        }
    }
    else if ((pstSeatBeltState->boFv == True) || (pstSeatBeltStateMat->boFv == True))
    {
        enRearSeatState = nenError;
    }
    // Check if state was changed
    if (enRearSeatState != *penRearSeatState)
    {
        *penRearSeatState = enRearSeatState;
    }
}

/** check the presence for rear seat mat**/
/* SBW__vCheckRearPresence*/
static void SBW__vCheckRearPresence(const SBW__tstSeatBeltState *pstSeatBeltStateMat, enum enRearSeat enCurrentRearSeat)
{

    if ((pstSeatBeltStateMat->boSo == True) && (pstSeatBeltStateMat->boTo == False) && (pstSeatBeltStateMat->boFv == True))

    {
        if ((pstSeatBeltStateMat->u8State == SBW_nenSeatMatPresent))
        {

            SBW__stStatNCAP2018Flg.enSeatPresence[enCurrentRearSeat] = SBW_nenSeatMatPresent;
        }
        else if ((pstSeatBeltStateMat->u8State == SBW_nenSeatMatUnknown))
        {
            SBW__stStatNCAP2018Flg.enSeatPresence[enCurrentRearSeat] = SBW_nenSeatMatUnknown;
        }
        else
        {
            SBW__stStatNCAP2018Flg.enSeatPresence[enCurrentRearSeat] = SBW_nenSeatMatAbsent;
        }
    }
    else if (pstSeatBeltStateMat->boFv == True)
    {
        SBW__stStatNCAP2018Flg.enSeatPresence[enCurrentRearSeat] = SBW_nenSeatMatNotMonitored;
    }

}
/** Check door state in case of seatmat and returns true if reset should be done **/
/*SBW__vCheckRearDoorMat*/
static uint8 SBW__vCheckRearDoorMat(const SBW__tstDoorState * pstDoorState, bool * pboDoorWasOpen)
{
    uint8 u8ReturnValue = nenNotClosed;
    if ((pstDoorState->boSo == True) && (pstDoorState->boTo == False) && (pstDoorState->boFv == True))
    {
        if ((pstDoorState->u8State == SBW__nenDoorOpen) || (pstDoorState->u8State == SBW__nenDoorNotDef) || (pstDoorState->u8State == SBW__nenDoorSignalNotAvailable))
        {
            if (*pboDoorWasOpen == False)
            {
                *pboDoorWasOpen = True;
                u8ReturnValue |= nenOpenedRecently;
            }
            u8ReturnValue |= nenOpen;
        }
        else if (pstDoorState->u8State == SBW__nenDoorClosed)
        {
            u8ReturnValue &= ~nenNotClosed;
            if (*pboDoorWasOpen == True)
            {
                *pboDoorWasOpen = False;
                u8ReturnValue |= nenClosedRecently;
            }
        }
    }
    else if (pstDoorState->boTo == True)
    {
        u8ReturnValue |= nenOpen;
    }
    else
    {
        *pboDoorWasOpen = False;
    }
    return u8ReturnValue;
}
/** Rear seatbelts warning Mats **/
/*SBW__vRearSeatbeltWrnMat */
void SBW__vRearSeatbeltWrnMat(void)
{
    /***************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local variables (auto and static)
    ****************************************************************************/
    bool boSpeedOverThreshold = False;                 /* Speed value higher than SeatBelt_Threshold*/
    /* EasyCASE - */
    /* Local variables for rear seatbelt switches */
    SBW__tstSeatBeltState stSeatBeltStates[nenNumberOfSeats];
    SBW__tstSeatBeltState stSeatBeltStatesMats[nenNumberOfSeats];
    /* Local variables for rear doors state */
    SBW__tstDoorState stRearLeftDoor;
    SBW__tstDoorState stRearRightDoor;
    SBW__tstDoorState stRearTrunkDoor;
    enum enRearSeat enSeat;                        /* loop counter */
    uint8 u8ReturnValue = 0;
    bool boError = False;                          /* an error state was detected */
    /***************************************************************************
    * FUNCTION CODE
    ****************************************************************************/
    IREXT_vDisableAndSave_Int();
    /* Read the status of the rear seatbelt */

    //CIO_vInBckl_Sw_RL_Stat_SAM_R(&stSeatBeltStates[nenLeft]);
    Com_ReceiveSignalGroup(Com_Grp_Bckl_Sw_RL_State_SAM_R);
    stSeatBeltStates[nenLeft].boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Bckl_Sw_RL_State_SAM_R) ? True : False);
    stSeatBeltStates[nenLeft].boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Bckl_Sw_RL_State_SAM_R) ? True : False);
    stSeatBeltStates[nenLeft].boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Bckl_Sw_RL_State_SAM_R) ? True : False);
    Com_ReceiveShadowSignal(Com_Bckl_Sw_RL_Stat_SAM_R, &stSeatBeltStates[nenLeft].u8State);
    //CIO_vInSecondRowLeftPresenceState(&stSeatBeltStatesMats[nenLeft]);
    stSeatBeltStatesMats[nenLeft].boSo = (Com_GetRxSigStateOnFlag(Com_SecondRowLeftPresenceState) ? True : False);
    stSeatBeltStatesMats[nenLeft].boTo = (Com_GetRxSigTimeoutFlag(Com_SecondRowLeftPresenceState) ? True : False);
    stSeatBeltStatesMats[nenLeft].boFv = (Com_GetRxSigFirstValueFlag(Com_SecondRowLeftPresenceState) ? True : False);
    Com_ReceiveSignal(Com_SecondRowLeftPresenceState, &stSeatBeltStatesMats[nenLeft].u8State);
    SBW__vCheckRearPresence(stSeatBeltStatesMats + nenLeft, nenLeft);
    //CIO_vInBckl_Sw_RR_Stat_SAM_R(&stSeatBeltStates[nenRight]);
    Com_ReceiveSignalGroup(Com_Grp_Bckl_Sw_RR_State_SAM_R);
    stSeatBeltStates[nenRight].boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Bckl_Sw_RR_State_SAM_R) ? True : False);
    stSeatBeltStates[nenRight].boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Bckl_Sw_RR_State_SAM_R) ? True : False);
    stSeatBeltStates[nenRight].boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Bckl_Sw_RR_State_SAM_R) ? True : False);
    Com_ReceiveShadowSignal(Com_Bckl_Sw_RR_Stat_SAM_R, &stSeatBeltStates[nenRight].u8State);
    //CIO_vInSecondRowRightPresenceState(&stSeatBeltStatesMats[nenRight]);
    stSeatBeltStatesMats[nenRight].boSo = (Com_GetRxSigStateOnFlag(Com_SecondRowRightPresenceState) ? True : False);
    stSeatBeltStatesMats[nenRight].boTo = (Com_GetRxSigTimeoutFlag(Com_SecondRowRightPresenceState) ? True : False);
    stSeatBeltStatesMats[nenRight].boFv = (Com_GetRxSigFirstValueFlag(Com_SecondRowRightPresenceState) ? True : False);
    Com_ReceiveSignal(Com_SecondRowRightPresenceState, &stSeatBeltStatesMats[nenRight].u8State);
    SBW__vCheckRearPresence(stSeatBeltStatesMats + nenRight, nenRight);
    switch (SBW__u8Eeprom_RearSeatLayout)
    {
    case SBW__nRear2Seats:
    case SBW__nRear4Seats:
    case SBW__nRear3Seats:
        //CIO_vInBckl_Sw_RM_Stat_SAM_R(&stSeatBeltStates[nenMiddle]);
        Com_ReceiveSignalGroup(Com_Grp_Bckl_Sw_RM_State_SAM_R);
        stSeatBeltStates[nenMiddle].boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Bckl_Sw_RM_State_SAM_R) ? True : False);
        stSeatBeltStates[nenMiddle].boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Bckl_Sw_RM_State_SAM_R) ? True : False);
        stSeatBeltStates[nenMiddle].boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Bckl_Sw_RM_State_SAM_R) ? True : False);
        Com_ReceiveShadowSignal(Com_Bckl_Sw_RM_Stat_SAM_R, &stSeatBeltStates[nenMiddle].u8State);
        //CIO_vInSecondRowCenterPresenceState(&stSeatBeltStatesMats[nenMiddle]);
        stSeatBeltStatesMats[nenMiddle].boSo = (Com_GetRxSigStateOnFlag(Com_SecondRowCenterPresenceState) ? True : False);
        stSeatBeltStatesMats[nenMiddle].boTo = (Com_GetRxSigTimeoutFlag(Com_SecondRowCenterPresenceState) ? True : False);
        stSeatBeltStatesMats[nenMiddle].boFv = (Com_GetRxSigFirstValueFlag(Com_SecondRowCenterPresenceState) ? True : False);
        Com_ReceiveSignal(Com_SecondRowCenterPresenceState, &stSeatBeltStatesMats[nenMiddle].u8State);
        SBW__vCheckRearPresence(stSeatBeltStatesMats + nenMiddle, nenMiddle);
        break;
    case SBW__nRear5Seats:
        //CIO_vInBckl_Sw_RM_Stat_SAM_R(&stSeatBeltStates[nenMiddle]);
        Com_ReceiveSignalGroup(Com_Grp_Bckl_Sw_RM_State_SAM_R);
        stSeatBeltStates[nenMiddle].boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Bckl_Sw_RM_State_SAM_R) ? True : False);
        stSeatBeltStates[nenMiddle].boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Bckl_Sw_RM_State_SAM_R) ? True : False);
        stSeatBeltStates[nenMiddle].boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Bckl_Sw_RM_State_SAM_R) ? True : False);
        Com_ReceiveShadowSignal(Com_Bckl_Sw_RM_Stat_SAM_R, &stSeatBeltStates[nenMiddle].u8State);
        //CIO_vInSecondRowCenterPresenceState(&stSeatBeltStatesMats[nenMiddle]);
        stSeatBeltStatesMats[nenMiddle].boSo = (Com_GetRxSigStateOnFlag(Com_SecondRowCenterPresenceState) ? True : False);
        stSeatBeltStatesMats[nenMiddle].boTo = (Com_GetRxSigTimeoutFlag(Com_SecondRowCenterPresenceState) ? True : False);
        stSeatBeltStatesMats[nenMiddle].boFv = (Com_GetRxSigFirstValueFlag(Com_SecondRowCenterPresenceState) ? True : False);
        Com_ReceiveSignal(Com_SecondRowCenterPresenceState, &stSeatBeltStatesMats[nenMiddle].u8State);
        SBW__vCheckRearPresence(stSeatBeltStatesMats + nenMiddle, nenMiddle);
        //CIO_vInBckl_Sw_RL_Stat_SAM_R(&stSeatBeltStates[nen3RowLeft]);
        Com_ReceiveSignalGroup(Com_Grp_Bckl_Sw_3L_State_SAM_R);
        stSeatBeltStates[nen3RowLeft].boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Bckl_Sw_3L_State_SAM_R) ? True : False);
        stSeatBeltStates[nen3RowLeft].boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Bckl_Sw_3L_State_SAM_R) ? True : False);
        stSeatBeltStates[nen3RowLeft].boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Bckl_Sw_3L_State_SAM_R) ? True : False);
        Com_ReceiveShadowSignal(Com_Bckl_Sw_3L_Stat_SAM_R, &stSeatBeltStates[nen3RowLeft].u8State);
        //CIO_vInThirdRowLeftPresenceState(&stSeatBeltStatesMats[nen3RowLeft]);
        stSeatBeltStatesMats[nen3RowLeft].boSo = (Com_GetRxSigStateOnFlag(Com_ThirdRowLeftPresenceState) ? True : False);
        stSeatBeltStatesMats[nen3RowLeft].boTo = (Com_GetRxSigTimeoutFlag(Com_ThirdRowLeftPresenceState) ? True : False);
        stSeatBeltStatesMats[nen3RowLeft].boFv = (Com_GetRxSigFirstValueFlag(Com_ThirdRowLeftPresenceState) ? True : False);
        Com_ReceiveSignal(Com_ThirdRowLeftPresenceState, &stSeatBeltStatesMats[nen3RowLeft].u8State);
        SBW__vCheckRearPresence(stSeatBeltStatesMats + nen3RowLeft, nen3RowLeft);
        //CIO_vInBckl_Sw_RR_Stat_SAM_R(&stSeatBeltStates[nen3RowRight]);
        Com_ReceiveSignalGroup(Com_Grp_Bckl_Sw_3R_State_SAM_R);
        stSeatBeltStates[nen3RowRight].boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Bckl_Sw_3R_State_SAM_R) ? True : False);
        stSeatBeltStates[nen3RowRight].boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Bckl_Sw_3R_State_SAM_R) ? True : False);
        stSeatBeltStates[nen3RowRight].boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Bckl_Sw_3R_State_SAM_R) ? True : False);
        Com_ReceiveShadowSignal(Com_Bckl_Sw_3R_Stat_SAM_R, &stSeatBeltStates[nen3RowRight].u8State);
        //CIO_vInThirdRowRightPresenceState(&stSeatBeltStatesMats[nen3RowRight]);
        stSeatBeltStatesMats[nen3RowRight].boSo = (Com_GetRxSigStateOnFlag(Com_ThirdRowRightPresenceState) ? True : False);
        stSeatBeltStatesMats[nen3RowRight].boTo = (Com_GetRxSigTimeoutFlag(Com_ThirdRowRightPresenceState) ? True : False);
        stSeatBeltStatesMats[nen3RowRight].boFv = (Com_GetRxSigFirstValueFlag(Com_ThirdRowRightPresenceState) ? True : False);
        Com_ReceiveSignal(Com_ThirdRowRightPresenceState, &stSeatBeltStatesMats[nen3RowRight].u8State);
        SBW__vCheckRearPresence(stSeatBeltStatesMats + nen3RowRight, nen3RowRight);
        break;
    default:
        break;
    }
    IREXT_vRestore_Int();

    if (SBW__boKL15gReady)
    {
        for_all_seats(enSeat)
        {
            enOldSeatStates[enSeat] = SBW__stStatNCAP2018Flg.enSeatStates[enSeat];
        }
    }

    /* Check current speed for threshold */
    boSpeedOverThreshold = SBW__boIsSpeedOverThreshold();
    /* EasyCASE - */
    if (SBW__stStatNCAP2018Flg.boKl15SwitchedOn)
    {
        /* Reset all seatbelt states on KL15 reset */
        SBW__stStatNCAP2018Flg.boKl15SwitchedOn = False;

        if (SBW__boKL15gReady)
        {
            for_all_seats(enSeat)
            {
                SBW__stStatNCAP2018Flg.enSeatStates[enSeat] = nenEmpty;
            }
        }
    }

    if (SBW__boKL15gReady)
    {
        for_all_seats(enSeat)
        {
            if (SBW__boSeatIsApplicable(enSeat))
            {
                SBW__vGetRearSeatState(SBW__stStatNCAP2018Flg.enSeatStates + enSeat, stSeatBeltStatesMats + enSeat, stSeatBeltStates + enSeat, boSpeedOverThreshold, enSeat);
            }
        }
    }

    /* Check door states */
    /* 5-door car: rear doors are checked */
    /* Read the status of the back doors */
    //CIO_vInDrRLtch_RL_Stat(&stRearLeftDoor);
    Com_ReceiveSignalGroup(Com_Grp_Door_RL_Stat_Pr2);
    Com_ReceiveShadowSignal(Com_DrRLtch_RL_Stat, &stRearLeftDoor.u8State);
    stRearLeftDoor.boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Door_RL_Stat_Pr2) ? True : False);
    stRearLeftDoor.boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Door_RL_Stat_Pr2) ? True : False);
    stRearLeftDoor.boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Door_RL_Stat_Pr2) ? True : False);
    //CIO_vInDrRLtch_RR_Stat(&stRearRightDoor);
    Com_ReceiveSignalGroup(Com_Grp_Door_RR_Stat_Pr2);
    Com_ReceiveShadowSignal(Com_DrRLtch_RR_Stat, &stRearRightDoor.u8State);
    stRearRightDoor.boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_Door_RR_Stat_Pr2) ? True : False);
    stRearRightDoor.boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_Door_RR_Stat_Pr2) ? True : False);
    stRearRightDoor.boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_Door_RR_Stat_Pr2) ? True : False);
    //CIO_vInDL_RLtch_Stat(&stRearTrunkDoor);
    Com_ReceiveSignalGroup(Com_Grp_DL_Lk_Stat);
    Com_ReceiveShadowSignal(Com_DL_RLtch_Stat, &stRearTrunkDoor.u8State);
    stRearTrunkDoor.boSo = (Com_GetRxSigGrpStateOnFlag(Com_Grp_DL_Lk_Stat) ? True : False);
    stRearTrunkDoor.boTo = (Com_GetRxSigGrpTimeoutFlag(Com_Grp_DL_Lk_Stat) ? True : False);
    stRearTrunkDoor.boFv = (Com_GetRxSigGrpFirstValueFlag(Com_Grp_DL_Lk_Stat) ? True : False);

    u8ReturnValue |= SBW__vCheckRearDoorMat(&stRearLeftDoor, &SBW__stStatNCAP2018Flg.boRearDoorLeftWasOpen);
    u8ReturnValue |= SBW__vCheckRearDoorMat(&stRearRightDoor, &SBW__stStatNCAP2018Flg.boRearDoorRightWasOpen);
    u8ReturnValue |= SBW__vCheckRearDoorMat(&stRearTrunkDoor, &SBW__stStatNCAP2018Flg.boRearDoorTrunkWasOpen);
    SBW__stCanRear.unDoorRearOpen.stDoorRear.biLeft = SBW__vCheckRearDoorMat(&stRearLeftDoor, &SBW__stStatNCAP2018Flg.boRearDoorLeftWasOpen);
    SBW__stCanRear.unDoorRearOpen.stDoorRear.biRight = SBW__vCheckRearDoorMat(&stRearRightDoor, &SBW__stStatNCAP2018Flg.boRearDoorRightWasOpen);
    SBW__stCanRear.unDoorRearOpen.stDoorRear.biTrunk = SBW__vCheckRearDoorMat(&stRearTrunkDoor, &SBW__stStatNCAP2018Flg.boRearDoorTrunkWasOpen);

    if ((SBW__boKL15gReady) && (False == SBW__boStateSeatsWarning()) && (!CST_boGetStatus(CST_nenStatusVelStop) || ((u8ReturnValue & nenNotClosed) == 0)))
    {
        SBW__StatusIconRequest = 1;
        if (SBW__nSlackDisabled == SBW__boEeprom_RearSeatSlacks() && (False == boSBW_areSlackDisabled))
        {
            WIM_vDisableSlacks();
            boSBW_areSlackDisabled = True;
        }
    }
    else if (!(SBW__boKL15gReady) || (True == SBW__boStateSeatsWarning()) || (CST_boGetStatus(CST_nenStatusVelStop) && (u8ReturnValue & nenOpen) && (False == SBW__boSoundActivatedRear)))
    {
        SBW__StatusIconRequest = 0;
        if (SBW__nSlackDisabled == SBW__boEeprom_RearSeatSlacks() && (True == boSBW_areSlackDisabled))
        {
            WIM_vEnableSlacks();
            boSBW_areSlackDisabled = False;
        }
    }

    if (SBW__boKL15gReady)

    {
        for_all_seats(enSeat)
        {
            if (True == SBW__boSeatIsApplicable(enSeat))
            {
                if ((SBW_nenSeatMatPresent == stSeatBeltStatesMats[enSeat].u8State) || (SBW_nenSeatMatUnknown == stSeatBeltStatesMats[enSeat].u8State))
                {
                    switch (stSeatBeltStates[enSeat].u8State)
                    {
                    case SBW_nenGSGesteckt:
                        SBW__stStatNCAP2018Flg.enSeatStates[enSeat] = nenFastened;
                        break;
                    case SBW_nenGSNichtGesteckt:
                        break;
                    default:
                        SBW__stStatNCAP2018Flg.enSeatStates[enSeat] = nenEmpty;
                        break;
                    }
                }
                else
                {
                    SBW__stStatNCAP2018Flg.enSeatStates[enSeat] = nenEmpty;
                }

                if ((SBW__bEeprom_SeatBelt != SBW__nEeprom_SeatBeltNcapEce || (False == SBW__boEeprom_SeatBeltBuz && SBW__nNoSoundFront != SBW__u8Eeprom_SeatBeltBuzInactive)) && (SBW__stStatNCAP2018Flg.enSeatStates[enSeat] == nenBlinking))
                {
                    SBW__stStatNCAP2018Flg.enSeatStates[enSeat] = nenWaiting;
                }
            }
            else
            {
                // nothing to do
            }
        }

        if (CST_boGetStatus(CST_nenStatusVelStop))
        { /********** vehicle is stopped **********/
            if (u8ReturnValue & nenOpen)
            {
                /*** The door of the passenger who has not fastened his seatbelt is opened ***/
                /* Retriggers warning */
                SBW__vRetriggerWarnRearMat();
                /* Cancel alarm / initialize NCAP warning interval */
                SBW__vAbortWarnRearMat();
            }
            else
            {
                /********** Doors closed **********/
                if (SBW__stWarnRequestRear.enNewWarnRequestBuzzer == nBuzzerNcapLastPhase)
                {
                    /* Handle NCAP warning (finish phase 4) */
                    SBW__vHandleRearMatWarn();
                }
                else
                {
                    /* Retriggers warning */
                    SBW__vRetriggerWarnRearMat();
                    /* Warnings Process (current Buzzer still finish) */
                    SBW__vHandleRearMatWarn();
                }
            }
        }
        else
        {
            /* Warning Start */
            SBW__vHandleRearMatWarnStart();

            /* Process warnings */
            SBW__vHandleRearMatWarn();

        }
    }
    else
    {
        SBW__vAbortWarnRearMat();
        SBW__vRetriggerWarnRearMat();
    }

    SBW__vHandleRequestRearMat();
}
/* SBW__boSeatBeltWasUnfastened */
static bool SBW__boSeatBeltWasUnfastened(void)
{
    enum enRearSeat enSeat;
    bool returnValue = False;

    for_all_seats(enSeat)
    {
        if (enOldSeatStates[enSeat] == nenFastened)
        {
            switch (SBW__stStatNCAP2018Flg.enSeatStates[enSeat])
            {
            case nenWaiting:
            case nenBlinking:
            case nenInactive:
                returnValue = True;
                break;
            }
        }
        else if ((enOldSeatStates[enSeat] == nenWaiting) || (enOldSeatStates[enSeat] == nenEmpty) || (enOldSeatStates[enSeat] == nenError))
        {
            switch (SBW__stStatNCAP2018Flg.enSeatStates[enSeat])
            {
            case nenBlinking:
                returnValue = True;
                break;
            }
        }
    }
    return returnValue;
}


/*SBW__vAbortWarnRearMat*/
static void SBW__vAbortWarnRearMat(void)
{
    /* Cancel request. The actual request is handled by SBW__ HandleRequest   */
    SBW__stWarnRequestRear.enNewWarnRequestBuzzer = nNoBuzzerWarning;   /* Buzzer off */
    /* Initialize timer for NCAP warning intervals */
    SBW__stWarnRequestRear.boDisableBuzzer = False;
    SBW__stNcapWarnRear.wCounterStartTimeRear = 0;                          /* Warning sequence starts at the beginning  */
    SBW__stNcapWarnRear.wCounterWarnTimeRear = 0;                           /* Reset remaining warning time to 0         */
    SBW__stNcapWarnRear.wCounterPhaseRear = 0;                              /* Reset phase counter to 0                  */
    /*  Clear registered sound warnings */
    SBW__vSetPhase(nNoBuzzerWarning, True);                         /* Buzzer off          */
    SBW__vProcessAcoustics(False, True);
    SBW__boSoundActivatedRear = False;
}
/* SBW__vRetriggerWarnRearMat */
static void SBW__vRetriggerWarnRearMat(void)
{
    /* Reset remaining warning time to 0. Current interval is possibly finished */
    SBW__stNcapWarnRear.wCounterWarnTimeRear = 0;
    /* Reset the PreStart timer to 0 */
    SBW__stNcapWarnRear.wCounterPreStartTimeRear = 0;
    /* Assume all passengers are buckled up - warning can be restarted */
}
/* SBW__vHandleRearMatWarnStart */
static void SBW__vHandleRearMatWarnStart(void)
{

    bool boSpeedOverThreshold = SBW__boIsSpeedOverThreshold();

    /***************************************************************************
    * FUNCTION CODE
    ****************************************************************************/
    if (SBW__bEeprom_SeatBelt == SBW__nEeprom_SeatBeltNcapEce)
    {
        if (SBW__boSeatBeltWasUnfastened() == True)
        {
            SBW__vSyncFrontRearAcoustic(True);
            /*********** Strapping detected ***********/
            /* EasyCASE - */
            /* Gets the car speed within *u16CarSpeed */
            if ((SBW__stWarnRequestRear.enNewWarnRequestBuzzer != nNoBuzzerWarning)
                ||
                (boSpeedOverThreshold))
            {
                /*********** Warning sequence active or V >= V threshold ***********/
                /* EasyCASE ( 1139
                Start Warning */
                if (/* If no warning sequence runs - initialize the beginning */
                    SBW__stWarnRequestRear.enNewWarnRequestBuzzer == nNoBuzzerWarning)
                {

                    /* Warning initialization -  at NCAP ECE: time since time since "the vehicle driver is wearing a seat belt" note */
                    SBW__stNcapWarnRear.wCounterStartTimeRear = SBW__stNcapWarnRear.wCounterPreStartTimeRear;

                }
                /* Set new warning time */
                SBW__stNcapWarnRear.wCounterWarnTimeRear = SBW__wBuzzerPhaseNCAPTime;
                /* Warning starts at V >= V threshold always from the beginning (to belt during the trip) */
                SBW__stNcapWarnRear.wCounterPreStartTimeRear = 0;
            }
            else
            {
                /*********** V < V threshold and seatbelt detected ***********/
                if ((SBW__stNcapWarnRear.wCounterPreStartTimeRear != SBW__wCounterFinish))
                {
                    /* Time since driver belt is strapped in count */
                    SBW__stNcapWarnRear.wCounterPreStartTimeRear++;
                }
            }
        }
        else
        {
            /*********** V < V-Threshold ***********/
            /* EasyCASE - */
            /* Initialize time since driver belt is strapped in */
            SBW__stNcapWarnRear.wCounterPreStartTimeRear = 0;
        }
    }
}

/*SBW__vHandleRearMatWarn */
static void SBW__vHandleRearMatWarn(void)
{
    /***************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local variables (auto and static)
    ****************************************************************************/
    /* EasyCASE - */

    tenWarnPhaseBuzzer enWarnPhaseCountRear;       /* Search current phase */
    tenWarnPhaseBuzzer enStartPhaseRear = nBuzzerNcapPhase3; /* nBuzzerNcapPhase3 in case of NCAP2018 */

    /* EasyCASE - */
    /***************************************************************************
    * FUNCTION CODE
    ****************************************************************************/
    if (SBW__bEeprom_SeatBelt == SBW__nEeprom_SeatBeltNcapEce)
    {
        if (False == SBW__boAreAllFastenedRearMat())
        {
            /*********** not wearing a seat belt ***********/
            if (/* Warning period has not yet expired */
                (SBW__stNcapWarnRear.wCounterWarnTimeRear != 0)
                ||
                /* Warning sequence is still running */
                (SBW__stWarnRequestRear.enNewWarnRequestBuzzer != nNoBuzzerWarning))
            {
                /*Process phase switching */
                if (SBW__stNcapWarnRear.wCounterPhaseRear == 0)
                {
                    /************ Phase switch ************/
                    if (/* Off phase was active */
                        SBW__stWarnRequestRear.boDisableBuzzer
                        ||
                        /* Off stage, the length 0 */
                        (SBW__stBuzzer[SBW__stWarnRequestRear.enNewWarnRequestBuzzer].wOffTime == 0)
                        ||
                        /* Warning not started yet */
                        (SBW__stWarnRequestRear.enNewWarnRequestBuzzer == nNoBuzzerWarning))
                    {
                        /* EasyCASE ( 993
                        Select Buzzer - New NCAP phase search */
                        /* first phase can be started without any condition */
                        SBW__stWarnRequestRear.enNewWarnRequestBuzzer = enStartPhaseRear;
                        for (enWarnPhaseCountRear = (tenWarnPhaseBuzzer)(enStartPhaseRear + 1); enWarnPhaseCountRear <= nBuzzerNcapLastPhase; enWarnPhaseCountRear++)
                        {
                            /* Check whether another phase must already be started */
                            if (SBW__stBuzzer[enWarnPhaseCountRear].wStartTimeSh <
                                (SBW__stNcapWarnRear.wCounterStartTimeRear + SBW__stBuzzer[enWarnPhaseCountRear - 1].wOnTime + SBW__stBuzzer[enWarnPhaseCountRear - 1].wOffTime))

                            {
                                /* take over new phase */
                                SBW__stWarnRequestRear.enNewWarnRequestBuzzer = enWarnPhaseCountRear;
                            }
                        }
                        if (SBW__stNcapWarnRear.wCounterStartTimeRear < SBW__stBuzzer[SBW__stWarnRequestRear.enNewWarnRequestBuzzer].wStartTimeSh
                            &&
                            SBW__stWarnRequestRear.enNewWarnRequestBuzzer != enStartPhaseRear)

                        {
                            /* Start was brought forward - catch up time */
                            /* EasyCASE - */
                            SBW__stNcapWarnRear.wCounterStartTimeRear = SBW__stBuzzer[SBW__stWarnRequestRear.enNewWarnRequestBuzzer].wStartTimeSh;


                        }
                        /* EasyCASE ) */
                        /* EasyCASE ( 1213
                        Start of the on period */
                        if (SBW__stBuzzer[SBW__stWarnRequestRear.enNewWarnRequestBuzzer].wOnTime != 0)
                        {
                            /* On-Phase started */
                            /* EasyCASE - */
                            /* Turn on buzzer */
                            SBW__stWarnRequestRear.boDisableBuzzer = False;
                            /* Set duration */
                            SBW__stNcapWarnRear.wCounterPhaseRear = SBW__stBuzzer[SBW__stWarnRequestRear.enNewWarnRequestBuzzer].wOnTime;
                        }
                        else
                        {
                            /* On-stage, the length 0 - configuration error! */
                            /* EasyCASE - */
                            /* Buzzer suppress - always off-stage */
                            SBW__stWarnRequestRear.boDisableBuzzer = True;
                            /* Check Next round again - time = 0 */
                            SBW__stNcapWarnRear.wCounterPhaseRear = 0;
                        }
                        /* EasyCASE ) */
                    }
                    else
                    {
                        /* EasyCASE ( 1214
                        Start of the off phase */
                        /* Turn off Buzzer */
                        SBW__stWarnRequestRear.boDisableBuzzer = True;
                        /* Set duration */
                        SBW__stNcapWarnRear.wCounterPhaseRear = SBW__stBuzzer[SBW__stWarnRequestRear.enNewWarnRequestBuzzer].wOffTime;
                        /* EasyCASE ) */
                    }
                }

                /* Activate phase 4 acoustic */

                if (nBuzzerNcapPhase4 == SBW__enGetPhase(True))
                {
                    /* NCAP Phase 4  */
                    if ((SBW__stWarnRequestRear.boDisableBuzzer == False) && (SBW__stNcapWarnRear.wCounterPhaseRear % SBW__u8NcapPhase4OnSubphasePeriod == 0))
                    {
                        /* Quit WIM's sound warning */
                        if (SBW__boSoundSupress == False)
                        {
                            SBW__vSetPhase(nBuzzerNcapPhase4, True);
                            SBW__vProcessAcoustics(True, True);
                        }

                    }
                }
                else
                {
                    /* all other phases of NCAP warning */
                }

                /* End NCAP ECE? */
                if (/* Warning time has elapsed */
                    (SBW__stNcapWarnRear.wCounterWarnTimeRear == 0)
                    &&
                    /* Off-Phase... */
                    SBW__stWarnRequestRear.boDisableBuzzer
                    &&
                    /* ... just started */
                    (SBW__stNcapWarnRear.wCounterPhaseRear == SBW__stBuzzer[SBW__stWarnRequestRear.enNewWarnRequestBuzzer].wOffTime))
                {
                    /* NOTE: if the phase 4 has no off-stage, it runs forever! */
                    SBW__stWarnRequestRear.enNewWarnRequestBuzzer = nNoBuzzerWarning;

                }
                /* EasyCASE ) */

                if ((CST_boGetStatus(CST_nenStatusVelStop))
                    &&
                    (SBW__stWarnRequestRear.enNewWarnRequestBuzzer != nBuzzerNcapLastPhase))
                {
                    /********** car is not moving and Phase 4 is not active **********/
                    /* EasyCASE - */
                    /* stop warning */
                    SBW__stWarnRequestRear.enNewWarnRequestBuzzer = nNoBuzzerWarning;
                    /* EasyCASE - */
                    /* retrigger warning */
                    SBW__vRetriggerWarnRearMat();

                    if (SBW__stCanRear.unDoorRearOpen.bAllRear != 0)
                    {
                        /********** Door open **********/
                        /* EasyCASE - */
                        /* Cancel alarm / initialize NCAP warning interval */
                        SBW__vAbortWarnRearMat();
                    }
                }
                /* EasyCASE ) */
                /* EasyCASE ( 1228
                Start and count more warning time */
                /* Warning time count down (only in the last phase!) */
                if ((SBW__stWarnRequestRear.enNewWarnRequestBuzzer == nBuzzerNcapLastPhase)
                    &&
                    (SBW__stNcapWarnRear.wCounterWarnTimeRear != 0))
                {
                    SBW__stNcapWarnRear.wCounterWarnTimeRear--;
                }
                /* Count start time high */
                if (SBW__stNcapWarnRear.wCounterStartTimeRear != SBW__wCounterFinish)
                {
                    SBW__stNcapWarnRear.wCounterStartTimeRear++;
                }
                /* Phase time count down */
                if (SBW__stNcapWarnRear.wCounterPhaseRear != 0)
                {
                    SBW__stNcapWarnRear.wCounterPhaseRear--;

                }
                /* EasyCASE ) */
            }
            if (SBW__stWarnRequestRear.enNewWarnRequestBuzzer == nNoBuzzerWarning)
            {
                /*********** Warning sequence closed ***********/
                /* EasyCASE - */
                /* Cancel alarm / initialize NCAP warning interval */
                SBW__vAbortWarnRearMat();

            }
            else
            {

            }
        }
        else
        {
            /*********** all seatbelts fastned ***********/
            /* EasyCASE - */
            /* Cancel alarm / initialize NCAP warning interval */
            SBW__vAbortWarnRearMat();
        }
    }
}
/* SBW__vHandleRequestRearMat */
static void SBW__vHandleRequestRearMat(void)
{
    /***************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local variables (auto and static)
    ****************************************************************************/
    /* EasyCASE - */
    /***************************************************************************
    * FUNCTION CODE
    ****************************************************************************/
    /* EasyCASE ( 789
    Process Buzzer Request */
    if (SBW__bEeprom_SeatBelt == SBW__nEeprom_SeatBeltNcapEce)
    {
        if ((SBW__enGetPhase(True) != SBW__stWarnRequestRear.enNewWarnRequestBuzzer) || SBW__stWarnRequestRear.boDisableBuzzer)
        {
            if (SBW__stWarnRequestRear.boDisableBuzzer)
            {
                /* no buzzer request */
                SBW__vSetPhase(nNoBuzzerWarning, True);
            }
            else
            {
                SBW__vSetPhase(SBW__stWarnRequestRear.enNewWarnRequestBuzzer, True);
                /* On-Phase - ggf. new Buzzer requests are allowed */
                if (SBW__stWarnRequestRear.enNewWarnRequestBuzzer != nNoBuzzerWarning)
                {
                    if (SBW__boSoundSupress == False)
                    {
                        /* Register new Buzzers Request */

                        SBW__boSoundActivatedRear = True;
                        SBW__vProcessAcoustics(True, True);
                    }
                }
                else
                {
                    /*do nothing*/
                }
            }
        }
    }
}
/* SBW__boIsAcousticOver */
static bool SBW__boIsAcousticOver(void)
{
    return ((SBW__stWarnRequestRear.enNewWarnRequestBuzzer == nBuzzerNcapLastPhase)
        && (SBW__stNcapWarnRear.wCounterWarnTimeRear == 0)
        && (SBW__stNcapWarnRear.wCounterPhaseRear == 0));
}
/** Returns the status of the rear seats seatbelts mats **/
/* SBW__u16GetRearSeatBeltMatsStatus */
uint16 SBW__u16GetRearSeatBeltMatsStatus(void)
{
    uint16 u16SeatBeltMatsState = (SBW__u8Eeprom_RearSeatLayout == SBW__nRear5Seats ? SBW__nRear5Seats : SBW__nRear3Seats) | (SBW__StatusIconRequest << 15);
    uint8 au8offsets[nenNumberOfSeats] = { SBW__nShiftToSeatMatsRow2RightBitPos, SBW__nShiftToSeatMatsRow2MiddleBitPos, SBW__nShiftToSeatMatsRow2LeftBitPos, SBW__nShiftToSeatMatsRow3RightBitPos, SBW__nShiftToSeatMatsRow3LeftBitPos };
    enum enRearSeat enSeat;

    for_all_seats(enSeat)
    {
        if (True == SBW__boSeatIsApplicable(enSeat))
        {
            switch (SBW__stStatNCAP2018Flg.enSeatStates[enSeat])
            {
            case nenFastened:
                u16SeatBeltMatsState |= SBW__nRearSeatFastenedStat << au8offsets[enSeat];
                break;
            case nenWaiting:
            case nenInactive:
                u16SeatBeltMatsState |= SBW__nRearSeatUnFastenedStat << au8offsets[enSeat];
                break;
            case nenBlinking:
                u16SeatBeltMatsState |= SBW__nRearSeatBlinkingStat << au8offsets[enSeat];
                break;
            }
        }
        else
        {
            /*Nothing to do*/
        }
    }

    return u16SeatBeltMatsState;
}

/* callback when timer is finish */
/* SBW__vDebouceTimerCallback */
void SBW__vDebouceTimerCallback(enum enRearSeat enSeat)
{
    TIMER_vClear(SBW__aenDebounceTimers[enSeat]);
    SBW__stStatNCAP2018Flg.enSeatStates[enSeat] = nenError;
}

#endif

/** Event handling **/
/* SBW__vEventHandler */
void SBW__vEventHandler(EVHD_tenReceiveEvent enEvent)
{
    uint8 u8IconBlinkState = SBW__nSbwIconBlinkOff;
    static uint8 u8OldIconBlinkStateValue = SBW__nSbwIconBlinkOff;
    static bool boBlinkRequest = False;

    switch (enEvent)
    {
#ifdef SBW__HL
    case SBW__Icon_Blink_Event:
        /* Icon blinking state has changed */
        DPOOL_enGetPoolData(DPOOL_nDataSTAT_u8SbwAnyIconBlinking, &u8IconBlinkState);
        /* Icon is blinking */
        if (u8IconBlinkState != SBW__nSbwIconBlinkOff)
        {
            /* If the timer has already been started by the lamp blink request
            * and after that the icon was also requested - do not retrigger the timer
            */
            if (u8OldIconBlinkStateValue != SBW__nSbwIconAndLampBlinkOn)
            {
                /* If there is an icon blink request or an icon and lamp blink request
                * - switch ON the icon by putting a request on dpool and start blinking timer
                */
                boBlinkRequest = True;
                DPOOL_enSetPoolData(DPOOL_nDataSBW_boIconState, &boBlinkRequest);
                TIMER_vStart(TIMER_nSBW_IconBlinkTimer, SBW__en250msTimerCounts);
            }
        }
        /* Icon is not blinking */
        else
        {
            /* Switch OFF the icon by by putting a request on dpool and clear the blinking timer */
            boBlinkRequest = False;
            DPOOL_enSetPoolData(DPOOL_nDataSBW_boIconState, &boBlinkRequest);
            TIMER_vClear(TIMER_nSBW_IconBlinkTimer);
        }
        /* Save the previous value of the icon blink state */
        if (u8OldIconBlinkStateValue != u8IconBlinkState)
        {
            u8OldIconBlinkStateValue = u8IconBlinkState;
        }
        break;

    case SBW__Icon_Blink_Timer:
        /* Switch between icon states: if ON turn OFF / if OFF turn ON */
        if (boBlinkRequest == True)
        {
            boBlinkRequest = False;
        }
        else
        {
            boBlinkRequest = True;
        }
        /* Switch ON or OFF the icon by putting a request on dpool and retrigger the blinking timer */
        DPOOL_enSetPoolData(DPOOL_nDataSBW_boIconState, &boBlinkRequest);
        TIMER_vStart(TIMER_nSBW_IconBlinkTimer, SBW__en250msTimerCounts);
        break;
    case EV_TIM_SBW_DebounceTimer_RL_SBW__vEventHandler:
        SBW__vDebouceTimerCallback(nenLeft);
        break;
    case EV_TIM_SBW_DebounceTimer_RR_SBW__vEventHandler:
        SBW__vDebouceTimerCallback(nenRight);
        break;
    case EV_TIM_SBW_DebounceTimer_RM_SBW__vEventHandler:
        SBW__vDebouceTimerCallback(nenMiddle);
        break;
    case EV_TIM_SBW_DebounceTimer_3RL_SBW__vEventHandler:
        SBW__vDebouceTimerCallback(nen3RowLeft);
        break;
    case EV_TIM_SBW_DebounceTimer_3RR_SBW__vEventHandler:
        SBW__vDebouceTimerCallback(nen3RowRight);
        break;

    default:
        break;
#endif
    }
}

void SBW__vRearHandleKL15ReadyDelay()
{    
    if (SBW__boKL15gReadyStopChecking)
    {
        return;
    }

    /* KL15g is active */
    if (CST_boGetStatus(CST_nenStatusKl15g) == True)
    {
        /* if RSIT is greater than 0, start the time counter per 100ms */
        if (SBW__u8RearSeatBeltInitTimeMs > 0)
        {
            SBW__u16RsbwDelayCounterMs += SBW__u16RsbwCyclicIncStepMs;

            /* RSIT has elapsed */
            if (SBW__u16RsbwDelayCounterMs >= SBW__u8RearSeatBeltInitTimeMs)
            {
                SBW__vUpdateRsbwKL15gReadyState(True, True, True);
            }
            else /* RSIT hasn't elapsed yet */
            {
                SBW__vUpdateRsbwKL15gReadyState(False, False, False);
            }
        }
        else /* RSIT is equal to 0 */
        {
            SBW__vUpdateRsbwKL15gReadyState(True, True, False);
        }
    }
    else if (CST_boGetStatus(CST_nenStatusKl15g) == False) /* KL15g is inactive */
    {
        SBW__vUpdateRsbwKL15gReadyState(False, True, True);
    }
}

static void SBW__vUpdateRsbwKL15gReadyState(const bool boKl15GReady, const bool boStopChecking, const bool boResetDelayCounter)
{
    SBW__boKL15gReady = boKl15GReady;
    SBW__boKL15gReadyStopChecking = boStopChecking;
    if (boResetDelayCounter)
    {
        SBW__u16RsbwDelayCounterMs = 0;
    }
}

/* EasyCASE ( 171
   EOF */
/***************************************************************************
* EOF: sbwwc2.c
****************************************************************************/
/* EasyCASE ) */
/* EasyCASE ) */
