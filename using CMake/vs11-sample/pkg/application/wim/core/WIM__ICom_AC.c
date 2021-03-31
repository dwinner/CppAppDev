/******************************************************************************
*=====================    Copyright by Continental AG    ======================
*******************************************************************************
* Titel        : WIM__ICom_AC.c
*
* Description  : Package private interface of icom-class:
*                ICom services AC
*                Private class that manages DPOOL access
*                package WIM
*
* Environment  : OSEK, JCP (NEC )

* Responsible  : L.Gruenewald, Schleissheimer GmbH
*
* Guidelines   : SMK 3.3  
*
* Template name: OOLite Codefile, Revision 1.0
*
* CASE-Tool    : Together Controlcenter, Version 6.2
*
* Revision List: (Will be filled by PVCS)
* Archive: $Log: WIM__ICom_AC.c  $
* Archive: Revision 1.9 2015/06/17 18:42:34CEST Wenske-EXT, Martin (uidj8453) 
* Archive: DC MR 47461 : runtime of BasicApp_Prio2 too long
* Archive: Revision 1.8 2014/07/29 18:34:19CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 41682 : WIM/AC: Prevent sporadic flicker of GC controlled complex warnings after Kl15ACC
* Archive: Revision 1.7 2014/04/17 14:08:31CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 39277: WIM: Sending of WIM HIL ID on CAN
* Archive: Revision 1.6 2014/04/08 17:13:02CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 40060 : 213/AC, WIM: Sending of SLACK HIL ID on CAN
* Archive: Revision 1.5 2014/03/28 15:23:33CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 39277 : WIM: Sending of WIM HIL ID on CAN
* Archive: Revision 1.4 2014/03/21 12:14:39CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 39404 : 213-AC, WIM: Changes in CAN flag handling and persistent storage of Wake IC warning states
* Archive: Revision 1.3 2013/09/17 13:10:09CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 34947: prevent PF3 compiler warnings
* Archive: DC MR 34940: BR213, WIM: Acoustic of door warning shall not be retriggered by another door
* Archive: DC MR 34883: WIM: Persistent storage of warn states for wake-IC warnings
* Archive: Revision 1.2 2013/05/17 13:42:22CEST Immel-EXT, Marc (uid37561) 
* Archive: D MR 33414: BR213/AC, E004, WIM: Takeover of the latest changes from BR222/BR205
* Archive: Revision 1.1 2013/03/21 16:26:49CET Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/adapt/BR213IC_AC_EL_SOP/project.pj
* Archive: Revision 1.2 2012/11/21 11:43:45CET Immel Marc (uid37561) (uid37561) 
* Archive: Migration of WIM-AC from PVCS to MKS 
* Archive: - used release: DC.SW.PAC.WIM_205IC_AC_COMMON_VarW.V01.00.pre17
* Archive: Revision 1.1 2011/11/08 12:59:36CET uid37556 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/adapt/project.pj
* 
*    Rev 1.2   Jun 15 2012 16:18:22   SCHL_Dirk.Gottwalles
* DC MR 26067: W205, E009/AC, WIM: New configuration CPAPlus_Menu_active
* DC MR 26325: W205, E009/AC, WIM: Boundary and Retrigger condition of protocol_class_2
* DC MR 25952: W205, E009/AC, WIM: Change of Prio1Mute and Lowering times - ÄLP2873
* 
*    Rev 1.1   May 18 2012 16:55:54   SCHL_Dirk.Gottwalles
* DC MR 25587: WDM21151/34246/35637: SBW/WIM Acoustic corrections
* DC MR 25914: W205, E009/AC, HIL: Mapping of WIM sound types
* 
*    Rev 1.0   Nov 08 2011 14:39:04   SCHL_Dirk.Gottwalles
* Initial revision.
* 
****************************************************************************/

/***************************************************************************
* HEADER-FILES (Only those that are needed in this file)
****************************************************************************/

/* System-headerfiles */
#include "cdef.h"

/* Foreign headerfiles */

/* Own headerfiles */
#include "WIM_c1.h"
#include "WIM__ICom_AC.h"

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

/**
* WakeIC state of message
*/
bool WIM__aboWakeICStates[WIM__nMaxWakeIcMsgCount];

