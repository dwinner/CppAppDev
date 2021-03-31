#ifndef WIM__TYPES_H
#define WIM__TYPES_H
/******************************************************************************
*=====================    Copyright by Continental AG    ======================
*******************************************************************************
* Titel        : WIM__Types.h
*
* Description  : Package global types and constants
*                Contains definitions of types and enumerations which are class 
*                independent and used package global.
*
* Responsible  : L.Gruenewald, Schleissheimer GmbH
*
* Guidelines   : SMK 3.3  
*
* Template name: OOLite Codefile, Revision 1.0
*
* CASE-Tool    : Together Controlcenter, Version 6.2
*
* Revision List: (Will be filled by PVCS)
* Archive: $Log: WIM__Types.h  $
* Archive: Revision 1.1.2.6 2015/02/27 11:06:23CET Wenske-EXT, Martin (uidj8453) 
* Archive: DC MR 45940 : BR213, E009.2/AC, invalid HIL-ID stored to WEM (WDM 16578)
* Archive: Revision 1.1.2.5 2014/02/10 13:28:59CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 38117 : WIM/AC : Implement new scheduling and state handling for acoustic part
* Archive: DC MR 38109 : 213/AC-HL: Implementation of preL2 into SW frame
* Archive: Revision 1.1.2.4 2013/09/17 13:11:50CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 34947: prevent PF3 compiler warnings
* Archive: DC MR 34940: BR213, WIM: Acoustic of door warning shall not be retriggered by another door
* Archive: DC MR 34883: WIM: Persistent storage of warn states for wake-IC warnings
* Archive: Revision 1.1.2.3 2013/05/17 13:46:11CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 33414: BR213/AC, E004, WIM: Takeover of the latest changes from BR222/BR205
* Archive: Revision 1.1.2.2 2013/01/12 16:43:11CET Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3/project.pj
* Archive: Revision 1.9 2013/01/12 16:43:11CET Immel-EXT, Marc (uid37561) 
* Archive: DC MR 31032: BR205: Overtake HMI components for flashing (HMI synchronisation) from IC222
* Archive: DC MR 30978: BR205, E011/GC, WIM: Remove exception raising if HMI reports a canceled warning
* Archive: DC MR 30976: BR205, E011/GC, WIM: Warning disappears before display is off
* Archive: DC MR 25690: W205IC-GC TSA: Prevent popup warning from being displayed when FAS menu is active (ÄLP2802)
* Archive: Revision 1.8 2012/06/13 16:44:40CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 26329: W222, E007/GC, WIM: Change of Prio1Mute and Lowering times - ÄLP2873
* Archive: DC MR 25901: W222, E007/AC, WIM: Change of Prio1Mute and Lowering times - ÄLP2873
* 
*    Rev 1.7   Apr 20 2012 15:19:38   SCHL_Dirk.Gottwalles
* DC MR 25586: WDM21151/34246/35637: SBW/WIM Acoustic corrections
* DC MR 24871: W222, E007/AC, WIM: Implement changes from Review ORM2907
* DC MR 25146: W222, E007/GC, WIM: Priorities for roll handling - WDM35385
* DC MR 25141: W222, E007/GC, WIM: SBW/WIM Acoustic corrections - WDM21151, WDM34246
* Archive: Revision 1.5 2012/04/04 15:30:26CEST 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: DC MR 24870: W222, E007/GC, WIM: Implement changes from Review ORM2907
* Archive: DC MR 25007: W222, E007/GC, WIM: Displacement of handling messages - WDM20280
* Archive: DC MR 25041: Do not specify message propagation in message description files
* Archive: DC MR 25095: W222, E007/GC, WIM: Improvement of Timer accuracy for display role - WDM 25704
* Archive: DC MR 25034: Reduction of lag times in case of vehicle locked
* Archive: DC MR 25393: W222, E007/GC, WIM: No cancel of interval acoustic - WDM31269, ÄLP2895
* Archive: Revision 1.4 2012/01/13 11:44:42CET 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: DC MR 24746: BR222 E7.1: Implementation of L3 MDB, WDB for E7.1
* Archive: DC MR 24995: IC222 GC: HMI Synchronization: Clock generation/Basic Mechanisms
* Archive: DC MR 24327: W222, E007/GC, WIM: Implement changes from Review ORM3245, ORM3314
* 
*    Rev 1.5   Jan 13 2012 16:18:56   SCHL_Dirk.Gottwalles
* DC MR 24093: W222, E007/GC, WIM: Acoustic warning does not block display - WDM20499
* DC MR 23683: W222, E007/GC, WIM: Sync acoustic is cancelled by async acoustic WDM21143
* DC MR 24088: W222, E007/GC, WIM: Warning blocks display WDM22837, WDM23219
* DC MR 24089: W222,E007,AC, WIM: New configuration values Chauffeur_Avl and ShiftStyle_Variant
* DC MR 24343: W222, E007/AC, WIM: Patch for 0x2000BC and 0x2000C1 (Country coding), WDM23191
* 
*    Rev 1.4   Dec 02 2011 14:50:02   SCHL_Dirk.Gottwalles
* DC MR 23223: W222, E007/AC: Warnung Parkbremse 0x2001A8 ÄLP2607
* DC MR 23256: W222GC:E006 new volume interface
* DC MR 23803: Applications should send global direct messages
* DC MR 22621: BR222/E007/GC: HIL: DisplayColor
* 
*    Rev 1.3   Aug 12 2011 16:39:36   SCHL_Dirk.Gottwalles
* DC MR 22652: W222, E006/AC, SCS: Remove warning management
* DC MR 22655: W222, E006/AC, WIM: Implmentation of complex key handling for warnings
* DC MR 22263: W222, E006/GC, WIM: Remove of unused sound Ids
* DC MR 22549: E006/GC: HIL: Get acoustics status indication for warnings
* DC MR 22686: Implementation of L3 Menu, Warn DB for E006
* DC MR 22733: W222, E006/GC, WIM: Implementation of complex key handling for warnings
* DC MR 21544: E006/GC: HIL: Get TPOL Menu HIL-ID and WIM-HIL-ID
* DC MR 22749: Integration of ARTEMMIS 3.2
* 
*    Rev 1.2   Nov 19 2010 16:04:18   SCHL_Dirk.Gottwalles
* DC MR21122 BR222: WIM reaction at wakeupreq.
* DC MR21302 BR222/AC: Optimierung Aufruf Checkfunktion WIM
* DC MR20423 W222: WIM new acoustics requirements
* DC MR21177 Implementation of first WarnDB for E003
* DC MR21336 WIM: Using Enumeration Symbols for State/Widget Mapping
* 
*    Rev 1.1   Jun 11 2010 14:01:08   SCHL_Thomas.Godemann
* DC MR20480 AC, Startup MR for Modul WIM in E001
* DC MR20481 GC, Startup MR for Modul WIM in E001
* 
*    Rev 1.0   Jun 07 2010 13:20:26   SCHL_Thomas.Godemann
* Initial revision.
* 
* --------------------------------------------------------------------------
* Date      | Author | Reason     | Change
* --------------------------------------------------------------------------
* 10-06-03    LarGru   MR20480      Initial revision for W222
*                      MR20481      Initial revision for W222
*
*******************************************************************************/

