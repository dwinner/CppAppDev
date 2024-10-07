
; Listing 12-2
;
; Demonstrate extracting bit strings from a register.

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 12-2", 0

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

            mov     rax, 123456788abcdefh
            mov     bl, 4
            mov     bh, 16
            
            bextr   rdx, rax, rbx
            
            call    print
            byte    "Extracted bits: %x", nl, 0

; <<<< end of unique code.
                         
allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
