; Listing 17-5
;
; strchr and strrchr Functions

            include    zstrings.inc
            include    aoalib.inc
            includelib aoalib.lib

; Number of iterators for timing loop:

repeatCnt   =       10000000

            .const
ttlStr      byte    "Listing 15-5", 0

data        segment align(32)
            align   32
startTime   dword   ?


; Generate a whole bunch of strings for
; testing purposes:
;
; string0 is a special case, just the
; empty string (always fails for strchr
; and strrchr).

string0     byte    0
string0_1st byte    0
string0_2nd byte    0
string0name byte    "string0", 0

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
strName1st  catstr  <string>, %strLength, <_1st>
strName2nd  catstr  <string>, %strLength, <_2nd>

            if      strLength gt 6
            
strName     byte    strLength-6 dup ('.')
strName     catstr  <string>, %strLength, <_1st>
            byte    80h, 81h, 0ffh
strName     byte    'ab'
strName     catstr  <string>, %strLength, <_2nd>
strName     byte    'a'

            else
            
strName     byte    strLength dup ('.')
strName1st  byte    0
strName2nd  byte    0
            
            endif
            byte    0
            makeStr %strLength

strLength   =       strLength + 1
            endm

data        ends            
            
            .code

;************************************************************
;
; Macro that generates code to time and test an
; strchr call.
;
; Parameters:
;
;           func:   Name of strchr function to test
;           srcReg: Name of register that will hold
;                   the string address in call to
;                   function.
;           chrReg: Name of register that will hold
;                   the character to search for.
;           posn:   1st for strchr, 2nd for strrchr.
;           txt:    Text describing function.

timeSC      macro   func, srcReg, chrReg, posn, txt
            local   strLp
            
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

lpCnt       =       0
            while   lpCnt lt 256
            local   strSuccess
strSuccess  catstr  <&func>, <_>, %lpCnt
strName     catstr  <string>, %lpCnt
stringName  catstr  strName, <name>
matchPosn   catstr  strName, <_>, <posn>

            lea     srcReg, strName
            mov     chrReg, 'a'
            call    func             ;Call strchr function.
            
            if      lpCnt le 6      ;NULL pointer only
            test    rax, rax        ; valid for 
            jz      strSuccess      ; string0..string5
            endif
            
            if      lpCnt gt 6      ;Expect actual
            lea     rsi, matchPosn  ; result if not
            cmp     rax, rsi        ; string0
            je      strSuccess
            endif

            lea     rdx, stringName 
            mov     r8, rax
            mov     r9, rsi
            call    print
            byte    "%s: Got %I64x, expected %I64x", nl, 0
            lea     rdx, strName
            lea     r8, matchPosn
            mov     r9, rax
            call    print
            byte    "base: %s, substr:%s, got:%s", nl, 0 
strSuccess:

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

            endm

;************************************************************

            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbx
            push    rsi
            push    rdi
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage
            
; This program requires SSE 4.2 features to run properly.
; Check for the presence of those features before running.
;
; Leaf function 1 is available on all CPUs that support
; CPUID, no need to test for it.  

            mov     eax, 1
            cpuid
            and     ecx, SSE42    ;Test bits 19 & 20
            cmp     ecx, SSE42    ;Both must be set
            jne     Unsupported
             


; Running timing tests on each of the various strchr and
; strrchr functions:

            timeSC  strchr1, rsi, rax, 1st, naive strchr
            timeSC  strchr2, rsi, rax, 1st, 64-bit optimized strchr
            timeSC  strchr3, rsi, rax, 1st, pcmpistri strchr
            timeSC  strchr4, rsi, rax, 1st, SSE strchr
            timeSC  strchr, rcx, rdx, 1st, C Stdlib strchr
            timeSC  strrchr1, rsi, rax, 2nd, naive strrchr
            timeSC  strrchr2, rsi, rax, 2nd, 64-bit optimized strrchr
            timeSC  strrchr3, rsi, rax, 2nd, pcmpistri strrchr
            timeSC  strrchr4, rsi, rax, 2nd, SSE strrchr
            timeSC  strrchr, rcx, rdx, 2nd, C Stdlib strrchr
            jmp     allDone
            
Unsupported:
            call    print
            byte    "CPU does not support SSE 4.2 "
            byte    "instructions", nl, 0
                    

allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end









                       