#ifdef QAC_Analysis
#pragma PRQA_MESSAGES_OFF 2300, 2426
#endif /* QAC_Analysis */

/******************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*******************************************************************************/

/* System-headerfiles */
#include "cdef.h"

/* Own headerfiles */
#include "WIM__TimerHandler.h"
/******************************************************************************
*  Definition of Package global, but Package internal Macros, 
*  Enumerations, Types .. for use in a certain (sub)system.
*******************************************************************************/

/****************************
* PACKAGE GLOBAL DATA TYPES 
*****************************/

/**                                      
* defines an invalid HIL ID  
*/
#define WIM__nInvalidHilId (0x20000000 | (WIM_nenInvalidMsg << 8))

/**
* Enumeration of all (internal) state handler events
*/
typedef enum
{
   WIM__nRegister, /* message has been registered                  */
   WIM__nWakeIC, /* message should wake up the display           */
   WIM__nRetrigger, /* message has been registered/retriggered      */
   WIM__nCancel, /* message has been canceled                    */
   WIM__nDelete, /* message has been deleted                     */
   WIM__nDspRequest, /* display has been requested for message       */
   WIM__nDspAssign, /* display has been assigned to message         */
   WIM__nDspCancel, /* display has been withdrawn from message      */
   WIM__nDspSuppr, /* display has been suppressed                  */
   WIM__nAcuAssign, /* acoustic has been assigned to message        */
   WIM__nAcuAssignTD, /* tone delay is inserted                       */
   WIM__nAcuDelayElapsed, /* tone delay is elapsed                        */
   WIM__nAcuCancel, /* acoustic has been withdrawn from message     */
   WIM__nTmrDspModal, /* display timer has elapsed (modal phase)      */
   WIM__nTmrDspNormal, /* display timer has elapsed (normal phase)     */
   WIM__nTmrHdlExpired, /* handling message has become invalid          */
   WIM__nManuQuitOk, /* message has been manually confirmed (Ok)     */
   WIM__nManuQuitBack, /* message has been manually confirmed (Back)   */
   WIM__nPreConfirmation, /* message has been manually pre confirmed (Ok) */
   WIM__nConfirmation, /* pre confirmed message has been acknowledged  */
   WIM__nAcuTerminated, /* time limeted acoustic has been finished      */
   WIM__nAbortWait, /* abort waiting handling if replaced by new    */
   WIM__nAcuRetrigger, /* acoustic of message shall be restarted       */
   WIM__nAcuStop, /* acoustic of message shall be stopped         */
   WIM__nDspRetrigger, /* Retrigger Display without retriggering sound */
   WIM__nNoOfStateEvents, /* end of state events                          */
   WIM__nInit, /* initialisation event (request control -> ChkFcts)       */
   WIM__nDeinit, /* deinitialisation event (request control -> ChkFcts)     */
   WIM__nCyclic, /* cyclic check event (request control -> ChkFcts)         */
   WIM__nRetriggerEvent /* external event based check (request control -> ChkFcts) */
} WIM__tenEventIntern;

