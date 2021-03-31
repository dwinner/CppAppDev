/***************************************************************************
*================== Copyright by Continental Automotive GmbH ===============
****************************************************************************
* Titel        : WIM_FaultMemStrategy.cpp
*
* Description  : This file contains the implementation of class WIMFaultMemStrategy.
*                WIMFaultMemStrategy is the contoller strategy used by WIMFaultMemController
*                and delivers the warning to be displayed in Menu fault memory, processes keys and
*                gives feedback via APIM to the HMI external WIM model.
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
* Archive: $Log: WIM_FaultMemStrategy.cpp  $
* Archive: Revision 1.1.2.4 2014/05/19 15:33:01CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 40623 : BR213, new BAK: Replace use of KBD up/down by new OFN events
* Archive: Revision 1.1.2.3 2013/08/16 13:43:05CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 33822 : IC213EL-GC WIM: display synchroneous periodic tone not stopped with display off: WDM62157
* Archive: DC MR 33932 : IC213EL GC WIM: Initial sound requests for warnings does not work if sound system is not ready
* Archive: DC MR 33999 : BR213GC-EL, E005, WIM, CWMDL: API split - ORM5621
* Archive: DC MR 34028 : BR213EL, E005, StyleGuide Validation and implementation
* Archive: DC MR 34202 : BR213IC-GC-EL, WIM: Missing HIL output for seat belt warning acoustics - Folow-Up 33655
* Archive: DC MR 34326 : BR213-GC-EL/E005.1, WIM: Display is on for 2 minutes even when warning has disappeared
* Archive: DC MR 34547 : BR213-EL, E005.1/GC,WIM: Removal of QAC warning
* Archive: DC MR 34706 : BR213-GC-EL, E005.1: Chance DOCG implementation in WIM and TPOL
* Archive: DC MR 34781 : BR213-GC-EL, E005.1, WIM: Inconsistent display output in Fault Memory
* Archive: Revision 1.1.2.2 2012/09/07 17:14:18CEST Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
* Archive: Revision 1.5 2012/09/07 17:14:19CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 27740: W205, E010/GC, WIM: Adaptions for ARTEMMIS 3.4
* Archive: DC MR 28962: W205, E010/GC, WIM: Remove QAC errors
* Archive: DC MR 28968: W205, E010/GC, WIM: Cancel of intervall acoustic for sync acoustic - WDM47461
* Archive: DC MR 27756: BR205 E010: Implement L2 delivery into the software frame (SRSC_Styleguide and XML files)
* Archive: Revision 1.4 2012/05/18 10:44:17CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: Member moved from WIM_FaultMemStrategy.cpp in project /id/dag_PF3/sw/pkg/wim/core/project.pj[dag_PF3.sw.pkg.wim_COMMON_IC222GC_VarP] to WIM_FaultMemStrategy.cpp in project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj[dag_PF3.sw.pkg.wim_COMMON_GenPF3GC_VarX].
* Archive: Revision 1.3 2012/04/04 15:06:09CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 24870: W222, E007/GC, WIM: Implement changes from Review ORM2907
* Archive: DC MR 25007: W222, E007/GC, WIM: Displacement of handling messages - WDM20280
* Archive: DC MR 25041: Do not specify message propagation in message description files
* Archive: DC MR 25095: W222, E007/GC, WIM: Improvement of Timer accuracy for display role - WDM 25704
* Archive: DC MR 25034: Reduction of lag times in case of vehicle locked
* Archive: DC MR 25393: W222, E007/GC, WIM: No cancel of interval acoustic - WDM31269, ÄLP2895
* Archive: Revision 1.2 2011/11/17 14:54:50CET Brueggemann Alexander (uidt3637) (uidt3637) 
* Archive: Revision derived from delivered sample DC.SW.SYS.222IC_GC_Series_E7.01.38.pre30
* 
*    Rev 1.7   Nov 18 2011 15:58:44   SCHL_Dirk.Gottwalles
* DC MR 23225: W222, E007/GC, WIM: Auto repeat feature for fault memory WDM19781
* DC MR 22930: BR222, E007/AC, WMN: Implementation of changes for new WEM
* DC MR 23685: W222, E007/GC, WIM: Acoustic macros access array out of bounds
* DC MR 23617: E007/AC WIM remove pragma 'callmode far'
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
***************************************************************************/

#ifdef __cplusplus
extern "C" 
{
#endif
#include "API_c1.h"
#include "KBD_c1.h"
#include "WIM_c1.h"
#include "API_Device_WIM_Api.h"
#include "WRS_ExternalEventDefinitions.h"
#include "OFN_ct.h"
#ifdef __cplusplus
}
#endif

#include "WIM_FaultMemStrategy.hpp"
#include "WIM_FaultMemController.hpp"

#include "WIM_ErrorIds.hpp"
#define __FILEID__ WIM_nenFaultMemStrategy_cpp

namespace WIM 
{
   // ------------------------------ static member ----------------------------

