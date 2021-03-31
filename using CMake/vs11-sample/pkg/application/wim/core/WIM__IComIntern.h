#ifndef WIM__ICOMINTERN_H
#define WIM__ICOMINTERN_H
/***************************************************************************
*=====================      Copyright by Continental AG      ===============
****************************************************************************
* Titel        : WIM__IComIntern.h
*
* Description  : This Header contains all definitions which are needed
*                on both Controllers for the WIM ICom communication.
*
* Environment  : OSEK, JCP
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
* Archive: $Log: WIM__IComIntern.h  $
* Archive: Revision 1.5 2015/06/17 18:47:50CEST Wenske-EXT, Martin (uidj8453) 
* Archive: DC MR 47461 : runtime of BasicApp_Prio2 too long
* Archive: Revision 1.4 2015/06/17 17:21:08CEST Henke, Thomas (uidt4246) 
* Archive: Member renamed from WIM__ICom_213EL.h to WIM__ICom_213.h in project /id/dag_PF3/sw/pkg/wim/~dag_PF3.sw.pkg.wim_COMMON_IC213AC_Var1/core/coreIC213/project.pj.
* Archive: Revision 1.3 2015/06/17 16:51:11CEST Wenske-EXT, Martin (uidj8453) 
* Archive: Member renamed from WIM__ICom_213EL.h to WIM__ICom_213.h in project /id/dag_PF3/sw/pkg/wim/~dag_PF3.sw.pkg.wim_COMMON_IC213AC_Var1/core/coreIC213EL/project.pj.
* Archive: Revision 1.2 2014/07/29 18:35:16CEST Wagner-EXT, Alexander (uidw3785) 
* Archive: DC MR 41682 : WIM/AC: Prevent sporadic flicker of GC controlled complex warnings after Kl15ACC
* Archive: Revision 1.1 2012/05/18 14:55:38CEST Immel-EXT, Marc (uid37561) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreIC213EL/project.pj
* Archive: Revision 1.3 2012/05/18 14:55:38CEST uid37556 
* Archive: DC MR 26142: BR205 E009: Implement E009 L2 delivery into the software frame (XML files and Styleguide) (WDM38885)
* 
*    Rev 1.1   May 18 2012 16:55:32   SCHL_Dirk.Gottwalles
* DC MR 25587: WDM21151/34246/35637: SBW/WIM Acoustic corrections
* DC MR 25914: W205, E009/AC, HIL: Mapping of WIM sound types
* Archive: Revision 1.1 2011/11/08 12:59:36CET Gottwalles Dirk (uid37556) (uid37556) 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/core/coreIC205/project.pj
* 
*    Rev 1.0   Nov 08 2011 14:32:26   SCHL_Dirk.Gottwalles
* Initial revision.
* 
*
****************************************************************************/

/****************************************************************************
** Header Files (Only those that are needed in this file)
****************************************************************************/

/* System Header Files */
#include "cdef.h"

/* Foreign headerfiles */

/* Own headerfiles */


/***************************************************************************
* Definition of exported global data used by Class
* Macros, Enumerations, Types,  Forward declarations
***************************************************************************/

/**
 * Description: All possible events to identify Data on WIM communication between
 *              WIM AC and WIM GC.
 *              This Enum must not exceed one Byte, because of the restrictions in 
 *              ICom communication!!!
*/
enum WIM__enIComIdentifier 
{
   /********************************/
   /* AC -> GC communication       */
   /********************************/
   /**
   * message has to be handled, sent by call of WIM__vOnEvent on AC.
   */
   WIM__nOnEventAcToGc,   
   /**
   * Finished RestoreWarnings on Ac. When Gc receive this, the next queued WIM__nOnEventAcToGc
   * has to be processed. 
   */
   WIM__nRestoreWarningsBeginReCheckAcToGc,
   /**
   * Finished complex warnings check on GC side
   */
   WIM__nRestoreWarningsCheckComplexDone,
   /**
   * Finished the first warnings re-check after RestoreWarnings on Ac. 
   * When Gc receive this, the Scheduler has to be restarted and triggered. 
   */
   WIM__nRestoreWarningsDoneReCheckAcToGc,  
   /**
   * Finished ResetWarnings on Ac. Is Feedback for Gc and part of HandShake mechanism.
   * all further queued WIM__nOnEventAcToGc has to be processed.
   */
   WIM__nResetWarningsFinishedAcToGc,

