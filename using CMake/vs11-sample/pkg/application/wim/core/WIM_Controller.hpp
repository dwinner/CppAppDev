/***************************************************************************
*================== Copyright by Continental Automotive GmbH ===============
****************************************************************************
* Titel        : WIM_Controller.hpp
*
* Description  : This file contains the definition of class WIMController.
*                WIMController is the Container for display of warnings.
*                Base type is SceneController, aatched strategy is WIMStrategy.
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
* Archive: $Log: WIM_Controller.hpp  $
* Archive: Revision 1.1.2.4 2014/08/18 14:09:10CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 40954: E008/WIM: Introduction of warnings in HUD - ÄLP 7584
* Archive: Revision 1.1.2.3 2013/05/17 16:11:29CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 33413: BR213EL/GC, E004, WIM: Takeover of the latest changes from BR205
* Archive: Revision 1.1.2.2 2013/01/12 16:38:36CET Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
* Archive: Revision 1.6 2013/01/12 16:38:37CET Immel-EXT, Marc (uid37561) 
* Archive: DC MR 31032: BR205: Overtake HMI components for flashing (HMI synchronisation) from IC222
* Archive: DC MR 30978: BR205, E011/GC, WIM: Remove exception raising if HMI reports a canceled warning
* Archive: DC MR 30976: BR205, E011/GC, WIM: Warning disappears before display is off
* Archive: DC MR 25690: W205IC-GC TSA: Prevent popup warning from being displayed when FAS menu is active (ÄLP2802)
* Archive: Revision 1.5 2012/05/18 10:44:17CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: Member moved from WIM_Controller.hpp in project /id/dag_PF3/sw/pkg/wim/core/project.pj[dag_PF3.sw.pkg.wim_COMMON_IC222GC_VarP] to WIM_Controller.hpp in project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj[dag_PF3.sw.pkg.wim_COMMON_GenPF3GC_VarX].
* Archive: Revision 1.4 2012/04/04 13:55:58CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 24870: W222, E007/GC, WIM: Implement changes from Review ORM2907
* Archive: DC MR 25007: W222, E007/GC, WIM: Displacement of handling messages - WDM20280
* Archive: DC MR 25041: Do not specify message propagation in message description files
* Archive: DC MR 25095: W222, E007/GC, WIM: Improvement of Timer accuracy for display role - WDM 25704
* Archive: DC MR 25034: Reduction of lag times in case of vehicle locked
* Archive: DC MR 25393: W222, E007/GC, WIM: No cancel of interval acoustic - WDM31269, ÄLP2895
* Archive: Revision 1.3 2012/03/23 13:40:41CET 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: DC MR 25160: BR222 E7.2: Implement E7.2 L2.2 delivery into the software frame (pre10)
* Archive: DC MR 24661: BR222 E7.2: PrioHandler: Changes after code review
* Archive: Revision 1.2 2011/10/19 11:37:12CEST Brueggemann Alexander (uidt3637) (uidt3637) 
* Archive: Revision derived from delivered sample DC.SW.SYS.222IC_GC_Series_E7.01.38.pre30
* 
*    Rev 1.3   Oct 21 2011 09:54:24   SCHL_Dirk.Gottwalles
* DC MR 23074: BR222: Implementation of E007 pre10 XML-Files and StyleGuide
* DC MR 22734: W222, E006/AC, WIM: Timeout function shall not use first value, WDM1378
* DC MR 23190: Use visibility change detection mechanism
* DC MR 23333: BR222/E007/GC: HIL: Acoustics WIM-REQ (WDM#19107)
* DC MR 22968: W222, E007/GC, WIM: Prio1 mute and partial lowering output WDM20219
* 
*    Rev 1.2   Aug 27 2010 18:50:00   SCHL_Lars.Gruenewald
* DC MR20751  E002/AC, Introduce Warning 120 km/h
* DC MR20742  W222: Startup Modul SBW for E002
* DC MR20810  AC: Warning requests of Fuel Level Gauge (FLG)
* DC MR20835  E002/AC Startup SBC
* DC MR20951  Add property for priority to WIMController
* DC MR20589  BR222: WIM additional functionality for E002
* DC MR20216  ÄLP2191: new requirements for 0x2000F2
* DC MR20377  Exception entries in EXEA made by WIM
* DC MR20759  Implementation of first WarnDB for E002
* 
*    Rev 1.1   Jul 09 2010 18:01:50   SCHL_Lars.Gruenewald
* DC MR 20710 Vr222 WIM: Menue is in Display before warning
* DC MR 20545 WIM: Extension of HMI Interface for E001.2
* 
*    Rev 1.0   Jun 11 2010 14:08:20   SCHL_Thomas.Godemann
* Initial revision.
* End of Revision History
***************************************************************************/

