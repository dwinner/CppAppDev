/******************************************************************************
*=====================      Copyright by Continental AG      ==================
*******************************************************************************
* Titel        : WIM__Diag.c
*
* Description  : This file implements special display behaviour of complex  
*                messages, e.g. dynamic or multiple pictures or other special 
*                requirements
*
* Environment  : OSEK, JCP (NEC V850)
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
* Archive: $Log: WIM__Diag.c  $
* Archive: Initial revision for VS11 (Based on 213IC-EL E009.4rel)
*
* Archive: Revision 1.1.2.4 2013/11/22 17:23:23CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 36779 : BR213EL, E006, Implementation of new WarnDB
* Archive: DC MR 36462 : WIM: Implement new scheduling and state handling for acoustic part
* Archive: Revision 1.1.2.3 2013/08/16 13:28:32CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 33822 : IC213EL-GC WIM: display synchroneous periodic tone not stopped with display off: WDM62157
* Archive: DC MR 33932 : IC213EL GC WIM: Initial sound requests for warnings does not work if sound system is not ready
* Archive: DC MR 33999 : BR213GC-EL, E005, WIM, CWMDL: API split - ORM5621
* Archive: DC MR 34028 : BR213EL, E005, StyleGuide Validation and implementation
* Archive: DC MR 34202 : BR213IC-GC-EL, WIM: Missing HIL output for seat belt warning acoustics - Folow-Up 33655
* Archive: DC MR 34326 : BR213-GC-EL/E005.1, WIM: Display is on for 2 minutes even when warning has disappeared
* Archive: DC MR 34547 : BR213-EL, E005.1/GC,WIM: Removal of QAC warning
* Archive: DC MR 34706 : BR213-GC-EL, E005.1: Chance DOCG implementation in WIM and TPOL
* Archive: DC MR 34781 : BR213-GC-EL, E005.1, WIM: Inconsistent display output in Fault Memory
* Archive: Revision 1.1.2.2 2012/05/18 10:42:42CEST Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
* Archive: Revision 1.2 2012/05/18 10:42:43CEST uid37556 
* Archive: Member moved from WIM__Diag.c in project /id/dag_PF3/sw/pkg/wim/core/project.pj[dag_PF3.sw.pkg.wim_COMMON_IC222GC_VarP] to WIM__Diag.c in project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj[dag_PF3.sw.pkg.wim_COMMON_GenPF3GC_VarX].
* Archive: Revision 1.1 2010/11/18 15:13:22CET Brueggemann Alexander (uidt3637) (uidt3637) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/project.pj
* 
*    Rev 1.2   Nov 19 2010 16:04:12   SCHL_Dirk.Gottwalles
* DC MR21122 BR222: WIM reaction at wakeupreq.
* DC MR21302 BR222/AC: Optimierung Aufruf Checkfunktion WIM
* DC MR20423 W222: WIM new acoustics requirements
* DC MR21177 Implementation of first WarnDB for E003
* DC MR21336 WIM: Using Enumeration Symbols for State/Widget Mapping
* 
*    Rev 1.1   Sep 17 2010 20:58:06   SCHL_Lars.Gruenewald
* DC MR21004 Startup MR for Module DOCG (Display Documentation Target Application)
* DC MR20908 E002/AC, Startup HIL
* 
*    Rev 1.0   Jun 11 2010 14:06:28   SCHL_Thomas.Godemann
* Initial revision.
* 
* --------------------------------------------------------------------------
* Date      | Author | Reason     | Change
* --------------------------------------------------------------------------
* 10-06-03    LarGru   MR20481      Initial revision for W222
*
*******************************************************************************/

/******************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*******************************************************************************/
/* System-headerfiles */
#include  "cdef.h"
/* Foreign headerfiles */
/* Own headerfiles */
#include "WIM_c1.h"
#include "WIM__Diag.h"

/******************************************************************************
* GLOBAL DEFINITIONS
*******************************************************************************/
/**
* Flag, indicates whether diagostic mode is active or not
*/
bool WIM__boDiagMode = False;

/******************************************************************************
* FILE LOCAL DEFINITIONS
*******************************************************************************/
/******************************************************************************
* FILE LOCAL FUNCTION PROTOTYPES
*******************************************************************************/
/******************************************************************************
* FUNCTION DEFINITIONS
*******************************************************************************/

/**
* Activate diagnostic mode. In this mode messages can be activated via the 
* diagnostic interface (special commands). Diag mode can not be entered,
* if any WIM configured message is active
*   @return  void
*   @param   none 
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vStartDiagMode(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   WIM__boDiagMode = True;       /* diagnostic mode now activated             */ 
   WIM__vStateHandlerInit_GC();  /* reset state handler                       */
   WIM__vTriggerSchedule();      /* trigger a schedule cycle                  */
   WIM__vScheduleAcoustics();
}

/**
* Deactivate diagnostic mode. The function is called at the end of the 
* diagnostic session or if any warning is activated the "regular" way.
* All warnings are restored to their "real" state if diagnostic mode ends.
*   @return  void
*   @param   none 
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vEndDiagMode(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (WIM__boDiagMode)
   {
      WIM__boDiagMode = False;   /* switch off diagnostic mode                */
      WIM__vRestoreWarnings();   /* restore state before DiagMode activation  */
   }
}

/**
* Function activates/deactivates a message in diagnostic mode
*   @return  DLIB_tenReturn
*   @param   boActivate: True > Register, False > Delete message 
*   @author  T.Godemann, Schleissheimer GmbH 
*/
DLIB_tenReturn WIM__enDiagWarnRequest(bool boActivate, WIM_tenMsg enMsg)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   DLIB_tenReturn enReturn = DLIB_nReturnCodeOK;
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* diagnostic mode is off? */
       !WIM__boDiagMode)
   {
      WIM__vStartDiagMode();  /* try to switch on  */
      if (/* mode could not be changed */ !WIM__boDiagMode) 
          enReturn = DLIB_nReturnCodeRefuse; /* report this in the return code */
   }
   if (/* diagnostic mode already active or yet activated */
       enReturn == DLIB_nReturnCodeOK)
   {
      if (/* valid message? */
          enMsg < WIM__mGetNoOfMessages)
      {
         /* activate the message */
         WIM__vOnEvent_GC(enMsg, (boActivate ? WIM__nRegister : WIM__nDelete));
      }
      else
      { 
         /* error: invalid message ID */
         enReturn = DLIB_nReturnCodeRange;
      }
   }
   return enReturn;
}

/**
* Function activates a message in diagnostic mode.
* Is for DocGen, allways the requested Message is the only registered and
* Displayed immediately.
*   @return  ---
*   @param   enMsg: Message to register 
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
void WIM__vDiagRemoteCtrlSetWarning(WIM_tenMsg enMsg)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   WIM__vStartDiagMode();  /* try to switch on or restart */
   if (/* Is DiagMode On */ WIM__boDiagMode) 
   {
      if (/* valid message? */
          enMsg < WIM__mGetNoOfMessages)
      {
         /* activate the message */
         WIM__vOnEvent_GC(enMsg, WIM__nRegister);
      }
   }
}
