
; Listing 11-5
;
; Generic print procedure and dynamically
; selecting CPU features.


        option  casemap:none

nl          =       10



; SSE4.2 feature flags (in ECX):

SSE42       =       00180000h       ;Bits 19 & 20
AVXSupport  =       10000000h       ;Bit 28

; CPUID bits (EAX=7, EBX register)

AVX2Support  =      20h             ;Bit 5 = AVX


            .const
ttlStr      byte    "Listing 11-5", 0

            
            

            .data
            align   qword
print       qword   choosePrint     ;Pointer to print function

; Floating-point values for testing purposes:

fp1         real8   1.0
fp2         real8   2.0
fp3         real8   3.0
fp4         real8   4.0
fp5         real8   5.0
            

            
            
            .code
            externdef printf:proc
            
; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp


;***************************************************************
;            
; print-
;
;  "Quick" form of printf that allows the format string to
; follow the call in the code stream. Supports up to five
; additional parameters in RDX, R8, R9, R10, and R11.
;
; This function saves all the Microsoft-ABI volatile,
; parameter, and return result registers so that code
; can call it without worrying about any registers being
; modified (this code assumes that Windows ABI treats
; YMM4..YMM15 as non-volatile).
;
; Of course, this code assumes that AVX instructions are
; available on the CPU.

; Allows up to 5 arguments in:
;
;  RDX-  Arg #1 
;  R8-   Arg #2  
;  R9-   Arg #3  
;  R10-  Arg #4
;  R11-  Arg #5
;
; Note that you must pass floating-point values in
; these registers, as well. The printf function
; expects real values in the integer registers. 
; 
;
; There are two versions of this function, one that
; will run on CPUs without AVX capabilities (no YMM
; registers) and one that will run on CPUs that
; have AVX capabilities (YMM registers). The difference
; between the two is which registers they preserve
; (print_SSE only preserves XMM registers and will
; run properly on CPUs that don't have YMM register
; support; print_AVX will preserve the volatile YMM
; registers on CPUs with AVX support);

; On first call, determine if we support AVX instructions
; and set the "print" pointer to point at print_AVX or
; print_SSE:
 
choosePrint proc
            push    rax     ;Preserve registers that get
            push    rbx     ; tweaked by CPUID
            push    rcx
            push    rdx
            
            mov     eax, 1
            cpuid
            test    ecx, AVXSupport ;Test bit 28 for AVX
            jnz     doAVXPrint
            
            lea     rax, print_SSE  ;From now on, call
            mov     print, rax      ;print_SSE directly

; Return address must point at the format string
; following the call to this function! So we have
; to clean up the stack and JMP to print_SSE.

            pop     rdx
            pop     rcx
            pop     rbx
            pop     rax
            jmp     print_SSE
            
doAVXPrint: lea     rax, print_AVX  ;From now on, call
            mov     print, rax      ;print_AVX directly
            
; Return address must point at the format string
; following the call to this function! So we have
; to clean up the stack and JMP to print_AUX.

            pop     rdx
            pop     rcx
            pop     rbx
            pop     rax
            jmp     print_AVX

choosePrint endp

; Version of print that will preserve volatile
; AVX registers (YMM0..YMM3):

print_AVX   proc

; Preserve all the volatile register
; (be nice to the assembly code that
;  calls this procedure):

            push    rax
            push    rbx
            push    rcx
            push    rdx
            push    r8
            push    r9
            push    r10
            push    r11
            
; YMM0..YMM3 are considered volatile, so preserve them

            sub     rsp, 128
            vmovdqu ymmword ptr [rsp+000], ymm0
            vmovdqu ymmword ptr [rsp+032], ymm1
            vmovdqu ymmword ptr [rsp+064], ymm2
            vmovdqu ymmword ptr [rsp+096], ymm3
            
            
            push    rbp

returnAdrs  textequ <[rbp+200]>

            mov     rbp, rsp
            sub     rsp, 128
            and     rsp, -16
            
; Format string (passed in RCX) is sitting at
; the location pointed at by the return address,
; load that into RCX:

            mov     rcx, returnAdrs
            
; To handle more than three arguments (4 counting
; RCX) must pass data on stack. However, to the
; print caller the stack is unavailable, so use
; R10 and R11 as extra parameters (could be just
; junk in these registers, but pass them just
; in case):

            mov     [rsp+32], r10
            mov     [rsp+40], r11
            call    printf
            
