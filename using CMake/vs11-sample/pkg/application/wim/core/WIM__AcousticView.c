/******************************************************************************
*=====================      Copyright by Continental AG      ==================
*******************************************************************************
* Titel        : WIM__AcousticView.c
*
* Description  : View class for messages with acoustic output (beep/gong)
*                Private class that manages sound attributes and controls
*                acoustic output for acoustic messages with and without display
*
* Environment  : OSEK, JCP (NEC V850)
*
* Responsible  : A.Wagner, Schleissheimer GmbH
*
* Guidelines   : SMK 3.3  
*
* Template name: OOLite Codefile, Revision 1.0
*
* CASE-Tool    : Together Controlcenter, Version 6.2
*
* Revision List: (Will be filled by PVCS)
* Archive: Initial revision for VS11 (Based on 213IC-EL E009.4rel)
*
* Archive: $Log: WIM__AcousticView.c  $
* Archive: Revision 1.1.2.9 2014/07/18 16:08:14CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 40728 : WIM: AcousticVel is not considered correctly for interval acoustics
* Archive: Revision 1.1.2.8 2014/06/06 18:56:36CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 40088 : WIM: Extend implementation for break in acoustic HIL signal - WDM 203
* Archive: DC MR 40569 : WIM: Deactivation time of FCW/LCW acoustics takes too long - WDMs 99460, 99457
* Archive: DC MR 40609 : WIM: Correct handling for "kurzzeitige Ruhe" (short rest) - WDMs 99458, 99481, 99485
* Archive: Revision 1.1.2.7 2014/03/21 13:01:40CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 39524 : WIM: Correct interval acoustic handling and HIL feedback
* Archive: DC MR 39163 : WIM: Overcome illegal memory access and correction of HMI acoustics notification
* Archive: DC MR 40021 : WIM: Sound of FCW warning is not retriggered after reset
* Archive: Revision 1.1.2.6 2013/11/22 16:52:43CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 36779 : BR213EL, E006, Implementation of new WarnDB
* Archive: DC MR 36462 : WIM: Implement new scheduling and state handling for acoustic part
* Archive: Revision 1.1.2.5 2013/08/16 13:30:41CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 33822 : IC213EL-GC WIM: display synchroneous periodic tone not stopped with display off: WDM62157
* Archive: DC MR 33932 : IC213EL GC WIM: Initial sound requests for warnings does not work if sound system is not ready
* Archive: DC MR 33999 : BR213GC-EL, E005, WIM, CWMDL: API split - ORM5621
* Archive: DC MR 34028 : BR213EL, E005, StyleGuide Validation and implementation
* Archive: DC MR 34202 : BR213IC-GC-EL, WIM: Missing HIL output for seat belt warning acoustics - Folow-Up 33655
* Archive: DC MR 34326 : BR213-GC-EL/E005.1, WIM: Display is on for 2 minutes even when warning has disappeared
* Archive: DC MR 34547 : BR213-EL, E005.1/GC,WIM: Removal of QAC warning
* Archive: DC MR 34706 : BR213-GC-EL, E005.1: Chance DOCG implementation in WIM and TPOL
* Archive: DC MR 34781 : BR213-GC-EL, E005.1, WIM: Inconsistent display output in Fault Memory
* Archive: Revision 1.1.2.4 2013/06/11 14:16:24CEST Harms-EXT, Daniel (uidw1026) 
* Archive: DC MR 33655: BR213IC-GC-EL, WIM: Implement break in HIL acoustic output signal - OPL55
* Archive: Revision 1.1.2.3 2013/05/17 16:07:21CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 33413: BR213EL/GC, E004, WIM: Takeover of the latest changes from BR205
* Archive: Revision 1.1.2.2 2013/03/27 15:53:38CET Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
* Archive: Revision 1.14 2012/11/15 18:42:04CET Immel-EXT, Marc (uid37561) 
* Archive: DC MR 30458: BR222 E010/GC, WIM: Error in display roll behaviour of warnings
* Archive: DC MR 30398: W222 E010/GC, WIM: First sound of SBW NCAP phase 4 is not played, Follow-up
* Archive: Revision 1.13 2012/10/19 10:50:25CEST Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 27470 W222, E010/GC, WIM: Active sound shall play to the end when display goes off - �LP2896
* Archive: - Correction
* Archive: Revision 1.12 2012/10/18 17:00:23CEST Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 27470: W222, E010/GC, WIM: Active sound shall play to the end when display goes off - �LP2896
* Archive: DC MR 29924: E010: WIM acoustic problems: corrections for WDM53980, 53982 and 53999
* Archive: DC MR 29926: W222GC: WDM47699 WIM do not differs between Frontal and Lateral Collision warning sound
* Archive: DC MR 29928: W222, E010/GC, WIM: Sync acoustic is delayed too long
* Archive: DC MR 29866: BR222, E010/GC, WIM: Redesign of fault memory entry management
* Archive: DC MR 30023: W222IC-GC, E010: When displaying the oil switch warning the GC makes a reset
* Archive: Revision 1.11 2012/10/02 12:24:53CEST Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 27252 BR222 MY - Use Global Storage for HMI internal variables
* Archive: DC MR 29677 W222, E010/GC, WIM: Possible access violation in fault memory
* Archive: DC MR 29701 W222, E010/GC, WIM: Changes for SBW acoustic handling - �LP 3082 / missing HIL output for NCAP acoustics - WDM 47538
* Archive: Revision 1.10 2012/07/20 08:56:18CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 27180: W222, E009/GC, WIM: Acoustic stop behavior - WDM43362, WDM43364
* Archive: DC MR 27539: BR222/E7.4/GC: WIM: Update HIL feedback for sound and soundrequests
* Archive: Revision 1.9.1.4 2012/07/20 08:56:18CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: D MR 26329: W222, E007/GC, WIM: Change of Prio1Mute and Lowering times - �LP2873
* Archive: Revision 1.9.1.3 2012/07/11 11:53:58CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 27179: W222, E007/GC, WIM: Acoustic stop behavior - WDM43362, WDM43364
* Archive: DC MR 26956: BR222/E7.4/GC: WIM: Update HIL feedback for sound and soundrequests
* Archive: Revision 1.9 2012/06/14 13:18:56CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 26329: W222, E007/GC, WIM: Change of Prio1Mute and Lowering times - �LP2873
* Archive: DC MR 25901: W222, E007/AC, WIM: Change of Prio1Mute and Lowering times - �LP2873
* Archive: Revision 1.7 2012/05/10 17:21:01CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 25842: BR222/E7.2/GC: WIM: HIL Fix Loudness Feedback (WDM31515)
* Archive: DC MR 25916: W222, E007/GC, WIM: Changes on display-block by sound only warning - WDM35459
* Archive: DC MR 25913: W222, E007/AC, HIL: Mapping of WIM sound types
* Archive: DC MR 25704: W222, E007/GC, WIM: Fix for corrupted sound - WDM35438
* Archive: Revision 1.6 2012/05/04 14:10:28CEST 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: DC MR 25131: W222, E007/GC, WIM: Implementation of exceptions
* Archive: DC MR 25823: BR222 E7.2: Implementation of L3 delivery (XML-Files)
* Archive: DC MR 21251: W222, E007/GC, WIM: ComplexFunction of Warning 0x2001A6 Kurvenlicht
* Archive: DC MR 25710: W222, E007/GC, WIM: Inactive handling messages show up after 600ms - WDM35020
* Archive: DC MR 25126: W222, E007/GC, WIM: Behaviour of sync acoustics - WDM35391, 35418, 35392, 35389, 35396, 35421
* Archive: Revision 1.4 2012/04/04 13:41:45CEST 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: DC MR 24870: W222, E007/GC, WIM: Implement changes from Review ORM2907
* Archive: DC MR 25007: W222, E007/GC, WIM: Displacement of handling messages - WDM20280
* Archive: DC MR 25041: Do not specify message propagation in message description files
* Archive: DC MR 25095: W222, E007/GC, WIM: Improvement of Timer accuracy for display role - WDM 25704
* Archive: DC MR 25034: Reduction of lag times in case of vehicle locked
* Archive: DC MR 25393: W222, E007/GC, WIM: No cancel of interval acoustic - WDM31269, �LP2895
* Archive: Revision 1.3 2011/12/02 10:53:00CET 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: Revision derived from PVCS revision DC.SW.PAC.WIM_222IC_GC_COMMON_VarP.V01.02.pre05
* 
*    Rev 1.12   Dec 02 2011 14:49:56   SCHL_Dirk.Gottwalles
* DC MR 23223: W222, E007/AC: Warnung Parkbremse 0x2001A8 �LP2607
* DC MR 23256: W222GC:E006 new volume interface
* DC MR 23803: Applications should send global direct messages
* DC MR 22621: BR222/E007/GC: HIL: DisplayColor
* 
*    Rev 1.11   Nov 18 2011 15:58:38   SCHL_Dirk.Gottwalles
* DC MR 23225: W222, E007/GC, WIM: Auto repeat feature for fault memory WDM19781
* DC MR 22930: BR222, E007/AC, WMN: Implementation of changes for new WEM
* DC MR 23685: W222, E007/GC, WIM: Acoustic macros access array out of bounds
* DC MR 23617: E007/AC WIM remove pragma 'callmode far'
* 
*    Rev 1.10   Oct 21 2011 09:54:20   SCHL_Dirk.Gottwalles
* DC MR 23074: BR222: Implementation of E007 pre10 XML-Files and StyleGuide
* DC MR 22734: W222, E006/AC, WIM: Timeout function shall not use first value, WDM1378
* DC MR 23190: Use visibility change detection mechanism
* DC MR 23333: BR222/E007/GC: HIL: Acoustics WIM-REQ (WDM#19107)
* DC MR 22968: W222, E007/GC, WIM: Prio1 mute and partial lowering output WDM20219
* 
*    Rev 1.9   Aug 12 2011 16:39:38   SCHL_Dirk.Gottwalles
* DC MR 22652: W222, E006/AC, SCS: Remove warning management
* DC MR 22655: W222, E006/AC, WIM: Implmentation of complex key handling for warnings
* DC MR 22263: W222, E006/GC, WIM: Remove of unused sound Ids
* DC MR 22549: E006/GC: HIL: Get acoustics status indication for warnings
* DC MR 22686: Implementation of L3 Menu, Warn DB for E006
* DC MR 22733: W222, E006/GC, WIM: Implementation of complex key handling for warnings
* DC MR 21544: E006/GC: HIL: Get TPOL Menu HIL-ID and WIM-HIL-ID
* DC MR 22749: Integration of ARTEMMIS 3.2
* 
*    Rev 1.8   Jul 13 2011 15:34:38   SCHL_Dirk.Gottwalles
* DC MR 22485: BR222, E006 Implementation of xml-files and style guide
* DC MR 22396: BR222: New acoustic for rearseatbeltwarning �LP2571
* DC MR 22456: Permanent Display menu - hybrid (GC)
* DC MR 21811: BR222: WIM: New Keywords/functions �LP2444, Part II
* DC MR 22265: W222, E006/AC, WIM:Change of Timeout behaviour
* DC MR 22261: W222, E006/AC, WIM: New keyword for WarnDB TIMEOUT_NOT_ENG_START, �LP2574
* DC MR 22260: W222, E006/AC, WIM: New keyword for WarnDB TIMEOUT_KL15_NOT_ENG_START, �LP2573
* DC MR 22092: W222, E006/AC, WIM: Door warning state is not correct evaluated for undefined values
* 
*    Rev 1.7   May 13 2011 15:15:24   SCHL_Dirk.Gottwalles
* DC MR 22206: FLG: No more WIM requests necessary
* DC MR 22089: E004/GC, WIM: Configure warnings that keep the IC awake
* DC MR 22090: BR222/GC, WIM: Warning sounds are not played correct if sound subsystem was not active previoulsy
* 
*    Rev 1.6   Mar 22 2011 16:07:26   SCHL_Dirk.Gottwalles
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
*    Rev 1.5   Dec 03 2010 15:56:40   SCHL_Lars.Gruenewald
* DC MR20903 BR222 WIM cancel dsp synch acustics at warning left the display
* DC MR21188 BR222: WIM Display lag time at multiple wakeupreq.
* DC MR21334 GC-E003: Update of PCMPL and changed Interface
* DC MR21353 HIL& WIM: Acoustics SetBeltWarningLevel2 und Level1, ContinuousWarning
* DC MR21151 HIL: wrong Accoustics Warning
* DC MR21384 BR222: two warnings for seatbeltwarning
* DC MR21318 E003: Startup MR for Traffic sign assistant (TSA)
* DC MR20897 WIM: Implementation of menu FaultMemory
* DC MR21257 Implementation of L3 WarnDB f�r E003
* 
*    Rev 1.4   Nov 19 2010 16:04:04   SCHL_Dirk.Gottwalles
* DC MR21122 BR222: WIM reaction at wakeupreq.
* DC MR21302 BR222/AC: Optimierung Aufruf Checkfunktion WIM
* DC MR20423 W222: WIM new acoustics requirements
* DC MR21177 Implementation of first WarnDB for E003
* DC MR21336 WIM: Using Enumeration Symbols for State/Widget Mapping
* 
*    Rev 1.3   Sep 17 2010 20:58:08   SCHL_Lars.Gruenewald
* DC MR21004 Startup MR for Module DOCG (Display Documentation Target Application)
* DC MR20908 E002/AC, Startup HIL
* 
*    Rev 1.2   Aug 27 2010 18:49:26   SCHL_Lars.Gruenewald
* DC MR20751  E002/AC, Introduce Warning 120 km/h
* DC MR20742  W222: Startup Modul SBW for E002
* DC MR20810  AC: Warning requests of Fuel Level Gauge (FLG)
* DC MR20835  E002/AC Startup SBC
* DC MR20951  Add property for priority to WIMController
* DC MR20589  BR222: WIM additional functionality for E002
* DC MR20216  �LP2191: new requirements for 0x2000F2
* DC MR20377  Exception entries in EXEA made by WIM
* DC MR20759  Implementation of first WarnDB for E002
* 
*    Rev 1.1   Jun 25 2010 12:22:14   SCHL_Lars.Gr�newald
* DC MR 20566  WIM222: WIM Part2 for E001
* DC MR 20629 Configuration of Display Handler
* DC MR 20639 WIM: Adaption of HMI part for E001.1 
* DC MR 20620 Startup-MR for dynamical area manager (prio)
* DC MR 20661 Br222: WIM: ICOM Reinitialization
* DC MR 20662 Needed patches for WarnDB E001
* DC MR 20560 Implementation of first WarnDB for E001
* DC MR 20490 W222 E001: start up MR SFG
* 
*    Rev 1.0   Jun 11 2010 14:05:26   SCHL_Thomas.Godemann
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
#include "CRHDL_C1.h"
/* Own headerfiles */
#include "WIM_c1.h"
/******************************************************************************
* GLOBAL DEFINITIONS
*******************************************************************************/
   
