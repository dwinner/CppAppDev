/******************************************************************************
*=====================    Copyright by Continental AG    ======================
*******************************************************************************
* Titel        : WIM__TimerHandler.c
*
* Description  : Timer services
*                Private class that manages several timers needed in
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
* Archive: $Log: WIM__TimerHandler.c  $
* Archive: Revision 1.1.3.2 2013/02/18 16:43:30CET Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3/project.pj
* Archive: Revision 1.7 2013/02/18 16:43:30CET Immel-EXT, Marc (uid37561) 
* Archive: DC MR 32156: BR222, E011/AC, WIM: Lowering/Mute signals are never set back -  WDM67946
* Archive: Revision 1.6 2013/01/12 16:43:05CET Immel Marc (uid37561) (uid37561) 
* Archive: DC MR 31032: BR205: Overtake HMI components for flashing (HMI synchronisation) from IC222
* Archive: DC MR 30978: BR205, E011/GC, WIM: Remove exception raising if HMI reports a canceled warning
* Archive: DC MR 30976: BR205, E011/GC, WIM: Warning disappears before display is off
* Archive: DC MR 25690: W205IC-GC TSA: Prevent popup warning from being displayed when FAS menu is active (ÄLP2802)
* Archive: Revision 1.5 2012/05/18 10:58:13CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: Member moved from WIM__TimerHandler.c in project /id/dag_PF3/sw/pkg/wim/core/project.pj[dag_PF3.sw.pkg.wim_COMMON_IC222GC_VarP] to WIM__TimerHandler.c in project /id/dag_PF3/sw/pkg/wim/core/coreGenPF3/project.pj[dag_PF3.sw.pkg.wim_COMMON_genPF3_VarX].
* Archive: Revision 1.4 2012/04/25 11:42:53CEST Gottwalles Dirk (uid37556) (uid37556) 
* Archive: DC MR 25131: W222, E007/GC, WIM: Implementation of exceptions
* Archive: DC MR 25823: BR222 E7.2: Implementation of L3 delivery (XML-Files)
* Archive: DC MR 21251: W222, E007/GC, WIM: ComplexFunction of Warning 0x2001A6 Kurvenlicht
* Archive: DC MR 25710: W222, E007/GC, WIM: Inactive handling messages show up after 600ms - WDM35020
* Archive: DC MR 25126: W222, E007/GC, WIM: Behaviour of sync acoustics - WDM35391, 35418, 35392, 35389, 35396, 35421
* Archive: Revision 1.3 2012/04/04 15:30:02CEST 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: DC MR 24870: W222, E007/GC, WIM: Implement changes from Review ORM2907
* Archive: DC MR 25007: W222, E007/GC, WIM: Displacement of handling messages - WDM20280
* Archive: DC MR 25041: Do not specify message propagation in message description files
* Archive: DC MR 25095: W222, E007/GC, WIM: Improvement of Timer accuracy for display role - WDM 25704
* Archive: DC MR 25034: Reduction of lag times in case of vehicle locked
* Archive: DC MR 25393: W222, E007/GC, WIM: No cancel of interval acoustic - WDM31269, ÄLP2895
* Archive: Revision 1.2 2010/06/11 13:39:58CEST 07_BH_FA Partnerroom-SSH-9 (uid37556) (uid37556) 
* Archive: DC MR 24746: BR222 E7.1: Implementation of L3 MDB, WDB for E7.1
* Archive: DC MR 24995: IC222 GC: HMI Synchronization: Clock generation/Basic Mechanisms
* Archive: DC MR 24327: W222, E007/GC, WIM: Implement changes from Review ORM3245, ORM3314
* 
*    Rev 1.2   Jan 13 2012 16:18:56   SCHL_Dirk.Gottwalles
* DC MR 24093: W222, E007/GC, WIM: Acoustic warning does not block display - WDM20499
* DC MR 23683: W222, E007/GC, WIM: Sync acoustic is cancelled by async acoustic WDM21143
* DC MR 24088: W222, E007/GC, WIM: Warning blocks display WDM22837, WDM23219
* DC MR 24089: W222,E007,AC, WIM: New configuration values Chauffeur_Avl and ShiftStyle_Variant
* DC MR 24343: W222, E007/AC, WIM: Patch for 0x2000BC and 0x2000C1 (Country coding), WDM23191
* 
*    Rev 1.1   Jun 11 2010 14:01:08   SCHL_Thomas.Godemann
* DC MR20480 AC, Startup MR for Modul WIM in E001
* DC MR20481 GC, Startup MR for Modul WIM in E001
* 
*    Rev 1.0   Jun 07 2010 13:20:10   SCHL_Thomas.Godemann
* Initial revision.
* 
* --------------------------------------------------------------------------
* Date      | Author | Reason     | Change
* --------------------------------------------------------------------------
* 10-06-03    LarGru   MR20480      Initial revision for W222
*                      MR20481      Initial revision for W222
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
#include "WIM__TimerHandler.h"

/******************************************************************************
* PACKAGE LOCAL DEFINITIONS
*******************************************************************************/

