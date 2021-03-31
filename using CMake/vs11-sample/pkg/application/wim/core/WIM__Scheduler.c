/******************************************************************************
*=====================      Copyright by Continental AG      ==================
*******************************************************************************
* Titel        : WIM__Scheduler.c
*
* Description  : Ressource scheduler, checks messages for their requests to be
*                outputed on display and/or acoustic channel. It also controls
*                synchronisation and requests the output channels
*
* Environment  : OSEK, JCP (NEC V850)
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
* Archive: $Log: WIM__Scheduler.c  $
* Archive: Revision 1.1.2.17 2014/08/23 16:19:19CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 42288 : WIM: Correct customer findings regarding non-urgent handling message and acoustic cancel - WDMs 341, 417
* Archive: Revision 1.1.2.16 2014/08/16 14:18:13CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 41960 : System Test Findings #11393 DSM Evaluating Display state as On while RampDown
* Archive: Revision 1.1.2.15 2014/08/13 17:16:52CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 42077: WIM: SLACK is displayed with noise
* Archive: DC MR 41987: WIM: Break of 100ms is seen in case of acoustic replacement async to async - #10894
* Archive: DC MR 41983: WIM: Start of "BSM Warnton" output is delayed >300ms - WDM 337
* Archive: DC MR 41981: BR213-EL/E008, WIM: Minimum display time are extended after retriggering - WDM 348
* Archive: DC MR 41975: WIM: Change HIL timing for single line acknowledgements according to customer - WDM257
* Archive: Revision 1.1.2.14 2014/08/08 17:31:03CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 41812 : WIM: Non-urgent handling messages are able to replace a warning after 500ms - WDM312
* Archive: Revision 1.1.2.13 2014/07/18 16:08:42CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 41427 : WIM: Corrections of acoustic issues found in customer tests
* Archive:  DC MR 41425 : WIM: Corrections of acoustic issues found in system test
* Archive: Revision 1.1.2.12 2014/06/06 18:57:43CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 40088 : WIM: Extend implementation for break in acoustic HIL signal - WDM 203
* Archive: DC MR 40569 : WIM: Deactivation time of FCW/LCW acoustics takes too long - WDMs 99460, 99457
* Archive: DC MR 40609 : WIM: Correct handling for "kurzzeitige Ruhe" (short rest) - WDMs 99458, 99481, 99485
* Archive: Revision 1.1.2.11 2014/06/06 17:05:00CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 38112 : WIM: Introduction of "Singleline Acknowledgements" - MR47
* Archive: DC MR 40764 : WIM: Changes after code review for single line acknowledgements -  ORM 7144
* Archive: DC MR 40531 : Single line acknowledgement should cancel a running startup animation
* Archive: Revision 1.1.2.10 2014/03/21 13:02:47CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 39524 : WIM: Correct interval acoustic handling and HIL feedback
* Archive: DC MR 39163 : WIM: Overcome illegal memory access and correction of HMI acoustics notification
* Archive: DC MR 40021 : WIM: Sound of FCW warning is not retriggered after reset
* Archive: Revision 1.1.2.9 2013/12/06 17:54:29CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 37353 : WIM: Implement changes on door warning acoustics after clarification with customer - OPL 2064
* Archive: Revision 1.1.2.8 2013/11/22 16:56:29CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 36779 : BR213EL, E006, Implementation of new WarnDB
* Archive: DC MR 36462 : WIM: Implement new scheduling and state handling for acoustic part
* Archive: Revision 1.1.2.7 2013/09/27 15:25:53CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 36116: DSM Remove Level 6 QAC warning in the KBD, WIM and AAD
* Archive: Revision 1.1.2.6 2013/08/16 13:32:37CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 33822 : IC213EL-GC WIM: display synchroneous periodic tone not stopped with display off: WDM62157
* Archive: DC MR 33932 : IC213EL GC WIM: Initial sound requests for warnings does not work if sound system is not ready
* Archive: DC MR 33999 : BR213GC-EL, E005, WIM, CWMDL: API split - ORM5621
* Archive: DC MR 34028 : BR213EL, E005, StyleGuide Validation and implementation
* Archive: DC MR 34202 : BR213IC-GC-EL, WIM: Missing HIL output for seat belt warning acoustics - Folow-Up 33655
* Archive: DC MR 34326 : BR213-GC-EL/E005.1, WIM: Display is on for 2 minutes even when warning has disappeared
* Archive: DC MR 34547 : BR213-EL, E005.1/GC,WIM: Removal of QAC warning
* Archive: DC MR 34706 : BR213-GC-EL, E005.1: Chance DOCG implementation in WIM and TPOL
* Archive: DC MR 34781 : BR213-GC-EL, E005.1, WIM: Inconsistent display output in Fault Memory
* Archive: Revision 1.1.2.5 2013/06/06 15:09:57CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: Removal of QA C and QA C++ Analysis BR222 E011pre51- Findings
* Archive: Revision 1.1.2.4 2013/06/04 15:47:49CEST Harms-EXT, Daniel (uidw1026) 
* Archive: DC MR 33454: IC213EL: Flickering effect when activating distronic warning (SV_13_3062)
* Archive: Revision 1.1.2.3 2013/05/17 16:09:14CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 33413: BR213EL/GC, E004, WIM: Takeover of the latest changes from BR205
* Archive: Revision 1.1.2.2 2013/01/21 12:12:32CET Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
* Archive: Revision 1.17 2013/01/21 12:12:32CET Immel-EXT, Marc (uid37561) 
* Archive: DC MR 30335: BR205/E011/GC: DIM: Update SwillLvl turn-on condition (Exlude Warning without wake-reason)
* Archive: DC MR 31127: Change allocator of CIA memory pool from flexible to static
* Archive: DC MR 31152: BR205, E011/GC, WIM: Waking up the display is not possible if another wake IC warning is active
* Archive: DC MR 31154: BR205 E011/GC, WIM: Wrong transition in case of display cancel event
* Archive: Revision 1.16 2012/12/20 18:56:51CET Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 30711: BR222 E011/GC, WIM: Wrong delay for synchronous acoustics - WDM 54612
* Archive: DC MR 30528: W222, E011/GC, WIM: complex display of warnung ConvertibleTop 0x200527 - ÄLP2745
* Archive: DC MR 30362: BR222 E011: Implementation of L2 delivery generic model part (SRSC_Style_Guide and XML files)
* Archive: Revision 1.15 2012/11/15 18:41:33CET Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 30458: BR222 E010/GC, WIM: Error in display roll behaviour of warnings
* Archive: DC MR 30398: W222 E010/GC, WIM: First sound of SBW NCAP phase 4 is not played, Follow-up
* Archive: Revision 1.14 2012/11/01 17:24:47CET Immel Marc (uid37561) (uid37561)
* Archive: DC MR 30267: BR222 E010, WIM: Acoustic problems found in customer pre tests of E7.6.pre30 frame - WDM56897
* Archive: DC MR 30242: E010: WIM, Correction of display state detection/ behaviour of wake-up warnings
* Archive: DC MR 26090: W222, E010/GC, WIM: Flashing dashes for warnings [WDM53127]
* Archive: Revision 1.13 2012/10/18 16:57:33CEST Immel Marc (uid37561) (uid37561)
* Archive: DC MR 27470: W222, E010/GC, WIM: Active sound shall play to the end when display goes off - ÄLP2896
* Archive: DC MR 29924: E010: WIM acoustic problems: corrections for WDM53980, 53982 and 53999
* Archive: DC MR 29926: W222GC: WDM47699 WIM do not differs between Frontal and Lateral Collision warning sound
* Archive: DC MR 29928: W222, E010/GC, WIM: Sync acoustic is delayed too long
* Archive: DC MR 29866: BR222, E010/GC, WIM: Redesign of fault memory entry management
* Archive: DC MR 30023: W222IC-GC, E010: When displaying the oil switch warning the GC makes a reset
* Archive: Revision 1.12 2012/10/02 12:21:51CEST Immel Marc (uid37561) (uid37561)
* Archive: DC MR 27252 BR222 MY - Use Global Storage for HMI internal variables
* Archive: DC MR 29677 W222, E010/GC, WIM: Possible access violation in fault memory
* Archive: DC MR 29701 W222, E010/GC, WIM: Changes for SBW acoustic handling - ÄLP 3082 / missing HIL output for NCAP acoustics - WDM 47538
* Archive: Revision 1.11 2012/09/07 17:04:00CEST Immel Marc (uid37561) (uid37561)
* Archive: DC MR 27740: W205, E010/GC, WIM: Adaptions for ARTEMMIS 3.4
* Archive: DC MR 28962: W205, E010/GC, WIM: Remove QAC errors
* Archive: DC MR 28968: W205, E010/GC, WIM: Cancel of intervall acoustic for sync acoustic - WDM47461
* Archive: DC MR 27756: BR205 E010: Implement L2 delivery into the software frame (SRSC_Styleguide and XML files)
* Archive: Revision 1.10 2012/07/12 10:42:42CEST Gottwalles Dirk (uid37556) (uid37556)
* Archive: DC MR 27180: W222, E009/GC, WIM: Acoustic stop behavior - WDM43362, WDM43364
* Archive: DC MR 27539: BR222/E7.4/GC: WIM: Update HIL feedback for sound and soundrequests
* Archive: Revision 1.9.1.3 2012/07/12 10:42:42CEST Gottwalles Dirk (uid37556) (uid37556)
* Archive: DC MR 27179: W222, E007/GC, WIM: Acoustic stop behavior - WDM43362, WDM43364
* Archive: DC MR 26956: BR222/E7.4/GC: WIM: Update HIL feedback for sound and soundrequests
* Archive: Revision 1.9 2012/05/18 10:42:43CEST Gottwalles Dirk (uid37556) (uid37556)
* Archive: Member moved from WIM__Scheduler.c in project /id/dag_PF3/sw/pkg/wim/core/project.pj[dag_PF3.sw.pkg.wim_COMMON_IC222GC_VarP] to WIM__Scheduler.c in project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj[dag_PF3.sw.pkg.wim_COMMON_GenPF3GC_VarX].
* Archive: Revision 1.8 2012/05/10 17:21:01CEST Gottwalles Dirk (uid37556) (uid37556)
* Archive: DC MR 25842: BR222/E7.2/GC: WIM: HIL Fix Loudness Feedback (WDM31515)
* Archive: DC MR 25916: W222, E007/GC, WIM: Changes on display-block by sound only warning - WDM35459
* Archive: DC MR 25913: W222, E007/AC, HIL: Mapping of WIM sound types
* Archive: DC MR 25704: W222, E007/GC, WIM: Fix for corrupted sound - WDM35438
* Archive: Revision 1.7 2012/05/04 09:19:33CEST 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556)
* Archive: DC MR 25131: W222, E007/GC, WIM: Implementation of exceptions
* Archive: DC MR 25823: BR222 E7.2: Implementation of L3 delivery (XML-Files)
* Archive: DC MR 21251: W222, E007/GC, WIM: ComplexFunction of Warning 0x2001A6 Kurvenlicht
* Archive: DC MR 25710: W222, E007/GC, WIM: Inactive handling messages show up after 600ms - WDM35020
* Archive: DC MR 25126: W222, E007/GC, WIM: Behaviour of sync acoustics - WDM35391, 35418, 35392, 35389, 35396, 35421
* Archive: Revision 1.5 2012/04/04 13:46:19CEST 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556)
* Archive: DC MR 24870: W222, E007/GC, WIM: Implement changes from Review ORM2907
* Archive: DC MR 25007: W222, E007/GC, WIM: Displacement of handling messages - WDM20280
* Archive: DC MR 25041: Do not specify message propagation in message description files
* Archive: DC MR 25095: W222, E007/GC, WIM: Improvement of Timer accuracy for display role - WDM 25704
* Archive: DC MR 25034: Reduction of lag times in case of vehicle locked
* Archive: DC MR 25393: W222, E007/GC, WIM: No cancel of interval acoustic - WDM31269, ÄLP2895
*
*    Rev 1.19   Mar 29 2012 16:03:12   SCHL_Dirk.Gottwalles
* DC MR 25158: Reduction of lag times in case of vehicle locked
*
*    Rev 1.18   Feb 22 2012 17:54:34   SCHL_Dirk.Gottwalles
* DC MR 24332: W222, E007/GC, WIM: Warnings can not be acknowledged with Nview active
* DC MR 24324: W222, E007/AC, WIM: Remove unused code parts from secondary mute request
* DC MR 24333: W222, E007/GC, WIM: HIL output for requested sound not working
* DC MR 24043: Move tube request from WIM to WarningStandard.xml
* DC MR 23682: W222, E007/GC, WIM: Acousic only messsage does not block display WDM21148
* DC MR 24086: W222, E007/GC, WIM: Short rest after warning display is not always 5 seconds
* Archive: Revision 1.3 2012/01/13 11:39:30CET 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556)
*    Rev 1.17   Feb 20 2012 09:22:26   SCHL_Dirk.Gottwalles
* DC MR 24337: W205, E007/GC, WIM: Short rest after warning display is not always 5 seconds
*
*    Rev 1.16   Jan 20 2012 14:19:52   SCHL_Dirk.Gottwalles
* DC MR 23690: E007/AC WIM reduce coreload
* DC MR 23692: W222, E007/AC: Warnung Parkbremse 0x2001A8 ÄLP2607
* DC MR 23765: W205, E007/AC, WIM: Patch for 0x2000BC and 0x2000C1 (Country coding), WDM23191
* DC MR 24330: W205, E007/GC, WIM: Takeover MR for 23683, 24093, 24088
* DC MR 24098: BR205: Implementation of L3 MDB, WDB for E007
*
*    Rev 1.15   Jan 13 2012 16:18:54   SCHL_Dirk.Gottwalles
* Archive: DC MR 24093: W222, E007/GC, WIM: Acoustic warning does not block display - WDM20499
* Archive: DC MR 23683: W222, E007/GC, WIM: Sync acoustic is cancelled by async acoustic WDM21143
* Archive: DC MR 24088: W222, E007/GC, WIM: Warning blocks display WDM22837, WDM23219
* DC MR 24089: W222,E007,AC, WIM: New configuration values Chauffeur_Avl and ShiftStyle_Variant
* DC MR 24343: W222, E007/AC, WIM: Patch for 0x2000BC and 0x2000C1 (Country coding), WDM23191
*
*    Rev 1.14   Nov 07 2011 08:11:16   SCHL_Dirk.Gottwalles
* DC MR 23228: W222, E007/GC, WIM: Urgent handling message is not treated urgent
* DC MR 23226: W222, E007/GC, WIM: Change from async acoustic to sync acoustic WDM20336
* DC MR 23230: W222, E007/GC, WIM: Async acoustic blocks urgent display message WDM20376
* DC MR 22977: Integration of ARTEMMIS 3.2.1
*
*    Rev 1.13   Oct 21 2011 09:54:24   SCHL_Dirk.Gottwalles
* DC MR 23074: BR222: Implementation of E007 pre10 XML-Files and StyleGuide
* DC MR 22734: W222, E006/AC, WIM: Timeout function shall not use first value, WDM1378
* DC MR 23190: Use visibility change detection mechanism
* DC MR 23333: BR222/E007/GC: HIL: Acoustics WIM-REQ (WDM#19107)
* DC MR 22968: W222, E007/GC, WIM: Prio1 mute and partial lowering output WDM20219
*
*    Rev 1.12   Sep 09 2011 13:52:12   SCHL_Dirk.Gottwalles
* DC MR 22733: W222, E006/GC, WIM: Implementation of complex key handling for warnings
*
*    Rev 1.11   Aug 12 2011 16:39:36   SCHL_Dirk.Gottwalles
* DC MR 22652: W222, E006/AC, SCS: Remove warning management
* DC MR 22655: W222, E006/AC, WIM: Implmentation of complex key handling for warnings
* DC MR 22263: W222, E006/GC, WIM: Remove of unused sound Ids
* DC MR 22549: E006/GC: HIL: Get acoustics status indication for warnings
* DC MR 22686: Implementation of L3 Menu, Warn DB for E006
* DC MR 22733: W222, E006/GC, WIM: Implementation of complex key handling for warnings
* DC MR 21544: E006/GC: HIL: Get TPOL Menu HIL-ID and WIM-HIL-ID
* DC MR 22749: Integration of ARTEMMIS 3.2
*
*    Rev 1.10   Jul 13 2011 15:35:38   SCHL_Dirk.Gottwalles
* DC MR 22485: BR222, E006 Implementation of xml-files and style guide
* DC MR 22396: BR222: New acoustic for rearseatbeltwarning ÄLP2571
* DC MR 22456: Permanent Display menu - hybrid (GC)
* DC MR 21811: BR222: WIM: New Keywords/functions ÄLP2444, Part II
* DC MR 22265: W222, E006/AC, WIM:Change of Timeout behaviour
* DC MR 22261: W222, E006/AC, WIM: New keyword for WarnDB TIMEOUT_NOT_ENG_START, ÄLP2574
* DC MR 22260: W222, E006/AC, WIM: New keyword for WarnDB TIMEOUT_KL15_NOT_ENG_START, ÄLP2573
* DC MR 22092: W222, E006/AC, WIM: Door warning state is not correct evaluated for undefined values
*
*    Rev 1.9   May 13 2011 15:15:26   SCHL_Dirk.Gottwalles
* DC MR 22206: FLG: No more WIM requests necessary
* DC MR 22089: E004/GC, WIM: Configure warnings that keep the IC awake
* DC MR 22090: BR222/GC, WIM: Warning sounds are not played correct if sound subsystem was not active previoulsy
*
*    Rev 1.8   Apr 26 2011 09:48:54   SCHL_Dirk.Gottwalles
* DC MR 21809: B222/GC: WIM: Not automatic acknowledged message is acknowledged
* DC MR 21658: E004/AC, WIM: Lower priority activation feedback is is displayed bevor higher prior warning
* DC MR 21808: BR222/AC, WIM: Mapping of config "Luftfeder" wrong
* DC MR 21258: WIM: Display lag time not reset on KL15r Off
*
*    Rev 1.7   Dec 03 2010 15:57:00   SCHL_Lars.Gruenewald
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
*    Rev 1.6   Nov 19 2010 16:04:14   SCHL_Dirk.Gottwalles
* DC MR21122 BR222: WIM reaction at wakeupreq.
* DC MR21302 BR222/AC: Optimierung Aufruf Checkfunktion WIM
* DC MR20423 W222: WIM new acoustics requirements
* DC MR21177 Implementation of first WarnDB for E003
* DC MR21336 WIM: Using Enumeration Symbols for State/Widget Mapping
*
*    Rev 1.5   Jul 12 2010 16:39:50   SCHL_Lars.Gruenewald
* DC MR 20545 WIM: Extension of HMI Interface for E001.2
*
*    Rev 1.4   Jul 09 2010 18:01:48   SCHL_Lars.Gruenewald
* DC MR 20710 Vr222 WIM: Menue is in Display before warning
* DC MR 20545 WIM: Extension of HMI Interface for E001.2
*
*    Rev 1.3   Jun 30 2010 14:36:40   SCHL_Lars.Gruenewald
* DC MR 20629 Configuration of Display Handler
*
*    Rev 1.2   Jun 29 2010 18:57:24   SCHL_Lars.Grünewald
* DC MR 20629 Configuration of Display Handler
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
*    Rev 1.0   Jun 11 2010 14:07:30   SCHL_Thomas.Godemann
* Initial revision.
*
* --------------------------------------------------------------------------
* Date      | Author | Reason     | Change
* --------------------------------------------------------------------------
* 10-06-03    LarGru   MR20481      Initial revision for W222
*
*******************************************************************************/

