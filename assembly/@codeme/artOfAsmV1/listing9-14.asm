; Listing 9-14
;
; String to numeric conversion

        option  casemap:none

false       =       0
true        =       1
tab         =       9
nl          =       10

            .const
ttlStr      byte    "Listing 9-14", 0
fmtStr1     byte    "strtou: String='%s'", nl
            byte    "    value=%I64u", nl, 0
            
fmtStr2     byte    "Overflow: String='%s'", nl
            byte    "    value=%I64x", nl, 0
            
fmtStr3     byte    "strtoi: String='%s'", nl
            byte    "    value=%I64i",nl, 0
                    
unexError   byte    "Unexpected error in program", nl, 0
            
value1      byte    "  1", 0
value2      byte    "12 ", 0
value3      byte    " 123 ", 0
value4      byte    "1234", 0
value5      byte    "1234567890123456789", 0
value6      byte    "18446744073709551615", 0
OFvalue     byte    "18446744073709551616", 0
OFvalue2    byte    "999999999999999999999", 0
            
ivalue1     byte    "  -1", 0
ivalue2     byte    "-12 ", 0
ivalue3     byte    " -123 ", 0
ivalue4     byte    "-1234", 0
ivalue5     byte    "-1234567890123456789", 0
ivalue6     byte    "-9223372036854775807", 0
OFivalue    byte    "-9223372036854775808", 0
OFivalue2   byte    "-999999999999999999999", 0
            
            .data
buffer      byte    30 dup (?)
            
            .code
            externdef printf:proc
            
; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp



; strtou-
;  Converts string data to a 64-bit unsigned integer.
;
; Input-
;   RDI-    Pointer to buffer containing string to convert
;
; Output-
;   RAX-    Contains converted string (if success), error code
;           if an error occurs.
;
;   RDI-    Points at first char beyond end of numeric string.
;           If error, RDI's value is restored to original value.
;           Caller can check character at [RDI] after a
;           successful result to see if the character following
;           the numeric digits is a legal numeric delimiter.
;
;   C       (carry flag) Set if error occurs, clear if
;           conversion was successful. On error, RAX will
;           contain 0 (illegal initial character) or
;           0ffffffffffffffffh (overflow).

strtou      proc
            push    rdi      ;In case we have to restore RDI
            push    rdx      ;Munged by mul 
            push    rcx      ;Holds input char
            
            xor     edx, edx ;Zero extends!
            xor     eax, eax ;Zero extends!
            
; The following loop skips over any whitespace (spaces and
; tabs) that appear at the beginning of the string.

            dec     rdi      ;Because of inc below.
skipWS:     inc     rdi
            mov     cl, [rdi]
            cmp     cl, ' '
            je      skipWS
            cmp     al, tab
            je      skipWS
            
; If we don't have a numeric digit at this point,
; return an error.

            cmp     cl, '0'  ;Note: '0' < '1' < ... < '9'
            jb      badNumber
            cmp     cl, '9'
            ja      badNumber
            
; Okay, the first digit is good. Convert the string
; of digits to numeric form:

convert:    and     ecx, 0fh ;Convert to numeric in RCX
            mul     ten      ;Accumulator *= 10
            jc      overflow
            add     rax, rcx ;Accumulator += digit
            jc      overflow
            inc     rdi      ;Move on to next character
            mov     cl, [rdi]
            cmp     cl, '0'
            jb      endOfNum
            cmp     cl, '9'
            jbe     convert

; If we get to this point, we've successfully converted
; the string to numeric form:

endOfNum:   pop     rcx
            pop     rdx
            
; Because the conversion was successful, this procedure
; leaves RDI pointing at the first character beyond the
; converted digits. As such, we don't restore RDI from
; the stack. Just bump the stack pointer up by 8 bytes
; to throw away RDI's saved value.

            add     rsp, 8
            clc              ;Return success in carry flag
            ret
            
; badNumber- Drop down here if the first character in
;            the string was not a valid digit.

badNumber:  mov     rax, 0
            pop     rcx
            pop     rdx
            pop     rdi
            stc              ;Return error in carry flag
            ret     
                    
overflow:   mov     rax, -1  ;0FFFFFFFFFFFFFFFFh
            pop     rcx
            pop     rdx
            pop     rdi
            stc              ;Return error in carry flag
            ret
                    
ten         qword   10
                    
strtou      endp


; strtoi-
;  Converts string data to a 64-bit signed integer.
;
; Input-
;   RDI-    Pointer to buffer containing string to convert
;
; Output-
;   RAX-    Contains converted string (if success), error code
;           if an error occurs.
;
;   RDI-    Points at first char beyond end of numeric string.
;           If error, RDI's value is restored to original value.
;           Caller can check character at [RDI] after a
;           successful result to see if the character following
;           the numeric digits is a legal numeric delimiter.
;
;   C       (carry flag) Set if error occurs, clear if
;           conversion was successful. On error, RAX will
;           contain 0 (illegal initial character) or
;           0ffffffffffffffffh (overflow).

strtoi      proc
negFlag     equ     <byte ptr [rsp]>
            
            push    rdi      ;In case we have to restore RDI
            sub     rsp, 8
            
; Assume we have a non-negative number.

            mov     negFlag, false

            
