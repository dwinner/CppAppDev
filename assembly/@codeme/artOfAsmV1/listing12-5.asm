
; Listing 12-5
;
; Demonstration of the blsr instruction.

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 12-5", 0

            include getTitle.inc
            include print.inc

            
            .code
            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbx
            push    rsi
            push    rdi
            push    rbp
            mov     rbp, rsp
            sub     rsp, 64         ;Shadow storage
            and     rsp, -16        ;16-byte align RSP

; >>>> Non-common code for various listings

            mov     r8, 12340000h            
            blsr    edx, r8

; Output value 1 is in rdx (extracted bit), resulting value
            
            call    print
            byte    "Value with xtracted bit: %x", nl, 0

; <<<< end of unique code.
                         
allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
