; build listing9-7
;
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
fmtStr6     byte    "itoStr(7FF...FFFF): string=%s", nl, 0
fmtStr7     byte    "itoStr(800...0000): string=%s", nl, 0
fmtStr8     byte    "usize(1234567890): length=%d",  nl, 0
fmtStr9     byte    "isize(-1234567890): length=%d", nl, 0
fmtStr10    byte    "utoStrSize(1234567890): string=%s",  nl, 0
fmtStr11    byte    "itoStrSize(-1234567890): string=%s",  nl, 0
            
            .data
buffer      byte    40 dup (?)

b0          oword   0
b1          oword   1234567890
b2          oword   2147483648
b3          oword   4294967296

; Largest oword value
; (decimal=340,282,366,920,938,463,463,374,607,431,768,211,455):
    
b4          oword   0FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFh
b5          oword   07FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFh
b6          oword   080000000000000000000000000000000h
b7          oword   -1234567890
            
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

            xor     rdx, rdx
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
;    Stack contains oword parameter
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
            pop     rax
            ret
    
otostr      endp



; i128toStr-
;   Converts a 128-bit signed integer to a string
;
; Inputs;
;    RDX:RAX- signed integer to convert
;    RDI-     pointer to buffer to receive string

i128toStr   proc
            push    rax
            push    rdx
            push    rdi
            
            test    rdx, rdx  ;Is number negative?
            jns     notNeg
            
            mov     byte ptr [rdi], '-'
            inc     rdi
            neg     rdx     ;128-bit negation
            neg     rax
            sbb     rdx, 0
            
notNeg:     call    otostr
            pop     rdi
            pop     rdx
            pop     rax
            ret
i128toStr   endp



; uSize-
;  Determines how many character positions it will take
; to hold a 64-bit numeric-to-string conversion.
;
; Input
;   RAX-    Number to check
;
; Returns-
;   RAX-    Number of character positions required.

dig2        qword   10
dig3        qword   100
dig4        qword   1000
dig5        qword   10000
dig6        qword   100000
dig7        qword   1000000
dig8        qword   10000000
dig9        qword   100000000
dig10       qword   1000000000
dig11       qword   10000000000
dig12       qword   100000000000
dig13       qword   1000000000000
dig14       qword   10000000000000
dig15       qword   100000000000000
dig16       qword   1000000000000000
dig17       qword   10000000000000000
dig18       qword   100000000000000000
dig19       qword   1000000000000000000
dig20       qword   10000000000000000000

uSize       proc
            push    rdx
            cmp     rax, dig10
            jae     ge10
            cmp     rax, dig5
            jae     ge5
            mov     edx, 4
            cmp     rax, dig4
            jae     allDone
            dec     edx
            cmp     rax, dig3
            jae     allDone
            dec     edx
            cmp     rax, dig2
            jae     allDone
            dec     edx
            jmp     allDone
            
ge5:        mov     edx, 9
            cmp     rax, dig9
            jae     allDone
            dec     edx
            cmp     rax, dig8
            jae     allDone
            dec     edx
            cmp     rax, dig7
            jae     allDone
            dec     edx
            cmp     rax, dig6
            jae     allDone
            dec     edx     ;Must be 5
            jmp     allDone
            
            
ge10:       cmp     rax, dig14
            jae     ge14
            mov     edx, 13
            cmp     rax, dig13
            jae     allDone
            dec     edx
            cmp     rax, dig12
            jae     allDone
            dec     edx
            cmp     rax, dig11
            jae     allDone
            dec     edx     ;Must be 10
            jmp     allDone
            
ge14:       mov     edx, 20
            cmp     rax, dig20
            jae     allDone
            dec     edx
            cmp     rax, dig19
            jae     allDone
            dec     edx
            cmp     rax, dig18
            jae     allDone
            dec     edx
            cmp     rax, dig17
            jae     allDone
            dec     edx
            cmp     rax, dig16
            jae     allDone
            dec     edx
            cmp     rax, dig15
            jae     allDone
            dec     edx     ;Must be 14             


