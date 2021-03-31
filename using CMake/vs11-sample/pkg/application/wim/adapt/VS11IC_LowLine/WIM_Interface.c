/******************************************************************************
*=====================    Copyright by Continental AG    ======================
*******************************************************************************
* Titel        : WIM_Interface.c
*
* Description  : exported functions of package WIM
*                All functions of the package that are externally visible are 
*                coded here (system and client interfaces)
*
* Responsible  : L.Gruenewald, Schleissheimer GmbH
*
* Guidelines   : SMK 3.3  
*
* Template name: OOLite Codefile, Revision 1.0
*
* CASE-Tool    : Together Controlcenter, Version 6.2
*
* Revision List: (Will be filled by PVCS)
* Archive: $Log: WIM_Interface.c  $
* Archive: Revision 1.1.3.8 2014/07/18 15:59:34CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 41550 : WIM: Robustness measures for SLACK state handling and scheduling
* Archive: Revision 1.1.3.7 2014/06/06 17:04:10CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 38112 : WIM: Introduction of "Singleline Acknowledgements" - MR47
* Archive: DC MR 40764 : WIM: Changes after code review for single line acknowledgements -  ORM 7144
* Archive: DC MR 40531 : Single line acknowledgement should cancel a running startup animation
* Archive: Revision 1.1.3.6 2014/03/21 13:00:16CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 39839 : BR205 E013: ALP3289 new warning 0x200542(Hybrid) 
* Archive: DC MR 40021 : WIM: Sound of FCW warning is not retriggered after reset
* Archive: Revision 1.1.3.5 2013/11/22 17:22:24CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 36779 : BR213EL, E006, Implementation of new WarnDB
* Archive: DC MR 36462 : WIM: Implement new scheduling and state handling for acoustic part
* Archive: Revision 1.1.3.4 2013/09/17 13:23:52CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 34944: WIM: Persistent storage of warn states for wake-IC warnings
* Archive: DC MR 34942: BR213, WIM: Acoustic of door warning shall not be retriggered by another door
* Archive: Revision 1.1.3.3 2013/08/16 13:32:49CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 33822 : IC213EL-GC WIM: display synchroneous periodic tone not stopped with display off: WDM62157
* Archive: DC MR 33932 : IC213EL GC WIM: Initial sound requests for warnings does not work if sound system is not ready
* Archive: DC MR 33999 : BR213GC-EL, E005, WIM, CWMDL: API split - ORM5621
* Archive: DC MR 34028 : BR213EL, E005, StyleGuide Validation and implementation
* Archive: DC MR 34202 : BR213IC-GC-EL, WIM: Missing HIL output for seat belt warning acoustics - Folow-Up 33655
* Archive: DC MR 34326 : BR213-GC-EL/E005.1, WIM: Display is on for 2 minutes even when warning has disappeared
* Archive: DC MR 34547 : BR213-EL, E005.1/GC,WIM: Removal of QAC warning
* Archive: DC MR 34706 : BR213-GC-EL, E005.1: Chance DOCG implementation in WIM and TPOL
* Archive: DC MR 34781 : BR213-GC-EL, E005.1, WIM: Inconsistent display output in Fault Memory
* Archive: Revision 1.1.3.2 2013/01/21 12:08:25CET Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3/project.pj
* Archive: Revision 1.18 2013/01/21 12:08:25CET Immel-EXT, Marc (uid37561) 
* Archive: DC MR 30335: BR205/E011/GC: DIM: Update SwillLvl turn-on condition (Exlude Warning without wake-reason)
* Archive: DC MR 31127: Change allocator of CIA memory pool from flexible to static
* Archive: DC MR 31152: BR205, E011/GC, WIM: Waking up the display is not possible if another wake IC warning is active
* Archive: DC MR 31154: BR205 E011/GC, WIM: Wrong transition in case of display cancel event
* Archive: Revision 1.17 2013/01/12 16:43:17CET Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 31032: BR205: Overtake HMI components for flashing (HMI synchronisation) from IC222
* Archive: DC MR 30978: BR205, E011/GC, WIM: Remove exception raising if HMI reports a canceled warning
* Archive: DC MR 30976: BR205, E011/GC, WIM: Warning disappears before display is off
* Archive: DC MR 25690: W205IC-GC TSA: Prevent popup warning from being displayed when FAS menu is active (ÄLP2802)
* Archive: Revision 1.16 2013/01/10 18:47:03CET Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 30975: BR222, E011/GC, WIM: Warning disappears before display is off
* Archive: DC MR 30972: BR222, E011/GC, WIM: Remove exception raising if HMI reports a canceled warning
* Archive: Revision 1.15 2012/12/20 18:49:13CET Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 30711: BR222 E011/GC, WIM: Wrong delay for synchronous acoustics - WDM 54612
* Archive: DC MR 30528: W222, E011/GC, WIM: complex display of warnung ConvertibleTop 0x200527 - ÄLP2745
* Archive: DC MR 30362: BR222 E011: Implementation of L2 delivery generic model part (SRSC_Style_Guide and XML files)
* Archive: Revision 1.14 2012/11/01 17:25:28CET Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 30267: BR222 E010, WIM: Acoustic problems found in customer pre tests of E7.6.pre30 frame - WDM56897
* Archive: DC MR 30242: E010: WIM, Correction of display state detection/ behaviour of wake-up warnings
* Archive: DC MR 26090: W222, E010/GC, WIM: Flashing dashes for warnings [WDM53127]
* Archive: Revision 1.13 2012/09/27 16:47:18CEST Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 27624 W222, E007/GC, WIM: Possible access violation in fault memory
* Archive: DC MR 29657 W222, E007/GC, WIM: Change attributes of warning 0x2004FE, 0x2004C0, 0x200002, 0x200003 - ÄLP 3088
* Archive: DC MR 29699 W222, E7.6/GC, WIM: Changes for SBW acoustic handling - ÄLP 3082 / missing HIL output for NCAP acoustics - WDM 47538
* Archive: Revision 1.12 2012/07/27 13:02:00CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 26921: W205 (copy W222) GC: Integration of SimEnv Simulation in MKS Script 4.0 environment
* 
*    Rev 1.18   Jul 25 2012 11:56:34   SCHL_Dirk.Gottwalles
* DC MR 27180: W222, E009/GC, WIM: Acoustic stop behavior - WDM43362, WDM43364
* DC MR 27539: BR222/E7.4/GC: WIM: Update HIL feedback for sound and soundrequests
* Archive: Revision 1.10 2012/07/10 08:53:51CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 26956: BR222/E7.4/GC: WIM: Update HIL feedback for sound and soundrequests
* Archive: Revision 1.9 2012/05/18 10:58:13CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: Member moved from WIM_Interface.c in project /id/dag_PF3/sw/pkg/wim/core/project.pj[dag_PF3.sw.pkg.wim_COMMON_IC222GC_VarP] to WIM_Interface.c in project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3/project.pj[dag_PF3.sw.pkg.wim_COMMON_genPF3_VarX].
* Archive: Revision 1.8 2012/04/19 14:42:41CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 25146: W222, E007/GC, WIM: Priorities for roll handling - WDM35385
* Archive: DC MR 25141: W222, E007/GC, WIM: SBW/WIM Acoustic corrections - WDM21151, WDM34246
* Archive: Revision 1.7 2012/04/04 15:31:24CEST 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: DC MR 24870: W222, E007/GC, WIM: Implement changes from Review ORM2907
* Archive: DC MR 25007: W222, E007/GC, WIM: Displacement of handling messages - WDM20280
* Archive: DC MR 25041: Do not specify message propagation in message description files
* Archive: DC MR 25095: W222, E007/GC, WIM: Improvement of Timer accuracy for display role - WDM 25704
* Archive: DC MR 25034: Reduction of lag times in case of vehicle locked
* Archive: DC MR 25393: W222, E007/GC, WIM: No cancel of interval acoustic - WDM31269, ÄLP2895
* Archive: Revision 1.6 2012/01/20 10:47:38CET 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: DC MR 24746: BR222 E7.1: Implementation of L3 MDB, WDB for E7.1
* Archive: DC MR 24995: IC222 GC: HMI Synchronization: Clock generation/Basic Mechanisms
* Archive: DC MR 24327: W222, E007/GC, WIM: Implement changes from Review ORM3245, ORM3314
* 
*    Rev 1.14   Jan 20 2012 14:19:54   SCHL_Dirk.Gottwalles
* DC MR 23690: E007/AC WIM reduce coreload
* DC MR 23692: W222, E007/AC: Warnung Parkbremse 0x2001A8 ÄLP2607
* DC MR 23765: W205, E007/AC, WIM: Patch for 0x2000BC and 0x2000C1 (Country coding), WDM23191
* DC MR 24330: W205, E007/GC, WIM: Takeover MR for 23683, 24093, 24088
* DC MR 24098: BR205: Implementation of L3 MDB, WDB for E007
* 
*    Rev 1.13   Jan 13 2012 16:18:56   SCHL_Dirk.Gottwalles
* DC MR 24093: W222, E007/GC, WIM: Acoustic warning does not block display - WDM20499
* DC MR 23683: W222, E007/GC, WIM: Sync acoustic is cancelled by async acoustic WDM21143
* DC MR 24088: W222, E007/GC, WIM: Warning blocks display WDM22837, WDM23219
* DC MR 24089: W222,E007,AC, WIM: New configuration values Chauffeur_Avl and ShiftStyle_Variant
* DC MR 24343: W222, E007/AC, WIM: Patch for 0x2000BC and 0x2000C1 (Country coding), WDM23191
* 
*    Rev 1.12   Dec 02 2011 14:50:04   SCHL_Dirk.Gottwalles
* DC MR 23223: W222, E007/AC: Warnung Parkbremse 0x2001A8 ÄLP2607
* DC MR 23256: W222GC:E006 new volume interface
* DC MR 23803: Applications should send global direct messages
* DC MR 22621: BR222/E007/GC: HIL: DisplayColor
* 
*    Rev 1.11   Nov 18 2011 15:58:44   SCHL_Dirk.Gottwalles
* DC MR 23225: W222, E007/GC, WIM: Auto repeat feature for fault memory WDM19781
* DC MR 22930: BR222, E007/AC, WMN: Implementation of changes for new WEM
* DC MR 23685: W222, E007/GC, WIM: Acoustic macros access array out of bounds
* DC MR 23617: E007/AC WIM remove pragma 'callmode far'
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
*    Rev 1.9   Mar 22 2011 16:07:24   SCHL_Dirk.Gottwalles
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
*    Rev 1.8   Dec 03 2010 15:57:14   SCHL_Lars.Gruenewald
* DC MR20903 BR222 WIM cancel dsp synch acustics at warning left the display
* DC MR21188 BR222: WIM Display lag time at multiple wakeupreq.
* DC MR21334 GC-E003: Update of PCMPL and changed Interface
* DC MR21353 HIL& WIM: Acoustics SetBeltWarningLevel2 und Level1, ContinuousWarning
* DC MR21151 HIL: wrong Accoustics Warning
* DC MR21384 BR222: two warnings for seatbeltwarning
* DC MR21318 E003: Startup MR for Traffic sign assistant (TSA)
* DC MR20897 WIM: Implementation of menu FaultMemory
* DC MR21257 Implementation of L3 WarnDB für E003
* 
*    Rev 1.7   Nov 19 2010 16:04:26   SCHL_Dirk.Gottwalles
* DC MR21122 BR222: WIM reaction at wakeupreq.
* DC MR21302 BR222/AC: Optimierung Aufruf Checkfunktion WIM
* DC MR20423 W222: WIM new acoustics requirements
* DC MR21177 Implementation of first WarnDB for E003
* DC MR21336 WIM: Using Enumeration Symbols for State/Widget Mapping
* 
*    Rev 1.6   Sep 17 2010 20:58:08   SCHL_Lars.Gruenewald
* DC MR21004 Startup MR for Module DOCG (Display Documentation Target Application)
* DC MR20908 E002/AC, Startup HIL
* 
*    Rev 1.5   Aug 27 2010 18:50:00   SCHL_Lars.Gruenewald
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
*    Rev 1.4   Jul 09 2010 18:01:50   SCHL_Lars.Gruenewald
* DC MR 20710 Vr222 WIM: Menue is in Display before warning
* DC MR 20545 WIM: Extension of HMI Interface for E001.2
* 
*    Rev 1.3   Jun 30 2010 14:36:40   SCHL_Lars.Gruenewald
* DC MR 20629 Configuration of Display Handler
* 
*    Rev 1.2   Jun 25 2010 12:22:12   SCHL_Lars.Grünewald
* DC MR 20566  WIM222: WIM Part2 for E001
* DC MR 20629 Configuration of Display Handler
* DC MR 20639 WIM: Adaption of HMI part for E001.1 
* DC MR 20620 Startup-MR for dynamical area manager (prio)
* DC MR 20661 Br222: WIM: ICOM Reinitialization
* DC MR 20662 Needed patches for WarnDB E001
* DC MR 20560 Implementation of first WarnDB for E001
* DC MR 20490 W222 E001: start up MR SFG
* 
*    Rev 1.1   Jun 11 2010 14:01:08   SCHL_Thomas.Godemann
* DC MR20480 AC, Startup MR for Modul WIM in E001
* DC MR20481 GC, Startup MR for Modul WIM in E001
* 
*    Rev 1.0   Jun 07 2010 13:20:42   SCHL_Thomas.Godemann
* Initial revision.
* 
* --------------------------------------------------------------------------
* Date      | Author | Reason     | Change
* --------------------------------------------------------------------------
* 10-06-03    LarGru   MR20480      Initial revision for W222
*                      MR20481      Initial revision for W222
*
*******************************************************************************/

