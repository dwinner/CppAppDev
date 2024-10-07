; listing16-4.inc
;
; Header file entries extracted from MASM32 header
; files (placed here rather than including the 
; ful MASM32 headers to avoid namespace pollution
; and speed up assemblies).

STD_INPUT_HANDLE                     equ -10
STD_OUTPUT_HANDLE                    equ -11
STD_ERROR_HANDLE                     equ -12
CREATE_NEW                           equ 1
CREATE_ALWAYS                        equ 2
OPEN_EXISTING                        equ 3
OPEN_ALWAYS                          equ 4
FILE_ATTRIBUTE_READONLY              equ 1h
FILE_ATTRIBUTE_HIDDEN                equ 2h
FILE_ATTRIBUTE_SYSTEM                equ 4h
FILE_ATTRIBUTE_DIRECTORY             equ 10h
FILE_ATTRIBUTE_ARCHIVE               equ 20h
FILE_ATTRIBUTE_NORMAL                equ 80h
FILE_ATTRIBUTE_TEMPORARY             equ 100h
FILE_ATTRIBUTE_COMPRESSED            equ 800h
FILE_SHARE_READ                      equ 1h
FILE_SHARE_WRITE                     equ 2h
GENERIC_READ                         equ 80000000h
GENERIC_WRITE                        equ 40000000h
GENERIC_EXECUTE                      equ 20000000h
GENERIC_ALL                          equ 10000000h
INVALID_HANDLE_VALUE                 equ -1

PPROC           TYPEDEF PTR PROC        ; for include file prototypes

externdef __imp_GetStdHandle:PPROC
externdef __imp_WriteFile:PPROC
externdef __imp_ReadFile:PPROC
externdef __imp_CreateFileA:PPROC
externdef __imp_CloseHandle:PPROC
externdef __imp_GetLastError:PPROC
