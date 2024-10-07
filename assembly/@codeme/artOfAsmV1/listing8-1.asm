; Listing 8-1
;
; 128-bit multiplication

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 8-1", 0
fmtStr1     byte    "%d * %d = %I64d (verify:%I64d)", nl, 0
            
            
             .data
op1         qword   123456789
op2         qword   234567890
product     oword   ?           
product2    oword   ?           

            .code
            externdef printf:proc
            
; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp


; mul64-
;
;  Multiplies two 64-bit values passed in rdx and rax by
; doing a 64x64-bit multiplication, producing a 128-bit result. 
; Algorithm is easily extended to 128x128 bits by switching the 
; 32-bit registers for 64-bit registers.
;
; Stores result to location pointed at by R8.


mul64       proc
mp          equ     <dword ptr [rbp-8]>     ;Multiplier
mc          equ     <dword ptr [rbp-16]>    ;Multiplicand
prd         equ     <dword ptr [r8]>        ;Result

            push    rbp
            mov     rbp, rsp
            sub     rsp, 24
            
            push    rbx     ;Preserve these register values
            push    rcx
            

; Save parameters passed in registers:

            mov     qword ptr mp, rax
            mov     qword ptr mc, rdx

; Multiply the LO dword of Multiplier times Multiplicand.
                                           
            mov eax, mp
            mul mc          ; Multiply LO dwords.
            mov prd, eax    ; Save LO dword of product.
            mov ecx, edx    ; Save HO dword of partial product result.

            mov eax, mp
            mul mc[4]       ; Multiply mp(LO) * mc(HO)
            add eax, ecx    ; Add to the partial product.
            adc edx, 0      ; Don't forget the carry!
            mov ebx, eax    ; Save partial product for now.
            mov ecx, edx

; Multiply the HO word of Multiplier with Multiplicand.

            mov eax, mp[4]  ; Get HO dword of Multiplier.
            mul mc          ; Multiply by LO word of Multiplicand.
            add eax, ebx    ; Add to the partial product.
            mov prd[4], eax ; Save the partial product.
            adc ecx, edx    ; Add in the carry!

            mov eax, mp[4]  ; Multiply the two HO dwords together.
            mul mc[4]
            add eax, ecx    ; Add in partial product.
            adc edx, 0      ; Don't forget the carry!
            
            mov prd[8], eax ;Save HO qword of result
            mov prd[12], edx
    
; EDX:EAX contains 64-bit result at this point

            pop     rcx     ; Restore these registers
            pop     rbx
            leave
            ret    
mul64       endp

            
            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbp
            mov     rbp, rsp
            sub     rsp, 64         ;Shadow storage
            

; Test the mul64 function:

            mov     rax, op1
            mov     rdx, op2
            lea     r8, product
            call    mul64
            
; Use a 64-bit multiply to test the result

            mov     rax, op1
            mov     rdx, op2
            imul    rax, rdx
            mov     qword ptr product2, rax
            
; Print the results:

            lea     rcx, fmtStr1
            mov     rdx, op1
            mov     r8,  op2
            mov     r9,  qword ptr product
            mov     rax, qword ptr product2
            mov     [rsp+32], rax
            call    printf
                
            
            leave
            ret     ;Returns to caller
        
asmMain     endp
            end