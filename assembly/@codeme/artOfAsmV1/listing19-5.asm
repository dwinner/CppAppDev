; Listing 19-5
;
; Test cset to string conversion

            include    aoalib.inc
            include    cset.inc
            includelib aoalib.lib

            .const
ttlStr      byte    "Listing 19-5", 0

            .data

; String that will hold the result:

            staticStr  result, 300

; The empty set (should be the fastest for the
; naive population count function):

            staticCset emptySet

; Alphabetics set (52 upper and lower case characters):
            
            csetInit                    ;Initialize cset.
            unionRng <A-Z>
            unionRng <a-z>
            unionRng <0-9>
            emitCset    alphaNumerics   ;Creates actual cset.

; Alphanumerics: 62 characters (alpha plus 10 digits):
            
            csetInit
            unionRng <A-Z>
            unionRng <a-z>
            emitCset alphabetics
            
            
; Numerics: 10 characters (10 digits):
            
            csetInit
            unionRng <0-9>
            emitCset numerics
            
            
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
            
            lea     rsi, emptySet
            lea     rdi, result
            call    csetToString
            jc      strOvfl
            lea     rdx, result
            call    print
            byte    "Empty cset is '%s'", nl, 0
            
            lea     rsi, alphabetics
            lea     rdi, result
            call    csetToString
            jc      strOvfl
            lea     rdx, result
            call    print
            byte    "Alphabetics cset is '%s'", nl, 0
            
            lea     rsi, alphaNumerics
            lea     rdi, result
            call    csetToString
            jc      strOvfl
            lea     rdx, result
            call    print
            byte    "AlphaNumerics cset is '%s'", nl, 0
            
            lea     rsi, numerics
            lea     rdi, result
            call    csetToString
            jc      strOvfl
            lea     rdx, result
            call    print
            byte    "Numerics cset is '%s'", nl, 0
            jmp     allDone
            
strOvfl:    call    print
            byte    "String overflow occurred", nl, 0
                         
allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
