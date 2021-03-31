/******************************************************************************
*=====================    Copyright by Continental AG    ======================
*******************************************************************************
* Titel        : WIM__CanInterface.c
*
* Description  : Class handling CAN signals WIM is receiving and transmitting
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
* Archive: $Log: WIM__CanInterface.c  $
* Archive: Initial revision for VS11 (Based on 213IC-EL E009.4rel)
*
* Archive: Revision 1.3.1.5 2014/04/08 17:19:24CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 40060 : 213/AC, WIM: Sending of SLACK HIL ID on CAN
* Archive: Revision 1.3.1.4 2014/03/28 15:26:25CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 39277 : WIM: Sending of WIM HIL ID on CAN
* Archive: Revision 1.3.1.3 2013/05/17 13:37:42CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 33414: BR213/AC, E004, WIM: Takeover of the latest changes from BR222/BR205
* Archive: Revision 1.3.1.2 2012/11/21 12:48:06CET Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3AC/project.pj
* Archive: Revision 1.2 2012/11/21 12:48:06CET Immel-EXT, Marc (uid37561) 
* Archive: Migration of WIM-AC from PVCS to MKS
* Archive: - used release: DC.SW.PAC.WIM_205IC_AC_COMMON_VarW.V01.00.pre17
* Archive: Revision 1.1 2012/02/21 11:46:48CET uid37556 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3AC/project.pj
* 
*    Rev 1.7   Aug 08 2012 12:07:58   SCHL_Dirk.Gottwalles
* DC MR 27477: W222, E007/AC, WIM: Change of Partial Lowering and Mute signal Pt. II - �LP2994
* DC MR 27613: W222, E007/GC, WIM: Sync acoustic is delayed too long
* 
*    Rev 1.6   Jun 14 2012 16:19:04   SCHL_Dirk.Gottwalles
* DC MR 26329: W222, E007/GC, WIM: Change of Prio1Mute and Lowering times - �LP2873
* DC MR 25901: W222, E007/AC, WIM: Change of Prio1Mute and Lowering times - �LP2873
* DC MR 26324: W222, E007/AC, WIM: Boundary and Retrigger condition of protocol_class_2
* 
*    Rev 1.5   Apr 05 2012 13:35:10   SCHL_Dirk.Gottwalles
* DC MR 24870: W222, E007/GC, WIM: Implement changes from Review ORM2907
* DC MR 25007: W222, E007/GC, WIM: Displacement of handling messages - WDM20280
* DC MR 25041: Do not specify message propagation in message description files
* DC MR 25095: W222, E007/GC, WIM: Improvement of Timer accuracy for display role - WDM 25704
* DC MR 25034: Reduction of lag times in case of vehicle locked
* DC MR 25393: W222, E007/GC, WIM: No cancel of interval acoustic - WDM31269, �LP2895
* DC MR 24871: W222, E007/AC, WIM: Implement changes from Review ORM2907
* 
*    Rev 1.4   Feb 22 2012 17:54:34   SCHL_Dirk.Gottwalles
* DC MR 24332: W222, E007/GC, WIM: Warnings can not be acknowledged with Nview active
* DC MR 24324: W222, E007/AC, WIM: Remove unused code parts from secondary mute request
* DC MR 24333: W222, E007/GC, WIM: HIL output for requested sound not working
* DC MR 24043: Move tube request from WIM to WarningStandard.xml
* DC MR 23682: W222, E007/GC, WIM: Acousic only messsage does not block display WDM21148
* DC MR 24086: W222, E007/GC, WIM: Short rest after warning display is not always 5 seconds
* 
*    Rev 1.3   Jan 13 2012 16:18:54   SCHL_Dirk.Gottwalles
* DC MR 24093: W222, E007/GC, WIM: Acoustic warning does not block display - WDM20499
* DC MR 23683: W222, E007/GC, WIM: Sync acoustic is cancelled by async acoustic WDM21143
* DC MR 24088: W222, E007/GC, WIM: Warning blocks display WDM22837, WDM23219
* DC MR 24089: W222,E007,AC, WIM: New configuration values Chauffeur_Avl and ShiftStyle_Variant
* DC MR 24343: W222, E007/AC, WIM: Patch for 0x2000BC and 0x2000C1 (Country coding), WDM23191
* 
*    Rev 1.2   Jul 29 2011 14:06:46   SCHL_Dirk.Gottwalles
* DC MR 22188: Controller containers should not call methods of their strategies
* DC MR 22573: E006/AC DPOOL Define Data Braces, remove compiler warning
* DC MR 22334: BR222: SBW sound in Phase 4 WDM10279
* DC MR 22312: W222, E006/AC, WIM: Mute and partial acoutic lowering delay, OPL528
* 
*    Rev 1.1   Jun 11 2010 14:01:08   SCHL_Thomas.Godemann
* DC MR20480 AC, Startup MR for Modul WIM in E001
* DC MR20481 GC, Startup MR for Modul WIM in E001
* 
*    Rev 1.0   Jun 07 2010 13:19:18   SCHL_Thomas.Godemann
* Initial revision.
* 
* --------------------------------------------------------------------------
* Date      | Author | Reason     | Change
* --------------------------------------------------------------------------
* 10-06-03    LarGru   MR20480      Initial revision for W222
*
****************************************************************************/

