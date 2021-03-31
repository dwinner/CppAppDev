/***************************************************************************
*================== Copyright by Continental Automotive GmbH ===============
****************************************************************************
* Titel        : WIM_Controller.cpp
*
* Description  : This file contains the implementation of class WIMController.
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
* Archive: $Log: WIM_Controller.cpp  $
* Archive: Revision 1.1.2.8 2014/09/11 18:17:06CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 42474 : WIM: Correct invalid exea exceptions find during internal test and "freeze" of kombi
* Archive: Revision 1.1.2.7 2014/08/26 14:59:16CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 40954 : E008/WIM: Introduction of warnings in HUD - ÄLP 7584
* Archive: Revision 1.1.2.6 2014/08/18 14:09:03CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 40954: E008/WIM: Introduction of warnings in HUD - ÄLP 7584
* Archive: Revision 1.1.2.5 2014/06/06 18:58:59CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 39712 : WIM: Adaptations for new dynamic area HIL ID handling
* Archive: Revision 1.1.2.4 2014/03/28 15:36:43CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 39712 : WIM: Adaptations for new dynamic area HIL ID handling
* Archive: Revision 1.1.2.3 2013/08/16 13:42:49CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 33822 : IC213EL-GC WIM: display synchroneous periodic tone not stopped with display off: WDM62157
* Archive: DC MR 33932 : IC213EL GC WIM: Initial sound requests for warnings does not work if sound system is not ready
* Archive: DC MR 33999 : BR213GC-EL, E005, WIM, CWMDL: API split - ORM5621
* Archive: DC MR 34028 : BR213EL, E005, StyleGuide Validation and implementation
* Archive: DC MR 34202 : BR213IC-GC-EL, WIM: Missing HIL output for seat belt warning acoustics - Folow-Up 33655
* Archive: DC MR 34326 : BR213-GC-EL/E005.1, WIM: Display is on for 2 minutes even when warning has disappeared
* Archive: DC MR 34547 : BR213-EL, E005.1/GC,WIM: Removal of QAC warning
* Archive: DC MR 34706 : BR213-GC-EL, E005.1: Chance DOCG implementation in WIM and TPOL
* Archive: DC MR 34781 : BR213-GC-EL, E005.1, WIM: Inconsistent display output in Fault Memory
* Archive: Revision 1.1.2.2 2013/01/31 18:28:48CET Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
* Archive: Revision 1.11 2013/01/31 18:28:48CET Immel-EXT, Marc (uid37561) 
* Archive: DC MR 31158: W222IC-GC TSA: Prevent popup warning from being displayed when FAS menu is active (ÄLP2802)
* Archive: DC MR 30528: W222, E011/GC, WIM: complex display of warnung ConvertibleTop 0x200527 - ÄLP2745
* Archive: Revision 1.10 2013/01/14 17:57:21CET Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 25690: W205IC-GC TSA: Prevent popup warning from being displayed when FAS menu is active (ÄLP2802)
* Archive: Revision 1.9 2013/01/12 16:38:25CET Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 31032: BR205: Overtake HMI components for flashing (HMI synchronisation) from IC222
* Archive: DC MR 30978: BR205, E011/GC, WIM: Remove exception raising if HMI reports a canceled warning
* Archive: DC MR 30976: BR205, E011/GC, WIM: Warning disappears before display is off
* Archive: DC MR 25690: W205IC-GC TSA: Prevent popup warning from being displayed when FAS menu is active (ÄLP2802)
* Archive: Revision 1.8 2012/09/07 17:15:19CEST Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 27740: W205, E010/GC, WIM: Adaptions for ARTEMMIS 3.4
* Archive: DC MR 28962: W205, E010/GC, WIM: Remove QAC errors
* Archive: DC MR 28968: W205, E010/GC, WIM: Cancel of intervall acoustic for sync acoustic - WDM47461
* Archive: DC MR 27756: BR205 E010: Implement L2 delivery into the software frame (SRSC_Styleguide and XML files)
* Archive: Revision 1.7 2012/08/09 08:49:47CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: D MR 27253: BR205 - Use Global Storage for HMI internal variables
* Archive: Revision 1.6 2012/05/18 10:44:17CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: Member moved from WIM_Controller.cpp in project /id/dag_PF3/sw/pkg/wim/core/project.pj[dag_PF3.sw.pkg.wim_COMMON_IC222GC_VarP] to WIM_Controller.cpp in project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj[dag_PF3.sw.pkg.wim_COMMON_GenPF3GC_VarX].
* Archive: Revision 1.5 2012/04/04 15:04:46CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 24870: W222, E007/GC, WIM: Implement changes from Review ORM2907
* Archive: DC MR 25007: W222, E007/GC, WIM: Displacement of handling messages - WDM20280
* Archive: DC MR 25041: Do not specify message propagation in message description files
* Archive: DC MR 25095: W222, E007/GC, WIM: Improvement of Timer accuracy for display role - WDM 25704
* Archive: DC MR 25034: Reduction of lag times in case of vehicle locked
* Archive: DC MR 25393: W222, E007/GC, WIM: No cancel of interval acoustic - WDM31269, ÄLP2895
* Archive: Revision 1.4 2012/03/23 12:31:13CET 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: DC MR 25160: BR222 E7.2: Implement E7.2 L2.2 delivery into the software frame (pre10)
* Archive: DC MR 24661: BR222 E7.2: PrioHandler: Changes after code review
* Archive: Revision 1.3 2012/02/22 17:32:07CET 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: DC MR 24333: W222, E007/GC, WIM: HIL output for requested sound not working
* Archive: DC MR 24043: Move tube request from WIM to WarningStandard.xml
* Archive: DC MR 23682: W222, E007/GC, WIM: Acousic only messsage does not block display WDM21148
* Archive: DC MR 24086: W222, E007/GC, WIM: Short rest after warning display is not always 5 seconds
* Archive: DC MR 24332: W222, E007/GC, WIM: Warnings can not be acknowledged with Nview active
* Archive: Revision 1.2 2011/11/01 11:41:08CET Brueggemann Alexander (uidt3637) (uidt3637) 
*
*    Rev 1.22   Jan 13 2012 16:18:56   SCHL_Dirk.Gottwalles
* DC MR 24093: W222, E007/GC, WIM: Acoustic warning does not block display - WDM20499
* DC MR 23683: W222, E007/GC, WIM: Sync acoustic is cancelled by async acoustic WDM21143
* DC MR 24088: W222, E007/GC, WIM: Warning blocks display WDM22837, WDM23219
* DC MR 24089: W222,E007,AC, WIM: New configuration values Chauffeur_Avl and ShiftStyle_Variant
* DC MR 24343: W222, E007/AC, WIM: Patch for 0x2000BC and 0x2000C1 (Country coding), WDM23191
* 
*    Rev 1.21   Nov 07 2011 08:11:16   SCHL_Dirk.Gottwalles
* DC MR 23228: W222, E007/GC, WIM: Urgent handling message is not treated urgent
* DC MR 23226: W222, E007/GC, WIM: Change from async acoustic to sync acoustic WDM20336
* DC MR 23230: W222, E007/GC, WIM: Async acoustic blocks urgent display message WDM20376
* DC MR 22977: Integration of ARTEMMIS 3.2.1
* 
*    Rev 1.20   Oct 21 2011 09:54:24   SCHL_Dirk.Gottwalles
* DC MR 23074: BR222: Implementation of E007 pre10 XML-Files and StyleGuide
* DC MR 22734: W222, E006/AC, WIM: Timeout function shall not use first value, WDM1378
* DC MR 23190: Use visibility change detection mechanism
* DC MR 23333: BR222/E007/GC: HIL: Acoustics WIM-REQ (WDM#19107)
* DC MR 22968: W222, E007/GC, WIM: Prio1 mute and partial lowering output WDM20219
* 
*    Rev 1.19   Sep 20 2011 10:12:30   SCHL_Dirk.Gottwalles
* DC MR 22971: W205, E006/GC, WIM: Remove of not supported HMI messages
* 
*    Rev 1.18   Aug 26 2011 17:25:04   SCHL_Dirk.Gottwalles
* DC MR 22466: W222, E006/AC, WIM: Retrigger on event for AdBlue
* DC MR 22872: Attention Assist output on CAN
* DC MR 22659: W222, E006/AC, WIM: FirstValue flag prohibits delete of warning WDM11861
* DC MR 22153: Support for key handling
* 
*    Rev 1.17   Aug 12 2011 16:39:36   SCHL_Dirk.Gottwalles
* DC MR 22652: W222, E006/AC, SCS: Remove warning management
* DC MR 22655: W222, E006/AC, WIM: Implmentation of complex key handling for warnings
* DC MR 22263: W222, E006/GC, WIM: Remove of unused sound Ids
* DC MR 22549: E006/GC: HIL: Get acoustics status indication for warnings
* DC MR 22686: Implementation of L3 Menu, Warn DB for E006
* DC MR 22733: W222, E006/GC, WIM: Implementation of complex key handling for warnings
* DC MR 21544: E006/GC: HIL: Get TPOL Menu HIL-ID and WIM-HIL-ID
* DC MR 22749: Integration of ARTEMMIS 3.2
* 
*    Rev 1.16   Jul 29 2011 14:06:46   SCHL_Dirk.Gottwalles
* DC MR 22188: Controller containers should not call methods of their strategies
* DC MR 22573: E006/AC DPOOL Define Data Braces, remove compiler warning
* DC MR 22334: BR222: SBW sound in Phase 4 WDM10279
* DC MR 22312: W222, E006/AC, WIM: Mute and partial acoutic lowering delay, OPL528
* 
*    Rev 1.15   Jul 13 2011 15:35:38   SCHL_Dirk.Gottwalles
* DC MR 22485: BR222, E006 Implementation of xml-files and style guide
* DC MR 22396: BR222: New acoustic for rearseatbeltwarning ÄLP2571
* DC MR 22456: Permanent Display menu - hybrid (GC)
* DC MR 21811: BR222: WIM: New Keywords/functions ÄLP2444, Part II
* DC MR 22265: W222, E006/AC, WIM:Change of Timeout behaviour
* DC MR 22261: W222, E006/AC, WIM: New keyword for WarnDB TIMEOUT_NOT_ENG_START, ÄLP2574
* DC MR 22260: W222, E006/AC, WIM: New keyword for WarnDB TIMEOUT_KL15_NOT_ENG_START, ÄLP2573
* DC MR 22092: W222, E006/AC, WIM: Door warning state is not correct evaluated for undefined values
* 
*    Rev 1.14.1.0   Jun 10 2011 09:34:24   SCHL_Dirk.Gottwalles
* DC MR 22144: Introduction of Day-Night scene switching (part 2 with animation, E005)
* 
*    Rev 1.14   Apr 01 2011 12:48:16   SCHL_Dirk.Gottwalles
* DC MR21947: Takeover of ARTEMMIS 3.1.4
* DC MR21820: Use Widget::boDoesWidgetShow
* DC MR21425: E004/AC, Startup Advanced Parking Control (APC)
* 
*    Rev 1.13   Mar 24 2011 15:44:34   SCHL_Dirk.Gottwalles
* Branch for MR21888
* 
*    Rev 1.11   Mar 22 2011 16:07:24   SCHL_Dirk.Gottwalles
* DC MR21742: AC-E004-System: Introduction Boardtestmode
* DC MR21178: BR222 WIM: Suppression of Sound
* DC MR21659: E004/AC, WIM: Proper intergration of KL15 events
* DC MR21660: E004/AC, WIM: Extension of ManuQuit callback
* DC MR21661: E004/GC, WIM: Extension of ManuQuit callback
* DC MR21657: E004/GC, Wrong Hil-ID on CAN when display goes into sleep
* DC MR21743: GC-E004-System: Introduction Boardtestmode
* DC MR21256: Implementation of L1 WarnDB for E004
* DC MR21663: E004/AC, WIM: 0x2001D8 wird nicht mit KONFIG(SOFA_Elektrik) angezeigt
* DC MR21618: Follow-Up 21009 - Supress sound of front-lid-warning with SID 31,01,00,17
* DC MR21801: WIM: No scene switch to Full tubes when warning becomes activated
* 
*    Rev 1.10   Nov 19 2010 16:04:18   SCHL_Dirk.Gottwalles
* DC MR21122 BR222: WIM reaction at wakeupreq.
* DC MR21302 BR222/AC: Optimierung Aufruf Checkfunktion WIM
* DC MR20423 W222: WIM new acoustics requirements
* DC MR21177 Implementation of first WarnDB for E003
* DC MR21336 WIM: Using Enumeration Symbols for State/Widget Mapping
* 
*    Rev 1.9   Sep 09 2010 11:29:42   SCHL_Lars.Gruenewald
* DC MR20928 WIMController does not initialize attribute ControllerId
* 
*    Rev 1.8   Aug 27 2010 18:50:00   SCHL_Lars.Gruenewald
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
*    Rev 1.7   Aug 05 2010 18:35:28   SCHL_Thomas.Godemann
* DC MR20853 E1.2 Projecthouse Backlog Items: Changes in API-F and Applications
* 
*    Rev 1.6   Jul 19 2010 11:35:12   SCHL_Thomas.Godemann
* DC MR20642 Startup-MR for startup screen manager, E001.2
* 
*    Rev 1.5   Jul 12 2010 16:39:50   SCHL_Lars.Gruenewald
* DC MR 20545 WIM: Extension of HMI Interface for E001.2
* 
*    Rev 1.4   Jul 09 2010 18:01:50   SCHL_Lars.Gruenewald
* DC MR 20710 Vr222 WIM: Menue is in Display before warning
* DC MR 20545 WIM: Extension of HMI Interface for E001.2
* 
*    Rev 1.3   Jun 28 2010 18:49:08   SCHL_Lars.Grünewald
* DC MR 20620 Startup-MR for dynamical area manager (prio)
* 
*    Rev 1.2   Jun 26 2010 15:36:32   SCHL_Thomas.Godemann
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
*    Rev 1.0   Jun 11 2010 14:08:12   SCHL_Thomas.Godemann
* Initial revision.
* End of Revision History
****************************************************************************/

