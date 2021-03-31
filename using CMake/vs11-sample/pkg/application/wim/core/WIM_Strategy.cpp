/***************************************************************************
*================== Copyright by Continental Automotive GmbH ===============
****************************************************************************
* Titel        : WIM_Strategy.cpp
*
* Description  : This file contains the implementation of class WIMStrategy.
*                WIMStrategy is the contoller strategy used by WIMController
*                and delivers the warning to be displayed, processes keys and
*                gives feedback via APIM to the HMI external WIM model.
*
* Environment  : ARTEMMIS/JCP2011
*
* Responsible  : Thomas Godemann, Schleissheimer GmbH
*
* Guidelines   : SMK 3.6
*
* Template name: VDO Cpp Class
*
* CASE-Tool    : Together, Version 6.1 or higher
*
* Revision List: (Will be filled by PVCS)
* Archive: $Log: WIM_Strategy.cpp  $
* Archive: Revision 1.1.2.4 2013/08/16 13:43:18CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 33822 : IC213EL-GC WIM: display synchroneous periodic tone not stopped with display off: WDM62157
* Archive: DC MR 33932 : IC213EL GC WIM: Initial sound requests for warnings does not work if sound system is not ready
* Archive: DC MR 33999 : BR213GC-EL, E005, WIM, CWMDL: API split - ORM5621
* Archive: DC MR 34028 : BR213EL, E005, StyleGuide Validation and implementation
* Archive: DC MR 34202 : BR213IC-GC-EL, WIM: Missing HIL output for seat belt warning acoustics - Folow-Up 33655
* Archive: DC MR 34326 : BR213-GC-EL/E005.1, WIM: Display is on for 2 minutes even when warning has disappeared
* Archive: DC MR 34547 : BR213-EL, E005.1/GC,WIM: Removal of QAC warning
* Archive: DC MR 34706 : BR213-GC-EL, E005.1: Chance DOCG implementation in WIM and TPOL
* Archive: DC MR 34781 : BR213-GC-EL, E005.1, WIM: Inconsistent display output in Fault Memory
* Archive: Revision 1.1.2.3 2013/05/17 16:12:02CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 33413: BR213EL/GC, E004, WIM: Takeover of the latest changes from BR205
* Archive: Revision 1.1.2.2 2012/05/18 10:44:16CEST Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
* Archive: Revision 1.6 2012/05/18 10:44:17CEST uid37556 
* Archive: Member moved from WIM_Strategy.cpp in project /id/dag_PF3/sw/pkg/wim/core/project.pj[dag_PF3.sw.pkg.wim_COMMON_IC222GC_VarP] to WIM_Strategy.cpp in project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj[dag_PF3.sw.pkg.wim_COMMON_GenPF3GC_VarX].
* Archive: Revision 1.5 2012/04/04 14:01:21CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 24870: W222, E007/GC, WIM: Implement changes from Review ORM2907
* Archive: DC MR 25007: W222, E007/GC, WIM: Displacement of handling messages - WDM20280
* Archive: DC MR 25041: Do not specify message propagation in message description files
* Archive: DC MR 25095: W222, E007/GC, WIM: Improvement of Timer accuracy for display role - WDM 25704
* Archive: DC MR 25034: Reduction of lag times in case of vehicle locked
* Archive: DC MR 25393: W222, E007/GC, WIM: No cancel of interval acoustic - WDM31269, ÄLP2895
* Archive: Revision 1.4 2012/02/22 17:32:43CET 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: DC MR 24333: W222, E007/GC, WIM: HIL output for requested sound not working
* Archive: DC MR 24043: Move tube request from WIM to WarningStandard.xml
* Archive: DC MR 23682: W222, E007/GC, WIM: Acousic only messsage does not block display WDM21148
* Archive: DC MR 24086: W222, E007/GC, WIM: Short rest after warning display is not always 5 seconds
* Archive: DC MR 24332: W222, E007/GC, WIM: Warnings can not be acknowledged with Nview active
* Archive: Revision 1.3 2012/01/13 11:54:42CET 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: DC MR 24093: W222, E007/GC, WIM: Acoustic warning does not block display - WDM20499
* Archive: DC MR 23683: W222, E007/GC, WIM: Sync acoustic is cancelled by async acoustic WDM21143
* Archive: DC MR 24088: W222, E007/GC, WIM: Warning blocks display WDM22837, WDM23219
* DC MR 24089: W222,E007,AC, WIM: New configuration values Chauffeur_Avl and ShiftStyle_Variant
* DC MR 24343: W222, E007/AC, WIM: Patch for 0x2000BC and 0x2000C1 (Country coding), WDM23191
* 
*    Rev 1.13   Nov 07 2011 08:11:18   SCHL_Dirk.Gottwalles
* DC MR 23228: W222, E007/GC, WIM: Urgent handling message is not treated urgent
* DC MR 23226: W222, E007/GC, WIM: Change from async acoustic to sync acoustic WDM20336
* DC MR 23230: W222, E007/GC, WIM: Async acoustic blocks urgent display message WDM20376
* DC MR 22977: Integration of ARTEMMIS 3.2.1
* 
*    Rev 1.12   Sep 20 2011 16:25:26   SCHL_Dirk.Gottwalles
* DC MR 21544: BR222/E006/GC: HIL: Get TPOL Menu HIL-ID and WIM-HIL-ID
* 
*    Rev 1.11   Aug 26 2011 17:25:02   SCHL_Dirk.Gottwalles
* DC MR 22466: W222, E006/AC, WIM: Retrigger on event for AdBlue
* DC MR 22872: Attention Assist output on CAN
* DC MR 22659: W222, E006/AC, WIM: FirstValue flag prohibits delete of warning WDM11861
* DC MR 22153: Support for key handling
* 
*    Rev 1.10   Aug 12 2011 16:39:34   SCHL_Dirk.Gottwalles
* DC MR 22652: W222, E006/AC, SCS: Remove warning management
* DC MR 22655: W222, E006/AC, WIM: Implmentation of complex key handling for warnings
* DC MR 22263: W222, E006/GC, WIM: Remove of unused sound Ids
* DC MR 22549: E006/GC: HIL: Get acoustics status indication for warnings
* DC MR 22686: Implementation of L3 Menu, Warn DB for E006
* DC MR 22733: W222, E006/GC, WIM: Implementation of complex key handling for warnings
* DC MR 21544: E006/GC: HIL: Get TPOL Menu HIL-ID and WIM-HIL-ID
* DC MR 22749: Integration of ARTEMMIS 3.2
* 
*    Rev 1.9   Jul 29 2011 14:06:44   SCHL_Dirk.Gottwalles
* DC MR 22188: Controller containers should not call methods of their strategies
* DC MR 22573: E006/AC DPOOL Define Data Braces, remove compiler warning
* DC MR 22334: BR222: SBW sound in Phase 4 WDM10279
* DC MR 22312: W222, E006/AC, WIM: Mute and partial acoutic lowering delay, OPL528
* 
*    Rev 1.8   Apr 01 2011 12:48:16   SCHL_Dirk.Gottwalles
* DC MR21947: Takeover of ARTEMMIS 3.1.4
* DC MR21820: Use Widget::boDoesWidgetShow
* DC MR21425: E004/AC, Startup Advanced Parking Control (APC)
* 
*    Rev 1.7   Mar 24 2011 15:44:34   SCHL_Dirk.Gottwalles
* Branch for MR21888
* 
*    Rev 1.5   Nov 19 2010 16:04:26   SCHL_Dirk.Gottwalles
* DC MR21122 BR222: WIM reaction at wakeupreq.
* DC MR21302 BR222/AC: Optimierung Aufruf Checkfunktion WIM
* DC MR20423 W222: WIM new acoustics requirements
* DC MR21177 Implementation of first WarnDB for E003
* DC MR21336 WIM: Using Enumeration Symbols for State/Widget Mapping
* 
*    Rev 1.4   Aug 05 2010 18:35:28   SCHL_Thomas.Godemann
* DC MR20853 E1.2 Projecthouse Backlog Items: Changes in API-F and Applications
* 
*    Rev 1.3   Jul 09 2010 18:01:50   SCHL_Lars.Gruenewald
* DC MR 20710 Vr222 WIM: Menue is in Display before warning
* DC MR 20545 WIM: Extension of HMI Interface for E001.2
* 
*    Rev 1.2   Jun 26 2010 15:36:28   SCHL_Thomas.Godemann
* DC MR 20620 Startup-MR for dynamical area manager (prio)
* 
*    Rev 1.1   Jun 25 2010 12:22:12   SCHL_Lars.Grünewald
* DC MR 20566  WIM222: WIM Part2 for E001
* DC MR 20629 Configuration of Display Handler
* DC MR 20639 WIM: Adaption of HMI part for E001.1 
* DC MR 20620 Startup-MR for dynamical area manager (prio)
* DC MR 20661 Br222: WIM: ICOM Reinitialization
* DC MR 20662 Needed patches for WarnDB E001
* DC MR 20560 Implementation of first WarnDB for E001
* DC MR 20490 W222 E001: start up MR SFG
* 
*    Rev 1.0   Jun 11 2010 14:08:40   SCHL_Thomas.Godemann
* Initial revision.
* End of Revision History
***************************************************************************/

