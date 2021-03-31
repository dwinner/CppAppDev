/***************************************************************************
*=====================      Copyright by Continental AG      ===============
****************************************************************************
* Titel        : WIM1c1.h
*
* Description  : internal configuration of package WIM
*
* Environment  : OSEK, JCP (NEC V850)
*
* Responsible  : A.Wagner, Schleissheimer GmbH
*
* Guidelines   : SMK 3.3  
*
* Template name: OOLite Codefile, Revision 1.0
*
* CASE-Tool    : Together Controlcenter, Version 6.2
*
* Revision List: (Will be filled by PVCS)
* Archive: $Log: WIM1c1.h  $
* Archive: Initial revision for VS11 (Based on 213IC-EL E009.4rel)
*
* Archive: Revision 1.12 2015/06/17 18:45:04CEST Wenske-EXT, Martin (uidj8453) 
* Archive: DC MR 47461 : runtime of BasicApp_Prio2 too long
* Archive: Revision 1.11 2015/02/27 10:51:35CET Wenske-EXT, Martin (uidj8453) 
* Archive: DC MR 46165 : GEAR: Fix for Warning 0x200528 Fahrprogramme is not displayed after reset
* Archive: Revision 1.10 2014/12/11 16:34:09CET Wenske-EXT, Martin (uidj8453) 
* Archive: DC MR 44771 : APC warnings are not displayed after the display was OFF and CAN bus was in sleep mode
* Archive: Revision 1.9 2014/12/05 11:33:10CET Wenske-EXT, Martin (uidj8453) 
* Archive: DC MR 44615 : AC\HL: BR213HL, E009.1, L2 implementation
* Archive: DC MR 44614 : AC\EL: BR213EL E009.1 L2 implementation
* Archive: DC MR 44471 : BR213 Basic implementation of AMG function
* Archive: Revision 1.8 2014/11/03 18:38:50CET Wenske-EXT, Martin (uidj8453) 
* Archive: DC MR 42554 : �LP11307: WIM: Introduction of new Keyword E2E in the WarnDB
* Archive: DC MR 44110 : AC: BR213EL E009 - L3 Implementation
* Archive: DC MR 44103 : AC: BR213HL - E009 L3 Implementation
* Archive: Revision 1.7 2014/11/03 14:38:04CET Wenske-EXT, Martin (uidj8453) 
* Archive: DC MR 41351 : ALP 9698: Acknowledge behavior for warning winter tire speed limit
* Archive: Revision 1.6 2014/07/18 15:10:26CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 41158 : BR213-Safety: Improvement of Safety warning management
* Archive: Revision 1.5 2014/06/16 15:01:10CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 41142 : WIM: HIL ID output on IC_WIM_AR does not work
* Archive: Revision 1.4 2013/12/06 17:57:46CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 37489 : AC/HL: Warnings 0x200430 and 0x200431 can't be activated
* Archive: DC MR 36977 : APC: start-up MR for APC V3
* Archive: DC MR 37374 : WIM: Implement changes on door warning acoustics after clarification with customer - OPL 2064
* Archive: Revision 1.3 2013/11/22 17:48:37CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 36728 : SBW: NCAP phases 1 to 3 are not played again in case of a cluster reset
* Archive: Revision 1.2 2013/08/29 17:35:06CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 34316 : BR213 AC: Removal of function complex Assyst
* Archive: DC MR 34919 : EED: Provide access to EVC coding IntFoldHdRst_Ft_Avl
* Archive: Revision 1.1 2013/03/21 16:49:47CET Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/adapt/BR213IC_AC_EL_SOP/project.pj
* Archive: Revision 1.4 2013/01/21 12:37:14CET Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 31161: BR205/AC, WIM: Overtake HMI components for flashing (HMI synchronisation) from IC222/change of generic code
* Archive: Revision 1.3 2012/12/21 14:08:42CET Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 30793: WIM: Condition check uses wrong speed reference for term "GESCHWINDIGKEIT" (WDM60874)
* Archive: DC MR 30796: BR205, E011/AC, WIM: Wrong usage of coding CPAPlus_Menu_active - WDM59276
* Archive: Revision 1.2 2012/11/21 11:54:05CET Immel Marc (uid37561) (uid37561) 
* Archive: Migration of WIM-AC from PVCS to MKS 
* Archive: - used release: DC.SW.PAC.WIM_205IC_AC_COMMON_VarW.V01.00.pre17
* Archive: Revision 1.1 2012/03/02 13:48:34CET uid37556 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/adapt/project.pj
*    Rev 1.7   Jun 15 2012 16:18:28   SCHL_Dirk.Gottwalles
* DC MR 26067: W205, E009/AC, WIM: New configuration CPAPlus_Menu_active
* DC MR 26325: W205, E009/AC, WIM: Boundary and Retrigger condition of protocol_class_2
* DC MR 25952: W205, E009/AC, WIM: Change of Prio1Mute and Lowering times - �LP2873
* 
*    Rev 1.6   May 18 2012 16:55:58   SCHL_Dirk.Gottwalles
* DC MR 25587: WDM21151/34246/35637: SBW/WIM Acoustic corrections
* DC MR 25914: W205, E009/AC, HIL: Mapping of WIM sound types
* 
*    Rev 1.5   Mar 02 2012 13:49:06   SCHL_Dirk.Gottwalles
* DC MR 23574: W205, APC: all the changes in APC of W222 should be taken for 205
* 
*    Rev 1.4   Mar 01 2012 13:04:46   SCHL_Dirk.Gottwalles
* DC MR 24004: HUD: Porting of functionalities to GC (AC)
* DC MR 24339: W205, E007/AC, WIM: Remove unused code parts from secondary mute request
* 
*    Rev 1.3   Jan 20 2012 14:21:16   SCHL_Dirk.Gottwalles
* DC MR 23690: E007/AC WIM reduce coreload
* DC MR 23692: W222, E007/AC: Warnung Parkbremse 0x2001A8 �LP2607
* DC MR 23765: W205, E007/AC, WIM: Patch for 0x2000BC and 0x2000C1 (Country coding), WDM23191
* 
*    Rev 1.2   Dec 08 2011 17:10:40   SCHL_Dirk.Gottwalles
* DC MR 24074: BR205, E007/AC, WMN: Implementation of changes for new WEM
* DC MR 23619: E007/AC WIM remove pragma 'callmode far'
* DC MR 23222: W205,  E007/AC, HUD: Implementation of HUD warnings
* DC MR 24084: W205, E007/AC, WIM: New keyword KL15_ON_1SEC �LP2647
* DC MR 24083: W222, E007/AC, WIM: Implementation and mapping of keyword ENGINE_START_2SEC
* DC MR 24076: W205, E006/AC, WIM: Timeout function shall not use first value, WDM1378
* DC MR 24077: BR205/E007/GC: HIL: Acoustics WIM-REQ (WDM#19107)
* 
*    Rev 1.1   Dec 05 2011 16:29:38   SCHL_Dirk.Gottwalles
* DC MR 23774: Integration of ARTEMMIS 3.2.1
* DC MR 23943: Use visibility change detection mechanism
* DC MR 23914: Applications should send global direct messages
* DC MR 23421: BR205: Implementation of E007 pre10 (XML-Files and StyleGuide)
* 
*    Rev 1.0   Nov 08 2011 14:39:06   SCHL_Dirk.Gottwalles
* Initial revision.
* 
****************************************************************************/