/******************************************************************************
* FILE LOCAL DEFINITIONS
*******************************************************************************/

/**
* Storage for the last HIL-ID-displayed, posted from GC by ICom.
* @range  uint32
* @values possible HIL-IDs and WIM__nInvalidHilId
*/
uint32 WIM__u32CurrentDspMsg = WIM__nInvalidHilId;


/*********************
* VARIABLES/CONSTANTS
**********************/

/**
* display master change container 
*/
static const WIM_tpvChangeCb WIM__apvDspChangeContainer_AC[] =
{  
   /* content defined in configuration */
   WIM__nDspChangeContainerContent_AC
   WIM__nLastCntEntry /* must always be the last entry */
};

/**
* ManuQuit container 
*/
static const WIM_tpvManuQuitCb WIM__apvManuQuitContainer[] = 
{
   /* content defined in configuration */
   WIM__nManuQuitContainerContent
   WIM__nLastCntEntry /* must always be the last entry */
};

/**
* PreConfirmation container 
*/
static const WIM_tpvPreConfirmationCb WIM__apvPreConfirmationContainer[] = 
{
   /* content defined in configuration */
   WIM__nPreConfirmationContainerContent
   WIM__nLastCntEntry /* must always be the last entry */
};

/**
* CheckComplex container 
*/
static const WIM_tpvCheckWarnCb WIM__apvCheckComplexContainer[] = 
{
   /* content defined in configuration */
   WIM__nCheckComplexContainerContent
   WIM__nLastCntEntry /* must always be the last entry */
};

/******************************************************************************
* FILE LOCAL FUNCTION PROTOTYPES
*******************************************************************************/
static void WIM__vDspChangeContainer_AC(uint32 u32HilId);
static void WIM__vManuQuitContainer(uint32 u32HilId, WIM_tenDisplayEvent enDispEvt);
static void WIM__vPreConfirmationContainer(uint32 u32HilId);

/******************************************************************************
* PACKAGE LOCAL FUNCTIONS - Initialisation
*******************************************************************************/
/**
* Initialise ICom internal components.
*   @return  void
*   @param   void
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
void WIM__vIComInit_AC(void)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   WIM__boRestoreWarningsActive = False;  
   WIM__boResetWarningsActive   = False;
   WIM__u32CurrentDspMsg = WIM__nInvalidHilId;
}

/******************************************************************************
* PACKAGE LOCAL FUNCTIONS - SYSTEM CALLS
*******************************************************************************/

