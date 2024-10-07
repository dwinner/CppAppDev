; Listing 18-11
;
; FindStr and findLastStr Functions

            option     casemap:none
            include    string.inc
            include    aoalib.inc

            includelib aoalib.lib

; Number of times to repeat timing loop:

repeatCnt   =       20000
maxLen      =       256


; SSE4.2 feature flags (in ECX):

SSE42       =       00180000h       ;Bits 19 & 20
AVXSupport  =       10000000h       ;Bit 28


            include getTitle.inc
            include print.inc
            include string.inc


            .const
ttlStr      byte    "Listing 18-11", 0

            
; Macro to generate a sequence of characters
; that are largely different:

genChrs     macro   count
            local   cntr, chr
cntr        =       0
chr         =       'A'
            while   cntr lt count
            byte    chr
chr         =       chr+1
            if      chr gt 'Z'
chr         =       'A'
            endif
cntr        =       cntr + 1
            endm
            endm

; A macro that converts text to a string.
            
genStr      macro   theStr
            exitm   <"&theStr">
            endm


            

data        segment align(4096)

startTime   dword   ?
hasSSE42    byte    0 ;True if CPU supports SSE4.2 instrs


; Needle strings for testing:

            staticStr testString0, 8
            strDcl    testString, 8, "abc"
            strDcl    testString2, 24, "abcdefghijklmnopqr"
            strDcl    testString15, 15, "abcdefhijklmnop"

; Generate a whole bunch of strings for
; testing purposes:

            strDcl    name0, 8, "name0"
            staticStr string0, 1
first0      =         -1

            strDcl  name1, 8, "name1"
            strDcl  string1, 32, "abcdefghijklmnopqr"
first1      =       0
second1     =       0


; The following test strings take the form:
;
; @XXX: ABC..XYZabcdefghijkl...
;           mnopqrstuvwxyzabcdefghi...
;            jklmnopqrstuvwxyzABC..XYZ
;
; where XXX is a sequence of 1..3 digits matching
; the string's name (e.g., "stringXXX")
;
; ABC...XYZ is a sequence of 2 or more characters
; repeating the uppercase alphabetic characters.
;
;  abcdefghijklmnopqrstuvwxyz is the actual
; string (used to match needle strings).
;
; The following compile-time loop generates
; strings with the names string2, string3, ...,
; string<maxLen-1> and name2, name3, ...,
; name<maxLen-1>

strLength   =       2
            while   strLength lt maxLen
            
nameStr     catstr  <name>, %strLength
            strDcl  %nameStr, 16, genStr( %nameStr )

theString   catstr  <string>, %strLength
            strBgn  %theString, %(strLength*2)+64 
            byte    '@'
            byte    genStr( %strLength )
            byte    ": "
            
            genChrs %strLength

substr1     catstr  <first>, %strLength
substr1     =       $-theString
            byte    'abcdefghijklmnopqrstuvwxyz'

            
substr2     catstr  <second>, %strLength
substr2     =       $-theString
            byte    'abcdefghijklmnopqrstuvwxyz'
            
            ;Stick an extra copy of the generated
            ; string here to make the timings for
            ; findStr and findLastStr more comparable
            ; (Both functions will need to pass over
            ; the same number of characters).
            
            genChrs %strLength

            strEnd  %theString
            
substr2     catstr  <third>, %strLength
substr2     =       $-theString
            
strLength   =       strLength + 1
            endm


; Create "strAtEnd1" with its zero-terminating byte
; right up against the edge of a page boundary.

            align   4096
            org     $ - 32
            strDcl  strAtEnd1, 15, "abcdefhijklmnop"
            strDcl  nameAtEnd1a, 15, "strAtEnd1a"
            strDcl  nameAtEnd1b, 15, "strAtEnd1b"
            
; Create "strAtEnd2" with its string split across
; a page boundary:

            align   4096
            org     $ - 32
            strDcl  strAtEnd2, 23, "12345678abcdefhijklmnop"
            strDcl  nameAtEnd2a, 15, "strAtEnd2a"
            strDcl  nameAtEnd2b, 15, "strAtEnd2b"
            
