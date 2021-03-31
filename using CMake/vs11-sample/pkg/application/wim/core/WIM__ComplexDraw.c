/******************************************************************************
*=====================    Copyright by Continental AG    ======================
*******************************************************************************
* Titel        : WIM__ComplexDraw.c
*
* Description  : Contains message configuration data:
*                - message attributes for view/state handling
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
* Archive: $Log: WIM__ComplexDraw.c  $
* Archive: Initial revision for VS11 (Based on 213IC-EL E009.4rel)
*
* Archive: Revision 1.4 2014/03/21 12:59:29CET Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 39839 : BR205 E013: ALP3289 new warning 0x200542(Hybrid) 
* Archive: DC MR 40021 : WIM: Sound of FCW warning is not retriggered after reset
* Archive: DC MR 39892 : BR213EL, E007, Implementation of L2
* Archive: Revision 1.3 2013/06/04 12:36:57CEST Harms-EXT, Daniel (uidw1026) 
* Archive: Part of DC MR 33454: IC213EL: Flickering effect when activating distronic warning (SV_13_3062)
* Archive: Revision 1.2 2013/05/17 16:07:47CEST Immel-EXT, Marc (uid37561) 
* Archive: DC MR 33413: BR213EL/GC, E004, WIM: Takeover of the latest changes from BR205
* Archive: Revision 1.1 2013/01/12 16:48:08CET Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/adapt/project.pj
* Archive: Revision 1.3 2013/01/12 16:48:08CET Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 31032: BR205: Overtake HMI components for flashing (HMI synchronisation) from IC222
* Archive: DC MR 30978: BR205, E011/GC, WIM: Remove exception raising if HMI reports a canceled warning
* Archive: DC MR 30976: BR205, E011/GC, WIM: Warning disappears before display is off
* Archive: DC MR 25690: W205IC-GC TSA: Prevent popup warning from being displayed when FAS menu is active (�LP2802)
* Archive: Revision 1.2 2012/07/27 13:01:45CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 26921: W205 (copy W222) GC: Integration of SimEnv Simulation in MKS Script 4.0 environment
* Archive: DC MR 27182: W205, E009/GC, WIM: Acoustic stop behavior - WDM43362, WDM43364
* Archive: DC MR 27540: BR222/E7.4/GC: WIM: Update HIL feedback for sound and soundrequests
* Archive: Revision 1.1 2012/05/18 15:47:51CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/adapt/project.pj
* Archive: Revision 1.1 2012/05/02 10:15:26CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/project.pj
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

/******************************************************************************
* GLOBAL DEFINITIONS
*******************************************************************************/
/******************************************************************************
* FILE LOCAL DEFINITIONS
*******************************************************************************/
/**
* Description: Masks used to set the blink status in the DPOOL data for SAM/SOM.
*/
#define WIM__nMaskIconFrequencies 0x07

typedef enum
{
   WIM__enDrawStart,    /* Drawing will start                 */
   WIM__enTimerEnd,     /* Special function timer has elapsed */
   WIM__enDrawEnd,
   WIM__enInvalidEvent
} WIM__enCplxDrawEvent;

/******************************************************************************
* FILE LOCAL FUNCTION PROTOTYPES
*******************************************************************************/
static void WIM__vSetFlashingElements(WIM_tenMsg enMsg, WIM__enCplxDrawEvent enEvent, WIM_tenFrequency enFrequency);
static void WIM__vResetFrequencies(WIM_tenMsg enMsg, WIM__enCplxDrawEvent enEvent);
/******************************************************************************
* FUNCTION DEFINITIONS
*******************************************************************************/
/**
* The function initializes the acoustic class
*   @return  void
*   @param   enMsg: Message that is requested next
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
void WIM__vHandleComplexDraw(WIM_tenMsg enMsg)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   switch(enMsg)
   {
#if (HMI_MODEL == MODEL_PLCD)
   case WIM_nen0x20026C:
   case WIM_nen0x2004ED:
   case WIM_nen0x20F394:
      {
          WIM__vSetFlashingElements(enMsg, WIM__enDrawStart, WIM_nFreq1Hz);
      } break;
   case WIM_nen0x201004:
   case WIM_nen0x201006:
      {
          WIM__vSetFlashingElements(enMsg, WIM__enDrawStart, WIM_nFreq2Hz);
      } break;
#endif
   case WIM_nen0x200666:
   case WIM_nen0x20072B:
      {
          WIM__vSetFlashingElements(enMsg, WIM__enDrawStart, WIM_nFreq1Hz);
      } break;
   default:
      /* No handling for special message */
      WIM__vResetFrequencies(enMsg, WIM__enDrawEnd);
      break;
   }
}

static void WIM__vSetFlashingElements(WIM_tenMsg enMsg, WIM__enCplxDrawEvent enEvent, WIM_tenFrequency enFrequency)
{
    /***************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    ****************************************************************************/
    uint8 u8BlinkStatus;     /* current DPOOL blink status */
    uint8 u8NewBlinkStatus;  /* new status for blinking */
    /***************************************************************************
    * FUNCTION CODE
    ****************************************************************************/
    /* read current blink status from DPOOL */
    DPOOL_enGetPoolData(DPOOL_nDataWIM_au8WarnControl, &u8BlinkStatus);
    u8NewBlinkStatus = u8BlinkStatus;
    if (enEvent == WIM__enDrawStart)
    {
        u8NewBlinkStatus &= (~WIM__nMaskIconFrequencies);
        u8NewBlinkStatus |= (uint8)enFrequency;
    }
    /* evaluate if blink status has changed and write to DPOOL if required */
    if (u8BlinkStatus != u8NewBlinkStatus)
    {
        /* write new blink status */
        DPOOL_enSetPoolData(DPOOL_nDataWIM_au8WarnControl, &u8NewBlinkStatus);
    }
}
/**
* The function resets the blinking frequency for the complex drawings
*   @return  void
*   @param   enMsg: Message that is requested next
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
static void WIM__vResetFrequencies(WIM_tenMsg enMsg, WIM__enCplxDrawEvent enEvent)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   uint8 u8BlinkStatus;          /* current DPOOL blink status */
   uint8 u8NewBlinkStatus;       /* new status for blinking */
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* read current blink status from DPOOL */
   DPOOL_enGetPoolData(DPOOL_nDataWIM_au8WarnControl, &u8BlinkStatus);
   u8NewBlinkStatus = u8BlinkStatus;

   if (enEvent == WIM__enDrawStart)
   {
       /* Set the frequency to static on
       */
       u8NewBlinkStatus &= (~WIM__nMaskIconFrequencies);
       u8NewBlinkStatus |= WIM_nStaticOn;
   }
   else
   {
       /* switch off */
       u8NewBlinkStatus &= (~WIM__nMaskIconFrequencies);
   }

   /* evaluate if blink status has changed and write to DPOOL if required */
   if(u8BlinkStatus != u8NewBlinkStatus)
   {
      /* write new blink status */
      DPOOL_enSetPoolData(DPOOL_nDataWIM_au8WarnControl, &u8NewBlinkStatus);
   }
}