/**
* Enumeration of acoustic states for scheduling
*/
typedef enum
{
   WIM__nAcuStateInactive = 0x00, /* no acoustic request              				    */
   WIM__nAcuStateWaiting = 0x01, /* waiting for acoustic channel    				    */
   WIM__nAcuStateWaitDsp = 0x02, /* waiting for display part of sync message       */
   WIM__nAcuStateToneDelay = 0x03, /* waiting for tone delay timer			          */
   WIM__nAcuStatePlaying = 0x04, /* a message is playing now							    */
   WIM__nAcuStateWaitForTerm = 0x05, /* a message was cancelled or deleted */
   WIM__nAcuStateTerm = 0x06, /* a single acoustic is terminated or cancelled   */
   WIM__nAcuStateAutoQuit = 0x07, /* a message was terminated, cancelled or deleted */
   WIM__nNoOfStatesAcu /* ---------------------------------------------- */
} WIM__tenAcuState;

/**
* Enumeration of acoustic qualifiers
*/
typedef enum
{
   WIM__nAcuReleased = 0x00, /* no acoustic request              */
   WIM__nAcuRequested = 0x01, /* acoustic request active          */
   WIM__nAcuSyncUrgent = 0x02, /* synch. acoustics, urgent flag set*/
   WIM__nAcuTdElapsed = 0x04, /* acoustic tone delay elapsed      */
   WIM__nAcuWaitForTerm = 0x08, /* wait for acoustic ends           */
   WIM__nNoOfQualifiersAcu /*------------------------------------------*/
} WIM__tenAcuQualifier;

