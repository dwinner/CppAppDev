#ifndef WIM__STATEHANDLERDISPLAYSTATEMATRIX_H
#define WIM__STATEHANDLERDISPLAYSTATEMATRIX_H
/******************************************************************************
*=====================      Copyright by Continental AG      ==================
*******************************************************************************
* Titel        : WIM__StateHandlerDisplayStateMatrix.h
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
* Archive: $Log: WIM__StateHandlerDisplayStateMatrix.h  $
* Archive: Revision 1.4 2014/08/13 18:28:16CEST Immel-EXT, Marc (uid37561) 
* Archive: - removed unknown tokes at the start of the file
* Archive: Revision 1.3 2014/08/13 17:15:00CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 42077: WIM: SLACK is displayed with noise
* Archive: DC MR 41987: WIM: Break of 100ms is seen in case of acoustic replacement async to async - #10894
* Archive: DC MR 41983: WIM: Start of "BSM Warnton" output is delayed >300ms - WDM 337
* Archive: DC MR 41981: BR213-EL/E008, WIM: Minimum display time are extended after retriggering - WDM 348
* Archive: DC MR 41975: WIM: Change HIL timing for single line acknowledgements according to customer - WDM257
* Archive: Revision 1.2 2014/03/28 15:38:16CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 40035 : WIM: Correct missing sound output after fast warning deactivation and initial display of handling message
* Archive: Revision 1.1 2013/10/18 15:52:03CEST Wagner-EXT, Alexander (uidw3785) 
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
#include "WIM__StateHandlerDisplayHandlerFunctions.h"

/**
* Event-State Matrix for messages of type Warning / Handling
* each column contains the event handler functions to be called in the 
* warning message state defined by the column
*/
static const WIM__tboEventHandler WIM__apboStateFctMatrixMsg[WIM__nNoOfStateEvents][WIM__nNoOfDspStatesMsg] =
{
   /* Event/Msg state          Inactive                  Waiting                     WaitingForDsp                  ModalPhase                 NormalPhase                  ContinousPhase               ManuQuit                        AutoQuit                    PreConfirmed                   */
   /* ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
   /* WIM__nRegister      */ { WIM__boDoRegMsg_Inact,    WIM__nNoAction,             WIM__nNoAction,                WIM__boDoRegMsgDsp,        WIM__boDoRegMsgDsp,          WIM__boDoRegMsgDsp,          WIM__boDoRegMsg_ManQuit,        WIM__boDoRegMsg_AutQuit,    WIM__boDoRegMsg_ManQuit        }
   /* WIM__nWakeIC        */,{ WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                WIM__nNoAction,            WIM__nNoAction,              WIM__nNoAction,              WIM__nNoAction,                 WIM__nNoAction,             WIM__nNoAction                 }
   /* WIM__nRetrigger     */,{ WIM__boDoRegMsg_Inact,    WIM__nNoAction,             WIM__nNoAction,                WIM__boDoReRegMsg,         WIM__boDoReRegMsg,           WIM__boDoReRegMsg,           WIM__boDoRetriggerMsg,          WIM__boDoRetriggerMsg,      WIM__boDoRetriggerMsg          }
   /* WIM__nCancel        */,{ WIM__nNoAction,           WIM__boDoCancelMsg_Wait,    WIM__nNoAction,                WIM__nNoAction,            WIM__boDoCancelMsg_Norm,     WIM__boDoCancelMsg_Cont,     WIM__nNoAction,                 WIM__nNoAction,             WIM__nNoAction                 }
   /* WIM__nDelete        */,{ WIM__nNoAction,           WIM__boDoDeleteMsg_Wait,    WIM__boDoDeleteMsg_WaitDsp,    WIM__boDoDeleteMsg_Modal,  WIM__boDoDeleteMsg_Norm,     WIM__boDoDeleteMsg_Cont,     WIM__boDoDeleteMsg_ManQuit,     WIM__boDoDeleteMsg_AutQuit, WIM__boDoDeleteMsg_PreConfirm  }
   /* WIM__nDspRequest    */,{ WIM__boDoException,       WIM__boDoDspRequestMsg_Wait,WIM__nNoAction,                WIM__boDoException,        WIM__boDoException,          WIM__boDoException,          WIM__boDoException,             WIM__boDoException,         WIM__boDoException,            }
   /* WIM__nDspAssign     */,{ WIM__boDoException,       WIM__boDoDspAssignMsg_Wait, WIM__boDoDspAssignMsg_WaitDsp, WIM__boDoException,        WIM__boDoException,          WIM__boDoException,          WIM__boDoException,             WIM__boDoException,         WIM__boDoException             }
   /* WIM__nDspCancel     */,{ WIM__nNoAction,           WIM__nNoAction,             WIM__boDoDspCnclMsg_WaitDsp,   WIM__boDoDspCnclMsg_Modal, WIM__boDoDspCnclMsg_Norm,    WIM__boDoDspCnclMsg_Cont,    WIM__nNoAction,                 WIM__nNoAction,             WIM__boDoDspCnclMsg_PreConfirm }
   /* WIM__nDspSuppr      */,{ WIM__nNoAction,           WIM__nNoAction,             WIM__boDoDspSupprMsg_WaitDsp,  WIM__nNoAction,            WIM__nNoAction,              WIM__nNoAction,              WIM__nNoAction,                 WIM__nNoAction,             WIM__nNoAction                 }                                   
   /* WIM__nAcuAssign     */,{ WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                WIM__nNoAction,            WIM__nNoAction,              WIM__nNoAction,              WIM__nNoAction,                 WIM__nNoAction,             WIM__nNoAction                 }
   /* WIM__nAcuAssignTD   */,{ WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                WIM__nNoAction,            WIM__nNoAction,              WIM__nNoAction,              WIM__nNoAction,                 WIM__nNoAction,             WIM__nNoAction,                }
   /* WIM__nAcuDelayElapsed*/,{WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                WIM__nNoAction,            WIM__nNoAction,              WIM__nNoAction,              WIM__nNoAction,                 WIM__nNoAction,             WIM__nNoAction,                }
   /* WIM__nAcuCancel     */,{ WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                WIM__nNoAction,            WIM__nNoAction,              WIM__nNoAction,              WIM__nNoAction,                 WIM__nNoAction,             WIM__nNoAction                 }
   /* WIM__nTmrDspModal   */,{ WIM__boDoException,       WIM__boDoException,         WIM__boDoException,            WIM__boDoEndModalMsg,      WIM__boDoException,          WIM__boDoException,          WIM__boDoException,             WIM__boDoException,         WIM__boDoException             }
   /* WIM__nTmrDspNormal  */,{ WIM__boDoException,       WIM__boDoException,         WIM__boDoException,            WIM__boDoException,        WIM__boDoEndNormalMsg,       WIM__boDoException,          WIM__boDoException,             WIM__boDoException,         WIM__boDoException             }
   /* WIM__nTmrHdlExpired */,{ WIM__boDoHdlExp_Wait,     WIM__boDoHdlExp_Wait,       WIM__nNoAction,                WIM__boDoException,        WIM__boDoException,          WIM__boDoException,          WIM__boDoException,             WIM__boDoException,         WIM__boDoException             }
   /* WIM__nManuQuitOk    */,{ WIM__boDoException,       WIM__boDoException,         WIM__boDoException,            WIM__nNoAction,            WIM__boDoManQuitMsg_Norm,    WIM__boDoManQuitMsg_Cont,    WIM__boDoException,             WIM__boDoException,         WIM__boDoException             }
   /* WIM__nManuQuitBack  */,{ WIM__boDoException,       WIM__boDoException,         WIM__boDoException,            WIM__nNoAction,            WIM__boDoManQuitMsg_Norm,    WIM__boDoManQuitMsg_Cont,    WIM__boDoException,             WIM__boDoException,         WIM__boDoManQuitMsg_Cont       }
   /* WIM__nPreConfirmed  */,{ WIM__boDoException,       WIM__boDoException,         WIM__boDoException,            WIM__nNoAction,            WIM__boDoPreConfirmMsg_Norm, WIM__boDoPreConfirmMsg_Cont, WIM__boDoDeleteMsg_ManQuit,     WIM__boDoDeleteMsg_AutQuit, WIM__boDoPreConfirmMsg_Cont    }
   /* WIM__nConfirmation  */,{ WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                WIM__nNoAction,            WIM__nNoAction,              WIM__nNoAction,              WIM__nNoAction,                 WIM__nNoAction,             WIM__boDoConfirmMsg_PreConfirm }
   /* WIM__nAcuTerminated */,{ WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                WIM__nNoAction,            WIM__nNoAction,              WIM__nNoAction,              WIM__nNoAction,                 WIM__nNoAction,             WIM__nNoAction                 }
   /* WIM__nAbortWait     */,{ WIM__boDoException,       WIM__boDoAbortHdl_Wait,     WIM__boDoException,            WIM__boDoException,        WIM__boDoException,          WIM__boDoException,          WIM__boDoException,             WIM__boDoException,         WIM__boDoException             }
   /* WIM__nAcuRetrigger  */,{ WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                WIM__nNoAction,            WIM__nNoAction,              WIM__nNoAction,              WIM__nNoAction,                 WIM__nNoAction,             WIM__nNoAction                 }
   /* WIM__nAcuStop       */,{ WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                WIM__nNoAction,            WIM__nNoAction,              WIM__nNoAction,              WIM__nNoAction,                 WIM__nNoAction,             WIM__nNoAction                 }
   /* WIM__nDspRetrigger  */,{ WIM__nNoAction,           WIM__nNoAction,             WIM__nNoAction,                WIM__boDoReRegMsg,         WIM__boDoReRegMsg,           WIM__boDoReRegMsg,           WIM__boDoRetriggerMsg,          WIM__boDoRetriggerMsg,      WIM__boDoRetriggerMsg          }
};

#endif
