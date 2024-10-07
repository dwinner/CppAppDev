
; Listing 18-10
;
; findChar and findLastChar functions

            option     casemap:none
            include    string.inc
            include    aoalib.inc

            includelib aoalib.lib


; Number of times to repeat benchmark loop:

repeatCnt   =       100000

            .const
ttlStr      byte    "Listing 18-10", 0


            .data
startTime   dword   ?


; Generate a whole bunch of strings for
; testing purposes:
;
; string0 is a special case, just the
; empty string (always fails for findChar
; and findLastChar).

            staticStr string0, 1

; The following compile time while loop
; generates data for the strings
; string1..string255. The data this
; while loop creates is
;
; For string1..string6:

;  stringX     byte  <<string of length X>>
;  stringX_1st byte  0
;  stringX_2nd byte  0
;              byte  0
;  stringXname byte  "stringX", 0
;
; For string7..string255:
;
;  stringX     byte  <<string of length X-6>>
;              byte  80h, 81h, 0ffh
;  stringX_1st byte  'ab'
;  stringX_2nd byte  'a'
;              byte  0
;  stringXname byte  "stringX", 0
;
;
; where X = 1..255.
; The <<string of length X>> is a string
; containing X or X-1 characters consisting
; of the byte values 1..X, except for
; 61h ('a').
;
; The name "stringX" marks the beginning
; of the string. The name "stringXa" marks
; the 1st occurrence of 'a' in the string.
; The name "stringXb" marks the last
; occurrence of 'a' in the string.
; The stringXname string is simply a string
; holding the string's name.
;
; The 80h byte appears because some of the
; algorithms might thing that 80h is a zero
; byte; this tests their proper operation.

makeStr     macro   len
            local   theName
theName     catstr  <string>, %len, <name>
theName     byte    "string&len", 0
            endm
            
strLength   =       1
            while   strLength lt 256
            
            
strName     catstr  <string>, %strLength
            strBgn  %strName, 300
            
            byte    strLength dup ('.')
            byte    'ab'
            byte    'a'
            byte    "Some junk At end without lowercAse A"
            
            strEnd  %strName
            

strLength   =       strLength + 1
            endm





            .code
            externdef time:proc

;************************************************************
;
; Macro that generates code to time and test an
; strchr call.
;
; Parameters:
;
;           func:   Name of strchr function to test.
;           ofs:    string length + this is the match posn.
;           posn:   1st for strchr, 2nd for strrchr.
;           txt:    Text describing function.

timeFC      macro   func, ofs, txt
            local   strLp, failed, badOffset
            local   allDone, badResult
                        
            call    print
            byte    "Timing &func:", nl, 0

            xor     rcx, rcx        ;NULL argument to time
            call    time
            mov     startTime, eax  ;Save starting time

            
; Call the string length function over and over again:

            mov     ebx, repeatCnt
strLp:

; Generate 256 calls to the string length function, one
; for each of the 256 strings created earlier (lengths
; 0..255):

lpCnt       =       1
            while   lpCnt lt 256
            local   strSuccess, failed, startLp
strName     catstr  <string>, %lpCnt


; Run a loop for all the starting offset values
; from 0 to lpCnt:

            mov     r15, 0
startLp:
            lea     rsi, strName
            mov     al, 'a'
            mov     rcx, r15
            call    func
            mov     rdx, lpCnt      
            jnz     badResult
            
            mov     rdx, lpCnt+ofs
            cmp     eax, edx       
            jne     badOffset
            
            inc     r15
            cmp     r15, lpCnt
            jb      startLp

            
lpCnt       =       lpCnt + 1
            endm
            
            dec     ebx
            jnz     strLp
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            sub     eax, startTime  
            
            mov     edx, eax
            call    print
            byte    "&txt time = %d seconds", nl, 0

; Outside the timing loop, test for correct operation with
; empty haystack string:

            lea     rsi, string0
            mov     al, 'a'
            xor     ecx, ecx
            call    func
            jnz     allDone
            
failed:     mov     r8, r15
            call    print
            byte    "Expected to fail on length 0, did not; "
            byte    "got offset %d, loop was %d"
            byte    nl, 0
            jmp     allDone

badOffset:  mov     r8, rax
            mov     r9, rcx
            mov     r10, r15
            call    print
            byte    "Expected offset %d, got %d, start was %d, "
            byte    "loop was %d", nl, 0
            jmp     allDone


badResult:  mov     r8, rax
            mov     r9, rcx
            mov     r10, r15
            call    print
            byte    "Bad condition code from function; "
            byte    " offset %d, got %d, start was %d, "
            byte    "loop was %d", nl, 0
            jmp     allDone

            

allDone:
            endm

;************************************************************

            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbx
            push    rsi
            push    rdi
            push    rbp
            push    r14
            push    r15
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage
            
; This program requires SSE 4.2 features to run properly.
; Check for the presence of those features before running.
;
; Leaf function 1 is available on all CPUs that support
; CPUID, no need to test for it.  

            timeFC  findChar1,     0, SSE findChar
            timeFC  findLastChar1, 2, SSE findLastChar


            mov     eax, 1
            cpuid
            and     ecx, SSE42    ;Test bits 19 & 20
            cmp     ecx, SSE42    ;Both must be set
            je      doFC2
            call    print
            byte    "CPU does not support SSE 4.2/3", nl
            byte    "Skipping findChar2/findLastChar2", nl,0
            jmp     allDone             

; Running timing tests on each of the various strchr and
; strrchr functions:

doFC2:
            timeFC  findChar2,     0, pcmpistri findChar
            timeFC  findLastChar2, 2, pcmpistri findLastChar
            
allDone:    leave
            pop     r15
            pop     r14
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end









                       