/**
* Displacement on AC for Central event function on GC.
* Sending all received Events with the pending Msg by using the ICom mechanism
* into the GC to process this Data.
* Additionally the Registered Flag (redundant copy on Ac) is set after an 
* Successfully sending.
*   @return  ---
*   @param   enMsg: Message identifier, enEvt: Event identifier
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
void WIM__vOnEvent_AC(WIM_tenMsg enMsg, WIM__tenEventIntern enEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint32                 u32DpoolDataTx = 0;                       /* Initialise DPOOL Data for TX          */
   WIM__tenIComIdentifier enIComTxIdentifier = WIM__nOnEventAcToGc; /* Identifier for Tx Data                */
   DPOOL_tenStatusType    enDpoolReturn = E_DATA_COM_LIMIT;         /* Returnvalue of DPOOL API              */
   uint32                 u32IndexWakeIcMessage;                    /* Index of WakeIc Warning */


   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/

   if(/* No reset/restore mechanism is active */
      WIM__boRestoreWarningsActive == False &&
      WIM__boResetWarningsActive == False)
   {
      if (/* event in valid range? */
         (enEvt < WIM__nNoOfStateEvents)
         /* message identifier in range? */
         && (enMsg < WIM__mGetNoOfMessages))
      {
         /***********************/
         /* Build uint32 TxData */
         /***********************/
         /* First Part of TxData is the enMsg */
         u32DpoolDataTx = WIM__mPackMsgEnum(enMsg);

         /* Add call Event for OnEvent Fct 0x00YY0000*/
         u32DpoolDataTx |= WIM__mPackByte3(enEvt);

         /* Add ICom Identifier for decoding on GC 0xYY000000 */
         u32DpoolDataTx |= WIM__mPackIComIdent(enIComTxIdentifier);


         /*************************************/
         /* Send uint32 TxData by using DPOOL */
         /*************************************/
         enDpoolReturn = DPOOL_enSetPoolData(DPOOL_nDataWIM_u32IcomDataAc_Queue, &u32DpoolDataTx);


         /*******************/
         /* Set Flags on Ac */
         /*******************/
         if (
            /* was Data sent successfully (into queue) */
            enDpoolReturn == E_DATA_OK
            && enDpoolReturn != E_DATA_COM_LIMIT
            )
         {
            /*** handle "Registered" and "Canceled" flags here */
            if (/* set the flags if "Register" or "Retrigger" */
                (enEvt == WIM__nRegister) || (enEvt == WIM__nRetrigger) )
            {
               /* Flag handling */
               WIM__mSetRegFlag(enMsg, On);
               WIM__mSetCanceledFlag(enMsg, Off);
               /* check WMN notification */
               WIM__vDoWmnReport(enMsg, WIM__nOnEdge);
            }
            if (enEvt == WIM__nWakeIC)
            {
               u32IndexWakeIcMessage = WIM__u32GetWakeICMsg(enMsg);
               /* Set WakeIc State Bit */
               WIM__vSetWakeICState(u32IndexWakeIcMessage, True);
            }
            if (/* reset/set the flags if "Delete" or "Cancel" */
                (enEvt == WIM__nCancel) || (enEvt == WIM__nDelete) )
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
               /* Index of WakeIC message */
               u32IndexWakeIcMessage = WIM__u32GetWakeICMsg(enMsg);
               /* Delete WakeIc State Bit */
               WIM__vSetWakeICState(u32IndexWakeIcMessage, False);
               /* check WMN notification */
               WIM__vDoWmnReport(enMsg, WIM__nOffEdge);
            }
         }
         else
         {
            /* Flags are not set, on next check cycle retry send by ICOM*/
            /* Throw an Exception for trace ICOM QUEUE overflow */
            WIM__vRaiseException(WIM_nErrIcom);   
         }
      }
      else
      {
         /* invalid parameter -> raise exception */
         WIM__vRaiseException(WIM_nErrState);
      }
   }
}

/**
* Send feedback for Gc that Ac had finished Restore all Warnings
* and further comming OnEvent - QueueEvents has to be used.
*   @return  void
*   @param   void
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
void WIM__vFinishedRestoreWarningsActivateICom(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   /* local Data for transmit by Icom       */
   uint32 u32DpoolDataTx = 0;
   /* Returnvalue of DPOOL API              */
   DPOOL_tenStatusType    enDpoolReturn = E_DATA_COM_LIMIT;         

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* Add ICom Identifier into Tx data */
   u32DpoolDataTx  = WIM__mPackIComIdent(WIM__nRestoreWarningsBeginReCheckAcToGc);

   /*************************************/
   /* Send uint32 TxData by using DPOOL */
   /*************************************/
   enDpoolReturn = DPOOL_enSetPoolData(DPOOL_nDataWIM_u32IcomDataAc_Queue, &u32DpoolDataTx);
   /* Activate OnEvent ICom communication */
   WIM__boRestoreWarningsActive = False;

   /*************************************/
   /* Check DPOOL QUEUE Result          */
   /*************************************/
   if (/* was Data sent successfully (into queue) */
       enDpoolReturn != E_DATA_OK)
   {
      /* Throw an Exception for trace ICOM QUEUE overflow */
      WIM__vRaiseException(WIM_nErrIcom);   
   }
}