/**
* type definition for check-functions
* The event parameter can have the following meaning:
* - WIM__nInit:   Initialisation of timers, states etc., called once at start
* - WIM__nDeinit: Deinitialisation of timers etc., called once at end
* - WIM__nCyclic: Cyclic call used for condition check
*/
typedef void (*WIM__tvCheckFct)(WIM__tenEventIntern);

/**
* structure containing references to all check functions and HIL-ID
*/
typedef struct
{
   /**
   * HIL-ID of Msg given by WarnDb
   * @range  0x0 - 0xffffffff
   * @values ---
   */
   uint32 u32HilId;

   /**
   * Check function pointer, called from request control in a predefined interval
   * @range  function pointer address
   * @values valid function pointer or NULL if unused
   */
   WIM__tvCheckFct pvCheck;
} WIM__tstMsgCheck;


/**
* Enumeration of message types (classes)
*/
typedef enum
{
   WIM__nWarning, /* warning message                           */
   WIM__nHandling, /* handling message (reaction on driver hdl.)*/
   WIM__nWarningPtnr, /* warning with partner message              */
   WIM__nHandlingPtnr, /* handling message with partner message     */
   WIM__nAcoustic, /* acoustic message                          */
   WIM__nNoOfMsgTypes /* ----------------------------------------- */
} WIM__tenMsgType;


/**
* Enumeration of display qualifiers for scheduling
*/
typedef enum
{
   WIM__nNoRequest = 0x00, /* no display request                  */
   WIM__nNoQualifier = 0x01, /* roller-mode/permanent               */
   WIM__nQualNew = 0x02, /* warning: normal message             */
   WIM__nQualUrgt = 0x04, /* warning: urgent message             */
   WIM__nQualHdl = 0x08 /* handling: always urgent             */
} WIM__tenDspQualifier;


/**
* Enumeration of wake IC qualifiers/states for scheduling
*/
typedef enum
{
   WIM__nNoWakeup = 0x00, /* no Wakeup               */
   WIM__nWakeup = 0x01, /* Wakeup                  */
   WIM__nWakeKeepActive = 0x02, /* Wakeup and keep active  */
   WIM__nKeepActive = 0x03, /* Keep active             */
   WIM__nNoOfStatesWakeIc /*------------------------------------------*/
} WIM__tenWakeIcQualifier;

/**
* Enumeration of display message states.
* If this enumeration is changed, the size of the Bitfiled 
* biDisplayState must be checked and adapted.
*/
typedef enum
{
   WIM__nInactive, /* inactive, no request                     */
   WIM__nWaiting, /* active, waiting for display              */
   WIM__nWaitForDsp, /* active, display requested, waiting for feedback from HMI */
   WIM__nModalPhase, /* displayed (t: 0..500ms)                  */
   WIM__nNormalPhase, /* displayed (t: 500..5000ms)               */
   WIM__nContinousPhase, /* displayed (t: > 5000ms)                  */
   WIM__nManuQuit, /* manually confirmed                       */
   WIM__nAutoQuit, /* canceled/deleted during display          */
   WIM__nPreConfirmed, /* manually confirmed but waiting for ack   */
   WIM__nNoOfDspStatesMsg /* number of states                         */
} WIM__tenDspState;


/**
* Description: types for key evaluation, can be extended to implement special
* behaviour such as switch functions on/off etc.
*/
typedef enum
{
   WIM__nNone, /* no key evaluation                      */
   WIM__nManuQuitKey, /* key evaluation for manual confirmation */
   WIM__nDiffManQuit, /* special handling for APA disclaimer    */
   /* -------------------------------------------------------------------- */
   WIM__nNoOfKeyCbTypes /* number of types                        */
} WIM__tenKeyCbType;