/******************************************************************************
* FILE LOCAL DEFINITIONS
*******************************************************************************/
/**                                            
* memory for current playing PCM streams       
*/                                             
static PCMPL_tenStream WIM__enStreamId;   

/**
* memory for current playing WIM acoustic Ids
*/
static WIM_tenMsg WIM__enPlayingSound;

/**
* memory for warning that is waiting for retrigger of sound
*/
static WIM_tenMsg WIM__enRetriggerSound;

/*
* memory-bit for Acustic Output special behavior -> old Sound = new Sound
*/
static bool WIM__boInsertBreakHIL;

/*
* memory for acoustic volume
*/
static bool WIM__u8Volume;

/*
* memory for frontal, lateral collision warning playing sound
*/
WIM_tenMsg WIM__enFrontLatCollWarnPlaying;

/*
* memory for continious playing sound
*/
WIM_tenMsg WIM__enContPlayingSound;

/******************************************************************************
* FILE LOCAL FUNCTION PROTOTYPES
*******************************************************************************/
static void WIM__vSoundCallback(PCMPL_tenStream enStreamNo, PCMPL_tenErrorCode enErrorCode);
static bool WIM__boStartAcousticIntern(WIM_tenMsg enMsg, WIM_tenMsg enReplacedMsg);

static inline const WIM__tstViewAttrAcu* WIM__pstGetAcuAttr(WIM_tenMsg enMsg);