/******************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*******************************************************************************/
/* System-headerfiles */
#include "cdef.h"

/* Foreign headerfiles */

/* Own headerfiles */
#include "WIM_c1.h"
#include "WIM_Interface.h"                      /* Interface          */

/******************************************************************************
* GLOBAL DEFINITIONS
*******************************************************************************/

/* N/A */

/******************************************************************************
* FILE LOCAL DEFINITIONS
*******************************************************************************/

/**
* Memory for partition valid state (SYSID)
*/
static bool WIM__boPartitionValid;

/******************************************************************************
* FILE LOCAL FUNCTION PROTOTYPES
*******************************************************************************/

/* N/A */

/******************************************************************************
* FUNCTION DEFINITIONS
*******************************************************************************/

/**************************
** System interfaces
***************************/


/**
* Initialisiation of package components on transition to system state Active
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM_vInitActive(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* partition valid? */ 
   WIM__boPartitionValid = True;

   #if (WIM__nEnableRTM_Cfg == WIM__nRtmInitActive)
   /* measure function run-time if enabled */
   WIM__mStartRtm();
   #endif

   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
      /* initialise components of ICOM*/
      WIM__vIComInit_AC();
      WIM__vIComInit_GC();
      
      /* initialise components of package */
      WIM__vStateHandlerInit_AC();
      WIM__vStateHandlerInit_GC();
      WIM__vTimerInit();

      WIM__vWakeIcStateInit();
      WIM__vReqCtrlInit();
      WIM__vCanInterfaceInit();

      /* send Init event to Check functions */
      WIM__vReqCtrlStart();

      /* initialise scheduler */
      WIM__vSchedulerInit();

      /* diagnostic mode is off */
      WIM__boDiagMode = False; 
      /* display is initially off */
      WIM__boDisplayState = Off;
      /* Init acoustics module */
      WIM__vInitAcoustic();

      /* allow scheduling now and initially trigger scheduler */
      WIM__vStartSchedule();
      WIM__vTriggerSchedule();
      WIM__vScheduleAcoustics();

      /* Register Events defined in ci.h */
      WIM__vEvhdRegisterEvents();
   }

   #if (WIM__nEnableRTM_Cfg == WIM__nRtmInitActive)
   /* measure function run-time if enabled */
   WIM__mStopRtm();
   #endif
}

