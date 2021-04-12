/* Generated by Together */
#ifndef WIM__STATEHANDLER_H
#define WIM__STATEHANDLER_H
/******************************************************************************
*=====================      Copyright by Continental AG      ==================
*******************************************************************************
* Titel        : WIM__StateHandler.h
*
* Description  : Package private interface of State Handler class. 
*                Contains a state machine reacting on internal and external 
*                events. The state machine is individual for the different
*                types of messages. Events are passed to a central interface 
*                function which dispatches the event to the message type.
*                Reaction on events can be state changes and actions that will
*                be initialiszed if the appropriate conditions are fulfilled.
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
* Archive: $Log: WIM__StateHandler.h  $
* Archive: Initial revision for VS11 (Based on 213IC-EL E009.4rel)
*
* Archive: Revision 1.1.2.5 2013/11/22 17:02:36CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 36779 : BR213EL, E006, Implementation of new WarnDB
* Archive: DC MR 36462 : WIM: Implement new scheduling and state handling for acoustic part
* Archive: Revision 1.1.2.4 2013/11/18 16:42:31CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 36361 : BR213: Optimize activation time for acoustic warnings
* Archive: Revision 1.1.2.3 2013/05/17 16:10:23CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 33413: BR213EL/GC, E004, WIM: Takeover of the latest changes from BR205
* Archive: Revision 1.1.2.2 2012/05/18 10:44:16CEST Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
* Archive: Revision 1.3 2012/05/18 10:44:17CEST uid37556 
* Archive: Member moved from WIM__StateHandler.h in project /id/dag_PF3/sw/pkg/wim/core/project.pj[dag_PF3.sw.pkg.wim_COMMON_IC222GC_VarP] to WIM__StateHandler.h in project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj[dag_PF3.sw.pkg.wim_COMMON_GenPF3GC_VarX].
* Archive: Revision 1.2 2012/04/04 15:08:51CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 24870: W222, E007/GC, WIM: Implement changes from Review ORM2907
* Archive: DC MR 25007: W222, E007/GC, WIM: Displacement of handling messages - WDM20280
* Archive: DC MR 25041: Do not specify message propagation in message description files
* Archive: DC MR 25095: W222, E007/GC, WIM: Improvement of Timer accuracy for display role - WDM 25704
* Archive: DC MR 25034: Reduction of lag times in case of vehicle locked
* Archive: DC MR 25393: W222, E007/GC, WIM: No cancel of interval acoustic - WDM31269, �LP2895
* Archive: Revision 1.1 2011/03/15 08:57:28CET Brueggemann Alexander (uidt3637) (uidt3637) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/project.pj
* 
*    Rev 1.5   Mar 22 2011 16:07:24   SCHL_Dirk.Gottwalles
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
*    Rev 1.4   Dec 03 2010 15:57:02   SCHL_Lars.Gruenewald
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
*    Rev 1.3   Nov 19 2010 16:04:14   SCHL_Dirk.Gottwalles
* DC MR21122 BR222: WIM reaction at wakeupreq.
* DC MR21302 BR222/AC: Optimierung Aufruf Checkfunktion WIM
* DC MR20423 W222: WIM new acoustics requirements
* DC MR21177 Implementation of first WarnDB for E003
* DC MR21336 WIM: Using Enumeration Symbols for State/Widget Mapping
* 
*    Rev 1.2   Jul 09 2010 18:01:48   SCHL_Lars.Gruenewald
* DC MR 20710 Vr222 WIM: Menue is in Display before warning
* DC MR 20545 WIM: Extension of HMI Interface for E001.2
* 
*    Rev 1.1   Jun 25 2010 12:22:12   SCHL_Lars.Gr�newald
* DC MR 20566  WIM222: WIM Part2 for E001
* DC MR 20629 Configuration of Display Handler
* DC MR 20639 WIM: Adaption of HMI part for E001.1 
* DC MR 20620 Startup-MR for dynamical area manager (prio)
* DC MR 20661 Br222: WIM: ICOM Reinitialization
* DC MR 20662 Needed patches for WarnDB E001
* DC MR 20560 Implementation of first WarnDB for E001
* DC MR 20490 W222 E001: start up MR SFG
* 
*    Rev 1.0   Jun 11 2010 14:07:50   SCHL_Thomas.Godemann
* Initial revision.
* 
* --------------------------------------------------------------------------
* Date      | Author | Reason     | Change
* --------------------------------------------------------------------------
* 10-06-03    LarGru   MR20481      Initial revision for W222
*
****************************************************************************/

/***************************************************************************
** Header Files (Only those that are needed in this file)
****************************************************************************/