; Need to modify the return address so
; that it points beyond the zero-terminating byte.
; Could use a fast strlen function for this, but
; printf is so slow it won't really save us anything.
            
            mov     rcx, returnAdrs
            dec     rcx
skipTo0:    inc     rcx
            cmp     byte ptr [rcx], 0
            jne     skipTo0
            inc     rcx
            mov     returnAdrs, rcx
            
            leave
            vmovdqu ymm0, ymmword ptr [rsp+000]
            vmovdqu ymm1, ymmword ptr [rsp+032]
            vmovdqu ymm2, ymmword ptr [rsp+064]
            vmovdqu ymm3, ymmword ptr [rsp+096]
            add     rsp, 128
            pop     r11
            pop     r10
            pop     r9
            pop     r8
            pop     rdx
            pop     rcx
            pop     rbx
            pop     rax
            ret
print_AVX   endp


; Version that will run on CPUs without
; AVX support and will preserve the
; volatile SSE registers (XMM0..XMM3):

print_SSE   proc

; Preserve all the volatile register
; (be nice to the assembly code that
;  calls this procedure):

            push    rax
            push    rbx
            push    rcx
            push    rdx
            push    r8
            push    r9
            push    r10
            push    r11
            
; XMM0..XMM3 are considered volatile, so preserve them

            sub     rsp, 64
            movdqu  xmmword ptr [rsp+00], xmm0
            movdqu  xmmword ptr [rsp+16], xmm1
            movdqu  xmmword ptr [rsp+32], xmm2
            movdqu  xmmword ptr [rsp+48], xmm3
            
            
            push    rbp

returnAdrs  textequ <[rbp+136]>

            mov     rbp, rsp
            sub     rsp, 128
            and     rsp, -16
            
; Format string (passed in RCX) is sitting at
; the location pointed at by the return address,
; load that into RCX:

            mov     rcx, returnAdrs
            
; To handle more than three arguments (4 counting
; RCX) must pass data on stack. However, to the
; print caller the stack is unavailable, so use
; R10 and R11 as extra parameters (could be just
; junk in these registers, but pass them just
; in case):

            mov     [rsp+32], r10
            mov     [rsp+40], r11
            call    printf
            
; Need to modify the return address so
; that it points beyond the zero-terminating byte.
; Could use a fast strlen function for this, but
; printf is so slow it won't really save us anything.
            
            mov     rcx, returnAdrs
            dec     rcx
skipTo0:    inc     rcx
            cmp     byte ptr [rcx], 0
            jne     skipTo0
            inc     rcx
            mov     returnAdrs, rcx
            
            leave
            movdqu  xmm0, xmmword ptr [rsp+00]
            movdqu  xmm1, xmmword ptr [rsp+16]
            movdqu  xmm2, xmmword ptr [rsp+32]
            movdqu  xmm3, xmmword ptr [rsp+48]
            add     rsp, 64
            pop     r11
            pop     r10
            pop     r9
            pop     r8
            pop     rdx
            pop     rcx
            pop     rbx
            pop     rax
            ret
print_SSE   endp            


            
;***************************************************************
;            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbx
            push    rsi
            push    rdi
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage

; Trivial example, no arguments:

            call    print
            byte    "Hello, World!", nl, 0
            
; Simple example with integer arguments:

            mov     rdx, 1          ;Argument #1 for printf
            mov     r8, 2           ;Argument #2 for printf
            mov     r9, 3           ;Argument #3 for printf
            mov     r10, 4          ;Argument #4 for printf
            mov     r11, 5          ;Argument #5 for printf
            call    print
            byte    "Arg 1=%d, Arg2=%d, Arg3=%d "
            byte    "Arg 4=%d, Arg5=%d", nl, 0
            
; Demonstration of floating-point operands. Note that
; args 1, 2, and 3 must be passed in rdx, r8, and
; r9 (despite Microsoft ABI requirements). You'll have
; to load parameters 4 and 5 into R10 and R11.

            mov     rdx, qword ptr fp1
            mov     r8,  qword ptr fp2
            mov     r9,  qword ptr fp3
            mov     r10, qword ptr fp4
            mov     r11, qword ptr fp5
            call    print
            byte    "Arg1=%6.1f, Arg2=%6.1f, Arg3=%6.1f "
            byte    "Arg4=%6.1f, Arg5=%6.1f ", nl, 0
                         
             


allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
