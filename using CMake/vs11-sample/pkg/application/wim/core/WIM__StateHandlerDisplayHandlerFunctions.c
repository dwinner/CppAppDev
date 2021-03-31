/******************************************************************************
*=====================      Copyright by Continental AG      ==================
*******************************************************************************
* Titel        : WIM__StateHandlerDisplayHandlerFunctions.c
*
* Description  : Definitions of acoustic state machine event-handling functions
*
* Responsible  : M.Lazarev, Schleissheimer GmbH
*
* Guidelines   : SMK 3.3  
*
* Template name: OOLite Codefile, Revision 1.0
*
* CASE-Tool    : Together Controlcenter, Version 6.2
*
* Revision List: (Will be filled by PVCS)
* Archive: $Log: WIM__StateHandlerDisplayHandlerFunctions.c  $
* Archive: Revision 1.8 2014/08/23 16:19:10CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 42288 : WIM: Correct customer findings regarding non-urgent handling message and acoustic cancel - WDMs 341, 417
* Archive: Revision 1.7 2014/08/13 18:28:09CEST Immel-EXT, Marc (uid37561) 
* Archive: - removed unknown tokes at the start of the file
* Archive: Revision 1.6 2014/08/13 17:17:12CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 42077: WIM: SLACK is displayed with noise
* Archive: DC MR 41987: WIM: Break of 100ms is seen in case of acoustic replacement async to async - #10894
* Archive: DC MR 41983: WIM: Start of "BSM Warnton" output is delayed >300ms - WDM 337
* Archive: DC MR 41981: BR213-EL/E008, WIM: Minimum display time are extended after retriggering - WDM 348
* Archive: DC MR 41975: WIM: Change HIL timing for single line acknowledgements according to customer - WDM257
* Archive: Revision 1.5 2014/08/08 17:33:16CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 41727 : WIM: Non auto-quit warnings are removed from display roll
* Archive: Revision 1.4 2014/06/06 18:58:48CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 40521 : WIM: Warnings have to be removed from display roll after 500ms if auto-confirmed - LP3471
* Archive: Revision 1.3 2014/06/06 17:06:22CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 40035 : WIM: Correct missing sound output after fast warning deactivation and initial display of handling message
* Archive: Revision 1.2 2014/03/28 15:38:04CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 40035 : WIM: Correct missing sound output after fast warning deactivation and initial display of handling message
* Archive: Revision 1.1 2013/10/15 15:41:39CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
*/

/***************************************************************************
** Header Files (Only those that are needed in this file)
****************************************************************************/
/* System-headerfiles */

/* Foreign headerfiles */

/* Own headerfiles */
#include "WIM__StateHandlerDisplayHandlerFunctions.h"
#include "WIM__StateAccessHelpers.h"

/**
* ManuQuit container 
*/
static const WIM_tpvManuQuitCb WIM__apvManuQuitContainer[] = 
{
   /* content defined in configuration */
   WIM__nManuQuitContainerContent
   WIM__nLastCntEntry /* must always be the last entry */
};

/**
* PreConfirmation container 
*/
static const WIM_tpvPreConfirmationCb WIM__apvPreConfirmationContainer[] = 
{
   /* content defined in configuration */
   WIM__nPreConfirmationContainerContent
   WIM__nLastCntEntry /* must always be the last entry */
};

/* container handler/notification handler */
static void WIM__vManuQuitContainer(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/* Inform applications about driver pre confirmation of a message (DiffManQuit) */
static void WIM__vPreConfirmationContainer(WIM_tenMsg enMsg);

/******************************************************************************
* EVENT FUNCTIONS
*******************************************************************************/

/**
* Exception event handler function. Is called from Event handler, if an
* event occures, which is not allowed in the current message state.
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoException(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   WIM__vRaiseException(WIM_nErrState); /* call exception handler */
   return False;
}