/****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "cdef.h"
#include "cdef_deprecated.h"
/* Foreign headerfiles */

/* Own headerfiles */
#include "WIM_c1.h"
#include "WIM__CanInterface.h"
#include "WIM__Types.h"

/******************************************************************************
* GLOBAL DEFINITIONS
*******************************************************************************/

#define WIM__nArraySize(x) (sizeof(x) / sizeof((x)[0]))

/**
 * Threshold value for privacy pop up pressed time
 */
#define WIM__nPrivacy_Popup_Max_Pressed_Time    4

/**
 * Threshold value for end call request
 */
#define WIM__nEndCall_Request_Counter           4

/************************************************************************/
/* HIL Id's for privacy pop up warning                                  */
/************************************************************************/

#ifndef WIM__nPrivacyPopup_MBenz
   #define WIM__nPrivacyPopup_MBenz          0x20F3C200
#endif

#ifndef WIM__nPrivacyPopup_Freightliner
   #define WIM__nPrivacyPopup_Freightliner   0x20F3E000
#endif

const uint32 WIM__aPrivacyPopUpWarningIds[] =
{
   WIM__nPrivacyPopup_MBenz,
   WIM__nPrivacyPopup_Freightliner
};

/************************************************************************/
/* HIL Id's for E-Call warning                                          */
/************************************************************************/

const uint32 WIM__aECallWarningIds[] = 
{
   0x20F3AA00,
   0x20F3AB00,
   0x20F3AC00,
   0x20F3AD00,
   0x20F3AE00,
   0x20F3B000
};

/******************************************************************************
* FILE LOCAL DEFINITIONS
*******************************************************************************/

/**
* Privacy pop up pressed time counter
*/
static uint8 WIM__u8PrivacyPopUpPressedTime = 0x0;

/**
 * Privacy pop up value for sending on CAN
 */
static uint16 WIM__u16PrivacyPopUpStateToSendOnCan = 0x0;

/**
 * E-call pressed time counter
 */
static uint8 WIM__u8ECallPressedTime = 0x0;

/**
 * E-call value for sending on CAN
 */
static bool WIM__boECallEndValueToSendOnCan = Off;

/**
* delay time for mute/lower CAN signal (HU) in ms in case of async acoustic
*/
static uint16 WIM__u16DelayAsyncOff;

/**
* structures storing request bits for both CAn signals, WIM internal
* and external (received from CAN ECU MPM)
*/
static struct
{
   /**
   * WIM internal request for lowering HU volume 
   * @range  boolean
   * @values True/False 
   */
   uint8 biVdecReqIntern : 1;

   /**
   * WIM internal request for muting HU volume 
   * @range  boolean
   * @values True/False 
   */
   uint8 biMuteReqIntern : 1;

   /**
   * external request for for muting HU volume
   * @range  boolean
   * @values True/False 
   */
   uint8 biMuteReqExtern : 1;

   /**
   * internal PrivacyPopUp request
   * @range  boolean
   * @values True/False
   */
   uint8 biPrivacyPopUpReqIntern : 1;

   /**
   * internal Ecall request
   * @range  boolean
   * @values True/False
   */
   uint8 biEcallReqIntern : 1;
} WIM__stRequest;

/**
* HIL ID of currently displayed warning
*/
static uint32 WIM__u32CanHilId;

/**
* HIL ID of currently displayed slack
*/
static uint32 WIM__u16CanSlackHilId;

