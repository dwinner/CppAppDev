/***************************************************************************
*================== Copyright by Continental Automotive GmbH ===============
****************************************************************************
* Titel        : WIM_ErrorIds.hpp
*
* Description  : This file contains the implementation of class WIMFaultMemController.
*                WIMFaultMemController is the Container for display of warnings in Menu-Fault-Memory.
*                Base type is SceneController, aatched strategy is WIMFaultMemStrategy.
*
* Environment  : ARTEMMIS/JCP2011
*
* Responsible  : Dirk Gottwalles, Schleissheimer GmbH
*
* Guidelines   : SMK 3.6
*
* Template name: VDO Cpp Class
*
* CASE-Tool    : Together, Version 6.1 or higher
*
* Revision List: (Will be filled by PVCS)
* Archive: $Log: WIM_ErrorIds.hpp  $
* Archive: Revision 1.1.1.4 2014/06/06 17:06:33CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 38112 : WIM: Introduction of "Singleline Acknowledgements" - MR47
* Archive: DC MR 40764 : WIM: Changes after code review for single line acknowledgements -  ORM 7144
* Archive: DC MR 40531 : Single line acknowledgement should cancel a running startup animation
* Archive: Revision 1.1.1.3 2013/05/17 16:11:35CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 33413: BR213EL/GC, E004, WIM: Takeover of the latest changes from BR205
* Archive: Revision 1.1.1.2 2012/09/07 17:14:56CEST Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
* Archive: Revision 1.4 2012/09/07 17:14:57CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 27740: W205, E010/GC, WIM: Adaptions for ARTEMMIS 3.4
* Archive: DC MR 28962: W205, E010/GC, WIM: Remove QAC errors
* Archive: DC MR 28968: W205, E010/GC, WIM: Cancel of intervall acoustic for sync acoustic - WDM47461
* Archive: DC MR 27756: BR205 E010: Implement L2 delivery into the software frame (SRSC_Styleguide and XML files)
* Archive: Revision 1.3 2012/05/18 10:45:16CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: Member moved from WIM_ErrorIds.hpp in project /id/dag_PF3/sw/pkg/wim/core/project.pj[dag_PF3.sw.pkg.wim_COMMON_IC222GC_VarP] to WIM_ErrorIds.hpp in project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj[dag_PF3.sw.pkg.wim_COMMON_GenPF3GC_VarX].
* Archive: Revision 1.2 2012/05/04 16:28:32CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 25131: W222, E007/GC, WIM: Implementation of exceptions
* Archive: DC MR 25823: BR222 E7.2: Implementation of L3 delivery (XML-Files)
* Archive: DC MR 21251: W222, E007/GC, WIM: ComplexFunction of Warning 0x2001A6 Kurvenlicht
* Archive: DC MR 25710: W222, E007/GC, WIM: Inactive handling messages show up after 600ms - WDM35020
* Archive: DC MR 25126: W222, E007/GC, WIM: Behaviour of sync acoustics - WDM35391, 35418, 35392, 35389, 35396, 35421
* Archive: Revision 1.1 2012/04/04 14:54:19CEST 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/project.pj
* Archive: Revision 1.2 2011/11/01 11:41:08CET Brueggemann Alexander (uidt3637) (uidt3637) 
* Archive: Revision derived from delivered sample DC.SW.SYS.222IC_GC_Series_E7.01.38.pre30
*
* End of Revision History
***************************************************************************/

//PINT_TBD_WIM:  warning #47-D: incompatible redefinition of macro "__PACKAGE__"
#pragma once
#ifdef __PACKAGE__
#   undef __PACKAGE__
#endif
#define __PACKAGE__ WIM

#ifndef WIM_ERRORIDS_HPP
#define WIM_ERRORIDS_HPP

#include "WES1C1.hpp"

namespace WIM
{

   //--------------- Errors IDs for WIM package ------------------------------
   typedef enum WIM_enErrorIds
   {
      // Required object could not be read
      WIM_nenController_cpp,
      WIM_nenFaultMemStrategy_cpp,
      WIM_nenStrategy_cpp,
      WIM_nenSlackStrategy_cpp
   } tenErrorIds;

}
#endif /* WIM_ERRORIDS_HPP */