/******************************************************************************
* WARNING MESSAGE EVENT FUNCTIONS
*******************************************************************************/

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nRegister (message -> active)
* - state:  WIM__nInactive
* - action: register warning if allowed
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoRegMsg_Inact(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   WIM_tenMsg enPartner = WIM_nenInvalidMsg;         /* partner message       */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* get partner message - if any */
   enPartner = WIM__enGetPartnerMsg(enMsg);
   if (/* a partner message exists */
       enPartner != WIM_nenInvalidMsg)
   {
      if (/* partner message is in Waiting state and was not displayed yet */
          WIM__mboMsgIsWaitForInitialDsp(enPartner))
      {
         if (/* new message has a lower priority? */
             enMsg > enPartner)
         {
            /* partner message has higher priority:
               -> enMsg must be deactivated (will not be registered) */
            enPartner = enMsg;
            enMsg = WIM_nenInvalidMsg;
         }
      }
      else
      {
         if (/* message is currently displayed or in U-roller mode */
             WIM__mboMsgIsDisplayed(enPartner))
         {
            /* partner message is now displayed:
               -> enMsg must be deactivated (will not be registered) */
            enPartner = enMsg;
            enMsg = WIM_nenInvalidMsg;
         }
         else
         {
            /* partner message is inactive:
               -> no handling required (enMsg will be registered) */
            enPartner = WIM_nenInvalidMsg;
         }
      }
   }
   if (/* the partner message must be deactivated? */
       enPartner != WIM_nenInvalidMsg)
   {
      /* move to Inactive state */
      WIM__mSetDspState(enPartner, WIM__nInactive);
      WIM__vSetDspQualifier(enPartner, WIM__nNoRequest);
   }
   if (/* do register the message if still valid */
       enMsg != WIM_nenInvalidMsg)
   {
      /* move to Waiting, reset displayed flag */
      WIM__mSetDspState(enMsg, WIM__nWaiting);
      WIM__mSetDisplayedFlag(enMsg, Off);
      if (/* special behaviour of handling messages: */
          WIM__mboIsHandling(enMsg) )
      {
         /* it is defined that a new handling message will replace any other handling 
            message waiting for display. So if we have one, generate a ManuQuit event
            to finish this message */
         if (WIM__enWaitingHdlMsg != WIM_nenInvalidMsg)
            WIM__vOnEvent_GC(WIM__enWaitingHdlMsg, WIM__nAbortWait);
         /* remember waiting handling */ 
         WIM__enWaitingHdlMsg = enMsg;
         /* start validity timer for the new message */
         WIM__vStartTimer(WIM__nTimerHdlExpire, (WIM__txCorrTag)enMsg);
         /* set qualifier URGENT */
         if (WIM__mboIsUrgent(enMsg) == On)
         {
            WIM__vSetDspQualifier(enMsg, WIM__nQualUrgt);
         }
         else
         {
            WIM__vSetDspQualifier(enMsg, WIM__nQualNew);
         }
         /* set qualifier HANDLING */
         WIM__vSetDspQualifier(enMsg, WIM__nQualHdl);
      }
      else
      {
         /* set qualifier URGENT or NEW */
         if (WIM__mboIsUrgent(enMsg) == On)
         {
            WIM__vSetDspQualifier(enMsg, WIM__nQualUrgt);
         }
         else
         {
            WIM__vSetDspQualifier(enMsg, WIM__nQualNew);
         }
      }
   }
   return True; /* event consumed */
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nRegister (message -> active)
* - state:  WIM__nManuQuit
* - action: register warning if allowed
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoRegMsg_ManQuit(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boReturn = False; /* return value */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* register in this state is only allowed if:
          - message is retriggerable after manual confirmation and 
          - message is retriggerable after automatic confirmation and 
          - message is automatic confirmable */
          WIM__mboIsManuRetrigEn(enMsg)
       && WIM__mboIsAutoRetrigEn(enMsg)
       && WIM__mboIsAutoQuitEn(enMsg))
   {
      if (/* if this message is still master, just trigger a reregister! */
          enMsg == WIM__enGetDisplayMasterWaiting())
         boReturn = WIM__boDoReRegMsg(enMsg, enEvt);
      else
         boReturn = WIM__boDoRegMsg_Inact(enMsg, enEvt);
   }
   return boReturn;
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nRegister (message -> active)
* - state:  WIM__nAutoQuit
* - action: register warning if allowed
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoRegMsg_AutQuit(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boReturn = False; /* return value */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* register is only allowed if the retrigger flag is set */
       WIM__mboIsAutoRetrigEn(enMsg))
   {
      if (/* if this message is still master, just trigger a reregister! */
          enMsg == WIM__enGetDisplayMasterWaiting())
         boReturn = WIM__boDoReRegMsg(enMsg, enEvt);
      else
         /* calll register function */
         boReturn = WIM__boDoRegMsg_Inact(enMsg, enEvt);
   }
   return boReturn;
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nRegister (message -> active)
* - state:  WIM__nModalPhase/WIM__nNormalPhase/WIM__nContinuousPhase
* - action: restore modal state, restart display timers, set registered flag
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoReRegMsg(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* handling messages: Qualifier handling */
       WIM__mboIsHandling(enMsg) )
   {
      /* set qualifier HANDLING */
      WIM__vSetDspQualifier(enMsg, WIM__nQualHdl);
      /* set qualifier URGENT */
      if (WIM__mboIsUrgent(enMsg) == On)
      {
         WIM__vSetDspQualifier(enMsg, WIM__nQualUrgt);
      }
   }
   else
   {
      /* set qualifier URGENT or NEW */
      if (WIM__mboIsUrgent(enMsg) == On)
      {
         WIM__vSetDspQualifier(enMsg, WIM__nQualUrgt);
      }
      else
      {
         WIM__vSetDspQualifier(enMsg, WIM__nQualNew);
      }
   }
   /* if enabled, store message in fault memory */
   if (WIM__mboIsFaultMemEn(enMsg))
   {
      WIM__vSetFaultMemFlag(enMsg, On);
   }
   /* reset display state (new display time starts) */
   WIM__vStartTimer(WIM__nTimerDspNormal, (WIM__txCorrTag)enMsg);
   if (WIM__mu8GetDspState(enMsg) != WIM__nModalPhase)
   {
      WIM__mSetDspState(enMsg, WIM__nNormalPhase);
   }
   return False; /* we consumed the event but no scheduling required */ 
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nRegister (message -> active)
* - state:  WIM__nModalPhase/WIM__nNormalPhase/WIM__nContinuousPhase
* - action: set fault mem flag
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoRegMsgDsp(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /* if enabled, store message in fault memory */
   if (WIM__mboIsFaultMemEn(enMsg))
   {
      WIM__vSetFaultMemFlag(enMsg, On);
   }
   
   if (/* handling messages: Qualifier handling */
         WIM__mboIsHandling(enMsg) )
   {   
      /* set qualifier HANDLING */
      WIM__vSetDspQualifier(enMsg, WIM__nQualHdl);
      /* set qualifier URGENT */
      if (WIM__mboIsUrgent(enMsg) == On)
      {
         WIM__vSetDspQualifier(enMsg, WIM__nQualUrgt);
      }
      /* reset display state (new display time starts) */
      WIM__vStartTimer(WIM__nTimerDspNormal, (WIM__txCorrTag)enMsg);
   }
   return False; /* we consumed the event but no scheduling required */
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nRetrigger (message -> active)
* - state:  WIM__nManuQuit/WIM__nAutoQuit
* - action: set registered flag, transition to waiting state 
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoRetriggerMsg(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boReturn = False; /* return value */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* if this message is still master, just trigger a reregister! */
       enMsg == WIM__enGetDisplayMasterWaiting())
      boReturn = WIM__boDoReRegMsg(enMsg, enEvt);
   else
   {
      /* calll register function */
      boReturn = WIM__boDoRegMsg_Inact(enMsg, enEvt);
   }
   return boReturn;
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nCancel (message has been automatically confirmed)
* - state:  WIM__nWaiting
* - action: if never displayed, reset warning - else if allowed move to 
*           AutoQuit state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoCancelMsg_Wait(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boReturn = True; /* return value */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* if handling, reset waiting */
          (WIM__enWaitingHdlMsg == enMsg) 
       && (WIM__enGetTimer(WIM__nTimerHdlExpire) == WIM__nTimerRunning))
   {  
      /* ignore Cancel during 600ms wait time! */
      boReturn = False; 
   }
   else
   {
      if (/* message was never displayed? */
          WIM__mboGetDisplayedFlag(enMsg) == Off)
      {
         /* reset warning state */
         WIM__mSetDspState(enMsg, WIM__nInactive);
         WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
      }
      else 
      {
         if (/* we are in roller mode. Allowed to accept the confirmation? */
             WIM__mboIsAutoQuitEn(enMsg))
         {
            /* move to AutoQuit state */
         WIM__mSetDspState(enMsg, WIM__nAutoQuit);
         WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
         }
         else
         {  
            boReturn = False; /* we did nothin' -> return False */
         }
      }
   }
   return boReturn;
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nCancel (message has been automatically confirmed)
* - state:  WIM__nNormalPhase
* - action: clear registered flag and if allowed switch state to AutoQuit
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoCancelMsg_Norm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boReturn = False; /* return value */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* allowed to accept the confirmation ... */
          WIM__mboIsAutoQuitEn(enMsg)
       /* and allowed to abort during normal phase -> end display */
       &&(WIM__mboIsPretermAutoQuitEn(enMsg)
       /* or unqualified in U-roller mode -> end display anyway */
       || (WIM__u8GetDspQualifier(enMsg) == WIM__nNoQualifier)))
   {
      /* end display, move to AutoQuit */
      WIM__mSetDspState(enMsg, WIM__nAutoQuit);
      WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
      WIM__vCancelTimer(WIM__nTimerDspNormal);
      boReturn = True; /* event consumed */
   }
   return boReturn;
}

