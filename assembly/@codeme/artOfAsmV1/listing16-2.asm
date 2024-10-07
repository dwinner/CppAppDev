; Listing 16-2            
;
; stringTokenize function test code:

; Include just the files we need from masm64rt.inc:

;            include \masm32\include64\masm64rt.inc
            OPTION DOTNAME                          ; required for macro files
            option casemap:none                     ; case sensitive
            include \masm32\include64\win64.inc     ; main include file
            include \masm32\macros64\macros64.inc   ; auxillary macro file
            include \masm32\include64\kernel32.inc

            .data
bytesWrtn   qword   ?
hwStr       byte    "Listing 16-2", 0ah, "Hello, World!", 0
hwLen       =       sizeof hwStr

            .code
         

;**********************************************************
;
; Here is the "asmMain" function.
        
            public  asmMain
asmMain     proc
            push    rbx
            push    rsi
            push    rdi
            push    r15
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage
            
            mov     rcx, -11    ; STD_OUTPUT
            call    __imp_GetStdHandle ;Returns handle
             
            xor     rcx, rcx
            mov     bytesWrtn, rcx
            
            lea     r9, bytesWrtn   ;Address of "bytesWritten" in R9
            mov     r8d, hwLen      ;Length of string to write in R8D 
            lea     rdx, hwStr      ;Ptr to string data in RDX
            mov     rcx, rax        ;File handle passed in RCX
            call    __imp_WriteFile
                         
allDone:    leave
            pop     r15
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
