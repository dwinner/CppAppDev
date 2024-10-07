; Listing 5-12
;
; Accessing a parameter on the stack

        option  casemap:none

nl          =       10
stdout      =       -11

            .const
ttlStr      byte    "Listing 5-12", 0
fmtStr1     byte    "Value of parameter: %d", nl, 0
        
            .data
value1      dword   20
value2      dword   30
        
            .code
            externdef printf:proc
            
; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp


theParm     equ     <[rbp+16]> 
ValueParm   proc
            push    rbp
            mov     rbp, rsp
            
            sub     rsp, 32 ;Magic instruction
            
            lea     rcx, fmtStr1
            mov     edx, theParm
            call    printf
            
            leave
            ret
ValueParm   endp


; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbp
            mov     rbp, rsp
            sub     rsp, 40
        
            mov     eax, value1
            mov     [rsp], eax      ;Store parameter on stack
            call    ValueParm
            
            mov     eax, value2
            mov     [rsp], eax
            call    ValueParm
            
; Clean up, as per Microsoft ABI:

            leave
            ret     ;Returns to caller
        
asmMain     endp
            end