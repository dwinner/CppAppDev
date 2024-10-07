; aoalib.inc
;
;   Header file containing external function
; definitions, constants, and other items used
; by code in "The Art of 64-bit Assembly Language"

        	option  	casemap:none

            ifndef      aoalib_inc
aoalib_inc  equ         0


; Constant definitions:
;
; nl: newline constant
; tab: tab constant

bs	=	08
tab	=	09
nl          =       10
lf	=	10
cr	=	13

; SSE4.2 feature flags (in ECX):

SSE42       =       00180000h       ;Bits 19 & 20
AVXSupport  =       10000000h       ;Bit 28

; CPUID bits (EAX=7, EBX register)

AVX2Support  =      20h             ;Bit 5 = AVX


;**********************************************************
;
; external data declarations:
    
            externdef   ttlStr:byte



;**********************************************************
;
; external function declarations:

            externdef   print:qword
            externdef   getTitle:proc

; Definition of C/C++ printf function that
; the print function will call (and some
; AoA sample programs call this directly,
; as well).

            externdef   printf:proc
            
            
            endif       ;aoalib_inc