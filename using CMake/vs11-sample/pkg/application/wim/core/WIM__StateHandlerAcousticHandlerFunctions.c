/******************************************************************************
*=====================      Copyright by Continental AG      ==================
*******************************************************************************
* Titel        : WIM__StateHandlerAcousticHandlerFunctions.c
*
* Description  : Definitions of acoustic state machine event-handling functions
*
* Responsible  : M.Lazarev, Schleissheimer GmbH
*
* Guidelines   : SMK 3.3  
*
* Template name: OOLite Codefile, Revision 1.0
*
* CASE-Tool    : Together Controlcenter, Version 6.2
*
* Revision List: (Will be filled by PVCS)
* Archive: $Log: WIM__StateHandlerAcousticHandlerFunctions.c  $
* Archive: Revision 1.10 2014/08/21 18:15:54CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 42268 : WIM: Sound of synchronous acoustic is played out after AutoQuit or ManuQuit and another Warning gets active - WDM354
* Archive: Revision 1.9 2014/08/13 18:28:00CEST Immel-EXT, Marc (uid37561) 
* Archive: - removed unknown tokes at the start of the file
* Archive: Revision 1.8 2014/08/13 17:17:06CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 42077: WIM: SLACK is displayed with noise
* Archive: DC MR 41987: WIM: Break of 100ms is seen in case of acoustic replacement async to async - #10894
* Archive: DC MR 41983: WIM: Start of "BSM Warnton" output is delayed >300ms - WDM 337
* Archive: DC MR 41981: BR213-EL/E008, WIM: Minimum display time are extended after retriggering - WDM 348
* Archive: DC MR 41975: WIM: Change HIL timing for single line acknowledgements according to customer - WDM257
* Archive: Revision 1.7 2014/07/18 16:09:21CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 41425 : WIM: Corrections of acoustic issues found in system test
* Archive: Revision 1.6 2014/06/06 18:58:38CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 40669 : WIM: NCAP acoustic should be interruptable by any synchronous acoustic with urgent
* Archive: DC MR 40303 : WIM: Correct issues in acoustic state handling and scheduling found in system test E015
* Archive: Revision 1.5 2014/03/21 13:03:56CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 39524 : WIM: Correct interval acoustic handling and HIL feedback
* Archive: DC MR 39163 : WIM: Overcome illegal memory access and correction of HMI acoustics notification
* Archive: DC MR 40021 : WIM: Sound of FCW warning is not retriggered after reset
* Archive: Revision 1.4 2014/01/20 18:25:43CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 36462: WIM: Implement new scheduling and state handling for acoustic part
* Archive: Revision 1.3 2014/01/03 10:40:20CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 36462 : WIM: Implement new scheduling and state handling for acoustic part
* Archive: Revision 1.2 2013/12/06 17:54:13CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 37353 : WIM: Implement changes on door warning acoustics after clarification with customer - OPL 2064
* Archive: Revision 1.1 2013/11/22 17:37:11CET Wagner-EXT, Alexander (uidw3785) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
*/

/***************************************************************************
** Header Files (Only those that are needed in this file)
****************************************************************************/
/* System-headerfiles */

/* Foreign headerfiles */

/* Own headerfiles */
#include "WIM__StateHandlerAcousticHandlerFunctions.h"
#include "WIM__StateAccessHelpers.h"

///******************************************************************************
//* ACOUSTIC EVENT FUNCTIONS
//*******************************************************************************/
//
/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nRegister (message -> active)
* - action: set acoustic request, set registered flag, set played flag
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoRegAcu(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* decide whether we have a display sync. acoustic or not */
       WIM__mboIsDspSyncAcu(enMsg))
   {
      WIM__mSetAcuState(enMsg, WIM__nAcuStateWaitDsp);
   }
   else
   {
      WIM__mSetAcuState(enMsg, WIM__nAcuStateWaiting);
      /* set acoustic request */
      WIM__vSetAcuQualifier(enMsg, WIM__nAcuRequested);
   }
   /* set the played flag */
   WIM__mSetAcuPlayedFlag(enMsg, Off);
   /* set retriggered flag */
   WIM__mSetAcuRetriggered((enMsg), False);

   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nCancel/WIM__nDelete