#ifdef __cplusplus
extern "C" 
{
#endif
#include "API_c1.h"
#include "KBD_c1.h"
#include "KBD_ce.h"
#include "WIM_c1.h"
#ifdef __cplusplus
}
#endif

#include "WIM_Strategy.hpp"
#include "WCS_Message.hpp"
#include "WSMS_ControllerStrategy.hpp"
#include "WIM_Controller.hpp"
#include "WIM_ErrorIds.hpp"
#define __FILEID__ WIM_nenStrategy_cpp

namespace WIM 
{
   // ------------------------------ static member ----------------------------

   // ------------------------------ Constructor ----------------------------
   WIMStrategy::WIMStrategy(uint16 u16ControllerID) :
      ControllerStrategy(u16ControllerID)      
   {
      /* init */
      m_u16State = WIM_nenInvalidMsg;
      m_u16WarnIdReq = WIM_nenInvalidMsg;
      m_u16StateRequested = WIM_nenInvalidMsg;
      m_boDisplayOn = False;
      m_u32HilIdRequested = 0;
      m_u16WarnIdDisplay = 0;
      m_stVisSendNotif.u8VisibileWidgetCnt = 0;
      m_stVisSendNotif.boSendNotification = false;
   }

   // ------------------------------ Init ----------------------------
   void WIMStrategy::vInit(void)
   {
      /* call base class */
      HMI::WSMS::ControllerStrategy::vInit();
      /* init state variables */
      m_u16State          = WIM_nenInvalidMsg; 
      m_u16WarnIdReq      = WIM_nenInvalidMsg;
      m_u16StateRequested = WIM_nenInvalidMsg;
      m_boDisplayOn       = False;
      m_u32HilIdRequested = 0;
   }

