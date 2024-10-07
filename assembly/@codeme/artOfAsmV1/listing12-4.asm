
; Listing 12-4
;
; Demonstration of the blsi and andn instructions.

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 12-4", 0

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
            blsi    edx, r8
            andn    r8, rdx, r8

; Output value 1 is in rdx (extracted bit),
; output value 2 in r8 (value with deleted bit)
            
            call    print
            byte    "Extracted bit: %x, result: %x", nl, 0

; <<<< end of unique code.
                         
allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
