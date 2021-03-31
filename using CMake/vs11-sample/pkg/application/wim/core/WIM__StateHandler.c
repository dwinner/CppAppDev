/******************************************************************************
*=====================      Copyright by Continental AG      ==================
*******************************************************************************
* Titel        : WIM__StateHandler.c
*
* Description  : Message State Handler class. 
*                Contains a state machine reacting on internal and external 
*                events. The state machine is individual for the different
*                types of messages. Events are passed to a central interface 
*                function which dispatches the event to the message type.
*                Reaction on events can be state changes and actions that will
*                be initialized if the appropriate conditions are fulfilled.
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
* Archive: $Log: WIM__StateHandler.c  $
* Archive: Revision 1.1.2.15 2014/08/23 16:19:35CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 42288 : WIM: Correct customer findings regarding non-urgent handling message and acoustic cancel - WDMs 341, 417
* Archive: Revision 1.1.2.14 2014/07/29 18:35:57CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 41681 : WIM: Prevent sporadic flicker of GC controlled complex warnings after Kl15ACC
* Archive: Revision 1.1.2.13 2014/07/18 16:08:55CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 41550 : WIM: Robustness measures for SLACK state handling and scheduling
* Archive: Revision 1.1.2.12 2014/06/06 18:58:01CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 40493 : WIM: Correct acoustic behaviour after activation of a warning by diagnosis and Kl15 Rese
* Archive: Revision 1.1.2.11 2014/06/06 17:06:14CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 38112 : WIM: Introduction of "Singleline Acknowledgements" - MR47
* Archive: DC MR 40764 : WIM: Changes after code review for single line acknowledgements -  ORM 7144
* Archive: DC MR 40531 : Single line acknowledgement should cancel a running startup animation
* Archive: Revision 1.1.2.10 2014/03/21 13:03:25CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 39524 : WIM: Correct interval acoustic handling and HIL feedback
* Archive: DC MR 39163 : WIM: Overcome illegal memory access and correction of HMI acoustics notification
* Archive: DC MR 40021 : WIM: Sound of FCW warning is not retriggered after reset
* Archive: Revision 1.1.2.9 2014/01/21 14:13:44CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 37965 : WIM: Correction of "Keep awake" handling for warnings
* Archive: Revision 1.1.2.8 2014/01/03 10:32:27CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 36462 : WIM: Implement new scheduling and state handling for acoustic part
* Archive: Revision 1.1.2.7 2013/11/22 16:59:31CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 36779 : BR213EL, E006, Implementation of new WarnDB
* Archive: DC MR 36462 : WIM: Implement new scheduling and state handling for acoustic part
* Archive: Revision 1.1.2.6 2013/11/18 16:42:16CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 36361 : BR213: Optimize activation time for acoustic warnings
* Archive: Revision 1.1.2.5 2013/09/17 13:25:15CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 34944: WIM: Persistent storage of warn states for wake-IC warnings
* Archive: DC MR 34942: BR213, WIM: Acoustic of door warning shall not be retriggered by another door
* Archive: Revision 1.1.2.4 2013/06/04 15:48:12CEST Harms-EXT, Daniel (uidw1026) 
* Archive: DC MR 33454: IC213EL: Flickering effect when activating distronic warning (SV_13_3062)
* Archive: Revision 1.1.2.3 2013/05/17 16:10:17CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 33413: BR213EL/GC, E004, WIM: Takeover of the latest changes from BR205
* Archive: Revision 1.1.2.2 2013/01/31 18:28:32CET Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
* Archive: Revision 1.15 2013/01/31 18:28:32CET Immel-EXT, Marc (uid37561) 
* Archive: DC MR 31158: W222IC-GC TSA: Prevent popup warning from being displayed when FAS menu is active (ÄLP2802)
* Archive: DC MR 30528: W222, E011/GC, WIM: complex display of warnung ConvertibleTop 0x200527 - ÄLP2745
* Archive: Revision 1.14 2013/01/21 12:12:46CET Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 30335: BR205/E011/GC: DIM: Update SwillLvl turn-on condition (Exlude Warning without wake-reason)
* Archive: DC MR 31127: Change allocator of CIA memory pool from flexible to static
* Archive: DC MR 31152: BR205, E011/GC, WIM: Waking up the display is not possible if another wake IC warning is active
* Archive: DC MR 31154: BR205 E011/GC, WIM: Wrong transition in case of display cancel event
* Archive: Revision 1.13 2013/01/12 16:37:35CET Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 31032: BR205: Overtake HMI components for flashing (HMI synchronisation) from IC222
* Archive: DC MR 30978: BR205, E011/GC, WIM: Remove exception raising if HMI reports a canceled warning
* Archive: DC MR 30976: BR205, E011/GC, WIM: Warning disappears before display is off
* Archive: DC MR 25690: W205IC-GC TSA: Prevent popup warning from being displayed when FAS menu is active (ÄLP2802)
* Archive: Revision 1.12 2013/01/10 18:42:43CET Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 30975: BR222, E011/GC, WIM: Warning disappears before display is off
* Archive: DC MR 30972: BR222, E011/GC, WIM: Remove exception raising if HMI reports a canceled warning
* Archive: Revision 1.11 2012/11/01 17:24:25CET Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 30267: BR222 E010, WIM: Acoustic problems found in customer pre tests of E7.6.pre30 frame - WDM56897
* Archive: DC MR 30242: E010: WIM, Correction of display state detection/ behaviour of wake-up warnings
* Archive: DC MR 26090: W222, E010/GC, WIM: Flashing dashes for warnings [WDM53127]
* Archive: Revision 1.10 2012/05/18 10:44:17CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: Member moved from WIM__StateHandler.c in project /id/dag_PF3/sw/pkg/wim/core/project.pj[dag_PF3.sw.pkg.wim_COMMON_IC222GC_VarP] to WIM__StateHandler.c in project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj[dag_PF3.sw.pkg.wim_COMMON_GenPF3GC_VarX].
* Archive: Revision 1.9 2012/05/10 15:50:06CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 25842: BR222/E7.2/GC: WIM: HIL Fix Loudness Feedback (WDM31515)
* Archive: DC MR 25916: W222, E007/GC, WIM: Changes on display-block by sound only warning - WDM35459
* Archive: DC MR 25913: W222, E007/AC, HIL: Mapping of WIM sound types
* Archive: DC MR 25704: W222, E007/GC, WIM: Fix for corrupted sound - WDM35438
* Archive: Revision 1.8 2012/05/04 16:26:14CEST 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: DC MR 25131: W222, E007/GC, WIM: Implementation of exceptions
* Archive: DC MR 25823: BR222 E7.2: Implementation of L3 delivery (XML-Files)
* Archive: DC MR 21251: W222, E007/GC, WIM: ComplexFunction of Warning 0x2001A6 Kurvenlicht
* Archive: DC MR 25710: W222, E007/GC, WIM: Inactive handling messages show up after 600ms - WDM35020
* Archive: DC MR 25126: W222, E007/GC, WIM: Behaviour of sync acoustics - WDM35391, 35418, 35392, 35389, 35396, 35421
* Archive: Revision 1.6 2012/04/05 14:28:29CEST 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: DC MR 25096: W222, E007/GC, WIM: Cancelled warning stays in display - WDM31758, WDM31856
* Archive: Revision 1.5 2012/04/04 13:47:54CEST 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: DC MR 24870: W222, E007/GC, WIM: Implement changes from Review ORM2907
* Archive: DC MR 25007: W222, E007/GC, WIM: Displacement of handling messages - WDM20280
* Archive: DC MR 25041: Do not specify message propagation in message description files
* Archive: DC MR 25095: W222, E007/GC, WIM: Improvement of Timer accuracy for display role - WDM 25704
* Archive: DC MR 25034: Reduction of lag times in case of vehicle locked
* Archive: DC MR 25393: W222, E007/GC, WIM: No cancel of interval acoustic - WDM31269, ÄLP2895
* Archive: Revision 1.4 2012/02/21 13:05:26CET 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: DC MR 24333: W222, E007/GC, WIM: HIL output for requested sound not working
* Archive: DC MR 24043: Move tube request from WIM to WarningStandard.xml
* Archive: DC MR 23682: W222, E007/GC, WIM: Acousic only messsage does not block display WDM21148
* Archive: DC MR 24086: W222, E007/GC, WIM: Short rest after warning display is not always 5 seconds
* Archive: DC MR 24332: W222, E007/GC, WIM: Warnings can not be acknowledged with Nview active
* Archive: Revision 1.3 2012/01/13 11:43:38CET 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: DC MR 24093: W222, E007/GC, WIM: Acoustic warning does not block display - WDM20499
* Archive: DC MR 23683: W222, E007/GC, WIM: Sync acoustic is cancelled by async acoustic WDM21143
* Archive: DC MR 24088: W222, E007/GC, WIM: Warning blocks display WDM22837, WDM23219
* 
*    Rev 1.15   Nov 07 2011 08:11:16   SCHL_Dirk.Gottwalles
* DC MR 23228: W222, E007/GC, WIM: Urgent handling message is not treated urgent
* DC MR 23226: W222, E007/GC, WIM: Change from async acoustic to sync acoustic WDM20336
* DC MR 23230: W222, E007/GC, WIM: Async acoustic blocks urgent display message WDM20376
* DC MR 22977: Integration of ARTEMMIS 3.2.1
* 
*    Rev 1.14   Sep 23 2011 09:16:14   SCHL_Dirk.Gottwalles
* DC MR 22733: W222, E006/GC, WIM: Implementation of complex key handling for warnings
* 
*    Rev 1.13   Sep 20 2011 10:12:30   SCHL_Dirk.Gottwalles
* DC MR 22971: W205, E006/GC, WIM: Remove of not supported HMI messages
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
*    Rev 1.9   Apr 26 2011 09:48:54   SCHL_Dirk.Gottwalles
* DC MR 21809: B222/GC: WIM: Not automatic acknowledged message is acknowledged
* DC MR 21658: E004/AC, WIM: Lower priority activation feedback is is displayed bevor higher prior warning
* DC MR 21808: BR222/AC, WIM: Mapping of config "Luftfeder" wrong
* DC MR 21258: WIM: Display lag time not reset on KL15r Off
* 
*    Rev 1.8   Mar 22 2011 16:07:26   SCHL_Dirk.Gottwalles
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
*    Rev 1.7   Dec 17 2010 13:54:30   SCHL_Lars.Gruenewald
* DC MR20897 WIM: Implementation of menu FaultMemory
* 
*    Rev 1.6   Dec 03 2010 15:57:02   SCHL_Lars.Gruenewald
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
*    Rev 1.5   Nov 19 2010 16:04:14   SCHL_Dirk.Gottwalles
* DC MR21122 BR222: WIM reaction at wakeupreq.
* DC MR21302 BR222/AC: Optimierung Aufruf Checkfunktion WIM
* DC MR20423 W222: WIM new acoustics requirements
* DC MR21177 Implementation of first WarnDB for E003
* DC MR21336 WIM: Using Enumeration Symbols for State/Widget Mapping
* 
*    Rev 1.4   Sep 03 2010 12:24:42   SCHL_Lars.Gruenewald
* DC MR20924 WIM: Wakeup Warnings not allways wakes up the Display
* DC MR20460 W222: activation of KOMBIINTERN warning 0x200068 in E002 sample
* DC MR20681 E002/AC, Startup MR WMN-AC
* 
*    Rev 1.3   Aug 27 2010 18:49:54   SCHL_Lars.Gruenewald
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
*    Rev 1.2   Jul 09 2010 18:01:48   SCHL_Lars.Gruenewald
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
*    Rev 1.0   Jun 11 2010 14:07:48   SCHL_Thomas.Godemann
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
#include <string.h>

/* Own headerfiles */
#include "WIM__DataInt.h"
#include "WIM_c1.h"
#include "WIM__StateHandler.h"
#include "WIM__Scheduler.h"
#include "WIM__StateHandlerDisplayHandlerFunctions.h"
#include "WIM__StateAccessHelpers.h"
#include "WIM__StateHandlerAcousticStateMatrix.h"
#include "WIM__StateHandlerDisplayStateMatrix.h"
#include "WIM__StateHandlerSlackStateMatrix.h"
#include "WIM__MenuFaultMemory.h"               /* MenuFaultMemory            */

