; Listing 18-8
;
; Parial Comparison functions.

            option     casemap:none
            include    string.inc
            include    aoalib.inc

            includelib aoalib.lib


; Note: maxLen must not exceed 252. The test code
; depends on this!

maxLen      =       32


            .const
ttlStr      byte    "Listing 18-8", 0

            .data
startTime   dword   ?

            staticStr       subs, 300


; Generate a string that can be used as the
; source string. Note, and this is very 
; important, that there are 253 characters
; in this string and their values range
; from 2..254. This allows the comparison
; arrays to use the values 1 and 255 to
; create strings that are less than or
; greater than to this string.
;
; Declare and initialize "source" string:

            strBgn  source, 300
chr         =       2
            while   chr lt 254
            byte    chr
chr         =       chr+1
            endm
            strEnd  source
            

; Special case string to test for greater than when
; the partial string matches a suffix of source 
; but is one character longer.

gt0Start    =       254-maxLen
            strBgn  gt0, 300
chr         =       gt0Start+2
ndx         =       0
            while   ndx lt maxLen-1
            byte    chr
chr         =       chr+1
ndx         =       ndx+1
            endm
            strEnd  gt0

            
; Special case string to test for less than when
; the partial string matches a suffix of source 
; but is one character longer.

lt0Start    =       254-maxLen
            strBgn  lt0, 300
chr         =       lt0Start+2
ndx         =       0
            while   ndx lt maxLen-3
            byte    chr
chr         =       chr+1
ndx         =       ndx+1
            endm
            byte    chr-2   ;Make it less than
            byte    chr+1   ;Arbitrary
            strEnd  lt0

            


; This program dynamically allocates and initializes
; all the test strings it uses. The test strings
; appear on the heap and the following two-dimensional
; array elements contain the address of each particular
; test string. The arrays are organized as follows:
;
;  arrayName[ofs][len]
;
; where "ofs" represents a starting offset into the
; "source" string and "len" represents the length of
; the partial string to compare.
;
; Each array has "maxLen" columns and "maxLen" rows.
;
; The "equalStrs" array contains pointers to strings
; that will be equal to substr( source, ofs, len )
;
; The ltStrs array contains pointers
; to strings that will be less than 
; substr( source, ofs, len )
;
; The gtStrs array contains pointers
; to strings that will be greater than 
; substr( source, ofs, len )
;
; Note that ofs ranges from 0..maxLen and
; len ranges from 1..(maxLen-ofs). Elements "[ofs][0]"
; and "[ofs][maxLen-ofs+1] "[ofs][maxLen]" in the 
; following arrays do not get used.
  

equalStrs   qword   maxLen dup (maxLen dup (0))
ltStrs      qword   maxLen dup (maxLen dup (0))
gtStrs      qword   maxLen dup (maxLen dup (0))

            

            

            .code
            externdef time:proc 
 
;**************************************************
;
;  Macro to test the various string compare functions
;
; Arguments:
;
;  func     strcpy function to call
;  txt      Text description of function
;
;  Executes specified partial compare function 
;  5,000,000 * 256 times so we can time its operation
;

substring   textequ <substring1>
tstPC       macro   func, txt
            local   strCmpLp, allDone, ofsLp, lenLp
            local   notEql, notLess, notGreater
            local   subIsShorter, subIsShorter1, subIsShorter2

            call    print
            byte    "Timing &func", nl, 0
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            mov     startTime, eax  ;Save starting time

; Call the substring function over and over again.

            mov     ebx, 5000000
strCmpLp:
            mov     r14, 0          ;R14 = offset
ofsLp:      mov     r15, 1          ;R15 = len
            mov     r13, maxLen-1
            sub     r13, r14

; Handle test for equality:

lenLp:
            imul    rax, r14, maxLen
            add     rax, r15
            lea     rcx, equalStrs
            mov     rsi, [rcx][rax*8]
            lea     rdi, source
            mov     rax, r14
            call    func
            jne     notEql