/******************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*******************************************************************************/
/* System-headerfiles */
#include "cdef.h"

/* Foreign headerfiles */
#include "HMI_c1.h"
#include "DSM_ct.h"

/* Own headerfiles */
#include "WIM_c1.h"
#include "WIM__Scheduler.h"
#include "WIM__StateHandler.h"
#include "WIM__AcousticView.h"
#include "WIM__StateAccessHelpers.h"

/******************************************************************************
* GLOBAL DEFINITIONS
*******************************************************************************/

/**
* dynamic state of messages
*/
WIM__tstMsgState WIM__astMsgStates[WIM__nMaxMsgCount];

/**
 * @brief The number of blocked SLAck's
 */
uint8 WIM__u8SlackDisplayBlocked;

/******************************************************************************
* FILE LOCAL DEFINITIONS
*******************************************************************************/

/*******************
* MACROS/DEFINITIONS
********************/

/**
* Identifies inactiv/invalid (base tick) timer
*/
#define WIM__nInvalidTmr ((uint16)0xFFFF)

/*********************
* VARIABLES/CONSTANTS
**********************/

/**
* Flag: Enable scheduling (master search)
*/
static bool WIM__boSchedulePrioCheck;

/**
* Flag: Enable scheduling (resource handling)
*/
static bool WIM__boScheduleResources;