/**
* event handler function
* - type:   warning message
* - event:  WIM__nCancel (message has been automatically confirmed)
* - state:  WIM__nContinousPhase
* - action: if allowed switch state to AutoQuit
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoCancelMsg_Cont(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boReturn = False; /* return value */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* accept the confirmation? */
       WIM__mboIsAutoQuitEn(enMsg))
   {
      WIM__mSetDspState(enMsg, WIM__nAutoQuit);
      WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
      boReturn = True; /* event consumed */
   }
   return boReturn;
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nDelete (message has been automatically confirmed)
* - state:  WIM__nWaiting
* - action: if never displayed, reset warning - else if allowed move to 
*           AutoQuit state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoDeleteMsg_Wait(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boReturn = True; /* return value */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if((WIM__enWaitingHdlMsg == enMsg) &&
      (WIM__enGetTimer(WIM__nTimerHdlExpire) == WIM__nTimerRunning))
   {  
      /* if this handling message, has the validity timer (600ms), reset 
       * waiting message and stop timer. Otehrwise the normal procedere for
       * inactive messages will be used.
       */
      WIM__vOnEvent_GC(WIM__enWaitingHdlMsg, WIM__nAbortWait);
   }
   else
   {
      if (/* message was never displayed? */
          WIM__mboGetDisplayedFlag(enMsg) == Off &&
          /* message is allowed to accept confirmation? */
          WIM__mboIsAutoQuitEn(enMsg))
      {
         /* reset warning state */
         WIM__mSetDspState(enMsg, WIM__nInactive);
         WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);

         /* Fault memory handling */
         if (   WIM__mboIsFaultMemEn(enMsg)
             && WIM__mboIsFaultMemClearEn(enMsg))
         {
            WIM__vSetFaultMemFlag(enMsg, Off); /* clear flag */  
         }
      }
      else if (/* we are in roller mode. Allowed to accept the confirmation? */
               WIM__mboIsAutoQuitEn(enMsg))
      {
         /* move to AutoQuit state */
         WIM__mSetDspState(enMsg, WIM__nAutoQuit);
         WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
         if (/* on Delete event also clear fault memory - if allowed */
             WIM__mboIsFaultMemClearEn(enMsg))
         {
            WIM__vSetFaultMemFlag(enMsg, Off);
         }
      }
      else
      {  
         boReturn = False; /* we did nothin' -> return False */
      }
   }
   return boReturn;
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nDelete (message has been automatically confirmed)
* - state:  WIM__nModalPhase
* - action: clear registered flag and if allowed switch state to AutoQuit
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoDeleteMsg_Modal(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/*  on Delete event also clear fault memory - if allowed */
       WIM__mboIsAutoQuitEn(enMsg) && WIM__mboIsFaultMemClearEn(enMsg))
   {
      WIM__vSetFaultMemFlag(enMsg, Off);
   }
   return False; /* we consumed the eventbut no scheduling required */ 
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nDelete (message has been automatically confirmed)
* - state:  WIM__nNormalPhase
* - action: clear registered flag and if allowed switch state to AutoQuit
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoDeleteMsg_Norm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boReturn = False; /* return value */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* are we allowed to accept the confirmation? */
       WIM__mboIsAutoQuitEn(enMsg))
   {
      if (/* on Delete event also clear fault memory - if allowed */
          WIM__mboIsFaultMemClearEn(enMsg))
      {
         WIM__vSetFaultMemFlag(enMsg, Off);
      }
      if (/* if it is allowed to abort during normal phase -> end display */
             WIM__mboIsPretermAutoQuitEn(enMsg)
          /* or unqualified in U-roller mode -> end display anyway */
          || (WIM__u8GetDspQualifier(enMsg) == WIM__nNoQualifier))
      {
         WIM__mSetDspState(enMsg, WIM__nAutoQuit);
         WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
         WIM__vCancelTimer(WIM__nTimerDspNormal);
         boReturn = True; /* scheduling required */
      }
   }
   return boReturn;
}