* - action: clear acoustic request
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Lazarev, Schleissheimer GmbH 
*/
bool WIM__boDoCnclDelAcu_Waiting (WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (enMsg != WIM_nenInvalidMsg
      && WIM__menGetMsgType(enMsg) != WIM__nAcoustic)
   {   
      if (/* check the autoquit flag */
          WIM__mboIsAutoQuitEn(enMsg) == True)
      {
         if (/* check the played flag */
             WIM__mboGetAcuPlayedFlag(enMsg) == True)
         {
            /* move to AutoQuit state */
            WIM__mSetAcuState(enMsg, WIM__nAcuStateAutoQuit);
         }
         else
         {
            /* move to Inactive state */
            WIM__mSetAcuState(enMsg, WIM__nAcuStateInactive);
         }
      }
   }
   else /* Message is only Acosutic */
   {
      /*switch the state to "Inactive" */
      WIM__mSetAcuState(enMsg, WIM__nAcuStateInactive);
	  /* Set the displayed flag for acoustic only messages */
      WIM__mSetDisplayedFlag(enMsg, Off);
   }
   /* clear the request */
   WIM__vSetAcuQualifier(enMsg, WIM__nAcuReleased);
   return True;
}

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nDspCancel/WIM__nDspSuppr
* - action: return to "Waiting for a display" state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Lazarev, Schleissheimer GmbH 
*/
bool WIM__boDoDspCnclSupprAcu (WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* Stop Delay Timer TIMER_nWIM_TimerAcuTDElapsed if still running */
   if(TIMER_u16Read(TIMER_nWIM_TimerAcuTDElapsed) != WIM__nTimerInactive)
   {
      TIMER_vClear(TIMER_nWIM_TimerAcuTDElapsed);
   }
   
   if (/* is it a display sync. acoustic? */
       WIM__mboIsDspSyncAcu(enMsg))
   {
      /* clear the acoustic request */
      WIM__vSetAcuQualifier(enMsg,WIM__nAcuReleased);
      /* switch to "Wait for a display" state */
      WIM__mSetAcuState(enMsg, WIM__nAcuStateWaitDsp);
   }

   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nAcuAssign
* - action: switch the state to "Playing"
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Lazarev, Schleissheimer GmbH 
*/
bool WIM__boDoAcuAssign (WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* Stop Delay Timer TIMER_nWIM_TimerAcuTDElapsed if still running */
   if(TIMER_u16Read(TIMER_nWIM_TimerAcuTDElapsed) != WIM__nTimerInactive)
   {
      TIMER_vClear(TIMER_nWIM_TimerAcuTDElapsed);
   }

   /* acoustic assigned - go to "Playing" state */
   WIM__mSetAcuState(enMsg, WIM__nAcuStatePlaying);
   
   /* Set the played flag */
   WIM__mSetAcuPlayedFlag(enMsg, On);

   /* clear elapsed flag */
   WIM__vDelAcuQualifier(enMsg, WIM__nAcuTdElapsed);

   /* acoustic restart flag */
   WIM__mSetAcuRestart(enMsg, False);
   
   /* Acoustic only messages block the display while the 
    * first "display". For display again this block will 
    * not be done.
    */
   if (enMsg != WIM_nenInvalidMsg && WIM__menGetMsgType(enMsg) == WIM__nAcoustic)
   {
      /* Set the displayed flag for acoustic only messages */
      WIM__mSetDisplayedFlag(enMsg, On);
   }


   return False; /* we consumed the event */
}

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nAcuAssignTD
* - action: switch the state to "Tone Delay"
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Lazarev, Schleissheimer GmbH 
*/
bool WIM__boDoAcuAssignToneDelay (WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* acoustic assigned - go to "Tone Delay" state */
   WIM__mSetAcuState(enMsg, WIM__nAcuStateToneDelay);

   /* Start Delay Timer */
   WIM__vToneDelayTimerStart(enMsg);
   /* Start "Silence" to hold the amplifier awake */
   SYN__mvStartDummySound();
   /* clear elapsed flag */
   WIM__vDelAcuQualifier(enMsg, WIM__nAcuTdElapsed);
   /* Set the played flag */
   WIM__mSetAcuPlayedFlag(enMsg, On);
   /* acoustic restart flag */
   WIM__mSetAcuRestart(enMsg, False);
   return False; /* we consumed the event */
}

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nDspCancel/ WIM__nDspSuppr
* - action: clear the request
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Lazarev, Schleissheimer GmbH 
*/
bool WIM__boDoDspCnclDspSupprAcu_WaitDisp (WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   bool boReturn = False;
   /* state change only if no longer registered */
   if (WIM__mboGetRegFlag(enMsg) == Off)
   {
      if (/* if a message was played */
         WIM__mboGetAcuPlayedFlag(enMsg) == True)
      {
         /* switch the state to "Auto Quit" */
         WIM__mSetAcuState(enMsg, WIM__nAcuStateAutoQuit);
      }
      else
      {
         /* switch the state to "Inactive" */
         WIM__mSetAcuState(enMsg, WIM__nAcuStateInactive);
      }
      /* clear acoustic request */
      WIM__vSetAcuQualifier(enMsg, WIM__nAcuReleased);
      boReturn = True;
   }
   return boReturn; /* we consumed the event */
}

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nDspAssign
* - action: go to "Waiting" state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Lazarev, Schleissheimer GmbH 
*/
bool WIM__boDoDspAssignAcu (WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* switch the state to "Waiting" */
   WIM__mSetAcuState(enMsg, WIM__nAcuStateWaiting);

   /* set acoustic request */
   WIM__vSetAcuQualifier(enMsg, WIM__nAcuRequested);

   /* set the sync and urgent bit of message */
   if(WIM__boGetStateAttr(WIM__nAttrAcuSync,enMsg) && WIM__boGetStateAttr(WIM__nAttrUrgent,enMsg))
   {
      WIM__vSetAcuQualifier(enMsg, WIM__nAcuSyncUrgent);      
   }

   /* set AcuRestart Flag */
   WIM__mSetAcuRestart(enMsg, True);

   /* clear WaitForTerm flag */
   WIM__vDelAcuQualifier(enMsg, WIM__nAcuWaitForTerm);

   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nCancel/WIM__nDelete (message -> AutoQuit)
* - action: clear acoustic request
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Immel, Schleissheimer GmbH 
*/
bool WIM__boDoCnclDelAcuTd(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if(/* check what the message is asynchronous */
             WIM__mboIsDspSyncAcu(enMsg) == False)
   {
      /* Stop Delay Timer TIMER_nWIM_TimerAcuTDElapsed if still running */
      if(TIMER_u16Read(TIMER_nWIM_TimerAcuTDElapsed) != WIM__nTimerInactive)
      {
         TIMER_vClear(TIMER_nWIM_TimerAcuTDElapsed);
      }
      /* move to state AutoQuit if possible */
      if (WIM__mboIsAutoQuitEn(enMsg) == True) 
      {
	      WIM__mSetAcuState(enMsg, WIM__nAcuStateAutoQuit);
      }
      /* clear the acoustic request */
      WIM__vSetAcuQualifier(enMsg,WIM__nAcuReleased);
      
      /* Acoustic only messages block the display while the 
       * first "display". For display again this block will 
       * not be done. If the message gets inactive the displayed
       * flag must be reset.
      */
      if (enMsg != WIM_nenInvalidMsg && WIM__menGetMsgType(enMsg) == WIM__nAcoustic)
      {
         /* Set the displayed flag for acoustic only messages */
         WIM__mSetDisplayedFlag(enMsg, Off);
      }
   }
   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nCancel/WIM__nDelete (message -> AutoQuit)
* - action: move to AutoQuit if possible
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Immel, Schleissheimer GmbH 
*/
bool WIM__boDoCnclDelAcuTerm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* move to state AutoQuit if possible */
   if (enMsg != WIM_nenInvalidMsg)
   {
      if (WIM__mboIsAutoQuitEn(enMsg) == True)
      {
         WIM__mSetAcuState(enMsg, WIM__nAcuStateAutoQuit);
      }
      else if (WIM__menGetMsgType(enMsg) == WIM__nAcoustic)
      {
         /* switch the state to "Inactive" */
         WIM__mSetAcuState(enMsg, WIM__nAcuStateInactive);
         /* clear the acoustic request */
         WIM__vSetAcuQualifier(enMsg, WIM__nAcuReleased);

         /* Acoustic only messages block the display while the
         * first "display". For display again this block will
         * not be done. If the message gets inactive the displayed
         * flag must be reset.
         */
         /* Set the displayed flag for acoustic only messages */
         WIM__mSetDisplayedFlag(enMsg, Off);
      }
   }

   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nAcuCancel, WIM__nAcuTerminated
* - action: switch to "Waiting" state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Lazarev, Schleissheimer GmbH 
*/
bool WIM__boDoAcuCnclTermAcu(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boKeepOnDisplayOrRegistered;

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   boKeepOnDisplayOrRegistered = WIM__mboIsAutoQuitEn(enMsg) == False || WIM__mboGetRegFlag(enMsg) == True;

   if (/* a message's tone type is a single tone */
      WIM__enGetToneType(enMsg) == WIM__enSingleTone)
   {
      /* is message registered and auto quit is disabled */
      if (boKeepOnDisplayOrRegistered)
      {
         /* switch the state to "Terminated" */
         WIM__mSetAcuState(enMsg, WIM__nAcuStateTerm);
      }
      else /* message is not registered */
      {
         /* switch the state to "Auto-Quit" */
         WIM__mSetAcuState(enMsg, WIM__nAcuStateAutoQuit);
      }
      /* clear the acoustic request and set also WIM__nAcuWaitForTerm = 0 */
      WIM__vSetAcuQualifier(enMsg, WIM__nAcuReleased);
   }
   else
   {
      /* a message's tone type is an interval tone */
      if (/* check what an auto quit is disabled for the message and this message is registered */
         boKeepOnDisplayOrRegistered)
      {
         if (/* check what the message is synchronous */
            WIM__mboIsDspSyncAcu(enMsg) == True)
         {
            /* switch the state to "Waiting" */
            WIM__mSetAcuState(enMsg, WIM__nAcuStateWaiting);
         }
         else /* message is asynchronous */
         {
            if (enEvt != WIM__nAcuTerminated)
            {
               /* switch the state to "Waiting" */
               WIM__mSetAcuState(enMsg, WIM__nAcuStateWaiting);
            }
         }
      }
      else
      {
         /* switch the state to "AutoQuit" */
         WIM__mSetAcuState(enMsg, WIM__nAcuStateAutoQuit);
         /* clear the acoustic request */
         WIM__vSetAcuQualifier(enMsg, WIM__nAcuReleased);
      }
   }
   return False; /* we consumed the event */
}

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nAcuCancel, WIM__nAcuTerminated
* - action: switch to "Waiting", "AutoQuit", "WaitForDisp", "Inactive" state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoAcuCnclTermAcu_WaitForTerm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (enMsg != WIM_nenInvalidMsg && WIM__menGetMsgType(enMsg) != WIM__nAcoustic)
   {
      if (/* a message's tone type is a single tone */
         WIM__enGetToneType(enMsg) == WIM__enSingleTone)
      {
         /* message is not registered */
         /* switch the state to "Auto-Quit" */
         WIM__mSetAcuState(enMsg, WIM__nAcuStateAutoQuit);   
         /* clear the acoustic request and set also WIM__nAcuWaitForTerm = 0 */
         WIM__vSetAcuQualifier(enMsg,WIM__nAcuReleased);
      }
      else
      {
         /* a message's tone type is an interval tone */
         if (/* check what an auto quit is disabled for the message and this message is registered */
                (WIM__mboIsAutoQuitEn(enMsg) == False) || (WIM__mboGetRegFlag(enMsg) == True))
         {
            if (/* check what the message is synchronous */
                WIM__mboIsDspSyncAcu(enMsg) == True)
            {
               /* switch the state to "Waiting for a display" */
               WIM__mSetAcuState(enMsg, WIM__nAcuStateWaitDsp);
            }
            else /* message is asynchronous */
            {
               if (enEvt != WIM__nAcuTerminated)
               {
                  /* switch the state to "Waiting" */
                  WIM__mSetAcuState(enMsg, WIM__nAcuStateWaiting);
               }
            }
         }
         else
         {
            /* switch the state to "AutoQuit" */
            WIM__mSetAcuState(enMsg, WIM__nAcuStateAutoQuit);
            /* clear the acoustic request */
            WIM__vSetAcuQualifier(enMsg,WIM__nAcuReleased);
         }
      }   
   }
   else /* message is only Acoustic */
   {
      /* switch the state to "Inactive" */
      WIM__mSetAcuState(enMsg, WIM__nAcuStateInactive);
      /* clear WaitForTerm flag */
      WIM__vDelAcuQualifier(enMsg, WIM__nAcuWaitForTerm);
   }
   return False; /* we consumed the event */
}

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nRetrigger
* - action: switch to "Waiting" state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Lazarev, Schleissheimer GmbH 
*/
bool WIM__boDoRetriggerAcu (WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* check what the message is asynchronous */
      WIM__mboIsDspSyncAcu(enMsg) == False)
   {
      /* set acoustic request */
      WIM__vSetAcuQualifier(enMsg, WIM__nAcuRequested);
      /* switch the state to "Waiting" */
      WIM__mSetAcuState(enMsg, WIM__nAcuStateWaiting);
   }
   else   /* message is synchronous */
   {
      /* switch the state to "Waiting for Display" */
      WIM__mSetAcuState(enMsg, WIM__nAcuStateWaitDsp);
   }
   WIM__mSetAcuRetriggered(enMsg, True);
   /* set the played flag */
   WIM__mSetAcuPlayedFlag(enMsg, Off);
   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM_nRegister/WIM__nRetrigger
* - action: switch to "Waiting" or "Waiting for a display" state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  M.Lazarev, Schleissheimer GmbH 
*/
bool WIM__boDoRegAcu_AutoQuit(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   bool boResult = True;
   if(/* if auto-retrigger enabled */
     WIM__mboIsAutoRetrigEn(enMsg) == True)
   {
      /* switch the state to "Waiting" or "Waiting for a display" state */
      boResult = WIM__boDoRegAcu(enMsg, enEvt);
   }
   return boResult;
}

/**
* event handler function
* - type:   handling display message with acoustic
* - event:  WIM__nTmrHdlExpired (handling validity timer terminated)
* - action: clear acoustic request
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boDoHdlExpAcu(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* reset acoustic request */
   WIM__mSetAcuState(enMsg, WIM__nAcuStateAutoQuit);
   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   display message with acoustic
* - event:  WIM__nAcuRetrigger (limited acoustic terminated)
* - action: set request, if sound is playing, restart sound directly
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
bool WIM__boDoAcuRetrigger(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   
   /* Sound can only be retriggered if the warning is still active */
   if(WIM__mboGetRegFlag(enMsg))
   {
      /* check if sound not already requested */
      if (!(WIM__mu8GetAcuQualifier(enMsg) & WIM__nAcuRequested))
      {
         /* The sound has already ended, restart the sound
          * using the register event for acu.
          */
         WIM__boDoRegAcu(enMsg, enEvt);
      }
      else
      {
         /* The sound is currently playing, it must
          * be stopped and started again.
          */
         WIM__vRestartAcoustic(enMsg);

         /* If the acu qualifier is requested but the sound is not 
          * playing, then the sound will be started as soon as the 
          * scheduler priorizes it. In this case the sound module 
          * will not store the sound as retrigger sound.
          */
      }

      /* Set retriggered flag */
      WIM__mSetAcuRetriggered(enMsg, True);
   }
   
   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   display message with acoustic
* - event:  WIM__nDelete/WIM__nCancel
* - action: clear the acoustic request
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
bool WIM__boDoCnclDelAcuPlaying(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{   
   if (/* if an auto-quit enabled */
      enMsg != WIM_nenInvalidMsg
      && (WIM__mboIsAutoQuitEn(enMsg) == True || WIM__menGetMsgType(enMsg) == WIM__nAcoustic))
   {
      if (/* a message's tone type is a interval tone */  
            (WIM__enGetToneType(enMsg) == WIM__enPeriodicIntervalTone)
         /* or if the message is asynchronous */
         || (WIM__mboIsDspSyncAcu(enMsg) == False))
      {
         /* clear the request */
         WIM__vSetAcuQualifier(enMsg,WIM__nAcuReleased);
      }
   }
   
   /* Acoustic only messages block the display while the 
    * first "display". For display again this block will 
    * not be done. If the message gets inactive the displayed
    * flag must be reset.
   */
   if (enMsg != WIM_nenInvalidMsg && WIM__menGetMsgType(enMsg) == WIM__nAcoustic)
   {
      /* Set the displayed flag for acoustic only messages */
      WIM__mSetDisplayedFlag(enMsg, Off);
   }

   /* switch the state to "WIM__nAcuStateWaitForTerm" */
   WIM__mSetAcuState(enMsg, WIM__nAcuStateWaitForTerm);
   /* clear acoustic restart flag */
   WIM__mSetAcuRestart(enMsg, False);
   /* wait for end */
   WIM__vSetAcuQualifier(enMsg,WIM__nAcuWaitForTerm);
   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   display message with acoustic
* - event:  WIM__nDspSuppr/WIM__nDspCancel
* - action: clear the acoustic request
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
bool WIM__boDoDspCnclSupprAcuPl(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   if(/* if the message is synchronous */
         WIM__mboIsDspSyncAcu(enMsg) == True)
   {
      /* clear the acoustic request */
      WIM__vSetAcuQualifier(enMsg,WIM__nAcuReleased);
      /* switch the state to "WIM__nAcuStateWaitForTerm" */
      WIM__mSetAcuState(enMsg, WIM__nAcuStateWaitForTerm);
      /* acoustic restart flag */
      WIM__mSetAcuRestart(enMsg, False);
      /* wait for end */
      WIM__vSetAcuQualifier(enMsg,WIM__nAcuWaitForTerm);
   }
   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   display message with acoustic
* - event:  WIM__nAcuDelayElapsed
* - action: inform scheduler that delay timer elapsed
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   
*   @author  A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoTdElapsed(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /* inform the scheduler after time delay elapsed */
   WIM__vSetAcuQualifier(enMsg, WIM__nAcuTdElapsed);
   
   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   display message with acoustic
* - event:  WIM__nAcuCancel
* - action: stop tone delay, switch to waiting state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   
*   @author  A.Wagner, Schleissheimer GmbH 
*/
bool WIM__nDoAcuCnclToneDelay(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /* Stop Delay Timer TIMER_nWIM_TimerAcuTDElapsed if still running */
   if(TIMER_u16Read(TIMER_nWIM_TimerAcuTDElapsed) != WIM__nTimerInactive)
   {
      TIMER_vClear(TIMER_nWIM_TimerAcuTDElapsed);
   }
   /* switch the state to "Waiting" */
   WIM__mSetAcuState(enMsg, WIM__nAcuStateWaiting);
   return False;
}

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nRegister/WIM__nRetrigger
* - action: switch the state to "Waiting"
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoAcuRestart (WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (  /* if the message is asynchronous */
         (WIM__mboIsDspSyncAcu(enMsg) == False))
   {
      /* acoustic assigned - go to "Waiting" state */
      WIM__mSetAcuState(enMsg, WIM__nAcuStateWaiting);
      
      /* set acoustic request */
      WIM__vSetAcuQualifier(enMsg, WIM__nAcuRequested);

      /* clear WaitForTerm flag */
      WIM__vDelAcuQualifier(enMsg, WIM__nAcuWaitForTerm);

      /* set AcuRestart Flag */
      WIM__mSetAcuRestart(enMsg, True);
   }
   else
   {
      /* acoustic assigned - go to "Wait for display" state */
      WIM__mSetAcuState(enMsg, WIM__nAcuStateWaitDsp);
      
      /* clear acoustic request */
      WIM__vSetAcuQualifier(enMsg, WIM__nAcuReleased);
   }

   /* set retriggered flag to false */
   WIM__mSetAcuRetriggered((enMsg), False);
   /* set the played flag */
   WIM__mSetAcuPlayedFlag(enMsg, Off);

   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nDspAssign
* - action: go to "Waiting" state
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  A.Wagner, Schleissheimer GmbH 
*/
bool WIM__boDoDspAssignAcuDspRoll (WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if(/* a message's tone type is a interval tone */
      (WIM__enGetToneType(enMsg) == WIM__enPeriodicIntervalTone)
      /* and if the message is synchronous */
      && (WIM__mboIsDspSyncAcu(enMsg) == True))
   {
      /* switch the state to "Waiting" */
      WIM__mSetAcuState(enMsg, WIM__nAcuStateWaiting);

      /* set acoustic request */
      WIM__vSetAcuQualifier(enMsg, WIM__nAcuRequested);

      /* set the sync and urgent bit of message */
      if(WIM__boGetStateAttr(WIM__nAttrAcuSync,enMsg) && WIM__boGetStateAttr(WIM__nAttrUrgent,enMsg))
      {
         WIM__vSetAcuQualifier(enMsg, WIM__nAcuSyncUrgent);      
      }

      /* set AcuRestart Flag */
      WIM__mSetAcuRestart(enMsg, True);

      /* clear WaitForTerm flag */
      WIM__vDelAcuQualifier(enMsg, WIM__nAcuWaitForTerm);
   }
   return True; /* we consumed the event */
}

/**
* event handler function
* - type:   acoustic message/display message with acoustic
* - event:  WIM__nDspCancel
* - action: release the acoustic qualifier for sync/single
*   @return  bool: True if event consumed and scheduling required, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @param   WIM__tenEventIntern Event identifier
*   @author  M.Wenske, Schleissheimer GmbH 
*/
bool WIM__boDoDspCncl_WaitForTerm(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   if(/* if the message is synchronous */
            (WIM__mboIsDspSyncAcu(enMsg) == True)
      /* and singletone */
         && (WIM__enGetToneType(enMsg) == WIM__enSingleTone)
     )
   {
      /* clear the acoustic request */
      WIM__vSetAcuQualifier(enMsg,WIM__nAcuReleased);
      /* wait for end */
      WIM__vSetAcuQualifier(enMsg,WIM__nAcuWaitForTerm);
      /* we consumed the event */
      return True;
   }
   return False;
}