/*
* Check if information is already included
*/
#ifndef WIM1C1_H
#define WIM1C1_H

/***************************************************************************
* HEADER-FILES (Only those that are needed in this file)
****************************************************************************/
/* System-headerfiles */
#include "cdef.h"               /* General definitions and types     */

/* Foreign headerfiles */
#include <string.h>                 /* for memset usage                  */
#include "EXEA_c1.h"                /* exception handler                 */
#include "DLIB_c1.h"                /* diagnostic interface library      */
#include "DPOOL_c1.h"               /* data pool                         */
#include "EVHD_c1.h"                /* event handler                     */
#include "CST_c1.h"                 /* car states                        */
#include "KBD_c1.h"                 /* keyboard interface                */
#include "Com.h"                    /* Can object access                 */
#include "Com_Cfg.h"                /* CAN State Flags                   */
#include "EED_c1.h"                 /* EEPROM Configuration              */
#include "RSST_c1.h"                /* Sound ressources                  */
#include "HMI_c1.h"                 /* HMI interface                     */
#include "PCMPL_c1.h"               /* Sound interface                   */
#include "AVOL_c1.h"                /* acoustic volume                   */
#include "CRHDL_c1.h"               /* central state handler             */
#include "E2EMG_GenInterface.h"       /* E2E Interface                     */

/* WIM clients */
#include "VEL_c1.h"                 /* velocity dependent Warnings      */
#include "SBW_c1.h"                 /* Seat Belt Warn                   */
#include "WTP_c1.h"                 /* Coolant Temp. Warn               */
#include "SCS_C1.h"                 /* SCS                              */
#include "GEAR_C1.h"                /* GEAR                             */
#include "TSA_C1.h"                 /* TSA                              */
#include "CFG_C1.h"                 /* GEAR                             */
#include "TIMER_C1.h"               /* GEAR                             */
#include "WIM1ce.h"                 /* GEAR                             */
#include "SBCxC1.H"                 /* SBC                              */
#include "FSM_C1.H"                 /* FSM                              */
#include "TETAC_C1.H"               /* TETAC                            */
#include "APC_C1.H"                 /* APC                              */
#include "ASPKE_c1.h"               /* WR Kernel                        */