/**
* display master (valid WIM-enum or WIM_nenInvalidMsg if none)
* Warning in display.
*/
WIM_tenMsg WIM__enDspMaster;

/**
* display slack master (valid WIM-enum or WIM_nenInvalidMsg if none)
* Slack in display.
*/
WIM_tenMsg WIM__enDspSlackMaster;

/**
* display master waiting (valid WIM-enum or WIM_nenInvalidMsg if none)
* Warning waiting for display. WIM__vDspWarningRequest was done but no Acknowledge received until now.
*/
WIM_tenMsg WIM__enDspMasterWaiting;

/**
* display slack master waiting (valid WIM-enum or WIM_nenInvalidMsg if none)
* Slack waiting for display. WIM__vDspWarningRequest was done but no Acknowledge received until now.
*/
WIM_tenMsg WIM__enDspSlackMasterWaiting;

/**
* display favourite (valid WIM-enum or WIM_nenInvalidMsg if none)
*/
WIM_tenMsg WIM__enDspFavourite;

/**
* display slack favourite (valid WIM-enum or WIM_nenInvalidMsg if none)
*/
WIM_tenMsg WIM__enDspSlackFavourite;


/**
* Indicator for sound power failure
*/
bool WIM__boSoundPowerFail;

/**
* acoustic master (valid WIM-enum or WIM_nenInvalidMsg if none)
*/
static WIM_tenMsg WIM__enAcuMaster;

/**
* acoustic favourite (valid WIM-enum or WIM_nenInvalidMsg if none)
*/
static WIM_tenMsg WIM__enAcuFavourite;

/**
* Message related to ToneDelayTimer (valid WIM-enum or WIM_nenInvalidMsg if none)
*/
static WIM_tenMsg WIM__enMsgTD;

/**
* synchronisation delay counter (0..0xFFFE or WIM__nInvalidTmr)
*/
static uint16 WIM__u16SyncDelay;

/**
* Flag: don't start delay timers at first schedule after "RestoreWarnings"
*/
static bool WIM__boFirstScheduleRun;

/**
* switch for scheduling
*/
static bool WIM__boDoSchedule;

/**
* switch for scheduling slacks
*/
static bool WIM__boDoScheduleSlack;

/**
* display master change container
*/
static const WIM_tpvChangeCb WIM__apvDspChangeContainer_GC[] =
{
   /* content defined in configuration */
   WIM__nDspChangeContainerContent_GC
   WIM__nLastCntEntry /* must always be the last entry */
};


/******************************************************************************
* FILE LOCAL FUNCTION PROTOTYPES
*******************************************************************************/
static WIM_tenMsg WIM__enGetLevelLastMsg(WIM_tenMsg enMsg);
static void WIM__vStartAcu(WIM_tenMsg enOldAcuMaster);
static void WIM__vAcuCancel(bool boStopAcoustic);
static uint8 WIM__u8CheckWarnSuppr(WIM_tenMsg enMsg);
static bool WIM__boSbwAcousticsHilId(uint32 u32HilId);
static bool WIM_boSlacksBlocked(void);

/******************************************************************************
* FILE LOCAL FUNCTIONS
*******************************************************************************/

/**
* FORWARD Acoustic Master as HIL-ID
* into DPOOL and HMI by message
*   @return  void
*   @param   WIM_tenMsg Message identifier
*   @author  L.Gruenewald, Schleissheimer GmbH
*/
void WIM__vPublishAcuMaster(WIM_tenMsg enAcuMaster)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint32 u32HilId = 0;
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if(enAcuMaster < WIM_nenNoOfMessages)
   {
      /* Get the Hil-ID */
      u32HilId = WIM__u32GetHilId(enAcuMaster);
      /* Send the Message with the HilId */
      WIM__vSendAcoustWarning(u32HilId);
   }
   else
   {
      /* Send the Message for NO AcuMaster */
      WIM__vSendAcoustWarningNone();
   }
   /* Always publish by DPOOL */
   DPOOL_enSetPoolData(DPOOL_nDataWIM_u32AcoustWarning, &u32HilId);


}


/**
* Pack the message specific data into the uint32 message parameter
*
*   @return  message data
*   @param   enMsgEnum   MsgEnum for warning display request
*   @author  L.Gruenewald, Schleissheimer GmbH
*/
uint32 WIM__u32CreateMsgDataReqWarn(WIM_tenMsg enMsgEnum)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint32 u32RetData = 0;                  /* 32Bit Returnvalue, initialise with zero */
   uint32 u32HilId   = WIM__nInvalidHilId; /* local copy of HilId                     */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (enMsgEnum < WIM__mGetNoOfMessages)
   {
      /* Add WIM warning number */
      u32RetData = (((uint32)enMsgEnum) << 16);
      /* Get the HilId of given WarnNumber */
      u32HilId    = WIM__u32GetHilId(enMsgEnum);
      /* Add reduced HilId as Byte1 and Byte2 */
      u32RetData |= (0x0000FFFF & (u32HilId >> 8));
   }
   else if(enMsgEnum == WIM_nenInvalidMsg)
   {
      /* Add WIM warning number */
      u32RetData = (((uint32)enMsgEnum) << 16);
      /* Get the HilId of given WarnNumber */
      u32HilId    = WIM__nInvalidHilId;
      /* Add reduced HilId as Byte1 and Byte2 */
      u32RetData |= (0x0000FFFF & (u32HilId >> 8));
   }
   return u32RetData;
}

/**
* Cancel acoustics
*
*   @return  void
*   @param   boStopAcoustic   Stop acoustic hard yes/no
*   @author  A.Wagner, Schleissheimer GmbH
*/
static void WIM__vAcuCancel(bool boStopAcoustic)
{
   /*** release master */
   WIM__vStopAcoustic(WIM__enAcuMaster, boStopAcoustic);
   /* switch Off Mute/LowerVolume request signals */
   WIM__vSwitchHUCanSignals(WIM__enAcuMaster, Off);
   /* Publish Acoustic Master for HMI */
   WIM__vPublishAcuMaster(WIM_nenInvalidMsg);
   /* generate state handler event 'Acoustic Cancel' */
   WIM__vOnEvent_GC(WIM__enAcuMaster, WIM__nAcuCancel);
   /* mark master as invalid */
   WIM__enAcuMaster = WIM_nenInvalidMsg;
}

/**
* Get the last message in the priority level of the given message.
*   @return  last message of priority level
*   @param   message inside prio level
*   @author  T.Godemann, Schleissheimer GmbH
*/
static WIM_tenMsg WIM__enGetLevelLastMsg(WIM_tenMsg enMsg)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   WIM_tenMsg enRet = WIM__mGetLastMsg; /* message identifier                */
   uint8 u8Level;                        /* loop variable                     */
   bool boFound = False;                 /* search result                     */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   for (u8Level = 0; (u8Level < WIM__mGetNoOfPrioLevels) && !boFound; u8Level++)
   {
      if (   (enMsg >= WIM__mGetPrioTable[u8Level].enLevelStart)
          && (enMsg <= WIM__mGetPrioTable[u8Level].enLevelEnd  ))
      {
         enRet = WIM__mGetPrioTable[u8Level].enLevelEnd;
         boFound = True;
      }
   }

   return enRet;
}

/**
* Inform applications about display master change
*   @return  void
*   @param   HIL Id of new master
*   @author  T.Godemann, Schleissheimer GmbH
*/
void WIM__vDspChangeContainer_GC(uint32 u32HilId)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint8 u8Index = 0; /* index variable                                       */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   while (/* loop through all container functions */
          WIM__apvDspChangeContainer_GC[u8Index] != WIM__nLastCntEntry)
   {
      /* call container function */
      (WIM__apvDspChangeContainer_GC[u8Index])(u32HilId);
      u8Index++;
   }
}

/**
* Checks if message has to be suppressed by DispMaster
*   @return  True/False
*   @param   message ID
*   @author  M.Wenske, Schleissheimer GmbH
*/
static uint8 WIM__u8CheckWarnSuppr(WIM_tenMsg enMsg)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint8 u8StateSuppr = False;
   uint16 i;

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/

   /* Search over all warnings in container */
   for( i = 0; i < WIM__enCheckWarnSupprCount; i++)
   {
      if(      /* Warning was found */
               (WIM__astCheckWarnSuppr[i].enMsgSuppr == enMsg)
               /* Is triggered warning requested */
            && (WIM__u8GetDspQualifier(WIM__astCheckWarnSuppr[i].enMsgSupprTrig) != WIM__nNoRequest)
        )
      {
         /* Warning should be suppressed */
         u8StateSuppr = True;
      }
   }
   return u8StateSuppr;
}
/******************************************************************************
* PACKAGE LOCAL FUNCTIONS
*******************************************************************************/

/**
* Power-On initialisiation of scheduler class
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH
*/
void WIM__vSchedulerInit(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* init file local identifiers */
   WIM__u8SlackDisplayBlocked = 0;
   WIM__enDspMaster             = WIM_nenInvalidMsg;
   WIM__enDspMasterWaiting      = WIM_nenInvalidMsg;
   WIM__enDspSlackMaster        = WIM_nenInvalidMsg;
   WIM__enDspSlackMasterWaiting = WIM_nenInvalidMsg;
   WIM__enDspFavourite          = WIM_nenInvalidMsg;
   WIM__enDspSlackFavourite     = WIM_nenInvalidMsg;
   WIM__enAcuMaster             = WIM_nenInvalidMsg;
   WIM__enAcuFavourite          = WIM_nenInvalidMsg;
   WIM__enMsgTD                 = WIM_nenInvalidMsg;
   WIM__u16SyncDelay            = WIM__nInvalidTmr;
   WIM__boSoundPowerFail        = False;
   /* clear scheduler control flags */
   WIM__boSchedulePrioCheck    = False;
   WIM__boScheduleResources    = False;
   WIM__boFirstScheduleRun     = False;
   /* cancel asyc. acoustic delay timers */
   WIM__vCancelTimer(WIM__nTimerAcuDelModal);
   WIM__vCancelTimer(WIM__nTimerAcuDelNormal);
   /* cancel display delay timers */
   WIM__vCancelTimer(WIM__nTimerDspDelModal);
   WIM__vCancelTimer(WIM__nTimerDspDelNormal);

   /* init the Display Request state handler */
   WIM__vRequestDisplayStateHdl(WIM__nInitRequestDsp);

}

/**
* Trigger scheduling
* Sets an internal state, that will cause scheduling process in cyclic function
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH
*/
void WIM__vTriggerSchedule(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   WIM__boDoSchedule = True; /* next mainloop will do scheduling              */
   WIM__boDoScheduleSlack = True;
   
   /* After each event call slack schedule to prevent incorrect 
    * states in slack statemachine
    */
   WIM__vScheduleSlack(); 
}