; Create "strAtStart" with its string beginning
; on a page boundary:

            align   4096
            org     $ - 16
            strDcl  strAtStart, 15, "abcdefhijklmnop"
            strDcl  nameAtStarta, 15, "strAtStarta"
            strDcl  nameAtStartb, 15, "strAtStartb"
            strDcl  nameAtStartc, 15, "strAtStartc"
            strDcl  nameAtStartd, 15, "strAtStartd"
            

            .code
            externdef time:proc

;**************************************************
;
;  Macro to test the various string compare functions
;
; Arguments:
;
;  func     find(Last)Str function to call
;  srcReg   Register holding source address
;  destReg  Register holding destination address
;  txt      Text description of function
;
;  Executes specified strcmp function 
; (repeatCnt * maxLen * (maxLen+1))/2 times so we can time 
; its operation
;

tstFS       macro   func, match, txt
            local   findStrLp, badFindStr, allDone
            local   badFindStr2, badFindStr3, nextLp
            local   badFindStr4 

            call    print
            byte    "Timing &func", nl, 0
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            mov     startTime, eax  ;Save starting time

; Call the findStr function over and over again:

            mov     ebx, repeatCnt
findStrLp:



; Generate maxLen calls to the string length function, one
; for each of the maxLen strings created earlier:

lpCnt       =       0
            while   lpCnt lt maxLen
            local   offsetLp, badMtchLp1, badMtchLp2
            
; Test a string (less than 16 chars):

nameStr     catstr  <name>, %lpCnt
strName     catstr  <string>, %lpCnt
resultStr   catstr  <&match>, %lpCnt

; Try varying offsets from 0 to maxLen:

            mov     r15, 0
offsetLp:

            lea     rsi, strName
            lea     rdi, testString
            mov     rax, r15
            call    func             ;Call find(Last)Str.
            lea     r11, nameStr
            if      lpCnt eq 0
            
            jz      badFindStr3
            
            else
            
            
            jnz     badFindStr2
            mov     r12d, resultStr
            cmp     rax, r12
            jne     badFindStr
            
            endif
            
            
; Test a longer string (more than 16 chars):

strName     catstr  <string>, %lpCnt

            lea     rsi, strName
            lea     rdi, testString2
            mov     rax, r15
            call    func             ;Call find(last)Str.
            lea     r11, nameStr
            
            if      lpCnt eq 0
            
            jz      badFindStr3
            
            else
            
            jnz     badFindStr2
            mov     r12d, resultStr
            cmp     rax, r12
            jne     badFindStr
            
            endif


            inc     r15
            cmp     r15, lpCnt
            jb      offsetLp
            
; Special tests (only once per lpCnt loop):
;
; 1. If testing findLastStr*, then check
;    to make sure that an empty needle string
;    returns an offset that is the length
;    of the haystack; if testing findString*,
;    then the offset must be zero.
;
; 2. Check find*Str* with 3 special strings:
;    (1) a string whose zero-terminating byte
;        falls on the last byte of an MMU page
;    (2) a string that is split across an MMU page.
;    (3) a string whose characters begin on an MMU page.

            ifidn   <&match>, <first> ;If findStr*

            ; Check empty needle:

            lea     rsi, strAtStart
            lea     rdi, testString0
            xor     rax, rax        ;Value is irrelevant
            call    func            ;Call findStr function.
            mov     r12, 0
            mov     r15, 0
            lea     r11, nameAtStartc
            jnz     badFindStr
            test    rax, rax        ;Empty needle always 
            jnz     badFindStr      ; matches and returns 0.
            
            
            else    ;Must be "second" (findLastStr*)

            ; Check empty needle:

            lea     rsi, strAtStart
            lea     rdi, testString0
            xor     rax, rax        ;Value is irrelevant
            call    func            ;Call findStr function.
            mov     r12, 15
            mov     r15, 0
            lea     r11, nameAtStartd
            jnz     badFindStr
            cmp     rax, 15         ;Empty needle always 
            jnz     badFindStr      ; matches and returns 15.
            
            
            endif

            ; Check end of page:
            
            lea     rsi, strAtEnd1
            lea     rdi, testString15
            xor     rax, rax
            call    func            ;Call findStr function.
            mov     r12, 0
            mov     r15, 0
            lea     r11, nameAtEnd1a
            jnz     badFindStr
            test    rax, rax        ;Matches at offset 0 
            jnz     badFindStr      ; matches and returns 0.

            lea     rsi, strAtEnd1
            lea     rdi, testString15
            mov     rax, 1          ;Will not match offset 1
            call    func            ;Call findStr function.
            mov     r15, 1
            lea     r11, nameAtEnd1b
            jz      badFindStr4
            
            ; Check crossing page:

            lea     rsi, strAtEnd2
            lea     rdi, testString15
            mov     rax, 8          ;Has 8 chars in front.
            call    func            ;Call findStr function.
            mov     r12, 8
            mov     r15, 8
            lea     r11, nameAtEnd2a
            jnz     badFindStr
            cmp     rax, 8          ;Matches at offset 8. 
            jnz     badFindStr
            
            mov     r15, 9
