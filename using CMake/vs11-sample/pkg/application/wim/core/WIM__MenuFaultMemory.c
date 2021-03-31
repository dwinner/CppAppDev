/******************************************************************************
*=====================    Copyright by Continental AG    ======================
*******************************************************************************
* Titel        : WIM__MenuFaultMemory.c
*
* Description  : The menu client WIM__FaultMemory by TPOL is activated and is
*                part of the Main menu 'SERVICE'. The stored errors while driving
*                are indicated.
*
* Environment  : OSEK, JCP (NEC V850)
*
* Responsible  : L. Gruenewald, Schleissheimer GmbH
*
* Guidelines   : SMK 3.3
*
* Template name: OOLite Codefile, Revision 1.0
*
* CASE-Tool    : Together Controlcenter, Version 6.2
*
* Revision List: (Will be filled by PVCS)
* Archive: $Log: WIM__MenuFaultMemory.c  $
* Archive: Revision 1.1.2.4 2014/05/19 15:32:28CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 40623 : BR213, new BAK: Replace use of KBD up/down by new OFN events
* Archive: Revision 1.1.2.3 2013/08/16 13:30:17CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 33822 : IC213EL-GC WIM: display synchroneous periodic tone not stopped with display off: WDM62157
* Archive: DC MR 33932 : IC213EL GC WIM: Initial sound requests for warnings does not work if sound system is not ready
* Archive: DC MR 33999 : BR213GC-EL, E005, WIM, CWMDL: API split - ORM5621
* Archive: DC MR 34028 : BR213EL, E005, StyleGuide Validation and implementation
* Archive: DC MR 34202 : BR213IC-GC-EL, WIM: Missing HIL output for seat belt warning acoustics - Folow-Up 33655
* Archive: DC MR 34326 : BR213-GC-EL/E005.1, WIM: Display is on for 2 minutes even when warning has disappeared
* Archive: DC MR 34547 : BR213-EL, E005.1/GC,WIM: Removal of QAC warning
* Archive: DC MR 34706 : BR213-GC-EL, E005.1: Chance DOCG implementation in WIM and TPOL
* Archive: DC MR 34781 : BR213-GC-EL, E005.1, WIM: Inconsistent display output in Fault Memory
* Archive: Revision 1.1.2.2 2012/10/18 16:58:00CEST Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj
* Archive: Revision 1.4 2012/10/18 16:58:01CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 27470: W222, E010/GC, WIM: Active sound shall play to the end when display goes off - ÄLP2896
* Archive: DC MR 29924: E010: WIM acoustic problems: corrections for WDM53980, 53982 and 53999
* Archive: DC MR 29926: W222GC: WDM47699 WIM do not differs between Frontal and Lateral Collision warning sound
* Archive: DC MR 29928: W222, E010/GC, WIM: Sync acoustic is delayed too long
* Archive: DC MR 29866: BR222, E010/GC, WIM: Redesign of fault memory entry management
* Archive: DC MR 30023: W222IC-GC, E010: When displaying the oil switch warning the GC makes a reset
* Archive: Revision 1.3 2012/10/02 12:26:10CEST Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 27252 BR222 MY - Use Global Storage for HMI internal variables
* Archive: DC MR 29677 W222, E010/GC, WIM: Possible access violation in fault memory
* Archive: DC MR 29701 W222, E010/GC, WIM: Changes for SBW acoustic handling - ÄLP 3082 / missing HIL output for NCAP acoustics - WDM 47538
* Archive: Revision 1.2 2012/05/18 10:42:43CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: Member moved from WIM__MenuFaultMemory.c in project /id/dag_PF3/sw/pkg/wim/core/project.pj[dag_PF3.sw.pkg.wim_COMMON_IC222GC_VarP] to WIM__MenuFaultMemory.c in project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3GC/project.pj[dag_PF3.sw.pkg.wim_COMMON_GenPF3GC_VarX].
* Archive: Revision 1.1 2010/12/17 12:18:20CET Brueggemann Alexander (uidt3637) (uidt3637) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/project.pj
* 
*    Rev 1.1   Dec 17 2010 13:54:14   SCHL_Lars.Gruenewald
* DC MR20897 WIM: Implementation of menu FaultMemory
* 
*    Rev 1.0   Dec 03 2010 15:54:28   SCHL_Lars.Gruenewald
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
#include "WIM_c1.h"                      /* internal configuration                */
#include "WIM__MenuFaultMemory.h"        /* WIM__MenuFaultMemory export interface */
//#include "OFN_ct.h"						 /* OFN event data 						  */