/**
* Deinitialisiation of package components on leaving AC_Active system state
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM_vDeinitActive(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   
   #if (WIM__nEnableRTM_Cfg == WIM__nRtmDeinitActive)
   /* measure function run-time if enabled */
   WIM__mStartRtm();
   #endif

   /* Deregister ICOM communication Event. No more information on incomming Data */
   WIM__vEvhdDeregisterEvents();

   if (/* no activities and no access to generated WIM data if flash partition
        not valid! */
        WIM__boPartitionValid)
   {
      /* send DeInit event to Check functions */
      WIM__vReqCtrlStop();
      /* reinit CAN send signals */
      WIM__vCanInterfaceDeinit();
      WIM__vWakeIcStateDeInit();

      /* Init acoustics module */
      WIM__vDeinitAcoustic();

      /* end scheduler */
      WIM__vEndSchedule();

      /* Deinit all Timer objects */
      WIM__vTimerDeinit();
   }

   #if (WIM__nEnableRTM_Cfg == WIM__nRtmDeinitActive)
   /* measure function run-time if enabled */
   WIM__mStopRtm();
   #endif
}

/**
*   Cyclic function called from CAM250.
*   @return  void
*   @param   none
*   @author  Dirk Gottwalles, Schleissheimer GmbH 
*/
void WIM_v250Active(void)
{
   static bool bo500Ms = True;      /* Flag to create a 500ms cycle */

   if(bo500Ms)
   {
      
      /* Trigger cyclic report of messages to WMN */
      WIM__vCyclicWMNReport();


      /* Reset 500ms Flag to prevent running of 500ms code next time */
      bo500Ms = False;
   }
   else
   {
      /* Set Flag to run thru 500ms code next time */
      bo500Ms = True;
   }
}

