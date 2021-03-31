/* EasyCASE V6.5 02/05/2014 12:14:17 */
/* EasyCASE O
If=vertical
LevelNumbers=no
LineNumbers=yes
Colors=8675151,9600103,12582912,8404992,0,0,0,16777215,8388736,13300724,33023,15457455,0,0,0,0,0,8454016,12632256,255,65280,255,255,16711935
ScreenFont=Courier New,Standard,100,4,-14,0,400,0,0,0,0,0,0,3,2,1,49,96,96
PrinterFont=Courier New,,80,4,-66,0,400,0,0,0,0,0,0,3,2,1,49,600,600
LastLevelId=1430 */
/* EasyCASE ( 66
   SBW_C1.C */
/* EasyCASE ( 1299
   FILE HEADER */
/***************************************************************************
*================= Copyright by SiemensVDO Automotive AG ===================
****************************************************************************
* Title        : SBW - Seatbelt Warning
*
* Description  : The SBW module is integrated across all model series.
*                       The SBW module handles only the acoustic and optical
*                       warnings according to the Euro NCAP reglementations.
*
* Environment  : FJ-16 und FJ-32
*
* Responsible  : Joachim Pieper, Siemens VDO Automotive AG
*
* Guidelines   : SMK
*
* Template name: SWMODxC1.C, Revision 1.0
*
* CASE-Tool    : EasyCASE(C++), Version 6.32
*
* Revision List: (Will be filled by PVCS)
* Archive: $Log: SBWxC1.C  $
* Archive: Revision 1.8 2014/12/16 10:53:45CET Urs-Hadadea-EXT, Andrei (uidj9689)
* Archive: MR 44626 Implementation: SBW: Changes in seatbeltWarning regarding the reduced cycle time after reactivation - ÄLP14345
* Archive: Revision 1.7 2014/12/10 16:23:58CET Urs-Hadadea-EXT, Andrei (uidj9689)
* Archive: MR 44626 SBW, implementation : SBW: Changes in seatbeltWarning regarding the reduced cycle time after reactivation - ÄLP14345
* Archive: Revision 1.6 2014/03/25 12:05:30CET Olenici-EXT, Alexandru (uidw5408)
* Archive: Updated after MR39407.
* Archive: Revision 1.5 2014/02/05 11:14:17CET Olenici-EXT, Alexandru (uidw5408)
* Archive: Updated after MR38043 and MR37822
* Archive: Revision 1.4 2013/11/11 17:57:06CET Lacko-EXT, Jan (uidu0305)
* Archive: Update according to MRs 36256, 36257, 36729.
* Archive: Revision 1.3 2013/10/31 16:07:52CET Lacko-EXT, Jan (uidu0305)
* Archive: Update according to MR36550.
* Archive: Revision 1.2 2013/08/29 10:37:35CEST Lacko-EXT, Jan (uidu0305)
* Archive: Update according to MR34954.
* Archive: Revision 1.1 2012/10/15 14:41:30CEST Lacko Jan (uidu0305) (uidu0305)
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/sbw/core/project.pj
*
*    Rev 1.16   Oct 15 2012 14:42:36   Jan.Lacko-EXT
* Update according to MRs 29999, 30000, 30001.
*
*    Rev 1.15   Sep 24 2012 18:26:24   Jan.Lacko-EXT
* Update according to MRs 29738, 29739, 29740.
*
*    Rev 1.14   Sep 05 2012 20:36:08   Jan.Lacko-EXT
* DC MR 27127 (update)
*
*    Rev 1.13   Aug 02 2012 19:15:44   Jan.Cavojsky-EXT
* DC MR 27127
*
*    Rev 1.12   May 31 2012 15:28:26   Jan.Cavojsky-EXT
* DC MR 25510
*
*    Rev 1.11   May 16 2012 12:34:38   Jan.Cavojsky-EXT
* DC MR 25586 (rearseatbelt sound output fix)
*
*    Rev 1.10   May 04 2012 22:35:20   Jan.Cavojsky-EXT
* DC MR 25586
*
*    Rev 1.9   Apr 20 2012 17:53:10   Jan.Cavojsky-EXT
* DC MR 25586
*
*    Rev 1.8   Mar 06 2012 17:30:18   Jan.Cavojsky-EXT
* DC MR 24511
*
*    Rev 1.7   Feb 17 2012 20:30:46   Jan.Cavojsky-EXT
* DC MR 24512
*
*    Rev 1.6   Jul 22 2011 14:44:08   Jan.Cavojsky-EXT
* Update after MRs 22355, 22334
*
*    Rev 1.5   Apr 26 2011 17:58:48   Nicolae.Gavrila
* DC MR 21991: BR222: SBW corrections
*
*    Rev 1.4   Apr 14 2011 18:10:32   Nicolae.Gavrila
* DC MR 21685: BR222 SBW: counting 30sec only when Warning in display -LP2440
*
*    Rev 1.3   Mar 18 2011 16:15:54   Nicolae.Gavrila
* DC MRs 21660, 21666, 21724
*
*    Rev 1.2   Dec 10 2010 14:04:40   Nicolae.Gavrila
* DC MR 21009: AC-E003: Diagnostic-Service connections handled by DLIB and SBW
*
*    Rev 1.1   Sep 17 2010 17:49:46   Nicolae.Gavrila
* DC MR 20908: E002/AC, Startup HIL
*
*    Rev 1.0   Aug 27 2010 16:37:40   Nicolae.Gavrila
* Initial revision.
*
*    Rev 1.20   Apr 08 2009 17:16:22   Nicolae.Gavrila
* DC MR 19729: W204EL: rear seatbelt warning follow up MR
*
*    Rev 1.19   Oct 10 2008 17:33:20   Nicolae.Gavrila
* DC MR 18453 Change of warning layout
*
*    Rev 1.18   Aug 22 2008 07:50:40   Radu.Teaha
* DC MR 18904, 18905, 18907
*
*    Rev 1.17   Feb 11 2008 17:32:06   Nicusor.Bordinc
* DC MR 17428 Correction
*
*    Rev 1.16   Jan 18 2008 14:48:04   Nicusor.Bordinc
* DC MR17428 Update of NCAP warning 3nd
*
*    Rev 1.15   Jan 18 2008 14:30:34   Nicusor.Bordinc
* DC MR 17428 Update of NCAP warning 2nd
*
*    Rev 1.14   Jan 16 2008 08:30:08   Nicusor.Bordinc
* DC MR 17428 Update of NCAP warning
*
*    Rev 1.13   Apr 11 2007 10:47:06   Radu.Teaha
* DC MR 15791
*
*    Rev 1.12   Dec 06 2006 11:43:58   Radu.Teaha
* MR 15538
*
*    Rev 1.11   Nov 09 2006 12:40:30   Radu.Teaha
* DC MR 15184, 15185, 15186, 15335, 15381, 15382
*
*    Rev 1.10   Apr 15 2006 15:12:52   Radu.Teaha
* MR 14230, 14231
*
*    Rev 1.9   Feb 07 2006 09:30:52   Radu.Teaha
* MRs 13724,13729
*
*    Rev 1.8   Jan 27 2006 08:32:38   Radu.Teaha
* MR12847, 12848
*
*    Rev 1.7   Dec 23 2005 07:45:08   Radu.Teaha
* MRs 13092,13094
*
*    Rev 1.6   Oct 05 2005 13:19:48   Radu.Teaha
* MR 11494,11495,12040,12041,12286,12287,12288,12289,12337,12338
*
*    Rev 1.5   Jul 20 2005 13:27:06   Daniel.Ciocea
* MR11756-second measure
*
*    Rev 1.4   Jul 11 2005 16:55:42   Daniel.Ciocea
* MR11757,MR11756
*
*    Rev 1.3   May 06 2005 14:01:56   Daniel.Ciocea
* MR11522-Update NCAP Algorithm
*
*    Rev 1.2   May 06 2005 13:30:24   Daniel.Ciocea
* MR11524-Update NCAP Algorithm
*
*    Rev 1.1   May 05 2005 08:55:32   Daniel.Ciocea
* MR11653-Seatbeltwarnig Rearseat
*
*    Rev 1.0   Feb 17 2005 14:25:34   Daniel.Ciocea
* Initial revision.
*
*
****************************************************************************/