/**
* Allow scheduling now, called at LCL Init
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH
*/
void WIM__vStartSchedule(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   WIM__boSchedulePrioCheck = True;
   WIM__boScheduleResources = True;
}

/**
* Stop search for new master
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH
*/
void WIM__vStopSchedule(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   WIM__boSchedulePrioCheck = False;
   /* cancel asyc. acoustic delay timers */
   WIM__vCancelTimer(WIM__nTimerAcuDelModal);
   WIM__vCancelTimer(WIM__nTimerAcuDelNormal);
   /* cancel display delay timers */
   WIM__vCancelTimer(WIM__nTimerDspDelModal);
   WIM__vCancelTimer(WIM__nTimerDspDelNormal);

   /* Flag: don't start delay timers at first schedule after "RestoreWarnings" */
   WIM__boFirstScheduleRun = True;
}

/**
* Disable scheduling, called at LCL Off
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH
*/
void WIM__vEndSchedule(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   WIM__boSchedulePrioCheck = False;
   WIM__boScheduleResources = False;
   WIM__boFirstScheduleRun  = False;
   /* cancel asyc. acoustic delay timers */
   WIM__vCancelTimer(WIM__nTimerAcuDelModal);
   WIM__vCancelTimer(WIM__nTimerAcuDelNormal);
   /* cancel display delay timers */
   WIM__vCancelTimer(WIM__nTimerDspDelModal);
   WIM__vCancelTimer(WIM__nTimerDspDelNormal);
}



/**
* This function returns the current displayed message if any.
*   @return  identifier of message - or WIM_nenInvalidMsg if not present
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH
*/
WIM_tenMsg WIM__enGetDisplayMaster(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   return WIM__enDspMaster;
}

/**
* This function returns the current message that is waiting for display assignment.
*   @return  identifier of message - or WIM_nenInvalidMsg if not present
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH
*/
WIM_tenMsg WIM__enGetDisplayMasterWaiting(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   return WIM__enDspMasterWaiting;
}

/**
* This function returns the current slack that is waiting for display assignment.
*   @return  identifier of message - or WIM_nenInvalidMsg if not present
*   @param   none
*   @author  A.Wagner, Schleissheimer GmbH
*/
WIM_tenMsg WIM__enGetDisplaySlackMasterWaiting(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   return WIM__enDspSlackMasterWaiting;
}

/**
* This function returns the current acoustic message if any.
*   @return  identifier of message - or WIM_nenInvalidMsg if not present
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH
*/
WIM_tenMsg WIM__enGetAcousticMaster(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   return WIM__enAcuMaster;
}

/**
* This function counts the delay timers used for synchronisation. The SFG
* function returns the number of BaseTicks needed to reach the synchronisation
* point. Used for synchroneous/display synchroneous acoustics.
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH
*/
void WIM__vCountSyncDelay(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* timer valid and running? */
          (WIM__u16SyncDelay != WIM__nInvalidTmr)
       && (WIM__u16SyncDelay > 0))
   {
      WIM__u16SyncDelay--;
   }
}

/**
* Timer callback function.
* Called if the display master change delay timers have elapsed.
* - WIM__nTimerAcuDelModal   timer modal output phase
* - WIM__nTimerAcuDelNormal  timer normal output phase
* - WIM__nTimerDspDelModal   timer modal output phase
* - WIM__nTimerDspDelNormal  timer normal output phase
*   @return  void
*   @param   enTimer: Timer identifier, xCorrTag: Correlation tag (message Id)
*   @author  T.Godemann, Schleissheimer GmbH
*/
void WIM__vDelayTimer(WIM__tenTimer enTimer, WIM__txCorrTag xCorrTag)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* just trigger the scheduler */
   WIM__vTriggerSchedule();
   WIM__vScheduleAcoustics();
}


/**
* Starts the ToneDelayTimer
*   @return  void
*   @param   enMsg: Message the timer was started with
*   @author  A.Wagner, Schleissheimer GmbH
*/
void WIM__vToneDelayTimerStart(WIM_tenMsg enMsg)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/

   /* set related message */
   WIM__enMsgTD = enMsg;
   /* start ToneDelay timer */
   TIMER_vStart(TIMER_nWIM_TimerAcuTDElapsed, WIM_nTimerDuration_AcuTDElapsed);
}

/**
* Tone Delay callback function.
* Called if the delay timer has elapsed.
* - WIM__nTimerAcuTDElapsed
*   @return  void
*   @param   none
*   @author  A.Wagner, Schleissheimer GmbH
*/
void WIM__vToneDelayTimerElapsed(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* inform the state machine after tone delay elapsed */
   WIM__vOnEvent_GC((WIM_tenMsg)WIM__enMsgTD,WIM__nAcuDelayElapsed);
}

/**
* Start the Acoustic
*   @return  void
*   @param   enOldAcuMaster: AcuMaster that was stopped before
*   @author  A.Wagner, Schleissheimer GmbH
*/
void WIM__vStartAcu(WIM_tenMsg enOldAcuMaster)
{
   bool boAcuStarted = FALSE;         /* flag, if start of acoustics was successful */
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /***** start new acoustic */
   WIM__enAcuMaster = WIM__enAcuFavourite;
   /* Publish Acoustic Master for HMI */
   WIM__vPublishAcuMaster(WIM__enAcuMaster);

   if ( /* new AcuMaster will be asynchron acoustic only */
      WIM__enAcuMaster != WIM_nenInvalidMsg
      && (WIM__mu8GetAcuQualifier(WIM__enAcuMaster) & WIM__nAcuRequested)
      && !WIM__boGetStateAttr(WIM__nAttrAcuSync, WIM__enAcuMaster)
      && WIM__menGetMsgType(WIM__enAcuMaster) == WIM__nAcoustic
      )
   {
      if (!WIM__mu8GetAcuRetriggered(WIM__enAcuMaster) &&
         !WIM__mboGetAcuPlayedFlag(WIM__enAcuMaster))
      {
         /* start asyc. acoustic delay timers */
         WIM__vStartTimer(WIM__nTimerAcuDelModal, WIM__enAcuMaster);
         WIM__vStartTimer(WIM__nTimerAcuDelNormal, WIM__enAcuMaster);
      }
   }
   else
   {
      if (   /* AcuMaster is synchron acoustic */
         WIM__enAcuMaster != WIM_nenInvalidMsg
         && (WIM__mu8GetAcuQualifier(WIM__enAcuMaster) & WIM__nAcuRequested)
         && (WIM__boGetStateAttr(WIM__nAttrAcuSync, WIM__enAcuMaster)))
      {
         /* cancel asyc. acoustic delay timers */
         WIM__vCancelTimer(WIM__nTimerAcuDelModal);
         WIM__vCancelTimer(WIM__nTimerAcuDelNormal);
      }
   }

   if (/* Display is ON or
          display is OFF and master has acoustic-only attribute */
          (WIM__boDisplayState || !WIM__boDisplayState && (WIM__menGetMsgType(WIM__enAcuMaster) == WIM__nAcoustic))
          &&
          !(WIM__boSbwAcousticsHilId(WIM__enAcuMaster) && (WIM__mu8GetAcuRetriggered(WIM__enAcuMaster) || WIM__mboGetAcuPlayedFlag(WIM__enAcuMaster)))
          )
   {
      boAcuStarted = WIM__boStartAcoustic(WIM__enAcuMaster, enOldAcuMaster);
      /* generate state handler event 'Acoustic Assign' */
      WIM__vOnEvent_GC(WIM__enAcuMaster, WIM__nAcuAssign);
   }
   if (!boAcuStarted)
   {
      /* cancel asyc. acoustic delay timers */
      WIM__vCancelTimer(WIM__nTimerAcuDelModal);
      WIM__vCancelTimer(WIM__nTimerAcuDelNormal);
      WIM__vOnEvent_GC(WIM__enAcuMaster, WIM__nAcuCancel);
   }
}