/**
*   Cyclic function called from CAM10.
*   @return  void
*   @param   none
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
void WIM_v10Active(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
      /* timer main (counter) */
      WIM__vTimerMain();
      /* timer main (counter) */
      WIM__mGetTurnOnDelayFctPtr();
      /* CAN Rx/Tx control */
      WIM__vCanInterfaceMain();
      /* timer for counter display time */
      WIM__vVanTrackingStatusTime();
   }
}

/**
*   Cyclic function called from CAM20.
*   @return  void
*   @param   none
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
void WIM_v20Active(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
      /* Trigger real time message condition check */
      EVHD_vSendEvent(EV_WIM_nStartCheckFctCycle);
      
   }
}

/**
* Main function called from SFG pre-scheduling container
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM_vSfgPreSchedule(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
      #if (WIM__nEnableRTM_Cfg == WIM__nRtmSchedulePrio)
      /* measure function run-time if enabled */
      WIM__mStartRtm();
      #endif

      /* call scheduler priority check */
      WIM__vSchedulePrioCheck();
      WIM__vScheduleSlack();

      #if (WIM__nEnableRTM_Cfg == WIM__nRtmSchedulePrio)
      /* measure function run-time if enabled */
      WIM__mStopRtm();
      #endif
   }
}

/**
* Cyclic function called from SFG base tick container
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM_vSfgBaseTick(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
      /* call scheduler ressouce request */
      WIM__vScheduleRessourceReq();
      /* call scheduler ressouce request for slacks */
      WIM__vScheduleRessourceReqSlack();
      /* count synchronisation delay */
      WIM__vCountSyncDelay();
   }
}


/**
* Notification callback from CST KL15R On container
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM_vKl15ROn(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
      /* restore the state of manually confirmed messages warnings 
         reset canceled/deleted warnings */
      WIM__vRestoreWarnings();
   }
}

/**
* Kl15Off-edge handling: Call RequestDisplay state handler
* for handling the Display requests
*   @return  void
*   @param   none
*   @author  L. Gruenewald, Schleissheimer GmbH 
*/
void WIM_vKl15ROff (void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
         /*** trigger RequestDisplay state handler. */
         WIM__vRequestDisplayStateHdl(WIM__nKl15rOffEdge);
   }
}

/**
* Notification callback from CST KL15 Off container
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM_vKl15Off(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
      /* event KL15G_TO_KL15R occured, handle RETRIGGER_ON_EVENT */
      WIM__vReqCtrlRetriggerKL15Off();
   }
}

/**
* Notification callback from CST KL15 Off container
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH
*/
void WIM_vKl15On(void)
{
    /***************************************************************************
    * FUNCTION CODE
    ****************************************************************************/
    if (/* no activities and no access to generated WIM data if flash partition
        not valid! */
        WIM__boPartitionValid)
    {
        /* Start Suppress Timer for tracking warning */
       TIMER_vStart(TIMER_nWIM_TimerVanTrackingStatusSuppress, WIM_u16TimerDuration_SuppressVanTrackingStatus);
    }
}