/* Own headerfiles */
#include "WIM__TimerConfig.h"       /* controller specific timer config                   */
#include "WIM__TimerHandler.h"      /* platform generic timer handler                     */
#include "WIM_Interface.h"          /* platform generic WIM interface                     */
#include "WIM__AcousticView.h"      /* controller generic inter processor communication   */
#include "WIM__ICom_AC.h"           /* controller generic inter processor communication   */
#include "WIM__ICom_GC.h"           /* controller generic inter processor communication   */
#include "WIM__DataInt.h"           /* platform specific message data                     */
#include "WIM__IComIntern.h"        /* controller specific inter processor communication  */
#include "WIM__CheckFct.h"          /* platform specific check functions                  */
#include "WIM__CanInterface.h"      /* platform generic CAN interface                     */
#include "WIM__RequestControl.h"    /* platform generic request control interface         */
#include "WIM__Scheduler.h"         /* Scheduler                                          */
#include "WIM__Types.h"             /* package internal type definitions                  */
#include "WIM__StateHandler.h"      /* State Handler                                      */
#include "WIM__KeyControl.h"        /* Key Handler                                        */
#include "WIM__Diag.h"              /* Diagnostic adaption                                */
#include "WIM__MenuFaultMemory.h"   /* MenuFaultMemory                                    */ 
#include "WIM__ComplexDraw.h"       /* Complex drawings                                   */
#include "WIM__ComplexCondition.h"  /* Complex condition check                            */
#include "WRS_ExternalMessageQueueConfiguration.hpp"  /* Message priorisation */

/****************************
* Timer Definiton
*****************************/
/* Timer for HIL Break (60ms) @ 10ms timer_tick */
#define WIM_nTimerDuration_HilBreak       ((uint16)6 )
/* Timer for Acoustic Timer Delay (300ms) @ 10ms timer_tick */
#define WIM_nTimerDuration_AcuTDElapsed   ((uint16)30 )
/* Timer for suppressing VAN tracking status warning */
#define WIM_u16TimerDuration_SuppressVanTrackingStatus	((uint16)EEH_biGetSuppressTime_TrackingDisclaimer()*(uint16)100 )
/* Timer for display tracking status time */
#define WIM_u16DisplayTimeVanTrackingStatus	((uint16)EEH_biGetTimer_TrackingDisclaimer()*(uint16)100)
/* Timer for Frontal/Lateral Collision Tone (400ms) @ 10ms timer_tick */
#define WIM_nTimerDuration_FreqCollWarn ((uint16)40 )
/* Timer for Continious Acoustic Delay (1000ms) @ 10ms timer_tick */
#define WIM_nTimerDuration_FreqContWarn ((uint16)100 )
/****************************
* DISPLAY
*****************************/
/* Give the timing parameter in ms and use DSM TimeBase for adaption */
#define WIM__nDspReleaseLagLong    (uint16) (120000 / DSM_nDispStrTimeBase)
#define WIM__nDspReleaseNoLag      (uint16) (0 / DSM_nDispStrTimeBase)
#define WIM__nDspReleaseLagDefault (uint16) (DSM_nDispStrUseDefaultTimeLag)
/* Send Information into DRM to Handle Dipslay Requests */
#define WIM__vRequestDisplay() \
   HMI_boSendMessagePrio(MsgID_DSM_RequestDisplay,          True, (uint32)enClientWIM, HMI_Message_Direct, HighestExtMsgListPriorityLevel) 
#define WIM__vRequestDisplayIfOn() \
   HMI_boSendMessagePrio(MsgID_DSM_RequestDisplayIfOn,      True, (uint32)enClientWIM, HMI_Message_Direct, HighestExtMsgListPriorityLevel) 
#define WIM__vReleaseDisplay(u32Data) \
   HMI_boSendMessagePrio(MsgID_DSM_ReleaseDisplay,          True, u32Data,             HMI_Message_Direct, HighestExtMsgListPriorityLevel) 
#define WIM__vReleaseDisplayProtected(u32Data) \
   HMI_boSendMessagePrio(MsgID_DSM_ReleaseDisplayProtected, True, u32Data,             HMI_Message_Direct, HighestExtMsgListPriorityLevel) 
/* display request/release */
#define WIM__vDspWarningRequest(u32MessageData) \
   HMI_boSendMessagePrio(WIM_DisplayWarning,       True, u32MessageData, HMI_Message_GlobalDirect,    HighestExtMsgListPriorityLevel) 
/* display request/release slack message*/
#define WIM__vDspSlackRequest(u32MessageData) \
   HMI_boSendMessagePrio(MsgId_WIM_DisplaySlack,   True, u32MessageData,   HMI_Message_Direct,        HighestExtMsgListPriorityLevel)
