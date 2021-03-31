/***************************************************************************
*================== Copyright by Continental Automotive GmbH ===============
****************************************************************************
* Titel        : WIM_SlackController.hpp
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
* Archive: $Log: WIM_SlackController.hpp  $
* Archive: Revision 1.1.1.2 2014/04/04 16:47:47CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj

* Initial revision.
* End of Revision History
***************************************************************************/

#ifndef WIM_SLACKCONTROLLER_HPP
#define WIM_SLACKCONTROLLER_HPP

#include "WFC_SceneController.hpp"        /* include base class interface */

namespace WIM 
{
   /** 
   * SceneController has several visuals under it. 
   * Based on the decision of Decider, SceneController will enable the appropriate visual, and inactive all other visual. 
   * @stereotype sealed
   */
   class SLACKController : public HMI::WFC::SceneController
   {
      public:
         /**
         * Constructor with parameters
         * @param uint16 u16MyID. This is widget ID. It is unique in the whole tree. Default value is 0.
         * @param uint16 u16MyWinID. Window type (1 for managed window nd 0 for unmanaged window) . Default value is 1.
         * @param [input] uint16 u16Index. Index for direct message. 			 
         */
         explicit SLACKController(const uint16 u16MyID , const uint16 u16WinID, const uint16 u16Index);

         /**
         * Setter for index of controller which is associated with this controller container
         * @param [input] int16 i16Index. Index of strategy
         * @return void.
         */
         virtual void vSetControllerByIndex(int16 i16Index);
         
         /**
         * Destructor
         */
         virtual ~SLACKController( );

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
         * Return widget type
         * @param void.
         * @return HMI::WRS::WidgetClass
         */
         virtual HMI::WRS::WidgetClassID enGetType() const;

    private:
         /**
         * Copy constructor
         * Intentionally made private and not implemented to prohibit usage (noncopyable stereotype)
         */
         SLACKController(const SLACKController&);
 
         /**
         * Copy assignment operator
         * Intentionally made private and not implemented to prohibit usage (noncopyable stereotype)
         */
         SLACKController& operator= (const SLACKController&);

         
   };
   /********************
   **  CLASS END
   *********************/

   /******************************************************************************
   **							INLINE FUNCTION                                         **
   *******************************************************************************/

   /*-------------------------- Get type of widget -------------------------------------*/
   inline HMI::WRS::WidgetClassID SLACKController::enGetType() const 
   {
      return HMI::WRS::WidgetClassID_WIM_SLACKController;
   }
}
#endif /* WIM_CONTROLLER_HPP */