/**
* Initialize CAN Tx data, called from CMON InitTxCanData container
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM_vInitTxCanData(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
      /* initialise HU mute/volume signals */
      WIM__vCanInterfaceInitTxCan();
   }
}

/**
* Called on new DPOOL data from ICom was received
*   @return  void
*   @param   EVHD_tenReceiveEvent enEvent
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
void WIM_vDoDpoolEvents(EVHD_tenReceiveEvent enEvent)
{   
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
      switch(enEvent)
      {
         case EV_DPOOL_Always_WIM_u32IcomDataGc_QueueGC_to_AC_WIM_vDoDpoolEvents:
            /* Process ICOM DPOOL Queue until it is empty */
            WIM__vDoDpoolEventsByICom_AC(enEvent);
            break;
         case EV_DPOOL_OnChange_ICBWMDL_u32DynAreaHilId_WIM_vDoDpoolEvents:
            WIM__vCheckDPOOLWimHilId();
            break;
         case EV_DPOOL_OnChange_WIMMDL_u32SlackHilId_WIM_vDoDpoolEvents:
            WIM__vCheckDPOOLSlackHilId();
            break;
         case EV_DPOOL_Always_WIM_u32IcomDataAc_QueueAC_to_GC_WIM_vDoDpoolEvents:
            /* Process ICOM DPOOL Queue until it is empty */
            WIM__vDoDpoolEventsByICom_GC(enEvent);
            break;
         case EV_DPOOL_OnChange_CSP_u8StateConvertibleTop_WIM_vDoDpoolEvents:            
            break;
         case EV_DPOOL_OnChange_HYHLPOW_stModelDataAC_WIM_vDoDpoolEvents:            
            break;
         default:
            /* Fct call by unhandled Event */
            WIM__vRaiseException(WIM_nErrConfig);
            break;
      }
   }
}

/**
* Called when new EVHD events are received
*   @return  void
*   @param   EVHD_tenReceiveEvent enEvent
*   @author  D. Gottwalles, Schleissheimer GmbH 
*/
void WIM_vDoGeneralEvents(EVHD_tenReceiveEvent enEvent)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
    uint16 u16SoundOutput = (uint16)WIM_nenNoAcoustic;    /* init Information for HIL-ID */
    uint8 u8VolumeHIL = 0;                                /* init Information for HIL-ID */
    uint8 u8Loudness = WIM_nenVolumeNoSound;              /* init Information for HIL-ID */
    static uint16 u16Counter = 0;
   switch(enEvent)
   {
   case EV_WIM_nStartCheckFctCycle_WIM_vDoGeneralEvents:
      {
         /* Event for processing the real time checks has been received */

         /* execute real time check functions */
         /* filter every second call */
          if ((u16Counter % 2 ) == 0)
          {
               WIM__vReqCtrl25ms();
          }
          u16Counter++;

      }break;
   default:
      {
         /* do nothing */
      } break;
   }
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
      switch(enEvent)
      {
      case EV_ChangeNotificSMSRES_Sound_WIM_vDoGeneralEvents:
      {
         if (CRHDL_enStateHdlGetState(CRHDL_nSMSRES_Sound) == CRHDL_nStateOn)
         {
            /* sound interface ready, trigger scheduler (MR33925) */
            WIM__vTriggerSchedule();
            WIM__vScheduleAcoustics();
         }
      } break;
      // AlTo: Fix for Acoustic Playback when returning from Powerfail
      case EV_ChangeNotificSMSRES_Audio_HW_WIM_vDoGeneralEvents:
          if (CRHDL_enStateHdlGetState(CRHDL_nSMSRES_Audio_HW) == CRHDL_nStateOn)
          {
              /* sound interface ready, trigger scheduler (MR33925) */
              WIM__boSoundPowerFail = False;
              WIM__vScheduleAcoustics();
          }
          else if (CRHDL_enStateHdlGetState(CRHDL_nSMSRES_Audio_HW) == CRHDL_nStateOff)
          {
              /* Send WIM__u16SoundOutput with init value (WIM_nenNoAcoustic). */
              DPOOL_enSetPoolData(DPOOL_nDataWIM_u16SoundOutput, &u16SoundOutput);
              DPOOL_enSetPoolData(DPOOL_nDataWIM_u8SoundVolume, &u8VolumeHIL);
              DPOOL_enSetPoolData(DPOOL_nDataWIM_u8SoundLoudness, &u8Loudness);
              WIM__vSoundOutputReqHIL(WIM_nenNoAcoustic);
              /* Set state of power fail indicator */
              WIM__boSoundPowerFail = True;
              WIM__vScheduleAcoustics();
          }
      break;
      // AlTo: End
      default:
         /* nothing to do */
         break;
      }
   }
}