/******************************************************************************
* GLOBAL DEFINITIONS
*******************************************************************************/

/******************************************************************************
* FILE LOCAL DEFINITIONS
*******************************************************************************/
#define WIM__nFaultMemInit 0x0000FFFF
#define WIM__nFaultMemFirstIndex 0x01
#define WIM__nFaultMemNoWarnings 0x00

/******************************************************************************
* FILE LOCAL FUNCTION PROTOTYPES
*******************************************************************************/

static bool WIM__boCheckFaultMemFlagAndPartnerMessage(WIM_tenMsg enMsg);
static WIM_tenMsg WIM__enSearchHigherPrioMsg(WIM_tenMsg enMsgStart);
static WIM_tenMsg WIM__enSearchLowerPrioMsg(WIM_tenMsg enMsgStart);


/******************************************************************************
* GLOBAL FUNCTION DEFINITIONS
*******************************************************************************/

/**
* WIM-'Fault Memory' menu initialisation
*/
void WIM__vMenuFaultMemInit(void)
{
   uint32 u32FaultMemBorderInit = WIM__nFaultMemInit;  /* zero warnings in FaultMem, first warning should displayed is WIM_nenInvalidMsg*/
   uint32 u32FaultMemStateInit  = WIM__nFaultMemInit;  /* warning index 0 displayed in FaultMem, WIM_nenInvalidMsg should displayed in FaultMem*/
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* Set initial DPOOL Data */
   DPOOL_enSetPoolData(DPOOL_nDataWIM_u32FaultMemBorder, &u32FaultMemBorderInit);
   DPOOL_enSetPoolData(DPOOL_nDataWIM_u32FaultMemState, &u32FaultMemStateInit);
}                                                                 



