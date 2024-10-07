
; Listing 12-7
;
; Creating a bit mask with blsi and dec 

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 12-7", 0


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

            mov     r8, 12340000h            
            blsi    rdx, r8
            dec     rdx

; Output value 1 is in rdx (mask)
            
            call    print
            byte    "Mask: %x", nl, 0

; <<<< end of unique code.
                         
allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