/******************************************************************************
* GLOBAL DEFINITIONS
*******************************************************************************/

/**
 * Counter for acoustic retrigger
 */
uint8 WIM__u8CounterStartsAcousticRetrigger = 0x0;

/**
* Memory for current display state
*/
bool WIM__boDisplayState;

/**
* Counter for Registered Warnings with KeepActive Attribute (see Attribute WakeIc)
* @range  uint8
* @values 0...255
*/
uint8 WIM__u8KeepActiveIcRegisteredCount;

/******************************************************************************
* FILE LOCAL FUNCTION PROTOTYPES
*******************************************************************************/
static void WIM__vNotifyStateChange(WIM_tenMsg enMsg, 
                                    WIM__tenEventIntern enEvt, 
                                    bool boDisplayedFlag);

/******************************************************************************
* FILE LOCAL DEFINITIONS
*******************************************************************************/
/**
* Identifier of a handling message waiting to be displayed. If during the 
* period of validity time the message not gets the display, it will be cleared.
* The same thing happens, if another handling message becomes active while
* we have a waiting handling message.
*/
WIM_tenMsg WIM__enWaitingHdlMsg;

/**
* CheckComplex container
*/
static const WIM_tpvCheckWarnCb WIM__apvCheckComplexContainer[] =
{
   /* content defined in configuration */
   WIM__nCheckComplexContainerContent
   WIM__nLastCntEntry /* must always be the last entry */
};

