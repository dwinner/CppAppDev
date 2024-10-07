; Listing 17-1
;
; String Length Functions

            include    zstrings.inc
            include    aoalib.inc
            includelib aoalib.lib        

            .const
ttlStr      byte    "Listing 17-1", 0

            .data
            align   16
xmm         oword   0
            
startTime   dword   ? ;Used to time various strlen functions
hasSSE42    byte    0 ;True if CPU supports SSE4.2 instrs
hasAVX2     byte    0 ;True if CPU supports AVX2 instrs


; Generate a whole bunch of strings for
; testing purposes.
;
; The following compile-time code generates
; 256 strings, taking the form:
;
;  stringX  byte    <<data for string>>
;  lengthX  =       <<length of string>>
;
; Special cases:
;
; string0 and length0 are handled separately.
;
; string1..string6 are strings whose character
; data consists of the bytes 1, 2, ... , length
;
; string7..string255 are strings whose character
; data is 1..(length-5),7eh,7fh,80h,0feh,0ffh,01h
; (which tests some special cases on these 
; strings).

string0     byte    0
length0     =       0

strLength   =       1
            while   strLength lt 256
strName     catstr  <string>, %strLength

; For all strings whose length is greater
; than 1, emit the first byte of the
; string here:

strName     byte    1


; Special cases for strings whose length
; is less than or equal to 6 and strings
; whose length is greater than 6:

            if      strLength gt 6

; For strings whose length is greater than
; size, output strLength-6 bytes in the
; loop because this code manually emits
; 6 (special valued) bytes after the loop.
            
cntBytes    =       7
            while   cntBytes lt strLength
            byte    cntBytes-6
cntBytes    =       cntBytes + 1
            endm
            
; Six special bytes (for strings whose length
; is greater than 6) to test special values
; that certain algorithms might have problems
; with.

            byte    7eh,7fh,80h,0feh,0ffh,01h
            
            else

; Special case for strings whose length is
; less than 6: no special bytes at the end
; of the string.
            
cntBytes    =       2
            while   cntBytes le strLength
            byte    cntBytes
cntBytes    =       cntBytes + 1
            endm
            endif
 
; Zero-terminating byte at the end of the
; string.
           
            byte    0
            
; Generate a special equate holding the
; length of this string, so the strlen
; functions can test the length.

strLenName  catstr  <length>, %strLength
strLenName  =       strLength
strLength   =       strLength + 1
            endm

                     
            .code


;***************************************************************
;            
; testLen-
;
;  Macro that generates code to test a strlen function.
;
; Arguments:
;
;           func-   Name of function to test.
;           srcReg- Register that passes address
;                   of string to strlen function.
;           txt-    Text description of strlen version.
;
; Assumes function result comes back in EAX.


testLen     macro   func, srcReg, txt
            local   strLenLp
            
            call    print
            byte    "Timing &func", nl, 0
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            mov     startTime, eax  ;Save starting time
            
; Call the string length function over and over again:

            mov     ebx, 5000000
strLenLp:   
            
; Generate 256 calls to the string length function, one
; for each of the 256 strings created earlier (lengths
; 0..255):

lpCnt       =       0
            while   lpCnt lt 256
            local   goodLength
            
strName     catstr  <string>, %lpCnt
lenName     catstr  <length>, %lpCnt
            lea     srcReg, strName
            call    func             ;Call strlen function.
            cmp     eax, lenName
            je      goodLength
            
            mov     rdx, lpCnt
            mov     r8, rax
            mov     r9, lenName
            call    print
            byte    "Length failure on string%d: "
            byte    "got %d, expected %d", nl, 0
goodLength: 
            
lpCnt       =       lpCnt + 1
            endm
            
            dec     ebx
            jnz     strLenLp
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            sub     eax, startTime  
            
            mov     edx, eax
            call    print
            byte    "&txt strlen time = %d seconds", nl, 0

            endm
            


            
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

; This program requires AVX features to run properly.
; Check for the presence of those features before running.
;
; Leaf function 1 is available on all CPUs that support
; CPUID, no need to test for it.  

            mov     eax, 1
            cpuid
            and     ecx, SSE42      ;Test bits 19 & 20
            cmp     ecx, SSE42      ;Both must be set
            sete    hasSSE42

            
; Check for AVX2 instructions:

            mov     eax, 7
            xor     ecx, ecx
            cpuid

            and     ebx, AVX2Support        ;Test bit 5
            cmp     ebx, AVX2Support
            sete    hasAVX2

; Time the strlen1 function (naive version):
           
            testLen strlen1, rsi, naive 
            testLen strlen2, rsi, scasb 
            testLen strlen3, rsi, AMD optimized 
            testLen strlen4, rsi, 64-bit optimized 
            testLen strlen5, rsi, GLIBC
            cmp     hasSSE42, 1
            je      doPCMP
            
            call    print
            byte    "CPU does not support SSE42 "
            byte    "instructions, skipping strlen6"
            byte    nl, 0
            jmp     noSSE42
            

doPCMP:     testLen strlen6, rsi, pcmpistri 
noSSE42:    testLen strlen7, rsi, SSE
            cmp     hasAVX2, 1
            je      doSL8
            
            call    print
            byte    "CPU does not support AVX2 "
            byte    "instructions, skipping strlen8"
            byte    nl, 0
            jmp     noAVX2
            
doSL8:      testLen strlen8, rsi, AVX2
            
noAVX2:     testLen strlen, rcx, C Stdlib
            jmp     allDone
            
Unsupported:
            call    print
            byte    "CPU does not support SSE4.2 "
            byte    "instructions", nl, 0
             
             


allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
