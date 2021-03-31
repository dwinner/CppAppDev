/***************************************************************************
*================== Copyright by Continental Automotive GmbH ===============
****************************************************************************
* Titel        : WIM_SlackStrategy.cpp
*
* Description  : This file contains the definition of class SLACKStrategy.
*                SLACKStrategy is the controller strategy used by
*                SLACKController and delivers the slack to be displayed,
*                and gives feedback via APIM to the HMI
*                external WIM model.
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
* Archive: $Log: WIM_SlackStrategy.cpp  $
* Archive: Revision 1.3.1.7 2014/08/13 17:17:58CEST Immel-EXT, Marc (uid37561)
* Archive: DC MR 42077: WIM: SLACK is displayed with noise
* Archive: DC MR 41987: WIM: Break of 100ms is seen in case of acoustic replacement async to async - #10894
* Archive: DC MR 41983: WIM: Start of "BSM Warnton" output is delayed >300ms - WDM 337
* Archive: DC MR 41981: BR213-EL/E008, WIM: Minimum display time are extended after retriggering - WDM 348
* Archive: DC MR 41975: WIM: Change HIL timing for single line acknowledgements according to customer - WDM257
* Archive: Revision 1.3.1.6 2014/08/08 17:34:02CEST Wagner-EXT, Alexander (uidw3785)
* Archive: DC MR 40697 : Abort of SUA by SLACK via Animation Manager
* Archive: Revision 1.3.1.5 2014/07/18 16:00:29CEST Wagner-EXT, Alexander (uidw3785)
* Archive: DC MR 41550 : WIM: Robustness measures for SLACK state handling and scheduling
* Archive: Revision 1.3.1.4 2014/06/30 15:31:58CEST Wagner-EXT, Alexander (uidw3785)
* Archive: DC MR 41321 : WIM: Patch HMI notification macros for acoustic warnings (integration request)
* Archive: Revision 1.3.1.3 2014/06/06 18:43:02CEST Wagner-EXT, Alexander (uidw3785)
* Archive: DC MR 38112 : WIM: Introduction of "Singleline Acknowledgements" - MR47
* Archive: Revision 1.3.1.2 2014/06/06 17:02:12CEST Wagner-EXT, Alexander (uidw3785)
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
* Initial revision.
* End of Revision History
***************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif
#include "API_c1.h"
#include "DFW_Api.h"
#include "WIM_c1.h"
#ifdef __cplusplus
}
#endif

#include "WIM_SlackStrategy.hpp"
#include "WIM_SlackController.hpp"
#include "WAS_Service.hpp"
/* ErrorIds */
#include "WIM_ErrorIds.hpp"

#define __FILEID__ WIM_nenSlackStrategy_cpp

#ifdef __cplusplus
extern "C"
{
#endif
extern uint8 WIM__u8SlackDisplayBlocked;
#ifdef __cplusplus
}
#endif

namespace WIM
{
   // ------------------------------ Constructor ----------------------------
   SLACKStrategy::SLACKStrategy(uint16 u16ControllerID) :
      ControllerStrategy(u16ControllerID),
      m_boAnimStarted(False),
      m_boAnimActive(False),
      m_oSHMAAnim(),
      m_oSHMABlinkingAnim()
   {
      /* init */
      m_u16State = WIM_nenInvalidMsg;
      m_u16StateRequested = WIM_nenInvalidMsg;
      m_boDisplayOn = False;
      m_u32HilFeedback = 0;
      m_u16SlackIdDisplay = WIM_nenInvalidMsg;
      m_enAnimState = WIM__nenInvalidAnimState;
      m_boResourceAvailable = False;
      m_stVisSendNotif.boSendNotification = False;
   }