/**
* FastActivation sounds
*/
static const WIM_tenMsg WIM__aenFastActivationSound[] =
{  
   /* content defined in configuration */
   WIM__nFastActivationSoundList,
   WIM_nenInvalidMsg /* must always be the last entry */
};

/******************************************************************************
* PACKAGE GLOBAL FUNCTION DEFINITIONS
*******************************************************************************/
/**
* Message in Fast Activation List or not
*   @return  True, if message is in container
*   @param   const WIM_tenMsg
*   @author  A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boFastActivationSound(const WIM_tenMsg enMsg)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint8 u8Index = 0;    /* index variable                                    */
   bool boFound = False; /* search result                                     */
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   while (/* loop through all warnings in container */
             WIM__aenFastActivationSound[u8Index] != WIM_nenInvalidMsg
          && boFound == False)
   {
      if(/* is message in list ? */
         WIM__aenFastActivationSound[u8Index] == enMsg)
      {
         boFound = True;
      }
      u8Index++;
   }
   return boFound;
}

/**
* Returns the current display qualifier for the message
*   @return  uint8 - Display qualifier
*   @param   const WIM_tenMsg - Display message
*   @author  D. Gottwalles, Schleissheimer GmbH 
*/
uint8 WIM__u8GetDspQualifier(const WIM_tenMsg enMsg)
{
   if(enMsg < WIM_nenNoOfMessages)
   {
      return (WIM__astMsgStates[(enMsg)].biQualifier & 0x0F);
   }
   else
   {
      /* raise exception */
      WIM__vRaiseException(WIM_nWrongParameter);
      return 0;
   }
}

/**
* For HMI its only allowed to send the Feedback if the displayed warning changed.
*   @return  void
*   @param   const WIM_tenMsg - Message whichs display qualifier shall be modified
*   @param   const WIM__tenDspQualifier - Display qulifier to add
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
void WIM__vSetDspQualifier(const WIM_tenMsg enMsg, const WIM__tenDspQualifier enQualifier)
{
   if(enMsg < WIM_nenNoOfMessages)
   {
      if(enQualifier != WIM__nQualUrgt &&
         enQualifier != WIM__nQualHdl)
      {
         WIM__astMsgStates[(enMsg)].biQualifier &= 0xF0;
      }
      
      WIM__astMsgStates[(enMsg)].biQualifier |= (((uint8)enQualifier) & 0x0F);
   }
   else
   {
      /* raise exception */
      WIM__vRaiseException(WIM_nWrongParameter);
   }
}

/**
* Sets the acoustic qualifier for the message
* A request or relase leads to a full reset of all acoustic qualifiers
*   @return  none
*   @param   const WIM_tenMsg - Display message
*            const WIM__tenDspQualifier - acoustic qualifier
*   @author  A.Wagner, Schleissheimer GmbH 
*/
void WIM__vSetAcuQualifier(const WIM_tenMsg enMsg, const WIM__tenAcuQualifier enQualifier)
{
   if(enMsg < WIM_nenNoOfMessages)
   {
      if(enQualifier == WIM__nAcuReleased ||
         enQualifier == WIM__nAcuRequested)
      {
         WIM__astMsgStates[(enMsg)].biQualifier &= 0x0F;
      }
      WIM__astMsgStates[(enMsg)].biQualifier |= (((enQualifier) << 4) & 0xF0);
   }
   else
   {
      /* raise exception */
      WIM__vRaiseException(WIM_nWrongParameter);
   }
}

/**
* clear the acoustic qualifier for the message
*   @return  none
*   @param   const WIM_tenMsg - Display message
*            const WIM__tenDspQualifier - acoustic qualifier
*   @author  A.Wagner, Schleissheimer GmbH 
*/
void WIM__vDelAcuQualifier(const WIM_tenMsg enMsg, const WIM__tenAcuQualifier enQualifier)
{
   if(enMsg < WIM_nenNoOfMessages)
   {
      WIM__astMsgStates[(enMsg)].biQualifier &= (~((enQualifier) << 4) );
   }
   else
   {
      /* raise exception */
      WIM__vRaiseException(WIM_nWrongParameter);
   }
}

