#ifndef WIM__STATEHANDLERACOUSTICSTATEMATRIX_H
#define WIM__STATEHANDLERACOUSTICSTATEMATRIX_H
/******************************************************************************
*=====================      Copyright by Continental AG      ==================
*******************************************************************************
* Titel        : WIM__StateHandlerAcousticStateMatrix.h
*
* Description  : Definition of a state machine's matrix for acoustic.
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
* Archive: $Log: WIM__StateHandlerAcousticStateMatrix.h  $
* Archive: Revision 1.5 2014/08/13 18:28:05CEST Immel-EXT, Marc (uid37561) 
* Archive: - removed unknown tokes at the start of the file
* Archive: Revision 1.4 2014/03/21 13:04:30CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 39524 : WIM: Correct interval acoustic handling and HIL feedback
* Archive: DC MR 39163 : WIM: Overcome illegal memory access and correction of HMI acoustics notification
* Archive: DC MR 40021 : WIM: Sound of FCW warning is not retriggered after reset
* Archive: Revision 1.3 2014/01/20 18:26:18CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 36462: WIM: Implement new scheduling and state handling for acoustic part
* Archive: Revision 1.2 2013/12/06 17:53:33CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 37353 : WIM: Implement changes on door warning acoustics after clarification with customer - OPL 2064
* Archive: Revision 1.1 2013/11/05 13:30:54CET Wagner-EXT, Alexander (uidw3785) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
*/

/***************************************************************************
** Header Files (Only those that are needed in this file)
****************************************************************************/

/* System Header Files */
#include "cdef.h"

/* Foreign headerfiles */

/* Own headerfiles */
#include "WIM_c1.h"
#include "WIM__StateHandlerAcousticHandlerFunctions.h"

/** 
* event handler function type
* @param  WIM_tenMsg: identifier of message
*/
typedef bool (*WIM__tboEventHandler)(WIM_tenMsg, WIM__tenEventIntern);

/**
* State matrix entry if no action should be performed on event
*/
#define WIM__nNoAction NULL

