; Listing 13-7
;
; OPATTR demonstration

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 14-7", 0
           
fmtStr      byte    nl, "Hello, World! #2", nl, 0

            .code
            externdef printf:proc
            
; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp


; cprintf macro-
;
;           cprintf fmtStr
;           cprintf "Format String"

cprintf     macro   fmtStrArg
            local   fmtStr, attr, isConst
            
attr        =       OPATTR fmtStrArg
isConst     =       (attr and 4) eq 4
            if      (attr eq 0) or isConst
            .data                                              
fmtStr      byte    fmtStrArg, 0
            .code
            lea     rcx, fmtStr
            
            else
            
            lea     rcx, fmtStrArg
            
            endif
            call    printf
            endm
 
atw         =       opattr "Hello Word"
bin         =       opattr "abcdefghijklmnopqrstuvwxyz"                 
                    
            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbx
            push    rdi
            push    rsi
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage

            cprintf "Hello World!"
            cprintf fmtStr
             
allDone:    leave
            pop     rsi
            pop     rdi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
