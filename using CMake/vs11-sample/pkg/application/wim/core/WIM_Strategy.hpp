/***************************************************************************
*================== Copyright by Continental Automotive GmbH ===============
****************************************************************************
* Titel        : WIM_Strategy.hpp
*
* Description  : This file contains the definition of class WIMStrategy.
*                WIMStrategy is the controller strategy used by WIMController
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
* Archive: $Log: WIM_Strategy.hpp  $
* Archive: Revision 1.1.2.3 2013/05/17 16:12:12CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 33413: BR213EL/GC, E004, WIM: Takeover of the latest changes from BR205
* Archive: Revision 1.1.2.2 2012/05/18 10:44:16CEST Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
* Archive: Revision 1.6 2012/05/18 10:44:17CEST uid37556 
* Archive: Member moved from WIM_Strategy.hpp in project /id/dag_PF3/sw/pkg/wim/core/project.pj[dag_PF3.sw.pkg.wim_COMMON_IC222GC_VarP] to WIM_Strategy.hpp in project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj[dag_PF3.sw.pkg.wim_COMMON_GenPF3GC_VarX].
* Archive: Revision 1.5 2012/04/04 14:01:40CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 24870: W222, E007/GC, WIM: Implement changes from Review ORM2907
* Archive: DC MR 25007: W222, E007/GC, WIM: Displacement of handling messages - WDM20280
* Archive: DC MR 25041: Do not specify message propagation in message description files
* Archive: DC MR 25095: W222, E007/GC, WIM: Improvement of Timer accuracy for display role - WDM 25704
* Archive: DC MR 25034: Reduction of lag times in case of vehicle locked
* Archive: DC MR 25393: W222, E007/GC, WIM: No cancel of interval acoustic - WDM31269, ÄLP2895
* Archive: Revision 1.4 2012/02/21 13:36:29CET 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: DC MR 24333: W222, E007/GC, WIM: HIL output for requested sound not working
* Archive: DC MR 24043: Move tube request from WIM to WarningStandard.xml
* Archive: DC MR 23682: W222, E007/GC, WIM: Acousic only messsage does not block display WDM21148
* Archive: DC MR 24086: W222, E007/GC, WIM: Short rest after warning display is not always 5 seconds
* Archive: DC MR 24332: W222, E007/GC, WIM: Warnings can not be acknowledged with Nview active
* Archive: Revision 1.3 2012/01/13 11:54:42CET 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: DC MR 24093: W222, E007/GC, WIM: Acoustic warning does not block display - WDM20499
* Archive: DC MR 23683: W222, E007/GC, WIM: Sync acoustic is cancelled by async acoustic WDM21143
* Archive: DC MR 24088: W222, E007/GC, WIM: Warning blocks display WDM22837, WDM23219
* 
*    Rev 1.4   Nov 07 2011 08:11:18   SCHL_Dirk.Gottwalles
* DC MR 23228: W222, E007/GC, WIM: Urgent handling message is not treated urgent
* DC MR 23226: W222, E007/GC, WIM: Change from async acoustic to sync acoustic WDM20336
* DC MR 23230: W222, E007/GC, WIM: Async acoustic blocks urgent display message WDM20376
* DC MR 22977: Integration of ARTEMMIS 3.2.1
* 
*    Rev 1.3   Nov 19 2010 16:04:26   SCHL_Dirk.Gottwalles
* DC MR21122 BR222: WIM reaction at wakeupreq.
* DC MR21302 BR222/AC: Optimierung Aufruf Checkfunktion WIM
* DC MR20423 W222: WIM new acoustics requirements
* DC MR21177 Implementation of first WarnDB for E003
* DC MR21336 WIM: Using Enumeration Symbols for State/Widget Mapping
* 
*    Rev 1.2   Jul 09 2010 18:01:50   SCHL_Lars.Gruenewald
* DC MR 20710 Vr222 WIM: Menue is in Display before warning
* DC MR 20545 WIM: Extension of HMI Interface for E001.2
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
*    Rev 1.0   Jun 11 2010 14:08:42   SCHL_Thomas.Godemann
* Initial revision.
* End of Revision History
***************************************************************************/