/**
* Called when new EVHD timer events are received
*   @return  void
*   @param   EVHD_tenReceiveEvent enEvent
*   @author  Martin Wenske, Schleissheimer GmbH 
*/
void WIM_vDoGeneralTimerEvents(EVHD_tenReceiveEvent enEvent)
{
   switch(enEvent)
   {
      case EV_TIM_WIM_HilBreakTimer_WIM_vDoGeneralTimerEvents:
         {
            TIMER_vClear(TIMER_nWIM_HilBreakTimer);
            WIM__vHilBreakTimerElapsed();
         } break;
      case EV_TIM_WIM_TimerAcuTDElapsed_WIM_vDoGeneralTimerEvents:
         {
            TIMER_vClear(TIMER_nWIM_TimerAcuTDElapsed);
            WIM__vToneDelayTimerElapsed();
         } break;
      case EV_TIM_WIM_TimerVanTrackingStatusSuppress_WIM_vDoGeneralTimerEvents:
         {
            TIMER_vClear(TIMER_nWIM_TimerVanTrackingStatusSuppress);
         } break;
      case EV_TIM_WIM_TimerFreqCollWarn_WIM_vDoGeneralTimerEvents:
         {
            TIMER_vClear(TIMER_nWIM_TimerFreqCollWarn);
            WIM__vIntervalTimerElapsedCallback(WIM__enFrontLatCollWarnPlaying);
         } break;
      case EV_TIM_WIM_TimerFreqContWarn_WIM_vDoGeneralTimerEvents:
         {
            TIMER_vClear(TIMER_nWIM_TimerFreqContWarn);
            WIM__vIntervalTimerElapsedCallback(WIM__enContPlayingSound);
         } break;
      default:
      /* nothing to do */
      break;
   }
}

/**
* Called on new DPOOL data from HMI was received
*   @return  void
*   @param   EVHD_tenReceiveEvent enEvent
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
void WIM_vDoHmiEvents(EVHD_tenReceiveEvent enEvent)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boDisplayOn;
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
      switch(enEvent)
      {
         case EV_DPOOL_Always_WIM_u16CanceledWarning_WIM_vDoHmiEvents:
         case EV_DPOOL_Always_WIM_stHmiFeedback_WIM_vDoHmiEvents:
         case EV_DPOOL_Always_WIM_u16SuppressedWarning_WIM_vDoHmiEvents:
         case EV_DPOOL_Always_WIM_u16CanceledSlack_WIM_vDoHmiEvents:
         case EV_DPOOL_Always_WIM_stHmiFeedbackSlack_WIM_vDoHmiEvents:
            /* Forward into StateHandler */
            WIM__vDoHmiFeedback(enEvent);
            break;
         case EV_DPOOL_Always_WIM_stKeyEvent_WIM_vDoHmiEvents:
            /* Forward into KeyControl */
            WIM__vDoKeyEvent(enEvent);
            break;
         case EV_DPOOL_Always_WIM_u8FaultMemEvReset_WIM_vDoHmiEvents:
            /* Forward into MenuFaultMemory */
            WIM__vMenuFaultMemResetCallback(enEvent);
            break;
         case EV_DPOOL_Always_WIM_u8FaultMemEvPrevNext_WIM_vDoHmiEvents:
            /* Forward into MenuFaultMemory */
            WIM__vMenuFaultMemKeyCallback(enEvent);
            break;
         case EV_DPOOL_OnChange_WIM_boDisplayOn_WIM_vDoHmiEvents:
            if(DPOOL_enGetPoolData(DPOOL_nDataWIM_boDisplayOn, &boDisplayOn) != E_DATA_OK)
               WIM__vRaiseException(WIM_nErrIcom);
            if (boDisplayOn)
            {
               if (WIM__boDisplayState != On)
               {
                  WIM__boDisplayState = On;
                  WIM__vTriggerSchedule();
                  WIM__vScheduleAcoustics();
               }
            }
            else
               if (WIM__boDisplayState != Off)
                  {
                     /* set state in Request */
                     WIM__boDisplayState = Off;
                     /* If the display is switched off the we do not want to display a warning anymore.
                      * Send this info to the WIM widget.
                      */
                     WIM__vDspWarningRelease();
                     WIM__vDspSlackRelease();
                     /* reset state of all warnings - MR31152 */
                     WIM__vResetAllWarnings();
                  }

            break;
         case EV_DPOOL_Always_WIM_stPhoneCallKey_WIM_vDoHmiEvents:
            WIM__vProcessMBCallPrivacyPopup(enEvent);
            break;
         default:
            /* Fct call with unhandled Event */
            break;
      }
   }
}

/**************************
** Services
***************************/
   