/***************************************************************************
* HEADER-FILES (Only those that are needed in this file)
****************************************************************************/
/* System-headerfiles */
#include  <cdef.h>                      /* General definitions and types   */

/* Foreign headerfiles */
#include  "CST_C1.H"                    /* Car-State                       */
#include  "wim_c1.h"                    /* Warning manager                 */
#include  "irext_c1.h"                  /* Interrupt handler               */
#include  "eed_c1.h"
#include  "dpool_c1.h"

/* Own headerfiles */
#include  "sbw_c1.h"                    /* Export interface (Own interface)*/
/* Indirect: Export configuration  */
#include  "sbw_ci.h"                    /* Import interface and local cfg. */
#include  "sbw_c2.h"                    /* Import CAN-Data                 */
#include "SBW__AcousticPlayer.h"

#include "com.h"
/* EasyCASE ) */
/* EasyCASE ( 121
   DEFINITIONS */
/***************************************************************************
* GLOBAL DEFINITIONS
*
* In this section define
* - all global ROM-constants of your module
* - all global variables of your module
****************************************************************************/
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
/* EasyCASE - */
/*
*
* Description: End of timer
*
* Values     : 0xFFFF
*/
/* EasyCASE - */
/* Workaround for synchronous start of the seat belt warning lamp test */

static bool             SBW__boSoundActivated = False;
extern bool             SBW__boSoundActivatedRear;
/* EasyCASE - */
/* Workaround for synchronous start of the seat belt warning lamp test */

bool            SBW__boSoundSupress = False;
/* EasyCASE - */
/* Workaround for synchronous start of the seat belt warning lamp test */

static bool            SBW__boFirstCheckAfterInitAcitve15 = False;
/* EasyCASE - */
/* Marker for EEPROM configuration */

static byte            SBW__bEeprom_SeatBeltConfig;       /* EEPROM Configuration */
static byte            SBW__bCounterDelay = 0;            /*Counts for delay between Normal warning and NCAP_USA warning*/
/* EasyCASE ( 2
   Marker for CAN signals */
/* EasyCASE C */
static struct
{
    SBW__tunDoorOpen     unDoorOpen;                /* Door status*/
    SBW__tunBeltState    unBeltState;               /* Belt status*/
    bool                 boDriverBeltStateValid;    /* Driver Belt Valid State Information*/
} SBW__stCan;
/* EasyCASE E */
/* EasyCASE ) */
/* EasyCASE ( 3
   Legal status seatbelt warning */
/* EasyCASE C */

SBW__tstNcapWarn SBW__stNcapWarn;
SBW__tstWarnRequest SBW__stWarnRequest;

static struct
{
    word        wCounterWarn;             /* Seat belt warning counter */
} SBW__stNormalWarn;

#define SBW__nLampOff         (0)
#define SBW__nLampStaticOn    (1)
#define SBW__nLampBlinking    (2)
#define SBW__nLampTest        (3)
#define SBW__nLegalWarnPeriod (9)


static uint8 SBW__u8LampStatus;
static uint8 SBW__u8LegalWarnCounter = SBW__nLegalWarnPeriod;


/* EasyCASE - */
/******************************************************************************
* FILE LOCAL FUNCTION PROTOTYPES
*
* In this section declare
* - all tasks
* - all file local function prototypes needed for your module (static)
******************************************************************************/
/* EasyCASE ( 592
   SBW__vAbortWarn */
/***************************************************************************
* Interface Description:
*
* Implementation       : -
*
* Return Value         : -
*
* Author               : Joachim Pieper
*
****************************************************************************/

static void SBW__vAbortWarn(void);
/* EasyCASE ) */
/* EasyCASE ( 737
   SBW__vRetriggerNcapWarn */
/***************************************************************************
* Interface Description:
*
* Implementation       : -
*
* Return Value         : -
*
* Author               : Joachim Pieper
*
****************************************************************************/

static void SBW__vRetriggerNcapWarn(void);
/* EasyCASE ) */
/* EasyCASE ( 944
   SBW__vRetriggerNormalWarn */
/***************************************************************************
* Interface Description:
*
* Implementation       : -
*
* Return Value         : -
*
* Author               : Joachim Pieper
*
****************************************************************************/

static void SBW__vRetriggerNormalWarn(void);
/* EasyCASE ) */
/* EasyCASE ( 656
   SBW__vHandleNcapWarnStart */
/***************************************************************************
* Interface Description:
*
* Implementation       : -
*
* Return Value         : -
*
* Author               : Joachim Pieper
*
****************************************************************************/

static void SBW__vHandleNcapWarnStart(void);
/* EasyCASE ) */
/* EasyCASE ( 739
   SBW__vHandleNcapWarn */
/***************************************************************************
* Interface Description:
*
* Implementation       : -
*
* Return Value         : -
*
* Author               : Joachim Pieper
*
****************************************************************************/

static void SBW__vHandleNcapWarn(void);
/* EasyCASE ) */
/* EasyCASE ( 760
   SBW__vHandleRequest */
/***************************************************************************
* Interface Description: Processes the delay for drivers or
*                        Passenger seat during the trip
*
* Implementation       : -
*
* Return Value         : -
*
* Author               : Joachim Pieper
*
****************************************************************************/

static void SBW__vHandleRequest(void);
/* EasyCASE ) */

#if defined(SBW__CFG_CanLampState) && (SBW__CFG_CanLampState == On)
/* EasyCASE ( 1450
   SBW__vSendLampState */
/***************************************************************************
* Interface Description: Send the warning lamp state on CAN
*
*
* Implementation       : The function checks the LampTest flag from TETAC and
*                        sends on CAN the state of the lamp depending on the
*                        internal state and the LampTest flag.
*
* Return Value         : void
*
* Author               : Alexandru Olenici-EXT
*
****************************************************************************/

static void SBW__vSendLampState(void);
/* EasyCASE ) */
#endif
/* EasyCASE ( 238
   FILE LOCAL FUNCTIONS */
/* EasyCASE ( 1393
   SBW__vSetDpoolData */
