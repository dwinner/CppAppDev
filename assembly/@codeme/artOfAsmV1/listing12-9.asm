
; Listing 12-9
;
; Demonstration of the pdep instruction.

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 12-9", 0

            include	getTitle.inc
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

            mov     r8d, 1234h
            mov     r9d, 0F0FF00Fh             
            pdep    edx, r8d, r9d

; Output value 1 is in rdx (mask)
            
            call    print
            byte    "Distributed: %x", nl, 0
	                         
allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
