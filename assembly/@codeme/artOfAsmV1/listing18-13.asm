; Listing 18-13
;
; stringInsert Function

            option     casemap:none
            include    string.inc
            include    aoalib.inc

            includelib aoalib.lib

; Maximum length of source string expansion
; (Controls timing loop iterations, too).

maxLen      =       256



            .const
ttlStr      byte    "Listing 18-13", 0

            strDcl  strNE1, 32, "begin1"            
            strDcl  strNE2, 32, "begin2"            
            strDcl  strNE3, 32, "middle1"            
            strDcl  strNE4, 32, "middle2"            
            strDcl  strNE5, 32, "end1"            
            strDcl  strNE6, 32, "end2"            
            

            .data
startTime   qword   ?
endTime     qword   ?
frequency   qword   ?


            

; Generate a whole bunch of strings for
; testing purposes:

; strToInsert is the test string to insert into 
; the strings below:

            strBgn  strToInsert, 32
            byte    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            strEnd  strToInsert


            strBgn  strToInsert2, 64
            byte    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            byte    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            strEnd  strToInsert2



; Generate the test strings into which the above
; will be inserted:


begin1Strs  equ     this qword
strIndex    =       0
            while   strIndex lt maxLen
            local   begin1Str
            
begin1Str   catstr  <string>, %strIndex, <_>, <begin>
begin1Str   qword   0
strIndex    =       strIndex + 1
            endm    ;while
            
            
            
middle1Strs equ     this qword
strIndex    =       0
            while   strIndex lt maxLen
            local   middle1Str
            
middle1Str  catstr  <string>, %strIndex, <_>, <middle>
middle1Str  qword   0
strIndex    =       strIndex + 1
            endm    ;while
            
            
            
end1Strs    equ     this qword
strIndex    =       0
            while   strIndex lt maxLen
            local   end1Str
            
end1Str     catstr  <string>, %strIndex, <_>, <end>
end1Str     qword   0
strIndex    =       strIndex + 1
            endm    ;while
            




begin2Strs  equ     this qword
strIndex    =       0
            while   strIndex lt maxLen
            local   begin2Str
            
begin2Str   catstr  <string>, %strIndex, <_>, <begin2>
begin2Str   qword   0
strIndex    =       strIndex + 1
            endm    ;while
            
            
            
middle2Strs equ     this qword
strIndex    =       0
            while   strIndex lt maxLen
            local   middle2Str
            
middle2Str  catstr  <string>, %strIndex, <_>, <middle2>
middle2Str  qword   0
strIndex    =       strIndex + 1
            endm    ;while
            
            
            
end2Strs    equ     this qword
strIndex    =       0
            while   strIndex lt maxLen
            local   end2Str
            
end2Str     catstr  <string>, %strIndex, <_>, <end2>
end2Str     qword   0
strIndex    =       strIndex + 1
            endm    ;while
            


            
; Macro to generate a sequence of characters:

genChrs     macro   count
            if      count gt 0
            byte    count dup ('.')
            endif
            endm
            
; Generate some result strings. To keep assembly times
; manageable, this generates 3 strings for each string
; length
;
; 1) With insertion at position 0.
; 2) With insertion at the middle of the string.
; 3) With insertion at the end of the string.
;
; E.g.,
;
; result3_begin is   "ABCDEFGHIJKLMNOPQRSTUVWXYZ..."
; resultg3_middle is "..ABCDEFGHIJKLMNOPQRSTUVWXYZ."
; result3_end is     "...ABCDEFGHIJKLMNOPQRSTUVWXYZ"
;
; Start with the beginning:


strLength   =       0
            while   strLength lt maxLen
            local   begin1Str
theString   catstr  <result>, %strLength, <_>, <begin>
%           strBgn  theString, strLength+32
            byte    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
%           genChrs strLength
%           strEnd  theString
            
; With insertion in the middle of the string:

theString   catstr  <result>, %strLength, <_>, <middle>
%           strBgn  theString, strLength+32
%           genChrs (strLength+1)/2
            byte    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
%           genChrs strLength/2
%           strEnd  theString
            
; With insertion at the end of the string:

theString   catstr  <result>, %strLength, <_>, <end>
%           strBgn  theString, strLength+32
%           genChrs strLength
            byte    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
%           strEnd  theString


theString   catstr  <result>, %strLength, <_>, <begin2>
%           strBgn  theString, strLength+64
            byte    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            byte    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
%           genChrs strLength
%           strEnd  theString
            
; With insertion in the middle of the string:

theString   catstr  <result>, %strLength, <_>, <middle2>
%           strBgn  theString, strLength+64
%           genChrs (strLength+1)/2
            byte    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            byte    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
%           genChrs strLength/2
%           strEnd  theString
            
; With insertion at the end of the string:

theString   catstr  <result>, %strLength, <_>, <end2>
%           strBgn  theString, strLength+64
%           genChrs strLength
            byte    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            byte    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
%           strEnd  theString

strLength   =       strLength + 1
            endm    ;while


; Pointers to the above strings, so we can compare
; them against the generated strings in a loop:

rBeginStrs  equ     this qword
strIndex    =       0
            while   strIndex lt maxLen
            local   theString
            
theString   catstr  <result>, %strIndex, <_>, <begin>
            qword   theString
strIndex    =       strIndex + 1
            endm    ;while
            
            
rMiddleStrs equ     this qword
strIndex    =       0
            while   strIndex lt maxLen
            local   theString
            
theString   catstr  <result>, %strIndex, <_>, <middle>
            qword   theString
strIndex    =       strIndex + 1
            endm    ;while
            
            
rEndStrs    equ     this qword
strIndex    =       0
            while   strIndex lt maxLen
            local   theString
            
