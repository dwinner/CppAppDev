; Listing 8-2
;
; 256-bit by 64-bit division

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 8-2", 0
fmtStr1     byte    "quotient  = "
            byte    "%08x_%08x_%08x_%08x_%08x_%08x_%08x_%08x"
            byte    nl, 0
            
fmtStr2     byte    "remainder = %I64x", nl, 0
            
            
             .data

; op1 is a 256-bit value. Initial values were chosen
; to make it easy to verify result.

op1         oword   2222eeeeccccaaaa8888666644440000h
            oword   2222eeeeccccaaaa8888666644440000h
            
op2         qword   2
result      oword   2 dup (0) ;Also 256 bits
remain      qword   0

            .code
            externdef printf:proc
            
; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp


; div256-
;    Divides a 256-bit number by a 64-bit number.
;
; Dividend - passed by reference in RCX.
; Divisor  - passed in RDX.
;
; Quotient - passed by reference in R8.
; Remainder- passed by reference in R9.

div256      proc
divisor     equ     <qword ptr [rbp-8]>
dividend    equ     <qword ptr [rcx]>
quotient    equ     <qword ptr [r8]>
remainder   equ     <qword ptr [r9]>

            push    rbp
            mov     rbp, rsp
            sub     rsp, 8
            
            mov     divisor, rdx
            
            mov     rax, dividend[24]  ; Begin div with HO qword
            xor     rdx, rdx           ; Zero extend into RDS
            div     divisor            ; Divide HO word
            mov     quotient[24], rax  ; Save HO result
            
            mov     rax, dividend[16]  ; Get dividend qword #2
            div     divisor            ; Continue with division
            mov     quotient[16], rax  ; Store away qword #2
            
            mov     rax, dividend[8]   ; Get dividend qword #1
            div     divisor            ; Continue with division
            mov     quotient[8], rax   ; Store away qword #1
            
            mov     rax, dividend[0]   ; Get LO dividend qword
            div     divisor            ; Continue with division
            mov     quotient[0], rax   ; Store away LO qword
            
            mov     remainder, rdx     ; Save away remainder
                
            leave
            ret            
div256      endp
            
            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbp
            mov     rbp, rsp
            sub     rsp, 80         ;Shadow storage
            

; Test the div256 function:

            lea     rcx, op1
            mov     rdx, op2
            lea     r8, result
            lea     r9, remain
            call    div256
                        
; Print the results:

            lea     rcx, fmtStr1
            mov     edx, dword ptr result[28]
            mov     r8d, dword ptr result[24]
            mov     r9d, dword ptr result[20]
            mov     eax, dword ptr result[16]
            mov     [rsp+32], rax
            mov     eax, dword ptr result[12]
            mov     [rsp+40], rax
            mov     eax, dword ptr result[8]
            mov     [rsp+48], rax
            mov     eax, dword ptr result[4]
            mov     [rsp+56], rax
            mov     eax, dword ptr result[0]
            mov     [rsp+64], rax
            call    printf
                

            lea     rcx, fmtStr2
            mov     rdx, remain
            call    printf
                
            
            leave
            ret     ;Returns to caller
        
asmMain     endp
            end