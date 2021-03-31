/******************************************************************************
*=====================      Copyright by Continental AG      ==================
*******************************************************************************
* Titel        : WIM__ICom_GC.c
*
* Description  : Package private interface of icom-class:
*                ICom services GC
*                Private class that manages DPOOL access
*                package WIM
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
* Archive: $Log: WIM__ICom_GC.c  $
* Archive: Revision 1.4 2014/07/29 18:35:38CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 41681 : WIM: Prevent sporadic flicker of GC controlled complex warnings after Kl15ACC
* Archive: Revision 1.3 2014/03/21 12:59:58CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 39839 : BR205 E013: ALP3289 new warning 0x200542(Hybrid) 
* Archive: DC MR 40021 : WIM: Sound of FCW warning is not retriggered after reset
* Archive: DC MR 39892 : BR213EL, E007, Implementation of L2
* Archive: Revision 1.2 2013/11/22 17:20:04CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 36779 : BR213EL, E006, Implementation of new WarnDB
* Archive: DC MR 36462 : WIM: Implement new scheduling and state handling for acoustic part
* Archive: Revision 1.1 2013/03/21 18:16:07CET Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/adapt/project.pj
* Archive: Revision 1.3 2012/06/15 15:43:57CEST uid37556 
* Archive: DC MR 26087: W205, E009/GC, WIM: Change of Prio1Mute and Lowering times - ÄLP2873
* Archive: Revision 1.2 2012/05/18 14:47:55CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 25917: W222, E007/GC, WIM: Changes on display-block by sound only warning - WDM35459
* Archive: DC MR 25905: W205, E008/GC, WIM: Displacement of handling messages - Follow-Up
* Archive: DC MR 25716: W205, E009/GC, WIM: Behaviour of sync acoustics - WDM35391, 35418, 35392, 35389, 35396, 35421
* Archive: DC MR 25711: W205, E009/GC, WIM: Inactive handling messages show up after 600ms - WDM35020
* Archive: DC MR 25705: W205, E009/GC, WIM: Fix for corrupted sound
* Archive: DC MR 25460: BR205 E009: PrioHandler: Changes after code review
* Archive: DC MR 25147: W205, E009/GC, WIM: Priorities for roll handling - WDM35385
* Archive: DC MR 25142: W205, E009/GC, WIM: SBW/WIM Acoustic corrections - WDM21151, WDM34246
* Archive: DC MR 25132: W205, E009/GC, WIM: Implementation of exceptions
* Archive: DC MR 25089: W205, E008/GC, WIM: Improvement of Timer accuracy for display role - WDM 32006
* Archive: Revision 1.1 2011/11/08 13:47:56CET Gottwalles Dirk (uid37556) (uid37556) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/adapt/project.pj
* 
*    Rev 1.0   Nov 08 2011 14:34:36   SCHL_Dirk.Gottwalles
* Initial revision.
* 
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
#include "WIM__ICom_GC.h"
#include "WIM__IComIntern.h"


/******************************************************************************
* PACKAGE LOCAL DEFINITIONS
*******************************************************************************/

   /**
   * Flag, indicates Active RestoreWarnings Handshake.
   */
   static bool WIM__boRestoreWarningsActive = False;

   /**
   * Flag, indicates Active ResetWarnings Handshake.
   */
   static bool WIM__boResetWarningsActive = False;

/******************************************************************************
* FILE LOCAL DEFINITIONS
*******************************************************************************/

/******************************************************************************
* PACKAGE LOCAL FUNCTIONS - Initialisation
*******************************************************************************/
/**
* Initialise ICom internal components.
*   @return  void
*   @param   void
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
void WIM__vIComInit_GC(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   WIM__boRestoreWarningsActive = False;  
   WIM__boResetWarningsActive   = False;  
}


/******************************************************************************
* PACKAGE LOCAL FUNCTIONS - Receive ICom Function
*******************************************************************************/