/**
* structure containing generic message attributes and referneces to all type-specific
* data structures
*/
typedef struct
{
   /**
   * priority level as defined in WarnDb
   * @range  0..255
   * @values 1..4
   */
   uint8 u8Prio;

   /**
   * First message of priority level
   * @range  defined in enum WIM_tenMsg
   * @values see WIM_tenMsg
   */
   WIM_tenMsg enLevelStart;

   /**
   * Last message of priority level
   * @range  defined in enum WIM_tenMsg
   * @values see WIM_tenMsg
   */
   WIM_tenMsg enLevelEnd;
} WIM__tstMsgPrio;


/**
* structure containing generic message attributes and referneces to all type-specific
* data structures
*/
typedef struct
{
   /**
   * Type of message (message class)
   * @range  defined in enum WIM__tenMsgType
   * @values WIM__nWarning, WIM__nHandling, WIM__nWarningPtnr, WIM__nHandlingPtnr, WIM__nAcoustic
   */
   WIM__tenMsgType enMsgType;

   /**
   * Type of message (message class)
   * @range  bool
   * @values True, False
   */
   bool boSingleLine;

   /**
   * Type of key evaluation (handled by WIM__KeyControl)
   * @range  as defined in enum WIM__tenKeyCbType
   * @values WIM__nManuQuitKey, WIM__nNone
   */
   WIM__tenKeyCbType enKeyCbType;

   /**
   * HIL-ID of Msg
   * @range  uint32
   * @values possible HilId Values 
   */
   uint32 u32HilId;

   /**
   * Time slack is displayed
   * @range  uint16
   * @values 0 - 65535 ms 
   */
   uint16 u16SlackDispTime;

   /**
   * State handler attributes, controlling the behaviour of the message
   * @range  void pointer (pointing to type-specific structure)
   * @values pointer to WIM__tstStateAttr___ 
   */
   const void* pvStateAttr;

   /**
   * Acoustic attributes, describing the acoustic properties of the message
   * @range  pointer to WIM__tstViewAttrAcu
   * @values pointer to WIM__tstViewAttr___ 
   */
   const WIM__tstViewAttrAcu* pvAcousticAttr;
} WIM__tstMsgProperty;


/**
* pointer to KOMBIEXTERN handler function (section .WIMAttribute)
*/
typedef void (*pvHandleExtCondition)(WIM_tenExtEvtFunction, uint8, WIM__tenEventIntern);

/**                                      
* Structure describing all mapped data structures of the warning partition.
* The structure is located at a fixed address in the warning partition.
* Access to the data of the warning partition is encapsulated by this struct
* and the following set of access macros.
*/
typedef struct
{
   /**
   * number of generated messages (section .WIMAttribute)
   */
   const WIM_tenMsg enNoOfMsgs;

   /**
   * enum of last generated message (section .WIMAttribute)
   */
   const WIM_tenMsg enLastMsg;

   /**
   * pointer to timer configuration (section .WIMAttribute)
   */
   const WIM__tstTimerConfig* pastTimerConfig;

   /**
   * number of configured timers (section .WIMAttribute)
   */
   const uint16 u16NoOfTimers;

   /**
   * pointer to KOMBIEXTERN handler function (section .WIMAttribute)
   */
   pvHandleExtCondition pvHandleExtCondition;

   /**
   * pointer to message property table (section .WIMTable)
   */
   const WIM__tstMsgCheck* pastMsgCheckTable;

   /**
   * number of KOMBIINTERN container entries (section .WIMAttribute)
   */
   const uint16 u16KombiIntCnt;

   /**
   * pointer to "RealTime" check container (section .WIMAttribute)
   */
   const WIM_tenMsg* paenRealTimeCont;

   /**
   * pointer to "Kl15Off" check container (section .WIMAttribute)
   */
   const WIM_tenMsg* paenKl15OffCont;

   /**
   * pointer to "AdBlueDispReq" check container (section .WIMAttribute)
   */
   const WIM_tenMsg* paenAdBlueCont;

   /**
   * pointer to KOMBIINTERN/KOMBIEXTERN condition container (section .WIMAttribute)
   */
   const WIM_tenMsg* paenCheckCondCont;

   /**
   * pointer to KOMBIINTERN HIL Id container (section .WIMAttribute)
   */
   const uint32* pau32KombiIntCont;

   /**
   * pointer to TurnOnDelay handler function (section .WIMAttribute)
   */
   void (*pvHandleTurnOnDelay)(void);

   /**
   * pointer to WakeIC warnings container 
   */
   const WIM_tenMsg* paenWakeIcCont;

   /**
   * pointer to WakeIC warnings container 
   */
   const uint16 u16NoOfWakeIcMsgs;

   /**
   * number of message priority levels (section .WIMAttribute)
   */
   const uint8 u8NoOfPrioLevels;

   /**
   * pointer to message priority table (section .WIMAttribute)
   */
   const WIM__tstMsgPrio* pastPrioTable;

   /**
   * pointer to message property table (section .WIMTable)
   */
   const WIM__tstMsgProperty* pastMsgPropertyTable;
} WIM__tstDataHdr;

