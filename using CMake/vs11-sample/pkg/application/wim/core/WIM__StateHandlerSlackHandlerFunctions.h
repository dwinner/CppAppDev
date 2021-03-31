#ifndef WIM__STATEHANDLERSLACKFUNCTIONS_H
#define WIM__STATEHANDLERSLACKFUNCTIONS_H
/******************************************************************************
*=====================      Copyright by Continental AG      ==================
*******************************************************************************
* Titel        : WIM__StateHandlerSlackHandlerFunctions.h
*
* Description  : Interfaces for Single Line state machine event-handling functions
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
* Archive: $Log: WIM__StateHandlerSlackHandlerFunctions.h  $
* Archive: Revision 1.2.1.3 2014/08/13 18:28:24CEST Immel-EXT, Marc (uid37561) 
* Archive: - removed unknown tokes at the start of the file
* Archive: Revision 1.2.1.2 2014/06/05 13:53:28CEST Wagner-EXT, Alexander (uidw3785) 
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

/******************************************************************************
* FUNCTION PROTOTYPES
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
bool WIM__boDoRegRetSlackMsg_Inact(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   Single line message
* - event:  WIM__nCancel / WIM__nDelete
* - state:  WIM__nWaiting
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoCnclDelSlackMsg_Wait(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   Single Line message
* - event:  WIM__nDspRequest
* - state:  WIM__nWaiting
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoDspRequestSlackMsg_Wait(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   Single Line message
* - event:  WIM__nRegister/WIM__nRetrigger
* - state:  WIM__nWaitingForDsp
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author M.Wenske, Schleissheimer GmbH 
*/
bool WIM__boDoRegRetSlackMsg_WaitForDisp(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   Single Line message
* - event:  WIM__nDspAssign
* - state:  WIM__nWaitingForDsp
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoDspAssignSlackMsg_WaitForDisp(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   Single Line message
* - event:  WIM__nAbortWait
* - state:  WIM__nWaitingForDsp
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoAbortHdlSlack_WaitForDisp(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   Single line message
* - event:  WIM__nDspCancel
* - state:  WIM__nWaitForDsp
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoCnclDelSlackMsg_WaitForDisp(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   Single Line message
* - event:  WIM__nRegister/WIM__nRetrigger
* - state:  WIM__nNormalPhase
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoRegRetSlackMsg_Norm(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   Single Line message
* - event:  WIM__nCancel / WIM__nDelete
* - state:  WIM__nNormalPhase
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoCnclDelSlackMsg_Norm(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   Single Line message
* - event:  WIM__nDspCancel
* - state:  WIM__nNormalPhase
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoDspCnclSlackMsg_Norm(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   Single line message
* - event:  WIM__nDspCancel
* - state:  WIM__nWaitingForDsp
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoDspCnclSlackMsg_WaitForDisp(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt);

/**
* event handler function
* - type:   Single Line message
* - event:  WIM__nTmrDspNormal
* - state:  WIM__nNormalPhase
*   @return bool: True if event consumed and scheduling required, False otherwise
*   @param  WIM_tenMsg Message identifier
*   @author A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoEndNormalSlackMsg(const WIM_tenMsg enMsg, const WIM__tenEventIntern enEvt);

#endif