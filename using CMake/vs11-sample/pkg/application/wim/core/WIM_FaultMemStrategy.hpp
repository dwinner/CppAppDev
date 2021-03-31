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
* Archive: $Log: WIM_FaultMemStrategy.hpp  $
* Archive: Revision 1.1.2.3 2013/05/17 16:11:50CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 33413: BR213EL/GC, E004, WIM: Takeover of the latest changes from BR205
* Archive: Revision 1.1.2.2 2012/05/18 10:44:16CEST Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
* Archive: Revision 1.4 2012/05/18 10:44:17CEST uid37556 
* Archive: Member moved from WIM_FaultMemStrategy.hpp in project /id/dag_PF3/sw/pkg/wim/core/project.pj[dag_PF3.sw.pkg.wim_COMMON_IC222GC_VarP] to WIM_FaultMemStrategy.hpp in project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj[dag_PF3.sw.pkg.wim_COMMON_GenPF3GC_VarX].
* Archive: Revision 1.3 2012/04/04 13:57:09CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 24870: W222, E007/GC, WIM: Implement changes from Review ORM2907
* Archive: DC MR 25007: W222, E007/GC, WIM: Displacement of handling messages - WDM20280
* Archive: DC MR 25041: Do not specify message propagation in message description files
* Archive: DC MR 25095: W222, E007/GC, WIM: Improvement of Timer accuracy for display role - WDM 25704
* Archive: DC MR 25034: Reduction of lag times in case of vehicle locked
* Archive: DC MR 25393: W222, E007/GC, WIM: No cancel of interval acoustic - WDM31269, ÄLP2895
* Archive: Revision 1.2 2011/11/01 12:59:30CET Brueggemann Alexander (uidt3637) (uidt3637) 
* Archive: Revision derived from delivered sample DC.SW.SYS.222IC_GC_Series_E7.01.38.pre30
* 
*    Rev 1.2   Nov 07 2011 08:11:18   SCHL_Dirk.Gottwalles
* DC MR 23228: W222, E007/GC, WIM: Urgent handling message is not treated urgent
* DC MR 23226: W222, E007/GC, WIM: Change from async acoustic to sync acoustic WDM20336
* DC MR 23230: W222, E007/GC, WIM: Async acoustic blocks urgent display message WDM20376
* DC MR 22977: Integration of ARTEMMIS 3.2.1
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

#ifndef WIM_FAULTMEMSTRATEGY_HPP
#define WIM_FAULTMEMSTRATEGY_HPP

#include "cdef.h"
#include "WAS_Service.hpp"  /* WidgetAdministrationServices, sending Msgs etc. */


namespace WIM 
{
   /**
    * A ControllerStrategy object has a ProcessMessage( ) method and a state. It can be used as base class
    * for strategy objects to be attached to a WFC::ControllerContainer instance.
    * @stereotype polymorphic, abstract
    */       



   class WIMFaultMemStrategy : public HMI::WSMS::ControllerStrategy
   {
   public:

      /** Build a strategy object with a specified ID. */
      explicit WIMFaultMemStrategy(uint16 u16ControllerID);

      /** Virtual destructor */
      virtual ~WIMFaultMemStrategy() {}


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
   protected:
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
      WIMFaultMemStrategy(const WIMFaultMemStrategy&);
 
      /**
       * Copy assignment operator
       * Intentionally made private and not implemented to prohibit usage (noncopyable stereotype)
       */
      WIMFaultMemStrategy& operator= (const WIMFaultMemStrategy&);
   };
   /********************
   **  CLASS END
   *********************/

   /******************************************************************************
   **                   INLINE FUNCTIONS                                        **
   *******************************************************************************/

} // end namespace WIM

#endif /* WIM_FAULTMEMSTRATEGY_HPP */