   // ------------------------------ Constructor ----------------------------
   WIMFaultMemStrategy::WIMFaultMemStrategy(uint16 u16ControllerID) : 
      HMI::WSMS::ControllerStrategy(u16ControllerID)
   { 
      /* init */
      m_u16State          = WIM_nenInvalidMsg; 
   }

   // ------------------------------ Init ----------------------------
   void WIMFaultMemStrategy::vInit(void)
   {
      /* call base class */
      HMI::WSMS::ControllerStrategy::vInit();
   }

   // ------------------------------ Process Messsage ----------------------------
   HMI::WCS::enMessageStatus WIMFaultMemStrategy::enProcessMessage(HMI::WCS::Message* poReceivedMsg) 
   { 
      /* local variables */
      HMI::WCS::enMessageStatus enMsgState = HMI::WCS::PASS_MESSAGE;
      KBD_tunOFNKeyData unOfnData;
      KBD_tunKeyData unKeyData;
      uint16 u16MsgId   = 0xFFFF;
      uint32 u32MsgData = 0xFFFF;
      WIM::WIMFaultMemController* const poMyController = (WIM::WIMFaultMemController*)poGetController();

      if (poReceivedMsg != NULL)
	  {
         u16MsgId = poReceivedMsg->u16GetID();
         u32MsgData = poReceivedMsg->u32GetData();
	  }

      switch (u16MsgId)
      {
         /*** LowLine ***/
         case HMI::WRS::KBD_KeyMessage:
            if (/* bubbling message? */
                poReceivedMsg->enGetType() == HMI::WCS::TREE_BUBBLING_MESSAGE)
                {
                KBD_mu32OfnHmiMsgData(unKeyData) = u32MsgData;
                if (/* key is OK or BACK key */
                    (KBD_mu16KeyCode(unKeyData) == KBD_nenDown)
                    /* key stae is "pressed" */
                    && (KBD_mu16KeyState(unKeyData) == KBD_nenPressed)
                    /* there is a message displayed (if not no Key forwarding) */
                    && (m_u16State != WIM_nenInvalidMsg))
                {
                    /* call API setter to notify model for Navigation in MenuFaultMemory */
                    API_WIM_vFaultMemSetEventPrevNext((uint8)(KBD_mu16KeyCode(unKeyData)));
                    /* consume the message */
                    enMsgState = HMI::WCS::CONSUME_MESSAGE;
                }
            }
            break;
         /* MidLine/HighLine */
         case HMI::WRS::MsgID_KBD_OfnMessage:
            if (/* bubbling message? */
                poReceivedMsg->enGetType() == HMI::WCS::TREE_BUBBLING_MESSAGE)
            {
                if (/* there is a message displayed (if not - do not react) */
                    (m_u16State != WIM_nenInvalidMsg))
                {
                    KBD_mu32OfnHmiMsgData(unOfnData) = u32MsgData;
                    if (/* key is UP or DOWN key */
                        (KBD_mu16OfnEvent(unOfnData) == OFN_nenOfnUp || KBD_mu16OfnEvent(unOfnData) == OFN_nenOfnDown))
                    {
                        /* call API setter to notify model for Navigation in MenuFaultMemory */
                        API_WIM_vFaultMemSetEventPrevNext((uint8)KBD_mu16OfnEvent(unOfnData));
                        /* Call API for touch acoustic event */
                        if ((API_WIM_u16FaultMemGetCurrIndexFaultMemMsg() == 0x01) &&
                            (KBD_mu16OfnEvent(unOfnData) == OFN_nenOfnUp) ||
                            (API_WIM_u16FaultMemGetCurrIndexFaultMemMsg() == API_WIM_u16FaultMemGetCountOfFaultMemMsgs()) &&
                            (KBD_mu16OfnEvent(unOfnData) == OFN_nenOfnDown))
                        {
                            APIF_enSetSendTouchAcousticEvent(APIF_nenHMITAE_Reject);
                        }
                        else
                        {
                            APIF_enSetSendTouchAcousticEvent(APIF_nenHMITAE_ListChange);
                        }
                        /* consume the message */
                        enMsgState = HMI::WCS::CONSUME_MESSAGE;
                    }
                }
            }
            break;
         /*** Information about Warning to display changed. Internally send. ***/
         case HMI::WRS::MsgId_WIMFaultMemUpdate:

            /* The message is send by FaultMemController on call of 
             * setter for property m_u16CurrentWarnID. Now the context has changed
             * and we can set the new state for Strategy.                          */
            
            if (/* robustness */
                poMyController)
            {
			   /* Set the new State by using getter of Controller */
               m_u16State = poMyController->u16GetCurrentWarnID_FaultMem();
            }
            else
            {
               WIM__mThrowHMIError(WIM_nExcNoObject);
            }
            /* consume the message */
            enMsgState = HMI::WCS::CONSUME_MESSAGE;
            break;

         default:
            break;
      }   
      return enMsgState;
   }
} // namespace WIM
