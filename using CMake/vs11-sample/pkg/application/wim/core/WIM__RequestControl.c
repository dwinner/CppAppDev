/******************************************************************************
*=====================    Copyright by Continental AG    ======================
*******************************************************************************
* Titel        : WIM__RequestControl.c
*
* Description  : Request control checks the conditions under which a message
*                will be activated or deactivated.
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
* Archive: $Log: WIM__RequestControl.c  $
* Archive: Revision 1.3.1.6 2014/07/29 18:35:02CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 41682 : WIM/AC: Prevent sporadic flicker of GC controlled complex warnings after Kl15ACC
* Archive: Revision 1.3.1.5 2014/03/21 12:18:24CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 39404 : 213-AC, WIM: Changes in CAN flag handling and persistent storage of Wake IC warning states
* Archive: Revision 1.3.1.4 2013/09/17 13:13:34CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 34947: prevent PF3 compiler warnings
* Archive: DC MR 34940: BR213, WIM: Acoustic of door warning shall not be retriggered by another door
* Archive: DC MR 34883: WIM: Persistent storage of warn states for wake-IC warnings
* Archive: Revision 1.3.1.3 2013/05/17 13:45:42CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 33414: BR213/AC, E004, WIM: Takeover of the latest changes from BR222/BR205
* Archive: Revision 1.3.1.2 2012/11/21 12:45:43CET Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3AC/project.pj
* Archive: Revision 1.2 2012/11/21 12:45:43CET Immel-EXT, Marc (uid37561) 
* Archive: Migration of WIM-AC from PVCS to MKS
* Archive: - used release: DC.SW.PAC.WIM_205IC_AC_COMMON_VarW.V01.00.pre17
* Archive: Revision 1.1 2010/11/18 19:03:48CET uid37556 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3AC/project.pj
*
*    Rev 1.6   Apr 20 2012 15:19:38   SCHL_Dirk.Gottwalles
* DC MR 25586: WDM21151/34246/35637: SBW/WIM Acoustic corrections
* DC MR 24871: W222, E007/AC, WIM: Implement changes from Review ORM2907
* DC MR 25146: W222, E007/GC, WIM: Priorities for roll handling - WDM35385
* DC MR 25141: W222, E007/GC, WIM: SBW/WIM Acoustic corrections - WDM21151, WDM34246
* 
*    Rev 1.5   Apr 05 2012 13:35:12   SCHL_Dirk.Gottwalles
* DC MR 24870: W222, E007/GC, WIM: Implement changes from Review ORM2907
* DC MR 25007: W222, E007/GC, WIM: Displacement of handling messages - WDM20280
* DC MR 25041: Do not specify message propagation in message description files
* DC MR 25095: W222, E007/GC, WIM: Improvement of Timer accuracy for display role - WDM 25704
* DC MR 25034: Reduction of lag times in case of vehicle locked
* DC MR 25393: W222, E007/GC, WIM: No cancel of interval acoustic - WDM31269, ÄLP2895
* DC MR 24871: W222, E007/AC, WIM: Implement changes from Review ORM2907
* 
*    Rev 1.4   Jan 13 2012 16:18:54   SCHL_Dirk.Gottwalles
* DC MR 24093: W222, E007/GC, WIM: Acoustic warning does not block display - WDM20499
* DC MR 23683: W222, E007/GC, WIM: Sync acoustic is cancelled by async acoustic WDM21143
* DC MR 24088: W222, E007/GC, WIM: Warning blocks display WDM22837, WDM23219
* DC MR 24089: W222,E007,AC, WIM: New configuration values Chauffeur_Avl and ShiftStyle_Variant
* DC MR 24343: W222, E007/AC, WIM: Patch for 0x2000BC and 0x2000C1 (Country coding), WDM23191
* 
*    Rev 1.3   Nov 19 2010 16:04:14   SCHL_Dirk.Gottwalles
* DC MR21122 BR222: WIM reaction at wakeupreq.
* DC MR21302 BR222/AC: Optimierung Aufruf Checkfunktion WIM
* DC MR20423 W222: WIM new acoustics requirements
* DC MR21177 Implementation of first WarnDB for E003
* DC MR21336 WIM: Using Enumeration Symbols for State/Widget Mapping
* 
*    Rev 1.2   Jun 25 2010 12:22:12   SCHL_Lars.Grünewald
* DC MR 20566  WIM222: WIM Part2 for E001
* DC MR 20629 Configuration of Display Handler
* DC MR 20639 WIM: Adaption of HMI part for E001.1 
* DC MR 20620 Startup-MR for dynamical area manager (prio)
* DC MR 20661 Br222: WIM: ICOM Reinitialization
* DC MR 20662 Needed patches for WarnDB E001
* DC MR 20560 Implementation of first WarnDB for E001
* DC MR 20490 W222 E001: start up MR SFG
* 
*    Rev 1.1   Jun 11 2010 14:01:08   SCHL_Thomas.Godemann
* DC MR20480 AC, Startup MR for Modul WIM in E001
* DC MR20481 GC, Startup MR for Modul WIM in E001
* 
*    Rev 1.0   Jun 07 2010 13:19:48   SCHL_Thomas.Godemann
* Initial revision.
* 
* --------------------------------------------------------------------------
* Date      | Author | Reason     | Change
* --------------------------------------------------------------------------
* 10-06-03    LarGru   MR20480      Initial revision for W222
*
****************************************************************************/

