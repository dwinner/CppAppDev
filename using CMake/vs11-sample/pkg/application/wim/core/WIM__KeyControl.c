/******************************************************************************
*=====================      Copyright by Continental AG      ==================
*******************************************************************************
* Titel        : WIM__KeyControl.c
*
* Description  : The class controlls key-events delivered by KBD module.
*                It provides a global callback function, called for the active
*                display message if a key event occures
*
* Environment  : OSEK, JCP (NEC V850)
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
* Archive: $Log: WIM__KeyControl.c  $
* Archive: Revision 1.1.2.2 2012/05/18 10:42:42CEST Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
* Archive: Revision 1.3 2012/05/18 10:42:43CEST uid37556 
* Archive: Member moved from WIM__KeyControl.c in project /id/dag_PF3/sw/pkg/wim/core/project.pj[dag_PF3.sw.pkg.wim_COMMON_IC222GC_VarP] to WIM__KeyControl.c in project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj[dag_PF3.sw.pkg.wim_COMMON_GenPF3GC_VarX].
* Archive: Revision 1.2 2012/04/04 13:44:54CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 24870: W222, E007/GC, WIM: Implement changes from Review ORM2907
* Archive: DC MR 25007: W222, E007/GC, WIM: Displacement of handling messages - WDM20280
* Archive: DC MR 25041: Do not specify message propagation in message description files
* Archive: DC MR 25095: W222, E007/GC, WIM: Improvement of Timer accuracy for display role - WDM 25704
* Archive: DC MR 25034: Reduction of lag times in case of vehicle locked
* Archive: DC MR 25393: W222, E007/GC, WIM: No cancel of interval acoustic - WDM31269, ÄLP2895
* Archive: Revision 1.1 2011/08/11 12:57:16CEST Brueggemann Alexander (uidt3637) (uidt3637) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/project.pj
* 
*    Rev 1.2   Aug 12 2011 16:39:36   SCHL_Dirk.Gottwalles
* DC MR 22652: W222, E006/AC, SCS: Remove warning management
* DC MR 22655: W222, E006/AC, WIM: Implmentation of complex key handling for warnings
* DC MR 22263: W222, E006/GC, WIM: Remove of unused sound Ids
* DC MR 22549: E006/GC: HIL: Get acoustics status indication for warnings
* DC MR 22686: Implementation of L3 Menu, Warn DB for E006
* DC MR 22733: W222, E006/GC, WIM: Implementation of complex key handling for warnings
* DC MR 21544: E006/GC: HIL: Get TPOL Menu HIL-ID and WIM-HIL-ID
* DC MR 22749: Integration of ARTEMMIS 3.2
* 
*    Rev 1.1   Nov 19 2010 16:04:12   SCHL_Dirk.Gottwalles
* DC MR21122 BR222: WIM reaction at wakeupreq.
* DC MR21302 BR222/AC: Optimierung Aufruf Checkfunktion WIM
* DC MR20423 W222: WIM new acoustics requirements
* DC MR21177 Implementation of first WarnDB for E003
* DC MR21336 WIM: Using Enumeration Symbols for State/Widget Mapping
* 
*    Rev 1.0   Jun 11 2010 14:06:40   SCHL_Thomas.Godemann
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
#include "WIM__KeyControl.h"

/******************************************************************************
* GLOBAL DEFINITIONS
*******************************************************************************/

/* N/A */

/******************************************************************************
* FILE LOCAL DEFINITIONS
*******************************************************************************/

/******************************************************************************
* FILE LOCAL FUNCTION PROTOTYPES
*******************************************************************************/

/* N/A */

/******************************************************************************
* FUNCTION DEFINITIONS
*******************************************************************************/

/**
* Central key event handler. Function is called for current display master if
* a key event was detected. Key events may be used to confirm a message or do 
* some specific handling. How the key has to be evaluated is configured in
* the central message property table. The enumeration WIM__tenKeyCbType 
* defines the allowed configurations.
*   @return  none 
*   @param   EVHD_tenReceiveEvent enKeyEvent: Message that DpoolData for Key changed
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
void WIM__vDoKeyEvent(EVHD_tenReceiveEvent enRxKeyEvent)
{    
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   /* Struct with KeyEvent and its Msg */
   /* local copy of DpoolData */
   DPOOL_txWIM_tstKeyEvent stKeyEvent;
   KBD_tenKeyCode enKey;

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   
   if( /* Receive DpoolData and Check validation */
       E_DATA_OK == DPOOL_enGetPoolData(DPOOL_nDataWIM_stKeyEvent, &stKeyEvent))
   {
      /* Recieved KeyEvent has valid WarnID */
      if(stKeyEvent.u16WarningID < WIM_nenNoOfMessages)
      {
         /* copy key code */
         enKey = (KBD_tenKeyCode)stKeyEvent.u8Key;
         switch ( /* Get the type of Key Handling e.g. default or any special */
                  WIM__menGetKeyCbType(stKeyEvent.u16WarningID))
         {
            case WIM__nManuQuitKey: /* key is used for driver confirmation */
               {
                  if (/* test if key-event is valid for confirmation */
                      WIM__boIsOkKey(enKey) || WIM__boIsBackKey(enKey))
                  {
                     /* pulse the event 'manually confirmed' */
                     WIM__vOnEvent_GC(((WIM_tenMsg)stKeyEvent.u16WarningID), WIM__mGetManuQuitEvt(enKey));
                  }
               } break;                                                              
            case WIM__nNone:  /* key is not used */
            default:
               break;
         }
      }
   }
}