/**
* Hmi send Feedback with new Warning in Display. Forward it into StateHandler!
* For HMI its only allowed to send the Feedback if the displayed warning changed.
*   @return  void
*   @param   EVHD_tenReceiveEvent enWarnResponseEvent
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
void WIM__vDoHmiFeedback(EVHD_tenReceiveEvent enWarnResponseEvent)
{ 
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   /* Struct with former and know displayed WarnId (Msg-Enum) */
   /* local copy of DpoolData */
   WIM_tstHmiFeedback stHmiFeedback;
   WIM_tstHmiFeedback stHmiFeedbackSlack;
   uint16 u16CanceledMsg;
   uint16 u16CanceledSlack;
   uint16 u16SupprMsg;

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   switch(enWarnResponseEvent)
   {
   case EV_DPOOL_Always_WIM_u16SuppressedWarning_WIM_vDoHmiEvents:
      {
         /* Receive DpoolData and Check validation */
         if(E_DATA_OK == DPOOL_enGetPoolData(DPOOL_nDataWIM_u16SuppressedWarning, &u16SupprMsg))
         {
            if((WIM_tenMsg)u16SupprMsg != WIM_nenInvalidMsg)
            {
               if(WIM__mu8GetDspState((WIM_tenMsg)u16SupprMsg) == WIM__nWaitForDsp)
               {
                  /* Generate suppress event for valid messages */
                  WIM__vOnEvent_GC((WIM_tenMsg)u16SupprMsg, WIM__nDspSuppr);
               }
            }
         }
      } break;
   case EV_DPOOL_Always_WIM_u16CanceledWarning_WIM_vDoHmiEvents:
      {
         /* Receive DpoolData and Check validation */
         if(E_DATA_OK == DPOOL_enGetPoolData(DPOOL_nDataWIM_u16CanceledWarning, &u16CanceledMsg))
         {
            if((WIM_tenMsg)u16CanceledMsg != WIM_nenInvalidMsg)
            {
               if(WIM__mu8GetDspState((WIM_tenMsg)u16CanceledMsg) == WIM__nWaitForDsp)
               {
                  /* Generate cancel event for valid messages */
                  WIM__vOnEvent_GC((WIM_tenMsg)u16CanceledMsg, WIM__nDspCancel);
               }
            }
         }

      } break;
   case EV_DPOOL_Always_WIM_stHmiFeedback_WIM_vDoHmiEvents:
      {
         if (/* Receive DpoolData and Check validation */
             E_DATA_OK == DPOOL_enGetPoolData(DPOOL_nDataWIM_stHmiFeedback, &stHmiFeedback))
         {

            if((WIM_tenMsg)stHmiFeedback.u16WarningIDNew != WIM__enDspMaster)
            {
               /* Request the displayed warning again. This is done to overwrite
                * older requests that have been sent while this feedback was pending.
                */
               WIM__enDspMasterWaiting = (WIM_tenMsg)stHmiFeedback.u16WarningIDNew;
               WIM__vDspWarningRequest(WIM__u32CreateMsgDataReqWarn((WIM_tenMsg)stHmiFeedback.u16WarningIDNew));
         
               /* Gernerate Display cancel event for the old warning */
               if((WIM_tenMsg)stHmiFeedback.u16WarningIDOld != WIM_nenInvalidMsg &&
                  stHmiFeedback.u16WarningIDOld != stHmiFeedback.u16WarningIDNew)
               {
                  WIM__vOnEvent_GC((WIM_tenMsg)stHmiFeedback.u16WarningIDOld, WIM__nDspCancel);
               }

               /* The given HMI-Feedback is the new Display Master. */
               WIM__enDspMaster = (WIM_tenMsg)stHmiFeedback.u16WarningIDNew;
               /* Handle complex drawing */
               WIM__vHandleComplexDraw(WIM__enDspMaster);
               if(/* Only generate a state handler event, when new Master is not invalid */
                  WIM__enDspMaster != WIM_nenInvalidMsg)
               {
                  /* generate state handler event 'Display Assign' */
                  WIM__vOnEvent_GC(WIM__enDspMaster, WIM__nDspAssign);
               }

               /* run display change container to inform about new master  */  
               WIM__vDspChangeContainer_GC(WIM__u32GetHilId(WIM__enDspMaster));
            }
            else
            {
               if(WIM__enDspMaster != WIM_nenInvalidMsg &&
                  stHmiFeedback.u16WarningIDNew != stHmiFeedback.u16WarningIDOld)
               {
                  //WIM__vRaiseException(WIM_nSynchHmi);
                  /* On architecture switch this state occures with u16WarningIDOld == WIM_nenInvalidMsg  
                     This behaviour is OK. We ignore it here.*/ 
               }
            }
         }
      } break;
      case EV_DPOOL_Always_WIM_stHmiFeedbackSlack_WIM_vDoHmiEvents:
      {
         if (/* Receive DpoolData and Check validation */
             E_DATA_OK == DPOOL_enGetPoolData(DPOOL_nDataWIM_stHmiFeedbackSlack, &stHmiFeedbackSlack))
         {
            if((WIM_tenMsg)stHmiFeedbackSlack.u16WarningIDNew != WIM__enDspSlackMaster)
            {
               /* Gernerate Display cancel event for the old slack */
               if((WIM_tenMsg)stHmiFeedbackSlack.u16WarningIDOld != WIM_nenInvalidMsg &&
                  stHmiFeedbackSlack.u16WarningIDOld != stHmiFeedbackSlack.u16WarningIDNew)
               {
                  WIM__vOnEvent_GC((WIM_tenMsg)stHmiFeedbackSlack.u16WarningIDOld, WIM__nDspCancel);
               }

               /* Set DspSlackMaster */
               WIM__enDspSlackMaster = (WIM_tenMsg)stHmiFeedbackSlack.u16WarningIDNew;

               /* clear stored (waiting) single line message */
               WIM__enDspSlackMasterWaiting = WIM_nenInvalidMsg;

               if(/* Only generate a state handler event, when new Master is not invalid */
                  WIM__enDspSlackMaster != WIM_nenInvalidMsg)
               {
                  /* generate state handler event 'Display Assign' */
                  WIM__vOnEvent_GC(WIM__enDspSlackMaster, WIM__nDspAssign);
               }
               
               /* Handle complex drawing */
               /*WIM__vHandleComplexSlackDraw(WIM__enDspSlackMaster);*/
            }
            else
            {
               if(WIM__enDspSlackMaster != WIM_nenInvalidMsg &&
                  stHmiFeedbackSlack.u16WarningIDNew != stHmiFeedbackSlack.u16WarningIDOld)
               {
                  //WIM__vRaiseException(WIM_nSynchHmi);
                  /* On architecture switch this state occures with u16WarningIDOld == WIM_nenInvalidMsg 
                     This behaviour is OK. We ignore it here.*/
               }
            }
         }
      } break;
      case EV_DPOOL_Always_WIM_u16CanceledSlack_WIM_vDoHmiEvents:
      {
         /* Receive DpoolData and Check validation */
         if(E_DATA_OK == DPOOL_enGetPoolData(DPOOL_nDataWIM_u16CanceledSlack, &u16CanceledSlack))
         {
            if((WIM_tenMsg)u16CanceledSlack != WIM_nenInvalidMsg)
            {
               if(u16CanceledSlack ==  WIM__enDspSlackMasterWaiting)
               {
                  WIM__enDspSlackMasterWaiting = WIM_nenInvalidMsg;
                  /* Generate cancel event for valid messages */
                  WIM__vOnEvent_GC((WIM_tenMsg)u16CanceledSlack, WIM__nDspCancel);
               }
               if(u16CanceledSlack == WIM__enDspSlackMaster)
               {
                  WIM__enDspSlackMaster = WIM_nenInvalidMsg;
                  /* Generate cancel event for valid messages */
                  WIM__vOnEvent_GC((WIM_tenMsg)u16CanceledSlack, WIM__nDspCancel);
               }
            }
         }
      } break;
   }
}