/* System Header Files */
#include "cdef.h"

/* Foreign headerfiles */

/* Own headerfiles */

/******************************************************************************
* Definition of exported global data used by Class
* Macros, Enumerations, Types,  Forward declarations
*******************************************************************************/
   /**
   * State handler attributes generated from warn database for type 
   * 'Display Warning'
   */
   typedef struct 
   {
      /**
      * 'Urgent' attribute, message has urgent priority if set
      * @range  boolean
      * @values True/False
      */
      uint16 biUrgent : 1;

      /**
      * 'Automatic confirmation' attribute, if set message can be confirmed
      * if the message condition has gone
      * @range  boolean
      * @values True/False
      */
      uint16 biAutoQuit : 1;

      /**
      * 'Preterm confirmation' attribute, if set message can be confirmed
      * before the normal display time has elapsed (but after modal phase)
      * @range  boolean
      * @values True/False
      */
      uint16 biPretermAutoQuit : 1;

      /**
      * 'Retrigger after autom. confirmation' attribute, if set message 
      * can be retriggered after it was automatically confirmed
      * @range  boolean
      * @values True/False
      */
      uint16 biAutoQuitRetrig : 1;

      /**
      * 'Retrigger after manual confirmation' attribute, if set message can
      * be retriggered after it was confirmed by the driver
      * @range  boolean
      * @values True/False
      */
      uint16 biManuQuitRetrig : 1;

      /**
      * 'Fault memory' attribute, if set message will be stored in the 
      * fault memory after it was displayed
      * @range  boolean
      * @values True/False
      */
      uint16 biFaultMemory : 1;

      /**
      * 'Fault memory eraseable' attribute, if set, the message can be removed
      * from fault memory if the 'Delete' event occurs
      * @range  boolean
      * @values True/False
      */
      uint16 biEraseFaultMemory : 1;

      /**
      * 'wake IC' attribute, if set wakes the IC display
      * @range  2 bit
      * @values WIM__nNoWakeup - 0, WIM__nWakeup - 1, WIM__nWakeKeepActive - 2, WIM__nKeepActive - 3
      */
      uint16 bi2WakeIC : 2;

      /**
      * Acoustics attribute, identifies linked acoustic behaviour
      * @range  2 bit
      * @values WIM__nAcuStateInactive - 0, WIM__nActiveDspSync - 1, WIM__nActiveDspAsync - 2 
      */
      uint16 bi2Acoustic : 2; 

      /**
      * unused bits
      * @range  5 bit
      * @values n.a.
      */
      uint16 biReserved : 5;

   } WIM__tstStateAttr;

   /**
   * State handler attributes generated from warn database for type 
   * 'Display Warning with Partner message'
   */
   typedef struct
   {
      /**
      * 'Urgent' attribute, message has urgent priority if set
      * @range  boolean
      * @values True/False
      */
      uint16 biUrgent : 1;

      /**
      * 'Automatic confirmation' attribute, if set message can be confirmed
      * if the message condition has gone
      * @range  boolean
      * @values True/False
      */
      uint16 biAutoQuit : 1;

      /**
      * 'Preterm confirmation' attribute, if set message can be confirmed
      * before the normal display time has elapsed (but after modal phase)
      * @range  boolean
      * @values True/False
      */
      uint16 biPretermAutoQuit : 1;

      /**
      * 'Retrigger after autom. confirmation' attribute, if set message 
      * can be retriggered after it was automatically confirmed
      * @range  boolean
      * @values True/False
      */
      uint16 biAutoQuitRetrig : 1;

      /**
      * 'Retrigger after manual confirmation' attribute, if set message can
      * be retriggered after it was confirmed by the driver
      * @range  boolean
      * @values True/False
      */
      uint16 biManuQuitRetrig : 1;

      /**
      * 'Fault memory' attribute, if set message will be stored in the 
      * fault memory after it was displayed
      * @range  boolean
      * @values True/False
      */
      uint16 biFaultMemory : 1;

      /**
      * 'Fault memory eraseable' attribute, if set, the message can be removed
      * from fault memory if the 'Delete' event occurs
      * @range  boolean
      * @values True/False
      */
      uint16 biEraseFaultMemory : 1;

      /**
      * 'wake IC' attribute, if set wakes the IC display
      * @range  2 bit
      * @values WIM__nNoWakeup - 0, WIM__nWakeup - 1, WIM__nKeepActive - 2, WIM__nWakeKeepActive - 3
      */
      uint16 bi2WakeIC : 2;

      /**
      * 'Acoustics' attribute, identifies linked acoustic behaviour
      * @range  2 bit
      * @values WIM__nAcuStateInactive - 0, WIM__nActiveDspSync - 1, WIM__nActiveDspAsync - 2 
      */
      uint16 bi2Acoustic : 2; 

      /**
      * unused bits
      * @range  5 bit
      * @values n.a.
      */
      uint16 biReserved : 5;

      /**
      * 'Partner' attribute, identifies partner message connected with this message
      * @range  0 .. WIM_nNoOfMessages - 1
      * @values any message identifier
      */
      WIM_tenMsg enPartner;

   } WIM__tstStateAttrPtnr;

   /**
   * State handler attributes generated from warn database for type 
   * 'Acoustic only message'
   */
   typedef struct
   {
      /**
      * 'wake IC' attribute, if set wakes the IC display
      * @range  2 bit
      * @values WIM__nNoWakeup - 0, WIM__nWakeup - 1, WIM__nKeepActive - 2, WIM__nWakeKeepActive - 3
      */
      uint8 bi2WakeIC : 2;

      /**
      * unused bits
      * @range  6 bit
      * @values n.a.
      */
      uint8 biReserved : 6;

   } WIM__tstStateAttrAcu;

   /**
   * Enumeration of state handler attributes
   */
   typedef enum
   {
      WIM__nAttrUrgent,      /* message is urgent                                */
      WIM__nAttrWakeIc,      /* message will wake cluster                        */
      WIM__nAttrKeepActiveIc,/* message will keep the cluster active             */
      WIM__nAttrAutoQuit,    /* message can be automatic confirmed               */
      WIM__nAttrPretermAuto, /* message can be preterm automatic confirmed       */
      WIM__nAttrRetrigAuto,  /* message can be retriggered after autom. confirm  */
      WIM__nAttrRetrigManu,  /* message can be retriggered after manual confirm  */
      WIM__nAttrFaultMem,    /* message will cause a fault memory entry          */
      WIM__nAttrFaultMemClr, /* fault memory entry can be removed on Delete      */
      WIM__nAttrAcuSync,     /* message has display sync. acoustic               */
      WIM__nAttrWithAcu      /* message has acoustic                             */
   } WIM__tenAttrId;

   /**
    * Counter for acoustic retrigger
    */
   extern uint8 WIM__u8CounterStartsAcousticRetrigger;