/******************************************************************************
* FILE LOCAL FUNCTION PROTOTYPES
*******************************************************************************/
static void WIM__vReadCanSignals(void);

static bool WIM_boInPrivacyPopUpFamily(const uint32 u32DisplayMessage);

/******************************************************************************
* FUNCTION DEFINITIONS
*******************************************************************************/

/**
* Reads CAN input signals and sets request bits
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
static void WIM__vReadCanSignals(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   WIM__mCreateAudioMute_1();         /* create CAN signal struct             */
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* read mute signal from CAN */
   WIM__mGetAudioMute_1();
   /* volume decrease request from MPM */
   if (   (WIM__mboToAudioMute_1 == WIM__nPassive)
       && (WIM__mboFvAudioMute_1 != WIM__nPassive) )
   {
      /* set request as received from CAN signal */
      WIM__stRequest.biMuteReqExtern = WIM__mboAudioMute_1;   
   }
   else
   {
      /* in case of time-out or signal not available, clear request */
      WIM__stRequest.biMuteReqExtern = Off;   
   }
}

/**
 * @brief Returns True if display message is privacy popup warning, False - otherwise
 * @param u32DisplayMessage Display message (in format 0x2xxxxxxx)
 * @return True if display message is privacy popup warning, False - otherwise
 */
static bool WIM_boInPrivacyPopUpFamily(const uint32 u32DisplayMessage)
{
   /******************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   *******************************************************************************/
   uint32 u32Idx, u32ArraySize;
   bool boIsPrivacyPopupWarning = False;

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   u32ArraySize = WIM__nArraySize(WIM__aPrivacyPopUpWarningIds);
   for (u32Idx = 0; u32Idx < u32ArraySize; u32Idx++)
   {
      if (WIM__aPrivacyPopUpWarningIds[u32Idx] == u32DisplayMessage)
      {
         boIsPrivacyPopupWarning = True;
         break;
      }
   }

   return boIsPrivacyPopupWarning;
}

/**
* Initialisation of the the class
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vCanInterfaceInit(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* get the mute/volume decrease delays for HU CAN signals from EEPROM */
   WIM__u16DelayAsyncOff = WIM__nAsyncMuteLowerDelay * WIM__nDelayTmFactor;
   /* clear all request bits at startup */
   WIM__stRequest.biMuteReqExtern = Off; 
   WIM__stRequest.biVdecReqIntern = Off;   
   WIM__stRequest.biMuteReqIntern = Off;
   WIM__u32CanHilId = 0;
   WIM__u16CanSlackHilId = 0;
}

/**
* Deinitialisation of the class
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vCanInterfaceDeinit(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* reset the CAN signals to OFF */
   WIM__vCanInterfaceInitTxCan();
   /* cancel the delay timer */
   WIM__vCancelTimer(WIM__nTimerReqOffDelay);
}


/**
* send "mute"/"volume decrease" to head-unit
*   @return  void
*   @param   boSwitchMute - Send value for the mute signal
*   @param   boSwitchVolDec - Send value for the decrease signal
*   @param   u32WimHilId - HIL ID of currently displayed warning
*   @param   u16SlackHilId - HIL ID of currently displayed slack
*   @param   u16PrivacyPopUpState - Privacy pop up state for sending value on CAN
*   @param   boEcallEnd - E call state for sending value on CAN
*   @author  D.Gottwallse, Schleissheimer GmbH 
*/
void WIM__vTransmitHeadUnitSig(
    bool boSwitchMute,
    bool boSwitchVolDec,
    uint32 u32WimHilId,
    uint16 u16SlackHilId,
    uint16 u16PrivacyPopUpState,
    bool boEcallEnd)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint8 u8My_AcustWarn_Actv_IC;
   uint8 u8My_WarnPrio1_Mute_Rq;
   uint8 u8My_ECall_End_Rq;
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   u8My_AcustWarn_Actv_IC = (uint8)boSwitchVolDec;
   u8My_WarnPrio1_Mute_Rq = (uint8)boSwitchMute;
   u8My_ECall_End_Rq = (uint8)boEcallEnd;
   Com_UpdateShadowSignal(Com_AcustWarn_Actv_IC, &u8My_AcustWarn_Actv_IC);
   Com_UpdateShadowSignal(Com_WarnPrio1_Mute_Rq, &u8My_WarnPrio1_Mute_Rq);
   Com_UpdateShadowSignal(Com_MBCall_End_Call_Rq, &u8My_ECall_End_Rq);
   Com_UpdateShadowSignal(Com_IC_Msg_Disp_Stat, &u32WimHilId);
   Com_UpdateShadowSignal(Com_IC_Msg_Disp_Stat2, &u16SlackHilId);
   Com_UpdateShadowSignal(Com_MBCall_Popup_Cnfrm, &u16PrivacyPopUpState);
   Com_SendSignalGroup(Com_Grp_Warnings_IC);   
}

