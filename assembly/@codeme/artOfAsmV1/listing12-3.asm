
; Listing 12-3
;
; Demonstration of the blsi instruction.

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 12-3", 0

            include getTitle.inc
            include print.inc

; Here is the "asmMain" function.
        
            .code
            public  asmMain
asmMain     proc
            push    rbx
            push    rsi
            push    rdi
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage


; >>>> Non-common code for various listings

            mov     r8, 12340000h            
            blsi    edx, r8
            
            call    print
            byte    "Extracted bit: %x", nl, 0

; <<<< end of unique code.
                         
allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