#ifdef __cplusplus
extern "C" 
{
#endif

   #include "cdef.h"
   #include "WIM_c1.h"
   #include "API_C1.h"
   //#include "TPOL_C1.h"

#ifdef __cplusplus
}
#endif

#include "WIM_Controller.hpp"                              /* own header   */
#include "WIM_Strategy.hpp"                                /* strategy     */

#include "WRS_VisualTypesIDs.hpp"                          /* for class ID */
#include "WRS_ListValuesGetter.hpp"
#include "DSM_PrioHandler.hpp"                             /* PrioHandler  */
#include "DSM_PrioHandlerInfo.hpp"
#include "WAS_Service.hpp"
#include "WAS_DisplayController.hpp"
#include "WRS_ExternalEventDefinitions.h"
#include "WRS_GlobalStorage.hpp"                            /* Global Variables */

#include "WIM_ErrorIds.hpp"
#define __FILEID__ WIM_nenController_cpp

namespace WIM 
{
   // ---------------------------------- Constructor -----------------------------
   WIMController::WIMController(const uint16 u16MyID, 
                                const uint16 u16WinID, 
                                const uint16 u16Index)
   : HMI::WFC::SceneController( u16MyID , u16WinID, u16Index)
   {
      /* initialisation */
      m_u16PrioHandlerPriority = 0;
      /* Initialize as Slave controller, because master instance will request FullTubes */
      m_boMasterController = False;
      m_u16MenuIdSuppr = WIM__nNoListTemplate;
      m_u16WarningIdSuppr = WIM__nNoListTemplate;
      m_u32WarnHilId          = 0;
   }