/**
* set WIM Hil ID to head-unit
*   @return  void
*   @param   u32WimHilId - HIL ID of currently displayed warning
*   @author  A.Wagner, Schleissheimer GmbH 
*/
void WIM__vSetHeadUnitHilId(uint32 u32WimHilId)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   WIM__u32CanHilId = u32WimHilId;
}

/**
* set Slack Hil ID to head-unit
*   @return  void
*   @param   u16SlackHilId - HIL ID of currently displayed slack
*   @author  A.Wagner, Schleissheimer GmbH 
*/
void WIM__vSetHeadUnitSlackHilId(uint16 u16SlackHilId)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   WIM__u16CanSlackHilId = u16SlackHilId;
}

/**
* Initialisation of CAN transmit signals
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vCanInterfaceInitTxCan(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* init CAN send signals                                                   */
   WIM__vTransmitHeadUnitSig(Off, Off, 0, 0, 0, Off);
}

/**
* Timer callback-function
* Called if the delay timer for HU mute/volume decrease has elapsed. Depending
* on the CorrTag parameter the CAN signals are cleared
*   @return  void
*   @param   enTimer: Identifier of timer, xCorrTag: correlation tag
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vClearHuTxSignal(WIM__tenTimer enTimer, WIM__txCorrTag xCorrTag)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   xCorrTag = xCorrTag; /* to avoid compiler warning */
   if (enTimer == WIM__nTimerReqOffDelay)
   {
      /* delay counter has elapsed: clear both request flags (only one can be
         active at a time, so dont't care which one */
      WIM__stRequest.biVdecReqIntern = WIM__stRequest.biMuteReqIntern = Off;
   }
   else
   {
      WIM__vRaiseException(WIM_nWrongParameter);
   }
}

/**
* The function sets the internal request 
* A mute/volume decrease of the head unit is canceled by sending specific CAN 
* signals (if a delay is specified, the signals are canceled on timer end).
*   @return  void
*   @param   boOn: True = set request, False = clear request
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vSetVolDecRequest_AC(WIM__tenAcuQualifier enAcuType, bool boOn)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* set request */
       boOn)
   {
      /* only one of both request can be active at a time 
         current WIM caoustic requests a volume decrease, the acoustic before 
         may have had a mute request, which is canceled now */
      WIM__stRequest.biVdecReqIntern = On;
      WIM__stRequest.biMuteReqIntern = Off;
      WIM__vCancelTimer(WIM__nTimerReqOffDelay);
      /* The timer is started with the beginning of the sound 
         for a fixed period length the signal is turned on */
      if(WIM__u16DelayAsyncOff > 0)
      {
         WIM__vStartTimerEx(WIM__nTimerReqOffDelay, 0, WIM__u16DelayAsyncOff);
      }
   }
   else
   {
      /* clear request */
      /* 
       * The signal is switched on for a fixed period of time, the sound 
       * length will not affect the moment when the signal is switched off.
       * This will be done via the Timer event of timer WIM__nTimerReqOffDelay.
       */
   }
}
 
/**
* The function sets the internal request 
* A mute/volume decrease of the head unit is canceled by sending specific CAN 
* signals (if a delay is specified, the signals are canceled on timer end).
*   @return  void
*   @param   boOn: True = set request, False = clear request
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vSetMuteRequest_AC(WIM__tenAcuQualifier enAcuType, bool boOn)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* set request */
       boOn)
   {
      /* only one of both request can be active at a time 
         current WIM acoustic requests a mute, the acoustic before 
         may have had a volume decrease request, which is canceled now */
      WIM__stRequest.biMuteReqIntern = On;
      WIM__stRequest.biVdecReqIntern = Off;
      WIM__vCancelTimer(WIM__nTimerReqOffDelay);

      /* The timer is started with the beginning of the sound 
         for a fixed period length the signal is turned on */
      if(WIM__u16DelayAsyncOff > 0)
      {
         WIM__vStartTimerEx(WIM__nTimerReqOffDelay, 0, WIM__u16DelayAsyncOff);
      }
   }
   else
   {
      /* clear request */
      /* 
       * The signal is switched on for a fixed period of time, the sound 
       * length will not affect the moment when the signal is switched off.
       * This will be done via the Timer event of timer WIM__nTimerReqOffDelay.
       */
   }
}