/***************************************************************************
* CLASS DEFINITION
***************************************************************************/
#ifdef TOGETHER /* open C++ class */

/**
* State handler class, handles events and manages states of messages
*/
class WIM__StateHandler {
public: 
#endif

/***************************************************************************
*   Class Attributes
***************************************************************************/

/* System Wide Scope */
#ifdef TOGETHER
public:
#endif
  
#ifdef QAC_Analysis
#pragma PRQA_MESSAGES_OFF 2300
#endif /* QAC_Analysis */

/* Package Global Scope */
   

   /**
   * Memory for current display state
   * @range  boolean
   * @values True: display on, False: display off
   */
   extern bool WIM__boDisplayState;

   /**
   * Counter for Registered Warnings with KeepActive Attribute (see Attribute WakeIc)
   * @range  uint8
   * @values 0...255
   */
   extern uint8 WIM__u8KeepActiveIcRegisteredCount;

#ifdef QAC_Analysis
#pragma PRQA_MESSAGES_ON 2300
#endif /* QAC_Analysis */

/* File Local Scope */
#ifdef TOGETHER
private:
#endif

/***************************************************************************
*   Class Operations
***************************************************************************/

/* Package Global Scope */
#ifdef TOGETHER
public:
#endif

   /**
   * Returns the current display qualifier for the message
   *   @return  uint8 - Display qualifier
   *   @param   const WIM_tenMsg - Display message
   *   @author  D. Gottwalles, Schleissheimer GmbH 
   */
   uint8 WIM__u8GetDspQualifier(const WIM_tenMsg enMsg);

   /**
   * Hmi send Feedback with new Warning in Display. Forward it into StateHandler!
   * For HMI its only allowed to send the Feedback if the displayed warning changed.
   *   @return  void
   *   @param   const WIM_tenMsg - Message whichs display qualifier shall be modified
   *   @param   const WIM__tenDspQualifier - Display qulifier to add
   *   @author  D.Gottwalles, Schleissheimer GmbH 
   */
   void WIM__vSetDspQualifier(const WIM_tenMsg enMsg, const WIM__tenDspQualifier enQualifier);

   /**
   * Sets the acoustic qualifier for the message
   *   @return  none
   *   @param   const WIM_tenMsg - Display message
   *            const WIM__tenDspQualifier - acoustic qualifier
   *   @author  A.Wagner, Schleissheimer GmbH 
   */
   void WIM__vSetAcuQualifier(const WIM_tenMsg enMsg, const WIM__tenAcuQualifier enQualifier);