/**
* event handler function
* - type:   warning message
* - event:  WIM__nDelete (message has been automatically confirmed)
* - state:  WIM__nContinousPhase
* - action: if allowed switch state to AutoQuit
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoDeleteMsg_Cont(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boReturn = False; /* return value */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* are we allowed to accept the confirmation? */
       WIM__mboIsAutoQuitEn(enMsg))
   {
      WIM__mSetDspState(enMsg, WIM__nAutoQuit);
      WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
      if (/* on Delete event also clear fault memory - if allowed */
          WIM__mboIsFaultMemClearEn(enMsg))
      {
         WIM__vSetFaultMemFlag(enMsg, Off);
      }
      boReturn = True; /* we consumed the event */
   }
   return boReturn;
}

/**
* event handler function
* - type:   warning message
* - event:  WIM__nDelete (message has been automatically confirmed)
* - state:  WIM__nManuQuit
* - action: clear FaultMemFlag if allowed
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoDeleteMsg_ManQuit(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* on Delete event also clear fault memory - if allowed */
          WIM__mboIsAutoQuitEn(enMsg)
       && WIM__mboIsFaultMemClearEn(enMsg))
   {
      WIM__vSetFaultMemFlag(enMsg, Off);
   }
   return False;
}

/**
* event handler function
* - type:   warning message
* - event:  WIM__nDelete (message has been automatically confirmed)
* - state:  WIM__nAutoQuit
* - action: clear FaultMemFlag if allowed
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoDeleteMsg_AutQuit(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* on Delete event also clear fault memory - if allowed */
       WIM__mboIsFaultMemClearEn(enMsg))
   {
      WIM__vSetFaultMemFlag(enMsg, Off);
   }
   return False;
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nDspAssign (display access has been given)
* - state:  WIM__nWaiting
* - action: move to modal phase and change qualifier to roller mode
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoDspAssignMsg_Wait(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* remind, that we are displayed */
   WIM__mSetDisplayedFlag(enMsg, On);
   /* start modal phase */
   WIM__mSetDspState(enMsg, WIM__nModalPhase);
   /* start display timers */
   WIM__vStartTimer(WIM__nTimerDspModal, (WIM__txCorrTag)enMsg);
   WIM__vStartTimer(WIM__nTimerDspNormal, (WIM__txCorrTag)enMsg);
   
   /* Is the warning still active? */
   if (WIM__mboGetRegFlag(enMsg))
   {
      /* if enabled, store message in fault memory */
      if (WIM__mboIsFaultMemEn(enMsg))
      {
         WIM__vSetFaultMemFlag(enMsg, On);
      }
   }

   if (/* if handling, reset waiting */
       WIM__enWaitingHdlMsg == enMsg)
   {
      /* cancel validity timer */
      WIM__vCancelTimer(WIM__nTimerHdlExpire);
      /* clear stored (waiting) handling message */ 
      WIM__enWaitingHdlMsg = WIM_nenInvalidMsg;
   }
   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   handling message
* - event:  WIM__nDspCancel (display access has been withdrawn)
* - state:  WIM__nModalPhase
* - action: only allowed for handling messages, move to AutoQuit state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoDspCnclMsg_Modal(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boReturn = False; /* return value */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* special behaviour of handling messages */
       WIM__mboIsHandling(enMsg) )
   {
      /* set state to AutoQuit & clear request */
      WIM__mSetDspState(enMsg, WIM__nAutoQuit);
      WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
      /* cancel timers eventually running */
      WIM__vCancelTimer(WIM__nTimerDspModal);
      WIM__vCancelTimer(WIM__nTimerDspNormal);
      boReturn = True;
   }
   else
   {
      /* warnings can NEVER be displaced in modal phase! */
      WIM__boDoException(enMsg, enEvt);
   }
   return boReturn;
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nDspCancel (display access has been withdrawn)
* - state:  WIM__nNormalPhase
* - action: move to waiting and change qualifier to roller mode or
*           move to AutoQuit if no more registered or handling message
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoDspCnclMsg_Norm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* is a handling message? */
          WIM__mboIsHandling(enMsg)
       /* has message been canceled/deleted during normal phase
          and it's allowed to accept that */
       || (!WIM__mboGetRegFlag(enMsg) && WIM__mboIsAutoQuitEn(enMsg)) )
   {
      /* move to AutoQuit state */
      WIM__mSetDspState(enMsg, WIM__nAutoQuit);
      WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
      WIM__vCancelTimer(WIM__nTimerDspNormal);
   }
   else
   {
      /* roller mode, waiting for repeated display */
      WIM__vSetDspQualifier(enMsg, WIM__nNoQualifier);
      WIM__mSetDspState(enMsg, WIM__nWaiting);
      WIM__vCancelTimer(WIM__nTimerDspNormal);
   }
   return True; /* we consumed the event */
}