badMtchLp1: lea     rsi, strAtEnd2
            lea     rdi, testString15
            mov     rax, r15        ;Will not match offset r15.
            call    func            ;Call findStr function.
            lea     r11, nameAtEnd2b
            jz      badFindStr4
            inc     r15
            cmp     r15, 23
            jb      badMtchLp1  
            
            ; Check at start of page:
            
            lea     rsi, strAtStart
            lea     rdi, testString15
            mov     rax, 0          ;Will match at offset 0.
            call    func            ;Call findStr function.
            mov     r12, 0
            mov     r15, 0
            lea     r11, nameAtStarta
            jnz     badFindStr
            test    rax, rax        ;Matches at offset 0 
            jnz     badFindStr      ; matches and returns 0.
            

            mov     r12, 1
badMtchLp2: lea     rsi, strAtStart
            lea     rdi, testString15
            mov     rax, r12        ;Will not match offset 1.
            call    func            ;Call findStr function.
            lea     r11, nameAtStartb
            jz      badFindStr4
            inc     r12
            cmp     r12, 15
            jb      badMtchLp2 

            
            
            
lpCnt       =       lpCnt + 1
            endm
            

; Timing loop:

nextLp:     dec     ebx
            jnz     findStrLp
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            sub     eax, startTime  
            
            mov     edx, eax
            call    print
            byte    "&txt "
            ifidn   <&match>, <first>
            byte    "findStr"
            else
            byte    "findLastStr"
            endif
            byte    " time = %d seconds", nl, 0
            jmp     allDone
            
badFindStr: mov     rdx, rsi
            mov     r8, rdi 
            mov     r9, r12
            mov     r10, rax
            ;mov    r11, r11
            call    print
            byte    "Searching in '%s' for '%s'", nl
            byte    "Expected %d, got %d", nl 
            byte    "string:%s ", 0

            mov     rdx, r15
            call    print
            byte    "offset:%d", nl, 0
            jmp     allDone
            
badFindStr2:        
            mov     rdx, r11
            mov     r8, r15
            mov     r9, rdi
            mov     r10, rsi
            call    print
            byte    "%s:String should match", nl
            byte    "Offset:%d, Needle:'%s', Haystack:'%s'"
            byte    nl, 0
            jmp     allDone
            
badFindStr3:        
            mov     rdx, r11
            call    print
            byte    "%s:Empty haystack string should not match"
            byte    nl, 0
            jmp     allDone
            
badFindStr4:        
            mov     rdx, r11
            mov     r8, r15
            mov     r9, rdi
            mov     r10, rsi
            call    print
            byte    "%s:String should not match", nl
            byte    "Offset:%d, Needle:'%s', Haystack:'%s'"
            byte    nl, 0
            
allDone:
                    
            endm




            
;**************************************************
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
            
; This program requires SSE4.2 features to run properly.
; Check for the presence of those features before running.
;
; Leaf function 1 is available on all CPUs that support
; CPUID, no need to test for it.  

            mov     eax, 1
            cpuid
            and     ecx, SSE42      ;Test bits 19 & 20
            cmp     ecx, SSE42      ;Both must be set
            sete    hasSSE42

; Time the SSE variant of findStr and findLastStr here:

            tstFS  findStr1, first, SSE
            tstFS  findLastStr1, second, SSE        
            
; Time the PCMPISTRI version here:

            cmp     hasSSE42, 1
            je      doPSTR
            
            call    print
            byte    "CPU does not support SSE42 "
            byte    "instructions, skipping find(Last)Str2"
            byte    nl, 0
            jmp     noSSE42

; Test variants that are pcmpistri-based:
            
doPSTR:     
            tstFS  findStr2, first, pcmpistri
            tstFS  findLastStr2, second, pcmpistri


noSSE42:
            

allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
