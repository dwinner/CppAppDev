; Listing 9-4
;
; Numeric unsigned integer to string function

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 9-4", 0
fmtStr1     byte    "utoStr: Value=%I64u, string=%s"
            byte    nl, 0
            
            .data
buffer      byte    24 dup (?)
            
            .code
            externdef printf:proc
            
; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp


; utoStr-
;
;  Unsigned integer to string.
;
; Inputs:
;
;    RAX:   Unsigned integer to convert
;    RDI:   Location to hold string.
;
; Note: for 64-bit integers, resulting
; string could be as long as  20 bytes
; (including the zero-terminating byte).

utoStr      proc
            push    rax
            push    rdx
            push    rdi

; Handle zero specially:
            
            test    rax, rax
            jnz     doConvert
            
            mov     byte ptr [rdi], '0'
            inc     rdi
            jmp     allDone 
            

doConvert:  call    rcrsvUtoStr

; Zero-terminte the string and return:
            
allDone:    mov     byte ptr [rdi], 0
            pop     rdi
            pop     rdx
            pop     rax
            ret
utoStr      endp

ten         qword   10

; Here's the recursive code that does the
; actual conversion:

rcrsvUtoStr proc

            xor     rdx, rdx ;Zero-extend RAX->RDX
            div     ten
            push    rdx      ;Save output value
            test    eax, eax ;Quit when RAX is 0
            jz      allDone 
            
; Recursive call to handle value % 10:

            call    rcrsvUtoStr

allDone:    pop     rax                ;Retrieve char to print
            and     al, 0Fh            ;Convert to '0'..'9'
            or      al, '0'
            mov     byte ptr [rdi], al ;Save in buffer
            inc     rdi                ;Next char position
            ret
rcrsvUtoStr endp


            
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
            mov     rax, 1234567890
            call    utoStr
            
; Print the result

            lea     rcx, fmtStr1
            mov     rdx, rax
            mov     r8, rdi
            call    printf
            
            leave
            pop     rdi
            ret     ;Returns to caller
        
asmMain     endp
            end