/* EasyCASE F */
/* EasyCASE ) */
void SBW__vSetDpoolData(void)
{
    DPOOL_txuint16 u16DpoolData = 0;
    /* EasyCASE - */
    //* bit 0: left seat is fastened
    //* bit 1 : left seat is blinking
    //* bit 2 : middle seat is fastened
    //* bit 3 : middle seat is blinking
    //* bit 4 : right seat is fastened
    //* bit 5 : right seat is blinking
    //* bit 6 :  3rd row left seat is fastened
    //* bit 7 : 3rd row left seat is blinking
    //* bit 8 : 3rd row right seat is fastened
    //* bit 9 : 3rd row right seat is blinking
    //* bits 10 - 13 : reserved
    //* bits 14 - 15 : used for front SBW(like in the past)

    DPOOL_txuint16 u16DpoolDataMats = 0;
    //* bit 0-1: number of seats
    //* bit 2: left seat is fastened
    //* bit 3 : left seat is blinking
    //* bit 4 : middle seat is fastened
    //* bit 5 : middle seat is blinking
    //* bit 6 : right seat is fastened
    //* bit 7 : right seat is blinking
    //* bit 8 : 3rd row left seat is fastened
    //* bit 9 : 3rd row left seat is blinking
    //* bit 10 : 3rd row right seat is fastened
    //* bit 11 : 3rd row right seat is blinking
    //* bits 12 - 14 : reserved
    //* bit 15 : use for Status_Icon_Request

#ifdef SBW__HL

    if (SBW__boEeprom_RearSeatMat())
    {
        u16DpoolDataMats = SBW__u16GetRearSeatBeltMatsStatus();
        DPOOL_enSetPoolData_DPOOL_nDataSBW_u16ModelDataMats(&u16DpoolDataMats);
        u16DpoolData = (SBW__u8LampStatus << 14) | SBW__u16GetRearSeatBeltStatus();
        DPOOL_enSetPoolData_DPOOL_nDataSBW_u16ModelData(&u16DpoolData);
    }
    else
    {
        u16DpoolData = (SBW__u8LampStatus << 14) | SBW__u16GetRearSeatBeltStatus();
        DPOOL_enSetPoolData_DPOOL_nDataSBW_u16ModelData(&u16DpoolData);
    }
#endif
#ifdef SBW__LL
    u16DpoolData = (SBW__u8LampStatus << 14) | SBW__u16GetRearSeatBeltStatus();
    DPOOL_enSetPoolData_DPOOL_nDataSBW_u16ModelData(&u16DpoolData);
#endif

}

/* EasyCASE ( 673
   SBW__vAbortWarn */
/* EasyCASE F */
static void SBW__vAbortWarn(void)
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

    /* Cancel request. The actual request is handled by SBW__ HandleRequest   */
    SBW__stWarnRequest.enNewWarnRequestLamp = nNoLampWarning;       /* Lamp off            */
    SBW__stWarnRequest.enNewWarnRequestBuzzer = nNoBuzzerWarning;   /* Buzzer off          */
    SBW__stWarnRequest.boDisableBuzzer = False;                     /* Buzzer not disabled */
    /* Initialize timer for NCAP warning intervals */
    SBW__stNcapWarn.wCounterStartTime = 0;                          /* Warning sequence starts at the beginning  */
    SBW__stNcapWarn.wCounterWarnTime = 0;                           /* Reset remaining warning time to 0         */
    SBW__stNcapWarn.wCounterPhase = 0;                              /* Reset phase counter to 0                  */
    /*  Clear registered sound warnings */
    SBW__vProcessAcoustics(False, False);
    /* If An ECE NCAP warning was active next warnings will be in short phases */
    if (SBW__bEeprom_SeatBeltConfig == SBW__nEeprom_SeatBeltNcapEce)
    {
        /* Shorter duration for Phases 1-3 */
        /* Use the short 3rd phase as 1st phase in NCAP2018 */
        SBW__stWarnRequest.boShortPhase = True;
    }


#ifdef QAC_Analysis
#pragma PRQA_MESSAGES_OFF 3201
#endif /* This statement is unreachable. */
    else
    {
        /* Normal phases */
    }
#ifdef QAC_Analysis
    /* re-activate QA C Warning(s) */
#pragma PRQA_MESSAGES_ON 3201
#endif /* QAC_Analysis */



    /* Normal phases */

}
/* EasyCASE ) */
/* EasyCASE ( 630
   SBW__vRetriggerNcapWarn */
/* EasyCASE F */
static void SBW__vRetriggerNcapWarn(void)
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
    /* Reset remaining warning time to 0. Current interval is possibly finished */
    SBW__stNcapWarn.wCounterWarnTime = 0;
    /* EasyCASE - */
    /* Reset the PreStart timer to 0 */
    SBW__stNcapWarn.wCounterPreStartTime = 0;
    /* EasyCASE - */
    /* Assume all passengers are buckled up - warning can be restarted */
    SBW__stNcapWarn.unOldBeltState.bAll = 0;
}
/* EasyCASE ) */
/* EasyCASE ( 948
   SBW__vRetriggerNormalWarn */
/* EasyCASE F */
static void SBW__vRetriggerNormalWarn(void)
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
    /* Initialize legal Seat Belt Warning */
    SBW__stNormalWarn.wCounterWarn = 0;
    /* EasyCASE - */
    /*Counter for delay between Normal warning and NCAP SUA warning */
    SBW__bCounterDelay = 0;
}
/* EasyCASE ) */
/* EasyCASE ( 839
   SBW__vHandleNcapWarnStart */
/* EasyCASE F */
static void SBW__vHandleNcapWarnStart(void)
{
    /***************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local variables (auto and static)
    ****************************************************************************/
    /* EasyCASE - */
    uint16 u16CarSpeed = 0;
    /* EasyCASE - */
    /***************************************************************************
    * FUNCTION CODE
    ****************************************************************************/
    if (/* Is someone wearing a seat belt? */
        (SBW__stCan.unBeltState.bAll & ~SBW__stNcapWarn.unOldBeltState.bAll) != 0)
    {
        SBW__vSyncFrontRearAcoustic(False);
        /*********** Strapping detected ***********/
        /* EasyCASE - */
        SBW__vGetVelocity(&u16CarSpeed, SBW_nUnitKm);
        /* Gets the car speed within *u16CarSpeed */
        if ((SBW__stWarnRequest.enNewWarnRequestBuzzer != nNoBuzzerWarning)
            ||
            ((u16CarSpeed >= (uint16)SBW__nEepromSpeedThreshold) && !(SBW__boCarStands)))
        {
            /*********** Warning sequence active or V >= V threshold ***********/
            /* EasyCASE ( 1139
               Start Warning */
            if (/* If no warning sequence runs - initialize the beginning */
                SBW__stWarnRequest.enNewWarnRequestBuzzer == nNoBuzzerWarning)
            {
                if (SBW__bEeprom_SeatBeltConfig == SBW__nEeprom_SeatBeltNcapEce)
                {
                    /* Warning initialization -  at NCAP ECE: time since time since "the vehicle driver is wearing a seat belt" note */
                    SBW__stNcapWarn.wCounterStartTime = SBW__stNcapWarn.wCounterPreStartTime;
                }
                else
                {
                    /* Warning Initialization - at NCAP USA: always from the beginning*/
                    SBW__stNcapWarn.wCounterStartTime = 0;
                }
            }
            /* Set new warning time */
            SBW__stNcapWarn.wCounterWarnTime = SBW__wBuzzerPhaseNCAPTime;
            /* EasyCASE ) */
            /* Store last seat belt check */
            SBW__stNcapWarn.unOldBeltState.bAll = SBW__stCan.unBeltState.bAll;
            /* EasyCASE - */
            /* Warning starts at V >= V threshold always from the beginning (to belt during the trip) */
            SBW__stNcapWarn.wCounterPreStartTime = 0;
        }
        else
        {
            /*********** V < V threshold and seatbelt detected ***********/
            if ((SBW__stNcapWarn.wCounterPreStartTime != SBW__wCounterFinish))
            {
                /* Time since driver belt is strapped in count */
                SBW__stNcapWarn.wCounterPreStartTime++;
            }
        }
    }
    else
    {
        /*********** V < V-Threshold ***********/
        /* EasyCASE - */
        /* Initialize time since driver belt is strapped in */
        SBW__stNcapWarn.wCounterPreStartTime = 0;
    }
    /* Store old seatbelt status to detect changes */
    /* EasyCASE - */
    SBW__stNcapWarn.unOldBeltState.bAll = SBW__stCan.unBeltState.bAll & SBW__stNcapWarn.unOldBeltState.bAll;
}
/* EasyCASE ) */
/* EasyCASE ( 725
   SBW__vHandleNcapWarn */