/**
* Cyclic function. Processes CAN input signals and controls transmission of
* output signals
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vCanInterfaceMain(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* evaluate CAN Signals from MPM */
   WIM__vReadCanSignals();
   /*** transmit the CAN signals depending on request bits */
   /* mute request? */
   if (   WIM__stRequest.biMuteReqIntern == 1
       || WIM__stRequest.biMuteReqExtern == 1 )
   {
      /* mute request is active, send signal */
      WIM__vTransmitHeadUnitSig(
         On, Off, WIM__u32CanHilId, WIM__u16CanSlackHilId, WIM__u16PrivacyPopUpStateToSendOnCan, WIM__boECallEndValueToSendOnCan);
   }
   else
   {
      if ( /* volume decrease request? */
           WIM__stRequest.biVdecReqIntern )
      {
         /* volume decrease request is active, send signal */
         WIM__vTransmitHeadUnitSig(
            Off, On, WIM__u32CanHilId, WIM__u16CanSlackHilId, WIM__u16PrivacyPopUpStateToSendOnCan, WIM__boECallEndValueToSendOnCan);
      }
      else
      {
         /* no request is active, both signals are off */
         WIM__vTransmitHeadUnitSig(
            Off, Off, WIM__u32CanHilId, WIM__u16CanSlackHilId, WIM__u16PrivacyPopUpStateToSendOnCan, WIM__boECallEndValueToSendOnCan);
      }
   }
}

/**
* Find out whether this warning is related to e-call warnings
*    @param u32DisplayMessageId Display message Id
*    @return On, if this warning is related to e-call warnings, Off otherwise
*    @author D.Vinevtsev, Schleissheimer GmbH
*/
static bool WIM_boIsECallWarning(uint32 u32DisplayMessageId)
{
   /******************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   *******************************************************************************/
   uint32 idx, size;
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   size = WIM__nArraySize(WIM__aECallWarningIds);
   for (idx = 0; idx < size; ++idx)
   {
      if (WIM__aECallWarningIds[idx] == u32DisplayMessageId)
         return On;
   }

   return Off;
}

/**
 * Indicates Com_Grp_Warnings_IC signal group transmission was finished
 */
extern FUNC(void, COM_APPL_CODE) WIM_vMBCallPopupCnfrmTxConfirmation(void)
{   
   if (!WIM__stRequest.biPrivacyPopUpReqIntern)
      return;

   if (WIM__u8PrivacyPopUpPressedTime != 0)
   {
      WIM__u8PrivacyPopUpPressedTime--;
   }
   else
   {
      WIM__u8PrivacyPopUpPressedTime = WIM__nPrivacy_Popup_Max_Pressed_Time;
      WIM__stRequest.biPrivacyPopUpReqIntern = 0x0;
      WIM__u16PrivacyPopUpStateToSendOnCan = 0x00;
   }
}

/**
 * Callback function impl for End E-Call request notification
 */
extern FUNC(void, COM_APPL_CODE) WIM_vMBCallTxConfirmation(void)
{
   /******************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   *******************************************************************************/
   bool boHeadUnitAvl;   

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   boHeadUnitAvl = EEH_boGetHeadunit();

   /* if no head-unit is available in the car and there is a e-call related warning on display */
   if (boHeadUnitAvl || !WIM__stRequest.biEcallReqIntern)
      return;

   if (WIM__u8ECallPressedTime != 0)
   {
      WIM__u8ECallPressedTime--;
   }
   else
   {
      WIM__u8ECallPressedTime = WIM__nEndCall_Request_Counter;
      WIM__stRequest.biEcallReqIntern = 0x0;
      WIM__boECallEndValueToSendOnCan = 0x00;
   }
}

/**
 * Get privacy pop up value for sending on CAN
 *   @param boPrivacyPopupIsInDisplay True, if privacy pop up warning is on the display, False - otherwise
 *   @param stPhoneCallKey Phone call key for privacy pop up state
 *   @return Privacy pop up value for sending on CAN
 *   @author D.Vinevtsev, Schleissheimer GmbH
 */
