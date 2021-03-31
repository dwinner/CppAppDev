/***************************************************************************
*================== Copyright by Continental Automotive GmbH ===============
****************************************************************************
* Titel        : WIM_SlackStrategy.hpp
*
* Description  : This file contains the definition of class WIMSlackStrategy.
*                WIMSlackStrategy is the controller strategy used by
*				 WIMSlackController and delivers the slack to be displayed,
* 				 processes keys and gives feedback via APIM to the HMI
* 				 external WIM model.
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
* Archive: $Log: WIM_SlackStrategy.hpp  $
* Archive: Revision 1.3.1.4 2014/08/13 17:18:07CEST Immel-EXT, Marc (uid37561)
* Archive: DC MR 42077: WIM: SLACK is displayed with noise
* Archive: DC MR 41987: WIM: Break of 100ms is seen in case of acoustic replacement async to async - #10894
* Archive: DC MR 41983: WIM: Start of "BSM Warnton" output is delayed >300ms - WDM 337
* Archive: DC MR 41981: BR213-EL/E008, WIM: Minimum display time are extended after retriggering - WDM 348
* Archive: DC MR 41975: WIM: Change HIL timing for single line acknowledgements according to customer - WDM257
* Archive: Revision 1.3.1.3 2014/08/08 17:34:09CEST Wagner-EXT, Alexander (uidw3785)
* Archive: DC MR 40697 : Abort of SUA by SLACK via Animation Manager
* Archive: Revision 1.3.1.2 2014/06/05 13:50:09CEST Wagner-EXT, Alexander (uidw3785)
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
*
* End of Revision History
***************************************************************************/

#ifndef WIM_SLACKSTRATEGY_HPP
#define WIM_SLACKSTRATEGY_HPP

#include "cdef.h"
#include "WSMS_ControllerStrategy.hpp"
#include "ACE_AnimAssembler.hpp"
#include "SLAA_SlidingAnimControl.hpp"
#include "SLAA_BlinkingAnimControl.hpp"

namespace WIM
{
   /**
   * This struct hold the information about the visible Widget instances and
   * if any changed for what we has to send a HMI feedback notification about
   * Displayed slack into the WIM GC Model.
   * It has to be initiated static.
   * @values see structure elements
   */
   typedef struct
   {
      /** If Flag is True Widget with Id has to send HMI Feedback Notification */
      bool boSendNotification;
   }tstVisSendNotifSlack;

   /* This struct defines the animation states for slacks */
   typedef enum
   {
      WIM__nenInvalidAnimState,
      WIM__nenFloatUpStarted,
      WIM__nenFloatUpDone,
      WIM__nenSinkDownStarted,
      WIM__nenSinkDownDone
   }tenSlackAnimState;

   class SLACKStrategy : public HMI::WSMS::ControllerStrategy
   {
   public:

      /** Build a strategy object with a specified ID. */
      explicit SLACKStrategy(uint16 u16ControllerID);

      /** Virtual destructor */
      virtual ~SLACKStrategy() {}

      /* ==================== Accessors ==================== */

      /** Processes message */
      virtual HMI::WCS::enMessageStatus enProcessMessage(HMI::WCS::Message* poReceivedMsg);

      /**
      * This method initializes object to the default state as configured.
      * This method can be overridden by specific strategy implementation.
      * This method is called after construction by the BuildStrategy method.
      * @param void
      * @return void
      */
      virtual void vInit(void);

      /** Send notification to WIM model if slack display state has changed
      * @param void
      * @return void
      */
      void vSendNotification(void);

      /** Call this if Send notification to WIM model has to be done.
      * @param void
      * @return void
      */
      void vSetSendNotification(void);

      /** This function informs the WIM GC model about a cancelled display request.
      * @param void
      * @return void
      */
      void vSendCancelNotification(void);

      /** This function gets the current active style.
      * @param u16CurrentStyle
      * @return void
      */
      void vDeleteRunningAnimPart(void);
      
      /**
       * \brief Handle fade out done
       * \details preventing case WIM__nenFloatUpStarted not to cancel blinking
       */
      void vHandleFadeOutDone();

   protected:
      /**
      * This attribute stores the id current in display showed slack (the WIM internal,
      * not the HIL-ID).
      */
      uint16 m_u16SlackIdDisplay;

      /**
      * This attribute stores the state that was last requested
      * dependent of the Display state it should be similar to m_u16State).
      * DisplayOn  --> m_u16StateRequested == m_u16State
      * DisplayOff --> m_u16StateRequested != m_u16State
      */
      uint16 m_u16StateRequested;

      /**
      * Variable that holds the HIL-ID which is send to HIL
      */
      uint32 m_u32HilFeedback;

      /**
      * This attribute stores the last known state of the Display
      * It is changed by DSM_nDispStrDispOn/OffMsg
      */
      bool m_boDisplayOn;

      /**
      * Resourcen are avaible after boot
      */

      bool m_boResourceAvailable;

      /**
      * This attribute stores the current state of the Slack animation
      */
      WIM::tenSlackAnimState m_enAnimState;

		/**
      * This attribute stores visible Widget instances
      * and if it necessary to send a HMI Feedback into WIM GC Model.
      */
      WIM::tstVisSendNotifSlack m_stVisSendNotif;

		/* Save state into pMem.
      *  Function will not be supported and shall be empty
      */
		virtual void vSerialize(uint16 *pMem, uint16 const u16Size)
		{
         // Empty, see SSD_HMI_148 for details
      }

		/* Restore an object from serialized version pMem
      *  Function will not be supported and shall be empty
      */
		virtual void vDeserialize(uint16 *pMem, uint16 const u16Size)
		{
         // Empty, see SSD_HMI_148 for details
      }

    private:

       /**
       * This attribute stores if Animation is actually started or not
       * Animation should only start first time
       */
       bool m_boAnimStarted;

       /**
       * This attribute stores if Animation is currently running or not
       */
       bool m_boAnimActive;

       /**
       * Handlerobject for the slack animation
       */
       HMI::ACE::AnimCtrlHandle<HMI::SLAA::SLAASlidingAnimation> m_oSHMAAnim;
       HMI::ACE::AnimCtrlHandle<HMI::SLAA::SLAABlinkingAnimation> m_oSHMABlinkingAnim;

       /**
       * Copy constructor
       * Intentionally made private and not implemented to prohibit usage (noncopyable stereotype)
       */
       SLACKStrategy(const SLACKStrategy&);

       /**
       * Copy assignment operator
       * Intentionally made private and not implemented to prohibit usage (noncopyable stereotype)
       */
       SLACKStrategy& operator= (const SLACKStrategy&);

       /**
        * @brief Check if Rear seat belt was activated or not
        * @return true if RSBW is active, false - otherwise
        */
       bool boRsbwActive() const;
   };
} // end namespace WIM
#endif /* WIM_STRATEGY_HPP */
