; Listing 7-4
;
; Demonstration of register indirect jumps

        option  casemap:none

nl          =       10
maxLen      =       256
EINVAL      =       22      ;"Magic" C stdlib constant, invalid argument
ERANGE      =       34      ;Value out of range


            .const
ttlStr      byte    "Listing 7-4", 0
fmtStr1     byte    "Enter an integer value between "
            byte    "1 and 10 (0 to quit): ", 0
            
badInpStr   byte    "There was an error in readLine "
            byte    "(ctrl-Z pressed?)", nl, 0
            
invalidStr  byte    "The input string was not a proper number"
            byte    nl, 0
            
rangeStr    byte    "The input value was outside the "
            byte    "range 1-10", nl, 0
            
unknownStr  byte    "The was a problem with strToInt "
            byte    "(unknown error)", nl, 0
            
goodStr     byte    "The input value was %d", nl, 0

fmtStr      byte    "result:%d, errno:%d", nl, 0

            .data
            externdef _errno:dword  ;Error return by C code
endStr      qword   ?
inputValue  dword   ?
buffer      byte    maxLen dup (?)
        
            .code
            externdef readLine:proc
            externdef strtol:proc
            externdef printf:proc
            
; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp


; strToInt-
;
;  Converts a string to an integer, checking for errors.
;
; Argument:
;    RCX-   Pointer to string containing (only) decimal 
;           digits to convert to an integer.
;
; Returns:
;    RAX-   Integer value if conversion was successful.
;    RCX-   Conversion state. One of the following:
;           0- Conversion successful
;           1- Illegal characters at the beginning of the 
;                   string (or empty string).
;           2- Illegal characters at the end of the string
;           3- Value too large for 32-bit signed integer.

 
strToInt    proc
strToConv   equ     [rbp+16]        ;Flush RCX here
endPtr      equ     [rbp-8]         ;Save ptr to end of str.
            push    rbp
            mov     rbp, rsp
            sub     rsp, 32h        ;Shadow + 16-byte alignment
            
            mov     strToConv, rcx  ;Save, so we can test later.
            
            ;RCX already contains string parameter for strtol
            
            lea     rdx, endPtr     ;Ptr to end of string goes here.
            mov     r8d, 10         ;Decimal conversion
            call    strtol
            
; On return:
;
;    RAX-   Contains converted value, if successful.
;    endPtr-Pointer to 1 position beyond last char in string.
;
; If strtol returns with endPtr == strToConv, then there were no
; legal digits at the beginning of the string.

            mov     ecx, 1          ;Assume bad conversion
            mov     rdx, endPtr
            cmp     rdx, strToConv
            je      returnValue
            
; If endPtr is not pointing at a zero byte, then we've got
; junk at the end of the string.

            mov     ecx, 2          ;Assume junk at end
            mov     rdx, endPtr
            cmp     byte ptr [rdx], 0
            jne     returnValue
            
; If the return result is 7fff_ffffh or 8000_0000h (max long and
; min long, respectively), and the C global _errno variable 
; contains ERANGE, then we've got a range error.

            mov     ecx, 0          ;Assume good input
            cmp     _errno, ERANGE
            jne     returnValue
            mov     ecx, 3          ;Assume out of range
            cmp     eax, 7fffffffh
            je      returnValue
            cmp     eax, 80000000h
            je      returnValue
            
; If we get to this point, it's a good number

            mov     ecx, 0
            
returnValue:
            leave
            ret
strToInt    endp
            
            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
saveRBX     equ     qword ptr [rbp-8]       ;Must preserve RBX
            push    rbp
            mov     rbp, rsp
            sub     rsp, 48                 ;Shadow storage
            
            mov     saveRBX, rbx            ;Must preserve RBX

            
            ; Prompt the user to enter a value
            ; between 1 and 10:
            
repeatPgm:  lea     rcx, fmtStr1
            call    printf
            
            ; Get user input:
            
            lea     rcx, buffer
            mov     edx, maxLen     ;Zero extends!
            call    readLine
            lea     rbx, badInput   ;Initialize state machine
            test    rax, rax        ;RAX is -1 on bad input
            js      hadError        ;(only neg value readLine returns)
            
            ;Call strtoint to convert string to an integer and
            ;check for errors:
            
            lea     rcx, buffer     ;Ptr to string to convert
            call    strToInt
            lea     rbx, invalid
            cmp     ecx, 1
            je      hadError
            cmp     ecx, 2
            je      hadError
            
            lea     rbx, range
            cmp     ecx, 3
            je      hadError
            
            lea     rbx, unknown
            cmp     ecx, 0
            jne     hadError
            
            
; At this point, input is valid and is sitting in EAX.
;
; First, check to see if the user entered 0 (to quit
; the program).

            test    eax, eax        ;Test for zero
            je      allDone
            
; However, we need to verify that the number is in the
; range 1-10. 

            lea     rbx, range
            cmp     eax, 1
            jl      hadError
            cmp     eax, 10
            jg      hadError
            
; Pretend a bunch of work happens here dealing with the
; input number.

            lea     rbx, goodInput
            mov     inputValue, eax

; The different code streams all merge together here to
; execute some common code (we'll pretend that happens,
; for brevity, no such code exists here).

hadError:

; At the end of the common code (which doesn't mess with
; RBX), separate into five different code streams based
; on the pointer value in RBX:

            jmp     rbx
            
; Transfer here if readLine returned an error:

badInput:   lea     rcx, badInpStr
            call    printf
            jmp     repeatPgm
            
; Transfer here if there was a non-digit character:
; in the string:
 
invalid:    lea     rcx, invalidStr
            call    printf
            jmp     repeatPgm

; Transfer here if the input value was out of range:
                    
range:      lea     rcx, rangeStr
            call    printf
            jmp     repeatPgm

; Shouldn't ever get here. Happens if strToInt returns
; a value outside the range 0-3.
            
unknown:    lea     rcx, unknownStr
            call    printf
            jmp     repeatPgm

; Transfer down here on a good user input.
            
goodInput:  lea     rcx, goodStr
            mov     edx, inputValue ;Zero extends!
            call    printf
            jmp     repeatPgm

; Branch here when the user selects "quit program" by
; entering the value zero:

allDone:    mov     rbx, saveRBX ;Must restore before returning
            leave
            ret     ;Returns to caller
        
asmMain     endp
            end