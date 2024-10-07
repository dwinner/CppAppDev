; Listing 13-4
;
; neg128 macro

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 13-4", 0
           

neg128      macro reg64HO, reg64LO

            ifb   <reg64LO>
            .err "neg128 requires 2 operands"
            endif

            neg  reg64HO
            neg  reg64LO
            sbb  reg64HO, 0
            endm



            include getTitle.inc
            include print.inc
            
            .code
            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbx
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage


            mov     rdx, 12345678h
            mov     rax, 90123456h
            neg128  rdx, rax
            
             
allDone:    leave
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
