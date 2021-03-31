#ifndef WIM__STATEHANDLERSLACKSTATEMATRIX_H
#define WIM__STATEHANDLERSLACKSTATEMATRIX_H
/******************************************************************************
*=====================      Copyright by Continental AG      ==================
*******************************************************************************
* Titel        : WIM__StateHandlerSlackStateMatrix.h
*
* Description  : Definition of a state machine's matrix for single line 
*                acknowledgements.
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
* Archive: $Log: WIM__StateHandlerSlackStateMatrix.h  $
* Archive: Revision 1.2.1.3 2014/08/13 18:28:28CEST Immel-EXT, Marc (uid37561) 
* Archive: - removed unknown tokes at the start of the file
* Archive: Revision 1.2.1.2 2014/06/05 13:52:54CEST Wagner-EXT, Alexander (uidw3785) 
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
#include "WIM__StateHandlerSlackHandlerFunctions.h"

/**
* Event-State Matrix for messages of type Handling
* each column contains the event handler functions to be called in the 
* warning message state defined by the column
*/
static const WIM__tboEventHandler WIM__apboStateFctMatrixSlackMsg[WIM__nNoOfStateEvents][WIM__nNoOfDspStatesMsg] =
{
   /* Event/Msg state          Inactive                           Waiting                           WaitingForDsp                       ModalPhase                         NormalPhase                     ContinousPhase                ManuQuit                   AutoQuit                       PreConfirmed          */
   /* --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
   /* WIM__nRegister       */ { WIM__boDoRegRetSlackMsg_Inact,    WIM__nNoAction,                   WIM__boDoRegRetSlackMsg_WaitForDisp,     WIM__boDoException,                WIM__boDoRegRetSlackMsg_Norm,   WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nWakeIC         */,{ WIM__boDoException,               WIM__boDoException,               WIM__boDoException,                      WIM__boDoException,                WIM__boDoException,             WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nRetrigger      */,{ WIM__boDoRegRetSlackMsg_Inact,    WIM__nNoAction,                   WIM__boDoRegRetSlackMsg_WaitForDisp,     WIM__boDoException,                WIM__boDoRegRetSlackMsg_Norm,   WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nCancel         */,{ WIM__nNoAction,                   WIM__boDoCnclDelSlackMsg_Wait,    WIM__boDoCnclDelSlackMsg_WaitForDisp,    WIM__boDoException,                WIM__boDoCnclDelSlackMsg_Norm,  WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nDelete         */,{ WIM__nNoAction,                   WIM__boDoCnclDelSlackMsg_Wait,    WIM__boDoCnclDelSlackMsg_WaitForDisp,    WIM__boDoException,                WIM__boDoCnclDelSlackMsg_Norm,  WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nDspRequest     */,{ WIM__nNoAction,                   WIM__boDoDspRequestSlackMsg_Wait, WIM__nNoAction,                          WIM__boDoException,                WIM__boDoException,             WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nDspAssign      */,{ WIM__nNoAction,                   WIM__nNoAction,                   WIM__boDoDspAssignSlackMsg_WaitForDisp,  WIM__boDoException,                WIM__boDoException,             WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nDspCancel      */,{ WIM__nNoAction,                   WIM__nNoAction,                   WIM__boDoDspCnclSlackMsg_WaitForDisp,    WIM__boDoException,                WIM__boDoDspCnclSlackMsg_Norm,  WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nDspSuppr       */,{ WIM__nNoAction,                   WIM__nNoAction,                   WIM__nNoAction,                          WIM__boDoException,                WIM__nNoAction,                 WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }                                   
   /* WIM__nAcuAssign      */,{ WIM__boDoException,               WIM__boDoException,               WIM__boDoException,                      WIM__boDoException,                WIM__boDoException,             WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nAcuAssignTD    */,{ WIM__boDoException,               WIM__boDoException,               WIM__boDoException,                      WIM__boDoException,                WIM__boDoException,             WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nAcuDelayElapsed*/,{ WIM__boDoException,               WIM__boDoException,               WIM__boDoException,                      WIM__boDoException,                WIM__boDoException,             WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nAcuCancel      */,{ WIM__boDoException,               WIM__boDoException,               WIM__boDoException,                      WIM__boDoException,                WIM__boDoException,             WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nTmrDspModal    */,{ WIM__boDoException,               WIM__boDoException,               WIM__boDoException,                      WIM__boDoException,                WIM__boDoException,             WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nTmrDspNormal   */,{ WIM__boDoException,               WIM__boDoException,               WIM__boDoException,                      WIM__boDoException,                WIM__boDoEndNormalSlackMsg,     WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nTmrHdlExpired  */,{ WIM__boDoException,               WIM__boDoException,               WIM__boDoException,                      WIM__boDoException,                WIM__boDoException,             WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nManuQuitOk     */,{ WIM__boDoException,               WIM__boDoException,               WIM__boDoException,                      WIM__boDoException,                WIM__nNoAction,                 WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nManuQuitBack   */,{ WIM__boDoException,               WIM__boDoException,               WIM__boDoException,                      WIM__boDoException,                WIM__nNoAction,                 WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nPreConfirmed   */,{ WIM__boDoException,               WIM__boDoException,               WIM__boDoException,                      WIM__boDoException,                WIM__nNoAction,                 WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nConfirmation   */,{ WIM__nNoAction,                   WIM__nNoAction,                   WIM__nNoAction,                          WIM__boDoException,                WIM__nNoAction,                 WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nAcuTerminated  */,{ WIM__boDoException,               WIM__boDoException,               WIM__boDoException,                      WIM__boDoException,                WIM__boDoException,             WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nAbortWait      */,{ WIM__nNoAction,                   WIM__nNoAction,                   WIM__boDoAbortHdlSlack_WaitForDisp,      WIM__boDoException,                WIM__boDoException,             WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nAcuRetrigger   */,{ WIM__boDoException,               WIM__boDoException,               WIM__boDoException,                      WIM__boDoException,                WIM__boDoException,             WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nAcuStop        */,{ WIM__boDoException,               WIM__boDoException,               WIM__boDoException,                      WIM__boDoException,                WIM__boDoException,             WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
   /* WIM__nDspRetrigger   */,{ WIM__boDoException,               WIM__boDoException,               WIM__boDoException,                      WIM__boDoException,                WIM__boDoException,             WIM__boDoException,           WIM__boDoException,        WIM__boDoException,              WIM__boDoException     }
};

#endif