/* 0xffff0000 is the WIM_nenInvalidMsg and 0x0000 is the reduced WIM__nInvalidHilId */
#define WIM__vDspWarningRelease() \
   HMI_boSendMessagePrio(WIM_DisplayWarning,       True, 0xFFFF0000,       HMI_Message_GlobalDirect,  HighestExtMsgListPriorityLevel) 
#define WIM__vDspSlackRelease() \
   HMI_boSendMessagePrio(MsgId_WIM_DisplaySlack,   True, 0xFFFF0000,       HMI_Message_Direct,        HighestExtMsgListPriorityLevel) 

/****************************
* ACOUSTIC
*****************************/
#define WIM__vSendAcoustWarning(u32HilId)
#define WIM__vSendAcoustWarningNone()

/****************************
* TIMER HANDLER
*****************************/
/* loop time of WIM main function in microsec */
#define WIM__nLoopTime  10000UL
/* calculation of WIM main function loops for millisec timer values */
#define WIM__mu16GetLoopCount(u32TimeInMillisec) \
   ((uint16)(( (u32TimeInMillisec)*1000 + WIM__nLoopTime/2 ) / WIM__nLoopTime))

/****************************
* CONTAINERS
********************************/
/* ManuQuit container:
   the functions added to this container are called every time
   a WIM message is confirmed by the driver.
   As parameter the enum of the new master is passed to the callback. 
   The callback must be of type WIM_tpvManuQuitCb defined in the export 
   interface.
*/
#define WIM__nManuQuitContainerContent    \
/* add application callbacks here e.g. */ \
   SBW_vManuQuitCallback,                 \
   ASPKE_vManuQuitCallback,               \
   WIM_vManuQuitCallback,                 \
   SCS_vManuQuitCallback,                 \
   WIM__vIComManuQuitContainer,           \
/* MOD1_vManuQuitCallback,             */ \
/* MOD2_vManuQuitCallback,             */


/* PreConfirmation container:
   the functions added to this container are called every time
   a WIM message is confirmed by the driver, which has the special DiffManQuit
   configured and was only pre confirmed. As parameter the Hil-Id of the confirmed 
   message is passed. 
   The callback must be of type WIM_tpvPreConfirmationCb defined in the export 
   interface.
*/
#define WIM__nPreConfirmationContainerContent   \
/* Forward to AC by ICom */                     \
   WIM__vIComPreConfirmationContainer,          \
/* add application callbacks here e.g. */       \
/* MOD1_vPreConfirmationCallback,      */       \
/* MOD2_vPreConfirmationCallback,      */


/* CheckComplex container:
   the functions added to this container are called every time
   WIM resets the dynamic state of messages (DisplayOn/Kl15ROn)
   Applications must re-check the conditions of their warnings
   and request them again (if active)
*/
#define WIM__nCheckComplexContainerContent   \
   /*WIM__vCheckConvertibleTop,         */       \
   /*WIM__vReCheckOperationModeHybrid, */        \
/* add application callbacks here e.g. */    \
/*BeHe   ASPKE_vReCheckWarnings, */                  \
   VEL_vReCheckWarnings,                     \
   SBC_vReCheckWarnings,                     \
   WTP_vReCheckWarnings,                     \
   TSA_vReCheckWarnings,                     \
   TETAC_vReCheckWarnings,                   \
   SBW_vReCheckWarnings,                     \
   WIM_vReCheckWarnings,                     \
   FSM_vReCheckWarnings,                     \
   SCS_vReCheckWarningsCallback,             \
   GEAR_vReCheckWarnings,                    \
   APC_vReCheckWarnings,                     \
/* MOD1_vCheckWarnings,                */    \
/* MOD2_vCheckWarnings,                */

/****************************
* SCHEDULER/ACOUSTIC VIEW
*****************************/
/* master change containers:
   the functions added to these containers are called every time
   a new WIM message gets the display/acoustic channel.
   As parameter the enum of the new master is passed to the callback. 
   The callback must be of type WIM_tpvChangeCb defined in the export 
   interface.
*/
#define WIM__nDspChangeContainerContent_GC      \
    /* Forward to AC by ICom */                 \
    WIM__vIComDspChangeContainer,               \
    /* add application callbacks here e.g. */   \
    /* MOD1_vDisplayChangeCallback,        */   \
    /* MOD2_vDisplayChangeCallback,        */

#define WIM__nDspChangeContainerContent_AC   \
/* Forward to AC by ICom */                 \
   WIM__vWmnReportDspChangeTrigger,         \
   SBW_vDisplayChangeCallback,              \
   APC_vDisplayChangeCallback,              \