/**
* PowerOn initialisation of State Handler
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vStateHandlerInit_GC(void)
{ 
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* reset stored handling message */
   WIM__enWaitingHdlMsg = WIM_nenInvalidMsg;
   /* Reset WakeIC attributes counter for registered warnings*/
   WIM__u8KeepActiveIcRegisteredCount = 0;
   /* clear dynamic states of all messages */
   memset(WIM__astMsgStates, 0, WIM__mGetNoOfMessages * sizeof(WIM__tstMsgState));
   /* reset the fault memory message */
   WIM__vMenuFaultMemInit();
   /* cancel all timers that maybe running */
   WIM__vCancelTimer(WIM__nTimerDspModal);
   WIM__vCancelTimer(WIM__nTimerDspNormal);
   WIM__vCancelTimer(WIM__nTimerDspNormalSlack);
   WIM__vCancelTimer(WIM__nTimerHdlExpire);
   WIM__vCancelTimer(WIM__nTimerAcuDelModal);
   WIM__vCancelTimer(WIM__nTimerAcuDelNormal);
   WIM__vCancelTimer(WIM__nTimerDspDelModal);
   WIM__vCancelTimer(WIM__nTimerDspDelNormal);
}

/**
* Reset state of all warnings at Display-Off-Edge
*   @return  void
*   @param   none
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
void WIM__vResetAllWarnings(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   
   /* reset stored handling message */
   WIM__enWaitingHdlMsg = WIM_nenInvalidMsg;
   /* cancel all timers that maybe running */
   WIM__vCancelTimer(WIM__nTimerDspModal);
   WIM__vCancelTimer(WIM__nTimerDspNormal);
   WIM__vCancelTimer(WIM__nTimerDspNormalSlack);
   WIM__vCancelTimer(WIM__nTimerHdlExpire);
   WIM__vCancelTimer(WIM__nTimerAcuDelModal);
   WIM__vCancelTimer(WIM__nTimerAcuDelNormal);
   WIM__vCancelTimer(WIM__nTimerDspDelModal);
   WIM__vCancelTimer(WIM__nTimerDspDelNormal);

   /* Reset WakeIC attributes counter for registered warnings*/
   WIM__u8KeepActiveIcRegisteredCount = 0;

   /* Reset the stored display master status  */
   /* Must be set only in WIM__vDoHmiFeedback! Otherwise Hil output will be wrong.
   WIM__enDspMaster = WIM_nenInvalidMsg;
   */
   WIM__enDspMasterWaiting = WIM_nenInvalidMsg;
   WIM__enDspSlackMasterWaiting = WIM_nenInvalidMsg;

   /* Reset also the MenuFaultMemory */
   WIM__vMenuFaultMemInit();
   /* clear dynamic states of all messages */
   memset(WIM__astMsgStates, 0, WIM__mGetNoOfMessages * sizeof(WIM__tstMsgState));

   /* Reset all warning states that are handled in RequestControl
   *  and re-check all warnings.*/
   WIM__vStartResetWarningsRequestControl_GC();
}

/**
* Restore state of messages on KlR On event 
* It is defined that:
* - all messages that are deleted/canceled will be reset
* - all messages that are displayed or waiting stay as they are
* - all messages that are manually confirmed are restored (to Waiting)
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vRestoreWarnings(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   WIM__tstMsgState stStateDispMaster = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   WIM__tstMsgState stStateDispSlackMaster = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   WIM__tstMsgState stStateDispSlackMasterWaiting = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   bool boRestoreDispMaster = False; 
   bool boRestoreDspSlackMaster = False; 
   bool boRestoreDspSlackMasterWaiting = False; 
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   
   /**
   * (I) stop scheduler - will be re-enabled again if all messages have been 
   * checked again after reset 
   */
   WIM__vStopSchedule();

   /**
   * (II) reset all warning states that are handled in StateHandler
   */
   /* Reset WakeIC attributes counter for registered warnings*/
   WIM__u8KeepActiveIcRegisteredCount = 0;

   /* if display master present and still registered */
   if(   (WIM__enDspMaster < WIM_nenNoOfMessages)
      && (WIM__mboGetRegFlag(WIM__enDspMaster)))
   {
      stStateDispMaster = WIM__astMsgStates[WIM__enDspMaster];
      boRestoreDispMaster = True;
   }

   /* if display Slack master present and still registered */
   if(   (WIM__enDspSlackMaster < WIM_nenNoOfMessages)
      && (WIM__mboGetRegFlag(WIM__enDspSlackMaster)))
   {
      stStateDispSlackMaster = WIM__astMsgStates[WIM__enDspSlackMaster];
      boRestoreDspSlackMaster = True;
   }
   
   /* if display Slack master present and still registered */
   else if(   (WIM__enDspSlackMasterWaiting < WIM_nenNoOfMessages)
      && (WIM__mboGetRegFlag(WIM__enDspSlackMasterWaiting)))
   {
      stStateDispSlackMasterWaiting = WIM__astMsgStates[WIM__enDspSlackMasterWaiting];
      boRestoreDspSlackMasterWaiting = True;
   }

   /* clear dynamic states of all messages */
   memset(WIM__astMsgStates, 0, WIM__mGetNoOfMessages * sizeof(WIM__tstMsgState));

   /* Restore DispMaster */
   if(boRestoreDispMaster == True)
   {
      /* restore acoustic flags for currently displayed message */
      WIM__astMsgStates[WIM__enDspMaster].biAcousticPlayed  = stStateDispMaster.biAcousticPlayed;
      WIM__astMsgStates[WIM__enDspMaster].biAcuRestart      = stStateDispMaster.biAcuRestart;
      WIM__astMsgStates[WIM__enDspMaster].biAcuRetriggered  = stStateDispMaster.biAcuRetriggered;
      WIM__astMsgStates[WIM__enDspMaster].biAcuState        = stStateDispMaster.biAcuState;
      WIM__astMsgStates[WIM__enDspMaster].biQualifier       = stStateDispMaster.biQualifier & 0xF0;
   }
      
   /* Restore DspSlackMaster */
   if(boRestoreDspSlackMaster == True)
   {
      /* restore flags for currently displayed message */
      WIM__astMsgStates[WIM__enDspSlackMaster].biDisplayState  = stStateDispSlackMaster.biDisplayState;
      WIM__astMsgStates[WIM__enDspSlackMaster].biQualifier     = stStateDispSlackMaster.biQualifier;
      WIM__astMsgStates[WIM__enDspSlackMaster].biRegistered    = stStateDispSlackMaster.biRegistered;
      WIM__astMsgStates[WIM__enDspSlackMaster].biDisplayState  = stStateDispSlackMaster.biDisplayState;
   }
      
   /* Restore DspSlackMasterWaiting */
   if(boRestoreDspSlackMasterWaiting == True)
   {
      /* restore flags for currently displayed message */
      WIM__astMsgStates[WIM__enDspSlackMasterWaiting].biDisplayState  = stStateDispSlackMasterWaiting.biDisplayState;
      WIM__astMsgStates[WIM__enDspSlackMasterWaiting].biQualifier     = stStateDispSlackMasterWaiting.biQualifier;
      WIM__astMsgStates[WIM__enDspSlackMasterWaiting].biRegistered    = stStateDispSlackMasterWaiting.biRegistered;
      WIM__astMsgStates[WIM__enDspSlackMasterWaiting].biDisplayState  = stStateDispSlackMasterWaiting.biDisplayState;
   }

   /* reset stored handling message */
   WIM__enWaitingHdlMsg = WIM_nenInvalidMsg;
   /* Reset also the MenuFaultMemory */
   WIM__vMenuFaultMemInit();

   /**
   * (III) cancel all timers of StateHandler that maybe running 
   */
   WIM__vCancelTimer(WIM__nTimerDspModal);
   WIM__vCancelTimer(WIM__nTimerDspNormal);
   WIM__vCancelTimer(WIM__nTimerDspNormalSlack);
   WIM__vCancelTimer(WIM__nTimerHdlExpire);

   /**
   * (IV) reset all warning states that are handled in RequestControl
   *      and re-check all warnings. 
   */
   /* Start restore of warning states handled in RequestControl *
   *  then re-check all warnings.                               *
   *  In case of multi controller system this processed in ICom */
   WIM__vStartRestoreWarningsRequestControl_GC();

   /* Trigger application checked warnings (complex condition) 
    *  Results are queued in after StartRestoreWarnings */ 
   WIM__vCheckComplexWarningsRequestControl();
   

   /* finally WIM__vFinishedRestoreWarnings_GC(); is called by RequestControl
   *  direct, or by using of ICom communication on a multi controller System. */
   
}