/**
* WIM interface for IC external events evaluated in check-functions
* Triggers a call of the check-function and sets a flag storing the state
* of the event. This functions sets the event flag
*   @return  void
*   @param   u8Function: code of the function triggering the event
*   @param   u8Index: index of the event
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM_vSetExtEvent(WIM_tenExtEvtFunction enFunction, uint8 u8Index)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
      WIM__mGetExtConditionFctPtr(enFunction, u8Index, WIM__nRegister);
   }
}

/**
* WIM interface for IC external events evaluated in check-functions
* Triggers a call of the check-function and sets a flag storing the state
* of the event. This functions sets the event flag and the Retrigger Flag.
* The message is retriggered.
*   @return  void
*   @param   u8Function: code of the function triggering the event
*   @param   u8Index: index of the event
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM_vRetriggerExtEvent(WIM_tenExtEvtFunction enFunction, uint8 u8Index)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
      WIM__mGetExtConditionFctPtr(enFunction, u8Index, WIM__nRetrigger);
   }
}

/**
* WIM interface for IC external events evaluated in check-functions
* Triggers a call of the check-function and sets a flag storing the state
* of the event. This functions clears the event flag
*   @return  void
*   @param   u8Function: code of the function triggering the event
*   @param   u8Index: index of the event
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM_vRelExtEvent(WIM_tenExtEvtFunction enFunction, uint8 u8Index)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
      WIM__mGetExtConditionFctPtr(enFunction, u8Index, WIM__nDelete);
   }
}

/**
* WIM interface for IC internal events evaluated in check-functions
* Triggers a call of the check-function and sets a flag storing the state
* of the event. This functions sets the event flag
* The message is activated with "Register"
*   @return  void
*   @param   u32HilId: HIL ID of the related message
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM_vSetIntEvent(uint32 u32HilId)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
       WIM__vHandleIntCondition_AC(u32HilId, WIM__nRegister);
   }
}

/**
* WIM interface for IC internal events evaluated in check-functions
* Triggers a call of the check-function and sets a flag storing the state
* of the event. This functions sets the event flag.
* The message is activated with "Retrigger" (reactivation)
*   @return  void
*   @param   u32HilId: HIL ID of the related message
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM_vRetriggerIntEvent(uint32 u32HilId)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
       WIM__vHandleIntCondition_AC(u32HilId, WIM__nRetrigger);
   }
}

/**
* WIM interface for IC internal  events evaluated in check-functions
* Triggers a call of the check-function and sets a flag storing the state
* of the event. This functions clears the event flag
*   @return  void
*   @param   u32HilId: HIL ID of the related message
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM_vRelIntEvent(uint32 u32HilId)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
       WIM__vHandleIntCondition_AC(u32HilId, WIM__nDelete);
   }
}

void WIM_vManualConfirmEvent(uint32 u32HilId)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* no activities and no access to generated WIM data if flash partition
      not valid! */
   if(WIM__boPartitionValid)
   {
      WIM__vOnEvent_AC(WIM__enHilId2Enum(u32HilId), WIM__nConfirmation);
   }
}

/**
* The function returns the current WIM message displayed if any (HIL ID)
*   @return  u32HilId: message HIL-ID, WIM__nInvalidHilId if no msg displayed
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
uint32 WIM_u32GetCurrentDisplayMsg(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint32 u32HilId = WIM__nInvalidHilId;               /* return value     */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* no activities and no access to generated WIM data if flash partition
      not valid! */
   if (True == WIM__boPartitionValid)
   {
      if(!WIM__boGetDisplayMaster(&u32HilId))
      {
         u32HilId = WIM__nInvalidHilId;
      }
   }

   return u32HilId;
}


/**
* The function returns the "Registered" state of the message
*   @return  True = registered, False = not registered
*   @param   uint32 u32HilId: HIL ID of message to evaluate                       
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM_boIsRegistered(uint32 u32HilId)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boReturn = False;                /* return value                      */
   WIM_tenMsg enMsg;                    /* ID of message                     */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       True == WIM__boPartitionValid)
   {
      enMsg = WIM__enHilId2Enum(u32HilId);
      boReturn = ( (enMsg < WIM__mGetNoOfMessages) ? 
                   (WIM__mboGetRegFlag(enMsg)    ) : 
                    False );
   }
   return boReturn;
}

/**
 * @brief Disable SLAck's
 */
void WIM_vDisableSlacks(void)
{
   /* mark SLAck's as blocked */
   WIM__u8SlackDisplayBlocked++;

   /* if there is currently displayed SLAck which is set as a master - release it */
   if (WIM__enDspSlackMaster != WIM_nenInvalidMsg)
   {
      /* mark waiting SLAck as invalid */
      WIM__enDspSlackMasterWaiting = WIM_nenInvalidMsg;

      /* release SLAck from the display via sending wrapped HMI-message */
      WIM__vDspSlackRelease();
   }
}

/**
 * @brief Enable SLAck's by decreasing WIM__u8SlackDisplayBlocked
 */
void WIM_vEnableSlacks(void)
{
   /* if SLAck's are blocked - release them to be displayed again */
   if (WIM__u8SlackDisplayBlocked > 0)
   {
      WIM__u8SlackDisplayBlocked--;
   }   
}


/**************************
** Diag interface
***************************/

/**
* DLIB interface function.
* End diagnostic mode. Reset (modified) state of messagess
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM_vEndDiagnosticSession(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
      WIM__vEndDiagMode(); /* stop diagnostic mode */
   }
}

/**
* DLIB interface function.
* Allows to switch on diagnostic mode and to activate or deactivate a message 
* identified by HIL-Id. 
*   @return  DLIB_tenReturn
*   @param   boActivate: True > Register, False > Delete message 
*   @author  T.Godemann, Schleissheimer GmbH 
*/
DLIB_tenReturn WIM_enDiagSetWarning(bool boActivate, uint32 u32HilId)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   DLIB_tenReturn enRet= DLIB_nReturnCodeRefuse;        /* return value       */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
      /* convert HIL to WIM enum and call enum based function */
      enRet = WIM__enDiagWarnRequest(boActivate, WIM__enHilId2Enum(u32HilId));
   }
   else
   {  
      enRet = DLIB_nReturnCodeRefuse;
   }
   return enRet;
}

