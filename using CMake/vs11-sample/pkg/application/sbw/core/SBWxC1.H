/* EasyCASE V6.5 11.04.2011 17:14:35 */
/* EasyCASE O
If=vertical
LevelNumbers=no
LineNumbers=yes
Colors=8675151,9600103,12582912,8404992,0,0,0,16777215,8388736,13300724,33023,15457455,0,0,0,0,0,8454016,12632256,255,65280,255,255,16711935
ScreenFont=Courier New,Standard,100,4,-14,0,400,0,0,0,0,0,0,3,2,1,49,96,96
PrinterFont=Courier New,,80,4,-66,0,400,0,0,0,0,0,0,3,2,1,49,600,600
LastLevelId=94 */
/* EasyCASE ( 1
   SBW_C1.H */
/* EasyCASE ( 2
   FILE HEADER */
/***************************************************************************
*================= Copyright by SiemensVDO Automotive AG ===================
****************************************************************************
* Titel        : SBW - Seatbelt Warnung
*
* Description  : Die Aufgabe des SBW-Moduls ist eine baureihenÅbergreifende
*                Warnerfassung und Anmeldung der Gurtwarnung. Von SBW werden
*                nur die Gurtwarnung Akustik und die Gurtwarnung Lampe nach
*                Euro-NCAP bedient.
*
* Environment  : FJ-16 und FJ-32
*
* Responsible  : Joachim Pieper, Siemens VDO Automotive AG
*
* Guidelines   : SMK
*
* Template name: SWMODxC1.H, Revision 1.0
*
* CASE-Tool    : EasyCASE(C++), Version 6.32
*
* Revision List: (Will be filled by PVCS)
* Archive: $Log: SBWxC1.H  $
* Archive: Revision 1.2 2013/10/31 16:08:56CET Lacko-EXT, Jan (uidu0305)
* Archive: Update according to MR36550.
* Archive: Revision 1.1 2011/07/22 14:25:54CEST Lacko-EXT, Jan (uidu0305)
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/sbw/core/project.pj
*
*    Rev 1.4   Jul 22 2011 14:42:30   Jan.Cavojsky-EXT
* Update after MR 22334
*
*    Rev 1.3   Apr 14 2011 18:10:28   Nicolae.Gavrila
* DC MR 21685: BR222 SBW: counting 30sec only when Warning in display ƒLP2440
*
*    Rev 1.2   Mar 18 2011 16:15:50   Nicolae.Gavrila
* DC MRs 21660, 21666, 21724
*
*    Rev 1.1   Sep 17 2010 17:49:42   Nicolae.Gavrila
* DC MR 20908: E002/AC, Startup HIL
*
*    Rev 1.0   Aug 27 2010 16:37:14   Nicolae.Gavrila
* Initial revision.
*
*    Rev 1.10   Apr 08 2009 17:16:16   Nicolae.Gavrila
* DC MR 19729: W204EL: rear seatbelt warning follow up MR
*
*    Rev 1.9   Oct 10 2008 17:34:10   Nicolae.Gavrila
* DC MR 18453 Change of warning layout
*
*    Rev 1.8   Aug 22 2008 07:53:06   Radu.Teaha
* DC 18904, 18905, 18907
*
*    Rev 1.7   Apr 11 2007 10:46:28   Radu.Teaha
* DC MR 15791
*
*    Rev 1.6   Dec 06 2006 11:43:02   Radu.Teaha
* MR 15538
*
*    Rev 1.5   Nov 09 2006 12:41:40   Radu.Teaha
* DC MR 15335, 15381, 15382
*
*    Rev 1.4   Feb 07 2006 09:28:12   Radu.Teaha
* MRs 13724, 13729
*
*    Rev 1.3   Sep 15 2005 14:27:36   Radu.Teaha
* DC MRs 12246, 12247
*
*    Rev 1.2   Jul 11 2005 16:53:58   Daniel.Ciocea
* MR11757,MR1756
*
*    Rev 1.1   May 05 2005 08:51:14   Daniel.Ciocea
* MR11653-Seatbeltwarnig Rearseat
*
*    Rev 1.0   Feb 17 2005 14:22:18   Daniel.Ciocea
* Initial revision.
*
****************************************************************************/

/*
* Check if information are already included
*/
#ifndef SBW_C1_H
#define SBW_C1_H


/***************************************************************************
* HEADER-FILES (Only those that are needed in this file)
****************************************************************************/
/* System-headerfiles */
#include  <cdef.h>                      /* General definitions and types */
#include  "wim_ce.h"                    /* warn information manager      */

/* Foreign headerfiles */

/* Own headerfiles */
#include "sbw_ci.h"
/* EasyCASE ) */
/* EasyCASE ( 4
   EXPORT INTERFACE */
/***************************************************************************
* EXPORT INTERFACE FUNCTION PROTOTYPES
*
* In this section declare
* - all system global function prototypes of your module
****************************************************************************/
/* EasyCASE ( 30
   SBW_vInitActive */
/***************************************************************************
* Interface Description: Initalisierung in Uebergang -> Active.
*                        (nur bei ARMADA-Workaround erforderlich)
*
* Implementation       :
*
* Return Value         : void
*
* Author               : Joachim Pieper, Siemens VDO Automotive AG
*
****************************************************************************/

