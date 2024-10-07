; Listing 7-5
;
; Demonstration of memory indirect jumps

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 7-5", 0
fmtStr1     byte    "Before indirect jump", nl, 0
fmtStr2     byte    "After indirect jump", nl, 0
            

            .code
            externdef printf:proc
            
; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp


            
            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbp
            mov     rbp, rsp
            sub     rsp, 48                 ;Shadow storage
            
            lea     rcx, fmtStr1
            call    printf
            jmp     memPtr
            
memPtr      qword   ExitPoint

ExitPoint:  lea     rcx, fmtStr2
            call    printf
            
            leave
            ret     ;Returns to caller
        
asmMain     endp
            end