/* EasyCASE F */
static void SBW__vHandleNcapWarn(void)
{
    /***************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local variables (auto and static)
    ****************************************************************************/

    tenWarnPhaseBuzzer enWarnPhaseCount;       /* Search current phase */
    tenWarnPhaseBuzzer enStartPhase = nBuzzerNcapPhase1; /* nBuzzerNcapPhase3 in case of NCAP2018 */
    /* EasyCASE - */
    /***************************************************************************
    * FUNCTION CODE
    ****************************************************************************/
    if (SBW__bEeprom_SeatBeltConfig == SBW__nEeprom_SeatBeltNcapEce)
    {
        enStartPhase = nBuzzerNcapPhase3;
    }
    else
    {
        enStartPhase = nBuzzerNcapPhase1;
    }
    if (SBW__stCan.unBeltState.bAll != 0)
    {
        /*********** not wearing a seat belt ***********/
        if (/* Warning period has not yet expired */
            (SBW__stNcapWarn.wCounterWarnTime != 0)
            ||
            /* Warning sequence is still running */
            (SBW__stWarnRequest.enNewWarnRequestBuzzer != nNoBuzzerWarning))
        {
            /* EasyCASE ( 729
               Process phase switching */
            if (SBW__stNcapWarn.wCounterPhase == 0)
            {
                /************ Phase switch ************/
                if (/* Off phase was active */
                    SBW__stWarnRequest.boDisableBuzzer
                    ||
                    /* Off stage, the length 0 */
                    (SBW__stBuzzer[SBW__stWarnRequest.enNewWarnRequestBuzzer].wOffTime == 0)
                    ||
                    /* Warning not started yet */
                    (SBW__stWarnRequest.enNewWarnRequestBuzzer == nNoBuzzerWarning))
                {
                    /* EasyCASE ( 993
                       Select Buzzer - New NCAP phase search */
                    /* first phase can be started without any condition */
                    SBW__stWarnRequest.enNewWarnRequestBuzzer = enStartPhase;
                    for (enWarnPhaseCount = (tenWarnPhaseBuzzer)(enStartPhase + 1); enWarnPhaseCount <= nBuzzerNcapLastPhase; enWarnPhaseCount++)
                    {
                        /* Check whether another phase must already be started */
                        if ((SBW__stWarnRequest.boShortPhase ? SBW__stBuzzer[enWarnPhaseCount].wStartTimeSh : SBW__stBuzzer[enWarnPhaseCount].wStartTime) <
                            (SBW__stNcapWarn.wCounterStartTime + SBW__stBuzzer[enWarnPhaseCount - 1].wOnTime + SBW__stBuzzer[enWarnPhaseCount - 1].wOffTime))
                        {
                            /* take over new phase */
                            SBW__stWarnRequest.enNewWarnRequestBuzzer = enWarnPhaseCount;
                        }
                    }
                    if ((SBW__stNcapWarn.wCounterStartTime < (SBW__stWarnRequest.boShortPhase ? SBW__stBuzzer[SBW__stWarnRequest.enNewWarnRequestBuzzer].wStartTimeSh :
                        SBW__stBuzzer[SBW__stWarnRequest.enNewWarnRequestBuzzer].wStartTime))
                        &&
                        SBW__stWarnRequest.enNewWarnRequestBuzzer != enStartPhase)
                    {
                        /* Start was brought forward - catch up time */
                        /* EasyCASE - */
                        SBW__stNcapWarn.wCounterStartTime = (SBW__stWarnRequest.boShortPhase ? SBW__stBuzzer[SBW__stWarnRequest.enNewWarnRequestBuzzer].wStartTimeSh :
                            SBW__stBuzzer[SBW__stWarnRequest.enNewWarnRequestBuzzer].wStartTime);

                    }
                    /* EasyCASE ) */
                    /* EasyCASE ( 1213
                       Start of the on period */
                    if (SBW__stBuzzer[SBW__stWarnRequest.enNewWarnRequestBuzzer].wOnTime != 0)
                    {
                        /* On-Phase started */
                        /* EasyCASE - */
                        /* Turn on buzzer */
                        SBW__stWarnRequest.boDisableBuzzer = False;
                        /* Set duration */
                        SBW__stNcapWarn.wCounterPhase = SBW__stBuzzer[SBW__stWarnRequest.enNewWarnRequestBuzzer].wOnTime;
                    }
                    else
                    {
                        /* On-stage, the length 0 - configuration error! */
                        /* EasyCASE - */
                        /* Buzzer suppress - always off-stage */
                        SBW__stWarnRequest.boDisableBuzzer = True;
                        /* Check Next round again - time = 0 */
                        SBW__stNcapWarn.wCounterPhase = 0;
                    }
                    /* EasyCASE ) */
                }
                else
                {
                    /* EasyCASE ( 1214
                       Start of the off phase */
                    /* Turn off Buzzer */
                    SBW__stWarnRequest.boDisableBuzzer = True;
                    /* Set duration */
                    SBW__stNcapWarn.wCounterPhase = SBW__stBuzzer[SBW__stWarnRequest.enNewWarnRequestBuzzer].wOffTime;
                    /* EasyCASE ) */
                }
            }

            /* Activate phase 4 acoustic */

            if (nBuzzerNcapPhase4 == SBW__enGetPhase(False))
            {
                /* NCAP Phase 4  */
                if ((SBW__stWarnRequest.boDisableBuzzer == False) && (SBW__stNcapWarn.wCounterPhase % SBW__u8NcapPhase4OnSubphasePeriod == 0))
                {
                    /* Quit WIM's sound warning */
                    if (SBW__boSoundSupress == False)
                    {
                        SBW__vSetPhase(nBuzzerNcapPhase4, False);
                        SBW__vProcessAcoustics(True, False);
                    }
                }
            }
            else
            {
                /* all other phases of NCAP warning */

            }
            /* EasyCASE ) */
            /* EasyCASE ( 1236
               Check the warning stop sequence */
            if (SBW__bEeprom_SeatBeltConfig == SBW__nEeprom_SeatBeltNcapAdvanced)
            {
                /* EasyCASE ( 1243
                   End NCAP USA? */
                if (SBW__stWarnRequest.enNewWarnRequestBuzzer == nBuzzerNcapLastPhase)
                {
                    SBW__stWarnRequest.enNewWarnRequestBuzzer = nNoBuzzerWarning;
                }
                /* EasyCASE ) */
            }
            else
            {
                /* EasyCASE ( 1244
                   End NCAP ECE? */
                if (/* Warning time has elapsed */
                    (SBW__stNcapWarn.wCounterWarnTime == 0)
                    &&
                    /* Off-Phase... */
                    SBW__stWarnRequest.boDisableBuzzer
                    &&
                    /* ... just started */
                    (SBW__stNcapWarn.wCounterPhase == SBW__stBuzzer[SBW__stWarnRequest.enNewWarnRequestBuzzer].wOffTime))
                {
                    /* NOTE: if the phase 4 has no off-stage, it runs forever! */

                    SBW__stWarnRequest.enNewWarnRequestBuzzer = nNoBuzzerWarning;
                }
                /* EasyCASE ) */
            }
            if ((CST_boGetStatus(CST_nenStatusVelStop))
                &&
                (SBW__stWarnRequest.enNewWarnRequestBuzzer != nBuzzerNcapLastPhase))
            {
                /********** car is not moving and Phase 4 is not active **********/
                /* EasyCASE - */
                /* stop warning */
                SBW__stWarnRequest.enNewWarnRequestBuzzer = nNoBuzzerWarning;
                /* EasyCASE - */
                /* retrigger warning */
                SBW__vRetriggerNcapWarn();
                if (SBW__stCan.unDoorOpen.bAll != 0)
                {
                    /********** Door open **********/
                    /* EasyCASE - */
                    /* Cancel alarm / initialize NCAP warning interval */
                    SBW__vAbortWarn();
                }
            }
            /* EasyCASE ) */
            /* EasyCASE ( 1228
               Start and count more warning time */
            /* Warning time count down (only in the last phase!) */
            if ((SBW__stWarnRequest.enNewWarnRequestBuzzer == nBuzzerNcapLastPhase)
                &&
                (SBW__stNcapWarn.wCounterWarnTime != 0))
            {
                SBW__stNcapWarn.wCounterWarnTime--;
            }
            /* Count start time high */
            if (SBW__stNcapWarn.wCounterStartTime != SBW__wCounterFinish)
            {
                SBW__stNcapWarn.wCounterStartTime++;
            }
            /* Phase time count down */
            if (SBW__stNcapWarn.wCounterPhase != 0)
            {
                SBW__stNcapWarn.wCounterPhase--;

            }
            /* EasyCASE ) */
        }
        if (SBW__stWarnRequest.enNewWarnRequestBuzzer == nNoBuzzerWarning)
        {
            /*********** Warning sequence closed ***********/
            /* EasyCASE - */
            /* Cancel alarm / initialize NCAP warning interval */
            SBW__vAbortWarn();
            if ((SBW__stCan.unDoorOpen.bAll != 0) &&
                CST_boGetStatus(CST_nenStatusVelStop))
            {
                /********** Door open and car stopped **********/
                /* EasyCASE - */
                /* switch Lamp off */
                SBW__stWarnRequest.enNewWarnRequestLamp = nNoLampWarning;
            }
            else
            {
                /* switch lamp on static */
                SBW__stWarnRequest.enNewWarnRequestLamp = nLampStatic;
            }
        }
        else
        {
            /*********** Warning sequence runs ***********/
            /* EasyCASE - */
            /* Control lamp flashing */
            SBW__stWarnRequest.enNewWarnRequestLamp = nLampFlash;
        }
    }
    else
    {
        /*********** all seatbelts fastned ***********/
        /* EasyCASE - */
        /* Cancel alarm / initialize NCAP warning interval */
        SBW__vAbortWarn();
    }
}
/* EasyCASE ) */
/* EasyCASE ( 754
   SBW__vHandleRequest */
