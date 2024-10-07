; Listing 8-3
;
; 128-bit by 128-bit division

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 8-3", 0
fmtStr1     byte    "quotient  = "
            byte    "%08x_%08x_%08x_%08x"
            byte    nl, 0
            
fmtStr2     byte    "remainder = "
            byte    "%08x_%08x_%08x_%08x"
            byte    nl, 0
            
fmtStr3     byte    "quotient (2)  = "
            byte    "%08x_%08x_%08x_%08x"
            byte    nl, 0
            
            
             .data

; op1 is a 128-bit value. Initial values were chosen
; to make it easy to verify result.

op1         oword   2222eeeeccccaaaa8888666644440000h            
op2         oword   2
op3         oword   11117777666655554444333322220000h
result      oword   ?
remain      oword   ?

            .code
            externdef printf:proc
            
; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp


; div128-
;
; This procedure does a general 128/128 division operation 
; using the following algorithm (all variables are assumed 
; to be 128-bit objects):
;
; Quotient := Dividend;
; Remainder := 0;
; for i := 1 to NumberBits do
; 
;  Remainder:Quotient := Remainder:Quotient SHL 1;
;  if Remainder >= Divisor then
; 
;      Remainder := Remainder - Divisor;
;      Quotient := Quotient + 1;
; 
;  endif
; endfor
;
; Data passed:
;
; 128-bit dividend, by reference in RCX
; 128-bit divisor, by reference in RDX
;
; Data returned:
;
; Pointer to 128-bit quotient in R8
; Pointer to 128-bit remainder in R9 

div128      proc
remainder   equ     <[rbp-16]>
dividend    equ     <[rbp-32]>
quotient    equ     <[rbp-32]>      ;Aliased to dividend
divisor     equ     <[rbp-48]>

            push    rbp
            mov     rbp, rsp
            sub     rsp, 48
            
            push    rax
            push    rcx
            
            xor     rax, rax        ;Initialize remainder to 0
            mov     remainder, rax
            mov     remainder[8], rax
            
; Copy the dividend to local storage

            mov     rax, [rcx]
            mov     dividend, rax
            mov     rax, [rcx+8]
            mov     dividend[8], rax
            
; Copy the divisor to local storage

            mov     rax, [rdx]
            mov     divisor, rax
            mov     rax, [rdx+8]
            mov     divisor[8], rax
            
            
            mov     cl, 128           ;Count off bits in cl

; Compute Remainder:Quotient := Remainder:Quotient SHL 1:

repeatLp:   shl     qword ptr dividend[0], 1  ;256-bit extended
            rcl     qword ptr dividend[8], 1  ; precision shift
            rcl     qword ptr remainder[0], 1 ; through remainder
            rcl     qword ptr remainder[8], 1       

; Do a 128-bit comparison to see if the remainder
; is greater than or equal to the divisor.

            mov     rax, remainder[8]
            cmp     rax, divisor[8]
            ja      isGE
            jb      notGE
            
            mov     rax, remainder
            cmp     rax, divisor
            ja      isGE
            jb      notGE
            
; Remainder := Remainder - Divisor

isGE:       mov     rax, divisor
            sub     remainder, rax
            mov     rax, divisor[8]
            sbb     remainder[8], rax

; Quotient := Quotient + 1;


            add     qword ptr quotient, 1
            adc     qword ptr quotient[8], 0

notGE:      dec     cl
            jnz     repeatLp


; Okay, copy the quotient (left in the Dividend variable)
; and the remainder to their return locations.
    
            mov     rax, quotient[0]
            mov     [r8], rax
            mov     rax, quotient[8]
            mov     [r8][8], rax
            
            mov     rax, remainder[0]
            mov     [r9], rax
            mov     rax, remainder[8]
            mov     [r9][8], rax


            pop     rcx
            pop     rax
            leave
            ret
                        
div128      endp





            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbp
            mov     rbp, rsp
            sub     rsp, 64         ;Shadow storage
            

; Test the div128 function:

            lea     rcx, op1
            lea     rdx, op2
            lea     r8, result
            lea     r9, remain
            call    div128
                        
; Print the results:

            lea     rcx, fmtStr1
            mov     edx, dword ptr result[12]
            mov     r8d, dword ptr result[8]
            mov     r9d, dword ptr result[4]
            mov     eax, dword ptr result[0]
            mov     [rsp+32], rax
            call    printf
                

            lea     rcx, fmtStr2
            mov     edx, dword ptr remain[12]
            mov     r8d, dword ptr remain[8]
            mov     r9d, dword ptr remain[4]
            mov     eax, dword ptr remain[0]
            mov     [rsp+32], rax
            call    printf
                
            
; Test the div128 function:

            lea     rcx, op1
            lea     rdx, op3
            lea     r8, result
            lea     r9, remain
            call    div128
                        
; Print the results:

            lea     rcx, fmtStr3
            mov     edx, dword ptr result[12]
            mov     r8d, dword ptr result[8]
            mov     r9d, dword ptr result[4]
            mov     eax, dword ptr result[0]
            mov     [rsp+32], rax
            call    printf
                

            lea     rcx, fmtStr2
            mov     edx, dword ptr remain[12]
            mov     r8d, dword ptr remain[8]
            mov     r9d, dword ptr remain[4]
            mov     eax, dword ptr remain[0]
            mov     [rsp+32], rax
            call    printf
            
            leave
            ret     ;Returns to caller
        
asmMain     endp
            end