/**
* Configuration structure of display elements
*/
typedef struct
{
   WIM_tenDisplColor enColor; /* Color of the displayed warnings according to WarnDB */
} WIM__tstDisplayConfig;

/**                                      
* The structure WIM__stDataHdr is located at a fixed address .WIMHeader
*/
extern const WIM__tstDataHdr WIM__stDataHdr;

/**                                      
* access macros for mapped data (WIMGEN) in warning partition
*/
#define WIM__mGetNoOfMessages       (WIM__stDataHdr.enNoOfMsgs)
#define WIM__mGetLastMsg            (WIM__stDataHdr.enLastMsg)
#define WIM__mGetTimerConfig        (WIM__stDataHdr.pastTimerConfig)
#define WIM__mGetNoOfTimers         (WIM__stDataHdr.u16NoOfTimers)
#define WIM__mGetExtConditionFctPtr (WIM__stDataHdr.pvHandleExtCondition)
#define WIM__mGetMsgCheckTable      (WIM__stDataHdr.pastMsgCheckTable)
#define WIM__mGetKombiInternMsgCnt  (WIM__stDataHdr.u16KombiIntCnt)
#define WIM__mGetRealTimeContainer  (WIM__stDataHdr.paenRealTimeCont)
#define WIM__mGetKl15OffContainer   (WIM__stDataHdr.paenKl15OffCont)
#define WIM__mGetAdBlueContainer    (WIM__stDataHdr.paenAdBlueCont)
#define WIM__mGetCheckCondContainer (WIM__stDataHdr.paenCheckCondCont)
#define WIM__mGetKombiIntContainer  (WIM__stDataHdr.pau32KombiIntCont)
#define WIM__mGetTurnOnDelayFctPtr  (WIM__stDataHdr.pvHandleTurnOnDelay)
#define WIM__mGetWakeIcContainer    (WIM__stDataHdr.paenWakeIcWarningsCont)
#define WIM__mGetNoOfWakeIcMessages (WIM__stDataHdr.u16NoOfWakeIcMsgs)
#define WIM__mGetNoOfPrioLevels     (WIM__stDataHdr.u8NoOfPrioLevels)
#define WIM__mGetPrioTable          (WIM__stDataHdr.pastPrioTable)
#define WIM__mGetMsgPropertyTable   (WIM__stDataHdr.pastMsgPropertyTable)

/*******************
* ACCESS MACROS 
********************/

/**
* Returns the message type class for the given message 
*/
#define WIM__menGetMsgType(enMsg) \
      (WIM__mGetMsgPropertyTable[(enMsg)].enMsgType)

/**
* Returns the message attribute slack (true or not)
* for the given message 
*/
#define WIM__menGetSlackMsgType(enMsg) \
      (WIM__mGetMsgPropertyTable[(enMsg)].boSingleLine)

/**
* Macro to retrieve the view type
*/
#define WIM__menGetViewType(enMsg) \
      (WIM__mGetMsgPropertyTable[enMsg].enViewType)

   /**
   * Macro to retrieve the type of key event evaluation
   */
   #define WIM__menGetKeyCbType(enMsg) \
      (WIM__mGetMsgPropertyTable[enMsg].enKeyCbType)