/**
* This is the first phase of scheduler operation called from foreground.
* Depending on the current master's state it will be checked if a new request
* with a higher priority will displace current display or acoustic master.
* Display blink and acoustic frequencies are requested here. The synchronisation
* conditions are checked in WIM__vScheduleRessourceReq at a later point. Do to
* the order of function calls (WIM SchedulerPrioCheck, SFG, WIM SchedulerReq)
* requested frequencies may be already available at the call of
* WIM__vScheduleRessourceReq.
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH
*/
void WIM__vSchedulePrioCheck(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boSearchRoll = False;     /* flag: search favourite via U-Roll algor.        */
   bool boFavouriteFound;         /* flag: found favourite during search             */
   WIM_tenMsg enFirstDspRollMsg;  /* leading/first message in U-Roll                 */
   WIM_tenMsg enNextDspRollMsg;   /* message in U-Roll behind master                 */
   WIM_tenMsg enSearchStart;      /* start message in search loop                    */
   WIM_tenMsg enSearchEndDsp;     /* message where dsp favourite search ends         */
   WIM_tenMsg enCurMsg;           /* search loop variable, current message           */
   uint8 u8SearchMask = 0;        /* bit mask for dsp favourite search               */
   uint8 u8QualFavourite = 0;     /* qualifier of current favourite                  */
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   
   if (/* scheduler triggered? */
          (True == WIM__boDoSchedule)
       /* and scheduling allowed */
       && (True == WIM__boSchedulePrioCheck))
   {
      /* preset favourites as invalid */
      WIM__enDspFavourite = WIM_nenInvalidMsg;
      enFirstDspRollMsg = WIM_nenInvalidMsg;
      enNextDspRollMsg = WIM_nenInvalidMsg;

      /*----------------------------------------------------------------------
        Scheduling will be done in 3 steps. At first the master is analyzed.
        Depending on the state of the master a search mask is defined:
        DISPLAY:
        a) there is no master or current master has withdrawn display request:
           -> search all messages starting with highest priority
        b) master is handling and in modal display phase:
           -> search starts with highest prio and ends within masters level
           -> master can only be replaced by other handling messages
        c) master is in normal display phase:
           -> search starts with highest prio and ends within masters level
           -> master can be replaced by handling or urgent messages
           -> if master is in roll mode (unqualified) other 'new'
              messages can replace it too
        d) master is in continuous display phase (unqualified):
           -> search starts with highest prio and ends within masters level
           -> master can be replaced by any other new/urgent/handling msg.
           -> if there is no message, the next message for roll is chosen
        ACOUSTICS:
        a) search always starts with highest prio message
        b) search ends with current master or if any favourite is found
        ----------------------------------------------------------------------*/

      /* search always starts at the highest priority level */
      enSearchStart = WIM__mGetHighestPrioMessage;

      /* --- Display ---------------------------------------------------------*/
      if (/* no current display master? */
             (WIM__enDspMaster == WIM_nenInvalidMsg)
          /* or this master does not request the display */
          || (WIM__u8GetDspQualifier(WIM__enDspMaster) == WIM__nNoRequest))
      {
            /* No master: search all from top to find a least one favourite */
            u8SearchMask = WIM__nQualNew | WIM__nQualUrgt | WIM__nQualHdl;
            /* search all levels */
            enSearchEndDsp = WIM__mGetLowestPrioMessage;

            /*
            * If the current display master has no display request anymore, then the
            * roll has to be used as new master source too.
            * This is the case if the last master was a handling message and now the display
            * roll must proceed with a normal warning. Or if the current roll message has
            * been automatically quitted.
            */
            if(WIM__enDspMaster != WIM_nenInvalidMsg &&
               WIM__u8GetDspQualifier(WIM__enDspMaster) == WIM__nNoRequest)
            {
               boSearchRoll = True;
            }
      }
      else /* display master present */
      {
         /* search only current master prio level and above */
         enSearchEndDsp = WIM__enGetLevelLastMsg(WIM__enDspMaster);
         /* keep current master until new favourite found */
         WIM__enDspFavourite = WIM__enDspMaster;

         switch (/* check master state */
                 WIM__mu8GetDspState(WIM__enDspMaster))
         {
            /*********** 0ms < display time <= 500ms ***************/
            case WIM__nWaitForDsp:
            case WIM__nModalPhase:
               {
	               if (/* check if master is a handling-message */
	                   (WIM__u8GetDspQualifier(WIM__enDspMaster) & WIM__nQualHdl) != 0)
	               {
	                  u8SearchMask = WIM__nQualHdl; /* search only handling msgs */
	               }
	               else
	               {
	                  u8SearchMask = WIM__nNoRequest; /* don't search new favourite */
	               }
               } break;

            /*********** 500ms < display time <= 5000ms ************/
            case WIM__nPreConfirmed:
            case WIM__nNormalPhase:
               {
                  if (/* check if master is a handling-message */
                      (WIM__u8GetDspQualifier(WIM__enDspMaster) & WIM__nQualHdl) != 0)
	               {
                     /* search urgent and handling msgs */
	                  u8SearchMask = WIM__nQualUrgt | WIM__nQualHdl;
	               }
	               else
	               {
	                  u8SearchMask = WIM__nQualUrgt; /* search only urgent msgs */
	               }
               } break;

            /*********** display time > 5000ms *********************/
            case WIM__nContinousPhase:
               {
	               /* master in countinous display/roll: search qualified */
	               u8SearchMask = WIM__nQualNew | WIM__nQualUrgt | WIM__nQualHdl;
	               boSearchRoll = True;          /* search roll favourite */
               } break;

            /*********** invalid state: perform full search ********/
            default:
               {
	               /* invalidate master */
	               WIM__enDspMasterWaiting = WIM__enDspMaster = WIM_nenInvalidMsg;
	               /* search all from top to find a least one favourite */
	               u8SearchMask = WIM__nNoQualifier | WIM__nQualNew | WIM__nQualUrgt | WIM__nQualHdl;
	               /* search all levels */
	               enSearchEndDsp = WIM__mGetLowestPrioMessage;
               } break;
         }
      }


      /*----------------------------------------------------------------------
        Now the second Scheduling step follows:
        DISPLAY:
        In a loop the message state of each message inside the search range
        is checked:
        - all messages without display request are omitted
        - all messages matching the search mask will be evaluated
        - the message with the most prior qualifier will be chosen as new
          favourite
        - qualifier prio (lo->hi): unqualified -> new -> urgent -> handling
        If there is more then one message with the same qualifier level, the
        one with the highest sub-priority is used as new favourite.

        If the master is unqualified and there is no other qualified but
        several unqualified msgs, the roll mechanism will be used.
        Roll:
        - The (unqualified) msg directly following current master is selected
        - If there is no following, the 1st unqualified in master's prio level
          is selected
        - If no other unqualified is found, master will be displayed
          continously
        ACOUSTIC:
        The same loop also searches a new acoustic favourite. If a master is
        present, only messages with a higher prio then the master are checked.
        If not, search stops when the first request is found.
       ----------------------------------------------------------------------*/

      /* some initialisations: */
      u8QualFavourite = WIM__nNoRequest; /* init qualifier memory */
      enCurMsg = enSearchStart; /* start with first msg in search range */
      boFavouriteFound = False;
      /* --- DISPLAY ---- */
      while (/* search until display favourite have been found */
                (enCurMsg <= enSearchEndDsp))
      {
         if (/* omit all msgs with no request for display or acoustic channel */
             WIM__mu8GetQualifier(enCurMsg) != WIM__nNoRequest
             /* Message is not a slack */
             && !WIM__mboIsSlackMsg(enCurMsg))
         {
            /* --- DISPLAY ---- */
            if (/* Is a display request set for this message? */
                   (WIM__u8GetDspQualifier(enCurMsg) != WIM__nNoRequest)
                /* and has the end of the search range not been reached? */
                && (enCurMsg <= enSearchEndDsp)
                /* and do we need to search at all? */
                && (u8SearchMask != WIM__nNoRequest)
                /* Warning should not be suppressed */
                && !WIM__u8CheckWarnSuppr(enCurMsg)
               )
            {
               /*** search for qualified message ************************/
               if (/* does the message match our search mask? */
                     (WIM__u8GetDspQualifier(enCurMsg) & u8SearchMask) &&
                     /* is this not the current master */
                     (enCurMsg != WIM__enDspMaster) &&
                     /* and has a higher qualification */
                     (
                        (
                           ((u8QualFavourite & (~WIM__nQualHdl)) < (WIM__u8GetDspQualifier(enCurMsg) & (~WIM__nQualHdl))) ||
                           /* or if same qualification is given, has a higher sub prio (priorization of urgent warnings) */
                           ((u8QualFavourite & (~WIM__nQualHdl)) == (WIM__u8GetDspQualifier(enCurMsg) & (~WIM__nQualHdl))) &&
                           (enCurMsg < WIM__enDspFavourite)
                        ) ||
                        /* A handling message always replaces a current handling message */
                        (
                           (WIM__u8GetDspQualifier(WIM__enDspFavourite) & WIM__nQualHdl) &&
                           (WIM__u8GetDspQualifier(enCurMsg) & WIM__nQualHdl)
                        )
                     )
                  )
               {
                  /* select this message as new favourite */
                  WIM__enDspFavourite = enCurMsg;
                  /* save qualifier for comparison */
                  u8QualFavourite = WIM__u8GetDspQualifier(enCurMsg);
                  if (/* do this only once (after first candidate was found) */
                      False == boFavouriteFound)
                  {
                     /* set end of search to end of this message priority level   */
                     enSearchEndDsp = WIM__enGetLevelLastMsg(enCurMsg);
                     /* no roller search, because we found a qualified favourite  */
                     enFirstDspRollMsg = enNextDspRollMsg = WIM_nenInvalidMsg;
                     boSearchRoll = False;    /* not longer required              */
                     boFavouriteFound = True; /* prevent second execution of code */
                  }
               }

               /*** search for display roll message *********************/
               if (boSearchRoll)
               {
                  if (/* must be the first unqualified message */
                         (enFirstDspRollMsg == WIM_nenInvalidMsg)
                      && (WIM__u8GetDspQualifier(enCurMsg) == WIM__nNoQualifier))
                  {
                     enFirstDspRollMsg = enCurMsg;
                     enSearchEndDsp = WIM__enGetLevelLastMsg(enCurMsg);
                  }
                  else
                  {
                     if (/* must follow master in sub-priority */
                            (enCurMsg > WIM__enDspMaster)
                         /* and must be unqualified */
                         && (WIM__u8GetDspQualifier(enCurMsg) == WIM__nNoQualifier))
                     {
                        enNextDspRollMsg = enCurMsg;
                        boSearchRoll = False; /* not longer required */
                     }
                  }
               }
            }

         }
         /* step to next message */
         enCurMsg++;
      }

      /*** roll handling */
      if (/* successing message found? */
          enNextDspRollMsg != WIM_nenInvalidMsg)
      {
         WIM__enDspFavourite = enNextDspRollMsg; /* select msg as new favourite */
      }
      else
      {
         if (/*  first/start message of roll found? */
             enFirstDspRollMsg != WIM_nenInvalidMsg)
         {
            WIM__enDspFavourite = enFirstDspRollMsg; /* select msg as new favourite */
         }
      }

      /*** display message delay due to async. acoustic/master release
       - if a async. acoustic is running < 500 sec. no message will be displayed
       - if a async. acoustic is running > 500 && < 5000 sec. only urgent and handling
         messages are displayed
       - if the display master is no longer valid, it will be freed
       - if master was released, next message is delayed for 5000ms,
         or 500ms if the new message is urgent or handling "kurzzeitige Ruhe"
      */
      if (/* we have no display master */
             (WIM__enDspMaster == WIM_nenInvalidMsg)
          /* or current master still requests the display - if not, allow the change
             even if a delay timer is running */
          || (WIM__u8GetDspQualifier(WIM__enDspMaster) != WIM__nNoRequest)  )
      {
         if (/* we found a display favourite */
             (WIM__enDspFavourite != WIM_nenInvalidMsg))
         {
            u8QualFavourite = WIM__u8GetDspQualifier(WIM__enDspFavourite);
            if (
                (/* timer for async. acoustic "Normal" time (5000ms) is running */
                    (WIM__enGetTimer(WIM__nTimerAcuDelNormal) == WIM__nTimerRunning)
                 && (!WIM__boGetStateAttr(WIM__nAttrAcuSync, WIM__enAcuMaster))
                 /* and the acoustic modal timer is running (500ms) */
                 && (   (WIM__enGetTimer(WIM__nTimerAcuDelModal) == WIM__nTimerRunning)
                     /* or the new favourite is not urgent -> use current master  */
                     || ((u8QualFavourite & (WIM__nQualUrgt | WIM__nQualHdl)) == 0))
                )
                ||
                (/* timer for display delay after master release (5000ms) is running */
                    (WIM__enGetTimer(WIM__nTimerDspDelNormal) == WIM__nTimerRunning)
                 /* if the new favourite is urgent do use new favourite */
                 && (   ((u8QualFavourite & (WIM__nQualUrgt | WIM__nQualHdl)) == 0)
                     /* if the display modal timer is running (500ms) */
                     || (WIM__enGetTimer(WIM__nTimerDspDelModal) == WIM__nTimerRunning)
                     /* or the favourite is not urgent -> use current master */
                     || ((u8QualFavourite & WIM__nQualUrgt) == 0))
                )
                ||
                /* If current master is acousitc only, do not search for new
                 * favourite in lower H-Prios, even if there is no display master,
                 * while in the normal display time (5000ms).
                 * WKIS2799, Case 7-9
                */
                (   WIM__enGetTimer(WIM__nTimerAcuDelNormal) == WIM__nTimerRunning
                 && WIM__enAcuMaster != WIM_nenInvalidMsg
                 && WIM__menGetMsgType(WIM__enAcuMaster) == WIM__nAcoustic
                 && WIM__u8GetMsgPrioLevel(WIM__enAcuMaster) < WIM__u8GetMsgPrioLevel(WIM__enDspFavourite)
                )
               )
            {
               /* keep old master or if none an empty display */
               WIM__enDspFavourite = WIM__enDspMaster;
            }
         }
      }
      /*--------------------------------------------------------------------
        The third step deals with display frequency requests
        - request frequencies for display
        - overwrite acoustic favourite if display favourite has sync. acoustic
          and a higher priority
        --------------------------------------------------------------------*/

      /*** 1: Display frequency request   replaced in W222 */
      /* replaced for W222, no ComplexView handling by WIM */

      /*** 2: Display synchroneous acoustic */
      /* overwrite acoustic favourite by display master if
         - display master has display synchroneous acoustic
         - the priority of the display master is higher then the current
           acoustic favourite's
      */
      /* Removed due to acoustic redesign */

      /* scheduling done! */
      WIM__boDoSchedule = False;
   }
   
}

