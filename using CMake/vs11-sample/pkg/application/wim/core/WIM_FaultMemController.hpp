/***************************************************************************
*================== Copyright by Continental Automotive GmbH ===============
****************************************************************************
* Titel        : WIM_FaulMemController.hpp
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
* Archive: $Log: WIM_FaultMemController.hpp  $
* Archive: Revision 1.1.2.3 2013/05/17 16:11:43CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 33413: BR213EL/GC, E004, WIM: Takeover of the latest changes from BR205
* Archive: Revision 1.1.2.2 2012/05/18 10:44:16CEST Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
* Archive: Revision 1.4 2012/05/18 10:44:17CEST uid37556 
* Archive: Member moved from WIM_FaultMemController.hpp in project /id/dag_PF3/sw/pkg/wim/core/project.pj[dag_PF3.sw.pkg.wim_COMMON_IC222GC_VarP] to WIM_FaultMemController.hpp in project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj[dag_PF3.sw.pkg.wim_COMMON_GenPF3GC_VarX].
* Archive: Revision 1.3 2012/04/04 14:47:30CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 24870: W222, E007/GC, WIM: Implement changes from Review ORM2907
* Archive: DC MR 25007: W222, E007/GC, WIM: Displacement of handling messages - WDM20280
* Archive: DC MR 25041: Do not specify message propagation in message description files
* Archive: DC MR 25095: W222, E007/GC, WIM: Improvement of Timer accuracy for display role - WDM 25704
* Archive: DC MR 25034: Reduction of lag times in case of vehicle locked
* Archive: DC MR 25393: W222, E007/GC, WIM: No cancel of interval acoustic - WDM31269, ÄLP2895
* Archive: Revision 1.2 2011/11/01 11:41:08CET Brueggemann Alexander (uidt3637) (uidt3637) 
* Archive: Revision derived from delivered sample DC.SW.SYS.222IC_GC_Series_E7.01.38.pre30
* 
*    Rev 1.8   Nov 07 2011 08:11:16   SCHL_Dirk.Gottwalles
* DC MR 23228: W222, E007/GC, WIM: Urgent handling message is not treated urgent
* DC MR 23226: W222, E007/GC, WIM: Change from async acoustic to sync acoustic WDM20336
* DC MR 23230: W222, E007/GC, WIM: Async acoustic blocks urgent display message WDM20376
* DC MR 22977: Integration of ARTEMMIS 3.2.1
* 
*    Rev 1.7   Aug 26 2011 17:25:04   SCHL_Dirk.Gottwalles
* DC MR 22466: W222, E006/AC, WIM: Retrigger on event for AdBlue
* DC MR 22872: Attention Assist output on CAN
* DC MR 22659: W222, E006/AC, WIM: FirstValue flag prohibits delete of warning WDM11861
* DC MR 22153: Support for key handling
* 
*    Rev 1.6   Aug 12 2011 16:39:34   SCHL_Dirk.Gottwalles
* DC MR 22652: W222, E006/AC, SCS: Remove warning management
* DC MR 22655: W222, E006/AC, WIM: Implmentation of complex key handling for warnings
* DC MR 22263: W222, E006/GC, WIM: Remove of unused sound Ids
* DC MR 22549: E006/GC: HIL: Get acoustics status indication for warnings
* DC MR 22686: Implementation of L3 Menu, Warn DB for E006
* DC MR 22733: W222, E006/GC, WIM: Implementation of complex key handling for warnings
* DC MR 21544: E006/GC: HIL: Get TPOL Menu HIL-ID and WIM-HIL-ID
* DC MR 22749: Integration of ARTEMMIS 3.2
* 
*    Rev 1.5   Apr 01 2011 12:48:16   SCHL_Dirk.Gottwalles
* DC MR21947: Takeover of ARTEMMIS 3.1.4
* DC MR21820: Use Widget::boDoesWidgetShow
* DC MR21425: E004/AC, Startup Advanced Parking Control (APC)
* 
*    Rev 1.4   Mar 24 2011 15:44:34   SCHL_Dirk.Gottwalles
* Branch for MR21888
* 
*    Rev 1.2   Dec 17 2010 13:54:40   SCHL_Lars.Gruenewald
* DC MR20897 WIM: Implementation of menu FaultMemory
* 
*    Rev 1.1   Dec 06 2010 10:16:02   SCHL_Lars.Gruenewald
* DC MR20897 WIM: Implementation of menu FaultMemory
* 
*    Rev 1.0   Dec 03 2010 15:54:30   SCHL_Lars.Gruenewald
* Initial revision.
* 
*
* End of Revision History
***************************************************************************/

#ifndef WIM_FAULTMEMCONTROLLER_HPP
#define WIM_FAULTMEMCONTROLLER_HPP

#include "WAS_Service.hpp"
#include "WFC_SceneController.hpp"