void WIM__vDoDpoolEventsByICom_GC(EVHD_tenReceiveEvent enEvent)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   /* Helper for count receive data tries without getting valid data */
   uint8 u8NoDataReceived = 0;    
   /* Returnvalue of DPOOL API */
   DPOOL_tenStatusType enDpoolReturn;      
   /* Local Variable to store DPOOL Data for Processing */
   uint32 u32DpoolDataRx;                     
   /* Identifier for Rx Data */
   WIM__tenIComIdentifier enIComRxIdentifier; 
   /* Storage for Msg Enum if required */
   WIM_tenMsg enMsg = WIM_nenInvalidMsg;      
   /* Temporarly byte storage when extract DPOOL data */ 
   uint8 u8Byte1 = 0;                        


   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if(/* Check if received Event is the handled event */
       enEvent == EV_DPOOL_Always_WIM_u32IcomDataAc_QueueAC_to_GC_WIM_vDoDpoolEvents)
   {
      /********************************************************/
      /* Get Data from DPOOL and extract WIM__ICom Identifier */
      /********************************************************/

      do /* when called by EVHD poll until the Queue is empty*/
      {
         /* Reset for next data receive */
         u32DpoolDataRx     = 0;
         enIComRxIdentifier = WIM__nNoOfIdentifiers;
         enDpoolReturn      = E_DATA_COM_LIMIT;

         /* receive Data */
         enDpoolReturn = DPOOL_enGetPoolData(DPOOL_nDataWIM_u32IcomDataAc_QueueAC_to_GC, &u32DpoolDataRx);

         if(enDpoolReturn == E_DATA_OK)
         {
            /* reset helper */
            u8NoDataReceived = 0;

            /* extract Identifier */
            enIComRxIdentifier = WIM__mExtractIComIdent(u32DpoolDataRx);

            /*************************************************************/
            /* Do the Data Handling for the received WIM__IComIdentifier */
            /*************************************************************/
            switch(enIComRxIdentifier)
            {
            case WIM__nOnEventAcToGc:
               /*********************/
               /* RequestControl send Data for WIM__vOnEvent_GC Fct */
               /*********************/
               if(( /* Use or drop Event */
                  WIM__boRestoreWarningsActive == False && 
                  WIM__boResetWarningsActive == False) &&
                  /* Only if Diag Mode is off */
                  WIM__boDiagMode == False)
               {
                  /* Extract the Msg-Enum */
                  enMsg = WIM__mExtractMsgEnum(u32DpoolDataRx);
                  /* Extract 3. Byte, the InternalEvent for call of WIM__vOnEvent_GC */
                  u8Byte1 = WIM__mExtractByte3(u32DpoolDataRx);
                  /* Call the Function WIM__vOnEvent_GC with received data */
                  WIM__vOnEvent_GC(enMsg,(WIM__tenEventIntern)u8Byte1);
               }
               break;

            case WIM__nRestoreWarningsBeginReCheckAcToGc:
               /*********************/
               /* RequestControl notify RestoreAllWarnings done
               *  and now beginning with re-check all warnings */
               /*********************/
               /* Activate ICom reception of OnEvent-Queue-Elements */
               WIM__boRestoreWarningsActive = False; 
               break;

            case WIM__nRestoreWarningsDoneReCheckAcToGc:
               /*********************/
               /* RequestControl notify RestoreAllWarnings Finished
               *  and has done the first re-check all warnings */
               /*********************/
               /* Cancel Timer for timeout handling */
               WIM__vCancelTimer(WIM__nTimerTmOutRestore);
               /* Restart, trigger Scheduler as last step of RestoreWarnings */
               WIM__vFinishedRestoreWarnings_GC(); 
               break;

            case WIM__nResetWarningsFinishedAcToGc:
               /*********************/
               /* RequestControl notify that ResetAllWarnings is done */
               /*********************/
               /* Cancel Timer for timeout handling */
               WIM__vCancelTimer(WIM__nTimerTmOutReset);
               /* Activate ICom reception of OnEvent-Queue-Elements */
               WIM__boResetWarningsActive = False; 
               break;

            default:
               break;

            }
         }
         else
         {
            /* increase helper on unhandled returnvalue of GetPoolData */
            u8NoDataReceived++;
         }
      } while( /* when called by EVHD poll until the Queue is empty */
         (enDpoolReturn != E_DATA_COM_NOMSG) &&
         /* to prevent infinite loop by bad returnvalue */
         u8NoDataReceived < WIM__nMaxNumRetries);
   }
}