/***************************************************************************
* HEADER-FILES (Only those that are needed in this file)
****************************************************************************/
/* System-headerfiles */
#include "cdef.h"

/* Foreign headerfiles */

/* Own headerfiles */
#include "WIM_c1.h"
#include "WIM__RequestControl.h"         /* own interface                     */

/******************************************************************************
* GLOBAL DEFINITIONS
*******************************************************************************/


/******************************************************************************
* FILE LOCAL DEFINITIONS
*******************************************************************************/

/**
* Macro to retrieve the check function pointer
*/
#define WIM__mpvGetCheckFct(enMsg) \
   (WIM__mGetMsgCheckTable[(enMsg)].pvCheck)

/**
* Flag, indicating whether request control is active or not
*/
static bool WIM__boRequestControlActive;

/******************************************************************************
* FILE LOCAL FUNCTION PROTOTYPES
*******************************************************************************/

static inline void WIM__vCallContainerFct(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/******************************************************************************
* FUNCTION DEFINITIONS
*******************************************************************************/

/**
* Helper function calling a container check-function
*   @return  void
*   @param   enMsg: ID of message, enEvt event (WIM__nInit, WIM__nDeinit, WIM__nCyclic, WIM__nRetriggerEvent) 
*   @author  T.Godemann, Schleissheimer GmbH 
*/
static inline void WIM__vCallContainerFct(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* valid msg identifier? */
          (enMsg < WIM__mGetNoOfMessages)
       /* check-function valid? */
       && (WIM__mpvGetCheckFct(enMsg) != NULL))
   {
      /* call check function */
      WIM__mpvGetCheckFct(enMsg)(enEvt);
   }
   else
   {
      /* call exception handler */
      WIM__vRaiseException(WIM_nErrConfig);
   }
}

/**
* Power-on initialisation of request control class
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vReqCtrlInit(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   WIM__boRequestControlActive = False;
   WIM__vInitStateFlagArrays(True);
   
}

/**
* start request control. Start the timers triggering the event task. In the 
* interval of these timers the check functions of the messages inside the
* check-containers are called.
* At start send to all check-functions the Init-event.
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vReqCtrlStart(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint16 u16Index;  /* loop variable */
   WIM_tenMsg enMsg; /* message identifier */
      
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* set active flag */
   WIM__boRequestControlActive = True;
   
   /* Special functions: WIM checked warn conditions or RetriggerOnEvent */
   WIM__vHandleSpecialChkFct(WIM__nInit);

   /*** send all check functions in all containers the Init-event */
   for (/* loop through all messages in the container */
        u16Index = 0; 
        WIM__mGetRealTimeContainer[u16Index] != WIM_nenInvalidMsg; 
        u16Index++)
   {
      enMsg = WIM__mGetRealTimeContainer[u16Index];
      WIM__vCallContainerFct(enMsg, WIM__nInit);
   }

   /* Enable real time check event */
   EVHD_vRegister(EV_WIM_nStartCheckFctCycle_WIM_vDoGeneralEvents, False);
}