#ifndef WIM_CONTROLLER_HPP
#define WIM_CONTROLLER_HPP

#include "WFC_SceneController.hpp"        /* include base class interface */

/* List template index, when no list template is set */
#define WIM__nNoListTemplate					(0xFFFFu)

namespace WIM 
{
   /** 
   * SceneController has several visuals under it. 
   * Based on the decision of Decider, SceneController will enable the appropriate visual, and inactive all other visual. 
   * @stereotype sealed
   */
   class WIMController : public HMI::WFC::SceneController 
   {
      public:
         /**
         * Constructor with parameters
         * @param uint16 u16MyID. This is widget ID. It is unique in the whole tree. Default value is 0.
         * @param uint16 u16MyWinID. Window type (1 for managed window and 0 for unmanaged window) . Default value is 1.
         * @param [input] uint16 u16Index. Index for direct message. 			 
         */
         explicit WIMController(const uint16 u16MyID , const uint16 u16WinID, const uint16 u16Index);

         /**
         * Setter for index of controller which is associated with this controller container
         * @param [input] int16 i16Index. Index of strategy
         * @return void.
         */
         virtual void vSetControllerByIndex(int16 i16Index);
         
         /**
         * Destructor
         */
         virtual ~WIMController( );

         /**
         * Process messages which are passed from Communication Services. 
         * Special processing by this class is described below:
         * - The message is forwarded to its strategy object (m_poStrategy)
         * - If the strategy changed its state due to the message, this controller prepares to build a new (sub)-scene for that state:
         *   - Pre-destroy message is broadcast to this controller and all its children
         *   - The new sub-tree for the new state is built. (See vBuildChildren( ))
         *   - The z-order of the whole tree is fixed (See vFixZOrder( ))
         *   - Post-build message is broadcast to this controller and all its children
         * - The above is done by the base class implementation, WIMController only adds key handling here 
         * @param [input] HMI::WCS::Message *poMyMsg . A pointer points to message passed to this widget from Communication Services
         * @return HMI::WCS::enMessageStatus. block message flag, pass message flag and consume message flag
         */
         virtual HMI::WCS::enMessageStatus enProcessMessage(HMI::WCS::Message* const poMyMsg);

         /**
			* This method is called when visibility of the widget has changed.
			* @param boNewVisibility - resulting visibility after visibility has changed
			* @return void
			* @author D. Gottwalles, Schleissheimer GmbH
			*/
         virtual void vResultingVisibilityChanged( const bool boNewVisibility );

         /** 
         * Return widget type
         * @param void.
         * @return HMI::WRS::WidgetClass
         */
         virtual HMI::WRS::WidgetClassID enGetType() const;

         /**
			 * This function returns the master state of this controller. 
			 * @param void
			 * @return True  - This is the master controller
          *         False - This is a slave controller
			 */
			bool boGetMasterController(void) const;

         /**
			 * This function is to set the WimControllerId. 
			 * @param uint8 WimControllerId
			 * @return void.
			 */
			void vSetMasterController(bool boMaster);
         
         /**
			 * This function is to get the PrioHandlerPriority. 
			 * @param void
			 * @return uint16. Return m_u16PrioHandlerPriority.
			 */
			uint16 u16GetWimPrioHandlerPriority(void) const;

         /**
			 * This function is to set the PrioHandlerPriority. The priority is used by the master 
             * controller to request its own priority in the widget tree.
			 * @param uint8 PrioHandlerPriority
			 * @return void.
			 */
			void vSetWimPrioHandlerPriority(uint16 u16PrioHandlerPriority);
            
          /**
			 * This function is to set the MenuIdSuppr. 
			 * @param uint32 MenuId
			 * @return void.
			 */
            void vSetMenuIdSuppr(uint16 u16MenuId);

          /**
			 * This function is to set the WarningIdSuppr. 
			 * @param uint32 WarningId
			 * @return void.
			 */
            void vSetWarningIdSuppr(uint16 u16WarningId);

          /**
			 * This function is to set the WarnHilId. 
			 * @param uint32 WarnHilId
			 * @return void.
			 */
            void vSetWarnHilId (uint32 u32WarnHilId);

          /**
			 * This function is to het the WarnHilId. 
			 * @param uint32 WarnHilId
			 * @return void.
			 */
            uint32 u32GetWarnHilId(void) const;

   protected:

         /**
         * This attribute stores the id of current WIM-Widget instance. 
         * Is property configured by WidgetTypeDefinitions.xml
         */
         bool m_boMasterController;

