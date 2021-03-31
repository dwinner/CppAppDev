/******************************************************************************
*=====================      Copyright by Continental AG      ==================
*******************************************************************************
* Titel        : WIM__StateHandlerSlackHandlerFunctions.c
*
* Description  : Definitions of Single Line state machine event-handling functions
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
* Archive: $Log: WIM__StateHandlerSlackHandlerFunctions.c  $
* Archive: Revision 1.2.1.4 2014/08/13 18:28:20CEST Immel-EXT, Marc (uid37561) 
* Archive: - removed unknown tokes at the start of the file
* Archive: Revision 1.2.1.3 2014/07/18 16:01:09CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 41550 : WIM: Robustness measures for SLACK state handling and scheduling
* Archive: Revision 1.2.1.2 2014/06/05 13:54:52CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
*/

/***************************************************************************
** Header Files (Only those that are needed in this file)
****************************************************************************/
/* System-headerfiles */

/* Foreign headerfiles */

/* Own headerfiles */
#include "WIM__StateHandlerSlackHandlerFunctions.h"
#include "WIM__StateHandlerDisplayHandlerFunctions.h"
#include "WIM__StateAccessHelpers.h"


/******************************************************************************
* EVENT FUNCTIONS
*******************************************************************************/

/******************************************************************************
* WARNING MESSAGE EVENT FUNCTIONS
*******************************************************************************/
/**
* event handler function
* - type:   Single Line message
* - event:  WIM__nRegister/WIM__nRetrigger
* - state:  WIM__nInactive
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoRegRetSlackMsg_Inact(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* do register the slack if still valid */
       enMsg != WIM_nenInvalidMsg)
   {
      /* set qualifier HANDLING */
      WIM__vSetDspQualifier(enMsg, WIM__nQualHdl);
      /* move to Waiting, reset displayed flag */
      WIM__mSetDspState(enMsg, WIM__nWaiting);
      /* it is defined that a new slack will replace any other
      slack message waiting for display. So if we have one, generate a 
      ManuQuit event to finish this message */
      if (WIM__enDspSlackMasterWaiting != WIM_nenInvalidMsg)
      {
         WIM__vOnEvent_GC(WIM__enDspSlackMasterWaiting, WIM__nAbortWait);
      }
   }
   return True; /* event consumed */
}

/**
* event handler function
* - type:   Single line message
* - event:  WIM__nCancel / WIM__nDelete
* - state:  WIM__nWaiting
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoCnclDelSlackMsg_Wait(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* reset warning state */
   WIM__mSetDspState(enMsg, WIM__nInactive);
   WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);

   return True;
}

/**
* event handler function
* - type:   Single Line message
* - event:  WIM__nDspRequest
* - state:  WIM__nWaiting
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoDspRequestSlackMsg_Wait(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   WIM__mSetDspState(enMsg, WIM__nWaitForDsp);

   return True;
}

/**
* event handler function
* - type:   Single Line message
* - event:  WIM__nRegister/WIM__nRetrigger
* - state:  WIM__nWaitingForDsp
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author M.Wenske, Schleissheimer GmbH 
*/
bool WIM__boDoRegRetSlackMsg_WaitForDisp(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   bool boReturn = False; /* return value */

   if (/* slack is valid */
       enMsg != WIM_nenInvalidMsg)
   {
      /* set qualifier HANDLING */
      WIM__vSetDspQualifier(enMsg, WIM__nQualHdl);
      boReturn = True;
   }
   return boReturn; /* event consumed */
}

/**
* event handler function
* - type:   Single Line message
* - event:  WIM__nDspAssign
* - state:  WIM__nWaitingForDsp
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoDspAssignSlackMsg_WaitForDisp(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* start modal phase */
   WIM__mSetDspState(enMsg, WIM__nNormalPhase);
   /* start display timer */
   WIM__vStartTimerEx(WIM__nTimerDspNormalSlack, (WIM__txCorrTag)enMsg, WIM__u16GetSlackDispTime(enMsg));

   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   Single Line message
* - event:  WIM__nAbortWait
* - state:  WIM__nWaitingForDsp
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoAbortHdlSlack_WaitForDisp(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   WIM__mSetDspState(enMsg, WIM__nInactive);
   WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
   /* clear stored (waiting) single line message */ 
   WIM__enDspSlackMasterWaiting = WIM_nenInvalidMsg;

   return True;
}

/**
* event handler function
* - type:   Single line message
* - event:  WIM__nDspCancel
* - state:  WIM__nWaitForDsp
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoCnclDelSlackMsg_WaitForDisp(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt)
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
       && WIM__mboIsPretermAutoQuitEn(enMsg))
   {
      WIM__mSetDspState(enMsg, WIM__nInactive);
      WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
      boReturn = True; /* event consumed */
   }

   return boReturn;
}

/**
* event handler function
* - type:   Single Line message
* - event:  WIM__nRegister/WIM__nRetrigger
* - state:  WIM__nNormalPhase
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoRegRetSlackMsg_Norm(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* set qualifier HANDLING */
   WIM__vSetDspQualifier(enMsg, WIM__nQualHdl);
   /* reset display state (new display time starts) */
   WIM__vStartTimerEx(WIM__nTimerDspNormalSlack, (WIM__txCorrTag)enMsg, WIM__u16GetSlackDispTime(enMsg));
   WIM__mSetDspState(enMsg, WIM__nNormalPhase);
   return True; /* we consumed the event but no scheduling required */ 
}

/**
* event handler function
* - type:   Single Line message
* - event:  WIM__nCancel / WIM__nDelete
* - state:  WIM__nNormalPhase
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoCnclDelSlackMsg_Norm(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt)
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
       && WIM__mboIsPretermAutoQuitEn(enMsg))
   {
      /* end display, move to Inactive */
      WIM__mSetDspState(enMsg, WIM__nInactive);
      WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
      WIM__vCancelTimer(WIM__nTimerDspNormalSlack);
      boReturn = True; /* event consumed */
   }

   return boReturn;
}

/**
* event handler function
* - type:   Single Line message
* - event:  WIM__nDspCancel
* - state:  WIM__nNormalPhase
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoDspCnclSlackMsg_Norm(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* move to Inactive state */
   WIM__mSetDspState(enMsg, WIM__nInactive);
   WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
   WIM__vCancelTimer(WIM__nTimerDspNormalSlack);
   
   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   Single line message
* - event:  WIM__nDspCancel
* - state:  WIM__nWaitingForDsp
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoDspCnclSlackMsg_WaitForDisp(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* move to Inactive state */
   WIM__mSetDspState(enMsg, WIM__nInactive);
   WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
   WIM__vCancelTimer(WIM__nTimerDspNormalSlack);
   
   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   Single Line message
* - event:  WIM__nTmrDspNormal
* - state:  WIM__nNormalPhase
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoEndNormalSlackMsg(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* move to Inactive phase */
   WIM__mSetDspState(enMsg, WIM__nInactive);
   WIM__vSetDspQualifier(enMsg, WIM__nNoRequest);
   
   return True; /* we consumed the event */
}
