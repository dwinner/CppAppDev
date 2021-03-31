/******************************************************************************
*=====================      Copyright by Continental AG      ==================
*******************************************************************************
* Titel        : WIM__StateAccessHelpers.c
*
* Description  : Message attribute access helpers definitions
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
* Archive: $Log: WIM__StateAccessHelpers.c  $
* Archive: Revision 1.2 2014/08/13 18:27:52CEST Immel-EXT, Marc (uid37561) 
* Archive: - removed unknown tokes at the start of the file
* Archive: Revision 1.1 2013/10/18 16:39:56CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
*/

/******************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*******************************************************************************/
/* System-headerfiles */

/* Foreign headerfiles */

/* Own headerfiles */
#include "WIM__StateAccessHelpers.h"

/******************************************************************************
* ATTRIBUTE ACCESS HELPERS
*******************************************************************************/
static bool WIM__boGetStateAttr_Acu    (WIM__tenAttrId enAttr, WIM_tenMsg enMsg);
/**
* Attribute access helper:
* Get state attribute flag for warning message
*   @return  bool: True, if Flag is set, False if not
*   @param   enAttr Attribute Id, enMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boGetStateAttr_Msg(WIM__tenAttrId enAttr, WIM_tenMsg enMsg)
{  
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   /* state attribute struct */
   WIM__tstStateAttr* pstAttr = \
      (WIM__tstStateAttr*)WIM__mGetMsgPropertyTable[enMsg].pvStateAttr;
   bool boReturn = False; /* return value */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (pstAttr)
   {
      switch (enAttr)
      {
         case WIM__nAttrUrgent:
            boReturn = (pstAttr->biUrgent == On);
            break;
         case WIM__nAttrWakeIc:
            boReturn = (   pstAttr->bi2WakeIC == WIM__nWakeup 
                        || pstAttr->bi2WakeIC == WIM__nWakeKeepActive);
            break;
         case WIM__nAttrKeepActiveIc:
            boReturn = (   pstAttr->bi2WakeIC == WIM__nKeepActive 
                        || pstAttr->bi2WakeIC == WIM__nWakeKeepActive);
            break;
         case WIM__nAttrAutoQuit:
            boReturn = (pstAttr->biAutoQuit == On);
            break;
         case WIM__nAttrPretermAuto:
            boReturn = (pstAttr->biPretermAutoQuit == On);
            break;
         case WIM__nAttrRetrigAuto:
            boReturn = (pstAttr->biAutoQuitRetrig == On);
            break;
         case WIM__nAttrRetrigManu:
            boReturn = (pstAttr->biManuQuitRetrig == On);
            break;
         case WIM__nAttrFaultMem:
            boReturn = (pstAttr->biFaultMemory == On);
            break;
         case WIM__nAttrFaultMemClr:
            boReturn = (pstAttr->biEraseFaultMemory == On);
            break;
         case WIM__nAttrAcuSync:
            boReturn = (pstAttr->bi2Acoustic == WIM__nActiveDspSync);
            break;
         case WIM__nAttrWithAcu:
            boReturn = (pstAttr->bi2Acoustic != WIM__nAcuStateInactive);
            break;
         default:
            break;
      }
   }
   return boReturn;
}