/******************************************************************************
* FUNCTION DEFINITIONS
*******************************************************************************/

/**
* Get acoustic attributes
*   @return  WIM__tstViewAttrAcu*
*   @param   enMsg: Message ID
*   @author  M.Immel, Schleissheimer GmbH 
*/
static inline const WIM__tstViewAttrAcu* WIM__pstGetAcuAttr(WIM_tenMsg enMsg)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   return (enMsg < WIM_nenNoOfMessages) ? WIM__mGetMsgPropertyTable[(enMsg)].pvAcousticAttr : NULL;
}

/**
* Timer function for acoustic HIL signals that show only peaks.
*   @return  none
*   @author  D. Gottwalles, Schleissheimer GmbH
*/
void WIM__vAcousticHilTimer(WIM__tenTimer enTimer, WIM__txCorrTag xCorrTag)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   const WIM__tstViewAttrAcu* pstAttr;        /* pointer to acoustic attrib.  */
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if(enTimer == WIM__nTimerHilSignal)
   {
      pstAttr = WIM__pstGetAcuAttr(WIM__enPlayingSound);   /* get struct with acoust. attrib. */
      if (pstAttr != NULL)
      {
         /*
         * If the current playing sound is WIM_nenSeatbeltWarningLevel1 or WIM_nenSeatbeltWarningLevel2
         * HIL request signal must be released here. The request signal on HIL 
         * is only set for one cycle. If this release is overwritten by a 
         * new sound request this release will not be visible on HIL.
         */
         if(pstAttr->biAcousticType == WIM_nenSeatbeltWarningLevel1 ||
            pstAttr->biAcousticType == WIM_nenSeatbeltWarningLevel2)
         {
            WIM__vSoundOutputReqHIL(WIM_nenNoAcoustic);
         }
      }
   }
}

/**
* Callback function for elapsed HilBreakTimer
*   @return  void
*   @param   none
*   @author  Martin Wenske, Schleissheimer GmbH 
*/
void WIM__vHilBreakTimerElapsed(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   /* pointer to acoustic attrib.  */
   const WIM__tstViewAttrAcu* pstAttr;   
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* init Information for HIL-ID */
   uint16 u16SoundOutput = (uint16)WIM_nenNoAcoustic; 

   /* get struct with acoust. Attrib. */
   pstAttr = WIM__pstGetAcuAttr(WIM__enPlayingSound);

   if (pstAttr != NULL)
   {
      u16SoundOutput = (uint16)pstAttr->biAcousticType;
      if(   u16SoundOutput != (uint16)WIM_nenSeatbeltWarningLevel1 
         && u16SoundOutput != (uint16)WIM_nenSeatbeltWarningLevel2 )
      {
         DPOOL_enSetPoolData(DPOOL_nDataWIM_u16SoundOutput, &u16SoundOutput);
      }
   }
}

/**
 * Restart interval acoustics
 *   @return  void
 *   @param   xCorrTag Correlation tag (message Id)
 *   @author  A.Wagner, Schleissheimer GmbH 
 */