/**
* RestoreWarnings has finished and
* the Scheduler has to be restarted, retriggered.
*   @return  void
*   @param   void
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
void WIM__vFinishedRestoreWarnings_GC(void)
{
   
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* If former display master is no longer registered, reset saved acoustic flags */
   if(WIM__enDspMaster < WIM_nenNoOfMessages &&
      !WIM__mboGetRegFlag(WIM__enDspMaster))
   {
      /* restore acoustic flags for currently displayed message */
      WIM__astMsgStates[WIM__enDspMaster].biAcousticPlayed = 0;
      WIM__astMsgStates[WIM__enDspMaster].biAcuRestart = 0;
      WIM__astMsgStates[WIM__enDspMaster].biAcuRetriggered = 0;
      WIM__astMsgStates[WIM__enDspMaster].biAcuState = 0;
      WIM__astMsgStates[WIM__enDspMaster].biQualifier = 0;
   }

   /* allow scheduling now and initially trigger scheduler */
   WIM__vStartSchedule();
   WIM__vTriggerSchedule();
   WIM__vScheduleAcoustics();
   
}

/**
* Timer callback function.
* Called if one of the state handler relevant timers has elapsed.
* - WIM__nTimerDspModal   timer modal display phase
* - WIM__nTimerDspNormal  timer normal display phase
* - WIM__nTimerHdlExpire  timer handling validity
*   @return  void
*   @param   enTimer: Timer identifier, xCorrTag: Correlation tag (message Id)
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vDspTimer(WIM__tenTimer enTimer, WIM__txCorrTag xCorrTag)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   switch (enTimer)
   {
      case WIM__nTimerDspModal:
         /* modal phase ended -> generate event */
         WIM__vOnEvent_GC((WIM_tenMsg)xCorrTag, WIM__nTmrDspModal); 
         break;
      case WIM__nTimerDspNormal:
         /* normal phase ended -> generate event */
         WIM__vOnEvent_GC((WIM_tenMsg)xCorrTag, WIM__nTmrDspNormal);
         /* @MaIm */
         WIM__vScheduleAcoustics();
         break;
      case WIM__nTimerDspNormalSlack:
         /* normal phase ended -> generate event */
         WIM__vOnEvent_GC((WIM_tenMsg)xCorrTag, WIM__nTmrDspNormal);
         break;
      case WIM__nTimerHdlExpire:
         /* validity time ended -> generate event */
         WIM__vOnEvent_GC((WIM_tenMsg)xCorrTag, WIM__nTmrHdlExpired); 
         break;
      default:
         /* invalid timer configuration */
         WIM__vRaiseException(WIM_nErrConfig);
         break;
   }
}