bool WIM__boDoDspCnclMsg_PreConfirm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* has message been canceled/deleted during continuous phase
          and it's allowed to accept that */
       !WIM__mboGetRegFlag(enMsg) && WIM__mboIsAutoQuitEn(enMsg))
   {
      /* move to AutoQuit state */
      WIM__mSetDspState(enMsg, WIM__nAutoQuit);
      WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
   }
   else
   {
      WIM__mSetDspState(enMsg, WIM__nWaiting);
      WIM__vSetDspQualifier(enMsg, WIM__nNoQualifier);
   }
   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   warning message
* - event:  WIM__nDspCancel (display access has been withdrawn)
* - state:  WIM__nContinuousPhase
* - action: move to waiting and change qualifier to roller mode or
*           move to AutoQuit if no more registered
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoDspCnclMsg_Cont(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* has message been canceled/deleted during continuous phase
          and it's allowed to accept that */
       !WIM__mboGetRegFlag(enMsg) && WIM__mboIsAutoQuitEn(enMsg))
   {
      /* move to AutoQuit state */
      WIM__mSetDspState(enMsg, WIM__nAutoQuit);
      WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
   }
   else
   {
      WIM__mSetDspState(enMsg, WIM__nWaiting);
      WIM__vSetDspQualifier(enMsg, WIM__nNoQualifier);
   }
   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nTmrDspModal (modal display phase ended)