/**
* Attribute access helper:
* Get state attribute flag for warning message with partner
*   @return  bool: True, if Flag is set, False if not
*   @param   enAttr Attribute Id, enMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boGetStateAttr_MsgPtnr(WIM__tenAttrId enAttr, WIM_tenMsg enMsg)
{  
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   /* state attribute struct */
   WIM__tstStateAttrPtnr* pstAttr = \
      (WIM__tstStateAttrPtnr*)WIM__mGetMsgPropertyTable[enMsg].pvStateAttr;
   bool boReturn = False; /* return value */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (pstAttr)
   {
      switch (enAttr)
      {
         case WIM__nAttrUrgent:
            boReturn = (pstAttr->biUrgent == On);
            break;
         case WIM__nAttrWakeIc:
            boReturn = (   pstAttr->bi2WakeIC == WIM__nWakeup 
                        || pstAttr->bi2WakeIC == WIM__nWakeKeepActive);
            break;
         case WIM__nAttrKeepActiveIc:
            boReturn = (   pstAttr->bi2WakeIC == WIM__nKeepActive 
                        || pstAttr->bi2WakeIC == WIM__nWakeKeepActive);
            break;
         case WIM__nAttrAutoQuit:
            boReturn = (pstAttr->biAutoQuit == On);
            break;
         case WIM__nAttrPretermAuto:
            boReturn = (pstAttr->biPretermAutoQuit == On);
            break;
         case WIM__nAttrRetrigAuto:
            boReturn = (pstAttr->biAutoQuitRetrig == On);
            break;
         case WIM__nAttrRetrigManu:
            boReturn = (pstAttr->biManuQuitRetrig == On);
            break;
         case WIM__nAttrFaultMem:
            boReturn = (pstAttr->biFaultMemory == On);
            break;
         case WIM__nAttrFaultMemClr:
            boReturn = (pstAttr->biEraseFaultMemory == On);
            break;
         case WIM__nAttrAcuSync:
            boReturn = (pstAttr->bi2Acoustic == WIM__nActiveDspSync);
            break;
         case WIM__nAttrWithAcu:
            boReturn = (pstAttr->bi2Acoustic != WIM__nAcuStateInactive);
            break;
         default:
            break;
      }
   }
   return boReturn;
}
   
/**
* Attribute access helper:
* Get state attribute flag for warning message with partner
*   @return  bool: True, if Flag is set, False if not
*   @param   enAttr Attribute Id, enMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
static bool WIM__boGetStateAttr_Acu(WIM__tenAttrId enAttr, WIM_tenMsg enMsg)
{  
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   /* state attribute struct */
   WIM__tstStateAttrAcu* pstAttr = \
      (WIM__tstStateAttrAcu*)WIM__mGetMsgPropertyTable[enMsg].pvStateAttr;
   bool boReturn = False; /* return value */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (pstAttr)
   {
      switch (enAttr)
      {
         case WIM__nAttrWakeIc:
            boReturn = (   pstAttr->bi2WakeIC == WIM__nWakeup 
                        || pstAttr->bi2WakeIC == WIM__nWakeKeepActive);
            break;
         case WIM__nAttrKeepActiveIc:
            boReturn = (   pstAttr->bi2WakeIC == WIM__nKeepActive 
                        || pstAttr->bi2WakeIC == WIM__nWakeKeepActive);
            break;
         default:
            break;
      }
   }
   return boReturn;
}

/**
* Attribute access helper:
* Get state attribute flag
*   @return  bool: True, if Flag is set, False if not
*   @param   enAttr Attribute Id, enMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boGetStateAttr(WIM__tenAttrId enAttr, WIM_tenMsg enMsg)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boReturn = False; /* return value */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (enMsg < WIM__mGetNoOfMessages)
   {
      /* call type specific subfunction */
      switch (WIM__menGetMsgType(enMsg))
      {
         case WIM__nWarning:
         case WIM__nHandling:
            boReturn = WIM__boGetStateAttr_Msg(enAttr, enMsg);
            break;
         case WIM__nHandlingPtnr:
         case WIM__nWarningPtnr:  
            boReturn = WIM__boGetStateAttr_MsgPtnr(enAttr, enMsg);
            break;
         case WIM__nAcoustic:
            boReturn = WIM__boGetStateAttr_Acu(enAttr, enMsg);
            break;
         default:
            break;
      }
   }
   return boReturn;
}