void WIM__vIntervalTimerElapsedCallback(WIM__txCorrTag xCorrTag)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   WIM_tenMsg enMsg = (WIM_tenMsg)xCorrTag;

   if (enMsg == WIM_nen0x20F3C5)
   {
      if (WIM__u8CounterStartsAcousticRetrigger > 1)
      {
         WIM__vRestartAcoustic(enMsg);
         WIM__u8CounterStartsAcousticRetrigger--;
      }
   }
   else
   {
      WIM__vRestartAcoustic(enMsg);
   }
}

/**
* Sound end callback-function
* Called if a time limited sound output has finished.
*   @return  void
*   @param   xCorrTag: correlation tag (Identifier of message)
*   @author  T.Godemann, Schleissheimer GmbH 
*/
static void WIM__vSoundCallback(PCMPL_tenStream enStreamNo, PCMPL_tenErrorCode enErrorCode)
{
   /***************************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************************/
   const WIM__tstViewAttrAcu* pstAttr = NULL;         /* pointer to acoustic attributes   */
   uint16 u16SoundOutput = (uint16)WIM_nenNoAcoustic; /* init Information for HIL-ID      */
   uint8 u8VolumeHIL = 0;                             /* init Information for HIL-ID      */
   uint8 u8Loudness = WIM_nenVolumeNoSound;           /* init Information for HIL-ID      */
   /****************************************************************************************
   * FUNCTION CODE
   ****************************************************************************************/
   switch(enErrorCode)
   {
   case PCMPL_nenNoErr:
   /*case PCMPL_nStreamEndNoErr: same as PCMPL_nNoErr */
      {
         /* Don't keep the system awake any longer - MR27470 */
         CRHDL_vReqHdlClearRequest(CRHDL_nReqSMSRES_SoundByWIM);
         /* Sound finished without error */
         if(WIM__enStreamId == enStreamNo ||
            WIM__enStreamId == PCMPL_nenStrError)
         {
            /* generate state handler event 'Acoustic Cancel' if limited acoustic */
            if(WIM__enStreamId <= PCMPL_nenNoOfStreams &&
               WIM__enPlayingSound < WIM__mGetNoOfMessages &&
               WIM__enRetriggerSound != WIM__enPlayingSound)
            {
               /* current acoustic stream has finished */
               WIM__vOnEvent_GC(WIM__enPlayingSound, WIM__nAcuTerminated);
            }

            /* switch Off Mute/LowerVolume request signals */
            WIM__vSwitchHUCanSignals(WIM__enPlayingSound, Off);

            /* current stream finished */
            WIM__enStreamId = PCMPL_nenStrError;
            WIM__enPlayingSound = WIM_nenInvalidMsg;
            WIM__boInsertBreakHIL = False;
            TIMER_vClear(TIMER_nWIM_HilBreakTimer);

            /* If retrigger sound was set, the sound shall be requested inside 
             * the callback
             */
            if(WIM__enRetriggerSound != WIM_nenInvalidMsg)
            {
               WIM__enPlayingSound = WIM__enRetriggerSound;
               /* Start sound that was marked to play again. This can cause the 
                * WIM to use more than one sound stream at a time.
                * WIM__enRetriggerSound will be reset inside this function.
                */
               WIM__boStartAcousticIntern(WIM__enRetriggerSound, WIM__enRetriggerSound);
            }
            else
            {
               /* Send WIM__u16SoundOutput with init value (WIM_nenNoAcoustic). */
               DPOOL_enSetPoolData(DPOOL_nDataWIM_u16SoundOutput, &u16SoundOutput);
               DPOOL_enSetPoolData(DPOOL_nDataWIM_u8SoundVolume, &u8VolumeHIL);
               DPOOL_enSetPoolData(DPOOL_nDataWIM_u8SoundLoudness, &u8Loudness);
               WIM__vSoundOutputReqHIL(WIM_nenNoAcoustic);
            }
            WIM__vScheduleAcoustics(); /* re-schedule warnings MR29923 */
         }
         else
         {
            /* unknown sound, nothing to do */
         }
      } break;
   case PCMPL_nenSndResErr:
   case PCMPL_nenDataTransferErr:
      {
         /* Don't keep the system awake any longer - MR27470 */
         CRHDL_vReqHdlClearRequest(CRHDL_nReqSMSRES_SoundByWIM);
         /* Sound did not start because of error */
         if(WIM__enStreamId == enStreamNo ||
            WIM__enStreamId == PCMPL_nenStrError)
         {
            /* switch Off Mute/LowerVolume request signals */
            WIM__vSwitchHUCanSignals(WIM__enPlayingSound, Off);
            /* current stream finished */
            WIM__enStreamId = PCMPL_nenStrError;
            WIM__enPlayingSound = WIM_nenInvalidMsg;
            WIM__enRetriggerSound = WIM_nenInvalidMsg;
            WIM__boInsertBreakHIL = False;
            TIMER_vClear(TIMER_nWIM_HilBreakTimer);
            /* Send WIM__u16SoundOutput with init value (WIM_nenNoAcoustic). */
            DPOOL_enSetPoolData(DPOOL_nDataWIM_u16SoundOutput, &u16SoundOutput);
            DPOOL_enSetPoolData(DPOOL_nDataWIM_u8SoundVolume, &u8VolumeHIL);
            DPOOL_enSetPoolData(DPOOL_nDataWIM_u8SoundLoudness, &u8Loudness);
            WIM__vSoundOutputReqHIL(WIM_nenNoAcoustic);
            /* Send statehandler event that acoustic has not been played */
            WIM__vOnEvent_GC(WIM__enPlayingSound, WIM__nAcuCancel);
         }
         else
         {
            /* unknown sound, nothing to do */
         }
      } break;
   case PCMPL_nenStreamStartNoErr:
   case PCMPL_nenPostSoundStartNoErr:
      {
         /* A sound has started */
         if(WIM__enStreamId == enStreamNo)
         {
            if(WIM__enStreamId != PCMPL_nenStrError &&
                WIM__enPlayingSound < WIM__mGetNoOfMessages)
            {
               /* Intervall tone handling */
               /* Get tone type and start the corresponding timer */
               if (/* Tone type =
                     WIM_nenFrontalCollisionWarning 
                     WIM_nenLateralCollisionWarning */
                     WIM__u16GetAcuFrequency(WIM__enPlayingSound) == WIM__nenFreq400)
               {
                  /* Start timer for 400ms phase */
                  TIMER_vStart(TIMER_nWIM_TimerFreqCollWarn, WIM_nTimerDuration_FreqCollWarn);
                  WIM__enFrontLatCollWarnPlaying = WIM__enPlayingSound;
               }
               else if (/* Tone type = 
			   			WIM_nenContinuousWarning */
                        WIM__u16GetAcuFrequency(WIM__enPlayingSound) == WIM__nenFreq1000)
               {
                  if(WIM__mu8GetAcuQualifier(WIM__enPlayingSound) & WIM__nAcuRequested)
                  {
                     /* Start timer for 1000ms phase */
                     TIMER_vStart(TIMER_nWIM_TimerFreqContWarn, WIM_nTimerDuration_FreqContWarn);
                     WIM__enContPlayingSound = WIM__enPlayingSound;
                  }
               }
               /* set HIL information only in case of valid volume */
               if(WIM__u8Volume > 0)
               {
                  /* Send WIM__u16SoundOutput with current stream id */
                  /* getting struct with acoustic attributes */
                  pstAttr = WIM__pstGetAcuAttr(WIM__enPlayingSound);
                  if (pstAttr != NULL)
                  {
                     if ((uint16)pstAttr->biAcousticType != WIM_nenSeatbeltWarningLevel1
                        && (uint16)pstAttr->biAcousticType != WIM_nenSeatbeltWarningLevel2)
                     {
                        if (WIM__boInsertBreakHIL)
                        {
                           /* getting acoustic attribute of message */
                           u16SoundOutput = WIM_nenNoAcoustic;
                           TIMER_vStart(TIMER_nWIM_HilBreakTimer, WIM_nTimerDuration_HilBreak);
                           WIM__boInsertBreakHIL = False;
                        }
                        else
                        {
                           /* getting acoustic attribute of message */
                           u16SoundOutput = (uint16)pstAttr->biAcousticType;
                        }
                     }
                     else
                     {
                        u16SoundOutput = (uint16)pstAttr->biAcousticType;
                     }
                  }
               }
               else
               {
                  /* no sound output if zero volume */
                  u16SoundOutput = WIM_nenNoAcoustic;
               }
               DPOOL_enSetPoolData(DPOOL_nDataWIM_u16SoundOutput, &u16SoundOutput);

               /* switch On Mute/LowerVolume request signals */
               WIM__vSwitchHUCanSignals(WIM__enPlayingSound, On);
            }
         }
         else
         {
            /* This sound should not start, stop sound immediatley */
            PCMPL_vStopSound(enStreamNo, True);
         }
      } break;
   default:
      {
         /* Don't keep the system awake any longer - MR27470 */
         CRHDL_vReqHdlClearRequest(CRHDL_nReqSMSRES_SoundByWIM);
      } break;
   }
}

