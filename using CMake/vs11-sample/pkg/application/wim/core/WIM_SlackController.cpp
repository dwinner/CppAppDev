/***************************************************************************
*================== Copyright by Continental Automotive GmbH ===============
****************************************************************************
* Titel        : WIM_SlackController.cpp
*
* Description  : This file contains the definition of class WIMSlackController.
*                WIMSlackController is the Container for display of slacks.
*                Base type is SceneController, aatched strategy is WIMSlackStrategy.
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
* Archive: $Log: WIM_SlackController.cpp  $
* Archive: Revision 1.2.1.4 2014/09/19 17:48:41CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 42690 : WIM: Adaptions need im WIM for update to new ARTEMMIS
* Archive: Revision 1.2.1.3 2014/06/06 18:42:35CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 38112 : WIM: Introduction of "Singleline Acknowledgements" - MR47
* Archive: Revision 1.2.1.2 2014/06/06 16:31:20CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj

* Initial revision.
* End of Revision History
***************************************************************************/

#ifdef __cplusplus
extern "C" 
{
#endif
   //#include "WIM_ci.h"
   #include "cdef.h"
   #include "WIM_c1.h"
   #include "API_C1.h"
   #include "DFW_Api.h"
#ifdef __cplusplus
}
#endif

#include "WIM_SlackController.hpp"                         /* own header   */
#include "WIM_SlackStrategy.hpp"                           /* strategy     */

#include "WRS_VisualTypesIDs.hpp"                          /* for class ID */
#include "WAS_Service.hpp"
#include "WAS_DisplayController.hpp"
#include "WRS_ExternalEventDefinitions.h"
#include "WIM_ErrorIds.hpp"
#define __FILEID__ WIM_nenController_cpp
namespace WIM 
{
   // ---------------------------------- Constructor -----------------------------
   SLACKController::SLACKController(const uint16 u16MyID, 
                                const uint16 u16WinID, 
                                const uint16 u16Index)
   : HMI::WFC::SceneController( u16MyID , u16WinID, u16Index)
   {
      /* intialisation */
   }

   void SLACKController::vSetControllerByIndex (int16 id) 
   {
      /* just call parent implementation */
      HMI::WFC::SceneController::boSetStrategyByID (id) ;
   }

   // ----------------------------------- Destructor -----------------------------
   SLACKController::~SLACKController() 
   {
      /* deinitialisation */
      API_DFW_vLogOff_HMI(HMI::WRS::Hil_enSlackHilId);
   }
#include "WAS_DisplayController.hpp"      
   // ------------------------------ Process Messsage ----------------------------
   HMI::WCS::enMessageStatus SLACKController::enProcessMessage(HMI::WCS::Message* const poReceivedMsg) 
   {
      SLACKStrategy* poMyStrategy = NULL;
      HMI::WCS::enMessageStatus enMsgState = HMI::WCS::PASS_MESSAGE;
      /* react on slack */
      if(poReceivedMsg)
      {
         switch(poReceivedMsg->u16GetID())
         {
         case MsgID_PreDestroyNotification:
            {
               /* get strategy object */
               poMyStrategy = (SLACKStrategy*)poGetStrategy();
               if (poMyStrategy != NULL)
               {
                  /* Delete running animation part */
                  poMyStrategy->vDeleteRunningAnimPart();
               }
            } break;
         default: break;
         }
         /* call base class method */
         enMsgState = HMI::WFC::SceneController::enProcessMessage(poReceivedMsg);
      }
      /* result of message processing */
      return enMsgState;
   }
} // namespace WIM