/** 
* indicator for invalid/unused correlation tag 
*/
#define WIM__nInvalidCorrTag  0xFFFF

/******************************************************************************
* FILE LOCAL DEFINITIONS
*******************************************************************************/

/** 
* Definition of internal timer status structure 
*/
typedef struct
{
   /** timer ticks (loop counts) 
   * @range   0..2^16-1 
   * @values  0 (off), > 0 remaining timer-ticks
   */
   uint16 u16Counter;

   /** correlation tag (e.g. Message enum) 
   * @range   type dependend, currently uint16 -> 0..2^16-1 
   * @values  range of type
   */
   WIM__txCorrTag xCorrTag;      
} WIM__tstTimerState;

/**
* RAM table with dynamic attributes of each timer 
*/
static WIM__tstTimerState WIM__astTimerState[WIM__nMaxTimers];


/******************************************************************************
* PACKAGE LOCAL FUNCTIONS - SYSTEM CALLS
*******************************************************************************/

/**
* Initialisation of all timer objects (counters) 
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vTimerInit(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   WIM__tenTimer enTimer; /* loop variable */
   
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* set all timers to zero == inactive */
   for (enTimer = WIM__nFirstTimer; enTimer < WIM__mGetNoOfTimers; enTimer++) 
   {
      WIM__astTimerState[enTimer].u16Counter = WIM__nTimerInactive;
      WIM__astTimerState[enTimer].xCorrTag = WIM__nInvalidCorrTag;
   }
}

/**
* Deinitialisation of all timer objects (counters) 
*   @return  void
*   @param   none
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
void WIM__vTimerDeinit(void)
{
   WIM__vTimerInit();
}

/**
* main routine, downcount all active timers, call registered function
* if timer elapses
*   @return  void
*   @param   none
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vTimerMain(void)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   WIM__tenTimer enTimer; /* loop variable */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* downcount timers if active */
   for (enTimer = WIM__nFirstTimer; enTimer < WIM__mGetNoOfTimers; enTimer++) 
   {
      if (/* timer running? */
          WIM__astTimerState[enTimer].u16Counter > WIM__nTimerElapsed)
      {
         /* decrement timer counter */ 
         (WIM__astTimerState[enTimer].u16Counter) --;
         if (/* counter elapsed? */
                (WIM__astTimerState[enTimer].u16Counter == WIM__nTimerElapsed) 
             /* and callback defined */
             && (WIM__mGetTimerConfig[enTimer].pvCallback != NULL))
         {
            /* call function with Timer-Id und correlation tag */
            (WIM__mGetTimerConfig[enTimer].pvCallback) \
                            (enTimer, WIM__astTimerState[enTimer].xCorrTag);
         }
      }
   }
}

/******************************************************************************
* PACKAGE LOCAL FUNCTIONS - SERVICES
*******************************************************************************/