#ifndef WIM_STRATEGY_HPP
#define WIM_STRATEGY_HPP

#include "cdef.h"
#include "WSMS_ControllerStrategy.hpp"

namespace WIM 
{
   /**
   * This struct hold the information about the visible Widget instances and
   * if any changed for what we has to send a HMI feedback notification about
   * Displayed Warning into the WIM GC Model.
   * It has to be initiated static.
   * @values see structure elements
   */
   typedef struct
   {
      /** Bitfield for Visibility of Widget instances */
      uint8 u8VisibileWidgetCnt;

      /** If Flag is True Widget with Id has to send HMI Feedback Notification */
      bool boSendNotification;

   }tstVisSendNotif;

   class WIMStrategy : public HMI::WSMS::ControllerStrategy
   {
   public:

      /** Build a strategy object with a specified ID. */
      explicit WIMStrategy(uint16 u16ControllerID);

      /** Virtual destructor */
      virtual ~WIMStrategy() {}

      /* ==================== Accessors ==================== */
      /**
      * Returns the warning state, last requested by WIM.
      */
      uint16 u16GetStateRequested() const { return m_u16StateRequested; }

      /**
      * Returns the HIL-ID of the warning, last requested by WIM.
      */
      uint32 u32GetHilIdRequested() const { return m_u32HilIdRequested; }

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

      /** Send notification to WIM model if warning display state has changed
      * @param boVisible: indicates, if WIMController is visible or not
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
      void vSendCancelNotification(void) const;

      /** This method is called if the visibility of the widget has changed.
      * @param boVisibility - New visibility information
      * @return void
      */
      void vSetControllerVisibility(bool boVisibility);      

   protected:      
      /**
      * This attribute stores the id of current requested warning (the WIM internal, 
      * not the HIL-ID). When this warning comes to display and the WIM on GC has been 
      * informed then this value is copied to m_u16WarnIdDisplay.
      */
      uint16 m_u16WarnIdReq;

      /**
      * This attribute stores the id current in display showed warning (the WIM internal, 
      * not the HIL-ID).
      */
      uint16 m_u16WarnIdDisplay;

      /**
      * This attribute stores the short HIL-ID, was last requested
      * dependent of the Display state it should be similar to m_u16State).
      * DisplayOn  --> m_u16StateRequested == m_u16State
      * DisplayOff --> m_u16StateRequested != m_u16State
      */
      uint16 m_u16StateRequested;

      /**
      * This attribute stores the HIL-ID, which was last requested
      */
      uint32 m_u32HilIdRequested;

      /**
      * This attribute stores the last known state of the Display
      * It is changed by DSM_nDispStrDispOn/OffMsg
      */
      bool m_boDisplayOn;

      /**
      * This attribute stores visible Widget instances
      * and if it necessary to send a HMI Feedback into WIM GC Model.
      */
      WIM::tstVisSendNotif m_stVisSendNotif;


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
       * Copy constructor
       * Intentionally made private and not implemented to prohibit usage (noncopyable stereotype)
       */
       WIMStrategy(const WIMStrategy&);
 
       /**
       * Copy assignment operator
       * Intentionally made private and not implemented to prohibit usage (noncopyable stereotype)
       */
       WIMStrategy& operator= (const WIMStrategy&);
             
      /**
        * Process privacy pop up confirmation
        *   @param enMsgState   Message state
        *   @param boConfirm    true if confirmed, false otherwise
        *   @param boReject     true if rejected, false otherwise
        *   @param boECall      true if call ended, flase otherwise
        */
       void vProcessPhoneCallKey(HMI::WCS::enMessageStatus& enMsgState,
          bool boConfirm,
          bool boReject,
          bool boECall,
          bool boBack) const;
   };
} // end namespace WIM

#endif /* WIM_STRATEGY_HPP */
