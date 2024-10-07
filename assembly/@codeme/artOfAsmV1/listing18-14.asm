; Listing 18-14
;
; stringDelete Function

            option     casemap:none
            include    string.inc
            include    aoalib.inc

            includelib aoalib.lib

; Maximum length of source string expansion
; (Controls timing loop iterations, too).

maxLen      =       256

; Number of repetitions of the timing loop:

repeatCnt   =       50000


            .const
ttlStr      byte    "Listing 18-14", 0


            .data
startTime   qword   ?
endTime     qword   ?
frequency   qword   ?


            

; Generate a whole bunch of strings for
; testing purposes:            

            
; Macro to generate a sequence of characters:

genChrs     macro   count
            if      count gt 0
            byte    count dup ('.')
            endif
            endm
            
; Generate some test strings. To keep assembly times
; manageable, this generates 3 strings for each string
; length
;
; 1) With text to delete at position 0.
; 2) With text to delete at the middle of the string.
; 3) With text to delete at the end of the string.
;
; E.g.,
;
; testStr3_begin is   "ABCDEFGHIJKLMNOPQRSTUVWXYZ..."
; testStr3_middle is "..ABCDEFGHIJKLMNOPQRSTUVWXYZ."
; testStr3_end is     "...ABCDEFGHIJKLMNOPQRSTUVWXYZ"
;
; The following loop also generates the corresponding
; result string, to test the deletion against.

strLength   =       0
            while   strLength lt maxLen
            local   theString

; This program uses the following strings to verify
; that the stringDelete function operates properly:
            
theString   catstr  <testStr>, %strLength, <_>, <begin>
%           strBgn  theString, strLength+32
            byte    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
%           genChrs strLength
%           strEnd  theString
            
; With insertion in the middle of the string:

theString   catstr  <testStr>, %strLength, <_>, <middle>
%           strBgn  theString, strLength+32
%           genChrs (strLength+1)/2
            byte    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
%           genChrs strLength/2
%           strEnd  theString
            
; With insertion at the end of the string:

theString   catstr  <testStr>, %strLength, <_>, <end>
%           strBgn  theString, strLength+32
%           genChrs strLength
            byte    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
%           strEnd  theString

; Generate the corresponding result strings. Note that
; the result string is the same for the begin, middle,
; and end strings, above.

theString   catstr  <result>, %strLength
%           strBgn  theString, strLength+32
%           genChrs strLength
%           strEnd  theString



; This program uses the following strings to time
; the operation of the stringDelete function:       
            
theString   catstr  <timeStr>, %strLength, <_>, <begin>
%           strBgn  theString, strLength+32
            byte    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
%           genChrs strLength
%           strEnd  theString
            
; With insertion in the middle of the string:

theString   catstr  <timeStr>, %strLength, <_>, <middle>
%           strBgn  theString, strLength+32
%           genChrs (strLength+1)/2
            byte    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
%           genChrs strLength/2
%           strEnd  theString
            
; With insertion at the end of the string:

theString   catstr  <timeStr>, %strLength, <_>, <end>
%           strBgn  theString, strLength+32
%           genChrs strLength
            byte    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
%           strEnd  theString

strLength   =       strLength + 1
            endm    ;while


            


            
            .code
            externdef QueryPerformanceCounter:proc
            externdef QueryPerformanceFrequency:proc
            


;**************************************************
;
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbx
            push    rsi
            push    rdi
            push    r14
            push    r15
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage

 
; Before timing the code, run a verification
; test to ensure that stringInsert is working
; properly:

            
strLen      =       0
            while   strLen lt maxLen

theString   catstr  <testStr>, %strLen, <_>, <begin>
            lea     rdi, theString
            mov     rax, 0
            mov     rcx, 26
            call    stringDelete
            jc      badParameters
            
theString   catstr  <result>, %strLen
            lea     rsi, theString
            call    stringCmp1
            jne     strNE 
            
theString   catstr  <testStr>, %strLen, <_>, <middle>
            lea     rdi, theString
            mov     rax, (strLen+1)/2
            mov     rcx, 26
            call    stringDelete
            jc      badParameters
            
theString   catstr  <result>, %strLen
            lea     rsi, theString
            call    stringCmp1
            jne     strNE 
            
theString   catstr  <testStr>, %strLen, <_>, <end>
            lea     rdi, theString
            mov     rax, strLen
            mov     rcx, 26
            call    stringDelete
            jc      badParameters
            
            
theString   catstr  <result>, %strLen
            lea     rsi, theString
            call    stringCmp1
            jne     strNE 

strLen      =       strLen + 1
            endm    ;while
            
            call    print
            byte    "stringDelete verified", nl, 0
            
; Time the execution of stringDelete:
            
            call    print
            byte    "Timing stringDelete"
            byte    nl, 0
            
            lea     rcx, startTime
            call    QueryPerformanceCounter
            
strLength   =       0
            while   strLength lt maxLen
            local   theString

theString   catstr  <timeStr>, %strLength, <_>, <begin>
            
            lea     rdi, theString
            mov     eax, 0
            mov     ecx, 26
            call    stringDelete
            jc      badParameters

theString   catstr  <timeStr>, %strLength, <_>, <middle>
            
            lea     rdi, theString
            mov     eax, (strLength+1)/2
            mov     ecx, 26
            call    stringDelete
            jc      badParameters

theString   catstr  <timeStr>, %strLength, <_>, <end>
            
            lea     rdi, theString
            mov     eax, strLength
            mov     ecx, 26
            call    stringDelete
            jc      badParameters
            
strLength   =       strLength + 1
            endm    ;while
            
            
            
            lea     rcx, endTime
            call    QueryPerformanceCounter
            lea     rcx, frequency
            call    QueryPerformanceFrequency
            
            mov     rax, endTime
            sub     rax, startTime
                        
            mov     rdx, rax
            mov     r8, frequency
            call    print
            byte    "stringDelete "
            byte    "time = %d/%d seconds", nl, 0
            
            
            jmp     allDone

strNE:      call    print
            byte    "stringDelete failed:", nl
            byte    "Got      '%s',", nl
            byte    "Expected '%s'", nl, 0
            jmp     allDone
            
badParameters:
            call    print
            byte    "Bad parameters in stringDelete call", nl, 0
            
            

allDone:    leave
            pop     r15
            pop     r14
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