   // ------------------------------ Init ----------------------------
   void SLACKStrategy::vInit(void)
   {
      /* call base class */
      HMI::WSMS::ControllerStrategy::vInit();
      /* init state variables */
      m_u16State = WIM_nenInvalidMsg;
      m_u16StateRequested = WIM_nenInvalidMsg;
      m_boDisplayOn = False;
      m_u32HilFeedback = 0;
      m_enAnimState = WIM__nenInvalidAnimState;
      m_boResourceAvailable = False;

      /* Create first endless animation once */
      if (!m_boAnimStarted)
      {
         /* Set flag for animation is created */
         m_boAnimStarted = True;
         /* Create new animation instance */
         HMI::ACE::AnimAssembler::boCreateAnimation(HMI::WRS::Animation_SLAASlidingAnimation, m_oSHMAAnim, this->poGetController(), HMI::WRS::Display_IC_Root, NULL, true);
         HMI::ACE::AnimAssembler::boCreateAnimation(HMI::WRS::Animation_SLAABlinkingAnimation, m_oSHMABlinkingAnim, this->poGetController(), HMI::WRS::Display_IC_Root, NULL, true);
      }

   }

   // ------------------------ Send notification ---------------------
   void SLACKStrategy::vSendNotification()
   {
      /*
      * During this function the value of m_u16StateRequested is confirmed to be in display
      * now. Becasue of this the content of m_u16StateRequested is newer as m_u16SlackIdDisplay.
      * The variable m_u16SlackDisplay therefore holds the old slack and m_u16StateRequested
      * the new slack, until the value of m_u16StateRequested is stored in m_u16SlackIdDisplay
      * at the end of the function.
      */

      /* has anyone requested to send feedback for WIM GC Model */
      if (m_stVisSendNotif.boSendNotification == True)
      {
         /* send the new and old SlackId into WIM GC Model. */
         API_WIM_vSetDisplayedSlack(m_u16StateRequested, m_u16SlackIdDisplay);

         /* Save the requested SlackId as current displayed SlackId. This
          * value will serve as old SlackId for the next feedback
          */
         m_u16SlackIdDisplay = m_u16StateRequested;

         /* the notification was send */
         m_stVisSendNotif.boSendNotification = False;
      }
   }

   void SLACKStrategy::vSendCancelNotification()
   {
      /* Inform WIM GC about a not displayed display request */
      API_WIM_vSetCanceledSlack(m_u16StateRequested);
   }

   // ------------------------ Set Send notification ------------------
   void SLACKStrategy::vSetSendNotification(void)
   {
      /* any has requested a Send Notification next time */
      m_stVisSendNotif.boSendNotification = True;
   }

   // ------------------------ PreDestroy is call from Controller  ------------------
   void WIM::SLACKStrategy::vDeleteRunningAnimPart()
   {
      /* Clear State */
      m_enAnimState = WIM__nenSinkDownDone;
      /* no animation is active */
      m_boAnimActive = False;

      // Delete created instance of animation 
      if (m_oSHMAAnim != NULL)
      {
         m_oSHMAAnim->m_vFinish();
         m_oSHMAAnim = NULL;
      }

      if (m_oSHMABlinkingAnim != NULL)
      {
         m_oSHMABlinkingAnim->m_vFinish();
         m_oSHMABlinkingAnim->vDeactivate();
         m_oSHMABlinkingAnim = NULL;
      }
   }

   void SLACKStrategy::vHandleFadeOutDone()
   {
      switch (m_enAnimState)
      {
      case WIM__nenFloatUpStarted:
         // do nothing
         break;

      case WIM__nenSinkDownStarted:
      {
         m_enAnimState = WIM__nenSinkDownDone;
         m_boAnimActive = False;

         // Update state            
         m_u16State = WIM_nenInvalidMsg;

         // Sending of notification is required 
         vSetSendNotification();

         // Inform other HMI parts about sinked down SLACK 
         HMI::WAS::DisplayController::PostMessage(
            HMI::WRS::MsgID_WIM_DispSlackStatusOff, HMI::WCS::DIRECT_MESSAGE, m_u32HilFeedback);
      }
      break;

      default:
         // in case we had a blinking SLACK stop the blinking here
         m_oSHMABlinkingAnim->vDeactivate();
         break;
      }
   }