/**
* Event-State Matrix for messages of type Acoustic
* each column contains the event handler functions to be called in the 
* warning state defined by the column
*/
static const WIM__tboEventHandler WIM__apboStateFctMatrixAcu[WIM__nNoOfStateEvents][WIM__nNoOfStatesAcu] =
{
   /* Event/Msg state          Inactive                 Waiting                      WaitingForDisplay                      ToneDelay                 Playing                     WaitForTerm                           Terminated                AutoQuit                */
   /* -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
   /* WIM__nRegister      */ { WIM__boDoRegAcu,         WIM__nNoAction,              WIM__nNoAction,                        WIM__nNoAction,           WIM__nNoAction,             WIM__boDoAcuRestart,                  WIM__nNoAction,           WIM__boDoRegAcu_AutoQuit }  /* WIM__nRegister      */
   /* WIM__nWakeIC        */,{ WIM__nNoAction,          WIM__nNoAction,              WIM__nNoAction,                        WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                       WIM__nNoAction,           WIM__nNoAction           }  /* WIM__nRegNoWakeIC   */
   /* WIM__nRetrigger     */,{ WIM__boDoRegAcu,         WIM__nNoAction,              WIM__nNoAction,                        WIM__nNoAction,           WIM__boDoAcuRestart,        WIM__boDoAcuRestart,                  WIM__boDoRetriggerAcu,    WIM__boDoRegAcu_AutoQuit }  /* WIM__nRetrigger     */
   /* WIM__nCancel        */,{ WIM__nNoAction,          WIM__boDoCnclDelAcu_Waiting, WIM__nNoAction,                        WIM__boDoCnclDelAcuTd,    WIM__boDoCnclDelAcuPlaying, WIM__nNoAction,                       WIM__boDoCnclDelAcuTerm,  WIM__nNoAction           }  /* WIM__nCancel        */
   /* WIM__nDelete        */,{ WIM__nNoAction,          WIM__boDoCnclDelAcu_Waiting, WIM__nNoAction,                        WIM__boDoCnclDelAcuTd,    WIM__boDoCnclDelAcuPlaying, WIM__nNoAction,                       WIM__boDoCnclDelAcuTerm,  WIM__nNoAction           }  /* WIM__nDelete        */
   /* WIM__nDspRequest    */,{ WIM__nNoAction,          WIM__nNoAction,              WIM__nNoAction,                        WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                       WIM__nNoAction,           WIM__nNoAction           }  /* WIM__nDspRequest    */
   /* WIM__nDspAssign     */,{ WIM__nNoAction,          WIM__nNoAction,              WIM__boDoDspAssignAcu,                 WIM__nNoAction,           WIM__nNoAction,             WIM__boDoDspAssignAcuDspRoll,         WIM__nNoAction,           WIM__nNoAction           }  /* WIM__nDspAssign     */
   /* WIM__nDspCancel     */,{ WIM__nNoAction,          WIM__boDoDspCnclSupprAcu,    WIM__boDoDspCnclDspSupprAcu_WaitDisp,  WIM__boDoDspCnclSupprAcu, WIM__boDoDspCnclSupprAcuPl, WIM__boDoDspCncl_WaitForTerm,         WIM__nNoAction,           WIM__nNoAction           }  /* WIM__nDspCancel     */
   /* WIM__nDspSuppr      */,{ WIM__nNoAction,          WIM__boDoDspCnclSupprAcu,    WIM__boDoDspCnclDspSupprAcu_WaitDisp,  WIM__boDoDspCnclSupprAcu, WIM__boDoDspCnclSupprAcuPl, WIM__nNoAction,                       WIM__nNoAction,           WIM__nNoAction           }  /* WIM__nDspSuppr      */
   /* WIM__nAcuAssign     */,{ WIM__nNoAction,          WIM__boDoAcuAssign,          WIM__nNoAction,                        WIM__boDoAcuAssign,       WIM__nNoAction,             WIM__nNoAction,                       WIM__nNoAction,           WIM__nNoAction           }  /* WIM__nAcuAssign     */
   /* WIM__nAcuAssignTD   */,{ WIM__nNoAction,          WIM__boDoAcuAssignToneDelay, WIM__nNoAction,                        WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                       WIM__nNoAction,           WIM__nNoAction           }  /* WIM__nAcuAssignTD   */
   /* WIM__nAcuDelayElapsed*/,{WIM__nNoAction,          WIM__nNoAction,              WIM__nNoAction,                        WIM__boDoTdElapsed,       WIM__nNoAction,             WIM__nNoAction,                       WIM__nNoAction,           WIM__nNoAction           }  /* WIM__nAcuTDElapsed  */
   /* WIM__nAcuCancel     */,{ WIM__nNoAction,          WIM__nNoAction,              WIM__nNoAction,                        WIM__nDoAcuCnclToneDelay, WIM__boDoAcuCnclTermAcu,    WIM__boDoAcuCnclTermAcu_WaitForTerm,  WIM__nNoAction,           WIM__nNoAction           }  /* WIM__nAcuCancel     */
   /* WIM__nTmrDspModal   */,{ WIM__nNoAction,          WIM__nNoAction,              WIM__nNoAction,                        WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                       WIM__nNoAction,           WIM__nNoAction           }  /* WIM__nTmrDspModal   */
   /* WIM__nTmrDspNormal  */,{ WIM__nNoAction,          WIM__nNoAction,              WIM__nNoAction,                        WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                       WIM__nNoAction,           WIM__nNoAction           }  /* WIM__nTmrDspNormal  */
   /* WIM__nTmrHdlExpired */,{ WIM__nNoAction,          WIM__nNoAction,              WIM__boDoHdlExpAcu,                    WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                       WIM__nNoAction,           WIM__nNoAction           }  /* WIM__nTmrHdlExpired */
   /* WIM__nManuQuitOk    */,{ WIM__nNoAction,          WIM__nNoAction,              WIM__nNoAction,                        WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                       WIM__nNoAction,           WIM__nNoAction           }  /* WIM__nManuQuitOk    */
   /* WIM__nManuQuitBack  */,{ WIM__nNoAction,          WIM__nNoAction,              WIM__nNoAction,                        WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                       WIM__nNoAction,           WIM__nNoAction           }  /* WIM__nManuQuitBack  */
   /* WIM__nPreConfirmed  */,{ WIM__nNoAction,          WIM__nNoAction,              WIM__nNoAction,                        WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                       WIM__nNoAction,           WIM__nNoAction           }  /* WIM__nPreConfirmed  */
   /* WIM__nConfirmation  */,{ WIM__nNoAction,          WIM__nNoAction,              WIM__nNoAction,                        WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                       WIM__nNoAction,           WIM__nNoAction           }  /* WIM__nConfirmation  */
   /* WIM__nAcuTerminated */,{ WIM__nNoAction,          WIM__nNoAction,              WIM__nNoAction,                        WIM__nNoAction,           WIM__boDoAcuCnclTermAcu,    WIM__boDoAcuCnclTermAcu_WaitForTerm,  WIM__nNoAction,           WIM__nNoAction           }  /* WIM__nAcuTerminated */
   /* WIM__nAbortWait     */,{ WIM__nNoAction,          WIM__nNoAction,              WIM__nNoAction,                        WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                       WIM__nNoAction,           WIM__nNoAction           }  /* WIM__nAbortWait     */
   /* WIM__nAcuRetrigger  */,{ WIM__boDoAcuRetrigger,   WIM__boDoAcuRetrigger,       WIM__nNoAction,                        WIM__nNoAction,           WIM__boDoAcuRetrigger,      WIM__nNoAction,                       WIM__boDoAcuRetrigger,    WIM__boDoAcuRetrigger    }  /* WIM__nAcuRetrigger  */
   /* WIM__nAcuStop       */,{ WIM__nNoAction,          WIM__nNoAction,              WIM__nNoAction,                        WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                       WIM__nNoAction,           WIM__nNoAction           }  /* WIM__nAcuStop       */
   /* WIM__nDspRetrigger  */,{ WIM__nNoAction,          WIM__nNoAction,              WIM__nNoAction,                        WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                       WIM__nNoAction,           WIM__nNoAction           }  /* WIM__nDspRetrigger  */ 
};
#endif