/**
* stop request control. Cancel the timers triggering the event task. Send all
* Check-functions in all containers the Deinit event.
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vReqCtrlStop(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint16 u16Index;  /* loop variable */
   WIM_tenMsg enMsg; /* message identifier */
      
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/

   /* Disable real time check event */
   EVHD_vDeregister(EV_WIM_nStartCheckFctCycle_WIM_vDoGeneralEvents);

   /* clear active flag */
   WIM__boRequestControlActive = False;
   
   /*** send all check functions in all containers the Deinit-event */
   for (/* loop through all messages in the container */
        u16Index = 0; 
        WIM__mGetRealTimeContainer[u16Index] != WIM_nenInvalidMsg; 
        u16Index++)
   {
      enMsg = WIM__mGetRealTimeContainer[u16Index];
      WIM__vCallContainerFct(enMsg, WIM__nDeinit);
   }

   /* Special functions: WIM checked warn conditions or RetriggerOnEvent */
   WIM__vHandleSpecialChkFct(WIM__nDeinit);
}

/**
* call checkfunctions of all changed IC internal and external conditions
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vCheckIntExtConditionChanged(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint16 u16Index;  /* loop variable */
   WIM_tenMsg enMsg; /* message identifier */
      
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   for (/* loop through all messages in the container */
        u16Index = 0; 
        WIM__mGetCheckCondContainer[u16Index] != WIM_nenInvalidMsg; 
        u16Index++)
   {
      if (/* condition state changed? */
          WIM__boGetIntExtConditionCheck(u16Index))
      {
         enMsg = WIM__mGetCheckCondContainer[u16Index];
         WIM__vCallContainerFct(enMsg, WIM__nCyclic);
         WIM__vSetIntExtConditionCheck(u16Index, False);
      }
   }
}

/**
* Check function container handling. Check functions of all messages are
* called (25ms foreground) are called within this function. 
*   @return  void
*   @param   none
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
void WIM__vReqCtrl25ms(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint16 u16Index;  /* loop variable */
   WIM_tenMsg enMsg; /* message identifier */
      
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* only if activated */
       WIM__boRequestControlActive)
   {
      
      /* Special functions: WIM checked warn conditions or RetriggerOnEvent */
      WIM__vHandleSpecialChkFct(WIM__nCyclic);

      #if (WIM__nEnableRTM_Cfg == WIM__nRtmCheckFunctions)
      /* measure function run-time if enabled */
      WIM__mStartRtm();
      #endif

      /* loop through all messages in the container */
      for (u16Index = 0; 
           WIM__mGetRealTimeContainer[u16Index] != WIM_nenInvalidMsg; 
           u16Index++)
      {
         enMsg = WIM__mGetRealTimeContainer[u16Index];
         WIM__vCallContainerFct(enMsg, WIM__nCyclic);

         /* Interrupt the processing of the check functions in defined 
            intervalls to enable other tasks to get processing time */
         if(((u16Index+1) % WIM__nNumOfConsecutiveChecks) == 0)
         {
            /* Trigger a OS schedule */
            WIM__vOsSchedule();
         }
      }

      #if (WIM__nEnableRTM_Cfg == WIM__nRtmCheckFunctions)
      /* measure function run-time if enabled */
      WIM__mStopRtm();
      #endif

      /* check all IC internal/external condition changes */
      WIM__vCheckIntExtConditionChanged();
   }
}

/**
* RETRIGGER_ON_EVENT callback for event KL15Off 
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vReqCtrlRetriggerKL15Off(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint16 u16Index;                 /* loop variable                          */
   WIM_tenMsg enMsg;               /* ID of message                          */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   for (/* loop through all messages in the container */
        u16Index = 0; 
        WIM__mGetKl15OffContainer[u16Index] != WIM_nenInvalidMsg; 
        u16Index++)
   {
      enMsg = WIM__mGetKl15OffContainer[u16Index];  /* get message ID         */
      if (/* message is stored in FaultMemory */
          WIM__mboGetFaultMemFlag(enMsg))
      {
         /* call check-function with WIM__nRetriggerEvent */
         WIM__vCallContainerFct(enMsg, WIM__nRetriggerEvent);
      }
   }                                                       
}

/**
* RETRIGGER_ON_EVENT callback for event RTGR_ADBLUE 
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vReqCtrlRetriggerAdBlue(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint16 u16Index;                 /* loop variable                          */
   WIM_tenMsg enMsg;               /* ID of message                          */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   for (/* loop through all messages in the container */
        u16Index = 0; 
        WIM__mGetAdBlueContainer[u16Index] != WIM_nenInvalidMsg; 
        u16Index++)
   {
      enMsg = WIM__mGetAdBlueContainer[u16Index];   /* get message ID         */
      if (/* message is stored in FaultMemory */
          WIM__mboGetFaultMemFlag(enMsg))
      {
         /* call check-function with WIM__nRetriggerEvent */
         WIM__vCallContainerFct(enMsg, WIM__nRetriggerEvent);
      }
   }                                                       
}

