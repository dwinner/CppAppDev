; Listing 9-9
;
; Formatted string output:
 
        option  casemap:none

tab	=	9
nl          =       10

            .const
ttlStr      byte    "Listing 9-9", 0
fmtStr1     byte    "fmtOut: value=%19I64d, string='%s'"
            byte    nl, 0
	
            
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

bigNum      qword   1000000000000000000
utoStr      proc
            push    rcx
            push    rdx
            push    rdi
            push    rax
            sub     rsp, 10

; Quick test for zero to handle that special case:

            test    rax, rax
            jnz     not0
            mov     byte ptr [rdi], '0'
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
            mov     [rsp+10], rdx   ;Remainder
            or      al, '0'
            mov     [rdi], al
            inc     rdi
            
            

; The number to convert is non-zero.
; Use BCD load and store to convert
; the integer to BCD:

lt19Digits: fild    qword ptr [rsp+10]
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

; Zero-terminte the string and return:
            
allDone:    mov     byte ptr [rdi], 0
            add     rsp, 10
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


; uSize-
;  Determines how many character positions it will take
; to hold a 64-bit numeric-to-string conversion.
; VERY brute-force algorithm. Just compares the value
; in RAX against 18 powers of 10 to determine if there
; are 1-19 digits in the number. 
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
            
ge14:       mov     edx, 19
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


; utoStrSize-
;   Converts an unsigned integer to a formatted string
; having at least "minDigits" character positions.
; If the actual number of digits is smaller than
; "minDigits" then this procedure inserts encough
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
            
            pop     rax
            pop     rdi
            pop     rcx
            ret
utoStrSize  endp    

; itoStrSize-
;   Converts a signed integer to a formatted string
; having at least "minDigits" character positions.
; If the actual number of digits is smaller than
; "minDigits" then this procedure inserts encough
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
            push    rbp
            mov     rbp, rsp
            sub     rsp, 64         ;Shadow storage
            
; Because the functions all preserve RDI, we only need
; to do this once:

	lea	rdi, buffer
	
	mov	rax, 1
	mov	cl, 19
	mov	ch, '0'
	call	utoStrSize
	
	lea	rcx, fmtStr1
	mov	rdx, 1
	lea	r8, buffer
	call	printf
	
	mov	rax, 12
	mov	cl, 19
	mov	ch, '.'
	call	utoStrSize
	
	lea	rcx, fmtStr1
	mov	rdx, 12
	lea	r8, buffer
	call	printf
	
	mov	rax, 123
	mov	cl, 19
	mov	ch, '+'
	call	utoStrSize
	
	lea	rcx, fmtStr1
	mov	rdx, 123
	lea	r8, buffer
	call	printf
	
	mov	rax, 1234
	mov	cl, 19
	mov	ch, '*'
	call	utoStrSize
	
	lea	rcx, fmtStr1
	mov	rdx, 1234
	lea	r8, buffer
	call	printf
	
	mov	rax, 12345
	mov	cl, 19
	mov	ch, '$'
	call	utoStrSize
	
	lea	rcx, fmtStr1
	mov	rdx, 12345
	lea	r8, buffer
	call	printf
	
	mov	rax, 123456
	mov	cl, 19
	mov	ch, '_'
	call	utoStrSize
	
	lea	rcx, fmtStr1
	mov	rdx, 123456
	lea	r8, buffer
	call	printf
	
	mov	rax, 1234567
	mov	cl, 19
	mov	ch, '-'
	call	utoStrSize
	
	lea	rcx, fmtStr1
	mov	rdx, 1234567
	lea	r8, buffer
	call	printf
	
	mov	rax, 12345678
	mov	cl, 19
	mov	ch, '@'
	call	utoStrSize
	
	lea	rcx, fmtStr1
	mov	rdx, 12345678
	lea	r8, buffer
	call	printf
	
	mov	rax, 123456789
	mov	cl, 19
	mov	ch, ' '
	call	utoStrSize
	
	lea	rcx, fmtStr1
	mov	rdx, 123456789
	lea	r8, buffer
	call	printf
	
	mov	rax, 1234567890
	mov	cl, 19
	mov	ch, ' '
	call	utoStrSize
	
	lea	rcx, fmtStr1
	mov	rdx, 1234567890
	lea	r8, buffer
	call	printf
	
	mov	rax, 12345678901
	mov	cl, 19
	mov	ch, ' '
	call	utoStrSize
	
	lea	rcx, fmtStr1
	mov	rdx, 12345678901
	lea	r8, buffer
	call	printf
	
	mov	rax, 123456789012
	mov	cl, 19
	mov	ch, ' '
	call	utoStrSize
	
	lea	rcx, fmtStr1
	mov	rdx, 123456789012
	lea	r8, buffer
	call	printf
	
	mov	rax, 1234567890123
	mov	cl, 19
	mov	ch, ' '
	call	utoStrSize
	
	lea	rcx, fmtStr1
	mov	rdx, 1234567890123
	lea	r8, buffer
	call	printf
	
	mov	rax, 12345678901234
	mov	cl, 19
	mov	ch, ' '
	call	utoStrSize
	
	lea	rcx, fmtStr1
	mov	rdx, 12345678901234
	lea	r8, buffer
	call	printf
	
	mov	rax, 123456789012345
	mov	cl, 19
	mov	ch, ' '
	call	utoStrSize
	
	lea	rcx, fmtStr1
	mov	rdx, 123456789012345
	lea	r8, buffer
	call	printf
	
	mov	rax, 1234567890123456
	mov	cl, 19
	mov	ch, ' '
	call	utoStrSize
	
	lea	rcx, fmtStr1
	mov	rdx, 1234567890123456
	lea	r8, buffer
	call	printf
	
	mov	rax, 12345678901234567
	mov	cl, 19
	mov	ch, ' '
	call	utoStrSize
	
	lea	rcx, fmtStr1
	mov	rdx, 12345678901234567
	lea	r8, buffer
	call	printf
	
	mov	rax, 123456789012345678
	mov	cl, 19
	mov	ch, ' '
	call	utoStrSize
	
	lea	rcx, fmtStr1
	mov	rdx, 123456789012345678
	lea	r8, buffer
	call	printf
	
	mov	rax, 1234567890123456789
	mov	cl, 19
	mov	ch, ' '
	call	utoStrSize
	
	lea	rcx, fmtStr1
	mov	rdx, 1234567890123456789
	lea	r8, buffer
	call	printf
             
allDone:    leave
            ret     ;Returns to caller
asmMain     endp
            end