         /**
         * This attribute stores the Priority of current WIM-Widget instance in the PrioHandler. 
         * Is property configured by WidgetTypeDefinitions.xml
         */
         uint16 m_u16PrioHandlerPriority;
        
         /**
         * This attribute stores the list index of the menu IDs that can suppress a specific warning. 
         * Is property configured by WIM_TypeDescriptions.xml
         */
         uint16 m_u16MenuIdSuppr;

         /**
         * This attribute stores the list index of the warning IDs that can be suppressed by a menu. 
         * Is property configured by WIM_TypeDescriptions.xml
         */
         uint16 m_u16WarningIdSuppr;
         
         /**
         * This attribute stores the HIL ID of the current displayed warning for access through HMI model.
         */
         uint32 m_u32WarnHilId;
         /**
         * This function processes the suppression lists and checks if the passed warning ID should be
           suppressed by the menu or not
         */
         bool boIsWarningSuppressed(uint32 u32MenuId, uint32 u32WarningId) const;
     
    private:
         /**
         * Copy constructor
         * Intentionally made private and not implemented to prohibit usage (noncopyable stereotype)
         */
         WIMController(const WIMController&);
 
         /**
         * Copy assignment operator
         * Intentionally made private and not implemented to prohibit usage (noncopyable stereotype)
         */
         WIMController& operator= (const WIMController&);
   };
   /********************
   **  CLASS END
   *********************/

   /******************************************************************************
   **							INLINE FUNCTION                                         **
   *******************************************************************************/

   /*-------------------------- Get type of widget -------------------------------------*/
   inline HMI::WRS::WidgetClassID WIMController::enGetType() const 
   {
      return HMI::WRS::WidgetClassID_WIM_WIMController;
   }

   /*------------------------ Set the master controller --------------------------------*/   
   inline void WIM::WIMController::vSetMasterController( bool boMaster )
   {
      if(m_boMasterController != boMaster)
      {
         m_boMasterController = boMaster;
         vNotify(HMI::WRS::WIM_WIMControllerPropertyID_MasterController);
      }
   }

   /*------------------------ Get the master status of this controller -----------------*/
   inline bool WIM::WIMController::boGetMasterController() const
   {
      return m_boMasterController;
   }

   /*------------------------ Set the WimPrioHandlerPriority ----------------------------------*/   

   inline void WIM::WIMController::vSetWimPrioHandlerPriority( uint16 u16Priority ){

      if(m_u16PrioHandlerPriority != u16Priority)
      {
         m_u16PrioHandlerPriority = u16Priority;
         vNotify(HMI::WRS::WIM_WIMControllerPropertyID_WimPrioHandlerPriority);
      }
   }

   /*------------------------ Get the WimPrioHandlerPriority ----------------------------------*/

   inline uint16 WIM::WIMController::u16GetWimPrioHandlerPriority() const{

      return m_u16PrioHandlerPriority;

   }
   /*------------------------ Set the MenuIdSuppr ----------------------------------*/   

   inline void WIM::WIMController::vSetMenuIdSuppr( uint16 u16MenuIdSupprIndex ){

      if(m_u16MenuIdSuppr != u16MenuIdSupprIndex)
      {
         m_u16MenuIdSuppr = u16MenuIdSupprIndex;
         vNotify(HMI::WRS::WIM_WIMControllerPropertyID_MenuIdSuppr);
      }
   }

   /*------------------------ Set the WarningIdSuppr ----------------------------------*/   

#ifdef QAC_Analysis
#pragma PRQA_MESSAGES_OFF 3231
#endif /* QAC_Analysis */

   inline void WIM::WIMController::vSetWarningIdSuppr( uint16 u16WarnIdSupprIndex ){

      if(m_u16WarningIdSuppr != u16WarnIdSupprIndex)
      {
         m_u16WarningIdSuppr = u16WarnIdSupprIndex;
         vNotify(HMI::WRS::WIM_WIMControllerPropertyID_WarningIdSuppr);
      }
   }

#ifdef QAC_Analysis
#pragma PRQA_MESSAGES_ON 3231
#endif /* QAC_Analysis */

   /*------------------------ Set the WarnHilId ----------------------------------*/

   inline void WIM::WIMController::vSetWarnHilId( uint32 u32WarnHilId ){

      m_u32WarnHilId = u32WarnHilId;
      vNotify(HMI::WRS::WIM_WIMControllerPropertyID_WarnHilId);

   }

   /*------------------------ Get the WarnHilId ----------------------------------*/

   inline uint32 WIM::WIMController::u32GetWarnHilId(void) const
   {
      return m_u32WarnHilId;

   }
}
#endif /* WIM_CONTROLLER_HPP */