/**
* WIM request internal interface 
* - Register a message if the message conditions and ground conditions are true
* - Retrigger a message if the message conditions and ground conditions are true
*   Retrigger is similar to register but has always effect if message has been
*   confirmed (independent from attributes) 
* - Cancel a message if the message ground conditions are no longer true.
* - Delete a message if the message conditions are no longer true oror the 
*   message deactivation condition is true.
* If a message is already active and Register is requested, the call is ignored.
* The same is True for cancel and delete. The behaviour of delete differs only
* in one point. If the message has a fault memory entry, this will be deleted
* if allowed by attribute configuration. A Delete following a Cancel will be
* ignored.
*   @return  void
*   @param   enMsg: message enum, enEvent: WIM_nRegister/WIM_nCancel/WIM_nDelete
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vRequest(WIM_tenMsg enMsg, WIM__tenEventIntern enEvent)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint32 u32Index = 0;  /* Index for WakeIC Messages */
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* check if message is valid */
       (enMsg < WIM__mGetNoOfMessages))
   {
      switch (enEvent)
      {
         case WIM__nRegister:
            if (/* not already registered? */
                !WIM__mboGetRegFlag(enMsg))
            {    
               /* send register event */
               WIM__vOnEvent_AC(enMsg, WIM__nRegister);
               u32Index = WIM__u32GetWakeICMsg(enMsg);
               if (   u32Index < WIM__nMaxWakeIcMsgCount
                   && WIM__boGetWakeICState(u32Index) == False )
               {  
                     /* send register event with wake IC */
                     WIM__vOnEvent_AC(enMsg, WIM__nWakeIC);
               }
            }
            break;
         case WIM__nRetrigger:
            /* send retrigger event */
            WIM__vOnEvent_AC(enMsg, WIM__nRetrigger);
            u32Index = WIM__u32GetWakeICMsg(enMsg);
            if (   u32Index < WIM__nMaxWakeIcMsgCount
                   && WIM__boGetWakeICState(u32Index) == False )
            {  
                  /* send register event with wake IC */
                  WIM__vOnEvent_AC(enMsg, WIM__nWakeIC);
            }
            break;
         case WIM__nCancel:
            if (/* message is registered? */
                WIM__mboGetRegFlag(enMsg))
            {
               /* send cancel event */
               WIM__vOnEvent_AC(enMsg, WIM__nCancel); 
            }
            else
            {
               u32Index = WIM__u32GetWakeICMsg(enMsg);
               /* if wake ic message, check if state is set */
               if (   u32Index < WIM__nMaxWakeIcMsgCount
                   && WIM__boGetWakeICState(u32Index))
               {
                  /* Delete WakeIc State Bit */
                  WIM__vSetWakeICState(u32Index, False);
               }
            }

            break;
         case WIM__nDelete:
            if (/* message is registered? */
                   (WIM__mboGetRegFlag(enMsg))
                /* or was Canceld before */
                || (WIM__mboGetCanceledFlag(enMsg)) )
            {
               /* send delete event */
               WIM__vOnEvent_AC(enMsg, WIM__nDelete); 
            }
            else
            {
                u32Index = WIM__u32GetWakeICMsg(enMsg);
               /* if wake ic message, check if state is set */
               if (   u32Index < WIM__nMaxWakeIcMsgCount
                   && WIM__boGetWakeICState(u32Index))
               {
                  /* Delete WakeIc State Bit */
                  WIM__vSetWakeICState(u32Index, False);
               }
            }           
            break;
         default:
            break;
      }
   } 
}
 