/**
* Central event function.
* Dispatches all events depending on message type to the appropriate
* handler function. The function is defined in the message type specific 
* state matrix. Scheduler is triggered, if required.
*   @return  bool: True if event consumed, False otherwise
*   @param   enMsg: Message identifier, enEvt: Event identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vOnEvent_GC(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boConsumed = False;       /* event consumed state (display)           */
   bool boConsumedAcu = False;    /* event consumed state (acoustics)         */
   bool boException = False;      /* raise exception on config/state error    */
   bool boHandleAcoustic = False; /* flag for acoustic event handling         */
   bool boDisplayedFlag;          /* temp. storage for displayed flag         */
   uint8 u8DspState = 0;          /* current display state                    */
   uint8 u8AcuState = 0;          /* current acoustic state                   */
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* find handler function in state matrix */
   if (/* event in valid range? */
          (enEvt < WIM__nNoOfStateEvents)
       /* message identifier in range? */
       && (enMsg < WIM__mGetNoOfMessages))
   {
      /*** handle "Registered" and "Canceled" flags here */
      if (/* set the flags if "Register" or "Retrigger" */
          (enEvt == WIM__nRegister) || (enEvt == WIM__nRetrigger))
      {
         /* Flag handling */
         WIM__mSetRegFlag(enMsg, On);
         WIM__mSetCanceledFlag(enMsg, Off);

         /* no Slack handling for Fast Activation and Keep Active */
         if ( !WIM__mboIsSlackMsg(enMsg))
         {
            if ( /* is message in FastActivationList */
                 WIM__boFastActivationSound(enMsg))
            {
               SYN__mvStartDummySound();
            }
            /*** increment Counter for registered messages that keep the display active */
            if (WIM__mboKeepActiveIc(enMsg)) 
            {
               WIM__u8KeepActiveIcRegisteredCount++;
            }

            /* Trigger DspRq state handler on edge from zero to one */
            if(WIM__u8KeepActiveIcRegisteredCount == 1)
            {
               /* This is a keep active warning only, do the transition with condition 
                  "Display == On" */
               WIM__vRequestDisplayStateHdl(WIM__nKeepActRegistered);
            }
         }
      }
      /* no Slack handling for WakeIC, DspCancel, DspSuppr */
      if ( !WIM__mboIsSlackMsg(enMsg))
      {
         /* if event "WakeIC"  
          * and not MsgType "WIM__nAcoustic", wake up handling */
         if( (enEvt == WIM__nWakeIC) && (WIM__menGetMsgType(enMsg) != WIM__nAcoustic))
         {
            /* Trigger DspRq state handler on edge from zero to one */
            if (WIM__mboWakeupIc(enMsg))
            {
               WIM__vRequestDisplayStateHdl(WIM__nWakeUpRegistered);
            }
         }

         if(enEvt == WIM__nDspCancel)
         {
            /* Master has been changed due to HMI feedback, if no warning is active anymore
             * the display state handler must be triggered
             */
            if(WIM__enDspFavourite == WIM_nenInvalidMsg &&
            WIM__enDspMasterWaiting == WIM_nenInvalidMsg)
            {
               WIM__vRequestDisplayStateHdl(WIM__nNoWarningRequested);
            }
         }

         if(enEvt == WIM__nDspSuppr)
         {
            if(WIM__enDspMasterWaiting == enMsg)
            {
               /* The favourite has been suppressed by the HMI,reset WIM__enDspMasterWaiting */
               WIM__enDspMasterWaiting = WIM_nenInvalidMsg;
            }

            /* if no warning is active anymore the display state handler must be triggered */
            if(WIM__enDspFavourite == WIM_nenInvalidMsg &&
               WIM__enDspMasterWaiting == WIM_nenInvalidMsg)
            {
               WIM__vRequestDisplayStateHdl(WIM__nNoWarningRequested);
            }
         }
      }

      /* reset/set the flags if "Delete" or "Cancel" */
      if ((enEvt == WIM__nCancel) || (enEvt == WIM__nDelete))
      {
         if (enEvt == WIM__nCancel)
         {
            /* set the flag if "Cancel" */
            WIM__mSetCanceledFlag(enMsg, On);
         }
         else
         {
            /* reset the flag if "Delete" */
            WIM__mSetCanceledFlag(enMsg, Off);
         }
         /* reset the flag if "Delete" */
         WIM__mSetRegFlag(enMsg, Off);
         /* if not a slack */
         if ( !WIM__mboIsSlackMsg(enMsg))
         {
            /*** decrement Counter for registered messages that keep the display active */
            if (WIM__mboKeepActiveIc(enMsg) && WIM__u8KeepActiveIcRegisteredCount > 0) 
            {
               /* decrement counter */
               WIM__u8KeepActiveIcRegisteredCount--;
               /* Trigger DspRq state handler on edge from one to zero */
               if (WIM__u8KeepActiveIcRegisteredCount == 0)
                  WIM__vRequestDisplayStateHdl(WIM__nNoKeepActRegistered);
            }
         }
      }
      /* get current display and acoustic state for given message  */
      u8DspState = WIM__mu8GetDspState(enMsg);
      u8AcuState = WIM__mu8GetAcuState(enMsg);
      boDisplayedFlag = WIM__mboGetDisplayedFlag(enMsg);
      /* find the appropritae state matrix for the type of message */
      if (/* Message is a Single Line Acknowledgement */
          WIM__mboIsSlackMsg(enMsg))
      {
         if (/* and message is handling */
             (WIM__menGetMsgType(enMsg) == WIM__nHandling))
         {
            /* valid source state? */
            if (u8DspState < WIM__nNoOfDspStatesMsg)
            {
               /* is an handler function configured for this event? */
               if (NULL != WIM__apboStateFctMatrixSlackMsg[enEvt][u8DspState])
               {
                  /* call the function configured for current warn state & event */ 
                  boConsumed = (WIM__apboStateFctMatrixSlackMsg[enEvt][u8DspState])(enMsg, enEvt);
               }
            }
            else 
            {
               /* Error -> call Exception handler */
               boException = True;
            }
            /* if the event fuction returned True, we need to trigger the scheduler */
            if(boConsumed)
            {
               WIM__vTriggerSchedule();
            }
         }
      }
      else
      {
         switch (WIM__menGetMsgType(enMsg))
         {
            case WIM__nWarning:      /* normal warning */
            case WIM__nWarningPtnr:  /* warning with partner message */      
            case WIM__nHandling:     /* handling message */
            case WIM__nHandlingPtnr: /* handling with partner message */
            {
               /* valid source state? */
               if (u8DspState < WIM__nNoOfDspStatesMsg)
               {
                  /* is an handler function configured for this event? */
                  if (NULL != WIM__apboStateFctMatrixMsg[enEvt][u8DspState])
                  {
                     /* call the function configured for current warn state & event */ 
                     boConsumed = (WIM__apboStateFctMatrixMsg[enEvt][u8DspState])(enMsg, enEvt);
                  }
                  /* if the display message has an acoustic, handle this too */
                  if (WIM__mboWithAcoustic(enMsg) == True)
                  {
                     boHandleAcoustic = True;
                  }
               } 
               else
               {
            	   /* Error -> call Exception handler */
            	   boException = True;
               }
            } break;

            case WIM__nAcoustic: /* acoustic only message */
               boHandleAcoustic = True;  /* handled below */
               break;
            default:
               boException = True; /* Error -> call Exception handler */
               break;
         }

         if (/* handle acoustic message events */
                (boHandleAcoustic == True)
             /* and valid source state */
             && (u8AcuState < WIM__nNoOfStatesAcu))
         {
            if (/* is an handler function configured for this event? */
                NULL != WIM__apboStateFctMatrixAcu[enEvt][u8AcuState])
            {
               /* call the function configured for current warn state & event */
               boConsumedAcu = (WIM__apboStateFctMatrixAcu[enEvt][u8AcuState])(enMsg, enEvt);
            }
         }
         /* notify clients about warning state changes */
         if ((u8DspState != WIM__mu8GetDspState(enMsg)) ||
             ((u8DspState == WIM__nManuQuit) && ((enEvt == WIM__nCancel) || (enEvt == WIM__nDelete))))
         {
            WIM__vNotifyStateChange(enMsg, enEvt, boDisplayedFlag);
         }        
         /* if the event fuction returned True, we need to trigger the scheduler */
         if(boConsumed)
         {
            WIM__vTriggerSchedule();
         }
         /* if the event function returned True, we need to trigger the acoustic scheduler */
         if(boConsumedAcu)
         {
            WIM__vScheduleAcoustics();
         }
      }
   }
   else
   {
      /* invalid parameter -> raise exception */
      boException = True;
   }
   if (/* an error ocurred -> Raise an exception */
       boException)
       WIM__vRaiseException(WIM_nErrState);
}