   bool SLACKStrategy::boRsbwActive() const
   {      
      const bool boRsbwIsActivated = WIM__u8SlackDisplayBlocked > 0
         ? true     // RSBW sent request to block SLAck's
         : false;   // RSBW didn't send such request

      return boRsbwIsActivated;
   }

   // ------------------------------ Process Messsage ----------------------------
   HMI::WCS::enMessageStatus SLACKStrategy::enProcessMessage(HMI::WCS::Message* poReceivedMsg)
   {
      /* local variables */
      HMI::WCS::enMessageStatus enMsgState = HMI::WCS::PASS_MESSAGE;
      uint16 u16NewState;
      bool boWidgetIsVisible = False;
      uint16 u16MsgId = poReceivedMsg->u16GetID();
      uint32 u32MsgData = poReceivedMsg->u32GetData();
      /* Store the animation id of feedback from AnimManager */
      bool   boVisibilityChanged = false;
      bool   boResAvailChanged = false;
      bool   boOldResourceAvailable = false;
      bool   boAbortDone = false;
      bool   boDisplaySlackEntered = False;
      // Save current state for evaluation if feedback is requried
      uint16 u16StateOld = m_u16State;

      /* get visibility of widget */
      if (m_poController != NULL)
      {
         boWidgetIsVisible = m_poController->boIsVisible();
      }

      switch (u16MsgId)
      {
         /*** Last chance to process any before draw ***/
      case MsgID_LastBeforeDraw:
      {
         if (m_poController != NULL)
         {
            /* send HMI Feedback for WIM GC Model if necessary */
            vSendNotification();
         }
      } break;
      /*** Display a slack or release display of slack ***/
      case HMI::WRS::MsgId_WIM_DisplaySlack:
      {
         /* the new state is in the low-word */
         m_u32HilFeedback = (((uint32)0x00200000) | (u32MsgData & 0xFFFF));
         /* the new slackId is in the high-word */
         u16NewState = (uint16)((u32MsgData >> 16) & 0x3FFF);
         if (u16NewState == (WIM_nenInvalidMsg & 0x3FFF))
            u16NewState = WIM_nenInvalidMsg;
         if (/* if the requested slack is already in the display */
            u16NewState == m_u16SlackIdDisplay)
         {
            /* Sending of notification is required to set application state machine accordingly */
            vSetSendNotification();
         }
         if (/* only if a new slack is requested */
            u16NewState != m_u16StateRequested)
         {
            /* In case that m_u16StateRequested is not the same as the m_u16SlackIdDisplay, the curernt displayed
            *  is not the slack specified in m_u16StateRequested. That means by replacing m_u16StateRequested the
            *  stored slack was never displayed and will never get displayed.
            */
            vSendCancelNotification();
            /* store the new slackId and state */
            m_u16StateRequested = u16NewState;
            /* Set new state for strategy if Display is on and valid Slack is requested */
            if ((m_boDisplayOn == True)
               && (m_u16StateRequested != WIM_nenInvalidMsg))
            {
               m_u16State = m_u16StateRequested;
               boDisplaySlackEntered = True;
            }
         }
      } break;
      /*** Display On Edge ***/
      case HMI::WRS::MsgID_DSM_DisplayOn:
      {
         /* Set the display state On */
         m_boDisplayOn = True;
         /* Set last requested state for strategy, Display is On. */
         m_u16State = m_u16StateRequested;
      } break;
      /*** Display Off Edge ***/
      case HMI::WRS::MsgID_DSM_DisplayOff:
      {
         /* Set the display state Off */
         m_boDisplayOn = False;
         /* Set state invalid for strategy, Display is Off. */
         m_u16State = WIM_nenInvalidMsg;
         if (u16StateOld != m_u16State)
         {
            /* Sending of notification is required */
            vSetSendNotification();
            /* Inform HIL about slack removed from display */
            API_DFW_vSetHilInfoData_HMI(HMI::WRS::Hil_enSlackHilId, 0);
         }
      } break;
      /*** Visibility of widget has changed ***/
      case HMI::WRS::MsgId_ResultingVisibilityChanged:
      {
         boVisibilityChanged = true;
         if ((m_poController != NULL)
            && (m_poController->boIsVisible()))
         {
            if (m_u16State == WIM_nenInvalidMsg)
            {
               /* Create init animation DAA_off */
               /* HMI::AVIAN::AnimationHandle<ANIM::ANTF::InitAnimation> oInitAnimation;
               AVIAN_vCreateAnimation(HMI::WRS::Animation_InitSLACK_Off, oInitAnimation, m_poController); */ /* Vaishnavi */
            }
         }
      } break;
      /*** animation float up done feedback ***/
      case HMI::WRS::MsgID_SLAA_adFadeInDone:
      {
         if (m_enAnimState == WIM__nenFloatUpStarted)
         {
            // Inform HIL about changed slack in display
            API_DFW_vSetHilInfoData_HMI(HMI::WRS::Hil_enSlackHilId, m_u32HilFeedback);
            m_enAnimState = WIM__nenFloatUpDone;
            // Sending of notification is required 
            vSetSendNotification();
         }
      } break;
      /*** animation sink down done feedback ***/
      case HMI::WRS::MsgID_SLAA_adFadeOutDone:
      {
         vHandleFadeOutDone();
      } break;
      /*** Slack ressource availability changed ***/
      case HMI::WRS::MsgId_ResourceAvailabilityChanged:
      {
         boOldResourceAvailable = m_boResourceAvailable;
         if ((m_poController != NULL)
            && (m_poController->boIsResourceSetAvailable(HMI::WFC::nenResSetHMI_Reduced)))
         {
            m_boResourceAvailable = True;
         }
         else
         {
            m_boResourceAvailable = False;
         }
         boResAvailChanged = (boOldResourceAvailable != m_boResourceAvailable);
      } break;
      default:
         break;
      }

      if (  /* state has changed or visibility changed */
         (((u16StateOld != m_u16State) || (boVisibilityChanged) || (boResAvailChanged)
         || (boAbortDone) || (boDisplaySlackEntered == True))
         /*and a we have a valid state */
         && boWidgetIsVisible && (m_u16State != WIM_nenInvalidMsg))
         && (m_boResourceAvailable))
      {
         /* ------------------------ Float Up Animation ------------------*/
         /* Blinking dashes slack is active */
         if (m_u16State == WIM_nen0x201004 /* Limit --- km/h (EzBRM) */
            || m_u16State == WIM_nen0x201006 /* Tempomat --- km/h (EzBRM) */
            || m_u16State == WIM_nen0x201009 /* ADTR --- km/h (EzBRM) */
            )
         {
            m_oSHMABlinkingAnim->vActivateDashes();
         }
         else if (m_u16State == WIM_nen0x201034)/* DTR Sollabstand */
         {
            m_oSHMABlinkingAnim->vActivateCar();
         }
         /* Normal slack is active */
         m_oSHMAAnim->vSlideUp();

         m_enAnimState = WIM__nenFloatUpStarted;
         m_boAnimActive = True;
      }

      if (   /* slack is removed */
         (m_u16State != m_u16StateRequested) && (m_u16StateRequested == WIM_nenInvalidMsg)
         && boWidgetIsVisible
         && (m_boDisplayOn)
         && (m_enAnimState == WIM__nenFloatUpDone))
      {
         if (boRsbwActive())  // Slide down by one frame animation
         {
            m_oSHMAAnim->vSlideDownOneFrame();
         }
         else  // Slide down for 5 seconds
         {
            m_oSHMAAnim->vSlideDown();
         }         

         /* Set internal state that slack sink down started */
         m_enAnimState = WIM__nenSinkDownStarted;

         /* Inform HIL about slack removed from display */
         API_DFW_vSetHilInfoData_HMI(HMI::WRS::Hil_enSlackHilId, 0);
      }

      return enMsgState;
   }
}// namespace WIM