   void WIMController::vSetControllerByIndex (int16 id) 
   {
      /* just call parent implementation */
      HMI::WFC::SceneController::boSetStrategyByID (id) ; /* @ThGa: Patched */
   }

   // ----------------------------------- Destructor -----------------------------
   WIMController::~WIMController() 
   {
      /* deinitialisation */
   }
#include "WAS_DisplayController.hpp"      
   // ------------------------------ Process Messsage ----------------------------
   HMI::WCS::enMessageStatus WIMController::enProcessMessage(HMI::WCS::Message* const poReceivedMsg) 
   {
      HMI::WCS::enMessageStatus enMsgState = HMI::WCS::PASS_MESSAGE;
      WIMStrategy* poMyStrategy = NULL;
      uint16 u16StateOld = (uint16)WIM_nenInvalidMsg;
      uint16 u16StateNew = (uint16)WIM_nenInvalidMsg;
      uint16 u16StateReqOld = (uint16)WIM_nenInvalidMsg;
      uint32 u32MenuHilId = 0;
      uint32 u32WarnHilId = 0;
      uint16 u16WarnId = 0;
      uint32 u32TpolHilId = 0;
      uint16 u16MsgId = 0;
      uint32 u32MsgData = 0;
      bool boSupprWarning = False;
      HMI::WAS::DisplayController *oDisplayController = NULL;

      /* get strategy object */
      poMyStrategy = (WIMStrategy*)poGetStrategy();
      /* Store current strategy status */
      if(poMyStrategy != NULL)
      {
         u16StateOld = poMyStrategy->u16GetState();
         u16StateReqOld = poMyStrategy->u16GetStateRequested();
      }
      if (poReceivedMsg)
      {
         u16MsgId = poReceivedMsg->u16GetID();
         u32MsgData = poReceivedMsg->u32GetData();
      }
      /* if message WIM_DisplayWarning was received, check suppression before */
      if ( u16MsgId == HMI::WRS::WIM_DisplayWarning)
      {
          /* get current menu HIL-Id from TPOL */
          u32TpolHilId = HMI::WRS::GetGlobalData(HMI::WRS::GlobalVariable_TPOL_u32CurrHilId);
          u32MenuHilId = (uint32)((u32TpolHilId & 0xFFFFFF) << 8);
          /* get current warning HIL-Id */
          u32WarnHilId = ((uint32)0x20000000) | ((u32MsgData & 0xFFFF)<<8);
          /* get current warning ID */
          u16WarnId = (uint16)(u32MsgData >> 16);
          if (u16WarnId == WIM_nenInvalidMsg)
              u16WarnId = WIM_nenInvalidMsg;
          /* Check if warning should be suppressed by menu */
          if (   (m_boMasterController)
              /*&& (u32TpolHilId & TPOL_nHilInfoValidFlag)*/
              && (boIsWarningSuppressed(u32MenuHilId, u32WarnHilId) == True))
          {
              /* set suppressed Warn ID in API */
              API_WIM_vSetSuppressedWarning(u16WarnId);
              boSupprWarning = True;
          }
      }
      /* react on message only if warning should not be suppressed */
      if(   poReceivedMsg
         && !boSupprWarning )
      {
         /* call base class method */
         enMsgState = HMI::WFC::SceneController::enProcessMessage(poReceivedMsg);
         if (poMyStrategy)
         {
            /*** FORWARD m_u16State as HIL-ID ***/
            /* Has the state changed? */
            u16StateNew = poMyStrategy->u16GetState();
            if(u16StateOld != u16StateNew)
            {
               if (u16StateNew != WIM_nenInvalidMsg)
               {
                  /* make the full Hil-Id and store it in property */
                  uint32 u32HilId = poMyStrategy->u32GetHilIdRequested();
                  vSetWarnHilId(u32HilId >> 8);
                  /* Set Hil-Id by API-Function */
                  HMI::WRS::SetGlobalData(HMI::WRS::GlobalVariable_WIM_GVenDispWarning, u32HilId);
                  /* ForcedPaint trigger for current display */
                  oDisplayController = poGetDisplay();
                  if (oDisplayController != NULL) 
                  {
                  HMI::WAS::Framework::TriggerForcedPaint();
                  }
               }
               else
               {
                  /* Reset Hil-Id in property */
                  vSetWarnHilId(0);
                  /* Set no warning (0) by API-Function */
                  HMI::WRS::SetGlobalData(HMI::WRS::GlobalVariable_WIM_GVenDispWarning, 0);
               }
            }
         }
         else
         {
            WIM__mThrowHMIError(WIM_nExcNoObject);
         }
      }
      else
      {
      }
      /* result of message processing */
      return enMsgState;
   }