   // ------------------------ Send notification ---------------------
   void WIMStrategy::vSendNotification()
   {
      uint32 u32HilFeedback;     /* Variable that holds the HIL-ID which is send to HIL */

      /*
      * During this function the value of m_u16WarnIdReq is confirmed to be in display 
      * now. Becasue of this the content of m_u16WarnIdReq is newer as m_u16WarnIdDisplay.
      * The variable m_u16WarnIdDisplay therefore holds the old warning and m_u16WarnId
      * the new warning, until the value of m_u16WarnIdReq is stored in m_u16WarnIdDisplay 
      * at the end of the function.
      */

      /* has anyone requested to send feedback for WIM GC Model */
      if(m_stVisSendNotif.boSendNotification == True)
      {
         /* Write feedback to API */
         if(/* Has the Widget a valid State */ 
            m_u16State != WIM_nenInvalidMsg &&
            /* and is one of its instances visible */
            m_stVisSendNotif.u8VisibileWidgetCnt > 0)
         {
            /* Inform HIL about changed warning in display. Only the 3-Byte Hil-Id is used. */
            u32HilFeedback = (m_u32HilIdRequested>>8);
         }
         else
         {
            /* set HIL output */
            u32HilFeedback = 0;
         }

         /* send the new and old WarnId into WIM GC Model. */
         API_WIM_vSetDisplayedWarning(m_u16WarnIdReq, m_u16WarnIdDisplay);

         /* Inform HIL about changed warning in display */
         API_HIL_vSetWimHilId(u32HilFeedback);

         /* Save the requested WarnId as current displayed WarnId. This 
          * value will serve as old WarnId for the next feedback
          */
         m_u16WarnIdDisplay = m_u16WarnIdReq;

         /* the notification was send */
         m_stVisSendNotif.boSendNotification = False;
      }
   }

   void WIMStrategy::vSendCancelNotification() const
   {
      /* Inform WIM GC about a not displayed display request */
      API_WIM_vSetCanceledWarning(m_u16WarnIdReq);
   }

