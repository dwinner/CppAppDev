
; Listing 17-7
;
; strspn and strcspn Functions

            include    zstrings.inc
            include    aoalib.inc
            includelib aoalib.lib

; Number of timing loop iterations:

repeatCnt   =       500000

            .const
ttlStr      byte    "Listing 17-7", 0


            .data
temp        oword   ?
startTime   dword   ?
hasSSE42    byte    0 ;True if CPU supports SSE4.2 instrs


; Macro to generate a sequence of characters
; that are largely different:

genChrs     macro   count
            local   cntr, chr
cntr        =       0
chr         =       'b'
            while   cntr lt count
            byte    chr
chr         =       chr+1
            if      chr gt 'o'
chr         =       'a'
            endif
cntr        =       cntr + 1
            endm
            endm
            
genStr      macro   theStr
            exitm   <"&theStr">
            endm
            
genVal      macro   theValue
            exitm   <&theValue>
            endm


; Generate a whole bunch of strings for
; testing purposes:


strLength   =       0
            while   strLength lt 200
theString   catstr  <string>, %strLength
theString   byte    'a'
            genChrs %strLength-1
            
substr1     catstr  <result>, %strLength
substr1     =       $-theString
            byte    'ABC012_'
substr1     catstr  <result2_>, %strLength
substr1     =       $-theString
            byte    '.'
            byte    0
            
nameStr     catstr  <name>, %strLength
nameStr     byte    "name", genStr(%strLength), 0
            
strLength   =       strLength + 1
            endm


; Character set strings the application uses
; to test the various functions:

cs1         byte    "abcdefghijklmno", 0    ;15 chars

cs2         byte    81h,82h,83h,84h,85h
            byte    "zyxwvutsrqpomnlkjihg"
            byte    "fedcba", 0             ;31 chars
            
cs3         byte    "!@#$%^&*()|+-=~`"
            byte    "zyxwvutsrqpomnlk"
            byte    "jihgfedcba<,>/?", 0    ;47 chars
            
cs4         byte    "abcdefghijklmnopqrst"
            byte    "uvwxyzABCDEFGHIJKLMN"
            byte    "OPQRSTUVWXYZ01234567"
            byte    "89_", 0                ;63 chars

; Note: cs5 is used to test the strcspn functions.
            
cs5         byte    "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 0


            
            .code
            externdef time:proc

            
;**************************************************
;
;  Macro to test the various string span functions
;
; Arguments:
;
;  func     strspn/strcspn function to call
;  which    Character set string to use
;  result   Result name prefix to use
;  srcReg   Register holding source address
;  setReg   Register holding charset address
;  txt      Text description of function
;
;  Executes specified strcmp function 500,000 * 256 times
; so we can time its operation
;

tstSpn      macro   func, which, result, strReg, setReg, txt
            local   strSpnLp, badSpn, badSpn2, allDone
            local   badStrstr2

            call    print
            byte    "Timing &func with character set "
            byte    genStr(which)
            byte    nl, 0
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            mov     startTime, eax  ;Save starting time

; Call the string copy function over and over again:

            mov     ebx, repeatCnt
strSpnLp:

; Generate 256 calls to the string length function, one
; for each of the 256 strings created earlier:

lpCnt       =       0
            while   lpCnt lt 200
            
; Test a string (less than 16 chars):

nameStr     catstr  <name>, %lpCnt
strName     catstr  <string>, %lpCnt
            lea     strReg, strName ;String to search thru
            
; Test the "abcdefghijklmnopqrstuvwxyz" character set:

spnIndex    catstr  <&result>, %lpCnt

            lea     setReg, which
            mov     r14, spnIndex   ;Expected index value
            call    func            ;Call str(c)spn function.
            lea     rcx, nameStr
            cmp     rax, -1
            jz      badSpn
            cmp     rax, r14
            jne     badSpn2
            
                                                
lpCnt       =       lpCnt + 1
            endm
            
            dec     ebx
            jnz     strSpnLp
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            sub     eax, startTime  
            
            mov     edx, eax
            call    print
            byte    "&txt "
            byte    "&which"
            byte    " time = %d seconds", nl, 0
            jmp     allDone
            
badSpn:     mov     rdx, rcx
            mov     r8, strReg
            mov     r9, setReg 
            call    print
            byte    "&func; "
            byte    "%s: Failed when skipping in '%s' for cset(%s)", nl, 0
            jmp     allDone
            
badSpn2:    mov     rdx, rcx
            mov     r8, strReg
            mov     r9, setReg
            mov     r10, rax
            mov     r11, r14 
            call    print
            byte    "&func; "
            byte    "%s:Failed when skipping in '%s' for cset(%s)", nl
            byte    "Got %d, expected %d", nl, 0
            
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
            push    r14
            push    r15
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
            
            tstSpn strspn1,  cs1, result,   rsi, rdi, naive
            tstSpn strspn1,  cs2, result,   rsi, rdi, naive
            tstSpn strspn1,  cs3, result,   rsi, rdi, naive
            tstSpn strspn1,  cs4, result2_, rsi, rdi, naive
            tstSpn strcspn1, cs5, result,   rsi, rdi, naive
            
            tstSpn strspnPS,  cs1, result,   rsi, rdi, bit set
            tstSpn strspnPS,  cs2, result,   rsi, rdi, bit set
            tstSpn strspnPS,  cs3, result,   rsi, rdi, bit set
            tstSpn strspnPS,  cs4, result2_, rsi, rdi, bit set
            tstSpn strcspnPS, cs5, result,   rsi, rdi, bit set

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
            tstSpn strspn3,  cs1, result,   rsi, rdi, pcmpistri
            tstSpn strspn3,  cs2, result,   rsi, rdi, pcmpistri
            tstSpn strspn3,  cs3, result,   rsi, rdi, pcmpistri
            tstSpn strspn3,  cs4, result2_, rsi, rdi, pcmpistri
            tstSpn strcspn3, cs5, result,   rsi, rdi, pcmpistri


; Test the SSE code:

noSSE42:
            tstSpn strspn4,  cs1, result,   rsi, rdi, SSE
            tstSpn strspn4,  cs2, result,   rsi, rdi, SSE
            tstSpn strspn4,  cs3, result,   rsi, rdi, SSE
            tstSpn strspn4,  cs4, result2_, rsi, rdi, SSE
            tstSpn strcspn4, cs5, result,   rsi, rdi, SSE

; Test C standard library code:
 
            tstSpn strspn,  cs1, result,   rcx, rdx, C stdlib
            tstSpn strspn,  cs2, result,   rcx, rdx, C stdlib
            tstSpn strspn,  cs3, result,   rcx, rdx, C stdlib
            tstSpn strspn,  cs4, result2_, rcx, rdx, C stdlib
            tstSpn strcspn, cs5, result,   rcx, rdx, C stdlib


allDone:    leave
            pop     r15
            pop     r14
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
