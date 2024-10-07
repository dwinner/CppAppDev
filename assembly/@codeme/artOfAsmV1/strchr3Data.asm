; strchr3Data.asm
;
; Some data used by the strchr2 and strrchr2 functions

            include zstrings.inc
            
            .data
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
            
maskOut0s1  oword 00000000000000000000000000000000h ;Mask 0
            oword 00000000000000000000000000000001h ;Mask 1
            oword 00000000000000000000000000000101h ;Mask 2
            oword 00000000000000000000000000010101h ;Mask 3
            oword 00000000000000000000000001010101h ;Mask 4
            oword 00000000000000000000000101010101h ;Mask 5
            oword 00000000000000000000010101010101h ;Mask 6
            oword 00000000000000000001010101010101h ;Mask 7
            oword 00000000000000000101010101010101h ;Mask 8
            oword 00000000000000010101010101010101h ;Mask 9
            oword 00000000000001010101010101010101h ;Mask 10
            oword 00000000000101010101010101010101h ;Mask 11
            oword 00000000010101010101010101010101h ;Mask 12
            oword 00000001010101010101010101010101h ;Mask 13
            oword 00000101010101010101010101010101h ;Mask 14
            oword 00010101010101010101010101010101h ;Mask 15
            
            end