* - state:  WIM__nModalPhase
* - action: end display or enter normal phase, depending on registered 
*           flag and attributes
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoEndModalMsg(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (enMsg < WIM__mGetNoOfMessages)
   {
         /* if a message has been automatically confirmed during modal phase
         and it is allowed to abort after modal phase -> end display */
      if (   (WIM__mboGetRegFlag(enMsg) == Off)
          && (WIM__mboIsAutoQuitEn(enMsg) == On)
          && ((WIM__mboIsPretermAutoQuitEn(enMsg) == On)
          /* or unqualified in U-roller mode -> end display anyway */
          || (WIM__u8GetDspQualifier(enMsg) == WIM__nNoQualifier)))
      {
         /* move to AutoQuit state */
         WIM__mSetDspState(enMsg, WIM__nAutoQuit);
         WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
         WIM__vCancelTimer(WIM__nTimerDspNormal);
      }
      else
      {
         /* move to Normal state */
         WIM__mSetDspState(enMsg, WIM__nNormalPhase);
      }
   }
   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nTmrDspNormal (normal display phase ended)
* - state:  WIM__nNormalPhase
* - action: end display or enter continuous phase, depending on registered flag and type
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoEndNormalMsg(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (enMsg < WIM__mGetNoOfMessages)
   {
      if (/* is a handling message? */
             WIM__mboIsHandling(enMsg)
          /* has message been canceled/deleted during normal phase
             and it's allowed to accept that */
          || (!WIM__mboGetRegFlag(enMsg) && WIM__mboIsAutoQuitEn(enMsg)) )
      {
         /* move to AutoQuit state */
         WIM__mSetDspState(enMsg, WIM__nAutoQuit);
         WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
      }
      else
      {
         /* move to continous phase */
         WIM__mSetDspState(enMsg, WIM__nContinousPhase);
         WIM__vSetDspQualifier(enMsg, WIM__nNoQualifier);
      }
   }
   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nPreConfirmed (manual premature confirmation of message)
* - state:  WIM__nContinousPhase
* - action: set PreConfirm state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
bool WIM__boDoPreConfirmMsg_Cont(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   WIM__mSetDspState(enMsg, WIM__nPreConfirmed);
   /* call pre confirm callback container */
   WIM__vPreConfirmationContainer(enMsg);
   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nDelete (manual premature confirmation of message)
* - state:  WIM__nPreConfirmPhase
* - action: set PreConfirm state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
bool WIM__boDoDeleteMsg_PreConfirm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boReturn = False; /* return value */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* are we allowed to accept the confirmation? */
       WIM__mboIsAutoQuitEn(enMsg))
   {
      if (/* on Delete event also clear fault memory - if allowed */
          WIM__mboIsFaultMemClearEn(enMsg))
      {
         WIM__vSetFaultMemFlag(enMsg, Off);
      }

      WIM__mSetDspState(enMsg, WIM__nAutoQuit);
      WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);

      boReturn = True; /* scheduling required */
   }
   return boReturn;
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nPreConfirmed (manual premature confirmation of message)
* - state:  WIM__nNormalPhase
* - action: set PreConfirm state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
bool WIM__boDoPreConfirmMsg_Norm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boReturn = False; /* return value */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* manual confirmation in this phase is only allowed, if we have a priority
      below Prio1 Level or we are NOT in the initial display */ 
   if (/* prio lower than level 1 ? */
          (WIM__u8GetMsgPrioLevel(enMsg) > 1)
       /* or unqualified in U-roller mode */
       || (WIM__u8GetDspQualifier(enMsg) == WIM__nNoQualifier))
   {
      WIM__mSetDspState(enMsg, WIM__nPreConfirmed);
      WIM__vCancelTimer(WIM__nTimerDspNormal);
      /* call pre confirm callback container */
      WIM__vPreConfirmationContainer(enMsg);

      boReturn = True; /* we consumed the event */
   }
   return boReturn;
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nConfirm (manual confirmation of message)
* - state:  WIM__nPreConfirm
* - action: set ManuQuit state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
bool WIM__boDoConfirmMsg_PreConfirm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   WIM__mSetDspState(enMsg, WIM__nManuQuit);
   WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
   WIM__vManuQuitContainer(enMsg, enEvt); /* call ManuQuit container */
   return True; /* we consumed the event */
}