theString   catstr  <result>, %strIndex, <_>, <end>
            qword   theString
strIndex    =       strIndex + 1
            endm    ;while
            


rBegin2Strs equ     this qword
strIndex    =       0
            while   strIndex lt maxLen
            local   theString
            
theString   catstr  <result>, %strIndex, <_>, <begin2>
            qword   theString
strIndex    =       strIndex + 1
            endm    ;while
            
            
rMiddle2Strs equ    this qword
strIndex    =       0
            while   strIndex lt maxLen
            local   theString
            
theString   catstr  <result>, %strIndex, <_>, <middle2>
            qword   theString
strIndex    =       strIndex + 1
            endm    ;while
            
            
rEnd2Strs   equ     this qword
strIndex    =       0
            while   strIndex lt maxLen
            local   theString
            
theString   catstr  <result>, %strIndex, <_>, <end2>
            qword   theString
strIndex    =       strIndex + 1
            endm    ;while
            


            
            .code
            externdef QueryPerformanceCounter:proc
            externdef QueryPerformanceFrequency:proc
            
; AllocStrs-
;
; Allocates "maxLen" strings, each maxLen*maxLen+64 bytes long.
;
; RDI-      Points at an array of pointers (to strings).

AllocStrs   proc
            push    rbx
            push    rdi
            push    rsi
            mov     rsi, rdi
            mov     rbx, 0
allocLp:    mov     rax, maxLen*64 + 64
            call    stringAlloc
            mov     [rsi][rbx*8], rax
            mov     rdi, rax
            mov     al, '.'
            mov     rcx, rbx
            call    stringInit 
            add     rbx, 1
            cmp     rbx, maxLen
            jb      allocLp
            pop     rsi
            pop     rdi
            pop     rbx
            ret
AllocStrs   endp


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

; Allocate a large set of strings on the heap:

            lea     rdi, begin1Strs
            call    AllocStrs
            lea     rdi, middle1Strs
            call    AllocStrs
            lea     rdi, end1Strs
            call    AllocStrs
 
            lea     rdi, begin2Strs
            call    AllocStrs
            lea     rdi, middle2Strs
            call    AllocStrs
            lea     rdi, end2Strs
            call    AllocStrs
 
; Before timing the code, run a verification
; test to ensure that stringInsert is working
; properly:

testIns     macro   dest, result, insert, which, posn
            local   lp
            mov     rbx, 0
            lea     rcx, dest
            lea     rdx, result
            lea     r15, which
lp:         lea     rsi, insert
            mov     rdi, [rcx][rbx*8]
            
            if      posn eq 0
            
            mov     rax, 100000000h
            
            elseif  posn eq 1
            
            mov     rax, rbx
            inc     rax
            shr     rax, 1
            
            else
            
            mov     eax, [rdi-sohs].strObject.strLength
            
            endif
            
            call    stringInsert
            jc      parameterError
            
            mov     rsi, [rdx][rbx*8]
            call    stringCmp1
            jne     stringsNE
            
            inc     rbx
            cmp     rbx, maxLen
            jb      lp
            endm
            
            testIns begin1Strs, rBeginStrs, \
                    strToInsert, strNE1, 0  
            testIns begin2Strs, rBegin2Strs, \
                    strToInsert2, strNE2, 0 
            testIns middle1Strs, rMiddleStrs, \
                            strToInsert, strNE3, 1  
            testIns middle2Strs, rMiddle2Strs, \
                            strToInsert2, strNE4, 1 
            testIns end1Strs, rEndStrs, \
                            strToInsert, strNE5, 2  
            testIns end2Strs, rEnd2Strs, \
                            strToInsert2, strNE6, 2 
            
            call    print
            byte    "All tests completed successfully", nl, 0
            
; Now that the code has checked the validity of the
; stringInsert procedure, let's time the execution of the code:

            call    print
            byte    "Timing stringInsert"
            byte    nl, 0
            
            lea     rcx, startTime
            call    QueryPerformanceCounter
            
timeLp:     mov     rcx, 0
timeLp2:    mov     r14, 0
timeLp3:    lea     rdx, begin1Strs
            mov     rdi, [rdx][rcx*8]
            lea     rsi, strToInsert
            mov     rax, r14
            call    stringInsert
            jc      timingFailure
                    
            lea     rdx, begin2Strs
            mov     rdi, [rdx][rcx*8]
            lea     rsi, strToInsert2
            mov     rax, r14
            call    stringInsert
            jc      timingFailure
                    
            inc     r14
            cmp     r14, maxLen
            jb      timeLp3
            inc     rcx
            cmp     rcx, maxLen
            jb      timeLp2
            
            lea     rcx, endTime
            call    QueryPerformanceCounter
            lea     rcx, frequency
            call    QueryPerformanceFrequency
            
            mov     rax, endTime
            sub     rax, startTime
                        
            mov     rdx, rax
            mov     r8, frequency
            call    print
            byte    "stringInsert "
            byte    "time = %d/%d seconds", nl, 0
            jmp     allDone

timingFailure:
            call    print
            byte    "Parameter failure during timing", nl, 0
            jmp     allDone
            
stringsNE:  mov     rdx, r15
            mov     r8, rbx
            mov     r9, rdi
            mov     r10, rsi
            call    print
            byte    "%s:Strings not equal, "
            byte    "RBX=%d, string='%s', '%s'", nl, 0
            jmp     allDone
            
parameterError:
            mov     rdx, rbx
            mov     r8, r15
            call    print
            byte    "strLength:%d, which:%s", nl, 0
            
            mov     rdx, rsi
            mov     r8, rdi
            call    print
            byte    "Error in parameters.", nl, 0

allDone:    leave
            pop     r15
            pop     r14
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
