/* EasyCASE V6.5 01/17/2012 09:12:56 */
/* EasyCASE O
If=vertical
LevelNumbers=no
LineNumbers=yes
Colors=8675151,9600103,12582912,8404992,0,0,0,16777215,8388736,13300724,33023,15457455,0,0,0,0,0,8454016,12632256,255,65280,255,255,16711935
ScreenFont=Courier New,Standard,100,4,-14,0,400,0,0,0,0,0,0,3,2,1,49,96,96
PrinterFont=Courier New,,80,4,-66,0,400,0,0,0,0,0,0,3,2,1,49,600,600
LastLevelId=142 */
/* EasyCASE ( 127
   SBWwC2.H */
/* EasyCASE ( 2
   FILE HEADER */
/***************************************************************************
*===================== Copyright by SiemensVDO Automotive AG ======================
****************************************************************************
* Titel        : sbwwc2.h
*
* Description  : Die Aufgabe des SBW-Moduls ist eine baureihenÅbergreifende
*                Warnerfassung und Anmeldung der Gurtwarnung. Von SBW werden
*                nur die Gurtwarnung Akustik und die Gurtwarnung Lampe nach
*                Euro-NCAP bedient.
*                In SBW_C2 werden Tuerstatus, Sitzbelegung und Gurtsignale
*                geholt und daraus der Status der Tueren und Gurte ermittelt
*
* Environment  : FJ-16 und FJ-32
*
* Responsible  : Joachim Pieper, Siemens VDO Automotive AG
*
* Guidelines   : SMK
*
* Template name: SWMODxC2.H, Revision 1.0
*
* CASE-Tool    : EasyCASE(C++), Version 6.32
*
* $Revision: 1.2 $
*
* Revision List: (Will be filled by PVCS)
* Archive: $Log: sbw1c2.h  $
* Archive: Revision 1.2 2014/03/14 07:04:12CET Olenici-EXT, Alexandru (uidw5408)
* Archive: Updated after MR38101 and MR38055.
* Archive: Revision 1.1 2012/11/16 15:27:30CET Lacko-EXT, Jan (uidu0305)
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/sbw/adapt/project.pj
* Archive: Revision 1.2 2012/11/16 15:27:30CET Lacko Jan (uidu0305) (uidu0305)
* Archive: Update header of file
*
*    Rev 1.3   Apr 14 2011 18:15:08   Nicolae.Gavrila
* DC MRs:
* 21685: BR222 SBW: counting 30sec only when Warning in display -LP2440
* 21684: BR222 SBW: new Condition instead of car_running -LP2439
*
*    Rev 1.2   Nov 19 2010 10:32:14   Nicolae.Gavrila
* DC MR 21117: Correction SBW
*
*    Rev 1.1   Sep 17 2010 17:51:44   Nicolae.Gavrila
* DC MR 20908: E002/AC, Startup HIL
*
*    Rev 1.0   Aug 27 2010 16:38:24   Nicolae.Gavrila
* Initial revision.
*
*    Rev 1.4   Dec 09 2008 17:29:56   Nicolae.Gavrila
* DC MR 19344: rear seatbelt warning follow up MR
*
*    Rev 1.3   Oct 10 2008 17:42:14   Nicolae.Gavrila
* DC MR 18453
*
*    Rev 1.2   Sep 10 2008 08:08:34   Nicolae.Gavrila
* DC MR 18905 update
*
*    Rev 1.1   Aug 22 2008 09:46:32   Radu.Teaha
* DC MR 18905
*
*    Rev 1.0   Mar 04 2008 14:13:40   Gaertner
* Initial revision.
*
*    Rev 1.2   Apr 11 2007 10:59:12   Radu.Teaha
* DC MR 15791
*
*    Rev 1.1   Apr 27 2006 12:52:04   Radu.Teaha
* MR 14145
*
*    Rev 1.0   Jan 16 2006 10:31:54   Toth.Zoltan
* Initial revision. Copied from revision 1.3 of file "Sbwmc2.h".
*
*
****************************************************************************/

/*
* Check if information are already included
*/
#ifndef SBW_C2_H
#define SBW_C2_H


/***************************************************************************
* HEADER-FILES (Only those that are needed in this file)
****************************************************************************/
/* System-headerfiles */
#include  <cdef.h>                      /* General definitions and types */

/* Foreign headerfiles */
/* Own headerfiles */
#include  "sbw_ci.h"                    /* Import interface and local cfg. */
/* EasyCASE ) */
/* EasyCASE ( 115
   MODULE GLOBAL INTERFACE */
/***************************************************************************
* MODULE GLOBAL DEFINITIONS AND DECLARATIONS
*
* In this section
* - define helpful macros for easy data access and for a comfortable function
*   use if necessary
* - define module global define-constants
* - declare module global interface ROM-constants
* - define module global type definitions
* - declare module global interface variables
****************************************************************************/
/* EasyCASE ( 116
   SBW__tunDoorOpen */
/* EasyCASE < */
typedef union {
    byte bAll;              /* irgendeine Tuer auf      */
    struct stDoor {
        byte biDriver : 1;     /* Fahrertuer auf           */
        byte biCoDriver : 1;   /* Beifahrertuer auf        */
    } stDoor;
} SBW__tunDoorOpen;
/* EasyCASE > */
/* EasyCASE ) */
/* Value of "no warning released" */
#define nSoundWarningDelay              (5)
/* EasyCASE - */
/***************************************************************************
* MODULE GLOBAL FUNCTION PROTOTYPES
*
* In this section declare
* - all module global function prototypes of your module
****************************************************************************/
/* EasyCASE ( 117
   SBW__stGetDoorState */