/**                                
* defines highest priority level  
*/
#define WIM__mGetHighestPrioLevel (WIM__mGetPrioTable[0].u8Prio)


/**                                                                 
* defines lowest priority level    
*/
#define WIM__mGetLowestPrioLevel (WIM__mGetPrioTable[WIM__mGetNoOfPrioLevels - 1].u8Prio)


/**                                                                                       
* defines highest priority level  
*/
#define WIM__mGetHighestPrioMessage (WIM__mGetPrioTable[0].enLevelStart)


/**                                               
* defines lowest priority message    
*/
#define WIM__mGetLowestPrioMessage (WIM__mGetPrioTable[WIM__mGetNoOfPrioLevels - 1].enLevelEnd)


/**
* Display data configuration table
*/
extern const WIM__tstDisplayConfig WIM__astDisplayConfiguration[];

/* Definitions for Electrical step board display bit-access */
#define WIM__nElStepMaskFl 0x01   /* Mask for front left  */
#define WIM__nElStepMaskFr 0x02   /* Mask for front right */
#define WIM__nElStepMaskRl 0x04   /* Mask for rear left  */
#define WIM__nElStepMaskRr 0x08   /* Mask for rear right */

/*****************************************
    * COMMON DEFINES FOR COMPLEX WARNINGS *
    *****************************************/
/**
* HIL Id of Stepboard not moved out
*/
#define WIM__nElecStepboardMovedOut 0x20F3B100

/**
* HIL Id's of Stepboard not moved in
*/
#define WIM__nElecStepboardMovedIn 0x20F3B200
#define WIM__nElecStepboardMovedIn_Acust1 0x20F3C900

/**
* HIL Id of ALDW Warnton
*/
#define WIM__nHilIdALDWWarnton 0x20F3C500

/**
 * Setting up the display state for electrical state board
 * @param pu8ElStepBoardDisplayState value for setting up the bits for electrical step board display state
 * @param u8EStep_FL_Flt Front left electrical step board value
 * @param u8EStep_FR_Flt Front right electrical step board value
 * @param u8EStep_RL_Flt Rear left electrical step board value
 * @param u8EStep_RR_Flt Rear right electrical step board value
 */
inline void WIM__vSetUpElStepDisplayState(uint8* pu8ElStepBoardDisplayState,
   uint8 u8EStep_FL_Flt, uint8 u8EStep_FR_Flt, uint8 u8EStep_RL_Flt, uint8 u8EStep_RR_Flt)
{
   if (u8EStep_FL_Flt == 1)   
      *pu8ElStepBoardDisplayState |= 0xFF & WIM__nElStepMaskFl;   
   else if (u8EStep_FL_Flt == 0)   
      *pu8ElStepBoardDisplayState &= 0xFF & ~WIM__nElStepMaskFl;   

   if (u8EStep_FR_Flt == 1)   
      *pu8ElStepBoardDisplayState |= 0xFF & WIM__nElStepMaskFr;   
   else if (u8EStep_FR_Flt == 0)   
      *pu8ElStepBoardDisplayState &= 0xFF & ~WIM__nElStepMaskFr;   

   if (u8EStep_RL_Flt == 1)   
      *pu8ElStepBoardDisplayState |= 0xFF & WIM__nElStepMaskRl;   
   else if (u8EStep_RL_Flt == 0)   
      *pu8ElStepBoardDisplayState &= 0xFF & ~WIM__nElStepMaskRl;   

   if (u8EStep_RR_Flt == 1)   
      *pu8ElStepBoardDisplayState |= 0xFF & WIM__nElStepMaskRr;   
   else if (u8EStep_RR_Flt == 0)   
      *pu8ElStepBoardDisplayState &= 0xFF & ~WIM__nElStepMaskRr;   
}

#endif /* WIM__TYPES_H */