/* EasyCASE F */
static void SBW__vHandleRequest(void)
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
    if (/* aktuelle Phase an-/abgemelden */
        (SBW__enGetPhase(False) != SBW__stWarnRequest.enNewWarnRequestBuzzer)
        ||
        /* In Off-Phase immer abmelden */
        SBW__stWarnRequest.boDisableBuzzer)
    {
        if (SBW__enGetPhase(False) != nNoBuzzerWarning)
        {
            /* Check out old Buzzer-Request */
            /* EasyCASE - */
            /* WIM_vRelIntEvent (SBW__stBuzzer[SBW__stWarnRequest.enAktWarnRequestBuzzer].enLogDevice); */
        }
        if (SBW__stWarnRequest.boDisableBuzzer)
        {
            /* Off-Phase - no new Buzzers request */
            /* EasyCASE - */
            /* no buzzer-active request */
            SBW__vSetPhase(nNoBuzzerWarning, False);
        }
        else
        {
            /* Save current Buzzer Request */
            SBW__vSetPhase(SBW__stWarnRequest.enNewWarnRequestBuzzer, False);
            /* On-Phase - ggf. new Buzzer requests are allowed */
            if (SBW__stWarnRequest.enNewWarnRequestBuzzer != nNoBuzzerWarning)
            {
                /* Register new Buzzers Request */
                if (SBW__boSoundSupress == False)
                {
                    /* Register new Buzzers Request */
                    /* EasyCASE - */
                    SBW__boSoundActivated = True;
                    SBW__vProcessAcoustics(True, False);
                }
                else
                {
                    /*do nothing*/
                }
            }
            else
            {
                /*do nothing*/
            }

        }
    }
    /* EasyCASE ) */
    /* EasyCASE ( 790
       Process lamps Request */
    if (SBW__stWarnRequest.enAktWarnRequestLamp != SBW__stWarnRequest.enNewWarnRequestLamp)
    {
        if (SBW__stWarnRequest.enAktWarnRequestLamp != nNoLampWarning)
        {
            /* Check out old lamps request */
            /* EasyCASE - */
            SBW__u8LampStatus = SBW__nLampOff;
            /* EasyCASE - */
            /*SAM_RelRequest(SBW__stLamp[SBW__stWarnRequest.enAktWarnRequestLamp].enLogDevice,
                           True);*/
        }
        if (SBW__stWarnRequest.enNewWarnRequestLamp != nNoLampWarning)
        {
            /* Register new lamps request */
            if ((SBW__stWarnRequest.enNewWarnRequestLamp == nLampFlash)
                &&
                ((SBW__nEeprom_SeatBeltNcapEce == SBW__bEeprom_SeatBeltConfig) || (SBW__nEeprom_SeatBeltNcapAdvanced == SBW__bEeprom_SeatBeltConfig))
                &&
                ((True == SBW__boEeprom_SeatBeltBuz) || (SBW__nNoSoundRear == SBW__u8Eeprom_SeatBeltBuzInactive)))
            {
                SBW__u8LampStatus = SBW__nLampBlinking;
            }
            else
            {
                SBW__u8LampStatus = SBW__nLampStaticOn;
            }
            /*SAM_SetRequest( SBW__stLamp[SBW__stWarnRequest.enNewWarnRequestLamp].enLogDevice,
                            SBW__stLamp[SBW__stWarnRequest.enNewWarnRequestLamp].wFrequency,
                            (SBW__stLamp[SBW__stWarnRequest.enNewWarnRequestLamp].wFrequency != SFG_Freq8StaticHi));*/
        }
        /* Remember lamp current request */
        SBW__stWarnRequest.enAktWarnRequestLamp = SBW__stWarnRequest.enNewWarnRequestLamp;
    }
    /* EasyCASE ) */
}
/* EasyCASE ) */
#if defined(SBW__CFG_CanLampState) && (SBW__CFG_CanLampState == On)
/* EasyCASE ( 1431
   SBW__vSendLampState */