allDone:    mov     rax, rdx        ;Return digit count
            pop     rdx
            ret
uSize       endp

; iSize-
;  Determines the number of print positions required by
; a 64-bit signed integer.

iSize       proc
            test    rax, rax
            js      isNeg

            jmp     uSize   ; Effectively a call and ret

; If the number is negative, negate it, call uSize,
; and then bump the size up by 1 (for the '-' character)
            
isNeg:      neg     rax
            call    uSize
            inc     rax
            ret
iSize       endp



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
; string could be as long as 21 bytes
; (including the zero-terminating byte).

bigNum      qword   1000000000000000000
utoStr      proc
            push    rcx
            push    rdx
            push    rdi
            push    rax
            push    rax
            sub     rsp, 16

; Quick test for zero to handle that special case:

            test    rax, rax
            jnz     not0
            mov     byte ptr [rdi], '0'
            inc     rdi
            jmp     allDone

; The FBSTP instruction only supports 18 digits.
; 64-bit integers can have up to 19 digits.
; Handle that 19th possible digit here:
            
not0:       cmp     rax, bigNum
            jb      lt19Digits

; The number has 19 digits (which can be 0-9).
; pull off the 19th digit:

            xor     edx, edx
            div     bigNum          ;19th digit in AL
            mov     [rsp+16], rdx   ;Remainder
            or      al, '0'
            mov     [rdi], al
            inc     rdi
            
; The number to convert is non-zero.
; Use BCD load and store to convert
; the integer to BCD:

lt19Digits: fild    qword ptr [rsp+16]
            fbstp   tbyte ptr [rsp]
            
            
; Begin by skipping over leading zeros in
; the BCD value (max 19 digits, so the most
; significant digit will be in the LO nibble
; of DH).

            mov     dx, [rsp+8]
            mov     rax, [rsp]
            mov     ecx, 20
            jmp     testFor0
            
Skip0s:     shld    rdx, rax, 4
            shl     rax, 4
testFor0:   dec     ecx         ;Count digits we've processed
            test    dh, 0fh     ;Because the number is not 0
            jz      Skip0s      ;this always terminates
            
; At this point the code has encountered
; the first non-0 digit. Convert the remaining
; digits to a string:

cnvrtStr:   and     dh, 0fh
            or      dh, '0'
            mov     [rdi], dh
            inc     rdi
            mov     dh, 0
            shld    rdx, rax, 4
            shl     rax, 4
            dec     ecx
            jnz     cnvrtStr

; Zero-terminate the string and return:
            
allDone:    mov     byte ptr [rdi], 0
            add     rsp, 16+8   ; We had an extra pop to use as a local
            pop     rax
            pop     rdi
            pop     rdx
            pop     rcx
            ret
utoStr      endp

; itoStr - Signed integer to string conversion
;
; Inputs:
;   RAX -   Signed integer to convert
;   RDI -   Destination buffer address

itoStr      proc
            push    rdi
            push    rax
            test    rax, rax
            jns     notNeg
            
; Number was negative, emit '-' and negate
; value.

            mov     byte ptr [rdi], '-'
            inc     rdi
            neg     rax
            
; Call utoStr to convert non-negative number:

notNeg:     call    utoStr
            pop     rax
            pop     rdi
            ret
itoStr      endp



; utoStrSize-
;   Converts an unsigned integer to a formatted string
; having at least "minDigits" character positions.
; If the actual number of digits is smaller than
; "minDigits" then this procedure inserts enough
; "pad" characters to extend the size of the string.
;
; Inputs:
;   RAX -   Number to convert to string
;   CL-     minDigits (minimum print positions)
;   CH-     Padding character
;   RDI -   Buffer pointer for output string

