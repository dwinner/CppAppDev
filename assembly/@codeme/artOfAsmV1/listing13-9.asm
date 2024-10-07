; Listing 13-9
;
; HLL-like procedure calls with
; a varying parameter list.

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 14-9", 0
            
            .code
            externdef printf:proc
            
            include getTitle.inc
            
; Note: don't include print.inc here
; because this code uses a macro for
; print.

; print macro-
;
; HLL-like calling sequence for the _print
; function (which is, itself, a shell for
; the printf function).
;
; If print appears on a line by itself (no
; arguments), then emit a string consisting
; of a single newline character (and zero
; terminating byte). If there are one or
; more arguments, emit each argument; append
; a single zero byte after all the arguments.
;
; Examples:
;
;           print
;           print   "Hello, World!"
;           print   "Hello, World!", nl

print       macro   arg1, optArgs:vararg
            call    _print
            
            ifb     <arg1>

; If print is used byte itself, print a
; newline character:
            
            byte    nl, 0
            
            else
            
; If we have one or more arguments, then
; emit each of them:
            
            byte    arg1

            for     oa, <optArgs>
            
            byte    oa
            
            endm

; Zero-terminate the string.

            byte    0
            
            endif
            endm
 
_print      proc
            push    rax
            push    rbx
            push    rcx
            push    rdx
            push    r8
            push    r9
            push    r10
            push    r11
            
            push    rbp
            mov     rbp, rsp
            sub     rsp, 40
            and     rsp, -16
            
            mov     rcx, [rbp+72]   ;Return address
            call    printf
            
            mov     rcx, [rbp+72]
            dec     rcx
skipTo0:    inc     rcx
            cmp     byte ptr [rcx], 0
            jne     skipTo0
            inc     rcx
            mov     [rbp+72], rcx
            
            leave
            pop     r11
            pop     r10
            pop     r9
            pop     r8
            pop     rdx
            pop     rcx
            pop     rbx
            pop     rax
            ret
_print      endp
              
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbx
            push    rdi
            push    rsi
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage

            print   "Hello world"
            print
            print   "Hello, World!", nl
                        

             
allDone:    leave
            pop     rsi
            pop     rdi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