/* EasyCASE F */
static void SBW__vSendLampState(void)
{
    /***************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local variables (auto and static)
    ****************************************************************************/
    bool boLampTest = False;
    bool boLmpData = False;
    uint8 u8LampState = SBW__nLampOff;
    /* EasyCASE - */
    /***************************************************************************
    * FUNCTION CODE
    ****************************************************************************/
    /* EasyCASE - */
    DPOOL_enGetPoolData(DPOOL_nDataTETAC_boLmpTst, &boLampTest);
    DPOOL_enGetPoolData(DPOOL_nDataSBW_boLmpData, &boLmpData);
    if (boLampTest == True)
    {
        if ((SBW__nEeprom_SeatBeltNcapEce == SBW__bEeprom_SeatBeltConfig)
            ||
            (SBW__nEeprom_SeatBeltNcapAdvanced == SBW__bEeprom_SeatBeltConfig))
        {
            u8LampState = SBW__nLampTest;
        }
    }
    else
    {
        if (SBW__u8LampStatus == SBW__nLampBlinking)
        {
            if (boLmpData)
                u8LampState = SBW__nLampStaticOn;
            else
                u8LampState = SBW__nLampOff;
        }
        else
        {
            u8LampState = SBW__u8LampStatus;
        }
    }
    Com_UpdateShadowSignal(Com_IC_Indicator24_Disp_Stat, &u8LampState);
    /* EasyCASE - */
    /* Group sending */
    Com_SendSignalGroup(Com_Grp_IC_Indicators_Disp_Stat);
}
/* EasyCASE ) */
#endif
/* EasyCASE ( 133
   GLOBAL FUNCTIONS */
/* EasyCASE ( 401
   SBW_vInitActive */
/* EasyCASE F */
void SBW_vInitActive(void)
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
    /* Complete re-initialization */
    /* EasyCASE - */
    /* Initialization: SBW has not made any request! */
    SBW__stWarnRequest.enAktWarnRequestLamp = nNoLampWarning;
    /* EasyCASE - */
    /* Initialization: CAN signals */
    SBW__stCan.unDoorOpen.bAll = 0;
    SBW__stCan.unBeltState.bAll = 0;
    SBW__stCan.boDriverBeltStateValid = False;
    /* EasyCASE - */
    /* Remember EEPROM configuration */
    SBW__bEeprom_SeatBeltConfig = SBW__bEeprom_SeatBelt;
    /* EasyCASE - */
    /* Cancel alarm / initialize NCAP warning interval */
    SBW__vAbortWarn();
    /* EasyCASE - */
    /* Initialize normal seat belt warning */
    SBW__vRetriggerNormalWarn();
    /* EasyCASE - */
    /* Initialize NCAP seat belt warning */
    SBW__vRetriggerNcapWarn();
    SBW__vInitializePlayer(SBW__bEeprom_SeatBelt);
    SBW_vRegSBWdebouceEvent();
}

void SBW_vDeinitActive(void)
{
    SBW_vDeRegSBWdebouceEvent();
}
/* EasyCASE ) */
/* EasyCASE ( 708
   SBW_vInitActive15 */
/* EasyCASE F */
void SBW_vInitActive15(void)
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
    /* Workaround for synchronous start of the seat belt warning lamp test */
    SBW__boFirstCheckAfterInitAcitve15 = True;
    SBW__boSoundActivated = False;
    SBW__boSoundSupress = False;
    /* EasyCASE - */
    /* Normal duration for Phases 1-3 */
    SBW__stWarnRequest.boShortPhase = False;
    /* EasyCASE - */
    SBW__vRsbwInitActive15();
    /* EasyCASE - */
    /* Cancel alarm / initialize NCAP warning interval */
    SBW__vAbortWarn();
    /* EasyCASE - */
    /* Initialize legal seat belt warning */
    SBW__vRetriggerNormalWarn();
    /* Initialize NCAP seat belt warning */
    SBW__vRetriggerNcapWarn();
    /* EasyCASE - */
    /* Handle warning request */
    SBW__vHandleRequest();
    /* Init function for project specific code section (sbw_c2.c file) */
}
/* EasyCASE ) */
/* EasyCASE ( 712
   SBW_vDeinitActive15 */
/* EasyCASE F */
void SBW_vDeinitActive15(void)
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
    if (!SBW__nMotorOn)
    {
        /* Cancel alarm / initialize NCAP warning interval */
        SBW__vAbortWarn();
        /* EasyCASE - */
        /* initialize normal seat belt warning */
        SBW__vRetriggerNormalWarn();
        /* Initialize NCAP seat belt warning */
        SBW__vRetriggerNcapWarn();
        /* EasyCASE - */
        /* Handle Warning requests */
        SBW__vHandleRequest();
    }
    /* Workaround for synchronous start of the seat belt warning lamp test */
    SBW__boFirstCheckAfterInitAcitve15 = False;
    /* EasyCASE - */
    /* Remove rear seat belt warnings when KL15g->off */
    SBW__vRsbwDeinitActive15();
}
/* EasyCASE ) */
/* EasyCASE ( 1172
   SBW_v25Active */
/* EasyCASE F */
void SBW_v25Active(void)
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
    /* Workaround for synchronous start of the seat belt warning lamp test */
    /* (hybrid no lamp test with terminal change) */
    if ((SBW__boFirstCheckAfterInitAcitve15)
        &&
        CST_boGetStatus(CST_nenStatusKl15g)
        &&
        !SBW__nMotorOn)
    {
        /* The seatbelt warning and the test lamp must be activated in the 25ms Container after
           the KL15 is switched on */
        SBW_v100Main();
        SBW__boFirstCheckAfterInitAcitve15 = False;
    }
    SBW__vSetDpoolData();
    /* EasyCASE - */
    /**
      * This is only for BR213 according to MR39407
      */
#if defined(SBW__CFG_CanLampState) && (SBW__CFG_CanLampState == On)
    /* EasyCASE - */
    SBW__vSendLampState();
    /* EasyCASE - */
#endif
}

/* EasyCASE ) */
/* EasyCASE ( 326
   SBW_v100Main */
/* EasyCASE F */
void SBW_v100Main(void)
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
    /* Remember EEPROM configuration */
    SBW__bEeprom_SeatBeltConfig = SBW__bEeprom_SeatBelt;
    /* EasyCASE ( 652
       Get CAN signals */
    /* @jopi Potential for improvement: validity for door status also tested? */
    /* EasyCASE - */
    /* Get door status */
    SBW__stCan.unDoorOpen = SBW__stGetDoorState();
    /* EasyCASE ( 1040
       Debugging: Run-time measurement: currently 25us */
#if SBW__CFG_SwiDebugTimeMeasurement
    /* EasyCASE - */
    PFRG_PFG4 = 0;   /* Port function: I/O-Port */
    DDRG_DDG4 = 1;   /* Direction   : Output   */

    PDRG_PDG4 = 1;   /* Port output : High     */
    /* EasyCASE - */
#endif
    /* EasyCASE ) */
    /* Get seatbelt */
    SBW__vGetBeltState(&SBW__stCan.unBeltState, &SBW__stCan.boDriverBeltStateValid);
    /* EasyCASE ( 1044
       Debugging: Run-time measurement: currently 25us */
#if SBW__CFG_SwiDebugTimeMeasurement
    /* EasyCASE - */
    PFRG_PFG4 = 0;   /* Port function: I/O-Port */
    DDRG_DDG4 = 1;   /* Direction  : Output    */

    PDRG_PDG4 = 0;   /* Port output: Low       */
    /* EasyCASE - */
