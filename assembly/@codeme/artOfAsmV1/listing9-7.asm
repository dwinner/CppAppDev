; Listing 9-7
;
; Extended-precision numeric unsigned integer 
; to string function

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 9-7", 0
fmtStr1     byte    "otoStr(0): string=%s", nl, 0
fmtStr2     byte    "otoStr(1234567890): string=%s", nl, 0
fmtStr3     byte    "otoStr(2147483648): string=%s", nl, 0
fmtStr4     byte    "otoStr(4294967296): string=%s", nl, 0
fmtStr5     byte    "otoStr(FFF...FFFF): string=%s", nl, 0
            
            .data
buffer      byte    40 dup (?)

b0          oword   0
b1          oword   1234567890
b2          oword   2147483648
b3          oword   4294967296
    
; Largest oword value
; (decimal=340,282,366,920,938,463,463,374,607,431,768,211,455):
    
b4          oword   0FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFh
            
            .code
            externdef printf:proc
            
; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp



; DivideBy10-
;
;  Divides "divisor" by 10 using fast
;  extended-precision division algorithm
;  that employs the div instruction.
;
;  Returns quotient in "quotient".
;  Returns remainder in rax.
;  Trashes rdx.
;
; RCX - points at oword dividend and location to
;       receive quotient

ten         qword   10

DivideBy10  proc
parm        equ     <[rcx]>

            xor     edx, edx
            mov     rax, parm[8]
            div     ten
            mov     parm[8], rax
            
            mov     rax, parm
            div     ten
            mov     parm, rax
            mov     eax, edx        ;Remainder (always 0..9!)
            ret    
DivideBy10  endp



; Recursive version of otoStr.
; A separate "shell" procedure calls this so that
; this code does not have to preserve all the registers
; it uses (and DivideBy10 uses) on each recursive call.
;
; On entry:
;    Stack contains oword in/out parameter (dividend in/quotient out)
;    RDI- contains location to place output string
;
; Note: this function must clean up stack (parameters)
;       on return.

rcrsvOtoStr proc
value       equ     <[rbp+16]>
remainder   equ     <[rbp-8]>
            push    rbp
            mov     rbp, rsp
            sub     rsp, 8
            lea     rcx, value
            call    DivideBy10
            mov     remainder, al
            
; If the quotient (left in value) is not 0, recursively
; call this routine to output the HO digits.

            mov     rax, value
            or      rax, value[8]
            jz      allDone
            
            mov     rax, value[8]
            push    rax
            mov     rax, value
            push    rax
            call    rcrsvOtoStr

allDone:    mov     al, remainder
            or      al, '0'
            mov     [rdi], al
            inc     rdi
            leave
            ret     16      ;Remove parms from stack
rcrsvOtoStr endp
            


; Nonrecursive shell to the above routine so we don't bother
; saving all the registers on each recursive call.
;
; On entry:
;
;   RDX:RAX- contains oword to print
;   RDI-     buffer to hold string (at least 40 bytes)

otostr      proc

            push    rax
	push	rcx
            push    rdx
            push    rdi

; Special-case zero:

            test    rax, rax
            jnz     not0
            test    rdx, rdx
            jnz     not0
            mov     byte ptr [rdi], '0'
            inc     rdi
            jmp     allDone
            
not0:       push    rdx
            push    rax
            call    rcrsvOtoStr
            
; Zero-terminate string before leaving

allDone:    mov     byte ptr [rdi], 0

            pop     rdi
            pop     rdx
	pop	rcx
            pop     rax
            ret
    
otostr      endp
            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rdi
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage
            
; Because all the (x)toStr functions preserve RDI,
; we only need to do the following once:
 
            lea     rdi, buffer

; Convert b0 to a string and print the result:
            
            mov     rax, qword ptr b0
            mov     rdx, qword ptr b0[8]
            call    otostr

            lea     rcx, fmtStr1
            lea     rdx, buffer
            call    printf
            
; Convert b1 to a string and print the result:
            
            mov     rax, qword ptr b1
            mov     rdx, qword ptr b1[8]
            call    otostr

            lea     rcx, fmtStr2
            lea     rdx, buffer
            call    printf
            
; Convert b2 to a string and print the result:
            
            mov     rax, qword ptr b2
            mov     rdx, qword ptr b2[8]
            call    otostr

            lea     rcx, fmtStr3
            lea     rdx, buffer
            call    printf
            
; Convert b3 to a string and print the result:
            
            mov     rax, qword ptr b3
            mov     rdx, qword ptr b3[8]
            call    otostr

            lea     rcx, fmtStr4
            lea     rdx, buffer
            call    printf
            
; Convert b4 to a string and print the result:
            
            mov     rax, qword ptr b4
            mov     rdx, qword ptr b4[8]
            call    otostr

            lea     rcx, fmtStr5
            lea     rdx, buffer
            call    printf
            
            leave
            pop     rdi
            ret     ;Returns to caller
        
asmMain     endp
            end