/******************************************************************************
* FILE LOCAL FUNCTION DEFINITIONS
*******************************************************************************/
/******************************************************************************
* EVENT CONTAINERS
*******************************************************************************/

/**
* Inform applications about message state changes
*   @return  void
*   @param   enMsg: message identifier
*   @param   enEvt: state event 
*   @param   boDisplayedFlag: message was displayed before
*   @author  T.Godemann, Schleissheimer GmbH 
*/
static void WIM__vNotifyStateChange(WIM_tenMsg enMsg, 
                                    WIM__tenEventIntern enEvt, 
                                    bool boDisplayedFlag)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   WIM_tenDisplayEvent enNotify;                    /* notification event     */
   uint8 u8NewState;                                /* new message state      */
   uint32 u32HilId;                                 /* message HIL Id         */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if ( enMsg < WIM__mGetNoOfMessages)
   {
      u32HilId = WIM__u32GetHilId(enMsg);
      enNotify = WIM_nNoOfDisplayEvents;
      u8NewState = WIM__mu8GetDspState(enMsg);
      if (/* display assignment? */
          enEvt == WIM__nDspAssign)
      {
         if (/* initial display? */
             boDisplayedFlag == False)
            enNotify = WIM_nDisplayOn;
         else
            enNotify = WIM_nDisplayAgain;
      }  
      else
      {
         if (/* display replacement? */
             enEvt == WIM__nDspCancel)
         {
            if (/* still in warn roll? */
                u8NewState == WIM__nWaiting)
               enNotify = WIM_nDisplayAway;
            else
            {
               enNotify = WIM_nDisplayOff;
               if (/* on condition no longer fulfilled? */
                   u8NewState == WIM__nAutoQuit)
               {
                  /* call handler */
                  WIM__mNotifyHandler_GC(u32HilId, enNotify);
                  enNotify = WIM_nInactive;
               }
            }
         }
         else
         {
            /* confirmation event? */
            if (u8NewState == WIM__nManuQuit)
            {
               switch (enEvt)
               {
                  case WIM__nConfirmation:
                  case WIM__nManuQuitOk:
                     /* OK key */
                     if (WIM__mboGetRegFlag(enMsg) == False)
                     {
                        /* message is not active anymore, send WIM_nInactive
                           in addition to ManuQuit event */
                        WIM__mNotifyHandler_GC(u32HilId, WIM_nManuQuitOk);
                        enNotify = WIM_nInactive; 
                     }
                     else
                     {
                        enNotify = WIM_nManuQuitOk; 
                     }
                     break;
                  case WIM__nManuQuitBack:
                     /* Back key */
                     if (WIM__mboGetRegFlag(enMsg) == False)
                     {
                        /* message is not active anymore, send WIM_nInactive
                           in addition to ManuQuit event */
                        WIM__mNotifyHandler_GC(u32HilId, WIM_nManuQuitBack);
                        enNotify = WIM_nInactive; 
                     }
                     else
                     {
                        enNotify = WIM_nManuQuitBack; 
                     }
                     break;
                  case WIM__nCancel:
                  case WIM__nDelete:
                     /* Cancel/Delete */
                     enNotify = WIM_nInactive;
                     break;
                  default:
                     break;
               }
            }
            else if(u8NewState == WIM__nPreConfirmed)
            {
               /* Application are informed by the PreConfirmation Container 
                * about pre confirmation of the warning
                */
               enNotify = WIM_nNoOfDisplayEvents;
            }
            else
            {
               if (/* on condition no longer fulfilled? */
                   u8NewState == WIM__nAutoQuit)
               {
                  if (/* confirmed message is active display master? */
                      enMsg == WIM__enGetDisplayMaster())
                  {
                     /* call handler */
                     WIM__mNotifyHandler_GC(u32HilId, WIM_nDisplayOff);
                  }
                  /* inactive */
                  enNotify = WIM_nInactive;
               }
               else
               {
                  if (/* message becomes active (again) */
                         (u8NewState == WIM__nWaiting  )
                      && (   (enEvt  == WIM__nRegister )
                          || (enEvt  == WIM__nRetrigger)))
                  {
                     /* active */
                     enNotify = WIM_nActive;
                  }
                  else
                  {
                     if (/* message becomes inactive (never displayed) */
                         u8NewState == WIM__nInactive)
                     {
                        /* active */
                        enNotify = WIM_nInactive;
                     }
                  }
               }
            }
         }
      }
      if (/* notification event occured? */
          enNotify != WIM_nNoOfDisplayEvents) 
      {
         /* call handler */
         WIM__mNotifyHandler_GC(u32HilId, enNotify);
      }
   }
}

/**
* Inform applications to re-check message conditions after message reset
*   @return  void
*   @param   void
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vCheckComplexWarnings_GC(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint8 u8Index = 0; /* index variable                                       */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   while (/* loop through all container functions */
          WIM__apvCheckComplexContainer[u8Index] != WIM__nLastCntEntry)
   {
      /* call container function */
      (WIM__apvCheckComplexContainer[u8Index])();
      u8Index++;
   }
}