/***************************************************************************
* Interface Description: Liefert den Status der Fahrer und Beifahrertuer
*                        zurueck
*
* Implementation       :
*
* Return Value         : siehe tunDoorOpen
*
* Author               : Joachim Pieper, Siemens VDO Automotive AG
*
****************************************************************************/

SBW__tunDoorOpen SBW__stGetDoorState(void);
/* EasyCASE ) */
/* EasyCASE ( 118
   SBW__vGetBeltState */
/***************************************************************************
* Interface Description: Get the validity of the driver seatbelt
*                        status of driver and codriver seatbelt
*
* Implementation       : -
*
* Return Value         : -
*
* Author               : Teaha Radu-Mihai
*
****************************************************************************/

void SBW__vGetBeltState(SBW__tunBeltState *stBeltState, bool *boBeltStateDriverValid);
/* EasyCASE ) */
/* EasyCASE ( 119
   SBW__vRsbwInitActive15 */
/***************************************************************************
* Interface Description: Called from SBW__vRsbwInitActive15 (sbw_c1.c file)
*                        before entering the system 'Active15' state
*
* Implementation       : The function is responsible for module parameters
*                        initialisation
*
* Return Value         : void
*
* Author               : Daniel Ciocea
*
****************************************************************************/

void SBW__vRsbwInitActive15(void);
/* EasyCASE ) */
/* EasyCASE ( 120
   SBW__vRsbwDeinitActive15 */
/***************************************************************************
* Interface Description: Called from SBW__vDeinitActive15 (sbw_c1.c file)
*                        before leaving the system 'Active15' state
*
* Implementation       : The function is responsible for rear seatbelt
*                        warnings removal at KL15g -> off
*
* Return Value         : void
*
* Author               : Daniel Ciocea
*
****************************************************************************/

void SBW__vRsbwDeinitActive15(void);

/* EasyCASE ) */
/* EasyCASE ( 121
   SBW__vRearSeatbeltWrn2018 */
/***************************************************************************
* Interface Description: The function called from SBW__vCheckFrontSeatbelts to handle
*                        the rear seatbelts warnings
*
* Implementation       : Handles the register/release actions of the warnings
*                        using the appropiate CAN signals for seatbelts and seat
*                        presence. Implements also the timer used for warning
*                        release actions.
* Return Value         : void
*
* Author               : Daniel Ciocea
*
****************************************************************************/
void SBW__vRearSeatbeltWrn2018(bool BoShouldDecrement);
/* SBW__vRearSeatbeltWrnMat */
/***************************************************************************
* Interface Description: The function called to handle the rear seatbelts warnings Mat
*
* Implementation       : Handles the register/release actions of the warnings
*                        using the appropiate CAN signals for seatbelts and seat
*                        presence when rear seats are equipped with the presense sensors.
Implements also the timer used for warning release actions.
* Return Value         : void
*
* Author               :
*
****************************************************************************/
void SBW__vRearSeatbeltWrnMat(void);
/* EasyCASE
SBW__vResetRearSeatbeltWrn */
/***************************************************************************
* Interface Description: The function called from SBW_vReCheckWarnings to reset
*                        the warning for the rear seatbelts.
*
* Implementation       : Resets the SBW__stStatFlg.biFirstCarRun to zero.
*
*
* Return Value         : void
*
* Author               : Alexandru Olenici
*
****************************************************************************/
void SBW__vResetRearSeatbeltWrn(void);
/* EasyCASE ) */
/* EasyCASE ( 122
   SBW__vManuQuitWarnRelease */
/***************************************************************************
* Interface Description: The function is called from SBW_vManuQuit to release
*                        the rear seatbelt warnings requests on button press
*
* Implementation       : Release the warning using the ID given as parameter
*                        by WIM. SBW selects only the relevant warnings to quit
* Return Value         : void
*
* Author               : Daniel Ciocea
*
****************************************************************************/
void SBW__vManuQuitWarnRelease(uint32 u32WarnNumber);
/* EasyCASE ) */
/* EasyCASE ( 136
   SBW__u8GetRearSeatBeltStatus */
/***************************************************************************
* Interface Description: Returns the status of the rear seats seatbelts
*
* Implementation       :
*
* Return Value         : uint8
*
* Author               : Nicolae Gavrila
*
****************************************************************************/
uint16 SBW__u16GetRearSeatBeltStatus(void);
/* SBW__u8GetRearSeatBeltStatus */
/***************************************************************************
* Interface Description: Returns the status of the rear seats seatbelts mats
*
* Implementation       :
*
* Return Value         : uint8
*
* Author               :
*
****************************************************************************/
uint16 SBW__u16GetRearSeatBeltMatsStatus(void);

/* EasyCASE ) */
/* EasyCASE ( 138
   SBW__vGetSbwHILInfo */
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
void SBW__vGetSbwHILInfo(uint32 *pu32Value);

/* EasyCASE ) */
/* EasyCASE ( 142
  SBW__vDisplayChangeCallback  */
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
void SBW__vDisplayChangeCallback(uint32 u32HilId);

/***************************************************************************
* Interface Description: Handler for EVHD events
*
* Implementation       :
*
* Return Value         : void
*
* Author               :
*
****************************************************************************/
void SBW__vEventHandler(EVHD_tenReceiveEvent enEvent);

/**
 * @brief Handle KL15g state for turn on delay for Rear seat belt
 */
void SBW__vRearHandleKL15ReadyDelay();

/* EasyCASE ) */
/* EasyCASE ) */
/* EasyCASE ( 6
   EOF */
/*
* End of check if information are already included
*/
#endif                                  /* ifndef SBW_C2_H */


/***************************************************************************
* EOF: sbwwc2.h
****************************************************************************/
/* EasyCASE ) */
/* EasyCASE ) */