   /**
   * Delete the acoustic qualifier for the message
   *   @return  none
   *   @param   const WIM_tenMsg - Display message
   *            const WIM__tenDspQualifier - acoustic qualifier
   *   @author  A.Wagner, Schleissheimer GmbH 
   */
   void WIM__vDelAcuQualifier(const WIM_tenMsg enMsg, const WIM__tenAcuQualifier enQualifier);

   /**
   * Hmi send Feedback with old and new Warning in Display. Forward it into StateHandler!
   *   @return  void
   *   @param   EVHD_tenReceiveEvent enWarnResponseEvent
   *   @author  L.Gruenewald, Schleissheimer GmbH 
   */
   void WIM__vDoHmiFeedback(EVHD_tenReceiveEvent enWarnResponseEvent);

   /**
   * PowerOn initialisation of State Handler
   *   @return  void
   *   @param   none
   *   @author  T.Godemann, Schleissheimer GmbH 
   */
   void WIM__vStateHandlerInit_GC(void);

   /**
   * Reset state of all warnings at Display-Off-Edge
   *   @return  void
   *   @param   none
   *   @author  L.Gruenewald, Schleissheimer GmbH 
   */
   void WIM__vResetAllWarnings(void);

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
   void WIM__vRestoreWarnings(void);

   /**
   * RestoreWarnings has finished and
   * the Scheduler has to be restarted, retriggered.
   *   @return  void
   *   @param   void
   *   @author  L.Gruenewald, Schleissheimer GmbH 
   */
   void WIM__vFinishedRestoreWarnings_GC(void);

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
   void WIM__vDspTimer(WIM__tenTimer enTimer, WIM__txCorrTag xCorrTag);
   
   /**
   * helper function: for ClearRequest_DisplayOn if DisplayOnTimer = 0
   *   @return  void
   *   @param   WIM__tenTimer: Timer identifier
   *   @param   WIM_txCorrTag: Timer user CorrTag
   *   @author  K. Warnicki, Schleissheimer GmbH 
   */
   void WIM__vDisplayOnTimer(WIM__tenTimer, WIM__txCorrTag);

   /**
   * Central event function.
   * Dispatches all events depending on message type to the appropriate
   * handler function. The function is defined in the message type specific 
   * state matrix. Scheduler is triggered, if required.
   *   @return  bool: True if event consumed, False otherwise
   *   @param   enMsg: Message identifier, enEvt: Event identifier
   *   @author  T.Godemann, Schleissheimer GmbH 
   */
   void WIM__vOnEvent_GC(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt);

   /**
   * Helper function for Scheduler accessing state attributes for Acoustic
   *   @return  bool: True if display synchroneous acoustic, False otherwise
   *   @param   WIM_tenMsg Message identifier
   *   @author  T.Godemann, Schleissheimer GmbH 
   */
   bool WIM__boIsDspSyncAcoustic(WIM_tenMsg enMsg);
   
   /**                                                                      
   * The function returns the message's priority level
   *   @return  priority level of message (0 == highest)                    
   *   @param   uint32 u32HilId: HIL ID of message to evaluate                       
   *   @author  T.Godemann, Schleissheimer GmbH                             
   */                                                                       
   uint8 WIM__u8GetMsgPrioLevel(WIM_tenMsg enMsg);                          

   /**
   * Attribute access helper:
   * Get message ID of partner message
   *   @return  WIM_tenMsg: valid message Id if partner present, WIM_nInvalidMsg otherwise
   *   @param   WIM_tenMsg Message identifier
   *   @author  T.Godemann, Schleissheimer GmbH 
   */
   WIM_tenMsg WIM__enGetPartnerMsg(WIM_tenMsg enMsg);

   /** 
   * Inform applications to re-check message conditions after message reset
   *   @return  void
   *   @param   void
   *   @author  T.Godemann, Schleissheimer GmbH 
   */
   void WIM__vCheckComplexWarnings_GC(void);

   /**
   * Message in Fast Activation List or not
   *   @return  True, if message is in container
   *   @param   enMsg
   *   @author  A.Wagner, Schleissheimer GmbH 
   */
   bool WIM__boFastActivationSound(WIM_tenMsg enMsg);

/* File Local Scope */
#ifdef TOGETHER
private:
#endif

#ifdef TOGETHER /* close the C++ class */
};
#endif
/********************
**  CLASS END
*********************/
#endif /* WIM__STATEHANDLER_H */