/**
* The total Number of entries in WimFaultMemory is changed. The function is called of
* WIM__vSetFaultMemFlag() on WIM__StateHandler.c.
* To be adapted must:
* - Number of entries in WimFaultMemory (always)
* - current number of the entry in WimFaultMemory (if necessary)
* - Number of Warning Message  (if necessary)
*/
void WIM__vMenuFaultMemEntriesChanged(WIM_tenMsg enChangingMsg, bool boFaultMemFlag)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint16         u16MsgIndex;        /* The Index of Warning in FaultMemory                   */
   uint16         u16MsgNo;           /* The Number of Warning in FaultMemory                  */
   uint32         u32FaultMemState;   /* DPOOL Data Buffer                                     */
   uint32         u32FaultMemBorder;  /* DPOOL Data Buffer                                     */   
   WIM_tenMsg     enMsgToDisplay;     /* The WarnID of Warning should displayed in FaultMemory */   
   WIM_tenMsg     enFirstMsgFaultMem; /* The WarnID of first Warning in FaultMem               */
   WIM_tenMsg     enPartnerMsg;       /* Storage for possible Partner Msg                      */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if ( /* Read pool data */
          E_DATA_OK == DPOOL_enGetPoolData(DPOOL_nDataWIM_u32FaultMemState,  &u32FaultMemState) 
       && E_DATA_OK == DPOOL_enGetPoolData(DPOOL_nDataWIM_u32FaultMemBorder, &u32FaultMemBorder))
   {
      /* Get the parameters from DPOOL copies */
      enMsgToDisplay     = (WIM_tenMsg)WIM__mGetLowWord(u32FaultMemState);
      enFirstMsgFaultMem = (WIM_tenMsg)WIM__mGetLowWord(u32FaultMemBorder);
      u16MsgIndex        = WIM__mGetHighWord(u32FaultMemState);
      u16MsgNo           = WIM__mGetHighWord(u32FaultMemBorder);
      enPartnerMsg       = WIM__enGetPartnerMsg(enChangingMsg);

      if (/* message's fault mem flag was set */ 
          boFaultMemFlag )
      {
         if (/* Check the conditions before adding 'enChangingMsg' */
             WIM__boCheckFaultMemFlagAndPartnerMessage(enChangingMsg) == True)
         {  
            u16MsgNo++; /* increment Msg counter */
            if (/* add before current visible one? */
                enChangingMsg < enMsgToDisplay)
            {
               if (/* replace displayed first entry, index is on the first message */
                   enMsgToDisplay == enFirstMsgFaultMem)
               {
                  enMsgToDisplay = enFirstMsgFaultMem = enChangingMsg;
                  u16MsgIndex = WIM__nFaultMemFirstIndex;
               }
               else
               {
                  u16MsgIndex++;	/* increment Index */
                  if (/* replace first message in FaultMem? */
                      enChangingMsg < enFirstMsgFaultMem)
                  {
                     enFirstMsgFaultMem = enChangingMsg;
                  }
               }
            }
            /* Check for low prio PartnerMsg with set FaultMemFlag added before,
            * if one is set then remove it from FaultMem. (adapt state and border) */
            if (    enPartnerMsg != WIM_nenInvalidMsg
                && WIM__mboGetFaultMemFlag(enPartnerMsg)
                && enPartnerMsg > enChangingMsg )
            {
               u16MsgNo--; /* Decrement Msg counter */
               if (enPartnerMsg <= enMsgToDisplay)
               {
                  if (u16MsgIndex > 1) u16MsgIndex--; /* Decrement Index */
                  /* Is the PartnerMsg the current displayed? */
                  if (enPartnerMsg == enMsgToDisplay)
                  {
                     if (/* Is there a higher prio Msg until FirsMsgFaulMem */
                         enFirstMsgFaultMem < enMsgToDisplay)
                     {
                        /* Search new higher prio Msg */
                        enMsgToDisplay = WIM__enSearchHigherPrioMsg(enMsgToDisplay);
                     }
                     else
                     { 
                        /* The removed warning was the first and the displayed.
                         * Search for new first and set as displayed one too */
                        enFirstMsgFaultMem = enMsgToDisplay = WIM__enSearchLowerPrioMsg(enMsgToDisplay);
                     }
                  }
               }
            }
         }
      }
      else
      {
         /*** message's fault mem flag was cleared */
         if (   enPartnerMsg != WIM_nenInvalidMsg
             && WIM__mboGetFaultMemFlag(enPartnerMsg)
             && enPartnerMsg < enChangingMsg )
         {
            /* Do nothing */
            /* No changes because given Msg is suppressed by higher prio partner anyway.*/
         }
         else
         {
            /* First add lower prio partner Msg if any */  
            if (   enPartnerMsg != WIM_nenInvalidMsg
                && WIM__mboGetFaultMemFlag(enPartnerMsg))
            {
               u16MsgNo++; /* increment Msg counter */
               if (/* add before current visible one? */
                  enPartnerMsg < enMsgToDisplay)
               {
                  if (/* replace displayed first entry, index is on the first message */
                      enMsgToDisplay == enFirstMsgFaultMem)
                  {
                     enMsgToDisplay = enFirstMsgFaultMem = enPartnerMsg;
                     u16MsgIndex = WIM__nFaultMemFirstIndex;
                  }
                  else
                  {
                     u16MsgIndex++;	/* increment Index */
                     if (/* replace first message in FaultMem? */
                        enPartnerMsg < enFirstMsgFaultMem)
                     {
                        enFirstMsgFaultMem = enPartnerMsg;
                     }
                  }
               }
            }
            /* Remove the given Msg */
            u16MsgNo--; /* decrement msg counter */
            if (enChangingMsg <= enMsgToDisplay)
            {
               if (u16MsgIndex > 1) u16MsgIndex--; /* Decrement Index */
               /* Is the Msg the current displayed? */
               if (enChangingMsg == enMsgToDisplay)
               {
                  if (/* Is there a higher prio Msg until FirsMsgFaulMem */
                      enFirstMsgFaultMem < enMsgToDisplay)
                  {
                     /* Search new higher prio Msg */
                     enMsgToDisplay = WIM__enSearchHigherPrioMsg(enMsgToDisplay);
                  }
                  else
                  { 
                     /* The removed warning was the first and the displayed.
                      * Search for new first and set as displayed one too */
                     enFirstMsgFaultMem = enMsgToDisplay = WIM__enSearchLowerPrioMsg(enMsgToDisplay);
                  }
               }
               else if (enChangingMsg == enFirstMsgFaultMem)
               {
                  /* The removed warning was the first message in fault memory 
                   * Search for new first message */ 
                  enFirstMsgFaultMem = WIM__enSearchLowerPrioMsg(enFirstMsgFaultMem); 
               }
            }
         }
      }

      /* Write changed state to DPOOL */
      WIM__mSetLowWord(u32FaultMemState, enMsgToDisplay); 
      WIM__mSetHighWord(u32FaultMemState, u16MsgIndex);
      DPOOL_enSetPoolData(DPOOL_nDataWIM_u32FaultMemState, &u32FaultMemState);
      WIM__mSetLowWord(u32FaultMemBorder, enFirstMsgFaultMem); 
      WIM__mSetHighWord(u32FaultMemBorder, u16MsgNo);
      DPOOL_enSetPoolData(DPOOL_nDataWIM_u32FaultMemBorder, &u32FaultMemBorder);
   }
}


