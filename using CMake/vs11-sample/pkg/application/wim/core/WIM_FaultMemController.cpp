/***************************************************************************
*================== Copyright by Continental Automotive GmbH ===============
****************************************************************************
* Titel        : WIM_FaulMemController.cpp
*
* Description  : This file contains the implementation of class WIMFaultMemController.
*                WIMFaultMemController is the Container for display of warnings in Menu-Fault-Memory.
*                Base type is SceneController, aatched strategy is WIMFaultMemStrategy.
*
* Environment  : ARTEMMIS/JCP2011
*
* Responsible  : Alexander Wagner, Schleissheimer GmbH
*
* Guidelines   : SMK 3.6
*
* Template name: VDO Cpp Class
*
* CASE-Tool    : Together, Version 6.1 or higher
*
* Revision List: (Will be filled by PVCS)
* Archive: $Log: WIM_FaultMemController.cpp  $
* Archive: Revision 1.1.2.3 2013/08/16 13:42:58CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 33822 : IC213EL-GC WIM: display synchroneous periodic tone not stopped with display off: WDM62157
* Archive: DC MR 33932 : IC213EL GC WIM: Initial sound requests for warnings does not work if sound system is not ready
* Archive: DC MR 33999 : BR213GC-EL, E005, WIM, CWMDL: API split - ORM5621
* Archive: DC MR 34028 : BR213EL, E005, StyleGuide Validation and implementation
* Archive: DC MR 34202 : BR213IC-GC-EL, WIM: Missing HIL output for seat belt warning acoustics - Folow-Up 33655
* Archive: DC MR 34326 : BR213-GC-EL/E005.1, WIM: Display is on for 2 minutes even when warning has disappeared
* Archive: DC MR 34547 : BR213-EL, E005.1/GC,WIM: Removal of QAC warning
* Archive: DC MR 34706 : BR213-GC-EL, E005.1: Chance DOCG implementation in WIM and TPOL
* Archive: DC MR 34781 : BR213-GC-EL, E005.1, WIM: Inconsistent display output in Fault Memory
* Archive: Revision 1.1.2.2 2012/05/18 10:44:16CEST Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
* Archive: Revision 1.4 2012/05/18 10:44:17CEST uid37556 
* Archive: Member moved from WIM_FaultMemController.cpp in project /id/dag_PF3/sw/pkg/wim/core/project.pj[dag_PF3.sw.pkg.wim_COMMON_IC222GC_VarP] to WIM_FaultMemController.cpp in project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj[dag_PF3.sw.pkg.wim_COMMON_GenPF3GC_VarX].
* Archive: Revision 1.3 2012/04/04 13:56:24CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 24870: W222, E007/GC, WIM: Implement changes from Review ORM2907
* Archive: DC MR 25007: W222, E007/GC, WIM: Displacement of handling messages - WDM20280
* Archive: DC MR 25041: Do not specify message propagation in message description files
* Archive: DC MR 25095: W222, E007/GC, WIM: Improvement of Timer accuracy for display role - WDM 25704
* Archive: DC MR 25034: Reduction of lag times in case of vehicle locked
* Archive: DC MR 25393: W222, E007/GC, WIM: No cancel of interval acoustic - WDM31269, ÄLP2895
* Archive: Revision 1.2 2011/11/01 11:41:08CET Brueggemann Alexander (uidt3637) (uidt3637) 
* Archive: Revision derived from delivered sample DC.SW.SYS.222IC_GC_Series_E7.01.38.pre30
* 
*    Rev 1.6   Nov 07 2011 08:11:16   SCHL_Dirk.Gottwalles
* DC MR 23228: W222, E007/GC, WIM: Urgent handling message is not treated urgent
* DC MR 23226: W222, E007/GC, WIM: Change from async acoustic to sync acoustic WDM20336
* DC MR 23230: W222, E007/GC, WIM: Async acoustic blocks urgent display message WDM20376
* DC MR 22977: Integration of ARTEMMIS 3.2.1
* 
*    Rev 1.5   Aug 26 2011 17:25:04   SCHL_Dirk.Gottwalles
* DC MR 22466: W222, E006/AC, WIM: Retrigger on event for AdBlue
* DC MR 22872: Attention Assist output on CAN
* DC MR 22659: W222, E006/AC, WIM: FirstValue flag prohibits delete of warning WDM11861
* DC MR 22153: Support for key handling
* 
*    Rev 1.4   Apr 01 2011 12:48:16   SCHL_Dirk.Gottwalles
* DC MR21947: Takeover of ARTEMMIS 3.1.4
* DC MR21820: Use Widget::boDoesWidgetShow
* DC MR21425: E004/AC, Startup Advanced Parking Control (APC)
* 
*    Rev 1.3   Mar 24 2011 15:44:34   SCHL_Dirk.Gottwalles
* Branch for MR21888
* 
*    Rev 1.1   Dec 17 2010 13:54:40   SCHL_Lars.Gruenewald
* DC MR20897 WIM: Implementation of menu FaultMemory
* 
*    Rev 1.0   Dec 03 2010 15:54:30   SCHL_Lars.Gruenewald
* Initial revision.
* 
*
* End of Revision History
****************************************************************************/

#ifdef __cplusplus
extern "C" 
{
#endif
#include "WIM_c1.h"
#include "API_Device_WIM_Api.h"
#include "WRS_ExternalEventDefinitions.h"
#ifdef __cplusplus
}
#endif

#include "WIM_FaultMemController.hpp"     /* own header   */
#include "WIM_FaultMemStrategy.hpp"       /* strategy     */
#include "WRS_VisualTypesIDs.hpp"         /* for class ID */
#include "WAS_Service.hpp"                /* WidgetAdministrationServices, sending Msgs etc. */
#include "WAS_DisplayController.hpp"


namespace WIM 
{
   // ---------------------------------- Constructor -----------------------------
   WIMFaultMemController::WIMFaultMemController(const uint16 u16MyID, 
                                                const uint16 u16WinID, 
                                                const uint16 u16Index)
   : HMI::WFC::SceneController( u16MyID , u16WinID, u16Index)
   {
      /* initialisation */
      m_u16CurrentWarnID  = WIM_nenInvalidMsg; 
      m_u16FirstWarnID    = WIM_nenInvalidMsg;  
   }

   void WIMFaultMemController::vSetControllerByIndex (int16 id) 
   {
      /* just call parent implementation */
      HMI::WFC::SceneController::boSetStrategyByID (id) ;
   }

   // ----------------------------------- Destructor -----------------------------
   WIMFaultMemController::~WIMFaultMemController() 
   {
      /* deinitialisation */

      /* Use API to create reset event for WIM-GC-Model
      * This is done to cause the WIM to reset the FaultMem state if the 
      * FaultMem looses the display.
      */
      API_WIM_vFaultMemSetEventReset(nResetTag);
   }
      
} // namespace WIM
