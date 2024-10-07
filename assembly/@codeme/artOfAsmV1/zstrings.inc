
; zstrings.inc
;
;  Header file for the zero-terminated
; string functions in Chapter 17.

                option  casemap:none
                ifndef  zstrings_inc
zstrings_inc    =       0

                include aoalib.inc


; Constant definitions:

nl              =       10

; Useful pcmpXstrY IMM8 equates:

EqualEach       =       0001000b
EqualAny        =       0000000b
EqualOrder      =       0001100b
MSBIndex        =       1000000b
NegPolarity     =       0010000b
ByteMask        =       1000000b
scFlags         =       EqualEach + NegPolarity
ss1Flags        =       EqualOrder + NegPolarity + ByteMask
spnFlags        =       EqualAny+ByteMask


; SSE4.2 feature flags (in ECX):

SSE42           =       00180000h       ;Bits 19 & 20
AVXSupport      =       10000000h       ;Bit 28

; CPUID bits (EAX=7, EBX register)

AVX2Support     =      20h             ;Bit 5 = AVX


;**********************************************************
;
; Common Macros:
;
;
; alignRSI-
;
; Macro used by several strlen procedures
; to align RSI on a particular byte
; boundary.

alignRSI        macro       mask
                cmp         byte ptr [rsi], 0
                je          SetRSI
                inc         rsi
                test        rsi, mask
                jz          RSIisAligned
                endm



;**********************************************************
;
; Function declarations:
;
; Zero-terminated string length functions:

                externdef   strlen1:proc    ;naive
                externdef   strlen2:proc    ;scasb
                externdef   strlen3:proc    ;32-bit
                externdef   strlen4:proc    ;64-bit
                externdef   strlen5:proc    ;GLIBC
                externdef   strlen6:proc    ;pcmpistri
                externdef   strlen7:proc    ;SSE
                externdef   strlen8:proc    ;AVX
                
; memset functions

                externdef   memset1:proc    ;naive
                externdef   memset2:proc    ;stosb
                externdef   memset3:proc    ;SSE
                externdef   memset4:proc    ;AVX
                
; strcpy functions

                externdef   copy16:proc     ;support code
                externdef   strcpy1:proc    ;naive
                externdef   strcpy2:proc    ;pcmpistr
                externdef   strcpy3:proc    ;SSE
                

; strcmp functions

                externdef   strcmp1:proc    ;naive
                externdef   strcmp2:proc    ;pcmpistr
                externdef   strcmp3:proc    ;SSE


; strchr/strrchr functions:

                externdef   sevenFs:qword   ;Used by strchr2
                externdef   eighties:qword  ; and strrchr2
                externdef   ones:qword

                
                externdef   maskOut0s:oword  ;Used by strchr3
                externdef   maskOut0s1:oword ; and strspn
                
                externdef   strchr1:proc    ;naive
                externdef   strrchr1:proc   ;naive
                externdef   strchr2:proc    ;64-bit
                externdef   strrchr2:proc   ;64-bit
                externdef   strchr3:proc    ;pcmpistri
                externdef   strrchr3:proc   ;pcmpistri
                externdef   strchr4:proc    ;SSE
                externdef   strrchr4:proc   ;SSE


; strstr/strrstr functions:

                externdef   strstr1:proc    ;naive
                externdef   strrstr1:proc   ;naive
                externdef   strstr2:proc    ;cmpsb
                externdef   strstr3:proc    ;pcmpistri
                externdef   strrstr3:proc   ;pcmpistri
                externdef   strstr4:proc    ;SSE

; strspn/strcspn functions

                externdef   matchSet:proc   ;support
                externdef   noMatchSet:proc ;support
                externdef   get16AtRDI:proc ;support
                externdef   strspnPS:proc   ;Powerset
                externdef   strcspnPS:proc  ;Powerset
                externdef   strspn1:proc    ;naive
                externdef   strcspn1:proc   ;naive
                externdef   strspn3:proc    ;pcmpistr
                externdef   strcspn3:proc   ;pcmpistr
                externdef   strspn4:proc    ;SSE
                externdef   strcspn4:proc   ;SSE
                        
                

; C standard library functions:
                
                externdef   strlen:proc
                externdef   strcpy:proc
                externdef   strcmp:proc
                externdef   strchr:proc
                externdef   strrchr:proc
                externdef   strstr:proc
                externdef   strspn:proc
                externdef   strcspn:proc
                externdef   time:proc
                
                
                endif       ;zstrings_inc