/**
* The function initializes the acoustic class
*   @return  void
*   @param   void
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vInitAcoustic(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* set Id's to invalid */
   WIM__enStreamId = PCMPL_nenStrError;
   WIM__enPlayingSound = WIM_nenInvalidMsg;  
   WIM__enRetriggerSound = WIM_nenInvalidMsg;
   WIM__enFrontLatCollWarnPlaying = WIM_nenInvalidMsg;
   WIM__enContPlayingSound = WIM_nenInvalidMsg;
   WIM__boInsertBreakHIL = False;
}

/**
* The function deinitializes the acoustic class
*   @return  void
*   @param   void
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
void WIM__vDeinitAcoustic(void)
{
   WIM__vInitAcoustic();
}

/**
* The function starts an acoustic message.
* It controls the type and volume of the acoustic and mutes the head unit
* if configured by sending specific CAN signals.
*   @return  none
*   @param   enMsg: Identifier of message
*   @author  T.Godemann, Schleissheimer GmbH 
*/
static bool WIM__boStartAcousticIntern(WIM_tenMsg enMsg, WIM_tenMsg enReplacedMsg )
{
   /**********************************************************************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   **********************************************************************************************************************************/
   RSST_tenSoundID enSoundId = RSST_nenInvalidSound;              /* sound output channel                                           */
   uint8 u8VolumeHIL = 0;                                         /* sound volume for HIL                                           */
   uint8 u8Loudness = (uint8)WIM_nenVolumeNoSound;                /* sound loudness (WIM defined volume)                            */
   WIM_tenAcousticType enSoundOutputReq = WIM_nenNoAcoustic;      /* init Information for HIL-ID                                    */
   const WIM__tstViewAttrAcu* pstAttr = NULL;                     /* pointer to acoustic attributes                                 */
   DPOOL_txVEL_tstModelData stVelData;                            /* velocity for warning suppression                               */
   bool boStartSuccessful = True;                                 /* The sound system is running and will process the sound request */
   WIM_tenAcousticType enTypePlayingSound = WIM_nenNoAcoustic;    /* save WIM__enPlayingSound                                       */    
   WIM_tenAcousticType enTypePlayingSoundOld = WIM_nenNoAcoustic; /* save Old WIM__enPlayingSound                                   */
   /**********************************************************************************************************************************
   * FUNCTION CODE
   **********************************************************************************************************************************/
   /* Fetch current Speed from DPOOL */
   DPOOL_enGetPoolData(DPOOL_nDataVEL_stModelData, &stVelData);
   /**
   * Sound Output is only allowed if the IC is correctly programmed or
   * if the velocity is above a certaian limit
   * read parameters */
   enSoundId = WIM__enGetSoundId(enMsg);
   if (/* valid ID? */
       enSoundId != RSST_nenInvalidSound)
   {
      WIM__u8Volume = WIM__u8GetVolume(enMsg, enSoundId, &u8VolumeHIL);
      /* Old PlayingSound valid? */
      if(enReplacedMsg != WIM_nenInvalidMsg)
      {
         pstAttr = WIM__pstGetAcuAttr(enReplacedMsg);
         if(pstAttr != NULL)
         {
            enTypePlayingSoundOld = (WIM_tenAcousticType)pstAttr->biAcousticType;
         }
      }
      /* switch on request */
      WIM__enPlayingSound = enMsg;
      WIM__enRetriggerSound = WIM_nenInvalidMsg;
      pstAttr = WIM__pstGetAcuAttr(WIM__enPlayingSound);
      if(pstAttr != NULL)
      {
         /* getting acoustic attribute of message */
         enTypePlayingSound = (WIM_tenAcousticType)pstAttr->biAcousticType;
      }
      /* only if the output is possible and at least one request for RES_Active is set */
      if ((CRHDL_enStateHdlGetState(CRHDL_nSMSRES_Audio_HW) == CRHDL_nStateOn)
          &&
          (CRHDL_enStateHdlGetCumReq(CRHDL_nSMSRES_Active) == CRHDL_nReqSet))
      {
         /* Note: With implementation of MR27470, WIM keeps the system awake from 
            the start of a sound until its end. It has to be ensured that only sounds
            without the loop feature (param boContPlay == False) are treated this way */
         WIM__enStreamId = SYN__enSoundRequest(                       
                                 SYN__enOutputChannel,  /* sound channel      */
                                 enSoundId,             /* sound Id           */
                                 WIM__u8Volume,         /* sound volume       */
                                 False,                 /* looped sound       */
                                 WIM__vSoundCallback); /* sound end callback */ 
         /* Check if sound could be started */
         if (WIM__enStreamId == PCMPL_nenStrError)
         {
            WIM__enPlayingSound = WIM_nenInvalidMsg;
            boStartSuccessful = False;
         }
         else
         {
            /* is sound type of new acoustic equal to type of old acoustic
             * and not of type SeatbeltWarning ? */
            if(    enTypePlayingSound != WIM_nenSeatbeltWarningLevel1
                && enTypePlayingSound != WIM_nenSeatbeltWarningLevel2
                && enTypePlayingSoundOld == enTypePlayingSound            )
            {
               /* Insert break on HIL signal */
               WIM__boInsertBreakHIL = True;
            }
            else
            {
               WIM__boInsertBreakHIL = False;
            }
            /* Keep system awake if a valid sound should be played and at least 
               one request for RES_Active is set - MR27470 */
            CRHDL_enReqHdlSetRequest(CRHDL_nReqSMSRES_SoundByWIM);
            
            /* HIL output only if PCMPL is ready - MR 29875 */
            /* Sound could be started, output request status for sounds on HIL */
            pstAttr = WIM__pstGetAcuAttr(WIM__enPlayingSound);
            if(pstAttr != NULL)
            {
               /* getting acoustic attribute of message */
               enSoundOutputReq = (WIM_tenAcousticType)pstAttr->biAcousticType;
               u8Loudness = (uint8)pstAttr->biVolume;
            }
            /* valid volume */
            if (WIM__u8Volume > 0)
            {
               WIM__vSoundOutputReqHIL(enSoundOutputReq);
               DPOOL_enSetPoolData(DPOOL_nDataWIM_u8SoundVolume, &u8VolumeHIL);
               DPOOL_enSetPoolData(DPOOL_nDataWIM_u8SoundLoudness, &u8Loudness);
            }
            else
            {
               u8VolumeHIL = 0;
               u8Loudness = WIM_nenVolumeNoSound;
               /* Send WIM__u16SoundOutput with init value (WIM_nenNoAcoustic). */
               DPOOL_enSetPoolData(DPOOL_nDataWIM_u8SoundVolume, &u8VolumeHIL);
               DPOOL_enSetPoolData(DPOOL_nDataWIM_u8SoundLoudness, &u8Loudness);
               WIM__vSoundOutputReqHIL(WIM_nenNoAcoustic);
            }
         }
      }
      else
      {
         WIM__enStreamId = PCMPL_nenStrError;
         WIM__enPlayingSound = WIM_nenInvalidMsg;
         boStartSuccessful = False;
      }
   }
   else
   {
      /* RSST-ID not valid sound could not be started */
      boStartSuccessful = False;
   }
   return boStartSuccessful;
}