/*   WIM_vDisplayChangeCallback,       */  \
/* add application callbacks here e.g. */   \
/* MOD1_vDisplayChangeCallback,        */   \
/* MOD2_vDisplayChangeCallback,        */

/* message state change notification */
#define WIM__mNotifyHandler_GC(u32HilId, enNotify)    \
/* Forward on AC by ICom */                           \
   WIM__vIComNotifyHandler((u32HilId), (WIM_tenDisplayEvent)(enNotify))
/* add application callbacks here e.g. */                
/* MOD1_vNotifyMe(u32HilId, enNotify), */                
/* MOD2_vNotifyMe(u32HilId, enNotify), */

#define WIM__mNotifyHandler_AC(u32HilId, enNotify)    \
    CFG_vWIMNotifyHandler((u32HilId), (enNotify));    \

/* Last entry in each container that will define the container end */
#define WIM__nLastCntEntry NULL

/************************
* CanInterface
************************/
/* CAN HU signal delays from EEPROM */
#define SYN__mu8MuteDelay     (uint8)EEH_biGetPrio1MuteDelay()
#define SYN__mu8VolDecDelay   (uint8)EEH_biGetLowerAcousticDelay()
#define SYN__u8GetVolume      AVOL_u8GetVolumePara
/* delay times for mute/volume decrease CAN signals (HU) */
#define WIM__nPrio1MuteDelayTimeConfiguration \
   10,  /*  1000 ms */               \
   20,  /*  2000 ms */               \
   5,   /*   500 ms */               \
   0    /* no delay */

/* Note: With implementation of MR27470, WIM keeps the system awake from 
   the start of a sound until its end. It has to be ensured that only sounds
   without the loop feature (param boContPlay == False) are treated this way */
#define SYN__enSoundRequest          PCMPL_enStartSound
#define SYN__enOutputChannel         PCMPL_nChnLeft

#define WIM__nLoweringDelayTimeConfiguration \
   5,   /*   500 ms */               \
   10,  /*  1000 ms */               \
   20,  /*  2000 ms */               \
   0    /* no delay */

/* bit mask coding array size */
#define WIM__nu8Bit2Mask ((uint8)0x03)

/* factor for delay times */
#define WIM__nDelayTmFactor 100

/* mute/lower time for async acoustics */
#define WIM__nAsyncMuteLowerDelay   16
/* display forerun before acoustic starts (300ms) in base ticks */
#define WIM__nu16ForeRun            WIM__mu16GetLoopCount(300) 

/* Start of dummy sound/silence before a synchronous acoustic is output */
#define SYN__mvStartDummySound()    //AHC_vActivateSound()

/* acoustic sound IDs */
#define SYN__nSoundIdFrontCollision  RSST_nenSound_Collision_Wrn
#define SYN__nSoundIdLatCollision    RSST_nenSound_LatCollision_Wrn
#define SYN__nSoundIdPrio1           RSST_nenSound_Prio1_Wrn
#define SYN__nSoundIdPrio2           RSST_nenSound_Prio2_Wrn
#define SYN__nSoundIdContinuous      RSST_nenSound_Permanent_Wrn
#define SYN__nSoundIdAcknowledgement RSST_nenSound_Confirmation
#define SYN__nSoundIdAttention       RSST_nenSound_Attention_Wrn
#define SYN__nSoundIdBeltWarnLevel1  RSST_nenSound_Belt_Phase1
#define SYN__nSoundIdBeltWarnLevel2  RSST_nenSound_Belt_Phase2
#define SYN__nSoundIdRearBeltWarn    RSST_nenSound_Belt_Phase2

/****************************
* CAN RX/TX signal access
*****************************/
/* receive signal: lower HU volume */ 
#define WIM__mCreateAudioMute_1() uint8 u8My_AudioMute_1_Rq
#define WIM__mGetAudioMute_1()    Com_ReceiveSignal(Com_AudioMute_1_Rq ,&u8My_AudioMute_1_Rq) 
#define WIM__mboToAudioMute_1     Com_GetRxSigTimeoutFlag(Com_AudioMute_1_Rq)
#define WIM__mboFvAudioMute_1     Com_GetRxSigFirstValueFlag(Com_AudioMute_1_Rq)  
#define WIM__mboAudioMute_1       u8My_AudioMute_1_Rq   

/****************************
* CHECK FCT
*****************************/
/* Access macros for Disabling/Enabling interrupts */
#define WIM__mvLock      IREXT_vDisableAndSave_Int
#define WIM__mvUnLock    IREXT_vRestore_Int

/* definition for Flag- and Bit-Signal Access */
#define WIM__nActive  1
#define WIM__nPassive 0