/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nManuQuitEvt (manual confirmation of message)
* - state:  WIM__nNormalPhase
* - action: set ManuQuit state and clear qualifier if allowed 
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoManQuitMsg_Norm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boReturn = False; /* return value */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* manual confirmation in this phase is only allowed, if we have a priority
      below Prio1 Level or we are NOT in the initial display */ 
   if (/* prio lower than level 1 ? */
          (WIM__u8GetMsgPrioLevel(enMsg) > 1)
       /* or unqualified in U-roller mode */
       || (WIM__u8GetDspQualifier(enMsg) == WIM__nNoQualifier))
   {
      WIM__mSetDspState(enMsg, WIM__nManuQuit);
      WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
      WIM__vCancelTimer(WIM__nTimerDspNormal); 
      WIM__vManuQuitContainer(enMsg, enEvt); /* call ManuQuit container */
      boReturn = True; /* we consumed the event */
   }
   return boReturn;
}

/**
* event handler function
* - type:   warning message
* - event:  WIM__nManuQuitEvt (manual confirmation of message)
* - state:  WIM__nContinousPhase
* - action: set ManuQuit state, clear qualifier
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoManQuitMsg_Cont(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   WIM__mSetDspState(enMsg, WIM__nManuQuit);
   WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
   WIM__vManuQuitContainer(enMsg, enEvt); /* call ManuQuit container */
   return True; /* we consumed the event */
}


/**
* event handler function
* - type:   handling message
* - event:  WIM__nTmrHdlExpired (validity timer has elapsed)
* - state:  WIM__nWaiting
* - action: clear display request, set state to AutoQuit
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoHdlExp_Wait(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boReturn = False; /* return value */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* must be a handling message  */
          WIM__mboIsHandling(enMsg)
       /* and must be the one waiting for display */
       && (WIM__enWaitingHdlMsg == enMsg))
   {
      WIM__mSetDspState(enMsg, WIM__nAutoQuit);
      WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
      /* clear stored (waiting) handling message */ 
      WIM__enWaitingHdlMsg = WIM_nenInvalidMsg;
      boReturn = True;
   }
   else
   {
      /* warning or invlid handling! */
      WIM__boDoException(enMsg, enEvt);
   }
   return boReturn;
}