void SBW_vInitActive(void);
/* EasyCASE ) */
/* EasyCASE ( 23
   SBW_vInitActive15 */
/***************************************************************************
* Interface Description: Initalisierung in Uebergang Active -> Active15 und
*                                                    Active15 -> Active
*
* Implementation       :
*
* Return Value         : void
*
* Author               : Joachim Pieper, Siemens VDO Automotive AG
*
****************************************************************************/

void SBW_vInitActive15(void);

/* EasyCASE ( 30
SBW_vDeinitActive */
/***************************************************************************
* Interface Description:  Called when resource RES_Active is deinit.
*
* Implementation       : deregister the events used by SBW module
*
* Return Value         : void
*
* Author               : 

****************************************************************************/

void SBW_vDeinitActive(void);
/* EasyCASE ) */
/* EasyCASE ( 38
   SBW_vDeinitActive15 */
/***************************************************************************
* Interface Description: Initalisierung in Uebergang Active -> Active15 und
*                                                    Active15 -> Active
*
* Implementation       :
*
* Return Value         : void
*
* Author               : Joachim Pieper, Siemens VDO Automotive AG
*
****************************************************************************/

void SBW_vDeinitActive15(void);
/* EasyCASE ) */
/* EasyCASE ( 34
   SBW_v100Main */
/***************************************************************************
* Interface Description: zyklische Funktion bei Active
*
* Implementation       :
*
* Return Value         : void
*
* Author               : Joachim Pieper, Siemens VDO Automotive AG
*
****************************************************************************/

void SBW_v100Main(void);
/* EasyCASE ) */
/* EasyCASE ( 42
   SBW_v25Active */
/***************************************************************************
* Interface Description: zyklische Funktion bei Active
*
* Implementation       :
*
* Return Value         : void
*
* Author               : Joachim Pieper, Siemens VDO Automotive AG
*
****************************************************************************/

void SBW_v25Active(void);
/* EasyCASE ) */
/* EasyCASE ( 95
   SBW_vReCheckWarnings */
/***************************************************************************
* Interface Description: Called by WIM at KL15On
*
* Implementation       : Retriggers the warning
*
* Return Value         : void
*
* Author               : Jan Lacko
*
****************************************************************************/
void SBW_vReCheckWarnings(void);
/* EasyCASE ) */
/* EasyCASE ( 55
   SBW_enDiagStartSupressing */
/***************************************************************************
* Interface Description: Set sound to no warning if requested via Diagnosis
*
*
* Implementation       :
*
* Return Value         : void
*
* Author               : Teaha Radu, Siemens VDO Automotive
*
****************************************************************************/

DLIB_tenReturn SBW_enDiagStartSupressing(void);
/* EasyCASE ) */
/* EasyCASE ( 56
   SBW_enDiagStopSupressing */
/***************************************************************************
* Interface Description: will re-initialize sound conditions
*                               if requested via Diagnosis
*
* Implementation       :
*
* Return Value         : void
*
* Author               : Teaha Radu, Siemens VDO Automotive
*
****************************************************************************/

DLIB_tenReturn SBW_enDiagStopSupressing(void);
/* EasyCASE ) */
/* EasyCASE ( 83
   SBW_vManuQuitCallback */
/***************************************************************************
* Interface Description: The function is called by WIM when a manual quit
*                        action was detected
*
* Implementation       : Releases the warning request for rear seatbelts warnings
*
* Return Value         : void
*
* Author               : Daniel Ciocea
*
****************************************************************************/
void SBW_vManuQuitCallback(uint32 u32WarnNumber, WIM_tenDisplayEvent enEvent);
/* EasyCASE ) */
/* EasyCASE ( 90
   SBW_vGetSbwHILInfo */
/***************************************************************************
* Interface Description: Provides information for HIL aplication
*
* Implementation       :
*
* Return Value         : void
*
* Author               : Nicolae Gavrila
*
****************************************************************************/
void SBW_vGetSbwHILInfo(uint32 *pu32Value);
/* EasyCASE ) */
/* EasyCASE ( 94
   SBW_vDisplayChangeCallback */
/***************************************************************************
* Interface Description: WIM callback for display master warning
*
* Implementation       :
*
* Return Value         : void
*
* Author               : Nicolae Gavrila
*
****************************************************************************/
void SBW_vDisplayChangeCallback(uint32 u32HilId);
/* EasyCASE ) */
/* EasyCASE ( 94
SBW_vRearSeatbeltWrn2018 */
/***************************************************************************
* Interface Description: WIM callback for re-evaluate the rear seatbelt warning
*
* Implementation       :
*
* Return Value         : void
*
* Author               : Oana Constantinescu
*
****************************************************************************/
void SBW_vRearSeatbeltWrn2018(void);
/* EasyCASE ) */
/* EasyCASE ( 6
   EOF */
/*
* End of check if information are already included
*/
#endif                                  /* ifndef SBW_C1_H */


/***************************************************************************
* EOF: SBW_C1.H
****************************************************************************/
/* EasyCASE ) */
/* EasyCASE ) */