/**
* reset all internal state flags to zero
*   @return  void
*   @param   boResetAll: True - reset all flags, False: rest only subset
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vInitStateFlagArrays(bool boResetAll)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* Retrigger flag array (RETRIGGER_ON_EVENT) */
   memset(&(WIM__au8RetriggerFlags[0]), 0, WIM__nu8RetriggerByteCnt);
   /* Message-Timeout flag array [TIMEOUT(ID)] */
   memset(&(WIM__au8TimeoutFlags[0]), 0, WIM__nu8TimeoutByteCnt);
   /* Message-Timeout flag array [TIMEOUTKL15ONNOTENGSTART(ID)] */
   memset(&(WIM__au8TimeoutKl15OnNotEngStartFlags[0]), 0, WIM__nu8TimeoutKl15OnNotEngStartByteCnt);
   /* Message-Timeout flag array [TIMEOUTNOTENGSTART(ID)] */
   memset(&(WIM__au8TimeoutNotEngStartFlags[0]), 0, WIM__nu8TimeoutNotEngStartByteCnt);
   /* State of IC internal condition - flag array [KOMBIINTERN] */
   memset(&(WIM__au8IntCondStateFlags[0]), 0, WIM__nu8IntCondStateByteCnt);
   /* Retrigger of IC internal condition - flag array [KOMBIINTERN] */
   memset(&(WIM__au8IntExtCondRetrigFlags[0]), 0, WIM__nu8IntExtCondRetrigByteCnt);
   /* Re-Check of message with int/ext condition - flag array [KOMBIINTERN/KOMBIEXTERN] */
   memset(&(WIM__au8IntExtCondCheckFlags[0]), 0, WIM__nu8IntExtCondCheckByteCnt);
   if (/* reset EXTKI state flags too? */
       boResetAll)
   {
      /* State of IC external condition - flag array [KOMBIEXTERN] */
      memset(&(WIM__au8ExtCondStateFlags[0]), 0, WIM__nu8ExtCondStateByteCnt);
   }
}

/**
* helper function: get state of flag
*   @return  bool: State of flag: True, flag set, False otherwise
*   @param   uint8* pu8FlagArray: data array for flag check
*   @param   uint16 u16FlagIdx: index of flag to check
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boGetFlag(uint8* pu8FlagArray, uint16 u16FlagIdx)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint8 u8Mask;                    /* flag bit-mask                          */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* calculate mask */
   u8Mask = 1 << (u16FlagIdx % 8);
   /* return True, if bit is set */
   return ( (pu8FlagArray[u16FlagIdx / 8] & u8Mask) != 0 ); 
}

/**
* message timeouts: set state of timeout flag
*   @return  void
*   @param   uint8* pu8FlagArray: data array for flag check
*   @param   uint16 u16FlagIdx: index of flag to check
*   @param   bool boState: State to set True - set flag, False - clear flag
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vSetFlag(uint8* pu8FlagArray, uint16 u16FlagIdx, bool boState)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint8 u8Mask;                    /* flag bit-mask                          */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* calculate mask */
   u8Mask = 1 << (u16FlagIdx % 8);
   if (boState)
      pu8FlagArray[u16FlagIdx / 8] |= u8Mask;  /* set   */
   else
      pu8FlagArray[u16FlagIdx / 8] &= ~u8Mask; /* clear */
}


/**
* Handle IC internal conditions: set/clear event state flag and re-check 
* message 
*   @return  void
*   @param   u32HilId: HIL ID of the related message
*   @param   WIM__tenEventIntern enEvt: WIM__nRegister, WIM__nRetrigger, WIM__nDelete
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vHandleIntCondition_AC(uint32 u32HilId, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint16 u16Left  = 0;
   uint16 u16Right = WIM__mGetKombiInternMsgCnt - 1;
   uint16 u16Index;

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   
   if (/* check boundary conditions:
          at least one KOMBIINTERN message? */ 
          WIM__mGetKombiInternMsgCnt > 0  
       /* and HIL ID in range? */ 
       && WIM__mGetKombiIntContainer[0] <= u32HilId
       && WIM__mGetKombiIntContainer[u16Right] >= u32HilId)
   {
      while (/* search loop */
             u16Left <= u16Right)
      {
         /* binary search... try center item of search interval */
         u16Index = u16Left + (u16Right - u16Left) / 2;
         if (/* HIL -ID found? */
             WIM__mGetKombiIntContainer[u16Index] == u32HilId)
         {
            switch (enEvt)
            {
               case WIM__nRegister:
                  if (/* condition was not set before? */
                      False == WIM__boGetIntCondition(u16Index))
                  {
                     /* set state and re-check flag for 
                        this IC internal condition */
                     WIM__vSetIntCondition(u16Index, On);
                     WIM__vSetIntConditionCheck(u16Index, On);
                  }
                  break;
               case WIM__nRetrigger:
                  /* set state, re-check and retrigger flag for 
                     this IC internal condition */
                  WIM__vSetIntCondition(u16Index, On);
                  WIM__vSetIntConditionRetrig(u16Index, On);
                  WIM__vSetIntConditionCheck(u16Index, On);
                  break;
               case WIM__nDelete:
                  if (/* condition was set before? */
                      True == WIM__boGetIntCondition(u16Index))
                  {
                     /* clear state flag and set re-check flag for 
                        this IC internal condition */
                     WIM__vSetIntCondition(u16Index, Off);
                     WIM__vSetIntConditionCheck(u16Index, On);
                  }
                  break;
               default:
                  /* wrong parameter */
                  WIM__vRaiseException(WIM_nWrongParameter);
                  break;
            }
            /* end the search */
            u16Left = u16Right + 1;
         }
         else
         {
            if (/* center item larger then search item? */
                WIM__mGetKombiIntContainer[u16Index] > u32HilId)
            {
               /* new search interval ends before center item (half interval) */
               u16Right = u16Index - 1;
            }
            else
            {
               /* new search interval starts after center item (half interval) */
               u16Left = u16Index + 1;
            }
         }
      }
   }
   else
   {
      /* wrong parameter */
      WIM__vRaiseException(WIM_nWrongParameter);
   }
}