/* Definitions for DoorState Bit-Access */
#define WIM__nDoorMaskFL 0x01
#define WIM__nDoorMaskFR 0x02
#define WIM__nDoorMaskRL 0x04
#define WIM__nDoorMaskRR 0x08
#define WIM__nDoorMaskTRL 0x10
#define WIM__nDoorMaskTRR 0x20
#define WIM__nDoorMaskElecRL 0x40
#define WIM__nDoorMaskElecRR 0x80

/* Defines the number of real time check function that are executed 
   consecutive before a Os schedule is performed */
#define WIM__nNumOfConsecutiveChecks 20
#define WIM__vOsSchedule() Schedule()

/****************************
* KEY CONTROL
*****************************/
/* definition of key events used for manual confirmation of messages */
#define WIM__boIsOkKey(Key)         ((Key) == KBD_nenOK  ) 
#define WIM__boIsBackKey(Key)       ((Key) == KBD_nenBack) 
/* mapping of key event to state handler event */
#define WIM__mGetManuQuitEvt(Key) \
   (((Key) == KBD_nenOK) ? WIM__nManuQuitOk : WIM__nManuQuitBack)

/****************************
* EXCEPTION HANDLING
*****************************/
/* exception handler calls */
#define WIM__vRaiseException(nErrNo) \
   EXEA_vHandleException(WIM_Package, nErrNo, __LINE__, 0)

/****************************
* EVENT PROCESSING
*****************************/
/*
* Description: Register all Events WIM owns by EVHD
*/
#define WIM__vEvhdRegisterEvents()                                                              \
   /* Register on ICOM communication Event, with pending Event. */                              \
   EVHD_vRegister(EV_DPOOL_Always_WIM_u32IcomDataGc_QueueGC_to_AC_WIM_vDoDpoolEvents, True);    \
   /* Register on ICOM communication Event, with pending Event. */                              \
   EVHD_vRegister(EV_DPOOL_OnChange_ICBWMDL_u32DynAreaHilId_WIM_vDoDpoolEvents, True);          \
   /* Register on ICOM communication Event, with pending Event. */                              \
   EVHD_vRegister(EV_DPOOL_OnChange_WIMMDL_u32SlackHilId_WIM_vDoDpoolEvents, True);             \
   /* Register on ICOM communication Event, with pending Event.*/                               \
   EVHD_vRegister(EV_DPOOL_Always_WIM_u32IcomDataAc_QueueAC_to_GC_WIM_vDoDpoolEvents, True);    \
   /* Register on HMI-API-Feedback Event for Warning displayed, with pending Event.*/           \
   EVHD_vRegister(EV_DPOOL_Always_WIM_stHmiFeedback_WIM_vDoHmiEvents, True);                    \
   /* Register on HMI-API-Feedback Event for Warning cancelleded */                             \
   EVHD_vRegister(EV_DPOOL_Always_WIM_u16CanceledWarning_WIM_vDoHmiEvents, True);               \
   /* Register on HMI-API-Feedback Event for slack displayed, with pending Event.*/             \
   EVHD_vRegister(EV_DPOOL_Always_WIM_stHmiFeedbackSlack_WIM_vDoHmiEvents, True);               \
   /* Register on HMI-API-Feedback Event for slack cancelleded */                               \
   EVHD_vRegister(EV_DPOOL_Always_WIM_u16CanceledSlack_WIM_vDoHmiEvents, True);                 \
   /* Register on HMI-API-Feedback Event for Warning suppressed */                              \
   EVHD_vRegister(EV_DPOOL_Always_WIM_u16SuppressedWarning_WIM_vDoHmiEvents, True);             \
   /* Register on HMI-API-Feedback Event for Key-Handling, with pending Event.*/                \
   EVHD_vRegister(EV_DPOOL_Always_WIM_stKeyEvent_WIM_vDoHmiEvents, False);                      \
   /* Register on HMI-API-MenuFaultMem Event for Reset-Handling, without pending Event.*/       \
   EVHD_vRegister(EV_DPOOL_Always_WIM_u8FaultMemEvReset_WIM_vDoHmiEvents, False);               \
   /* Register on HMI-API-MenuFaultMem Event for Navigation-Handling, without pending Event.*/  \
   EVHD_vRegister(EV_DPOOL_Always_WIM_u8FaultMemEvPrevNext_WIM_vDoHmiEvents, False);            \
   /* Register on HMI-API-DisplayOn Event, without pending Event.*/                             \
   EVHD_vRegister(EV_DPOOL_OnChange_WIM_boDisplayOn_WIM_vDoHmiEvents, True);                    \
   /* Register on ICOM State Change Event, without pending Event.*/                             \
   EVHD_vRegister(EV_DPOOL_OnChange_ICTP_enConStatus_WIM_vDoDpoolEvents, False);                \
   /* Register on CSP convertible top state change event, without pending Event.*/              \
   EVHD_vRegister(EV_DPOOL_OnChange_CSP_u8StateConvertibleTop_WIM_vDoDpoolEvents, False);       \
   /* Register on RES_Sound on notification.*/                                                  \
   EVHD_vRegister(EV_ChangeNotificSMSRES_Sound_WIM_vDoGeneralEvents, True);                     \
   /* Register on RES_Audio_HW on notification.*/                                               \
   EVHD_vRegister(EV_ChangeNotificSMSRES_Audio_HW_WIM_vDoGeneralEvents, True);                  \
   /* Register on Hybrid state change event, without pending Event.*/                           \
   EVHD_vRegister(EV_DPOOL_OnChange_HYHLPOW_stModelDataAC_WIM_vDoDpoolEvents, False);           \
   /* Register on timer event, without pending Event.*/                                         \
   EVHD_vRegister(EV_TIM_WIM_HilBreakTimer_WIM_vDoGeneralTimerEvents, False);                   \
   /* Register on timer event, without pending Event.*/                                         \
   EVHD_vRegister(EV_TIM_WIM_TimerAcuTDElapsed_WIM_vDoGeneralTimerEvents, False);               \
   /* Register on PhoneCall event, without pending Event.*/                                     \
   EVHD_vRegister(EV_DPOOL_Always_WIM_stPhoneCallKey_WIM_vDoHmiEvents, False);                  \
   /* Register on timer event, without pending Event.*/                                         \
   EVHD_vRegister(EV_TIM_WIM_TimerVanTrackingStatusSuppress_WIM_vDoGeneralTimerEvents, False);  \
   /* Register on timer event, without pending Event.*/                                         \
   EVHD_vRegister(EV_TIM_WIM_TimerFreqCollWarn_WIM_vDoGeneralTimerEvents, False);               \
   /* Register on timer event, without pending Event.*/                                         \
   EVHD_vRegister(EV_TIM_WIM_TimerFreqContWarn_WIM_vDoGeneralTimerEvents, False)