static uint16 WIM_u16GetPrivacyPopUpCanValue(bool boPrivacyPopupIsInDisplay, WIM_tstPhoneCallKey* stPhoneCallKey)
{
   /* Privacy pop up value for sending on CAN */
   uint16 u16PrivacyPopUpCanValue;
   
   /* privacy pop up is in the display */
   if (boPrivacyPopupIsInDisplay)
   {
      /* Warning confirmed with 'Yes' */
      if (stPhoneCallKey->boConfirm)
      {
         u16PrivacyPopUpCanValue = (uint16)0x02;
      }
      else if (stPhoneCallKey->boReject)
      {
         /* Warning rejected with 'No' */
         u16PrivacyPopUpCanValue = (uint16)0x03;
      }
      else if (stPhoneCallKey->boBack)
      {
         /* Warning rejected with 'Back' */
         u16PrivacyPopUpCanValue = (uint16)0x00;
      }
      else
      {
         /* Warning is on the display, but neither confirmation nor rejection was not */
         u16PrivacyPopUpCanValue = (uint16)0x01;
      }
   } 
   else
   {
      /* There is no privacy pop up warning on the display */
      u16PrivacyPopUpCanValue = (uint16)0x00;
   }

   return u16PrivacyPopUpCanValue;
}

/**
 * Process privacy popup warning
 *   @return void
 *   @param enEvent received event
 *   @author D.Vinevtsev, Schleissheimer GmbH
 */
void WIM__vProcessMBCallPrivacyPopup(EVHD_tenReceiveEvent enEvent)
{
   /******************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   *******************************************************************************/
   DPOOL_txWIM_tstPhoneCallKey stPhoneCall;
   bool boPrivacyPopupIsInDisplay;
   uint32 u32CurrentDisplayMsg;

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* Event type is correct and DPOOL data is valid, return otherwise */
      enEvent != EV_DPOOL_Always_WIM_stPhoneCallKey_WIM_vDoHmiEvents
      || DPOOL_enGetPoolData(DPOOL_nDataWIM_stPhoneCallKey, &stPhoneCall) != E_DATA_OK)
      return;

   WIM__stRequest.biEcallReqIntern = stPhoneCall.boECall;
   WIM__stRequest.biPrivacyPopUpReqIntern = (stPhoneCall.boConfirm || stPhoneCall.boReject)
      ? True
      : False;

   /* Let's find out whether the privacy pop up warning is on the display  */
   u32CurrentDisplayMsg = WIM_u32GetCurrentDisplayMsg();
   boPrivacyPopupIsInDisplay = WIM_boInPrivacyPopUpFamily(u32CurrentDisplayMsg);

   /* Set privacy pop up value for sending on CAN */
   WIM__u16PrivacyPopUpStateToSendOnCan = WIM_u16GetPrivacyPopUpCanValue(boPrivacyPopupIsInDisplay, &stPhoneCall);
   if (WIM__u16PrivacyPopUpStateToSendOnCan != 0)
      WIM__u8PrivacyPopUpPressedTime = WIM__nPrivacy_Popup_Max_Pressed_Time;

   /* Set E-call end value for sending on CAN */
   WIM__boECallEndValueToSendOnCan = stPhoneCall.boECall == True
      ? On
      : Off;
   if (WIM__boECallEndValueToSendOnCan)
      WIM__u8ECallPressedTime = WIM__nEndCall_Request_Counter;
}

/**
* Set CAN value if privacy popup warning gets activated from turn-on-condition
*   @return bool
*   @param boPrivacyPopUpActive True, if privacy pop up active, False - otherwise
*   @author A.Wagner, Schleissheimer GmbH
*/
bool WIM_boSetPrivacyPopUpCanValue(bool boPrivacyPopUpActive)
{
   bool boSet = False;

   /* If warning is on the display, set the value = 0x01 */
   if (boPrivacyPopUpActive)
   {
      WIM__u16PrivacyPopUpStateToSendOnCan = 0x01;
      boSet = True;
   }
   else if (!WIM__stRequest.biPrivacyPopUpReqIntern)
   {
      /* if warning is not on the display, set the value = 0x00 */
      WIM__u16PrivacyPopUpStateToSendOnCan = 0x00;
      boSet = False;
   }

   return boSet;
}