   /********************************/
   /* GC -> AC communication       */
   /********************************/
   /**
   * Sent by call of ManuQuitContainer on GC. Part of the HIL-ID is delivered in Data.
   */
   WIM__nContainerManuQuitGcToAc,
   /**
   * Sent by call of PreConfirmationContainer on GC. Part of the HIL-ID is delivered in Data.
   */
   WIM__nContainerPreConfirmationGcToAc,
   /**
   * Sent by call of DisplayChangeContainer on GC. Part of the HIL-ID is delivered in Data.
   */
   WIM__nContainerDspChangeGcToAc,
   /**
   * Sent by call of NotifyHandlerContainer on GC. Part of the HIL-ID and the Notification Event
   * are in the Data
   */
   WIM__nNotifyHandlerGcToAc,
   /**
   * Sent by call of SetFaultMemFlag (Stoermeldungsspeicher) on GC, to update the redundant copy on AC.
   * The Msg-Enum is Part of the Data.
   */
   WIM__nSetFaultMemFlagGcToAc,   
   /**
   * Sent by call of HandleIntCondition on GC. HIL-ID and WIM__tenEventIntern are in the Data.
   */
   WIM__nHandleIntConditionGcToAc,   
   /**
   * Sent by call of HandleExtCondition on GC. Function, Index and WIM__tenEventIntern are in the Data.
   */
   WIM__nHandleExtConditionGcToAc,   
   /**
   * Sent by call of WIM__vSetMuteRequest on GC. Boolean call param is part of the Data.
   */
   WIM__nSetMuteRqGcToAc,   
   /**
   * Sent by call of WIM__vSetVolDecRequest on GC. Boolean call param is part of the Data. 
   */
   WIM__nSetVolDecRqGcToAc,   
   /**
   * Start RestoreWarnings HandShake mechanism 
   */
   WIM__nStartRestoreWarningsGcToAc,   
   /**
   * Start ResetWarnings HandShake mechanism 
   */
   WIM__nStartResetWarningsGcToAc,   
   /**
   * Total number of identifiers  
   */
   WIM__nNoOfIdentifiers
};
typedef enum WIM__enIComIdentifier WIM__tenIComIdentifier;

/************************************
* MACROS FOR USAGE IN ICOM
************************************/
#define WIM__mPackIComIdent(Ident)      ((uint32)((Ident) << 24))
#define WIM__mPackDispEvent(enDispEvt)  (((uint32)(0xFF & (enDispEvt))) << 16)
#define WIM__mPackHilIdShort(u32Data)   (0x0000FFFF & ((u32Data) >> 8))
#define WIM__mPackMsgEnum(enMsgEnum)    (( 0x0000FFFF & (uint32)(enMsgEnum)))
#define WIM__mPackByte3(Byte)           ( ((uint32)(Byte)) << 16 )
#define WIM__mPackByte2(Byte)           ( ((uint32)(Byte)) << 8 )
#define WIM__mPackByte1(Byte)             ((uint32)(Byte))

#define WIM__mExtractIComIdent(u32Data) ((WIM__tenIComIdentifier)((u32Data) >> 24))
#define WIM__mExtractDispEvent(u32Data) (((u32Data) >> 16) & 0xFF)
#define WIM__mExtractHilId(u32Data)     (((u32Data) & 0x0000FFFF) > 0)  ?                /* Is deliverd HilId valid      */ \
                                        ((((u32Data) & 0x0000FFFF) << 8) | 0x20000000) : /* Yes, the build a valid HilId */ \
                                        WIM__nInvalidHilId                             /* No, the give invalid HilId   */
#define WIM__mExtractMsgEnum(u32Data)   ((WIM_tenMsg)((u32Data) & 0x0000FFFF))
#define WIM__mExtractByte3(u32Data)     (uint8)(((u32Data) & 0x00FF0000) >> 16)
#define WIM__mExtractByte2(u32Data)     (uint8)(((u32Data) & 0x0000FF00) >> 8 )
#define WIM__mExtractByte1(u32Data)     (uint8) ((u32Data) & 0x000000FF)

#endif /* WIM__ICOMINTERN_H*/