; Handle test for greater than:

            imul    rax, r14, maxLen
            add     rax, r15
            lea     rcx, gtStrs
            mov     rsi, [rcx][rax*8]

            lea     rdi, source
            mov     rax, r14
            call    func
            jbe     notGreater
            

; Handle test for less than:

            imul    rax, r14, maxLen
            add     rax, r15
            lea     rcx, ltStrs
            mov     rsi, [rcx][rax*8]
            lea     rdi, source
            mov     rax, r14
            call    func
            jae     notLess
            
; Repeat for lengths 1..(maxLen-start)

            inc     r15
            cmp     r15, r13
            jbe     lenLp
            
; Repeat for offsets 0 .. maxLen:

            inc     r14
            cmp     r14, maxLen
            jb      ofsLp
            
            
; Special case tests:
;
;
; gt0 is a special string that is a byte
; longer than the source string when
; starting at offset 222. It is equal
; to the string up to the last character
; in source. So it should be greater than
; source.

            lea     rsi, gt0
            lea     rdi, source
            mov     rax, gt0Start
            mov     r14, rax
            mov     r15d, [rsi-sohs].strObject.strLength
            call    func
            jbe     notGreater
;
; lt0 is a special string that is a byte
; longer than the source string when
; starting at offset 222. It is equal
; to the string up to the next to last character
; in source, which is less than the byte
; in the source string.

            lea     rsi, lt0
            lea     rdi, source
            mov     rax, lt0Start
            mov     r14, rax
            mov     r15d, [rsi-sohs].strObject.strLength
            call    func
            jae     notLess
  
                
; Repeat 5,000,000 times so we can time this:
      
            dec     ebx
            jnz     strCmpLp

; Compute and display the running time:
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            sub     eax, startTime  
            
            mov     edx, eax
            call    print
            byte    "&txt time = %d seconds", nl, 0
            jmp     allDone
       
notEql:     push    rsi
            lea     rsi, source
            mov     rax, r14
            mov     ecx, [rsi-sohs].strObject.strLength
            sub     rcx, rax
            cmp     rcx, r15
            jb      subIsShorter1
            mov     rcx, r15
subIsShorter1:
            lea     rdi, subs
            call    substring
            call    print
            byte    "Substring of source: ", nl, 0
            lea     rsi, subs
            call    printString
            pop     rsi
            call    print
            byte    nl, "is not equal to ", nl, 0
            call    printString
            mov     rdx, r14
            mov     r8, r15
            call    print
            byte    nl, "at offset %d with length %d", nl, 0
            jmp     allDone  
       
       
; Print an error if the partial was supposed to be less
; that the source, but it wasn't.

notGreater: push    rsi
            lea     rsi, source
            mov     rax, r14
            mov     ecx, [rsi-sohs].strObject.strLength
            sub     rcx, rax
            cmp     rcx, r15
            jb      subIsShorter
            mov     rcx, r15
subIsShorter:
            lea     rdi, subs
            call    substring
            call    print
            byte    "Substring of source: ", nl, 0
            lea     rsi, subs
            call    printString
            pop     rsi
            call    print
            byte    nl, "is not greater than ", nl, 0
            call    printString
            mov     rdx, r14
            mov     r8, r15
            call    print
            byte    nl, "at offset %d with length %d", nl, 0
            jmp     allDone  
                 
; Print an error if the partial was supposed to be less
; that the source, but it wasn't.

notLess:    push    rsi
            lea     rsi, source
            mov     rax, r14
            mov     ecx, [rsi-sohs].strObject.strLength
            sub     rcx, rax
            cmp     rcx, r15
            jb      subIsShorter2
            mov     rcx, r15
subIsShorter2:
            lea     rdi, subs
            call    substring
            call    print
            byte    "Substring of source: ", nl, 0
            lea     rsi, subs
            call    printString
            pop     rsi
            call    print
            byte    nl, "is not less than ", nl, 0
            call    printString
            mov     rdx, r14
            mov     r8, r15
            call    print
            byte    nl, "at offset %d with length %d", nl, 0
             
                                        