/*
* Description: Unregister all Events WIM owns by EVHD
*/
#define WIM__vEvhdDeregisterEvents()                                                               \
   /* Deregister ICOM communication Event. No more information on incomming Data */                \
   EVHD_vDeregister(EV_DPOOL_Always_WIM_u32IcomDataGc_QueueGC_to_AC_WIM_vDoDpoolEvents);           \
   /* Deregister ICOM communication Event. No more information on incomming Data */                \
   EVHD_vDeregister(EV_DPOOL_OnChange_ICBWMDL_u32DynAreaHilId_WIM_vDoDpoolEvents);                 \
   /* Deregister ICOM communication Event. No more information on incomming Data */                \
   EVHD_vDeregister(EV_DPOOL_OnChange_WIMMDL_u32SlackHilId_WIM_vDoDpoolEvents);                    \
   /* Deregister ICOM communication Event. No more information on incomming Data */                \
   EVHD_vDeregister(EV_DPOOL_Always_WIM_u32IcomDataAc_QueueAC_to_GC_WIM_vDoDpoolEvents);           \
   /* Deregister on HMI-API-Feedback Event for Warning displayed, with pending Event.*/            \
   EVHD_vDeregister(EV_DPOOL_Always_WIM_stHmiFeedback_WIM_vDoHmiEvents);                           \
   /* Deregister on HMI-API-Feedback Event for Warning cancelleded */                              \
   EVHD_vDeregister(EV_DPOOL_Always_WIM_u16CanceledWarning_WIM_vDoHmiEvents);                      \
   /* Deregister on HMI-API-Feedback Event for slack displayed, with pending Event.*/              \
   EVHD_vDeregister(EV_DPOOL_Always_WIM_stHmiFeedbackSlack_WIM_vDoHmiEvents);                      \
   /* Deregister on HMI-API-Feedback Event for slack cancelleded */                                \
   EVHD_vDeregister(EV_DPOOL_Always_WIM_u16CanceledSlack_WIM_vDoHmiEvents);                        \
   /* Deregister on HMI-API-Feedback Event for Key-Handling, with pending Event.*/                 \
   EVHD_vDeregister(EV_DPOOL_Always_WIM_u16SuppressedWarning_WIM_vDoHmiEvents);                    \
   /* Deregister on HMI-API-Feedback Event for Key-Handling, with pending Event.*/                 \
   EVHD_vDeregister(EV_DPOOL_Always_WIM_stKeyEvent_WIM_vDoHmiEvents);                              \
   /* Deregister on HMI-API-MenuFaultMem Event for Reset-Handling, without pending Event.*/        \
   EVHD_vDeregister(EV_DPOOL_Always_WIM_u8FaultMemEvReset_WIM_vDoHmiEvents);                       \
   /* Deregister on HMI-API-MenuFaultMem Event for Navigation-Handling, without pending Event.*/   \
   EVHD_vDeregister(EV_DPOOL_Always_WIM_u8FaultMemEvPrevNext_WIM_vDoHmiEvents);                    \
   /* Deregister on HMI-API-DisplayOn Event, without pending Event.*/                              \
   EVHD_vDeregister(EV_DPOOL_OnChange_WIM_boDisplayOn_WIM_vDoHmiEvents);                           \
   /* Deregister on ICOM State Change Event, without pending Event.*/                              \
   EVHD_vDeregister(EV_DPOOL_OnChange_ICTP_enConStatus_WIM_vDoDpoolEvents);                        \
   /* Deregister on CSP convertible top state change event, without pending Event.*/               \
   EVHD_vDeregister(EV_DPOOL_OnChange_CSP_u8StateConvertibleTop_WIM_vDoDpoolEvents);               \
   /* Deregister on RES_Sound on notificiation.*/                                                  \
   EVHD_vDeregister(EV_ChangeNotificSMSRES_Sound_WIM_vDoGeneralEvents);                            \
   /* Deregister on RES_Audio_HW on notificiation.*/                                               \
   EVHD_vDeregister(EV_ChangeNotificSMSRES_Audio_HW_WIM_vDoGeneralEvents);                         \
   /* Deregister on Hybrid state change event, without pending Event.*/                            \
   EVHD_vDeregister(EV_DPOOL_OnChange_HYHLPOW_stModelDataAC_WIM_vDoDpoolEvents);                   \
   /* Deregister on timer event */                                                                 \
   EVHD_vDeregister(EV_TIM_WIM_HilBreakTimer_WIM_vDoGeneralTimerEvents);                           \
   /* Deregister on timer event */                                                                 \
   EVHD_vDeregister(EV_TIM_WIM_TimerAcuTDElapsed_WIM_vDoGeneralTimerEvents);                       \
   /* Deregister on PhoneCall event */                                                             \
   EVHD_vDeregister(EV_DPOOL_Always_WIM_stPhoneCallKey_WIM_vDoHmiEvents);                          \
   /* Deregister on timer event */                                                                 \
   EVHD_vDeregister(EV_TIM_WIM_TimerVanTrackingStatusSuppress_WIM_vDoGeneralTimerEvents);          \
   /* Register on timer event, without pending Event.*/                                            \
   EVHD_vDeregister(EV_TIM_WIM_TimerFreqCollWarn_WIM_vDoGeneralTimerEvents);                       \
   /* Register on timer event, without pending Event.*/                                            \
   EVHD_vDeregister(EV_TIM_WIM_TimerFreqContWarn_WIM_vDoGeneralTimerEvents)
