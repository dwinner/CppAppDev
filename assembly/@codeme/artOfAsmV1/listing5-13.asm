; Listing 5-13
;
; Accessing a reference parameter on the stack

        option  casemap:none

nl          =       10
stdout      =       -11

            .const
ttlStr      byte    "Listing 5-13", 0
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
RefParm     proc
            push    rbp
            mov     rbp, rsp
            
            sub     rsp, 32 ;Magic instruction
            
            lea     rcx, fmtStr1
            mov     rax, theParm    ;Dereference parameter
            mov     edx, [rax]
            call    printf
            
            leave
            ret
RefParm     endp


; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbp
            mov     rbp, rsp
            sub     rsp, 40
        
            lea     rax, value1
            mov     [rsp], rax      ;Store address on stack
            call    RefParm
            
            lea     rax, value2
            mov     [rsp], rax
            call    RefParm
            
; Clean up, as per Microsoft ABI:

            leave
            ret     ;Returns to caller
        
asmMain     endp
            end