/**
* The function starts an acoustic message, request comes from outside AcousticView
* If NCAP sound level 1 or level 2 was requested, only the first request from scheduler
* is processed. SBW uses its own RetriggerSound interface for the further sound requests.
*   @return  none
*   @param   enMsg: Identifier of message
*   @param   enReplacedMsg: Identifier of replaced message
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boStartAcoustic(WIM_tenMsg enMsg, WIM_tenMsg enReplacedMsg)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boReturn = True;
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* start NCAP acoustic only for first sound, others always */
          WIM__enGetToneType(enMsg) != WIM__enIntervalTone
       || WIM__mboGetDisplayedFlag(enMsg) == False)
   {
      /* start PCMPL output */
      boReturn = WIM__boStartAcousticIntern(enMsg, enReplacedMsg);
   }
   return boReturn;
}

/**
* The function stops a running continous acoustic message.
*   @return  none
*   @param   enMsg: Identifier of message
*   @param   boAbort: stops the sound immediately
*   @author  M.Immel, Schleissheimer GmbH 
*/
void WIM__vStopContAcoustic(WIM_tenMsg enMsg, bool boAbort)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* end acoustic */
       WIM__enPlayingSound == enMsg)
   {
      if (/* Stream running? */
          WIM__enStreamId < PCMPL_nenNoOfStreams)
      {
         PCMPL_vStopSound(WIM__enStreamId, boAbort);
      }
   }
}

/**
* The function stops a running acoustic message.
* A mute/volume decrease of the head unit is canceled by sending specific CAN 
* signals (if a delay is specified, the signals are canceled on timer end).
*   @return  void
*   @param   enMsg: Identifier of message
*   @param   boAbort: stops sound immediately
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vStopAcoustic(WIM_tenMsg enMsg, bool boAbort)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* end acoustic */
       WIM__enPlayingSound == enMsg)
   {
      if (/* Stream running? */
          WIM__enStreamId < PCMPL_nenNoOfStreams)
      {
         /* Stop the stream */
         PCMPL_vStopSound(WIM__enStreamId, boAbort);
         if ((boAbort == True) &&  (WIM__enRetriggerSound != enMsg))
         {
            /* report sound on HIL only when immediate stop, else do this from sound callback MR29923 */
            WIM__vSoundOutputReqHIL(WIM_nenNoAcoustic);
         }
      }
   }
   /* if periodic interval sound type */
   if (WIM__enGetToneType(enMsg) == WIM__enPeriodicIntervalTone)
   {
       /* and timer running, stop corresponding timer */
       if (TIMER_u16Read(TIMER_nWIM_TimerFreqCollWarn) > 0)
       {                  
          /* Stop timer for 400ms phase */
          TIMER_vClear(TIMER_nWIM_TimerFreqCollWarn);
       }
       else if (TIMER_u16Read(TIMER_nWIM_TimerFreqContWarn) > 0)
       {
          TIMER_vClear(TIMER_nWIM_TimerFreqContWarn);
       }
   }
}

/**
* Function restarts a currently playing sound.
*   @param   enMsg: Identifier of message
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
void WIM__vRestartAcoustic(WIM_tenMsg enMsg)
{
   /* Only if the current sound is playing the retrigger will
    * be forced by the acoustic class. Otherwise the scheduler
    * must handle the retrigger of the sound.
    */
   if (enMsg == WIM__enGetAcousticMaster())
   {
      /* Store the retrigger sound for the scheduler */
      WIM__enRetriggerSound = enMsg;
      if(WIM__enPlayingSound != WIM_nenInvalidMsg)
      {
          /* Abort the current playing sound */
          WIM__vStopContAcoustic(WIM__enPlayingSound, True);
      }
      else
      {
         /* Start the sonud imeadietly if currently no sound is playing */
         WIM__boStartAcousticIntern(WIM__enRetriggerSound, WIM_nenInvalidMsg);
      }
   }
}