   // ------------------------------ Switch visibility ----------------------------
   void WIMController::vResultingVisibilityChanged( const bool boNewVisibility )
   {
      uint32 u32MsgData;

      /* Set Controller visibility Flag, next time the Strategy has to send feedback... */
      u32MsgData = (uint8)boNewVisibility;
      /* Send message */
      HMI::WAS::DisplayController::PostMessage(HMI::WRS::MsgId_WIM_SetCtrlrVisibility, (enum HMI::WRS::WidgetIDs)u16GetID(), u32MsgData);
   }

   // ------------------------------ Warning suppression ----------------------------
   bool WIMController::boIsWarningSuppressed(uint32 u32MenuId, uint32 u32WarningId) const
   {
      uint16 u16MenuListCount;
      uint16 u16WarnListCount;
      bool boReturn = False;
      /* are the list IDs valid */
      if (  (m_u16MenuIdSuppr != WIM__nNoListTemplate)
          &&(m_u16WarningIdSuppr != WIM__nNoListTemplate))
      {
          /* get number of entries in config lists */
          u16MenuListCount = HMI::WRS::ListValuesGetter::GetCountEntriesInInitalizerArray( m_u16MenuIdSuppr );
          u16WarnListCount = HMI::WRS::ListValuesGetter::GetCountEntriesInInitalizerArray( m_u16WarningIdSuppr );
          if (u16MenuListCount != u16WarnListCount)
          {
          /* Error, wrong config */
          WIM__mThrowHMIError(WIM_nErrConfig);
          }
          else
          {
              /* search for warning ID that should be suppressed by menu */
              for (uint16 u16ValueIndex = 0; u16ValueIndex < u16MenuListCount; u16ValueIndex++)
              {
                  if (HMI::WRS::ListValuesGetter::GetIntInInitalizerArray(m_u16MenuIdSuppr, u16ValueIndex) == u32MenuId)
                  {
                      if (HMI::WRS::ListValuesGetter::GetIntInInitalizerArray(m_u16WarningIdSuppr, u16ValueIndex) == u32WarningId)
                      {
                          boReturn = True;
                          break;
                      }
                  }
              }
          }
      }
      else
      {
          /* Error, wrong config */
          WIM__mThrowHMIError(WIM_nErrConfig);
      }
      return boReturn;
   }
} // namespace WIM