/**
* Send feedback for Gc that Ac had finished re-check all Warnings
* and the Scheduler has to be restarted, retriggered.
*   @return  void
*   @param   void
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
void WIM__vFinishedRestoreWarnings_AC(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   /* local Data for transmit by Icom       */
   uint32 u32DpoolDataTx = 0;
   /* Returnvalue of DPOOL API              */
   DPOOL_tenStatusType    enDpoolReturn = E_DATA_COM_LIMIT;         

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* Add ICom Identifier into Tx data */
   u32DpoolDataTx  = WIM__mPackIComIdent(WIM__nRestoreWarningsDoneReCheckAcToGc);

   /*************************************/
   /* Send uint32 TxData by using DPOOL */
   /*************************************/
   enDpoolReturn = DPOOL_enSetPoolData(DPOOL_nDataWIM_u32IcomDataAc_Queue, &u32DpoolDataTx);

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
* Send feedback for Gc that Ac had finished Reset all Warnings
* and further comming OnEvent-QueueEvents has to be used.
*   @return  void
*   @param   void
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
void WIM__vFinishedResetWarningsActivateICom(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   /* local Data for transmit by Icom       */
   uint32 u32DpoolDataTx = 0;
   /* Returnvalue of DPOOL API              */
   DPOOL_tenStatusType    enDpoolReturn = E_DATA_COM_LIMIT;         

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* Add ICom Identifier into Tx data */
   u32DpoolDataTx  = WIM__mPackIComIdent(WIM__nResetWarningsFinishedAcToGc);

   /*************************************/
   /* Send uint32 TxData by using DPOOL */
   /*************************************/
   enDpoolReturn = DPOOL_enSetPoolData(DPOOL_nDataWIM_u32IcomDataAc_Queue, &u32DpoolDataTx);
   /* Enable all further OnEvent calls */
   WIM__boResetWarningsActive = False;

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
* PowerOn initialisation of State Handler. Only the redundant copy of StateHandler Flags
* are initiated this time!!!
*   @return  void
*   @param   none
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
void WIM__vStateHandlerInit_AC(void)
{
   /* clear dynamic states of all messages on AC */
    memset(WIM__astMsgStates, 0, WIM__mGetNoOfMessages * sizeof(WIM__tstMsgState));
}

/**
* PowerOn initialisation of WakeIC states. 
*   @return  void
*   @param   none
*   @author  A.Wagner, Schleissheimer GmbH 
*/
void WIM__vWakeIcStateInit(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   /* Returnvalue of DPOOL API                                         */
   DPOOL_tenStatusType    enDpoolReturn; 
   /* Loop variable for the State Bits of the DPOOL_nDataWIM_u32WakeIcWarningsLow variable */
   uint32 u32LoopIndex = 0;
   /* Local Variable to store DPOOL Data for Processing */
   uint32 u32StateBitWakeIcLow;
   /* Local Variable to store DPOOL Data for Processing */
   uint32 u32StateBitWakeIcHigh;
   /* Variable for end of loop */
   uint32 u32loopEnd = 0;
   /* Loop variable End for Bits 1 to 32 */
   uint32 u32LoopEndLow = 32;
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* Init wake ic state array */
   memset(WIM__aboWakeICStates, 0, WIM__nMaxWakeIcMsgCount);
   /* receive Data */
   enDpoolReturn = DPOOL_enGetPoolData(DPOOL_nDataWIM_u32WakeIcWarningsLow, &u32StateBitWakeIcLow);
   u32LoopEndLow = ((WIM__nMaxWakeIcMsgCount >= u32LoopEndLow) ? u32LoopEndLow : WIM__nMaxWakeIcMsgCount);
   /* Getting DPOOL Data are succesfully */
   if(enDpoolReturn == E_DATA_OK)
   {
      /* Set the bits 1 to 32 of the wake-ic warnings */
      for(u32LoopIndex = u32loopEnd; u32LoopIndex < u32LoopEndLow; u32LoopIndex++)
      {
         /* set the state only if the state bit is set */
         if((WIM__boGetWakeIcStateBit(u32StateBitWakeIcLow, u32LoopIndex)) == 1)
         {
            WIM__vSetWakeICState(u32LoopIndex, True);
         }
      }
   }
   else
   {
      /* wrong parameter */
      WIM__vRaiseException(WIM_nWrongParameter);
   }  
   /* receive Data */
   enDpoolReturn = DPOOL_enGetPoolData(DPOOL_nDataWIM_u32WakeIcWarningsHigh, &u32StateBitWakeIcHigh);
   /* Getting DPOOL Data are succesfully */
   if (enDpoolReturn == E_DATA_OK)
   {
#ifdef QAC_Analysis
#pragma PRQA_MESSAGES_OFF 3201
#endif // QAC_Analysis
      /* For now this statement is really unreachable, but in the future we can change the WIM__nMaxWakeIcMsgCount */

      /* Set the bits 33 to End of the wake-ic warnings */
      for (u32LoopIndex = u32LoopEndLow; u32LoopIndex < WIM__nMaxWakeIcMsgCount; u32LoopIndex++)
      {
         if ((WIM__boGetWakeIcStateBit(u32StateBitWakeIcHigh, u32LoopIndex - u32LoopEndLow)) == 1)
         {
            WIM__vSetWakeICState(u32LoopIndex, True);
         }
      }

#ifdef QAC_Analysis
#pragma PRQA_MESSAGES_ON 3201
#endif // QAC_Analysis
   }
   else
   {
      /* wrong parameter */
      WIM__vRaiseException(WIM_nWrongParameter);
   }
}

/**
* Save wake-ic state bits to DPOOL data (persistent memory)
*   @return  void
*   @param   none
*   @author  A.Wagner, Schleissheimer GmbH 
*/
void WIM__vWakeIcStateDeInit(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   /* Loop variable for the State Bits of the DPOOL_nDataWIM_u32WakeIcWarningsLow variable */
   uint32 u32LoopIndex = 0;
   /* Local Variable to store DPOOL Data for Processing */
   uint32 u32StateBitWakeIcLow = 0;
   /* Local Variable to store DPOOL Data for Processing */
   uint32 u32StateBitWakeIcHigh = 0;
   /* Variable for end of loop */
   uint32 u32loopEnd = 0;
   /* Loop variable End for Bits 1 to 32 */
   uint32 u32LoopEndLow = 32;
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   u32LoopEndLow = ((WIM__nMaxWakeIcMsgCount >= u32LoopEndLow) ? u32LoopEndLow : WIM__nMaxWakeIcMsgCount);
   /* Set the bits 1 to 32 of the wake-ic warnings */
   for(u32LoopIndex = u32loopEnd; u32LoopIndex < u32LoopEndLow; u32LoopIndex++)
   {
      if( /* Is WakeIc State Bit == True ? */
          WIM__boGetWakeICState(u32LoopIndex))
      {
         u32StateBitWakeIcLow |= (1u << u32LoopIndex);
      }    
   }
   DPOOL_enSetPoolData(DPOOL_nDataWIM_u32WakeIcWarningsLow, &u32StateBitWakeIcLow);

#ifdef QAC_Analysis
#pragma PRQA_MESSAGES_OFF 3201
#endif // QAC_Analysis
   /* For now this statement is really unreachable, but in the future we can change the WIM__nMaxWakeIcMsgCount */

   /* Set the bits 1 to 32 of the wake-ic warnings */
   for (u32LoopIndex = u32LoopEndLow; u32LoopIndex < WIM__nMaxWakeIcMsgCount; u32LoopIndex++)
   {
      if ( /* Is WakeIc State Bit == True ? */
         WIM__boGetWakeICState(u32LoopIndex))
      {
         u32StateBitWakeIcHigh |= (1 << (u32LoopIndex - u32LoopEndLow));
      }
   }

#ifdef QAC_Analysis
#pragma PRQA_MESSAGES_ON 3201
#endif // QAC_Analysis

   DPOOL_enSetPoolData(DPOOL_nDataWIM_u32WakeIcWarningsHigh, &u32StateBitWakeIcHigh);
}

/**
* Helper function to get the WakeIC state bit out of a uint32 variable
*   @return  void
*   @param   none
*   @author  A.Wagner, Schleissheimer GmbH 
*/

bool WIM__boGetWakeIcStateBit(uint32 u32SaveWakeIcState, uint32 u32CountValue)
{
   /* Get State Bit of actually warning */
   u32SaveWakeIcState >>= u32CountValue;
   /* State Bit is now at position [0] */
   /* return State Bit */
   return ((u32SaveWakeIcState & 0x01) == On ? True : False);
}

/**
* This function is called by Interface function on reception of an Event
* which is processed by WIM__ICom
*   @return  void
*   @param   EVHD_tenReceiveEvent enEvent, contains the received Event.
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
void WIM__vDoDpoolEventsByICom_AC(EVHD_tenReceiveEvent enEvent)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   /* Helper for count receive data tries without getting valid data   */
   uint8                  u8NoDataReceived    = 0;    
   /* Returnvalue of DPOOL API                                         */
   DPOOL_tenStatusType    enDpoolReturn;      
   /* Local Variable to store DPOOL Data for Processing                */
   uint32                 u32DpoolDataRx;                     
   /* Identifier for Rx Data                                           */
   WIM__tenIComIdentifier enIComRxIdentifier; 
   /* Storage for HIL-ID if required                                   */
   uint32                 u32HilId            = WIM__nInvalidHilId;      
   /* Storage for Msg Enum if required                                 */
   WIM_tenMsg            enMsg               = WIM_nenInvalidMsg;      
   /* Temporarly byte storage when extract DPOOL data                  */ 
   uint8                  u8Byte1            = 0;                        
   /* Temporarly byte storage when extract DPOOL data                  */ 
   uint8                  u8Byte2            = 0;                        
   /* Temporarly byte storage when extract DPOOL data                  */ 
   uint8                  u8Byte3            = 0;                        
   WIM_tenDisplayEvent    enDspEvt;

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if(/* Check if received Event is the handled event */
       enEvent == EV_DPOOL_Always_WIM_u32IcomDataGc_QueueGC_to_AC_WIM_vDoDpoolEvents)
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
         enDpoolReturn = DPOOL_enGetPoolData(DPOOL_nDataWIM_u32IcomDataGc_QueueGC_to_AC, &u32DpoolDataRx);

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
            case WIM__nContainerManuQuitGcToAc:
               /*********************/
               /* Manu Quit Container was called on GC, call the Container on Ac */
               /*********************/
               /* Extract the HIL-ID */
               u32HilId = WIM__mExtractHilId(u32DpoolDataRx);
               /* Extract the dispaly event identifier */
               enDspEvt = (WIM_tenDisplayEvent)WIM__mExtractDispEvent(u32DpoolDataRx);
               /* Container in ci - Header aufrufen */
               WIM__vManuQuitContainer(u32HilId, enDspEvt);
               break;

            case WIM__nContainerPreConfirmationGcToAc:
               /*********************/
               /* Pre Confirmation Container was called on GC, call the Container on AC */
               /*********************/
               /* Extract the HIL-ID */
               u32HilId = WIM__mExtractHilId(u32DpoolDataRx);
               /* Container in ci - Header aufrufen */
               WIM__vPreConfirmationContainer(u32HilId);
               break;

            case WIM__nContainerDspChangeGcToAc:
               /*********************/
               /* Display Change Container was called on GC, call the Container on Ac */
               /* and store the received HIL-ID as CurrentDspMsg                      */
               /*********************/
               /* Extract the HIL-ID */
               u32HilId = WIM__mExtractHilId(u32DpoolDataRx);
               /* Store the new CurrentDspMsg */
               WIM__u32CurrentDspMsg = u32HilId;
               /* Container in ci - Header aufrufen */
               WIM__vDspChangeContainer_AC(u32HilId);
               break;

            case WIM__nNotifyHandlerGcToAc:
               /*********************/
               /* Notify Handler was called on GC, call AC Handler */
               /*********************/
               /* Extract the HIL-ID */
               u32HilId = WIM__mExtractHilId(u32DpoolDataRx);
               /* Extract the Notify Parameter */
               u8Byte1  = WIM__mExtractByte3(u32DpoolDataRx);
               /* Container in ci - Header aufrufen */
               WIM__mNotifyHandler_AC(u32HilId, (WIM_tenDisplayEvent) u8Byte1);
               break;

            case WIM__nSetFaultMemFlagGcToAc:
               /*********************/
               /* StateHandler on GC used WIM__mSetFaultMemFlag, update the redundant copy on AC */
               /*********************/
               /* Extract the Enum of the Msg which Flag should be set. */
               enMsg = WIM__mExtractMsgEnum(u32DpoolDataRx);
               /* Extract the Flagvalue */
               u8Byte1 = WIM__mExtractByte3(u32DpoolDataRx);
               /* Call the SetFaultMemFlag Macro */
               WIM__mSetFaultMemFlag(enMsg, (bool)u8Byte1);
               break;

            case WIM__nHandleIntConditionGcToAc:
               /*********************/
               /* An GC Application used a IntCondition Interface */
               /*********************/
               /* Extract the HIL-ID */
               u32HilId = WIM__mExtractHilId(u32DpoolDataRx);
               /* Extract the EventIntern Parameter */
               u8Byte1  = WIM__mExtractByte3(u32DpoolDataRx);
               /* Call Handle Int Condition */
               WIM__vHandleIntCondition_AC(u32HilId, (WIM__tenEventIntern)u8Byte1);
               break;

            case WIM__nHandleExtConditionGcToAc:
               /*********************/
               /* EXTKI Application on GC used a ExtCondition Interface */
               /*********************/
               /* Extract the ExtCondition Function */
               u8Byte1  = WIM__mExtractByte1(u32DpoolDataRx);
               /* Extract the ExtCondition Index */
               u8Byte2  = WIM__mExtractByte2(u32DpoolDataRx);
               /* Extract the ExtCondition EventIntern */
               u8Byte3  = WIM__mExtractByte3(u32DpoolDataRx);
               /* Call Handle Ext Condition (generated Function) */
               WIM__vHandleExtCondition((WIM_tenExtEvtFunction)u8Byte1, u8Byte2, (WIM__tenEventIntern)u8Byte3);
               break;

            case WIM__nSetMuteRqGcToAc:
               /*********************/
               /* Forward SetMuteRq by GC */
               /*********************/

               /* Set mute state HU volume */
               WIM__vSetMuteRequest_AC((WIM__tenAcuQualifier)WIM__mExtractByte1(u32DpoolDataRx), (bool)WIM__mExtractByte2(u32DpoolDataRx));
               break;

            case WIM__nSetVolDecRqGcToAc:
               /*********************/
               /* Forward SetVolDecRq by GC */
               /*********************/

               /* Set LoverVolume state HU volume */
               WIM__vSetVolDecRequest_AC((WIM__tenAcuQualifier)WIM__mExtractByte1(u32DpoolDataRx), (bool)WIM__mExtractByte2(u32DpoolDataRx));
               break;

            case WIM__nStartRestoreWarningsGcToAc:
               /*********************/
               /* Gc triggered start of RestoreWarnings */
               /*********************/
               /* Disable all further OnEvent calls */
               WIM__boRestoreWarningsActive = True;
               /* Clear dyn msg warnstates handled by RequestControl*/
               WIM__vStartRestoreWarningsRequestControl_AC();
               break;

            case WIM__nRestoreWarningsCheckComplexDone:
               /*********************/
               /* Gc notifies about check complex warnings done */
               /*********************/
               /* real time message condition check */
               WIM__vReqCtrl25ms();
               /* Allow scheduling on GC */
               WIM__vFinishedRestoreWarnings_AC();
               break;
            case WIM__nStartResetWarningsGcToAc:
               /*********************/
               /* Gc triggered start of ResetWarnings */
               /*********************/
               /* Disable all further OnEvent calls */
               WIM__boResetWarningsActive = True;
               /* Extract the Enum of the delivered wakeup Msg. */
               enMsg = WIM__mExtractMsgEnum(u32DpoolDataRx);
               /* Clear dyn msg warnstates handled by RequestControl*/
               WIM__vStartResetWarningsRequestControl_AC();
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
      }while( /* when called by EVHD poll until the Queue is empty */
         (enDpoolReturn != E_DATA_COM_NOMSG) &&
         /* to prevent infinite loop by bad returnvalue */
         u8NoDataReceived < WIM__nMaxNumRetries); 
   }
}

