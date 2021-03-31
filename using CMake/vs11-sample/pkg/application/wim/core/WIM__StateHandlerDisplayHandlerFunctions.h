#ifndef WIM__STATEHANDLERDISPLAYFUNCTIONS_H
#define WIM__STATEHANDLERDISPLAYFUNCTIONS_H
/******************************************************************************
*=====================      Copyright by Continental AG      ==================
*******************************************************************************
* Titel        : WIM__StateHandlerDisplayHandlerFunctions.h
*
* Description  : Interfaces for acoustic state machine event-handling functions
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
* Archive: $Log: WIM__StateHandlerDisplayHandlerFunctions.h  $
* Archive: Revision 1.3 2014/08/13 18:28:12CEST Immel-EXT, Marc (uid37561) 
* Archive: - removed unknown tokes at the start of the file
* Archive: Revision 1.2 2014/08/13 17:17:17CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 42077: WIM: SLACK is displayed with noise
* Archive: DC MR 41987: WIM: Break of 100ms is seen in case of acoustic replacement async to async - #10894
* Archive: DC MR 41983: WIM: Start of "BSM Warnton" output is delayed >300ms - WDM 337
* Archive: DC MR 41981: BR213-EL/E008, WIM: Minimum display time are extended after retriggering - WDM 348
* Archive: DC MR 41975: WIM: Change HIL timing for single line acknowledgements according to customer - WDM257
* Archive: Revision 1.1 2013/09/16 14:08:31CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
*/

/***************************************************************************
** Header Files (Only those that are needed in this file)
****************************************************************************/
/* System-headerfiles */
#include "cdef.h"

/* Foreign headerfiles */

/* Own headerfiles */
#include "WIM_c1.h"

/**
* Identifier of a handling message waiting to be displayed. If during the 
* period of validity time the message not gets the display, it will be cleared.
* The same thing happens, if another handling message becomes active while
* we have a waiting handling message.
*/
extern WIM_tenMsg WIM__enWaitingHdlMsg;

/******************************************************************************
* FUNCTION PROTOTYPES
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
bool WIM__boDoRegMsg_Inact(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoRegMsg_ManQuit(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoRegMsg_AutQuit(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoReRegMsg(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoRegMsgDsp(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoRetriggerMsg(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoCancelMsg_Wait(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoCancelMsg_Norm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoCancelMsg_Cont(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoDeleteMsg_Wait(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoDeleteMsg_Modal(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoDeleteMsg_Norm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoDeleteMsg_Cont(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoDeleteMsg_ManQuit(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoDeleteMsg_AutQuit(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoDspAssignMsg_Wait(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoDspCnclMsg_Modal(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoDspCnclMsg_Norm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoDspCnclMsg_Cont(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoEndModalMsg(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoEndNormalMsg(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoManQuitMsg_Norm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoManQuitMsg_Cont(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoHdlExp_Wait(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoAbortHdl_Wait(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoPreConfirmMsg_Norm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoPreConfirmMsg_Cont(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoDeleteMsg_PreConfirm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoConfirmMsg_PreConfirm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

bool WIM__boDoDspCnclMsg_PreConfirm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoDeleteMsg_WaitDsp(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoDspAssignMsg_WaitDsp(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoDspCnclMsg_WaitDsp(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

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
bool WIM__boDoDspSupprMsg_WaitDsp(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   warning / handling message
* - event:  WIM__nDspRequest (display access has been requested)
* - state:  WIM__nWaiting
* - action: move to wit for display phase
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
bool WIM__boDoDspRequestMsg_Wait(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* Exception event handler function. Is called from Event handler, if an
* event occures, which is not allowed in the current message state.
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoException(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

#endif