   // ------------------------ Set Send notification ------------------
   void WIMStrategy::vSetSendNotification(void)
   {
      /* any has requested a Send Notification next time */
      m_stVisSendNotif.boSendNotification = True;
   }

   // ------------------------ Set Controller Visibility --------------
   void WIMStrategy::vSetControllerVisibility(bool boVisibility)
   {
      if(boVisibility == True)
      {
         /* increment number of visible widgets */
         if(m_stVisSendNotif.u8VisibileWidgetCnt < 0xFF)
         {
            m_stVisSendNotif.u8VisibileWidgetCnt++;
         }
         else
         {
            /* Throw exception into EXEA */
            WIM__mThrowHMIError(WIM_nErrConfig);
         }
      }
      else
      {
         /* decrement number of visible widgets */
         if(m_stVisSendNotif.u8VisibileWidgetCnt >=1)
         {
             m_stVisSendNotif.u8VisibileWidgetCnt--;
         }
         else
         {
             /* Throw exception into EXEA */
             WIM__mThrowHMIError(WIM_nErrConfig);
         }
      }

      /* Always mark for send notification next time */
      m_stVisSendNotif.boSendNotification = True;
   }

   // ------------------------------ Process Messsage ----------------------------
   HMI::WCS::enMessageStatus WIMStrategy::enProcessMessage(HMI::WCS::Message* poReceivedMsg) 
   {
      /* local variables */
      HMI::WCS::enMessageStatus enMsgState = HMI::WCS::PASS_MESSAGE;
      KBD_tunKeyData unKeyData;
      uint16 u16NewWarning;
      uint16 u16NewState;
      uint16 u16MsgId = 0xFFFF;
      uint32 u32MsgData = 0xFFFF;
      if (poReceivedMsg != NULL)
      {
         u16MsgId = poReceivedMsg->u16GetID();
         u32MsgData = poReceivedMsg->u32GetData();
      }
      bool boVisibilityChanged = false;
      /* Save current state for evaluation if feedback is requried */
      uint16 u16StateOld = m_u16State;

      switch (u16MsgId)
      {
      /*** Last chance to process any before draw ***/
      case MsgID_LastBeforeDraw:
         {
            if(m_poController != NULL)
            {
               if(((WIMController*)m_poController)->boGetMasterController())
               {
                  /* send HMI Feedback for WIM GC Model if necessary */
                  vSendNotification();
               }
            }
         } break;
      /*** KEY message => confirmation event ***/
      case HMI::WRS::KBD_KeyMessage:
         {
            if (/* bubbling message? */
                poReceivedMsg->enGetType() == HMI::WCS::TREE_BUBBLING_MESSAGE)
            {
               KBD_mu32KeyHmiMsgData(unKeyData) = u32MsgData; 
               if (/* key is OK or BACK key */
                      (KBD_mu16KeyCode(unKeyData) == KBD_nenOK || KBD_mu16KeyCode(unKeyData) == KBD_nenBack) 
                   /* key stae is "pressed" */
                   && (KBD_mu16KeyState(unKeyData) == KBD_nenPressed)
                   /* there is a message displayed (must always be the case when receiving a message) */
                   && (m_u16State != WIM_nenInvalidMsg))
               {
                  /* call API setter to notify model */ 
                  API_WIM_vSetWarningConfirmed(m_u16WarnIdDisplay, (uint8) KBD_mu16KeyCode(unKeyData));
                  /* consume the message */
                  enMsgState = HMI::WCS::CONSUME_MESSAGE;
               }
            }
         } break;
      
      /*** Display a Warning or release display of warning ***/
      case HMI::WRS::WIM_DisplayWarning:
        {
         /* the new state is in the low-word */
         m_u32HilIdRequested = (((uint32)0x20000000) | ((u32MsgData & 0xFFFF)<<8));

         /* the new warnId is in the high-word */
         u16NewWarning = (uint16)(u32MsgData >> 16);
         u16NewState = u16NewWarning;
         if (/* only if a new warning is requested */
             u16NewState != m_u16StateRequested)
         {
            /* ensure consistency */
            if (u16NewState == WIM_nenInvalidMsg)
            {
               u16NewWarning = WIM_nenInvalidMsg;
            }

            /* Send cancel notification for warning that could not be displayed */
            if(m_u16WarnIdReq != m_u16WarnIdDisplay &&
               m_u16WarnIdReq != u16NewWarning)
            {
               /* In case that m_u16WarnIdReq is not the same as the m_u16WarnIdDisplay, the curernt displayed
                * is not the warning specified in m_u16WarnIdReq. That means by replacing m_u16WarnIdReq the 
                * stored warning was never displayed and will never get displayed.
                */
               vSendCancelNotification();
            }

            /* store the new warnId and state */
            m_u16WarnIdReq      = u16NewWarning;
            m_u16StateRequested = u16NewState;
            /* Set new state for strategy if Display is on. */
            if (m_boDisplayOn == True)
            {
               m_u16State = m_u16StateRequested;
            }


         }
      } break;
      /*** Display On Edge ***/
      case HMI::WRS::MsgID_DSM_DisplayOn:
      case HMI::WRS::MsgID_DSM_DisplayOn_LagTimeAbort:
         {
            /* Set the display state On */
            m_boDisplayOn = True;
            API_WIM_vSetDisplayOn(m_boDisplayOn);
            /* Set last requested state for strategy, Display is On. */
            m_u16State = m_u16StateRequested;
         } break;
      /*** Display Off Edge ***/
      case HMI::WRS::MsgID_DSM_DisplayOff:
         {
            /* Set the display state Off */
            m_boDisplayOn = False;
            API_WIM_vSetDisplayOn(m_boDisplayOn);
            /* Set state invalid for strategy, Display is Off. */
            m_u16State = WIM_nenInvalidMsg;
         } break;
      /*** Visibility of widget has changed ***/
      case HMI::WRS::MsgId_WIM_SetCtrlrVisibility:
         {
            bool boVisibility;
            /* read message data */
            /* visibility has changed */
            boVisibilityChanged = true;
            boVisibility = (u32MsgData > 0) ? true : false;
            vSetControllerVisibility(boVisibility);
         } break;
      /*** Privace pop up warning has been confirmed with Yes ***/
      case HMI::WRS::MsgId_WIM_PrivacyPopUp_Confirmed:
         {
            vProcessPhoneCallKey(enMsgState, true, false, false, false);
            if (m_u16State != WIM_nenInvalidMsg)
            {
               /* call API setter to notify model */
               API_WIM_vSetWarningConfirmed(m_u16WarnIdDisplay, static_cast<uint8>(KBD_nenOK));
            }
         } break;
      /*** Privace pop up warning has been rejected with No ***/
      case HMI::WRS::MsgId_WIM_PrivacyPopUp_Reject:
         {
            vProcessPhoneCallKey(enMsgState, false, true, false, false);
            if (m_u16State != WIM_nenInvalidMsg)
            {
               /* call API setter to notify model */
               API_WIM_vSetWarningConfirmed(m_u16WarnIdDisplay, static_cast<uint8>(KBD_nenOK));
            }
         } break;
      case HMI::WRS::MsgId_WIM_PrivacyPopUp_NoPopup:
         {
            vProcessPhoneCallKey(enMsgState, false, false, false, true);
            if (m_u16State != WIM_nenInvalidMsg)
            {
               /* call API setter to notify model */
               API_WIM_vSetWarningConfirmed(m_u16WarnIdDisplay, static_cast<uint8>(KBD_nenBack));
            }
         } break;
      /**** The call ended ***/
      case HMI::WRS::MsgId_WIM_MBCallPressed:
         {
            vProcessPhoneCallKey(enMsgState, false, false, true, false);
         } break;
      default:
         {
         } break;
      }

      /* State has changed, Feedback notification must be send */
      if ((u16StateOld != m_u16State ||
          u16MsgId == HMI::WRS::WIM_DisplayWarning || (boVisibilityChanged)) &&
          m_stVisSendNotif.u8VisibileWidgetCnt > 0)
      {
         /* Sending of notification is required */
         vSetSendNotification();
      }

      return enMsgState;
   }

   void WIMStrategy::vProcessPhoneCallKey(HMI::WCS::enMessageStatus& enMsgState,
      bool boConfirm,
      bool boReject,
      bool boECall,
      bool boBack) const
   {
      if (m_u16State != WIM_nenInvalidMsg)
      {
         // Notify model
         API_WIM_vProcessPhoneCallKey(boConfirm, boReject, boECall, boBack);

         // Consume message
         enMsgState = HMI::WCS::CONSUME_MESSAGE;
      }
   }
} // namespace WIM