/**
* Inform AC applications about display master change
*   @return  void
*   @param   HIL Id of new master
*   @author  T.Godemann, Schleissheimer GmbH 
*/
static void WIM__vDspChangeContainer_AC(uint32 u32HilId)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint8 u8Index = 0; /* index variable                                       */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   while (/* loop through all container functions */
      WIM__apvDspChangeContainer_AC[u8Index] != WIM__nLastCntEntry)
   {
      /* call container function */
      (WIM__apvDspChangeContainer_AC[u8Index])(u32HilId);
      u8Index++;
   }
}


/**
* Inform applications to re-check message conditions after message reset
*   @return  void
*   @param   void
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vCheckComplexWarnings_AC(void)
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

/**
* Inform AC applications about driver confirmation of a message
*   @return  void
*   @param   HIL-ID of confirmed message
*   @author  L.Gruenewald, Schleissheimer GmbH 
*/
static void WIM__vManuQuitContainer(uint32 u32HilId, WIM_tenDisplayEvent enDispEvt)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint8 u8Index = 0; /* index variable                                       */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   while (/* loop through all container functions */
          WIM__apvManuQuitContainer[u8Index] != WIM__nLastCntEntry)
   {
      /* call container function */
      (WIM__apvManuQuitContainer[u8Index])(u32HilId, enDispEvt);
      u8Index++;
   }
}