/**
* event handler function
* - type:   handling message
* - event:  WIM__nAbortWait (Waiting handling replaced by new handlung during wait)
* - state:  WIM__nWaiting
* - action: clear display request, set state to AutoQuit
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoAbortHdl_Wait(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boReturn = False; /* return value */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* must be a handling message  */
          WIM__mboIsHandling(enMsg)
       /* and must be the one waiting for display */
       && (WIM__enWaitingHdlMsg == enMsg))
   {
      WIM__mSetDspState(enMsg, WIM__nAutoQuit);
      WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
      /* clear stored (waiting) handling message */ 
      WIM__enWaitingHdlMsg = WIM_nenInvalidMsg;
      WIM__vCancelTimer(WIM__nTimerHdlExpire);
      boReturn = True;
   }
   else
   {
      /* warning or invlid handling! */
      WIM__boDoException(enMsg, enEvt);
   }
   return boReturn;
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nDelete (message has been automatically confirmed)
* - state:  WIM__nWaitingForDsp
* - action: clear fault memory flag
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
bool WIM__boDoDeleteMsg_WaitDsp(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/*  on Delete event also clear fault memory - if allowed */
       WIM__mboIsAutoQuitEn(enMsg) && WIM__mboIsFaultMemClearEn(enMsg))
   {
      WIM__vSetFaultMemFlag(enMsg, Off);
   }
   return False; /* we consumed the eventbut no scheduling required */ 
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nDspAssign (display access has been given)
* - state:  WIM__nWaitForDsp
* - action: move to modal phase and change qualifier to roller mode
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
bool WIM__boDoDspAssignMsg_WaitDsp(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* remind, that we are displayed */
   WIM__mSetDisplayedFlag(enMsg, On);
   /* start modal phase */
   WIM__mSetDspState(enMsg, WIM__nModalPhase);
   /* start display timers */
   WIM__vStartTimer(WIM__nTimerDspModal, (WIM__txCorrTag)enMsg);
   WIM__vStartTimer(WIM__nTimerDspNormal, (WIM__txCorrTag)enMsg);
   
   /* Is the warning still active? */
   if (WIM__mboGetRegFlag(enMsg))
   {
      /* if enabled, store message in fault memory */
      if (WIM__mboIsFaultMemEn(enMsg))
      {
         WIM__vSetFaultMemFlag(enMsg, On);
      }
   }

   if (/* if handling, reset waiting */
       WIM__enWaitingHdlMsg == enMsg)
   {
      /* cancel validity timer */
      WIM__vCancelTimer(WIM__nTimerHdlExpire);
      /* clear stored (waiting) handling message */ 
      WIM__enWaitingHdlMsg = WIM_nenInvalidMsg;
   }
   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nDspRequest (display access has been requested)
* - state:  WIM__nWaiting
* - action: move to wait for display phase
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
bool WIM__boDoDspRequestMsg_Wait(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   if (/* if handling, reset waiting */
   WIM__enWaitingHdlMsg == enMsg)
   {
      WIM__vCancelTimer(WIM__nTimerHdlExpire);
	  WIM__enWaitingHdlMsg = WIM_nenInvalidMsg;
   }
   WIM__mSetDspState(enMsg, WIM__nWaitForDsp);
   return True;
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nDspCancel
* - state:  WIM__nWaitForDsp
* - action: was not in display, display not possible go to waiting state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
bool WIM__boDoDspCnclMsg_WaitDsp(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   if (WIM__mboGetRegFlag(enMsg) == On)
   {
       WIM__mSetDspState(enMsg, WIM__nWaiting);
   }
   else 
       if (/* message was never displayed? */
            WIM__mboGetDisplayedFlag(enMsg) == Off &&
            /* message is allowed to accept confirmation? */
            WIM__mboIsAutoQuitEn(enMsg))
       {
           /* reset warning state */
           WIM__mSetDspState(enMsg, WIM__nInactive);
           WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
           /* Fault memory handling */
           if (WIM__mboIsFaultMemClearEn(enMsg))
           {
               WIM__vSetFaultMemFlag(enMsg, Off); /* clear flag */  
           }
       }
       else
           if (/* we are in roller mode. Allowed to accept the confirmation? */
               WIM__mboIsAutoQuitEn(enMsg))
           {
               /* move to AutoQuit state */
               WIM__mSetDspState(enMsg, WIM__nAutoQuit);
               WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
               if (/* on Delete event also clear fault memory - if allowed */
                   WIM__mboIsFaultMemClearEn(enMsg))
               {
                   WIM__vSetFaultMemFlag(enMsg, Off);
               }
           }
           else
           {
               WIM__mSetDspState(enMsg, WIM__nWaiting);
           }
   
   return True;
}

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nDspSuppr
* - state:  WIM__nWaitForDsp
* - action: was not in display, display suppressed, go to auto quit state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Immel, Schleissheimer GmbH 
*/
bool WIM__boDoDspSupprMsg_WaitDsp(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   WIM__mSetDspState(enMsg, WIM__nAutoQuit);
   WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
   if (/* if handling, reset waiting */
       WIM__enWaitingHdlMsg == enMsg)
   {
      /* cancel validity timer */
      WIM__vCancelTimer(WIM__nTimerHdlExpire);
      /* clear stored (waiting) handling message */ 
      WIM__enWaitingHdlMsg = WIM_nenInvalidMsg;
   }
   return True;
}

/**
* Inform applications about driver confirmation of a message
*   @return  void
*   @param   message identifier of confirmed message
*   @author  T.Godemann, Schleissheimer GmbH 
*/
static void WIM__vManuQuitContainer(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint8 u8Index = 0; /* index variable                                       */
   uint32 u32HilId;   /* message HIL Id                                       */
   WIM_tenDisplayEvent enKeyEvt = WIM_nManuQuitBack;

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/

   /* Map internal Event to KeyEevent */
   if(enEvt == WIM__nManuQuitOk)
   {
      enKeyEvt = WIM_nManuQuitOk;
   }
   else if(enEvt == WIM__nManuQuitBack)
   {
      enKeyEvt = WIM_nManuQuitBack;
   }

   u32HilId = WIM__u32GetHilId(enMsg);
   while (/* loop through all container functions */
          WIM__apvManuQuitContainer[u8Index] != WIM__nLastCntEntry)
   {
      /* call container function */
      (WIM__apvManuQuitContainer[u8Index])(u32HilId, enKeyEvt);
      u8Index++;
   }
}

/**
* Inform applications about driver pre confirmation of a message (DiffManQuit).
*   @return  void
*   @param   message identifier of confirmed message
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
static void WIM__vPreConfirmationContainer(WIM_tenMsg enMsg)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint8 u8Index = 0; /* index variable                                       */
   uint32 u32HilId;   /* message HIL Id                                       */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   u32HilId = WIM__u32GetHilId(enMsg);
   /* loop through all container functions */
   while (WIM__apvPreConfirmationContainer[u8Index] != WIM__nLastCntEntry)
   {
      /* call container function */
      (WIM__apvPreConfirmationContainer[u8Index])(u32HilId);
      u8Index++;
   }
}
