; maskOut0s.asm
;
;  SSE version of the strstr function that will
; run on any x86-64 CPU.
;
; RSI-      Points at haystack (string to search through)
; RDI-      Points at needle (string to search for)
;
; Returns:
;
; RAX-      Position of substring, or NULL if not present

            include zstrings.inc

            .const
            
; Table used to mask bytes in an XMM register:

            align 16
maskOut0s   oword 00000000000000000000000000000000h ;Mask 0
            oword 000000000000000000000000000000ffh ;Mask 1
            oword 0000000000000000000000000000ffffh ;Mask 2
            oword 00000000000000000000000000ffffffh ;Mask 3
            oword 000000000000000000000000ffffffffh ;Mask 4
            oword 0000000000000000000000ffffffffffh ;Mask 5
            oword 00000000000000000000ffffffffffffh ;Mask 6
            oword 000000000000000000ffffffffffffffh ;Mask 7
            oword 0000000000000000ffffffffffffffffh ;Mask 8
            oword 00000000000000ffffffffffffffffffh ;Mask 9
            oword 000000000000ffffffffffffffffffffh ;Mask 10
            oword 0000000000ffffffffffffffffffffffh ;Mask 11
            oword 00000000ffffffffffffffffffffffffh ;Mask 12
            oword 000000ffffffffffffffffffffffffffh ;Mask 13
            oword 0000ffffffffffffffffffffffffffffh ;Mask 14
            oword 00ffffffffffffffffffffffffffffffh ;Mask 15
            end

