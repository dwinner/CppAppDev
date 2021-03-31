/* EasyCASE V6.5 01/17/2012 09:04:51 */
/* EasyCASE O
If=vertical
LevelNumbers=no
LineNumbers=no
Colors=16777215,0,12582912,12632256,0,0,0,16711680,8388736,0,33023,32768,0,0,0,0,0,32768,12632256,255,65280,255,255,16711935
ScreenFont=Courier New,Standard,100,4,-14,0,400,0,0,0,0,0,0,3,2,1,49,96,96
PrinterFont=Courier New,,80,4,-66,0,400,0,0,0,0,0,0,3,2,1,49,600,600
LastLevelId=27 */
/* EasyCASE ( 1
   SBWwCE.H */
/* EasyCASE ( 2
   FILE HEADER */
/***************************************************************************
*=====================      Copyright by Continental AG      ===============
****************************************************************************
* Title        : SBWwCE.h
*
* Description  : External configuration of SBW module
*
* Environment  : JCP2011
*
* Responsible  : Jan Cavojsky, IID TSR S2
*
* Guidelines   : SMK 4.8
*
* Template name: SWMODxCE.H, Revision 1.0
*
* CASE-Tool    : EasyCASE(C++), Version 6.5
*
* $Revision: 1.1 $
*
* Revision List: (Will be filled by PVCS)
* Archive: $Log: SBW1CE.H  $
* Archive: Revision 1.1 2012/11/16 15:24:32CET Lacko-EXT, Jan (uidu0305)
* Archive: Initial revision
* Archive: Member added to project /id/dag_PF3/sw/pkg/sbw/adapt/project.pj
* Archive: Revision 1.2 2012/11/16 15:24:31CET Lacko Jan (uidu0305) (uidu0305)
* Archive: Update header of file.
*
*    Rev 1.0   Oct 21 2011 13:17:56   Jan.Cavojsky-EXT
* Initial revision.
*
****************************************************************************/

/*
* Check if information is already included
*/
#ifndef SBWWCE_H
#define SBWWCE_H


/***************************************************************************
* HEADER-FILES (Only those that are needed in this file)
****************************************************************************/
/* System-headerfiles */
#include  "cdef.h"                      /* General definitions and types */

/* Foreign headerfiles */
/* EasyCASE ) */
/* EasyCASE ( 4
   EXPORT CONFIGURATION */
/***************************************************************************
* EXPORT CONFIGURATION CONSTANTS
*
* In this section define
* - constants and macros to configure your export interface. These constants
*   are public for other modules
****************************************************************************/
/* HIL Info access macros */
// Description : SBW_vGetSbwHILInfo value format
//  00b = Invisible Seat
//  01b = Not fastened Seat
//  10b = Fastened Seat
//  11b = Default// bit 0-1: left seat
// bit 2-3 : middle seat 
// bit 4-5: right seat
// bit 6-7 :  3rd row left seat
// bit 8-9 : 3rd row right seat 
// bit 22: rows 
/* Value bit masks  */
/* Bit mask for accessing values for second row of seats */
#define SBW_nHILInfo_Row2Mask     (0x03)
/* Bit mask for accessing values for third row of seats */
#define SBW_nHILInfo_Row3Mask     (0x03)
/* Bit mask for accessing values for seats setup */
#define SBW_nHILInfo_SeatRowsMask (0x01)
/* Starting bit positions in HIL Info */
/* Second row - left seat */
#define SBW__nShiftToSeatRow2LeftBitPos     (0)
/* Second row - middle seat */
#define SBW__nShiftToSeatRow2MiddleBitPos   (2)
/* Second row - right seat */
#define SBW__nShiftToSeatRow2RightBitPos    (4)
/* Third row - left seat */
#define SBW__nShiftToSeatRow3LeftBitPos     (6)
/* Third row - right seat */
#define SBW__nShiftToSeatRow3RightBitPos    (8)
/* Seats setup */
#define SBW_nHILInfo_SeatRowsBitPos     (22)

/* Value access macros */
#define SBW_nHILInfo_Value2Rows(u32HilInfo, u8ShiftPosition) \
   (uint8)(((u32HilInfo) >> (u8ShiftPosition)) & SBW_nHILInfo_Row2Mask)

#define SBW_nHILInfo_Value3Rows(u32HilInfo, u8ShiftPosition) \
   (uint8)(((u32HilInfo) >> (u8ShiftPosition)) & SBW_nHILInfo_Row3Mask)

/* Second row - left seat */
#define SBW_nHILInfo_Row2LeftValue(u32HilInfo)   \
    SBW_nHILInfo_Value2Rows(u32HilInfo, SBW__nShiftToSeatRow2LeftBitPos)
/* Second row - right seat */
#define SBW_nHILInfo_Row2RightValue(u32HilInfo) \
   SBW_nHILInfo_Value2Rows(u32HilInfo, SBW__nShiftToSeatRow2RightBitPos)
/* Second row - middle seat */
#define SBW_nHILInfo_Row2MiddleValue(u32HilInfo) \
   SBW_nHILInfo_Value2Rows(u32HilInfo, SBW__nShiftToSeatRow2MiddleBitPos)

/* Third row - left seat */
#define SBW_nHILInfo_Row3LeftValue(u32HilInfo)  \
    SBW_nHILInfo_Value3Rows(u32HilInfo, SBW__nShiftToSeatRow3LeftBitPos)
/* Third row - right seat */
#define SBW_nHILInfo_Row3RightValue(u32HilInfo) \
    SBW_nHILInfo_Value3Rows(u32HilInfo, SBW__nShiftToSeatRow3RightBitPos)

/* Seats setup */
#define SBW_nHILInfo_SeatRowsValue(u32HilInfo)   (uint8)(((u32HilInfo) >> SBW_nHILInfo_SeatRowsBitPos)   & SBW_nHILInfo_SeatRowsMask)
/* EasyCASE ) */
/* EasyCASE ) */
/* EasyCASE ( 6
   EOF */
/*
* End of Check if information is already included
*/
#endif                                  /* ifndef SBWWCE_H */


/***************************************************************************
* EOF: SBWwCE.H
****************************************************************************/
/* EasyCASE ) */
/* EasyCASE ) */