/**
* Key callback-function that is called to handle a key-event.
*/
void WIM__vMenuFaultMemKeyCallback(EVHD_tenReceiveEvent enEvent)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   OFN_tenOfnEvent enOfnEvent;          /* Received Key Event                                    */
   KBD_tunKeyData unKeyData = { 0 };    /* Hard Key data                                         */
   uint32         u32FaultMemState;     /* DPOOL Data Buffer                                     */
   uint32         u32FaultMemBorder;    /* DPOOL Data Buffer                                     */
   uint16         u16MsgIndex;          /* The Index of Warning in FaultMemory                   */
   uint16         u16MsgNo;             /* The Number of Warning in FaultMemory                  */
   WIM_tenMsg     enMsgToDisplay;       /* The WarnID of Warning should displayed in FaultMemory */
   uint8          u8NewKey;             /* Save Received Key Event in u8 Variable                */
   bool           boLastMessage = False;/* Last Message reached                                  */  
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* check for received event */
   if(enEvent == EV_DPOOL_Always_WIM_u8FaultMemEvPrevNext_WIM_vDoHmiEvents)
   {
      if( /* Receive DpoolData and Check validation */
         E_DATA_OK == DPOOL_enGetPoolData(DPOOL_nDataWIM_u8FaultMemEvPrevNext, &u8NewKey))
      {
         /* For further use of enOfnEvent -> overtake u8NewKey via typecast to type enum */
         enOfnEvent = (OFN_tenOfnEvent)u8NewKey;
         unKeyData.stData.u16KeyCode = u8NewKey;

         if( /* Receive DpoolData and Check validation */
               E_DATA_OK == DPOOL_enGetPoolData(DPOOL_nDataWIM_u32FaultMemState, &u32FaultMemState) 
            && E_DATA_OK == DPOOL_enGetPoolData(DPOOL_nDataWIM_u32FaultMemBorder, &u32FaultMemBorder))
         {
            u16MsgIndex    = WIM__mGetHighWord(u32FaultMemState);
            enMsgToDisplay = (WIM_tenMsg)WIM__mGetLowWord(u32FaultMemState);
            u16MsgNo       = WIM__mGetHighWord(u32FaultMemBorder);

            if (SDF_enGetVariant() != SDF_enVariantLowLine)
            {
                /* Key 'UP' pressed ? */
                /* Evaluation for previous Msg */
                if (enOfnEvent == OFN_nenOfnUp)
                {
                    if (/* is the Number of Warning Message in FaultMemory not on the first position ? */
                        enMsgToDisplay > WIM_nenFirstMsg
                        /* and the index is not on first position */
                        && u16MsgIndex > WIM__nFaultMemFirstIndex
                        /* and not invalid ?*/
                        && enMsgToDisplay != WIM_nenInvalidMsg)
                    {
                        /* search the next 'fault memory entry' backwards */
                        for (--enMsgToDisplay; enMsgToDisplay != WIM_nenFirstMsg; enMsgToDisplay--)
                        {
                            /* Fault memory flag: is message stored in fault memory? */
                            /* and no more highly priore partner message ?           */
                            if (WIM__boCheckFaultMemFlagAndPartnerMessage(enMsgToDisplay))
                            {
                                /* next Number of Warning Message in FaultMemory backward is found */
                                /* decrement current index of the entry in WimFaultMemory */
                                u16MsgIndex--;
                                /* and left the loop */
                                break;
                            }
                        }
                    }
                }
                /* Key 'DOWN' pressed ? */
                /* Evaluation for next Msg */
                if (enOfnEvent == OFN_nenOfnDown)
                {

                    if (/* is the Number of Warning Message in FaultMemory not on the last position ? */
                        enMsgToDisplay < WIM__mGetNoOfMessages
                        /* and the index is not on last position */
                        && u16MsgIndex < u16MsgNo
                        /* and the displayed Warning is a valid one */
                        && enMsgToDisplay != WIM_nenInvalidMsg)
                    {
                        /* search the next 'fault memory entry' forward   */
                        for (++enMsgToDisplay; enMsgToDisplay < WIM__mGetNoOfMessages; enMsgToDisplay++)
                        {
                            /* Fault memory flag: is message stored in fault memory? */
                            /* and no more highly priore partner message ?           */
                            if (WIM__boCheckFaultMemFlagAndPartnerMessage(enMsgToDisplay))
                            {
                                /* next Number of Warning Message in FaultMemory forward is found */
                                /* increment current index of the entry in WimFaultMemory */
                                u16MsgIndex++;
                                /* and left the loop */
                                break;
                            }
                        }
                    }
                }
            }
            else
            {
                /* Key 'DOWN' pressed ? */
                /* Evaluation for next Msg */
                if (unKeyData.stData.u16KeyCode == KBD_nenDown)
                {
                    if (/* is the Number of Warning Message in FaultMemory not on the last position ? */
                        enMsgToDisplay < WIM__mGetNoOfMessages
                        /* and the index is not on last position */
                        && u16MsgIndex < u16MsgNo
                        /* and the displayed Warning is a valid one */
                        && enMsgToDisplay != WIM_nenInvalidMsg)
                    {
                        /* search the next 'fault memory entry' forward   */
                        for (++enMsgToDisplay; enMsgToDisplay < WIM__mGetNoOfMessages; enMsgToDisplay++)
                        {
                            /* Fault memory flag: is message stored in fault memory? */
                            /* and no more highly priore partner message ?           */
                            if (WIM__boCheckFaultMemFlagAndPartnerMessage(enMsgToDisplay))
                            {
                                /* next Number of Warning Message in FaultMemory forward is found */
                                /* increment current index of the entry in WimFaultMemory */
                                u16MsgIndex++;
                                /* and left the loop */
                                break;
                            }
                        }
                    }
                    else if (/* and the index is on last position */
                             u16MsgIndex == u16MsgNo
                             /* and the displayed Warning is a valid one */
                             && enMsgToDisplay != WIM_nenInvalidMsg)
                    {
                        WIM__vMenuFaultMemResetCallback(EV_DPOOL_Always_WIM_u8FaultMemEvReset_WIM_vDoHmiEvents);
                        boLastMessage = True;
                    }
                }
            }
            if (!boLastMessage)
            {
                /* Set changed state on DPOOL */
                WIM__mSetLowWord(u32FaultMemState, enMsgToDisplay);
                WIM__mSetHighWord(u32FaultMemState, u16MsgIndex);
                DPOOL_enSetPoolData(DPOOL_nDataWIM_u32FaultMemState, &u32FaultMemState);
            }
         }
      }
   }
}

