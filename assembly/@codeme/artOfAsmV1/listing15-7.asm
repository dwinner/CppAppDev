
; Listing 15-7
;
; Demonstration of linking

            include    aoalib.inc
            includelib aoalib.lib
            
            .data
ttlStr      byte       "Listing 15-7", 0
            
;***************************************************************
;            
; Here is the "asmMain" function.

            .code
proc1       proc
            call    print
            byte    "entered proc1", nl, 0
            cmp     eax, 0
            je      proc2
            call    print
            byte    "leaving proc1", nl, 0
            ret
proc1       endp

proc2       proc
            call    print
            byte    "entered proc2", nl, 0
            ret
proc2       endp


            public  asmMain
asmMain     proc
            push    rbx
            push    rsi
            push    rdi
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage
            
            mov     eax, 0
            call    proc1
            mov     eax, 1
            call    proc1
            leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