#endif
    /* EasyCASE ) */
    /* EasyCASE ) */
    if (/* Boundary condition: motor running / terminal 15 */
        SBW__nMotorOn)
    {
        /********** Boundary condition satisfied **********/
        if (/* not yet completed normal seat belt warning */
            (SBW__stNormalWarn.wCounterWarn != SBW__wCounterFinish))
        {
            /********** normal seat belt warning **********/
            /* EasyCASE ( 913
               Normal seat belt warning */
            if (/* not yet completed normal seat belt warning */
                (SBW__stNormalWarn.wCounterWarn < SBW__wNormalSeatBeltWarnTimeMaxsec)
                &&
                (SBW__bEeprom_SeatBeltConfig == SBW__nEeprom_SeatBeltNcapAdvanced))
            {
                /********** Warning light active **********/
                /* EasyCASE - */
                /* Turn on warning light */
                SBW__stWarnRequest.enNewWarnRequestLamp = nLampStatic;
                /* EasyCASE ( 1021
                   Acoustic warning */
                if (/* Configured acoustic warning */
                    SBW__boEeprom_SeatBeltBuz
                    &&
                    /* Seatbelt not fastned */
                    (SBW__stCan.unBeltState.stBelt.biDriver == 1)
                    &&
                    (SBW__u8LegalWarnCounter != 0))
                {
                    /********** Acoustic warning active **********/
                    /* EasyCASE - */
                    /* Turn on Buzzer */
                    SBW__stWarnRequest.enNewWarnRequestBuzzer = nBuzzerNormal;
                    /* EasyCASE - */
                    SBW__u8LegalWarnCounter--;
                }
                else
                {
                    /********** No acoustic warning active **********/
                    if (SBW__stCan.boDriverBeltStateValid)
                    {
                        /********** No acoustic warning active **********/
                        /* Turn off Buzzer */
                        SBW__stWarnRequest.enNewWarnRequestBuzzer = nNoBuzzerWarning;
                    }
                    SBW__u8LegalWarnCounter = SBW__nLegalWarnPeriod;
                }
                /* EasyCASE ) */
                /* Warning time for normal seat belt warning count high */
                SBW__stNormalWarn.wCounterWarn++;
            }
            else
            {
                /* Cancel alarm / initialize NCAP warning interval */
                SBW__vAbortWarn();
                /* EasyCASE - */
                /* Normal seat belt warning finished - change state to NCAP seat belt warning */
                SBW__stNormalWarn.wCounterWarn = SBW__wCounterFinish;
            }
            /* EasyCASE ) */
        }
        /* The NCAP seat belt warning can not just stand in the Else branch. Like the normal seat belt warning,
                NCAP seat belt warning must run both branches when switching on!
                */
        if (/* Closed normal seat belt warning or not configured */
            (SBW__stNormalWarn.wCounterWarn == SBW__wCounterFinish))
        {
            /********** NCAP seat belt warning **********/
            /* EasyCASE ( 903
               NCAP seat belt warning */
            if (/* Configured NCAP warning */
                (SBW__bEeprom_SeatBeltConfig == SBW__nEeprom_SeatBeltNcapEce))
            {
                if (SBW__nMotorOn)
                {
                    /********** Motor running **********/
                    if (CST_boGetStatus(CST_nenStatusVelStop))
                    {
                        /********** vehicle is stopped **********/
                        if (((SBW__stCan.unDoorOpen.stDoor.biDriver == 1) &&
                            (SBW__stCan.unDoorOpen.stDoor.biCoDriver == 1))
                            /* both door opened */
                            ||
                            ((SBW__stCan.unDoorOpen.stDoor.biDriver == 1) &&
                            (SBW__stCan.unBeltState.stBelt.biCoDriver == 0) &&
                            (SBW__stCan.unBeltState.stBelt.biMidPassenger == 0))
                            /* driver door opened and co-driver belt fastened and middle front belt fastened */
                            ||
                            ((SBW__stCan.unDoorOpen.stDoor.biCoDriver == 1) &&
                            (SBW__stCan.unBeltState.stBelt.biDriver == 0))
                            /* co-driver door opened and driver belt fastened */)
                        {
                            /*** The door of the passenger who has not fastened his seatbelt is opened ***/
                            /* EasyCASE - */
                            /* Retriggers warning */
                            SBW__vRetriggerNcapWarn();
                            /* EasyCASE - */
                            /* Cancel alarm / initialize NCAP warning interval */
                            SBW__vAbortWarn();
                        }
                        else
                        {
                            /********** Doors closed **********/
                            if (SBW__stWarnRequest.enNewWarnRequestBuzzer == nBuzzerNcapLastPhase)
                            {
                                /* ignore release of seatbelts */
                                SBW__stNcapWarn.unOldBeltState.bAll = SBW__stCan.unBeltState.bAll;
                                /* Handle NCAP warning (finish phase 4) */
                                SBW__vHandleNcapWarn();
                            }
                            else
                            {
                                /* Retriggers warning */
                                SBW__vRetriggerNcapWarn();
                                /* EasyCASE - */
                                /* Warnings Process (current Buzzer still finish) */
                                SBW__vHandleNcapWarn();
                            }
                        }
                    }
                    else
                    {
                        /********** Vehicle is running **********/
                        /* EasyCASE - */
                        /* Warning Start? */
                        SBW__vHandleNcapWarnStart();
                        /* EasyCASE - */
                        /* Process warnings */
                        SBW__vHandleNcapWarn();
                    }
                }
                else
                {
                    /********** Motor not running **********/
                    /* EasyCASE - */
                    /* Retriggers warning */
                    SBW__vRetriggerNcapWarn();
                    /* EasyCASE - */
                    /* Cancel alarm / initialize NCAP warning interval */
                    SBW__vAbortWarn();
                }
            }
            else
            {
                if (/* Configured NCAP warning */
                    (SBW__bEeprom_SeatBeltConfig == SBW__nEeprom_SeatBeltNcapAdvanced))
                {
                    if (SBW__bCounterDelay == SBW__wNormalSeatBeltDelayTimeMaxsec)
                    {
                        if (SBW__nMotorOn)
                        {
                            /********** Motor running **********/
                            if (CST_boGetStatus(CST_nenStatusVelStop))
                            {
                                /********** Vehicle is stopped **********/
                                if (SBW__stWarnRequest.enNewWarnRequestBuzzer == nBuzzerNcapLastPhase)
                                {
                                    /* ignore release of seatbelts */
                                    SBW__stNcapWarn.unOldBeltState.bAll = SBW__stCan.unBeltState.bAll;
                                    /* Handle NCAP warning (finish phase 4) */
                                    SBW__vHandleNcapWarn();
                                }
                                else
                                {
                                    /* Retriggers warning */
                                    SBW__vRetriggerNcapWarn();
                                    if (SBW__stCan.unDoorOpen.bAll != 0)
                                    {
                                        /********** Door Open **********/
                                        /* EasyCASE - */
                                        /* Cancel alarm / initialize NCAP warning interval */
                                        SBW__vAbortWarn();
                                    }
                                    else
                                    {
                                        /********** Doors closed **********/
                                        /* EasyCASE - */
                                        /* Warnings Process (current Buzzer still finish) */
                                        SBW__vHandleNcapWarn();
                                    }
                                }
                            }
                            else
                            {
                                /********** Vehicle is running **********/
                                /* EasyCASE - */
                                /* Warning Start? */
                                SBW__vHandleNcapWarnStart();
                                /* EasyCASE - */
                                /* Process warnings */
                                SBW__vHandleNcapWarn();
                            }
                        }
                        else
                        {
                            /********** Motor not running **********/
                            /* EasyCASE - */
                            /* Retriggers warningn */
                            SBW__vRetriggerNcapWarn();
                            /* EasyCASE - */
                            /* Cancel alarm / initialize NCAP warning interval */
                            SBW__vAbortWarn();
                        }
                    }
                    else
                    {
                        SBW__bCounterDelay++;
                    }
                }
                else
                {
                    /********** Not configured NCAP seat belt warning **********/
                    /* EasyCASE - */
                    /* Cancel alarm / initialize NCAP warning interval */
                    SBW__vAbortWarn();
                }
            }
            /* EasyCASE ) */
        }
    }
    else
    {
        /********** Boundary condition is not fulfilled **********/
        /* EasyCASE - */
        /* Normal duration for Phases 1-3 */
        SBW__stWarnRequest.boShortPhase = False;
        /* EasyCASE - */
        /* Cancel alarm / initialize NCAP warning interval */
        SBW__vAbortWarn();
        /* EasyCASE - */
        /* Initialize legal seat belt warning */
        SBW__vRetriggerNormalWarn();
        /* EasyCASE - */
        /* Initialize NCAP seat belt warning */
        SBW__vRetriggerNcapWarn();
        /* EasyCASE - */
        SBW__u8LegalWarnCounter = SBW__nLegalWarnPeriod;
    }
    /* Warning requests in and out */
    SBW__vHandleRequest();
    /* EasyCASE ( 1286
       Rear seatbelts warning handler */

    /* Rear seatbelts warning handler */
    if ((SBW__boEeprom_RearSeatbeltWrn())
        /* Rear seatbelts warnings are configured in EEPROM */
        &&
        (SBW__u8Eeprom_VehLine() != SBW__nVehLineBR447))
        /* Vehicle Line is not 447 */
    {
        SBW__vRearHandleKL15ReadyDelay();

#ifdef SBW__HL

        if (SBW__boEeprom_RearSeatMat())
        {
            SBW__vRearSeatbeltWrnMat();
        }
        else
        {
            SBW__vRearSeatbeltWrn2018(True);
        }
#endif
#ifdef SBW__LL
        SBW__vRearSeatbeltWrn2018(True);
#endif
    }
}
/* EasyCASE ) */
/* EasyCASE ( 1363
   SBW_enDiagStartSupressing */