/**
* Stop callback-function that is called if WIM-'Fault Memory' menu loses the display
*/
void WIM__vMenuFaultMemResetCallback(EVHD_tenReceiveEvent enEvent)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint32 u32FaultMemBorder = WIM__nFaultMemInit;      /* Temp storage for FaultMemBorder from DPOOL */
   uint32 u32FaultMemState  = WIM__nFaultMemInit;      /* Temp storage for FaultMemStater from DPOOL */
   uint16 u16NoMsgsFaultMem;                           /* for Number of Msgs in FaultMem */
   WIM_tenMsg enFirstMsgFaultMem;                      /* for First WarnID in FaultMem */
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if(enEvent == EV_DPOOL_Always_WIM_u8FaultMemEvReset_WIM_vDoHmiEvents)
   {
      /* Getting the Border from DPOOL */
      DPOOL_enGetPoolData(DPOOL_nDataWIM_u32FaultMemBorder, &u32FaultMemBorder);

      /* Getting Number of Msgs in FaultMem */
      u16NoMsgsFaultMem   = WIM__mGetHighWord(u32FaultMemBorder);
      /* Getting EnumValue of first Warning in FaultMem */
      enFirstMsgFaultMem  = (WIM_tenMsg)WIM__mGetLowWord(u32FaultMemBorder);

      /* Evaluate the new State*/
      if(/* Is there one Warning in FaultMem at least  */
         enFirstMsgFaultMem < WIM_nenNoOfMessages
         && u16NoMsgsFaultMem > WIM__nFaultMemNoWarnings)
      {
         /* Set Index to first Index */
         WIM__mSetHighWord(u32FaultMemState, WIM__nFaultMemFirstIndex);
         /* Set the first WarnID */
         WIM__mSetLowWord(u32FaultMemState, enFirstMsgFaultMem);
      }
      else
      {
         u32FaultMemState = WIM__nFaultMemInit;
      }

      /* Set the evaluated State on DPOOL*/
      DPOOL_enSetPoolData(DPOOL_nDataWIM_u32FaultMemState, &u32FaultMemState);

   }


}


