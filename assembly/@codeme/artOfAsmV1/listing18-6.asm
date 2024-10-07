; Listing 18-6
;
; Substring functions.

            option     casemap:none
            include    string.inc
            include    aoalib.inc

            includelib aoalib.lib
            


; doBenchmark is true if the app benchmarks
; and tests the code; it is false for
; test only (no benchmark).

doBenchmark =       1
maxSubstrs  =	256

            .const
ttlStr      byte    "Listing 18-6", 0

            .data
startTime   dword   ?
            
                    
; Declare a string to hold the substring result:

            staticStr subDest, 300
            
; Generate a string with 255 characters
; (ASCII codes 1..255) to use as a
; test string:

            strBgn  source1, 300
chrIndex    =       1
            while   chrIndex lt maxSubstrs
            byte    chrIndex
chrIndex    =       chrIndex + 1
            endm
            strEnd  source1
           
; Generate a set of strings that will hold the
; expected results for each of the substring
; operations. Assuming maxSubstrs = 256, 
; this generates the strings:
;
;   sub_<start index>_<length>
;
; I.e.,
;
;   sub_0_1    = 01h
;   sub_0_2    = 01h 02h
;    .
;    .
;    .
;   sub_0_255  = 01h 02h 03h ... 0FFh
;
;   sub_1_1    = 02h
;   sub_1_2    = 02h 03h
;    .
;    .
;    .
;   sub_1_254  = 02h 03h ... 0FFh
;
; WARNING: Because of the massive number of
; variable declarations this creates, this
; file takes a long time to assemble
; by MASM (remember the DUP bug).
;
; Note that the following compile-time loops
; only generate the strings to hold the values.
; The initial string values are actually created
; byte the program at run-time because generating
; this many different values at compile time is
; just too slow.

startNdx    =       0
            while   startNdx lt maxSubstrs
len         =       1
            while   len lt (maxSubstrs-startNdx)
strName     catstr  <sub_>, %startNdx, <_>, %len
            
            staticStr %strName, len+8
            
len         =       len + 1
            endm
startNdx    =       startNdx + 1
            endm
 
            
            .code
            externdef time:proc 
 
;**********************************************************
;
; testSS-
;
;  Macro to test the various substring functions
;
; Arguments:
;
;  func     strcpy function to call
;  txt      Text description of function
;
;  Executes specified strcpy function approximately
; 100,000 * 33,000 times so we can time its operation.
;

testSS      macro   func, txt
            local   substrLp, allDone, badCmp, strOvfl 

            if      doBenchmark
            
            call    print
            byte    "Timing &func", nl, 0
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            mov     startTime, eax  ;Save starting time

; Call the string copy function over and over again:

            mov     ebx, 100000
substrLp:

; Generate maxSubstrs calls to the string length function, one
; for each of the maxSubstrs strings created earlier (lengths
; 0..maxSubstrs):

startNdx    =       0
            while   startNdx lt maxSubstrs

len         =       1
            while   len lt (maxSubstrs-startNdx)

            lea     rsi, source1
            mov     rax, startNdx
            mov     rcx, len
            lea     rdi, subDest
            call    func        
            jc      strOvfl
len         =       len + 1
            endm
startNdx    =       startNdx + 1
            endm
            
            dec     ebx
            jnz     substrLp
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            sub     eax, startTime  
            
            mov     edx, eax
            call    print
            byte    "&txt substring time = %d seconds", nl, 0
            
            endif   ;doBenchmark
            
; Repeat the above, but compare the resulting substrings
; to verify that the code produced proper substrings:

startNdx    =       0
            while   startNdx lt maxSubstrs

len         =       1
            while   len lt (maxSubstrs-startNdx)
cmpName     catstr  <sub_>, %startNdx, <_>, %len

            lea     rsi, source1    ;Substr source
            mov     rax, startNdx
            mov     rcx, len
            lea     rdi, subDest
            call    func        

            mov     edx, startNdx
            mov     r8d, len
            
            lea     rsi, subDest
            lea     rdi, cmpName
            call    stringCmp1
            jne     badCmp          


len         =       len + 1
            endm
startNdx    =       startNdx + 1
            endm
            
            
            jmp     allDone
            
badCmp:     call    print
            byte    "subDest: ", 0
            lea     rsi, subDest
            call    printString
            
            ; Note: edx and r8d from loop above
            
            call    print
            byte    "did not match  sub_%d_%d: ", 0
            mov     rsi, rdi
            call    printString
            call    print
            byte    nl, 0
            jmp     allDone
            
strOvfl:    call    print
            byte    "String overflow on %s", nl, 0

allDone:
            endm


;**********************************************************
;
; Here is the "asmMain" function.
        
            public  asmMain
asmMain     proc
            push    rbx
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage
            
            
            
; Before running any test code, initialize the result
; strings (sub_x_y) with appropriate values for
; testing the results, after benchmarking the code.

            call    print
            byte    "Initializing result test substrings"
            byte    nl, 0
            
startNdx    =       0
            while   startNdx lt maxSubstrs

len         =       1
            while   len lt (maxSubstrs-startNdx)
            local   fillLp
resultName  catstr  <sub_>, %startNdx, <_>, %len

            lea     rsi, resultName
            mov     [rsi-sohs].strObject.strLength, len
            
            xor     rcx, rcx
            mov     rbx, startNdx+1
            mov     byte ptr [rsi][rcx*1], 0
fillLp:     mov     [rsi][rcx*1], bl
            inc     rbx
            inc     rcx
            cmp     rcx, len
            jb      fillLp
            
len         =       len + 1
            endm
startNdx    =       startNdx + 1
            endm
            
            call    print
            byte    "Initialization complete", nl, 0
            
; This program requires SSE4.2 features to run properly.

; Benchmark and test the results of the
; substring operations down here:

            
            testSS  substring1, movsb
            testSS  substring2, SSE

                         
allDone:    leave
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
