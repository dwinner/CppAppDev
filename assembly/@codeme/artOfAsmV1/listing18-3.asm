; Listing 18-3
;
; stringAlloc and stringFree functions.

            option     casemap:none
            include    aoalib.inc
            include    string.inc
            includelib aoalib.lib

            .const
ttlStr      byte    "Listing 18-3", 0

            .data
strPtr      qword   ?            

            .code

; Here is the "asmMain" function.
        
            public  asmMain
asmMain     proc
            push    rbx
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage

            mov     eax, 64
            call    stringAlloc
            mov     strPtr, rax

            mov     rax, strPtr
            call    stringFree
                         
allDone:    leave
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