/**
* Inform applications about driver pre confirmation of a message (DiffManQuit).
*   @return  void
*   @param   Hil-Id of the pre confirmed message
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
static void WIM__vPreConfirmationContainer(uint32 u32HilId)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint8 u8Index = 0; /* index variable                                       */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* loop through all container functions */
   while (WIM__apvPreConfirmationContainer[u8Index] != WIM__nLastCntEntry)
   {
      /* call container function */
      (WIM__apvPreConfirmationContainer[u8Index])(u32HilId);
      u8Index++;
   }
}

/**
* Check DPOOL data if it is a WIM Hil Id.
*   @return  void
*   @param   void
*   @author  A.Wagner, Schleissheimer GmbH 
*/
void WIM__vCheckDPOOLWimHilId(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   /* Returnvalue of DPOOL API                                         */
   DPOOL_tenStatusType    enDpoolReturn; 
   /* Value of DPOOL HilId                                             */
   uint32 u32DynamicAreaHilId;
   /* Value of masked DPOOL HilId for WIM                              */
   uint32 u32ValidHilId;
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* receive Data */
   enDpoolReturn = DPOOL_enGetPoolData(DPOOL_nDataICBWMDL_u32DynAreaHilId, &u32DynamicAreaHilId);
   /* Getting DPOOL Data are succesfully */
   if(enDpoolReturn == E_DATA_OK)
   {
      /* Get the actually Hil Id */
      u32ValidHilId = u32DynamicAreaHilId & 0x00FFF000;
      if (/* WIM Hil IDs only 0x00200xxx to 0x0020FFFF are valid */
          u32ValidHilId == 0x00200000
          || u32ValidHilId == 0x0020F000)
      {
         u32ValidHilId = u32DynamicAreaHilId & 0x00FFFFFF;
      }
      else
      {
         u32ValidHilId = 0;
      }
      WIM__vSetHeadUnitHilId(u32ValidHilId);
   }
   else
   {
      /* wrong parameter */
      WIM__vRaiseException(WIM_nWrongParameter);
   }
}