/**
* WIM__vScheduleAcoustics  
*   @return  void
*   @param   none
*   @author  A.Wagner, Schleissheimer GmbH 
*/
void WIM__vScheduleAcoustics(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boFavouriteFound;              /* flag: found favourite during search       */
   WIM_tenMsg enSearchStart;           /* start message in search loop              */
   WIM_tenMsg enSearchEndAcu;          /* message where acu favourite search ends   */
   WIM_tenMsg enCurMsg;                /* search loop variable, current message     */
   bool boAcuInRoll = False;           /* search for acoustics in display roll      */
   WIM_tenMsg enOldAcuMaster = WIM_nenInvalidMsg; /* stopped AcuMaster              */
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   
   if (
       /*scheduling allowed */
       True == WIM__boSchedulePrioCheck)
   {
      /* search always starts at the highest priority level */
      enSearchStart = WIM__mGetHighestPrioMessage;
      /* search all levels */
      enSearchEndAcu = WIM__mGetLowestPrioMessage;
      /* some initialisations: */
      enCurMsg = enSearchStart; /* start with first msg in search range */
      boFavouriteFound = False;

      if (/* no current acoustic master? */
             (WIM__enAcuMaster == WIM_nenInvalidMsg)
          /* or this master is not requested any more */
          || !(WIM__mu8GetAcuQualifier(WIM__enAcuMaster) & WIM__nAcuRequested))
      {
         /* search over all messages */
         WIM__enAcuFavourite = WIM_nenInvalidMsg;
      }
      else /* acoustic master present */
      {
         /* search only current master prio level and above */
         enSearchEndAcu = WIM__enGetLevelLastMsg(WIM__enAcuMaster);
         if (   WIM__mu8GetAcuState(WIM__enAcuMaster) != WIM__nAcuStatePlaying
             && WIM__mu8GetAcuState(WIM__enAcuMaster) != WIM__nAcuStateWaitForTerm
             && WIM__mu8GetAcuState(WIM__enAcuMaster) != WIM__nAcuStateToneDelay)
         {
            WIM__enAcuMaster = WIM_nenInvalidMsg;
         }
         /* keep current master until new favourite found */
         WIM__enAcuFavourite = WIM__enAcuMaster; 
      }

      if (WIM__mu8GetDspState(WIM__enDspMaster) == WIM__nContinousPhase)
      {
         boAcuInRoll = True;
      }

      /* --- ACOUSTICS ---- */
      while(/* search until acoustic favourite have been found */
            (enCurMsg <= enSearchEndAcu)) 
      {
         if (/* Is an acoustic request set for this message? */
             (WIM__mu8GetAcuQualifier(enCurMsg) & WIM__nAcuRequested))
         {
            /*** search for qualified message ************************/
            if (
                  /* has a higher qualification (SyncUrgent and not played yet) */
                  (
                        (WIM__mu8GetAcuQualifier(enCurMsg) & WIM__nAcuSyncUrgent) 
                     && (!WIM__mboGetAcuPlayedFlag(enCurMsg))
                  ) 
               ||
                  /* or has a higher sub prio (and not played yet) */
                  (
                        (enCurMsg < WIM__enAcuFavourite) 
                     && (!WIM__mboGetAcuPlayedFlag(enCurMsg))
                  ) 
               ||
                  /* no Fav anymore */
                  (
                        (enCurMsg < WIM__enAcuFavourite) 
                     && (WIM__enAcuFavourite == WIM_nenInvalidMsg)
                  ) 
               ||
                  /* Master waiting for termination */
                  (
                        (enCurMsg < WIM__enAcuFavourite) 
                     && (WIM__mu8GetAcuQualifier(WIM__enAcuMaster) & WIM__nAcuWaitForTerm)
                  )
                )
            {
               if( /* Exeption for replacement synchron-single -> asynchron with lower prio
                      => singletone is not canceled 
                      AcuMaster is in state WaitForTerm */
                     (WIM__mu8GetAcuQualifier(WIM__enAcuMaster) & WIM__nAcuWaitForTerm)
                     /* and AcuMaster is synchron singletone */
                  && (WIM__mboIsDspSyncAcu(WIM__enAcuMaster) == True)
                  && (WIM__enGetToneType(WIM__enAcuMaster) == WIM__enSingleTone)
                     /* and new acoustic is asynchron */
                  && (WIM__mboIsDspSyncAcu(enCurMsg) == False)
                     /* and priority of new acoustic is lower than AcuMaster */
                  && (enCurMsg > WIM__enAcuMaster)
                     /* and warning is still displayed */
                  && (WIM__enDspMaster != WIM_nenInvalidMsg)
                     /* and it wasn't triggered by ManuQuit event */
                  && (WIM__mu8GetDspState(WIM__enDspMaster) != WIM__nManuQuit)
                  )
               {
                  /* do nothing - AcuMaster is not canceled */
               }
               else
               {
                  /* select this message as new favourite */
                  WIM__enAcuFavourite = enCurMsg;
                  if (/* do this only once (after first candidate was found) */ 
                      False == boFavouriteFound)
                  {
                     /* set end of search to end of this message priority level   */
                     enSearchEndAcu = WIM__enGetLevelLastMsg(enCurMsg);
                     boFavouriteFound = True; /* prevent second execution of code */
                     boAcuInRoll = False;
                  }
               }
               
               if (boAcuInRoll)
               {
                  if( /* higher sub prio (and already played) */
                     ((enCurMsg < WIM__enAcuFavourite) &&
                      (WIM__mboGetAcuPlayedFlag(enCurMsg))))
                  {
                     /* select this message as new favourite */
                     WIM__enAcuFavourite = enCurMsg;             
                     /* set end of search to end of this message priority level   */
                     enSearchEndAcu = WIM__enGetLevelLastMsg(enCurMsg);
                     boAcuInRoll = False;
                  }
               }
            }
         }
      /* step to next message */
      enCurMsg++;
      }
   }
   /***********************************************************************
   ************************** RessourceRequest ****************************
   ***********************************************************************/
    /*-------------------------------------------------------------------------
     ACOUSTIC
     - check if synchronisation conditions are fullfilled (if existing)
     - replace/set master if new favourite found (or favourite synchronized)
     - release master if no favourite found
     -------------------------------------------------------------------------*/
   if (/* only if the output is possible and at least one request for RES_Active is set */
       (CRHDL_enStateHdlGetState(CRHDL_nSMSRES_Audio_HW) != CRHDL_nStateOn)
       ||
       /* or if scheduler is disabled */
          (False == WIM__boScheduleResources)
       /* or soundsystem is in state power fail */
       || (WIM__boSoundPowerFail == True))
   {
      WIM__enAcuFavourite = WIM_nenInvalidMsg;
   }
   /* Favourite not found */
   if (WIM__enAcuFavourite == WIM_nenInvalidMsg)
   {
      if (/* Master is valid */
          WIM__enAcuMaster != WIM_nenInvalidMsg)
      {
         if (/* acoustics should play to its end */
             (WIM__mu8GetAcuQualifier(WIM__enAcuMaster) & WIM__nAcuWaitForTerm)
             && !(
               /* No current playing Tone */
               (WIM_enGetPlayingSound() == WIM_nenInvalidMsg)
             ))
         {
            /* Stop acoustic, keep master until sound has ended */
            WIM__vStopAcoustic(WIM__enAcuMaster, False);
         }
         else
         {
            /* stop Acoustic -> hard Stop */
            WIM__vAcuCancel(True);
         }
      }
   }
   else  /* Favourite is found */
   {
      if (/* Master is active and fav */
          WIM__enAcuMaster == WIM__enAcuFavourite)
      {
         if (/* Tone Delay Elapsed (300ms) */
             WIM__mu8GetAcuQualifier(WIM__enAcuMaster) & WIM__nAcuTdElapsed)
         {
            /* Start Acoustic */
            WIM__vStartAcu(WIM_nenInvalidMsg);
         }
         else  /* Tone delay not elapsed */
         {
            if (/* a new Retrigger/Register threw playing is done */
                WIM__mu8GetAcuRestart(WIM__enAcuMaster) == True)
            {
               WIM__vAcuCancel(True);

               if (/* is Master a synchronous acosutic */
                  WIM__boGetStateAttr(WIM__nAttrAcuSync, WIM__enAcuFavourite))
               {
                  /* set Favourite already as new Master */
                  WIM__enAcuMaster = WIM__enAcuFavourite;
                  /* Start tone delay */
                  WIM__vOnEvent_GC(WIM__enAcuFavourite, WIM__nAcuAssignTD);
               }
               else  /* Master is asynchronous acosutic */
               {
                  /* Start Acoustic, set new Master */
                  WIM__vStartAcu(WIM__enAcuFavourite);
                  /* Send AcuAssign Event */
                  WIM__vOnEvent_GC(WIM__enAcuFavourite, WIM__nAcuAssign);
               }
            }
         }
      }
      else /* a new Favourite is found */
      {
         /* stop Acoustic -> hard Stop */
         if (WIM__enAcuMaster != WIM_nenInvalidMsg)
         {
            enOldAcuMaster = WIM__enAcuMaster;
            WIM__vAcuCancel(True);
         }
         /* is a Tone Delay (300ms) required ? */
         if (
            /* ---------------------------------------- Case 1 ---------------------------------------- */
            (
            /* Favorite is sync */
            (WIM__boGetStateAttr(WIM__nAttrAcuSync, WIM__enAcuFavourite))
            /* The tone delay isn't elapsed */
            && (!(WIM__mu8GetAcuQualifier(WIM__enAcuFavourite) & WIM__nAcuTdElapsed))
            )
            ||
            /* ---------------------------------------- Case 2 ---------------------------------------- */
            (
            (enOldAcuMaster != WIM_nenInvalidMsg)
            /* old acumaster isn't a handling message */            
            && (!WIM__mboIsHandling(enOldAcuMaster))
            /* old acumaster is not in the ManuQuit display state */
            && (WIM__mu8GetDspState(enOldAcuMaster) != WIM__nManuQuit)
            /* old acumaster is not in the AutoQuit display state */
            && (WIM__mu8GetDspState(enOldAcuMaster) != WIM__nAutoQuit)
            /* Favorite message is async */
            && (!WIM__boGetStateAttr(WIM__nAttrAcuSync, WIM__enAcuFavourite))
            /* Master is sync */
            && (WIM__boGetStateAttr(WIM__nAttrAcuSync, enOldAcuMaster)) 
            /* Master < Favourite */
            && (enOldAcuMaster < WIM__enAcuFavourite)
            /* Master isn't an interval tone */
            && (WIM__enGetToneType(enOldAcuMaster) != WIM__enPeriodicIntervalTone)
            /* The tone delay isn't elapsed */
            && (!(WIM__mu8GetAcuQualifier(WIM__enAcuFavourite) & WIM__nAcuTdElapsed))
            )
            ||
            /* ---------------------------------------- Case 3 ---------------------------------------- */
            (
            (enOldAcuMaster != WIM_nenInvalidMsg)
            /* Old acumaster is handling message */
            && (WIM__mboIsHandling(enOldAcuMaster))
            /* old acumaster is not in the ManuQuit display state */
            && (WIM__mu8GetDspState(enOldAcuMaster) != WIM__nManuQuit)
            /* old acumaster is not auto quit (is normal warning replacement) */
            /*&& !(WIM__mu8GetAcuQualifier(enOldAcuMaster) & WIM__nAcuQualHdlAQuit)*/
            /* Favorite message is async */
            && (!WIM__boGetStateAttr(WIM__nAttrAcuSync, WIM__enAcuFavourite))
            /* Master is sync */
            && (WIM__boGetStateAttr(WIM__nAttrAcuSync, enOldAcuMaster)) 
            /* Master < Favourite */
            && (enOldAcuMaster < WIM__enAcuFavourite)
            /* Master isn't an interval tone */
            && (WIM__enGetToneType(enOldAcuMaster) != WIM__enPeriodicIntervalTone)
            /* The tone delay isn't elapsed */
            && (!(WIM__mu8GetAcuQualifier(WIM__enAcuFavourite) & WIM__nAcuTdElapsed))
            )
            )
         {
            /* set Favourite already as new Master */
            WIM__enAcuMaster = WIM__enAcuFavourite;
            /* Start tone delay */
            WIM__vOnEvent_GC(WIM__enAcuFavourite, WIM__nAcuAssignTD);
         }
         else /* tone Delay not required */
         {
            /* Start Acoustic */
            WIM__vStartAcu(enOldAcuMaster);
         }
      }
   }
   
}

