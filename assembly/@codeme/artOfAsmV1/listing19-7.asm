; Listing 19-7
;
; Test csetToPCset function

            include    aoalib.inc
            include    cset.inc
            includelib aoalib.lib

            .const
ttlStr      byte    "Listing 19-7", 0

            .data


; The empty set (should be the fastest for the
; naive population count function):

            staticCset emptySet


; This will fail: too many individual characters
            csetInit                    ;Initialize cset.
            unionStr  "ACEGIKMOQSUWYbdfhjlnprtvxz"
            emitPCset everyOther

; This will fill up the range string (8 characters, whose
; codes are 2 apart):

            csetInit                    ;Initialize cset.
            unionStr  "ACEGIKMO"
            emitPCset fillRange


; This will (barely) succeed, filling up both the anyStr
; and rangeStr fields (24 characters, whose ASCII codes
; are 2 apart):

            csetInit                    ;Initialize cset.
            unionStr  "ACEGIKMOQSUWYbdfhjlnprtv"
            emitPCset everyOtherShort

; This will fill the any string (16 characters, with
; each ASCII code being 2 apart):

            csetInit                    ;Initialize cset.
            unionStr  "ACEGIKMOQSUWYbdf"
            emitPCset fillAny
            
; A generic character set that has ranges and individual
; characters (will require both rangeStr and anyStr fields):

            csetInit
            unionRng  <A-Z>
            unionRng  <a-z>
            unionRng  <0-9>
            unionRng  <#-)>
            unionRng  <[-]>
            unionRng  <{-}>
            unionHex  80h, 81h, 82h, 83h
            unionHex  90h, 91h, 92h, 93h
            unionStr  ",._"
            unionHex  0a0h,0b0h, 0c0h, 0d0h, 0e0h, 0f0h
            emitPCset manyItems
            
            staticStr result, 256
            
            .code
            
;**********************************************************
;
; Here is the "asmMain" function.
        
            public  asmMain
asmMain     proc
            push    rbx
            push    rsi
            push    rdi
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage
            
            lea     rsi, everyOther
            lea     rdi, everyOther
            call    csetToPCset
            
eo_pcs      textequ <qword ptr everyOther.pcs.pstrs>
            mov     rdx, eo_pcs.anyStr
            mov     r8,  eo_pcs.anyStr[8]
            mov     r9,  eo_pcs.rangeStr
            mov     r10, eo_pcs.rangeStr[8]
            call    print
            byte    "everyOther:", nl
            byte    "anyStr:   %016I64x, %016I64x", nl
            byte    "rangeStr: %016I64x, %016I64x", nl, nl, 0
            
            
            lea     rsi, everyOtherShort
            lea     rdi, everyOtherShort
            call    csetToPCset
            
eos_pcs     textequ <qword ptr everyOtherShort.pcs.pstrs>
            mov     rdx, eos_pcs.anyStr
            mov     r8,  eos_pcs.anyStr[8]
            mov     r9,  eos_pcs.rangeStr
            mov     r10, eos_pcs.rangeStr[8]
            call    print
            byte    "everyOtherShort:", nl
            byte    "anyStr:   %016I64x, %016I64x", nl
            byte    "rangeStr: %016I64x, %016I64x", nl, nl, 0
            
            
            lea     rsi, fillRange
            lea     rdi, fillRange
            call    csetToPCset

fr_pcs      textequ <qword ptr fillRange.pcs.pstrs>           
            mov     rdx, fr_pcs.anyStr
            mov     r8,  fr_pcs.anyStr[8]
            mov     r9,  fr_pcs.rangeStr
            mov     r10, fr_pcs.rangeStr[8]
            call    print
            byte    "fillRange:", nl
            byte    "anyStr:   %016I64x, %016I64x", nl
            byte    "rangeStr: %016I64x, %016I64x", nl, nl, 0
            
            
            lea     rsi, fillAny
            lea     rdi, fillAny
            call    csetToPCset

fa_pcs      textequ <qword ptr fillAny.pcs.pstrs>            
            mov     rdx, fa_pcs.anyStr
            mov     r8,  fa_pcs.anyStr[8]
            mov     r9,  fa_pcs.rangeStr
            mov     r10, fa_pcs.rangeStr[8]
            call    print
            byte    "fillAny:", nl
            byte    "anyStr:   %016I64x, %016I64x", nl
            byte    "rangeStr: %016I64x, %016I64x", nl, nl, 0
            
            
            lea     rsi, manyItems
            lea     rdi, manyItems
            call    csetToPCset
            
mi_pcs      textequ <qword ptr manyItems.pcs.pstrs>
            mov     rdx, mi_pcs.anyStr
            mov     r8,  mi_pcs.anyStr[8]
            mov     r9,  mi_pcs.rangeStr
            mov     r10, mi_pcs.rangeStr[8]
            call    print
            byte    "manyItems:", nl
            byte    "anyStr:   %016I64x, %016I64x", nl
            byte    "rangeStr: %016I64x, %016I64x", nl, 0
            
                         
allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
