
; Listing 15-4
;
; Demonstration of linking

            include aoalib.inc
            
            .data
ttlStr      byte    "Listing 15-4", 0
            
;***************************************************************
;            
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
            
            call    print
            byte    "Assembly units linked", nl, 0

            leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
