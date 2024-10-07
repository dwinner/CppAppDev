; caseData.asm
;
; Contains data used by case conversions
; and case insensitive comparisons.
;
; RDI-      Pointer to string.

            option  casemap:none
            include string.inc

            .code
            align   16
lowerMask   oword   20202020202020202020202020202020h
upperMask   oword   0dfdfdfdfdfdfdfdfdfdfdfdfdfdfdfdfh

; The following owords containing 16 copies of 'a'-1 and
; 'z'+1 so we can easily do >= 'a' and <= 'z' comparisons.

UCa         oword   40404040404040404040404040404040h
UCz         oword   5b5b5b5b5b5b5b5b5b5b5b5b5b5b5b5bh


; The following owords containing 16 copies of 'a'-1 and
; 'z'+1 so we can easily do >= 'a' and <= 'z' comparisons.

lcA         oword   60606060606060606060606060606060h
lcZ         oword   7b7b7b7b7b7b7b7b7b7b7b7b7b7b7b7bh

            end
