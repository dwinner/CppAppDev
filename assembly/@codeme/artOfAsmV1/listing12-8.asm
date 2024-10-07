
; Listing 12-8
;
; Demonstration of the pext instruction.

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 12-8", 0

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
            sub     rsp, 56         ;Shadow storage

; >>>> Non-common code for various listings

                         
            mov     r8d, 12340000h
            mov     r9d, 0F0f000Fh             
            pext    edx, r8d, r9d

; Output value 1 is in rdx (mask)
            
            call    print
            byte    "Extracted: %x", nl, 0

; <<<< end of unique code.
                         
allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