namespace WIM 
{
   /** 
   * SceneController has several visuals under it. 
   * Based on the decision of Decider, SceneController will enable the appropriate visual, and inactive all other visual. 
   * @stereotype sealed
   */

   #define nResetTag 0xAA

   class WIMFaultMemController : public HMI::WFC::SceneController 
   {
      public:
         /**
         * Constructor with parameters
         * @param uint16 u16MyID. This is widget ID. It is unique in the whole tree. Default value is 0.
         * @param uint16 u16MyWinID. Window type (1 for managed window and 0 for unmanaged window) . Default value is 1.
         * @param [input] uint16 u16Index. Index for direct message. 			 
         */
         explicit WIMFaultMemController(const uint16 u16MyID , const uint16 u16WinID, const uint16 u16Index);

         /**
         * Setter for index of controller which is associated with this controller container
         * @param [input] int16 i16Index. Index of strategy
         * @return void.
         */
         virtual void vSetControllerByIndex(int16 i16Index);
         
         /**
         * Copy constructor
         * Intentionally made private and not implemented to prohibit usage (noncopyable stereotype)
         */
         WIMFaultMemController(const WIMFaultMemController&);
 
         /**
         * Copy assignment operator
         * Intentionally made private and not implemented to prohibit usage (noncopyable stereotype)
         */
         WIMFaultMemController& operator= (const WIMFaultMemController&);
         
         /**
         * Destructor
         */
         virtual ~WIMFaultMemController( );

         /** 
         * Return widget type
         * @param void.
         * @return HMI::WRS::WidgetClass
         */
         virtual HMI::WRS::WidgetClassID enGetType() const;

      /*-------------------- Setter and Getter --------------------------------------*/
      /**
      * This function is to get the m_u16CurrentWarnID. 
      * @param void
      * @return uint16. Return m_u16CurrentWarnID.
      */
      uint16 u16GetCurrentWarnID_FaultMem(void) const;

      /**
      * This function is to set the m_u16CurrentWarnID. 
      * Additionally a HMI Message is send.
      * @param uint16 u16CurrentWarnID
      * @return void.
      */
      void vSetCurrentWarnID_FaultMem( uint16 u16CurrentWarnID ); 

      /**
      * This function is to get the m_u16FirstWarnID. 
      * @param void
      * @return uint16. Return m_u16FirstWarnID.
      */
      uint16 u16GetFirstWarnID_FaultMem(void) const; 

      /**
      * This function is to set the m_u16FirstWarnID. 
      * @param uint16 u16FirstWarnID
      * @return void.
      */
      void vSetFirstWarnID_FaultMem(uint16 u16FirstWarnID); 
   protected:
      /*------------- Properties ------------------------------------------*/
      /**
      * This attribute stores the id of message should be displayed, after some navigation events etc.
      * (the WIM internal, not the HIL-ID).
      */
      uint16 m_u16CurrentWarnID; 

      /**
      * This attribute stores the id of message should be displayed when the MenuFaultMemory
      * is displayed first (the WIM internal, not the HIL-ID).
      */
      uint16 m_u16FirstWarnID; 
   };
   /********************
   **  CLASS END
   *********************/

   /******************************************************************************
   **							INLINE FUNCTION                                         **
   *******************************************************************************/

   //-------------------------- Get type of widget -----------------------------
   inline HMI::WRS::WidgetClassID WIMFaultMemController::enGetType() const 
   {
      return HMI::WRS::WidgetClassID_WIM_WIMFaultMemController;
   }

   /*------------------------ Set the CurrentWarnID ----------------------------------*/   
   inline void WIM::WIMFaultMemController::vSetCurrentWarnID_FaultMem( uint16 u16CurrentWarnID )
   {
      if(m_u16CurrentWarnID != u16CurrentWarnID)
      {
         m_u16CurrentWarnID = u16CurrentWarnID;
         vNotify(HMI::WRS::WIM_WIMFaultMemControllerPropertyID_CurrentWarnID_FaultMem);
      }

      /* Send HMI Message for self information and context change */
      HMI::WAS::DisplayController::PostMessage(HMI::WRS::MsgId_WIMFaultMemUpdate, (enum HMI::WRS::WidgetIDs)u16GetID(), 0);
   }

   /*------------------------ Get the CurrentWarnID ----------------------------------*/

   inline uint16 WIM::WIMFaultMemController::u16GetCurrentWarnID_FaultMem() const{

      return m_u16CurrentWarnID;

   }

   /*------------------------ Set the FirstWarnID ----------------------------------*/   

   inline void WIM::WIMFaultMemController::vSetFirstWarnID_FaultMem( uint16 u16FirstWarnID ){

      m_u16FirstWarnID = u16FirstWarnID;

   }

   /*------------------------ Get the FirstWarnID ----------------------------------*/

   inline uint16 WIM::WIMFaultMemController::u16GetFirstWarnID_FaultMem() const{

      return m_u16FirstWarnID;

   }
}
#endif /* WIM_FAULTMEMCONTROLLER_HPP */