/**
* This is the second phase of scheduler operation called from the base tick
* function. Synchronisation conditions are checked within this function and
* current master is set, replaced or released for both display and acoustics.
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH
*/
void WIM__vScheduleRessourceReq(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   
   if (/* if scheduler is disabled, make sure that we stop savely display or
          acoustic output */
       False == WIM__boScheduleResources)
   {
      /* set favourite to invalid, this will cause release of master */
      WIM__enDspFavourite = WIM_nenInvalidMsg;
   }

   /*-------------------------------------------------------------------------
     DISPLAY
     - check if synchronisation conditions are fullfilled (if existing)
     - replace/set master if new favourite found (or favourite synchronized)
     - release master if no favourite found
     - do the display request for the current master
     -------------------------------------------------------------------------*/
   if (/* did we found a favourite? */
       WIM__enDspFavourite != WIM_nenInvalidMsg)
   {
      if (/* will favourite replace master? */
             WIM__enDspFavourite != WIM__enDspMaster
          /* For Favourite was no WarningRequest sent */
          && WIM__enDspFavourite != WIM__enDspMasterWaiting
          /* only request a Display warning when Display is On */
          && WIM__boDisplayState == On)
      {
         /** set new master */
         WIM__enDspMasterWaiting = WIM__enDspFavourite; /* assign new master waiting */

         if(/* DspMasterWaiting wasnt displayed before */
            WIM__mboGetDisplayedFlag(WIM__enDspMasterWaiting) == False)
         {
            /*** trigger RequestDisplay state handler. */
            WIM__vRequestDisplayStateHdl(WIM__nNewWarningRequested);
         }
         /* Generate warning display request event */
         WIM__vOnEvent_GC(WIM__enDspMasterWaiting, WIM__nDspRequest);

         /* then request the Warning should be displayed */
         WIM__vDspWarningRequest(WIM__u32CreateMsgDataReqWarn(WIM__enDspMasterWaiting));
      }
   }
   else if (/* no more message to display - release master if present */
            WIM__enDspMaster != WIM_nenInvalidMsg
            /* Display Master was not released */
            && WIM__enDspMasterWaiting != WIM_nenInvalidMsg)
   {
      WIM__enDspMasterWaiting = WIM_nenInvalidMsg; /* mark masterwaiting as invalid  */

      /*** First  trigger RequestDisplay state handler. */
      WIM__vRequestDisplayStateHdl(WIM__nNoWarningRequested);
      /*** then release the Warning from display */
      WIM__vDspWarningRelease();

      /* start delay timers for "kurzzeitige Ruhe"
         It is required that - if the last display message has been freed -
         a new message is delayed for
         - 500ms (if "Urgent") or for
         - 5000ms (if not "Urgent") */
      if (/* if first schedule after "RestoreWarnings", don't insert delay! */
          WIM__boFirstScheduleRun == False)
      {
         /* start delay timers */
         WIM__vStartTimer(WIM__nTimerDspDelModal, WIM__enDspMaster);
         WIM__vStartTimer(WIM__nTimerDspDelNormal, WIM__enDspMaster);
      }
   }
   else
   {
      /* no active display message */
   }

   /* TODO ????? */
   /*** flag handling */
   if (/* Scheduler is running? */
       WIM__boSchedulePrioCheck && WIM__boFirstScheduleRun)
   {
      /* ResetFlag: no delay timers at first schedule after "RestoreWarnings" */
      WIM__boFirstScheduleRun = False;
   }
   
}


