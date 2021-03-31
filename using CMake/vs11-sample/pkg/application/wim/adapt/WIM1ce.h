/***************************************************************************
*=====================      Copyright by Continental AG      ===============
****************************************************************************
* Titel        : WIM1ce.h
*
* Description  : export configuration of package WIM
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
* Archive: $Log: WIM1ce.h  $
* Archive: Initial revision for VS11 (Based on 213IC-EL E009.4rel)
*
* Archive: Revision 1.2 2015/06/17 18:44:26CEST Wenske-EXT, Martin (uidj8453) 
* Archive: DC MR 47461 : runtime of BasicApp_Prio2 too long
* Archive: Revision 1.1 2013/03/21 16:11:54CET uid37561 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/adapt/BR213IC_AC_EL_SOP/project.pj
* Archive: Revision 1.2 2012/11/21 11:52:33CET Immel Marc (uid37561) (uid37561) 
* Archive: Migration of WIM-AC from PVCS to MKS 
* Archive: - used release: DC.SW.PAC.WIM_205IC_AC_COMMON_VarW.V01.00.pre17
* Archive: Revision 1.1 2011/11/08 13:04:06CET uid37556 
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/wim/adapt/project.pj
* 
*    Rev 1.1   May 18 2012 16:55:58   SCHL_Dirk.Gottwalles
* DC MR 25587: WDM21151/34246/35637: SBW/WIM Acoustic corrections
* DC MR 25914: W205, E009/AC, HIL: Mapping of WIM sound types
* 
*    Rev 1.0   Nov 08 2011 14:39:06   SCHL_Dirk.Gottwalles
* Initial revision.
* 
*
****************************************************************************/
/*
* Check if information is already included
*/
#ifndef WIM1CE_H
#define WIM1CE_H

/***************************************************************************
* HEADER-FILES (Only those that are needed in this file)
****************************************************************************/
/* System-headerfiles */
#include "cdef.h"                     /* General definitions and types     */

/* Foreign headerfiles */
#include "EVHD_c1.h"                  /* Event handler                     */
#include "DLIB_c1.h"                  /* Diagnostic library                */

/* Own headerfiles */
#include "WIM_DataExt.h"

/******************************************************************************
* Definition of exported global data 
* Macros, Enumerations, Types,  Forward declarations
*******************************************************************************/

/******************************************************************************
* Compiler switches for configuration of the package
*******************************************************************************/
/**
* Description: Masks used to set the blink status in the DPOOL data for SAM/SOM.
*/


typedef enum
{
WIM_nStaticOn  = 0x01,
WIM_nFreq1Hz   = 0x02,   /*500ms/500ms*/
WIM_nFreq2Hz   = 0x04    /*200ms/300ms*/
} WIM_tenFrequency;

/**
* type definition for application provided callback functions 
* which inform about display/acoustic master change
* see definition of master change containers in CI-Header
* of package WIM
*/
#define WIM_nInvalidMsg WIM__nInvalidHilId

/**
* Enumeration of state transitions used by external clients
*/
typedef enum
{
   WIM_nActive,           /* message has been activated and waits for output */
   WIM_nInactive,         /* message has been deactivated                    */
   WIM_nManuQuitOk,       /* message has been confirmed with Ok key          */
   WIM_nManuQuitBack,     /* message has been confirmed with Back key        */
   WIM_nDisplayOn,        /* message is put into the display roll            */
   WIM_nDisplayOff,       /* message is removed from the display roll        */
   WIM_nDisplayAgain,     /* message becomes display master                  */
   WIM_nDisplayAway,      /* message is temporarily replaced by another msg. */
   WIM_nNoOfDisplayEvents /* ----------------------------------------------- */  
} WIM_tenDisplayEvent;

/**
* type definition for application provided callback functions 
* which inform about display/acoustic master change
* see definition of master change containers in CI-Header
* of package WIM
*/
typedef void (*WIM_tpvChangeCb)(uint32);

/**
* type definition for application provided callback functions 
* which inform about driver confirmation of a message
* see definition of containers in CI-Header of package WIM
*/
typedef void (*WIM_tpvManuQuitCb)(uint32, WIM_tenDisplayEvent);

/**
* type definition for application provided callback functions 
* which inform about driver confirmation of a message
* see definition of containers in CI-Header of package WIM
*/
typedef void (*WIM_tpvPreConfirmationCb)(uint32);

/**
* type definition for application provided callback functions 
* which are called if messages have been reset. The callback informs the
* application to re-check their warning messages
* see definition of containers in CI-Header of package WIM
*/
typedef void (*WIM_tpvCheckWarnCb)(void);

/**                                          
* Enumeration of external event functions    
*/                                           
typedef enum
{    
   WIM_nExtEventAPG,
   WIM_nExtEventLCT,
   WIM_nExtEventBSM,
   WIM_nNoOfExtEvtFunctions
} WIM_tenExtEvtFunction;

/*
* End of Check if information is already included
*/
#endif                                /*   ifndef WIM1CE_H                 */
/***************************************************************************
* EOF: WIM1ce.h
****************************************************************************/