/**
* Warning states handled by RequestControl has to be restored.
*   @return  void
*   @param   void
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
void WIM__vStartRestoreWarningsRequestControl_AC(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /**
   * (I) reset all warning states that are handled in RequestControl
   */
   /* reset all internal state flags */
   WIM__vInitStateFlagArrays(False);
   /* clear dynamic states of all messages */
   memset(WIM__astMsgStates, 0, WIM__mGetNoOfMessages * sizeof(WIM__tstMsgState));
   /* Activate ICom communication for WIM__vOnEvent_AC */
   WIM__vFinishedRestoreWarningsActivateICom();

   /**
   * (II) re-check all Warnings  
   */
   /* check TURN_ON_DELAY conditions */
   WIM__mGetTurnOnDelayFctPtr();
   /* trigger application checked warnings (complex condition) */ 
   WIM__vCheckComplexWarnings_AC();
   /* real time condition check is started when GC notifies about 
      check complex warning done */

   /**
   * (III) Start and trigger Scheduler. 
   *  In case of multi controller system this processed by ICom */
   /* This is done after GC notifies about check complex warning done */
}

/**
* Warning states handled by RequestControl has to be reset.
*   @return  void
*   @param   void
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
void WIM__vStartResetWarningsRequestControl_AC(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* reset all internal state flags */
   WIM__vInitStateFlagArrays(False);
      /* clear dynamic states of all messages */
       memset(WIM__astMsgStates, 0, WIM__mGetNoOfMessages * sizeof(WIM__tstMsgState));
      /* Activate ICom communication for WIM__vOnEvent_AC */
   WIM__vFinishedResetWarningsActivateICom();

   /* check TURN_ON_DELAY conditions */
   WIM__mGetTurnOnDelayFctPtr();
   /* trigger application checked warnings (complex condition) */ 
   WIM__vCheckComplexWarnings_AC();
}

/**
* Check if the actuallly Warning is a WakeIC Warning AND if it is active.
*   @return  TRUE, if actually Warning is WakeIC
*   @param   uint32: WakeIC message index
*   @author  A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boGetWakeICState(uint32 u32IndexWakeIc)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* Index of Message is in area*/
       u32IndexWakeIc < WIM__nMaxWakeIcMsgCount)
   {
      /* Is actually wake ic warning set ? */
      if( WIM__aboWakeICStates[u32IndexWakeIc])
      {
         return True;
      }
   }
   return False;
}

/**
*   Set the WakeICState if WakeIC warning
*   @return  void
*   @param   uint32: WakeIC message index
*   @param   boNewState: True OR False 
*   @author  A.Wagner, Schleissheimer GmbH 
*/
bool WIM__vSetWakeICState (uint32 u32IndexWakeIc, bool boNewState)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* Index of Message is in area*/
       u32IndexWakeIc < WIM__nMaxWakeIcMsgCount)
   {
      /* Set new state of a wake-ic warning */
      WIM__aboWakeICStates[u32IndexWakeIc] = boNewState;
      return True;
   }
   return False;
}

      /**
*   Get if Msg is a WakeIC warning
*   @return  void
*   @param   enMsg: message enum
*   @author  A.Wagner, Schleissheimer GmbH 
*/
uint32 WIM__u32GetWakeICMsg (WIM_tenMsg enMsg)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint32 u32Index = 0;                 /* loop variable                          */
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   for(u32Index = 0; u32Index < WIM__nMaxWakeIcMsgCount; u32Index++)
   {
      /* Is actually message a wake-ic warning */
      if( enMsg == WIM__aenWakeIcWarnings[u32Index])
      {
         return u32Index;
      }
   }
   return WIM__nMaxWakeIcMsgCount;
}