/**
*   Check all relevant information for Display Requests and
*   Request/Release the Display.
*
*   @return  void
*   @param   WIM__tenDspReqChangeEvents   Trigger event for new check
*   @author  L.Gruenewald, Schleissheimer GmbH
*/
void WIM__vRequestDisplayStateHdl(WIM__tenDspReqChangeEvents enEvent)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   static bool boDspRequested;
   static bool boDspLagTime120secOn;
   DSM_tunDispRelData unDisplayRelData;
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   
   unDisplayRelData.u32DispRelData= 0;
   unDisplayRelData.stClientData.u16ClientId  = enClientWIM;

   if(enEvent == WIM__nInitRequestDsp)
   {
      /* Init the state handler for Display requests */
      boDspRequested = False;
      boDspLagTime120secOn = False;
   }
   else
   {
      /* Do the state handler transitions */

      if(boDspRequested == True)
      {
         /****************************************************/
         /* Do the Transitions from State "DisplayRequested" */
         /****************************************************/
         switch(enEvent)
         {
            case WIM__nNoKeepActRegistered:
               /*******/
               /* The last warning with "KeepActive" was canceled/deleted */
               /*******/
               if(/* Kl15ROff */
                  CST_boGetStatus(CST_nenStatusKl15R) == False )
               {
                  if(/* and no DspMaster */
                     WIM__enDspMaster == WIM_nenInvalidMsg )
                  {
                     /* Release DspRequest Lag 30sec */
                     unDisplayRelData.stClientData.u16TimeLag = WIM__nDspReleaseLagDefault;
                     WIM__vReleaseDisplay(unDisplayRelData.u32DispRelData);
                     /* State change */
                     boDspRequested = False;
                  }
                  else /* and DspMaster */
                  {
                     /* Release DspRequest Lag 120sec */
                     unDisplayRelData.stClientData.u16TimeLag = WIM__nDspReleaseLagLong;
                     WIM__vReleaseDisplayProtected(unDisplayRelData.u32DispRelData);
                     /* State change */
                     boDspRequested = False;
                     boDspLagTime120secOn = True;
                  }
               }
               break;
            case WIM__nNoWarningRequested:
               /*******/
               /* The last warning was removed from Display */
               /*******/
               if(/* Kl15ROff*/
                     CST_boGetStatus(CST_nenStatusKl15R) == False
                  /* No more warnings with "KeepActive" registered */
                  && WIM__u8KeepActiveIcRegisteredCount == 0)
               {
                  /* Release DspRequest Lag 30sec */
                  unDisplayRelData.stClientData.u16TimeLag = WIM__nDspReleaseLagDefault;
                  WIM__vReleaseDisplay(unDisplayRelData.u32DispRelData);
                  /* State change */
                  boDspRequested = False;
               }
               break;
            case WIM__nKl15rOffEdge:
               /*******/
               /* The car state Kl15R switched to Off */
               /*******/
               if(/* No more warnings with "KeepActive" registered */
                  WIM__u8KeepActiveIcRegisteredCount == 0 )
               {
                  if(/* and no DspMaster */
                     WIM__enDspMaster == WIM_nenInvalidMsg )
                  {
                     /* Release DspRequest Lag 0sec */
                     unDisplayRelData.stClientData.u16TimeLag = WIM__nDspReleaseNoLag;
                     WIM__vReleaseDisplay(unDisplayRelData.u32DispRelData);
                     /* State change */
                     boDspRequested = False;
                  }
                  else /* and DspMaster */
                  {
                     /* Release DspRequest Lag 120sec */
                     unDisplayRelData.stClientData.u16TimeLag = WIM__nDspReleaseLagLong;
                     WIM__vReleaseDisplayProtected(unDisplayRelData.u32DispRelData);
                     /* State change */
                     boDspRequested = False;
                     boDspLagTime120secOn = True;
                  }
               }
               break;
            case WIM__nWakeUpRegistered:
               /* fall through*/
            case WIM__nKeepActRegistered:
               /* fall through*/
            case WIM__nNewWarningRequested:
               /* no Transitions with this Events */
               break;
            default:
               /* Error! */
               WIM__vRaiseException(WIM_nErrConfig);
               break;
         }
      }
      else
      {
         /****************************************************/
         /* Do the Transitions from State "NoDisplayRequested*/
         /****************************************************/

         switch(enEvent)
         {
            case WIM__nNoWarningRequested:
               /*******/
               /* The last warning was removed from Display */
               /*******/
               if(/* Kl15ROff*/
                  CST_boGetStatus(CST_nenStatusKl15R) == False)
               {
                  if (boDspLagTime120secOn)
                  {
                     /* Release DspRequest Lag 30sec */
                     unDisplayRelData.stClientData.u16TimeLag = WIM__nDspReleaseLagDefault;
                     WIM__vReleaseDisplay(unDisplayRelData.u32DispRelData);
                     /* no state change! */
                     boDspLagTime120secOn = False;
                  }
               }
               else /* Kl15ROn */
               {
                  /* Release DspRequest Lag 0sec */
                  unDisplayRelData.stClientData.u16TimeLag = WIM__nDspReleaseNoLag;
                  WIM__vReleaseDisplay(unDisplayRelData.u32DispRelData);
                  /* no state change! */
               }
               break;
            case WIM__nWakeUpRegistered:
               /*******/
               /* The first warning with "WakeUp" was registered */
               /*******/
               if(/* is the Display off yet? */
                  WIM__boDisplayState == Off)
               {
                  /* Request the Display */
                  WIM__vRequestDisplay();
                  /* Release DspRequest Lag 30sec */
                  unDisplayRelData.stClientData.u16TimeLag = WIM__nDspReleaseLagDefault;
                  WIM__vReleaseDisplay(unDisplayRelData.u32DispRelData);
                  /* no state change! */
               }
               break;
            case WIM__nNewWarningRequested:
               /*******/
               /* A warning was not in display before was requested */
               /*******/
               if(/* Kl15ROn */
                  CST_boGetStatus(CST_nenStatusKl15R) == True)
               {
                  /* Request the Display */
                  WIM__vRequestDisplay();
                  /* State change */
                  boDspRequested = True;
               }
               else /* Kl15ROff */
               {
                  if (WIM__mboWakeupIc(WIM__enGetDisplayMasterWaiting()))
                  {
                     /* Request the Display */
                     WIM__vRequestDisplay();
                     /* DspMaster && WakeIC */
                     /* Release DspRequest with Lag 120sec */
                     unDisplayRelData.stClientData.u16TimeLag = WIM__nDspReleaseLagLong;
                     WIM__vReleaseDisplayProtected(unDisplayRelData.u32DispRelData);
                     /* no state change! */
                     /* Lag time 120sec is turned on */
                     boDspLagTime120secOn = True;
                  }
               }
               break;
            case WIM__nKeepActRegistered:
               /*******/
               /* The first warning with "KeepActive" was registered */
               /*******/
               /* Request the Display */
               WIM__vRequestDisplay();
               /* State change */
               boDspRequested = True;
               break;
            case WIM__nNoKeepActRegistered:
               /*******/
               /* The last warning with "KeepActive" was canceled/deleted */
               /*******/
               /* Must not occour in this state */
               WIM__vRaiseException(WIM_nErrDspReq);
               break;
            case WIM__nKl15rOffEdge:
               /* no Transitions with this Events */
               break;
            default:
               /* Error! */
               WIM__vRaiseException(WIM_nErrConfig);
               break;
         }/* switch */
      }/* Do the Transitions from State "NoDisplayRequested*/
   }/* Do the state handler transitions */
   
}

/**
* This is the scheduler only for slacks.
*   @return  void
*   @param   none
*   @author  A.Wagner, Schleissheimer GmbH
*/
void WIM__vScheduleSlack(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   /* start message in search loop                    */
   WIM_tenMsg enSearchStart;
   /* message where dsp favourite search ends         */
   WIM_tenMsg enSearchEndDsp;
   /* search loop variable, current message           */
   WIM_tenMsg enCurMsg;
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   

   if (     /* slack scheduler triggered? */
      (True == WIM__boDoScheduleSlack)
      /* and slack scheduling allowed */
      && (True == WIM__boSchedulePrioCheck)
      )
   {
      /* preset favourites as invalid */
      WIM__enDspSlackFavourite = WIM_nenInvalidMsg;

      /* search always starts at the highest priority level */
      enSearchStart = WIM__mGetHighestPrioMessage;
      /* search all levels */
      enSearchEndDsp = WIM__mGetLowestPrioMessage;

      /* --- Search for DspFavourite ---- */
      for( enCurMsg = enSearchStart; enCurMsg <= enSearchEndDsp; enCurMsg++)
      {
          if (     /* Is message a slack */
              enCurMsg != WIM_nenInvalidMsg
              && WIM__menGetSlackMsgType(enCurMsg)
              /* Is a display request set for this slack message */
              && WIM__u8GetDspQualifier(enCurMsg) != WIM__nNoRequest)
          {
              if (     /* message is already in Display */
                  (enCurMsg == WIM__enDspSlackMasterWaiting)
                  || (enCurMsg == WIM__enDspSlackMaster))
              {
                  /* do nothing */
              }
            else /* message is not in display */
            {
               if ((WIM__enDspSlackFavourite == WIM_nenInvalidMsg) && !WIM_boSlacksBlocked())
               {
                  /* no favourite found -> select this slack message as new favourite */
                  WIM__enDspSlackFavourite = enCurMsg;
               }
               else
               {
                  /* already found a higher prio favourite or SLACKs are blocked -> request of all other messages will be deleted */
                  WIM__vSetDspQualifier(enCurMsg, WIM__nNoRequest);
               }
            }
         }
      }

      /* In case there was no new message found -> check for a displayed message */
      if(WIM__enDspSlackFavourite == WIM_nenInvalidMsg)
      {
         /* no new favourite was found */
         if(      /* There is a master waiting */
                  (WIM__enDspSlackMasterWaiting != WIM_nenInvalidMsg)
                  /* and it is still requested */
               && (WIM__u8GetDspQualifier(WIM__enDspSlackMasterWaiting) != WIM__nNoRequest))
         {
            /* keep kurrent display message */
            WIM__enDspSlackFavourite = WIM__enDspSlackMasterWaiting;
         }
         else if(    /* There is a master */    
                     (WIM__enDspSlackMaster != WIM_nenInvalidMsg)
                     /* and it is still requested */
                  && (WIM__u8GetDspQualifier(WIM__enDspSlackMaster) != WIM__nNoRequest))
         {
            /* keep kurrent display message */
            WIM__enDspSlackFavourite = WIM__enDspSlackMaster;
         }
      }

      /* scheduling done! */
      WIM__boDoScheduleSlack = False;
   }
   
}

void WIM__vScheduleRessourceReqSlack(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   
   if (/* if scheduler is disabled, make sure that we stop safely display or
          acoustic output */
       False == WIM__boScheduleResources
       /* or there have been block marks for SLAck's */
       || WIM_boSlacksBlocked())
   {
      /* set favorite to invalid, this will cause release of master */
      WIM__enDspSlackFavourite = WIM_nenInvalidMsg;
   }

   /*-------------------------------------------------------------------------
     DISPLAY
     - check if synchronisation conditions are fullfilled (if existing)
     - replace/set master if new favourite found (or favourite synchronized)
     - release master if no favourite found
     - do the display request for the current master
     -------------------------------------------------------------------------*/
   if (/* did we found a favourite? */
       WIM__enDspSlackFavourite != WIM_nenInvalidMsg)
   {
      if (     /* Favourite is not master */
               (WIM__enDspSlackFavourite != WIM__enDspSlackMaster)
               /* and Favourite is not masterwaiting */
            && (WIM__enDspSlackFavourite != WIM__enDspSlackMasterWaiting)
               /* only request a Display warning when Display is On */          
            && (WIM__boDisplayState == On))
      {
         /* Generate warning display request event */
         WIM__vOnEvent_GC(WIM__enDspSlackFavourite, WIM__nDspRequest);
         /* then request the Warning should be displayed */
         WIM__vDspSlackRequest(WIM__u32CreateMsgDataReqWarn(WIM__enDspSlackFavourite));
         /* Update DspSlackMasterWaiting */
         WIM__enDspSlackMasterWaiting = WIM__enDspSlackFavourite;
      }
      else if (     /* Fix for KL15 OFF->ON / HMI unsynchronously */
                     /* Warning is not in NormalPhase but is in display */
                    (WIM__enDspSlackFavourite == WIM__enDspSlackMaster)
                 && (WIM__mu8GetDspState(WIM__enDspSlackMaster) != WIM__nNormalPhase)
                    /* only request a Display warning when Display is On */          
                 && (WIM__boDisplayState == On))
      {
         /* set warning state on normal phase */
         WIM__mSetDspState(WIM__enDspSlackFavourite, WIM__nNormalPhase);
         /* start display timers */
         WIM__vStartTimer(WIM__nTimerDspNormalSlack, (WIM__txCorrTag)WIM__enDspSlackFavourite);
      }
   }
   else if (/* no more message to display - release master if present */
            WIM__enDspSlackMaster != WIM_nenInvalidMsg)
   {
      WIM__enDspSlackMasterWaiting = WIM_nenInvalidMsg; /* mark masterwaiting as invalid  */

      /*** then release the Warning from display */
      WIM__vDspSlackRelease();
   }
   
}

static bool WIM__boSbwAcousticsHilId(uint32 u32HilId)
{
   return u32HilId == WIM__nRearSeatBeltHilId || u32HilId == WIM__nBeltWarningHilId || u32HilId == WIM__nPreBeltWarningHilId
      ? True
      : False;
}

/**
 * \brief Check if Slacks are blocked or not
 * \return True if Slacks are blocked, false - otherwise
 */
static bool WIM_boSlacksBlocked(void)
{
   bool boSlacksBlocked = WIM__u8SlackDisplayBlocked > 0
      ? True
      : False;
   
   return boSlacksBlocked;
}