/**
* Function returns the sound id of a message
*   @return  RSST_tenSoundID: id of sound
*   @param   enMsg: Identifier of message
*   @author  T.Godemann, Schleissheimer GmbH 
*/
uint8 WIM__u8GetVolume(WIM_tenMsg enMsg, RSST_tenSoundID enSoundId, uint8* pu8HilVolume)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   const WIM__tstViewAttrAcu* pstAttr;      /* pointer to acoustic attributes */
   uint8 u8Volume;                          /* return value                   */
   AVOL_tenVolParam enVolParam;             /* Volume paramter */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   pstAttr = WIM__pstGetAcuAttr(enMsg);   /* get struct with acoust. attrib. */
   /* Map WIM volume to AVOL volume */
   if (pstAttr != NULL)
   {
      switch (pstAttr->biVolume)
      {
         case WIM_nenVolumeVel:
            enVolParam = AVOL_nWarningVolume_1;
            break;
         case WIM_nenVolumeMax:
            enVolParam = AVOL_nWarningVolume_2;
            break;
         case WIM_nenVolumeMin:
            enVolParam = AVOL_nWarningVolume_3;
            break;
         case WIM_nenVolumeNcap:
            enVolParam = AVOL_nWarningVolume_4;
            break;
         case WIM_nenVolumeLevel2:
            enVolParam = AVOL_nWarningVolume_5;
            break;
         case WIM_nenVolumeLevel3:
            enVolParam = AVOL_nWarningVolume_6;
            break;
         case WIM_nenVolumeLevel4:
            enVolParam = AVOL_nWarningVolume_7;
            break;
         case WIM_nenVolumeLevel5:
            enVolParam = AVOL_nWarningVolume_8;
            break;
         default:
            enVolParam = AVOL_nDefaultVolume;
            /* Error! */
            WIM__vRaiseException(WIM_nErrConfig);
            break;
      }
   }
   else
   {
      enVolParam = AVOL_nDefaultVolume;
      /* Error! */
      WIM__vRaiseException(WIM_nErrConfig);
   }
   /* Fetch volume and parameters from AVOL */
   u8Volume = SYN__u8GetVolume(enSoundId, enVolParam, pu8HilVolume);
   return u8Volume;
}

/**
* Function returns the sound id of a message
*   @return  RSST_tenSoundID: id of sound
*   @param   enMsg: Identifier of message
*   @author  T.Godemann, Schleissheimer GmbH 
*/
RSST_tenSoundID WIM__enGetSoundId(WIM_tenMsg enMsg)
{
   /************************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   *************************************************************************************/
   const WIM__tstViewAttrAcu* pstAttr;                /* pointer to acoustic attrib.   */
   RSST_tenSoundID enSoundID = RSST_nenInvalidSound;  /* return value                  */
   /************************************************************************************
   * FUNCTION CODE
   *************************************************************************************/
   pstAttr = WIM__pstGetAcuAttr(enMsg);   /* get struct with acoust. attrib. */
   if (pstAttr != NULL)
   {  
      switch(/* frequency depends on acoustic type */
             pstAttr->biAcousticType)
      { 
         case WIM_nenFrontalCollisionWarning:
            enSoundID = SYN__nSoundIdFrontCollision;
            break;
         case WIM_nenLateralCollisionWarning:
            enSoundID = SYN__nSoundIdLatCollision;
            break;
         case WIM_nenPriority1Warning:
            enSoundID = SYN__nSoundIdPrio1;
            break;
         case WIM_nenPriority2Warning:
            enSoundID = SYN__nSoundIdPrio2;
            break;
#if(HMI_MODEL == MODEL_PLCD)
         case WIM_nenEOSWarning:
            enSoundID = SYN__nSoundIdEOS;
            break;
#endif
         case WIM_nenContinuousWarning:
            enSoundID = SYN__nSoundIdContinuous;
            break;
         case WIM_nenAcknowledgement:
            enSoundID = SYN__nSoundIdAcknowledgement;
            break;
         case WIM_nenAttentionAssistWarning:
            enSoundID = SYN__nSoundIdAttention;
            break;
         case WIM_nenSeatbeltWarningLevel1:
            enSoundID = SYN__nSoundIdBeltWarnLevel1;
            break;
         case WIM_nenSeatbeltWarningLevel2:
            enSoundID = SYN__nSoundIdBeltWarnLevel2;
            break;
         case WIM_nenRearSeatbeltWarning:
            enSoundID = SYN__nSoundIdRearBeltWarn;
            break;
         default: 
            /* Error! */
            WIM__vRaiseException(WIM_nErrConfig); 
            break;
      }
   }
   else
   {
      /* Error! */
      WIM__vRaiseException(WIM_nErrConfig);
   }
   return enSoundID;
}

/**
* The function delivers the acoustic frequency. The frequency can be a beep
* (200/200) or a gong (800/200).
*   @return  uint16: frequency (SFG) or WIM__nInvalidFreq on error
*   @param   enMsg: Identifier of message
*   @author  T.Godemann, Schleissheimer GmbH 
*/
uint16 WIM__u16GetAcuFrequency(WIM_tenMsg enMsg)
{
   /*********************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   **********************************************************************************/
   const WIM__tstViewAttrAcu* pstAttr;          /* pointer to acoustic attributes   */
   uint16 u16Frequency = WIM__nenInvalidFreq;   /* sound frequency                  */
   /*********************************************************************************
   * FUNCTION CODE
   **********************************************************************************/
   pstAttr = WIM__pstGetAcuAttr(enMsg);   /* get struct with acoust. attrib. */
   if (pstAttr != NULL)
   {  
      switch(/* frequency depends on acoustic type */
             pstAttr->biAcousticType)
      {
         case WIM_nenFrontalCollisionWarning:
         case WIM_nenLateralCollisionWarning:
            u16Frequency = WIM__nenFreq400;
            break;
         case WIM_nenContinuousWarning:
            u16Frequency = WIM__nenFreq1000;
            break;
         default: 
            break;
      }
   }
   else
   {
      /* Error! */
      WIM__vRaiseException(WIM_nErrConfig);
   }
   return u16Frequency;
}