/******************************************************************************
* PACKAGE LOCAL FUNCTIONS - CONTAINER - Send ICom Data
*******************************************************************************/
   
   /**
   *   Helper function to trigger DspChangeCont on AC over ICom
   *   @return  void
   *   @param   u32HilID
   *   @author  L.Gruenewald, Schleissheimer GmbH 
   */
   void WIM__vIComDspChangeContainer(uint32 u32HilId)
   {
      /***************************************************************************
      * FUNCTION LOCAL DEFINITIONS
      ****************************************************************************/
      /* local Data for transmit by Icom       */
      uint32 u32TxData = 0;
      /* Returnvalue of DPOOL API              */
      DPOOL_tenStatusType    enDpoolReturn = E_DATA_COM_LIMIT;         

      /***************************************************************************
      * FUNCTION CODE
      ****************************************************************************/
      /* Set Short HIL-ID into Tx data */
      u32TxData  = WIM__mPackHilIdShort(u32HilId);
      /* Add ICom Identifier into Tx data */
      u32TxData |= WIM__mPackIComIdent(WIM__nContainerDspChangeGcToAc);

      /*************************************/
      /* Send uint32 TxData by using DPOOL */
      /*************************************/
      enDpoolReturn = DPOOL_enSetPoolData(DPOOL_nDataWIM_u32IcomDataGc_Queue, &u32TxData);

      /*************************************/
      /* Check DPOOL QUEUE Result          */
      /*************************************/
      if (
          /* was Data sent successfully (into queue) */
             enDpoolReturn != E_DATA_OK
         )
      {
         /* Throw an Exception for trace ICOM QUEUE overflow */
         WIM__vRaiseException(WIM_nErrIcom);   
      }
   }

   /**
   *   Helper function to trigger StateChangeCont on AC over ICom
   *   @return  void
   *   @param   u32HilID, enNotify
   *   @author  L.Gruenewald, Schleissheimer GmbH 
   */
   void WIM__vIComNotifyHandler(uint32 u32HilId, WIM_tenDisplayEvent enNotify)
   {
      /***************************************************************************
      * FUNCTION LOCAL DEFINITIONS
      ****************************************************************************/
      /* local Data for transmit by Icom       */
      uint32 u32TxData = 0;
      /* Returnvalue of DPOOL API              */
      DPOOL_tenStatusType    enDpoolReturn = E_DATA_COM_LIMIT;         

      /***************************************************************************
      * FUNCTION CODE
      ****************************************************************************/
      /* Set Short HIL-ID into Tx data    */
      u32TxData  = WIM__mPackHilIdShort(u32HilId);
      /* Add DisplayEvent as 3.Byte       */
      u32TxData |= WIM__mPackByte3(enNotify);
      /* Add ICom Identifier into Tx data */
      u32TxData |= WIM__mPackIComIdent(WIM__nNotifyHandlerGcToAc);

      /*************************************/
      /* Send uint32 TxData by using DPOOL */
      /*************************************/
      enDpoolReturn = DPOOL_enSetPoolData(DPOOL_nDataWIM_u32IcomDataGc_Queue, &u32TxData);

      /*************************************/
      /* Check DPOOL QUEUE Result          */
      /*************************************/
      if (
          /* was Data sent successfully (into queue) */
             enDpoolReturn != E_DATA_OK
         )
      {
         /* Throw an Exception for trace ICOM QUEUE overflow */
         WIM__vRaiseException(WIM_nErrIcom);   
      }
   }

   /**
   *   Helper function to trigger PreConfirmationContainer on AC over ICom
   *   @return  void
   *   @param   u32HilID
   *   @author  D.Gottwalles, Schleissheimer GmbH 
   */
   void WIM__vIComPreConfirmationContainer(uint32 u32HilId)
   {
      /***************************************************************************
      * FUNCTION LOCAL DEFINITIONS
      ****************************************************************************/
      /* local Data for transmit by Icom       */
      uint32 u32TxData = 0;
      /* Returnvalue of DPOOL API              */
      DPOOL_tenStatusType    enDpoolReturn = E_DATA_COM_LIMIT;         

      /***************************************************************************
      * FUNCTION CODE
      ****************************************************************************/
      /* Set Short HIL-ID into Tx data    */
      u32TxData  = WIM__mPackHilIdShort(u32HilId);
      /* Add ICom Identifier into Tx data */
      u32TxData |= WIM__mPackIComIdent(WIM__nContainerPreConfirmationGcToAc);

      /*************************************/
      /* Send uint32 TxData by using DPOOL */
      /*************************************/
      enDpoolReturn = DPOOL_enSetPoolData(DPOOL_nDataWIM_u32IcomDataGc_Queue, &u32TxData);

      /*************************************/
      /* Check DPOOL QUEUE Result          */
      /*************************************/
      /* was Data sent successfully (into queue) */
      if (enDpoolReturn != E_DATA_OK)
      {
         /* Throw an Exception for trace ICOM QUEUE overflow */
         WIM__vRaiseException(WIM_nErrIcom);   
      }
   }

   /**
   *   Helper function to trigger ManuQuitContainer on AC over ICom
   *   @return  void
   *   @param   u32HilID
   *   @author  L.Gruenewald, Schleissheimer GmbH 
   */
   void WIM__vIComManuQuitContainer(uint32 u32HilId, WIM_tenDisplayEvent enDispEvt)
   {
      /***************************************************************************
      * FUNCTION LOCAL DEFINITIONS
      ****************************************************************************/
      /* local Data for transmit by Icom       */
      uint32 u32TxData = 0;
      /* Returnvalue of DPOOL API              */
      DPOOL_tenStatusType    enDpoolReturn = E_DATA_COM_LIMIT;         

      /***************************************************************************
      * FUNCTION CODE
      ****************************************************************************/
      /* Set Short HIL-ID into Tx data    */
      u32TxData  = WIM__mPackHilIdShort(u32HilId);
      /* Add Display Event into Tx data */
      u32TxData |= WIM__mPackDispEvent(enDispEvt);
      /* Add ICom Identifier into Tx data */
      u32TxData |= WIM__mPackIComIdent(WIM__nContainerManuQuitGcToAc);

      /*************************************/
      /* Send uint32 TxData by using DPOOL */
      /*************************************/
      enDpoolReturn = DPOOL_enSetPoolData(DPOOL_nDataWIM_u32IcomDataAc_Queue, &u32TxData);

      /*************************************/
      /* Check DPOOL QUEUE Result          */
      /*************************************/
      if (
          /* was Data sent successfully (into queue) */
             enDpoolReturn != E_DATA_OK
         )
      {
         /* Throw an Exception for trace ICOM QUEUE overflow */
         WIM__vRaiseException(WIM_nErrIcom);   
      }
   }

   /******************************************************************************
   * PACKAGE LOCAL FUNCTIONS - Int/Ext Condition Replacements - Send ICom Data
   *******************************************************************************/

   /**                                                                                                     
   * This is replacement function on GC and send Information by ICom on AC
   *   @return  void                                                                                       
   *   @param   u8Function: function, event belongs to                                                     
   *   @param   u8Index: index of subfunction                                                              
   *   @param   WIM__tenEventIntern enEvt: Register/Retrigger/Delete                                       
   *   @author  L.Gruenewald, Schleissheimer GmbH                                                            
   */                                                                                                      
   void WIM__vHandleExtCondition_GC(WIM_tenExtEvtFunction enFunction, uint8 u8Index, WIM__tenEventIntern enEvt)
   {
      /***************************************************************************
      * FUNCTION LOCAL DEFINITIONS
      ****************************************************************************/
      /* local Data for transmit by Icom       */
      uint32 u32TxData = 0;
      /* Returnvalue of DPOOL API              */
      DPOOL_tenStatusType    enDpoolReturn = E_DATA_COM_LIMIT;         

      /***************************************************************************
      * FUNCTION CODE
      ****************************************************************************/
      /* Set Param 1, enFunction as 1.Byte   */
      u32TxData  = WIM__mPackByte1(((uint8)enFunction));
      /* Add Param 2, u8Index as 2.Byte   */
      u32TxData  |= WIM__mPackByte2(((uint8)u8Index));
      /* Add Param 3, enEvt as 3.Byte   */
      u32TxData  |= WIM__mPackByte3(((uint8)enEvt));
      /* Add ICom Identifier into Tx data */
      u32TxData  |= WIM__mPackIComIdent(WIM__nHandleExtConditionGcToAc);

      /*************************************/
      /* Send uint32 TxData by using DPOOL */
      /*************************************/
      enDpoolReturn = DPOOL_enSetPoolData(DPOOL_nDataWIM_u32IcomDataGc_Queue, &u32TxData);

      /*************************************/
      /* Check DPOOL QUEUE Result          */
      /*************************************/
      if (
          /* was Data sent successfully (into queue) */
             enDpoolReturn != E_DATA_OK
         )
      {
         /* Throw an Exception for trace ICOM QUEUE overflow */
         WIM__vRaiseException(WIM_nErrIcom);   
      }
   }

   /**
   * This is replacement function on GC and send Information by ICom on AC 
   *   @return  void
   *   @param   u32HilId: HIL ID of the related message
   *   @param   WIM__tenEventIntern enEvt: WIM__nRegister, WIM__nRetrigger, WIM__nDelete
   *   @author  T.Godemann, Schleissheimer GmbH 
   */
   void WIM__vHandleIntCondition_GC(uint32 u32HilId, WIM__tenEventIntern enEvt)
   {
      /***************************************************************************
      * FUNCTION LOCAL DEFINITIONS
      ****************************************************************************/
      /* local Data for transmit by Icom       */
      uint32 u32TxData = 0;
      /* Returnvalue of DPOOL API              */
      DPOOL_tenStatusType    enDpoolReturn = E_DATA_COM_LIMIT;         

      /***************************************************************************
      * FUNCTION CODE
      ****************************************************************************/
      /* Set Param 1, enFunction as 1.Byte   */
      u32TxData  = WIM__mPackHilIdShort(u32HilId);
      /* Add Param enEvt as 3.Byte   */
      u32TxData  |= WIM__mPackByte3(((uint8)enEvt));
      /* Add ICom Identifier into Tx data */
      u32TxData  |= WIM__mPackIComIdent(WIM__nHandleIntConditionGcToAc);

      /*************************************/
      /* Send uint32 TxData by using DPOOL */
      /*************************************/
      enDpoolReturn = DPOOL_enSetPoolData(DPOOL_nDataWIM_u32IcomDataGc_Queue, &u32TxData);

      /*************************************/
      /* Check DPOOL QUEUE Result          */
      /*************************************/
      if (
          /* was Data sent successfully (into queue) */
             enDpoolReturn != E_DATA_OK
         )
      {
         /* Throw an Exception for trace ICOM QUEUE overflow */
         WIM__vRaiseException(WIM_nErrIcom);   
      }
   }

   /******************************************************************************
   * PACKAGE LOCAL FUNCTIONS - FaultMemFlag
   *******************************************************************************/
   /**
   * helper function: set/clear fault memory flag on Automotive Controller
   *   @return  void
   *   @param   WIM_tenMsg: Message identifier
   *   @param   bool boSet: True set flag, False clear flag
   *   @author  L.Gruenewald, Schleissheimer GmbH 
   */
   void WIM__vSetFaultMemFlagICom(WIM_tenMsg enMsg, bool boSet)
   {
      /***************************************************************************
      * FUNCTION LOCAL DEFINITIONS
      ****************************************************************************/
      /* local Data for transmit by Icom       */
      uint32 u32TxData = 0;
      /* Returnvalue of DPOOL API              */
      DPOOL_tenStatusType    enDpoolReturn = E_DATA_COM_LIMIT;         

      /***************************************************************************
      * FUNCTION CODE
      ****************************************************************************/
      /* Set Msg-Enum into Tx data   */
      u32TxData   = WIM__mPackMsgEnum(enMsg);
      /* Add Param boSet as 3. Byte of Tx data */
      u32TxData  |= WIM__mPackByte3((bool)boSet);
      /* Add ICom Identifier into Tx data */
      u32TxData  |= WIM__mPackIComIdent(WIM__nSetFaultMemFlagGcToAc);

      /*************************************/
      /* Send uint32 TxData by using DPOOL */
      /*************************************/
      enDpoolReturn = DPOOL_enSetPoolData(DPOOL_nDataWIM_u32IcomDataAc_Queue, &u32TxData);

      /*************************************/
      /* Check DPOOL QUEUE Result          */
      /*************************************/
      if (
          /* was Data sent successfully (into queue) */
             enDpoolReturn != E_DATA_OK
         )
      {
         /* Throw an Exception for trace ICOM QUEUE overflow */
         WIM__vRaiseException(WIM_nErrIcom);   
      }

   }

   /******************************************************************************
   * PACKAGE LOCAL FUNCTIONS - CAN HeadUnit Replacements - Send ICom Data
   *******************************************************************************/
   /**
   * Replacement for RequestControl Function!!! Forwoard data by ICom.
   * The function sets the internal request 
   * A mute/volume decrease of the head unit is canceled by sending specific CAN 
   * signals (if a delay is specified, the signals are canceled on timer end).
   *   @return  void
   *   @param   boOn: True = set request, False = clear request
   *   @author  T.Godemann, Schleissheimer GmbH 
   */
   void WIM__vSetVolDecRequest_GC(WIM__tenAcuTypes enAcuType, bool boOn)
   {
      /***************************************************************************
      * FUNCTION LOCAL DEFINITIONS
      ****************************************************************************/

      /* local Data for transmit by Icom       */
      uint32 u32TxData = 0;
      /* Returnvalue of DPOOL API              */
      DPOOL_tenStatusType    enDpoolReturn = E_DATA_COM_LIMIT;         

      /***************************************************************************
      * FUNCTION CODE
      ****************************************************************************/
      /* Set Param boOn as 2.Byte   */
      u32TxData = WIM__mPackByte1((uint8)enAcuType);
      u32TxData |= WIM__mPackByte2((uint8)boOn);
      
      /* Add ICom Identifier into Tx data */
      u32TxData |= WIM__mPackIComIdent(WIM__nSetVolDecRqGcToAc);
      

      /*************************************/
      /* Send uint32 TxData by using DPOOL */
      /*************************************/
      enDpoolReturn = DPOOL_enSetPoolData(DPOOL_nDataWIM_u32IcomDataGc_Queue, &u32TxData);

      /*************************************/
      /* Check DPOOL QUEUE Result          */
      /*************************************/
      if (
          /* was Data sent successfully (into queue) */
             enDpoolReturn != E_DATA_OK
         )
      {
         /* Throw an Exception for trace ICOM QUEUE overflow */
         WIM__vRaiseException(WIM_nErrIcom);   
      }
   }
 
   /**
   * Replacement for RequestControl Function!!! Forwoard data by ICom.
   * The function sets the internal request 
   * A mute/volume decrease of the head unit is canceled by sending specific CAN 
   * signals (if a delay is specified, the signals are canceled on timer end).
   *   @return  void
   *   @param   boOn: True = set request, False = clear request
   *   @author  L.Gruenewald, Schleissheimer GmbH 
   */
   void WIM__vSetMuteRequest_GC(WIM__tenAcuTypes enAcuType, bool boOn)
   {
      /***************************************************************************
      * FUNCTION LOCAL DEFINITIONS
      ****************************************************************************/
      /* local Data for transmit by Icom       */
      uint32 u32TxData = 0;
      /* Returnvalue of DPOOL API              */
      DPOOL_tenStatusType    enDpoolReturn = E_DATA_COM_LIMIT;         

      /***************************************************************************
      * FUNCTION CODE
      ****************************************************************************/
      /* Set Param boOn as 2.Byte   */
      u32TxData = WIM__mPackByte1((uint8)enAcuType);
      u32TxData |= WIM__mPackByte2((uint8)boOn);

      /* Add ICom Identifier into Tx data */
      u32TxData  |= WIM__mPackIComIdent(WIM__nSetMuteRqGcToAc);

      /*************************************/
      /* Send uint32 TxData by using DPOOL */
      /*************************************/
      enDpoolReturn = DPOOL_enSetPoolData(DPOOL_nDataWIM_u32IcomDataGc_Queue, &u32TxData);

      /*************************************/
      /* Check DPOOL QUEUE Result          */
      /*************************************/
      if (
          /* was Data sent successfully (into queue) */
             enDpoolReturn != E_DATA_OK
         )
      {
         /* Throw an Exception for trace ICOM QUEUE overflow */
         WIM__vRaiseException(WIM_nErrIcom);   
      }
   }

   /******************************************************************************
   * PACKAGE LOCAL FUNCTIONS - RestoreReset Handshake - Send ICom Data
   *******************************************************************************/
   /**
   * Replacement for RequestControl Function!!! 
   * Warning states handled by RequestControl has to be restored.
   *   @return  void
   *   @param   void
   *   @author  L.Gruenewald, Schleissheimer GmbH 
   */
   void WIM__vStartRestoreWarningsRequestControl_GC(void)
   {
      /***************************************************************************
      * FUNCTION LOCAL DEFINITIONS
      ****************************************************************************/
      /* local Data for transmit by Icom       */
      uint32 u32TxData = 0;
      /* Returnvalue of DPOOL API              */
      DPOOL_tenStatusType    enDpoolReturn = E_DATA_COM_LIMIT;         

      /***************************************************************************
      * FUNCTION CODE
      ****************************************************************************/
      /* Drop all further incoming OnEvent Icom-Events */
      WIM__boRestoreWarningsActive = True;
      /* Add ICom Identifier into Tx data */
      u32TxData  = WIM__mPackIComIdent(WIM__nStartRestoreWarningsGcToAc);

      /*************************************/
      /* Send uint32 TxData by using DPOOL */
      /*************************************/
      enDpoolReturn = DPOOL_enSetPoolData(DPOOL_nDataWIM_u32IcomDataGc_Queue, &u32TxData);

      /* Start Timer for timeout handling */
      WIM__vStartTimer(WIM__nTimerTmOutRestore, WIM_nenInvalidMsg);

      /*************************************/
      /* Check DPOOL QUEUE Result          */
      /*************************************/
      if (
         /* was Data sent successfully (into queue) */
         enDpoolReturn != E_DATA_OK
         )
      {
         /* Throw an Exception for trace ICOM QUEUE overflow */
         WIM__vRaiseException(WIM_nErrIcom);   
      }

   }

   /******************************************************************************
   * PACKAGE LOCAL FUNCTIONS - RestoreReset Handshake - Send ICom Data
   *******************************************************************************/
   /**
   * Notification for check complex GC functions done.
   *   @return  void
   *   @param   void
   *   @author  L.Gruenewald, Schleissheimer GmbH 
   */
   void WIM__vCheckComplexWarningsRequestControl(void)
   {
      /***************************************************************************
      * FUNCTION LOCAL DEFINITIONS
      ****************************************************************************/
      /* local Data for transmit by Icom       */
      uint32 u32TxData = 0;
      /* Returnvalue of DPOOL API              */
      DPOOL_tenStatusType    enDpoolReturn = E_DATA_COM_LIMIT;         

      /***************************************************************************
      * FUNCTION CODE
      ****************************************************************************/
      /* Check complex warnings on GC */
      WIM__vCheckComplexWarnings_GC();
      /* Add ICom Identifier into Tx data */
      u32TxData  = WIM__mPackIComIdent(WIM__nRestoreWarningsCheckComplexDone);

      /*************************************/
      /* Send uint32 TxData by using DPOOL */
      /*************************************/
      enDpoolReturn = DPOOL_enSetPoolData(DPOOL_nDataWIM_u32IcomDataGc_Queue, &u32TxData);

      /*************************************/
      /* Check DPOOL QUEUE Result          */
      /*************************************/
      if (
         /* was Data sent successfully (into queue) */
         enDpoolReturn != E_DATA_OK
         )
      {
         /* Throw an Exception for trace ICOM QUEUE overflow */
         WIM__vRaiseException(WIM_nErrIcom);   
      }

   }

   /**
   * Replacement for RequestControl Function!!! 
   * Warning states handled by RequestControl has to be reset.
   *   @return  void
   *   @param   void
   *   @author  L.Gruenewald, Schleissheimer GmbH 
   */
   void WIM__vStartResetWarningsRequestControl_GC(void)
   {
      /***************************************************************************
      * FUNCTION LOCAL DEFINITIONS
      ****************************************************************************/
      /* local Data for transmit by Icom       */
      uint32 u32TxData = 0;
      /* Returnvalue of DPOOL API              */
      DPOOL_tenStatusType    enDpoolReturn = E_DATA_COM_LIMIT;         

      /***************************************************************************
      * FUNCTION CODE
      ****************************************************************************/
      /* Drop all further incoming OnEvent Icom-Events */
      WIM__boResetWarningsActive = True;
      /* Add ICom Identifier into Tx data */
      u32TxData  |= WIM__mPackIComIdent(WIM__nStartResetWarningsGcToAc);

      /*************************************/
      /* Send uint32 TxData by using DPOOL */
      /*************************************/
      enDpoolReturn = DPOOL_enSetPoolData(DPOOL_nDataWIM_u32IcomDataGc_Queue, &u32TxData);
      /* Trigger application checked warnings (complex condition) 
      *  Results are queued in after StartResetWarnings */ 

      /* Start Timer for timeout handling */
      WIM__vStartTimer(WIM__nTimerTmOutReset, WIM_nenInvalidMsg);

      WIM__vCheckComplexWarnings_GC();

      /*************************************/
      /* Check DPOOL QUEUE Result          */
      /*************************************/
      if (
         /* was Data sent successfully (into queue) */
         enDpoolReturn != E_DATA_OK
         )
      {
         /* Throw an Exception for trace ICOM QUEUE overflow */
         WIM__vRaiseException(WIM_nErrIcom);   
      }

   }

   /**
   * Timer callback function.
   * Called if one of the handshake mechanism relevant timers has elapsed.
   * - WIM__nTimerTmOutRestore Timeout for RestoreWarnings mechanism
   * - WIM__nTimerTmOutReset   Timeout for ResetAllWarnings mechanism
   *   @return  void
   *   @param   enTimer: Timer identifier, xCorrTag: Correlation tag (e.g. message Id)
   *   @author  L.Gruenewald, Schleissheimer GmbH 
   */
   void WIM__vResetRestoreTimer(WIM__tenTimer enTimer, WIM__txCorrTag xCorrTag)
   {
      /***************************************************************************
      * FUNCTION CODE
      ****************************************************************************/
      switch (enTimer)
      {
      case WIM__nTimerTmOutRestore:
         /* Restart RestoreWarnings */
         WIM__vRestoreWarnings();
         break;
      case WIM__nTimerTmOutReset:
         /* Restart ResetAllWarnings */
         WIM__vResetAllWarnings();
         break;
      default:
         /* invalid timer configuration */
         WIM__vRaiseException(WIM_nErrConfig);
         break;
      }
      /* ICom Error cause stuck the handshake mechanism between AC and GC */
      WIM__vRaiseException(WIM_nErrIcom);
   }

   /**
   * This function retrieves the HIL-Id of the current displayed message if any.
   *   @return  True: message present (HIL valid), False: no message (HIL invalid)
   *   @param   pointer to uint32, contains HIL on output
   *   @author  T.Godemann, Schleissheimer GmbH 
   */
   bool WIM__boGetDisplayMaster(uint32* pu32HilId)
   {
      /***************************************************************************
      * FUNCTION LOCAL DEFINITIONS
      ****************************************************************************/
      /* set default value */
      bool boReturn = False;
      *pu32HilId = 0;

      /***************************************************************************
      * FUNCTION CODE
      ****************************************************************************/
      if(WIM__enDspMaster != WIM_nenInvalidMsg)
      {
         boReturn = True;
         *pu32HilId = WIM__u32GetHilId(WIM__enDspMaster);
      }

      return boReturn;
   }

/* EOF */