/******************************************************************************
* LOCAL FUNCTION DEFINITIONS
*******************************************************************************/


/**
* The function looks for partner message according to the following rule:
* - is message stored in fault memory ? and
* not(
*    - has the found warning a partner message ? and
*    - is their fault signal memory flag set ? and
*    - is the WIM_Enum of the partner message smaller than that the found message ?
* )
* the function called of WIM__vFaultMemDisplayCallback() and WIM__boFaultMemKeyCallback()
*/
static bool WIM__boCheckFaultMemFlagAndPartnerMessage(WIM_tenMsg enMsg)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   WIM_tenMsg enPartner;          /* save variable, WIM Enum partner message */
   bool boReturnCode;              /* function return code                    */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (enMsg >= WIM__mGetNoOfMessages) 
   { 
     boReturnCode = False; 
   }
   else 
   {
     enPartner = WIM__enGetPartnerMsg(enMsg);
     boReturnCode =
      (
        WIM__mboGetFaultMemFlag(enMsg)
        &&
        !(
           enPartner != WIM_nenInvalidMsg
           &&
           WIM__mboGetFaultMemFlag(enPartner)
           &&
           enPartner < enMsg
        )
      );
   }
   return (boReturnCode);
}


static WIM_tenMsg WIM__enSearchHigherPrioMsg(WIM_tenMsg enMsgStart)
{
   if(enMsgStart != WIM_nenInvalidMsg)
   {
      /* search the next 'fault memory entry' backwards */
      for (--enMsgStart; enMsgStart != WIM_nenFirstMsg; enMsgStart--)
      {
         /* Fault memory flag: is message stored in fault memory? */
         /* and no more highly priore partner message ?           */
         if (WIM__boCheckFaultMemFlagAndPartnerMessage(enMsgStart))
         {
            return enMsgStart;
         }
      }
   }
   return WIM_nenInvalidMsg;
}

static WIM_tenMsg WIM__enSearchLowerPrioMsg(WIM_tenMsg enMsgStart)
{
   if(enMsgStart != WIM_nenInvalidMsg)
   {
      /* search the next 'fault memory entry' forward   */
      for (++enMsgStart; enMsgStart < WIM__mGetNoOfMessages; enMsgStart++)
      {
         /* Fault memory flag: is message stored in fault memory? */
         /* and no more highly priore partner message ?           */
         if (WIM__boCheckFaultMemFlagAndPartnerMessage(enMsgStart))
         {
            return enMsgStart;
         }
      }
   }
   return WIM_nenInvalidMsg;
}