/**
* Description: Maximum number of consecutve reads from ICOM queue.
*/
#define WIM__nMaxNumRetries 20

/****************************
* HMI-Messages
*****************************/
#define WIM_mSendMsg_MsgID_ScM_CancelDayNightAnim() HMI::WAS::DisplayController::PostMessage(HMI::WRS::MsgID_ScM_CancelDayNightAnim, HMI::WCS::DIRECT_MESSAGE, 0)
#define WIM__nAPIF_IC_Disp_Req (0x01)  /* Bit mask for APIF_u8DisplayRequest, is set if IC display is on */
#define WIM__mThrowHMIError(xErrorParam) WES_ThrowError((xErrorParam), 0)

/****************************
* RUN-TIME MEASURE
*****************************/
#define WIM__nRtmOff            1  /* runtime measure disabled */
#define WIM__nRtmInitActive     2  /* WIM_vInitActive          */
#define WIM__nRtmDeinitActive   3  /* WIM_vDeinitActive        */
#define WIM__nRtmCheckFunctions 4  /* WIM__vReqCtrl25ms        */
#define WIM__nRtmSchedulePrio   5  /* WIM__vSchedulePrioCheck  */
#define WIM__nEnableRTM_Cfg     WIM__nRtmOff

/*
* Description: Runtime measurement output on P84 which is Ac21 on sw-board
*              Define should be set to values above to enable RTM
*/
#if (WIM__nEnableRTM_Cfg != WIM__nRtmOff)
#warning "WIM: Run-time measure enabled!"
#endif

/*
* Description: configure port and set port pin to Hi-level
*/
#define WIM__mStartRtm()   \
   NEC_vSetPM17_4(0);      \
   NEC_vSetPMC17_4(0);     \
   NEC_vSetP17_4(1)

/*
* Description: set port pin to Lo-level
*/
#define WIM__mStopRtm()    \
   NEC_vSetP17_4(0)

/*
* End of Check if information is already included
*/
#endif                                  /* ifndef WIM1C1_H                 */
/***************************************************************************
* EOF: WIM1c1.h
****************************************************************************/