/* EasyCASE F */
DLIB_tenReturn SBW_enDiagStartSupressing(void)
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
    if ((SBW__boSoundActivated == True)/*if a SAM_Request was performed*/
        &&
        (SBW__enGetPhase(False) < nNoBuzzerWarning))
    {
        /*  Clear registered sound warnings */
        SBW__boSoundActivated = False;
    }

    if ((SBW__boSoundActivatedRear == True)/*if a SAM_Request was performed*/
        &&
        (SBW__enGetPhase(True) < nNoBuzzerWarning))
    {
        /*  Clear registered sound warnings */
        SBW__boSoundActivatedRear = False;
    }

    SBW__boSoundSupress = True;/*Supress sound, no SAM_Request will be performed*/

    /* EasyCASE - */
    /* EasyCASE < */
    return DLIB_nReturnCodeOK;
    /* EasyCASE > */
}
/* EasyCASE ) */
/* EasyCASE ( 1364
   SBW_enDiagStopSupressing */
/* EasyCASE F */
DLIB_tenReturn SBW_enDiagStopSupressing(void)
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
    if (SBW__boSoundSupress == True /*if Start supressing was requested*/)
    {
        /* EasyCASE < */
        SBW__boSoundActivated = False;
        SBW__boSoundActivatedRear = False;
        SBW__boSoundSupress = False;
        return DLIB_nReturnCodeOK;
        /* EasyCASE > */
    }
    else
    {
        /* EasyCASE < */
        return DLIB_nReturnCodeRefuse;
        /* EasyCASE > */
    }
}
/* EasyCASE ) */
/* EasyCASE ( 1430
   SBW_vReCheckWarnings */
/***************************************************************************
* Interface Description: Called by WIM at KL15On
*
* Implementation       : Retriggers the warning
*
* Return Value         : void
*
* Author               : Jan Lacko
*
****************************************************************************/
/* EasyCASE F */
void SBW_vReCheckWarnings(void)
{
    if (SBW__stWarnRequest.enNewWarnRequestBuzzer != nNoBuzzerWarning)
    {
        if ((SBW__boSoundSupress == False) && ((True == SBW__boEeprom_SeatBeltBuz) || (SBW__nNoSoundRear == SBW__u8Eeprom_SeatBeltBuzInactive)))
        {
            if (False == WIM_boIsRegistered(SBW__stBuzzer[SBW__stWarnRequest.enNewWarnRequestBuzzer].enLogDevice))
            {
                WIM_vSetIntEvent(SBW__stBuzzer[SBW__stWarnRequest.enNewWarnRequestBuzzer].enLogDevice);
            }
        }
    }

    if ((SBW__boEeprom_RearSeatbeltWrn())
        /* Rear seatbelts warnings are configured in EEPROM */
        &&
        (SBW__u8Eeprom_VehLine() != SBW__nVehLineBR447)
        /* Vehicle Line is not 447 */)
    {


#ifdef SBW__HL

        if (SBW__boEeprom_RearSeatMat())
        {
            SBW__vResetRearSeatbeltWrn();
            SBW__vRearSeatbeltWrnMat();
        }
        else
        {
            SBW__vResetRearSeatbeltWrn();
            /* Rear seatbelts warning handler NCAP 2018 */
            SBW__vRearSeatbeltWrn2018(True);
        }
#endif
#ifdef SBW__LL
        /* Rear seatbelts warning handler NCAP 2018 */
        SBW__vResetRearSeatbeltWrn();
        SBW__vRearSeatbeltWrn2018(True);
#endif

    }
    else
    {
        /*do nothing*/
    }

}
/* EasyCASE ) */
/* EasyCASE ( 1392
   SBW_vManuQuitCallback */
/* EasyCASE F */
void SBW_vManuQuitCallback(uint32 u32WarnNumber, WIM_tenDisplayEvent enEvent)
{
    /***************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local variables (auto and static)
    ****************************************************************************/
    /* EasyCASE - */
    /* to avoid compiler/QAC warnings */
    enEvent = enEvent;
    /* EasyCASE - */
#ifdef SBW__HL
    if (SBW__boEeprom_RearSeatMat())
    {

    }
    else
    {
        SBW__vManuQuitWarnRelease(u32WarnNumber);
    }
#endif
#ifdef SBW__LL
    SBW__vManuQuitWarnRelease(u32WarnNumber);
#endif
}
/* EasyCASE ) */
/* EasyCASE ( 1406
   SBW_vGetSbwHILInfo */
/* EasyCASE F */
void SBW_vGetSbwHILInfo(uint32 *pu32Value)
{
    SBW__vGetSbwHILInfo(pu32Value);
}
/* EasyCASE ) */
/* EasyCASE ( 1409
   SBW_vDisplayChangeCallback */
/* EasyCASE F */
void SBW_vDisplayChangeCallback(uint32 u32HilId)
{
    SBW__vDisplayChangeCallback(u32HilId);
}
/*SBW_vRearSeatbeltWrn2018*/
/* EasyCASE F */
void SBW_vRearSeatbeltWrn2018(void)
{

    /* Rear seatbelts warning handler */
    if ((SBW__boEeprom_RearSeatbeltWrn())
        /* Rear seatbelts warnings are configured in EEPROM */
        &&
        (SBW__u8Eeprom_VehLine() != SBW__nVehLineBR447)
        /* Vehicle Line is not 447 */)
    {

#ifdef SBW__HL

        if (SBW__boEeprom_RearSeatMat())
        {
            SBW__vRearSeatbeltWrnMat();
        }
        else
        {
            SBW__vRearSeatbeltWrn2018(False);
        }
#endif
#ifdef SBW__LL
        SBW__vRearSeatbeltWrn2018(False);
#endif
    }

}

/* EasyCASE ) */
/* EasyCASE ( 171
   EOF */
/***************************************************************************
* EOF: SBW_C1.C
****************************************************************************/
/* EasyCASE ) */
/* EasyCASE ) */
