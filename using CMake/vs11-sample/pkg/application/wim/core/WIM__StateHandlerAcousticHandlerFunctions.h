#ifndef WIM__STATEHANDLERACOUSTICFUNCTIONS_H
#define WIM__STATEHANDLERACOUSTICFUNCTIONS_H
/******************************************************************************
*=====================      Copyright by Continental AG      ==================
*******************************************************************************
* Titel        : WIM__StateHandlerAcousticHandlerFunctions.h
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
* Archive: $Log: WIM__StateHandlerAcousticHandlerFunctions.h  $
* Archive: Revision 1.4 2014/08/13 18:19:31CEST Immel-EXT, Marc (uid37561) 
* Archive: - removed unknown tokes at the start of the file
* Archive: Revision 1.3 2014/03/21 13:04:18CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 39524 : WIM: Correct interval acoustic handling and HIL feedback
* Archive: DC MR 39163 : WIM: Overcome illegal memory access and correction of HMI acoustics notification
* Archive: DC MR 40021 : WIM: Sound of FCW warning is not retriggered after reset
* Archive: Revision 1.2 2014/01/20 18:25:53CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 36462: WIM: Implement new scheduling and state handling for acoustic part
* Archive: Revision 1.1 2013/11/05 13:30:54CET Wagner-EXT, Alexander (uidw3785) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
*/

/***************************************************************************
** Header Files (Only those that are needed in this file)
****************************************************************************/
/* System-headerfiles */

/* Foreign headerfiles */

/* Own headerfiles */
#include "WIM_c1.h"

/* acoustic event functions */
/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nRegister (message -> active)
* - action: set acoustic request, set registered flag, set played flag
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoRegAcu(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nCancel/WIM__nDelete
* - action: clear acoustic request
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Lazarev, Schleissheimer GmbH 
*/
bool WIM__boDoCnclDelAcu_Waiting (WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nDspCancel/WIM__nDspSuppr
* - action: return to "Waiting for a display" state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Lazarev, Schleissheimer GmbH 
*/
bool WIM__boDoDspCnclSupprAcu (WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nAcuAssign
* - action: switch the state to "Playing"
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Lazarev, Schleissheimer GmbH 
*/
bool WIM__boDoAcuAssign (WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nAcuAssignTD
* - action: switch the state to "Tone Delay"
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Lazarev, Schleissheimer GmbH 
*/
bool WIM__boDoAcuAssignToneDelay (WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nDspCancel/ WIM__nDspSuppr
* - action: clear the request
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Lazarev, Schleissheimer GmbH 
*/
bool WIM__boDoDspCnclDspSupprAcu_WaitDisp (WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nDspAssign
* - action: go to "Waiting" state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Lazarev, Schleissheimer GmbH 
*/
bool WIM__boDoDspAssignAcu (WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   handling display message with acoustic
* - event:  WIM__nTmrHdlExpired (handling validity timer terminated)
* - action: clear acoustic request
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoHdlExpAcu(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nCancel/WIM__nDelete (message -> AutoQuit)
* - action: clear acoustic request
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoCnclDelAcuTd(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nCancel/WIM__nDelete (message -> AutoQuit)
* - action: clear acoustic request
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoCnclDelAcuTerm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nAcuCancel, WIM__nAcuTerminated
* - action: switch to "Waiting" state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Lazarev, Schleissheimer GmbH 
*/
bool WIM__boDoAcuCnclTermAcu(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nRetrigger
* - action: switch to "Waiting" state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Lazarev, Schleissheimer GmbH 
*/
bool WIM__boDoRetriggerAcu (WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM_nRegister/WIM__nRetrigger
* - action: switch to "Waiting" or "Waiting for a display" state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Lazarev, Schleissheimer GmbH 
*/
bool WIM__boDoRegAcu_AutoQuit(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   display message with acoustic
* - event:  WIM__nAcuRetrigger (limited acoustic terminated)
* - action: set request, if sound is playing, restart sound directly
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
bool WIM__boDoAcuRetrigger(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   display message with acoustic
* - event:  WIM__nDelete/WIM__nCancel
* - action: clear the acoustic request
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
bool WIM__boDoCnclDelAcuPlaying(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   display message with acoustic
* - event:  WIM__nDspSuppr/WIM__nDspCancel
* - action: clear the acoustic request
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
bool WIM__boDoDspCnclSupprAcuPl(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   display message with acoustic
* - event:  WIM__nAcuDelayElapsed
* - action: inform scheduler that delay timer elapsed
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   
*   @author  A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoTdElapsed(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   display message with acoustic
* - event:  WIM__nAcuCancel
* - action: stop tone delay, switch to waiting state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   
*   @author  A.Wagner, Schleissheimer GmbH 
*/
bool WIM__nDoAcuCnclToneDelay(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nRegister/WIM__nRetrigger
* - action: switch the state to "Playing"
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoAcuRestart (WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nAcuCancel, WIM__nAcuTerminated
* - action: switch to "Waiting", "AutoQuit", "WaitForDisp" state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Lazarev, Schleissheimer GmbH 
*/
bool WIM__boDoAcuCnclTermAcu_WaitForTerm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nDspAssign
* - action: go to "Waiting" state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoDspAssignAcuDspRoll (WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nDspCancel
* - action: release the acoustic qualifier for sync/single
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @param   WIM__tenEventIntern Event identifier
*   @author  M.Wenske, Schleissheimer GmbH 
*/
bool WIM__boDoDspCncl_WaitForTerm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);
#endif