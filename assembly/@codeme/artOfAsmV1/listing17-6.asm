; Listing 17-6
;
; strstr and strrstr Functions

            include    zstrings.inc
            include    aoalib.inc
            includelib aoalib.lib

; Number of iterations for the timing test

repeatCnt   =       5000000

            .const
ttlStr      byte    "Listing 17-6", 0


data        segment align(4096)

startTime   dword   ?
hasSSE42    byte    0 ;True if CPU supports SSE4.2 instrs


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
            
genStr      macro   theStr
            exitm   <"&theStr">
            endm


; Generate a whole bunch of strings for
; testing purposes:

string0     byte    0
first0      byte    0
name0       byte    "name0", 0

first1      equ     this byte
second1     equ     this byte
string1     byte    "abcdefghijklmnopqr", 0
name1       byte    "name1", 0

strLength   =       2
            while   strLength lt 256
theString   catstr  <string>, %strLength
theString   byte    '@', genStr( %strLength ), ": "
            genChrs %strLength
            
substr1     catstr  <first>, %strLength
substr1     byte    'abcdefghijklmnopqrstuvwxyz'

substr2     catstr  <second>, %strLength
substr2     byte    'abcdefghijklmnopqr'
            byte    0
nameStr     catstr  <name>, %strLength
nameStr     byte    "name", genStr(%strLength), 0
            
strLength   =       strLength + 1
            endm

testString  byte    "abc", 0            
testString2 byte    "abcdefghijklmnopqr", 0

; Test some strings that butt up against the end
; of an MMU page:

            align   4096
            
            byte    (4096-48) dup (0)

string256   byte    "@256"                          ;Ofs 0
first256    byte    'abcdefghijklmnopqrstuvwxyz'    ;Ofs 4
second256   byte    'abcdefghijklmnopqr'            ;Ofs 30
            byte    0                               ;Ofs 48
name256     byte    "name256", 0    
            
; PC is now at offset 0 into a new page.

            byte    (4096-47) dup (0)
            
string257   byte    "@257"                          ;Ofs 0
first257    byte    'abcdefghijklmnopqrstuvwxyz'    ;Ofs 4
second257   byte    'abcdefghijklmnopqr'            ;Ofs 30
            byte    0                               ;Ofs 48
name257     byte    "name257", 0    
            
; PC is now at offset 1 into a new page.

; Each iteration of the following loop generates
; 4097 bytes of data.

lpCntr      =       258
            while   lpCntr lt 300
            byte    (4096-47) dup (0)
            
theString   catstr  <string>, %lpCntr
theString   byte    "@", genStr(%lpCntr)            ;Ofs 0
firstStr    catstr  <first>, %lpCntr
firstStr    byte    'abcdefghijklmnopqrstuvwxyz'    ;Ofs 4
secondStr   catstr  <second>, %lpCntr
secondStr   byte    'abcdefghijklmnopqr'            ;Ofs 30
            byte    0                               ;Ofs 48
nameStr     catstr  <name>, %lpCntr
nameStr     byte    "name", genStr(%lpCntr), 0
            
lpCntr      =       lpCntr + 1
            endm
            


data        ends            
            
            .code
            externdef time:proc
            externdef strstr:proc



;**************************************************
;
;  Macro to test the various string compare functions
;
; Arguments:
;
;  func     strstr function to call
;  srcReg   Register holding source address
;  destReg  Register holding destination address
;  txt      Text description of function
;
;  Executes specified strcmp function 5,000,000 * 256 times
; so we can time its operation
;

tstStr      macro   func, match, hayReg, ndlReg, txt
            local   strCmpLp, badStrstr, allDone
            local   badStrstr2

            call    print
            byte    "Timing &func", nl, 0
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            mov     startTime, eax  ;Save starting time

; Call the string copy function over and over again:

            mov     ebx, repeatCnt
strCmpLp:

; Generate 300 calls to the string length function, one
; for each of the 300 strings created earlier:

lpCnt       =       0
            while   lpCnt lt 300
            
; Test a string (less than 16 chars):

nameStr     catstr  <name>, %lpCnt
strName     catstr  <string>, %lpCnt
            lea     hayReg, strName
            lea     ndlReg, testString
            call    func             ;Call str(r)str function.
            
            lea     r11, nameStr
            if      lpCnt eq 0
            
            test    rax, rax
            jnz     badStrstr2
            
            else
            
            lea     hayReg, strName         ;C Function
            lea     ndlReg, testString      ; wipes these.

substr1     catstr  <match>, %lpCnt
            lea     r12, substr1
            cmp     rax, r12
            jne     badStrstr
            
            endif
            
; Test a longer string (more than 16 chars):

strName     catstr  <string>, %lpCnt
            lea     hayReg, strName
            lea     ndlReg, testString2
            call    func             ;Call str(r)str function.
            lea     r11, nameStr
            
            if      lpCnt eq 0
            
            test    rax, rax
            jnz     badStrstr2
            
            else
            
            lea     hayReg, strName         ;C Function
            lea     ndlReg, testString      ; wipes these.

substr1     catstr  <match>, %lpCnt
            lea     r12, substr1
            cmp     rax, r12
            jne     badStrstr
            
            endif
            
lpCnt       =       lpCnt + 1
            endm
            
            dec     ebx
            jnz     strCmpLp
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            sub     eax, startTime  
            
            mov     edx, eax
            call    print
            byte    "&txt "
            ifidn   <&match>, <first>
            byte    "strstr"
            else
            byte    "strrstr"
            endif
            byte    " time = %d seconds", nl, 0
            jmp     allDone
            
badStrstr:  mov     rdx, hayReg
            mov     r8, ndlReg 
            mov     r9, r12
            mov     r10, rax
            ;mov    r11, r11
            call    print
            byte    "Searching in '%s' for '%s'", nl
            byte    "Expected %I64x, got %I64x", nl 
            byte    "string:%s", nl,0
            
            
            mov     rdx, rcx
            mov     r8, rax
            call    print
            byte    "expected: '%s', got '%s'", nl, 0
            
            lea     rdx, testString
            lea     r8, string259
            lea     r9, first259
            lea     r10, [r9][4096]
            call    print
            byte    "TestString:%I64x, string259=%I64x, first259=%I64x, 1st+4K='%s'", nl, 0
            jmp     allDone
            
badStrstr2: mov     rdx, r11
            call    print
            byte    "%s:Empty string should not match", nl, 0
            
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
            
; Time the strstr1 and strstr1 functions (naive versions):
            
            tstStr strstr1, first, rsi, rdi, naive
            tstStr strrstr1, second, rsi, rdi, naive

; Time the cmpsb version:

            tstStr strstr2, first, rsi, rdi, cmpsb
            
; Time the PCMPISTRI version here:

            cmp     hasSSE42, 1
            je      doPSTR
            
            call    print
            byte    "CPU does not support SSE42 "
            byte    "instructions, skipping strstr2"
            byte    nl, 0
            jmp     noSSE42

; Test variants that are pcmpistri-based:
            
doPSTR:     
            tstStr strstr3, first, rsi, rdi, pcmpistri
            tstStr strrstr3, second, rsi, rdi, pcmpistri

; Test C standard library code:

noSSE42:
            tstStr strstr4, first, rsi, rdi, SSE
            tstStr strstr, first, rcx, rdx, C stdlib

; Note: strrstr, technically, isn't part of the C standard
; library. GCC supports it, but MSVC does not, which is
; why there is no test code here for the C stdlib version.
            

allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