/**
* DLIB interface function, for DocGen.
* Allows to switch on diagnostic mode and to activate a message 
* identified by HIL-Id. 
*   @return  bool: true when requested Warning exists, false if not.
*   @param   u32HilId: Hil-Id which should be displayed. 
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
bool WIM_boRemoteControlSetWarning(uint32 u32HilId)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boRetValue = False;
   WIM_tenMsg enMsgRequested = WIM_nenInvalidMsg;


   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
       not valid! */
       WIM__boPartitionValid)
   {
      /* Get the enum value for requested Hil-ID if Hil-ID exists */
      enMsgRequested = WIM__enHilId2Enum(u32HilId);
      if (enMsgRequested != WIM_nenInvalidMsg)
      {
         /* valid Hil-ID was requested by DocGen */
         boRetValue = True;

         /* convert HIL to WIM enum and call enum based function */
         WIM__vDiagRemoteCtrlSetWarning(enMsgRequested);
      }
   }

   return boRetValue;
}

/**
* DLIB interface function, for DocGen.
* Allows to switch on diagnostic mode and to release warnings screen.  
*   @return  void
*   @param   void 
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
void WIM_vRemoteControlReleaseScreen(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
       not valid! */
       WIM__boPartitionValid)
   {

      /* Switch into, or hold Diag Mode and clear warning states and display */
      WIM__vDiagRemoteCtrlSetWarning(WIM_nenInvalidMsg);
   }

}
 
/**
* DLIB interface function, for DocGen.
* End diagnostic mode. Reset (modified) state of messages
*   @return  void
*   @param   void
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
void WIM_vRemoteControlLeaveMode(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* no activities and no access to generated WIM data if flash partition
          not valid! */
       WIM__boPartitionValid)
   {
     WIM__vEndDiagMode(); /* stop diagnostic mode */
   }
}
 
/**
* Interface function to query the display color of a warning.
*   @return  WIM_tenDisplColor of the specified HIL-ID
*   @param   u32HilId: 32Bit HIL-ID of the warning (e.g. 0x20048500)
*   @author  D. Gottwalles, Schleissheimer GmbH 
*/
WIM_tenDisplColor WIM_enGetdisplayColor(uint32 u32HilId)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   WIM_tenDisplColor enWarnColor=WIM_enInvalidColor;
   WIM_tenMsg        enMsgId;

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* Get Warn message id using the Hild-ID */
   enMsgId = WIM__enHilId2Enum(u32HilId);

   if(enMsgId != WIM_nenInvalidMsg &&
      enMsgId < WIM_nenNoOfMessages)
   {
      /* Get color from message structure */
      enWarnColor = WIM__astDisplayConfiguration[enMsgId].enColor;
   }

   return enWarnColor;
}


/**
* Sonud interface function.
* The function will retrigger the sound of the specified warning.
* Only in case that the warning is active and the sound channel is 
* not blocked by another warning. If the sound if the specified 
* warning is already playing, the sound is stopped and then started
* again.
*   @return  void
*   @param   u32HilID: Hil-ID of the warning in 24Bit format (e.g. 0x20012300)
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
void WIM_vRetriggerSound(uint32 u32HilID)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   WIM_tenMsg enMsg;

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   enMsg = WIM__enHilId2Enum(u32HilID);
   if(enMsg != WIM_nenInvalidMsg)
   {
      WIM__vOnEvent_AC(enMsg, WIM__nAcuRetrigger);
   }
   else
   {
      /* HIL-ID is unknown */
      WIM__vRaiseException(WIM_nWrongParameter);
   }
}

/**
* Sonud interface function.
* The function will stop the sound of the specified warning immeadiatly.
* The function will act only in case that the sound of the specified 
* warning is currently playing.
*   @return  void
*   @param   u32HilID: Hil-ID of the warning in 24Bit format (e.g. 0x20012300)
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
void WIM_vStopSound(uint32 u32HilID)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   WIM_tenMsg enMsg;

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   enMsg = WIM__enHilId2Enum(u32HilID);
   if(enMsg != WIM_nenInvalidMsg)
   {
      WIM__vOnEvent_AC(enMsg, WIM__nAcuStop);
   }
   else
   {
      /* HIL-ID is unknown */
      WIM__vRaiseException(WIM_nWrongParameter);
   }
}

/**
* Display interface function.
* The function will retrigger the Display without retriggering the sound, if
* the warning is still in display. Only in case that the warning
* is not in the display any longer, a sound output will be requested.
*   @return  void
*   @param   u32HilID: Hil-ID of the warning in 24Bit format (e.g. 0x20012300)
*   @author  A.Wagner, Schleissheimer GmbH 
*/
void WIM_vRetriggerDisplay(uint32 u32HilID)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   WIM_tenMsg enMsg;

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   enMsg = WIM__enHilId2Enum(u32HilID);
   if(enMsg != WIM_nenInvalidMsg)
   {
      WIM__vOnEvent_AC(enMsg, WIM__nDspRetrigger);
   }
   else
   {
      /* HIL-ID is unknown */
      WIM__vRaiseException(WIM_nWrongParameter);
   }
}