/**
* Attribute access helper:
* Get message ID of partner message
*   @return  WIM_tenMsg: valid message Id if partner present, WIM_nenInvalidMsg otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
WIM_tenMsg WIM__enGetPartnerMsg(WIM_tenMsg enMsg)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (enMsg < WIM__mGetNoOfMessages)
   {
      switch (WIM__menGetMsgType(enMsg))
      {
      case WIM__nWarningPtnr:
      case WIM__nHandlingPtnr:
         enMsg = WIM__mGetMsgPropertyTable[enMsg].pvStateAttr
            ? ((WIM__tstStateAttrPtnr*)WIM__mGetMsgPropertyTable[enMsg].pvStateAttr)->enPartner
            : WIM_nenInvalidMsg;
         break;
      default:
         enMsg = WIM_nenInvalidMsg;
         break;
      }
   }
   return enMsg;
}

/**
* Helper function for Scheduler accessing stae attributes for Acoustic
*   @return  bool: True if display synchroneous acoustic, False otherwise
*   @param   WIM_tenMsg Message identifier
*   @author  T.Godemann, Schleissheimer GmbH 
*/
bool WIM__boIsDspSyncAcoustic(WIM_tenMsg enMsg)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   bool boReturn = False; /* return value */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* decide whether we have a display sync. acoustic or not */
          (enMsg < WIM__mGetNoOfMessages) 
       && WIM__mboIsDspSyncAcu(enMsg))
   {
      boReturn = True;
   }
   return boReturn;
}

/**                                                                      
* The function returns the message's priority level
*   @return  priority level of message (0 == highest)                    
*   @param   uint32 u32HilId: HIL ID of message to evaluate                       
*   @author  T.Godemann, Schleissheimer GmbH                             
*/                                                                       
uint8 WIM__u8GetMsgPrioLevel(WIM_tenMsg enMsg)                           
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint8 u8Level;                        /* return value: priority level      */
   uint8 u8Index;                        /* loop variable                     */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* start with lowest priority */
   u8Level = WIM__mGetLowestPrioLevel;
   if (/* valid? */
       enMsg < WIM__mGetNoOfMessages)
   {
      for ( u8Index = 0; 
           (u8Index < WIM__mGetNoOfPrioLevels) && (enMsg < WIM__mGetNoOfMessages); 
            u8Index++)
      {
         if (   (enMsg >= WIM__mGetPrioTable[u8Index].enLevelStart) 
             && (enMsg <= WIM__mGetPrioTable[u8Index].enLevelEnd  ))
         {
            /* we found the prio level! */
            u8Level = WIM__mGetPrioTable[u8Index].u8Prio; 
            enMsg = WIM__mGetNoOfMessages;
         }
      }
   }
   return u8Level;
}

/**
* helper function: set/clear fault memory flag
*   @return  void
*   @param   WIM_tenMsg: Message identifier
*   @param   bool boSet: True set flag, False clear flag
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vSetFaultMemFlag(WIM_tenMsg enMsg, bool boSet)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (enMsg < WIM__mGetNoOfMessages)
   {
      if (/* changed? */
          boSet != WIM__mboGetFaultMemFlag(enMsg))
      {
         /* set/clear flag */
         WIM__mSetFaultMemFlag(enMsg, boSet);

            /* update message counter */
            if (boSet)
            {
               /* notify fault memory menu */
               /* One additional Warning in MenuFaultMemory */
               WIM__vMenuFaultMemEntriesChanged(enMsg, True);
            }
            else
            {
               /* notify fault memory menu */
               /* One Warning less in MenuFaultMemory */
               WIM__vMenuFaultMemEntriesChanged(enMsg, False);
            }
      }
   }
}

/**
* Attribute access helper:
* Get attribute for slack warning display time
*   @return  uint16: display time for slack in ms
*   @param   enMsg: Identifier of message
*   @author  M.Wenske, Schleissheimer GmbH 
*/
uint16 WIM__u16GetSlackDispTime(WIM_tenMsg enMsg)
{  
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   if (enMsg < WIM_nenNoOfMessages)
      return WIM__mGetMsgPropertyTable[enMsg].u16SlackDispTime;
   else
      return 0;
}