/**
* Function returns True, if an acoustic output needs to be synchronized with
* a running system frequency.
*   @return  True: sync. necessary, False: no sync. required
*   @param   enMsg: Identifier of message
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boSyncAcoustic(WIM_tenMsg enMsg)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   const WIM__tstViewAttrAcu* pstAttr;      /* pointer to acoustic attributes */
   bool boReturn = False;                   /* return value                   */
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   pstAttr = WIM__pstGetAcuAttr(enMsg);   /* get struct with acoust. attrib. */
   if (pstAttr)
   {  
      /* does acoustic frequency need to be synchronized with system clock? */
      boReturn = (pstAttr->biSfgSyncAcoustic != Off);
   }
   else
   {
      /* error! */
      WIM__vRaiseException(WIM_nErrConfig);
   }
   return boReturn;
}

/**
* Function returns True, if an acoustic is limited in time
*   @return  WIM__tenToneTypes: tone type of the specified message
*   @param   enMsg: Identifier of message
*   @author  D. Gottwalles, Schleissheimer GmbH 
*/
WIM__tenToneTypes WIM__enGetToneType(WIM_tenMsg enMsg)
{
   /*************************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   **************************************************************************************/
   const WIM__tstViewAttrAcu* pstAttr;                /* pointer to acoustic attributes */
   WIM__tenToneTypes enToneType = WIM__enSingleTone;  /* set intial single tone type    */
   /*************************************************************************************
   * FUNCTION CODE
   **************************************************************************************/
   pstAttr = WIM__pstGetAcuAttr(enMsg);   /* get struct with acoust. attrib. */
   if (pstAttr)
   {  
      switch(/* depends on acoustic type */
             pstAttr->biAcousticType)
      {
         /* single event acoustics */
         case WIM_nenPriority1Warning:
         case WIM_nenPriority2Warning:
         case WIM_nenAcknowledgement:
         case WIM_nenAttentionAssistWarning:
         case WIM_nenRearSeatbeltWarning:
            enToneType = WIM__enSingleTone;
            break;
         case WIM_nenSeatbeltWarningLevel1:
         case WIM_nenSeatbeltWarningLevel2:
            enToneType = WIM__enIntervalTone;
            break;
         case WIM_nenFrontalCollisionWarning:
         case WIM_nenLateralCollisionWarning:
         case WIM_nenContinuousWarning:
            enToneType = WIM__enPeriodicIntervalTone;
            break;
         default:
            enToneType = WIM__enSingleTone;
            /* software is not correctly configured, unknown tone type */
            WIM__vRaiseException(WIM_nWrongParameter);            
            break;
      }
   }
   return enToneType;
}
 
/**
* Called by Scheduler to switch HU Request signals
*   @return  void
*   @param   enMsg: Identifier of message, boOn: switch True=On/False=Off
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vSwitchHUCanSignals(WIM_tenMsg enMsg, bool boOn)
{
   /****************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   *****************************************************************************/
   const WIM__tstViewAttrAcu* pstAttr;       /* pointer to acoustic attributes */
   const WIM__tstStateAttr* pstStateAttr;    /* pointer to warning attributes  */
   WIM__tenAcuTypes enAcuType;               /* variable for acoustic type     */
   /****************************************************************************
   * FUNCTION CODE
   *****************************************************************************/
   if(enMsg <= WIM_nenLastMsg)
   {
      /* get struct with acoust. attrib. */
      pstAttr = WIM__pstGetAcuAttr(enMsg);
      pstStateAttr = (WIM__tstStateAttr*)WIM__mGetMsgPropertyTable[enMsg].pvStateAttr;
      if(pstStateAttr)
      {
         if(WIM__mGetMsgPropertyTable[enMsg].enMsgType == WIM__nAcoustic)
         {
            enAcuType = WIM__nActiveDspAsync;
         }
         else
         {
            enAcuType = (WIM__tenAcuTypes)pstStateAttr->bi2Acoustic;
         }
      }
      else
      {
         enAcuType = WIM__nAcuInactive;
      }
      if (pstAttr)
      {
         if (pstAttr->biMuteHeadUnit)
         {
            /* mute HU volume */
            WIM__vSetMuteRequest_GC(enAcuType, boOn);
         }
         else if (pstAttr->biDecVolHeadUnit)
         {
            /* lower HU volume */
            WIM__vSetVolDecRequest_GC(enAcuType, boOn);
         }
         else 
         {
            /* set both requests to OFF */
            WIM__vSetMuteRequest_GC(enAcuType, Off);
            WIM__vSetVolDecRequest_GC(enAcuType, Off);
         }
      }
      else
      {
         /* set both requests to OFF */
         WIM__vSetMuteRequest_GC(enAcuType, Off);
         WIM__vSetVolDecRequest_GC(enAcuType, Off);
      }
   }
   else
   {
      /* set both requests to OFF */
      WIM__vSetMuteRequest_GC(WIM__nAcuInactive, Off);
      WIM__vSetVolDecRequest_GC(WIM__nAcuInactive, Off);
   }
}

/**
* Called by Scheduler to switch HIL signals on DPOOL
*   @return  void
*   @param   enSoundOutputReq: Current requested sound type
*   @author  D. Gottwalles, Schleissheimer GmbH 
*/
void WIM__vSoundOutputReqHIL(WIM_tenAcousticType enSoundOutputReq)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint16 u16SoundOutputReq = (uint16)enSoundOutputReq;
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* Read current DPOOL value */
   DPOOL_enGetPoolData(DPOOL_nDataWIM_u16SoundOutputReq, &u16SoundOutputReq);
   /* Write only if value has changed */
   if(u16SoundOutputReq != (uint16)enSoundOutputReq)
   {
      u16SoundOutputReq = (uint16)enSoundOutputReq;
      DPOOL_enSetPoolData(DPOOL_nDataWIM_u16SoundOutputReq, &u16SoundOutputReq);
      /* Start signal length timer fo all sound types which show only a peak 
       * on HIL and not the real length
       */
      if(enSoundOutputReq == WIM_nenSeatbeltWarningLevel1 ||
         enSoundOutputReq == WIM_nenSeatbeltWarningLevel2)
      {
         WIM__vStartTimer(WIM__nTimerHilSignal, WIM_nenInvalidMsg);
      }
   }
}

/**
* Retruns the current playing sound, this output coresponds with 
* the speaker output.
*   @return  WIM_tenMsg
*   @author  D. Gottwalles, Schleissheimer GmbH 
*/
WIM_tenMsg WIM_enGetPlayingSound(void)
{
   return WIM__enPlayingSound;
}