utoStrSize  proc
            push    rcx
            push    rdi
            push    rax
            
            call    uSize   ;Get actual number of digits
            sub     cl, al  ;>= the minimum size?
            jbe     justConvert
            
; If the minimum size is greater than the number of actual
; digits, we need to emit padding characters here.
;
; Note that this code used "sub" rather than "cmp" above.
; As a result, CL now contains the number of padding
; characters to emit to the string (CL is always positive
; at this point, as negative and zero results would have
; branched to justConvert).

padLoop:    mov     [rdi], ch
            inc     rdi
            dec     cl
            jne     padLoop

; Okay, any necessary padding characters have already been
; added to the string. Call utostr to convert the number
; to a string and append to the buffer:

justConvert:
            mov     rax, [rsp]      ;Retrieve original value
            call    utoStr

abort:            
            pop     rax
            pop     rdi
            pop     rcx
            ret
utoStrSize  endp    

; itoStrSize-
;   Converts a signed integer to a formatted string
; having at least "minDigits" character positions.
; If the actual number of digits is smaller than
; "minDigits" then this procedure inserts enough
; "pad" characters to extend the size of the string.
;
; Inputs:
;   RAX -   Number to convert to string
;   CL-     minDigits (minimum print positions)
;   CH-     Padding character
;   RDI -   Buffer pointer for output string

itoStrSize  proc
            push    rcx
            push    rdi
            push    rax
            
            call    iSize   ;Get actual number of digits
            sub     cl, al  ;>= the minimum size?
            jbe     justConvert
            
; If the minimum size is greater than the number of actual
; digits, we need to emit padding characters here.
;
; Note that this code used "sub" rather than "cmp" above.
; As a result, CL now contains the number of padding
; characters to emit to the string (CL is always positive
; at this point, as negative and zero results would have
; branched to justConvert).

padLoop:    mov     [rdi], ch
            inc     rdi
            dec     cl
            jne     padLoop

; Okay, any necessary padding characters have already been
; added to the string. Call utostr to convert the number
; to a string and append to the buffer:

justConvert:
            mov     rax, [rsp]      ;Retrieve original value
            call    itoStr
            
            pop     rax
            pop     rdi
            pop     rcx
            ret
itoStrSize  endp


           
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rdi
            push    rbp
            mov     rbp, rsp
            sub     rsp, 64         ;Shadow storage
            and     rsp, -16
            
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
            
            mov     rax, qword ptr b5
            mov     rdx, qword ptr b5[8]
            call    i128toStr

            lea     rcx, fmtStr6
            lea     rdx, buffer
            call    printf
            
            mov     rax, qword ptr b6
            mov     rdx, qword ptr b6[8]
            call    i128toStr

            lea     rcx, fmtStr7
            lea     rdx, buffer
            call    printf
            
            mov     rax, qword ptr b1
            call    uSize

            lea     rcx, fmtStr8
            mov     rdx, rax
            call    printf
            
            mov     rax, qword ptr b7
            call    iSize

            lea     rcx, fmtStr9
            mov     rdx, rax
            call    printf

            mov     rax, qword ptr b1
            mov     cl, 13
            mov     ch, '.'
            lea     rdi, buffer
            call    utoStrSize

            lea     rcx, fmtStr10
            lea     rdx, buffer
            call    printf
            
            mov     rax, qword ptr b7
            mov     cl, 12
            mov     ch, '.'
            lea     rdi, buffer
            call    itoStrSize

            lea     rcx, fmtStr11
            lea     rdx, buffer
            call    printf
            
            mov     rax, qword ptr b7
            mov     cl, 11
            mov     ch, '.'
            lea     rdi, buffer
            call    itoStrSize

            lea     rcx, fmtStr11
            lea     rdx, buffer
            call    printf
            
            
            mov     rax, dig20
            call    uSize
            
            lea     rcx, fmtStr8
            mov     rdx, rax
            call    printf
            
            
            leave
            pop     rdi
            ret     ;Returns to caller
        
asmMain     endp
            end