; The following loop skips over any whitespace (spaces and
; tabs) that appear at the beginning of the string.

            dec     rdi      ;Because of inc below.
skipWS:     inc     rdi
            mov     al, [rdi]
            cmp     al, ' '
            je      skipWS
            cmp     al, tab
            je      skipWS
            
; If the first character we've encountered is '-',
; then skip it, but remember that this is a negative
; number.

            cmp     al, '-'
            jne     notNeg
            mov     negFlag, true
            inc     rdi               ;Skip '-'
            
notNeg:     call    strtou  ;Convert string to integer
            jc      hadError
            
; strtou returned success. Check the negative flag and
; negate the input if the flag contains true.

            cmp     negFlag, true
            jne     itsPosOr0
            
            cmp     rax, tooBig     ;number is too big
            ja      overflow
            neg     rax
itsPosOr0:  add     rsp, 16 ;Success, so don't restore RDI
            clc             ;Return success in carry flag
            ret

; If we have an error, we need to restore RDI from the stack

overflow:   mov     rax, -1 ;Indicate overflow      
hadError:   add     rsp, 8  ;Remove locals
            pop     rdi
            stc             ;Return error in carry flag
            ret 
            
tooBig      qword   7fffffffffffffffh
strtoi      endp
            
                    
            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbp
            mov     rbp, rsp
            sub     rsp, 64         ;Shadow storage
            

; Test unsigned conversions:
            
            lea     rdi, value1
            call    strtou
            jc      UnexpectedError
            
            lea     rcx, fmtStr1
            lea     rdx, value1
            mov     r8, rax
            call    printf
            
 
            lea     rdi, value2
            call    strtou
            jc      UnexpectedError
            
            lea     rcx, fmtStr1
            lea     rdx, value2
            mov     r8, rax
            call    printf
            
 
            lea     rdi, value3
            call    strtou
            jc      UnexpectedError
            
            lea     rcx, fmtStr1
            lea     rdx, value3
            mov     r8, rax
            call    printf
            
 
            lea     rdi, value4
            call    strtou
            jc      UnexpectedError
            
            lea     rcx, fmtStr1
            lea     rdx, value4
            mov     r8, rax
            call    printf
            
 
            lea     rdi, value5
            call    strtou
            jc      UnexpectedError
            
            lea     rcx, fmtStr1
            lea     rdx, value5
            mov     r8, rax
            call    printf
            
 
            lea     rdi, value6
            call    strtou
            jc      UnexpectedError
            
            lea     rcx, fmtStr1
            lea     rdx, value6
            mov     r8, rax
            call    printf
            
 
            lea     rdi, OFvalue
            call    strtou
            jnc     UnexpectedError
            test    rax, rax        ;Non-zero for overflow
            jz      UnexpectedError
            
            lea     rcx, fmtStr2
            lea     rdx, OFvalue
            mov     r8, rax
            call    printf
            
 
            lea     rdi, OFvalue2
            call    strtou
            jnc     UnexpectedError
            test    rax, rax        ;Non-zero for overflow
            jz      UnexpectedError
            
            lea     rcx, fmtStr2
            lea     rdx, OFvalue2
            mov     r8, rax
            call    printf
            
; Test signed conversions:
            
            lea     rdi, ivalue1
            call    strtoi
            jc      UnexpectedError
            
            lea     rcx, fmtStr3
            lea     rdx, ivalue1
            mov     r8, rax
            call    printf
            
 
            lea     rdi, ivalue2
            call    strtoi
            jc      UnexpectedError
            
            lea     rcx, fmtStr3
            lea     rdx, ivalue2
            mov     r8, rax
            call    printf
            
 
            lea     rdi, ivalue3
            call    strtoi
            jc      UnexpectedError
            
            lea     rcx, fmtStr3
            lea     rdx, ivalue3
            mov     r8, rax
            call    printf
            
 
            lea     rdi, ivalue4
            call    strtoi
            jc      UnexpectedError
            
            lea     rcx, fmtStr3
            lea     rdx, ivalue4
            mov     r8, rax
            call    printf
            
 
            lea     rdi, ivalue5
            call    strtoi
            jc      UnexpectedError
            
            lea     rcx, fmtStr3
            lea     rdx, ivalue5
            mov     r8, rax
            call    printf
            
 
            lea     rdi, ivalue6
            call    strtoi
            jc      UnexpectedError
            
            lea     rcx, fmtStr3
            lea     rdx, ivalue6
            mov     r8, rax
            call    printf
            
 
            lea     rdi, OFivalue
            call    strtoi
            jnc     UnexpectedError
            test    rax, rax        ;Non-zero for overflow
            jz      UnexpectedError
            
            lea     rcx, fmtStr2
            lea     rdx, OFivalue
            mov     r8, rax
            call    printf
            
 
            lea     rdi, OFivalue2
            call    strtoi
            jnc     UnexpectedError
            test    rax, rax        ;Non-zero for overflow
            jz      UnexpectedError
            
            lea     rcx, fmtStr2
            lea     rdx, OFivalue2
            mov     r8, rax
            call    printf
            
            jmp     allDone

UnexpectedError:
            lea     rcx, unexError
            call    printf

             
allDone:    leave
            ret     ;Returns to caller
asmMain     endp
            end