allDone:
            endm
            

;**********************************************************
;
; Here is the "asmMain" function.
        
            public  asmMain
asmMain     proc
            push    rbx
            push    rsi
            push    rdi
            push    r13
            push    r14
            push    r15
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage
            
; Before running the benchmarks, need to initialize
; all the strings:

            call    print
            byte    "Initializing test strings", nl, 0

            mov     r14, 0
ofsLp:      mov     r15, 1  ;Skip elements 0..start.
            mov     r13, maxLen-1
            sub     r13, r14
lenLp:

; Begin by allocating storage for the equalStrs[r14][r15]
; element and initialize it to substr( source, r14, r15 ):

            lea     rax, [r15+4]    ;Size of string to allocate.
            call    stringAlloc     ;Allocate the string
            test    rax, rax        ;Check for allocation error.
            jz      allocFailed
            
            imul    rbx, r14, maxLen ;Compute index into
            add     rbx, r15         ; arrays.
            lea     rcx, equalStrs
            mov     [rcx][rbx*8], rax
            
            mov     rdi, rax        ;Where to store substr
            mov     rax, r14        ;Offset into source
            mov     rcx, r15        ;Length of substr
            lea     rsi, source
            call    substring       ;Move substring to equalStrs.

; Next, allocate storage for the gtStrs[r14][r15]
; element and initialize it to substr( source, r14, r15 ),
; but change the first character to 0FFh to guarantee it
; is greater than the source string.

            lea     rax, [r15+4]    ;Size of string to allocate.
            call    stringAlloc     ;Allocate the string
            test    rax, rax        ;Check for allocation error.
            jz      allocFailed
            
            imul    rbx, r14, maxLen ;Compute index into
            add     rbx, r15         ; arrays.
            lea     rcx, gtStrs
            mov     [rcx][rbx*8], rax

            mov     rdi, rax        ;Where to store substr
            mov     rax, r14        ;Offset into source
            mov     rcx, r15        ;Length of substr
            lea     rsi, source
            call    substring       ;Move substring to equalStrs.
            
; Force the last byte of the string to 255 (0FFh).

            mov     byte ptr [rdi][r15*1-1], 0ffh
            
            
; Next, allocate storage for the ltStrs[r14][r15]
; element and initialize it to substr( source, r14, r15 ),
; but change the last character to 01h to guarantee it
; is less than the source string.

            lea     rax, [r15+4]    ;Size of string to allocate.
            call    stringAlloc        ;Allocate the string
            test    rax, rax        ;Check for allocation error.
            jz      allocFailed
            
            imul    rbx, r14, maxLen ;Compute index into
            add     rbx, r15         ; arrays.
            lea     rcx, ltStrs
            mov     [rcx][rbx*8], rax

            mov     rdi, rax        ;Where to store substr
            mov     rax, r14        ;Offset into source
            mov     rcx, r15        ;Length of substr
            lea     rsi, source
            call    substring       ;Move substring to equalStrs.
            
; Force the last byte of the string to 1.

            mov     byte ptr [rdi][r15*1-1], 1
            
            
; Repeat for the next len value:
            
            inc     r15
            cmp     r15, r13
            jbe     lenLp
            
; Repeat for the next ofs value:    
            
            inc     r14
            cmp     r14, maxLen
            jb      ofsLp
            
            call    print
            byte    "Initializing complete", nl, nl, 0
            
            
; Initialization is complete. Now run the tests/benchmarks


            tstPC   partialCmp1, cmpsb partial compare
            tstPC   partialCmp2, SSE partial compare
            tstPC   partialCmp3, pcmpestri partial compare
            
            jmp     allDone
            
allocFailed:
            call    print
            byte    "Memory allocation failure", nl
            byte    "Program aborting...", nl, 0

                         
allDone:
            leave
            pop     r15
            pop     r14
            pop     r13
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