/**
* service interface, start/restart a (preconfigured) timer
*   @return  void
*   @param   WIM__tenTimer enTimer : ID of timer to start
*   @param   int16         iCorrTag: correlation tag, return in callback function
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vStartTimer(WIM__tenTimer enTimer, WIM__txCorrTag xCorrTag)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* valid timer? */
   if (enTimer < WIM__mGetNoOfTimers)
   {
      /* calculate timer ticks (loop counts) */
      WIM__astTimerState[enTimer].u16Counter = WIM__mu16GetLoopCount(WIM__mGetTimerConfig[enTimer].u32TimerInterval);

      /* save timer related correlation tag */
      WIM__astTimerState[enTimer].xCorrTag = xCorrTag;

      /* add start value */
      WIM__astTimerState[enTimer].u16Counter += WIM__nTimerElapsed;
   }
}

/**
* service interface, start/restart a (preconfigured) timer
*   @return  void
*   @param   WIM__tenTimer enTimer : ID of timer to start
*   @param   WIM__txCorrTag xCorrTag: correlation tag, return in callback function
*   @param   uint32        u32Int  : timer interval in ms
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vStartTimerEx(WIM__tenTimer enTimer, WIM__txCorrTag xCorrTag, uint32 u32Int)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* valid timer? */
       enTimer < WIM__mGetNoOfTimers)
   {
      /* load timer ticks (loop counts) */
      WIM__astTimerState[enTimer].u16Counter = WIM__mu16GetLoopCount(u32Int);
      /* save timer related correlation tag */
      WIM__astTimerState[enTimer].xCorrTag = xCorrTag;
      /* add start value */
      WIM__astTimerState[enTimer].u16Counter += WIM__nTimerElapsed;
   }
}

/**
* service interface, cancel a timer; this will not cause the timer to call 
* the configured callback function
*   @return  void
*   @param   WIM__tenTimer enTimer: ID of timer to stop
*   @author  T.Godemann, Schleissheimer GmbH 
*/
void WIM__vCancelTimer(WIM__tenTimer enTimer)
{
   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* valid timer? */
       enTimer < WIM__mGetNoOfTimers)
   {
      WIM__astTimerState[enTimer].u16Counter = WIM__nTimerInactive;
      WIM__astTimerState[enTimer].xCorrTag = WIM__nInvalidCorrTag;
   }
}

/**
* service interface, get status of a timer
*   @return  WIM__tenTimerState: WIM__nRunning, WIM__nElapsed or WIM__nInactive
*   @param   WIM__tenTimer enTimer: ID of timer to start
*   @author  T.Godemann, Schleissheimer GmbH 
*/
WIM__tenTimerState WIM__enGetTimer(WIM__tenTimer enTimer)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   WIM__tenTimerState enState = WIM__nTimerInactive; /* start: timer inactive */

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   if (/* valid timer? */
       enTimer < WIM__mGetNoOfTimers)
   {
      /* return True if timer is still running */
      if (WIM__astTimerState[enTimer].u16Counter > WIM__nTimerElapsed)
         enState = WIM__nTimerRunning;
      else
         enState = (WIM__tenTimerState)(WIM__astTimerState[enTimer].u16Counter);
   }
   return enState;
}

/**
* 
*   @return  WIM__txCorrTag: stored tag with this timer
*   @param   WIM__tenTimer enTimer: ID of timer to start
*   @author  D.Gottwalles, Schleissheimer GmbH 
*/
WIM__txCorrTag WIM__txGetTimerCorrTag(WIM__tenTimer enTimer)
{
   /***************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ****************************************************************************/
   WIM__txCorrTag xCorrTag = 0;

   /***************************************************************************
   * FUNCTION CODE
   ****************************************************************************/
   /* valid timer? */
   if (enTimer < WIM__mGetNoOfTimers)
   {
      /* return True if timer is still running */
      xCorrTag = WIM__astTimerState[enTimer].xCorrTag;
   }
   return xCorrTag;
}