/**
* Check DPOOL data if it is a Slack Hil Id.
*   @return  void
*   @param   void
*   @author  A.Wagner, Schleissheimer GmbH 
*/
void WIM__vCheckDPOOLSlackHilId(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   /* Returnvalue of DPOOL API                                         */
   DPOOL_tenStatusType enDpoolReturn; 
   /* Value of DPOOL HilId                                             */
   uint32 u32SlackHilId;
   /* Value of masked DPOOL HilId for Slack                            */
   uint32 u32ValidHilId;
   /* Value of masked DPOOL HilId for Slack                            */
   uint16 u16Tmp;
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* receive Data */
   enDpoolReturn = DPOOL_enGetPoolData(DPOOL_nDataWIMMDL_u32SlackHilId, &u32SlackHilId);
   /* Getting DPOOL Data are succesfully */
   if(enDpoolReturn == E_DATA_OK)
   {
      /* Get the actually Hil Id */
      u32ValidHilId = u32SlackHilId & 0x00FFF000;
      if (/* Slack Hil IDs only 0x00201xxx are valid (also custom SLAck's 0x0020Fxxx for VS11) */
          u32ValidHilId == 0x00201000 || u32ValidHilId == 0x0020F000)
      {
         u16Tmp = (uint16)(u32SlackHilId & 0x00000FFF);
      }      
      else
      {
         u16Tmp = 0;
      }

      WIM__vSetHeadUnitSlackHilId(u16Tmp);
   }
   else
   {
      /* wrong parameter */
      WIM__vRaiseException(WIM_nWrongParameter);
   }
}
/* EOF */
