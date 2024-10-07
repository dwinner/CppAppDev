; Listing 18-7
;
; Prefix and Suffix Comparison functions.

            option     casemap:none
            include    string.inc
            include    aoalib.inc

            includelib aoalib.lib


            .const
ttlStr      byte    "Listing 18-7", 0

            .data
startTime   dword   ?
hasSSE42    byte    0 ;True if CPU supports SSE4.2 instrs


; Generate a string that can be used as the
; source1 string:

            strBgn  source1, 300
chr         =       1
            while   chr lt 256
            byte    chr
chr         =       chr+1
            endm
            strEnd  source1
            
            


; Macros to generate a sequence of characters
; that are largely different:

genChrs     macro   count
            local   cntr, chr
cntr        =       0
chr         =       1
            while   cntr lt count
            byte    chr
chr         =       chr+1
cntr        =       cntr + 1
            endm    ;while
            endm    ;genChrs

genSufx     macro   count
            local   cntr, chr
cntr        =       0
chr         =       256-count
            while   cntr lt count
            byte    chr
chr         =       chr+1
cntr        =       cntr + 1
            endm    ;while
            endm    ;genChrs

; Generate a sequence of strings that correspond
; to prefixes of each length of source1.
; Generates
;
;  prfx1, prfx2, prfx3, ..., prfx255


strLength   =       1
            while   strLength lt 256
strName     catstr  <prfx>, %strLength

            strBgn  %strName, %strLength+8
            genChrs %strLength
            strEnd  %strName
            
strLength   =       strLength + 1
            endm
            

; Generate another set of prefix strings that
; will return false when tested as a prefix
; string:
;
;  badPrfx1, badPrfx2, badPrfx3, ..., badPrfx255


strLength   =       1
            while   strLength lt 256
strName     catstr  <badPrfx>, %strLength

            strBgn  %strName, %strLength+8
            genChrs %strLength-1
            
            if      strLength ne 255
            byte    strLength+1     ;This char won't match.
            else
            byte    1               ;Special case for 255.
            endif
            strEnd  %strName
            
strLength   =       strLength + 1
            endm
            

; Generate a sequence of strings that correspond
; to suffixes of each length of source1.
; Generates
;
;  sufx1, sufx2, sufx3, ..., sufx255


strLength   =       1
            while   strLength lt 256
strName     catstr  <sufx>, %strLength

            strBgn  %strName, %strLength+8
            genSufx %strLength
            strEnd  %strName
            
strLength   =       strLength + 1
            endm
            

; Generate a sequence of strings that will not
; match as suffixes to source1:
;
; Generates
;
;  badSufx1, badSufx2, badSufx3, ..., badSufx255


strLength   =       1
            while   strLength lt 256
strName     catstr  <badSufx>, %strLength

            strBgn  %strName, %strLength+8
            genSufx %strLength-1
            byte    01h             ;Won't match
            strEnd  %strName
            
strLength   =       strLength + 1
            endm
            

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
;  Executes specified strcmp function 5,000,000 * 256 times
; so we can time its operation
;

tstPrfx     macro   func, nPrefix, badPrefix, txt
            local   strCmpLp, allDone
            local   notEql, wasEql, notLess, notGreater

            call    print
            byte    "Timing &func", nl, 0
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            mov     startTime, eax  ;Save starting time

; Call the string copy function over and over again:

            mov     ebx, 5000000
strCmpLp:

; Generate 256 calls to the string length function, one
; for each of the 256 strings created earlier (lengths
; 1..255):

lpCnt       =       1
            while   lpCnt lt 256
            
strName     catstr  <&nPrefix>, %lpCnt
            lea     rsi, strName
            lea     rdi, source1
            call    func
            jne     notEql
            
strName     catstr  <&badPrefix>, %lpCnt
            lea     rsi, strName
            lea     rdi, source1
            call    func
            je      wasEql
            
lpCnt       =       lpCnt + 1
            endm
            
            dec     ebx
            jnz     strCmpLp
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            sub     eax, startTime  
            
            mov     edx, eax
            call    print
            byte    "&txt time = %d seconds", nl, 0
            jmp     allDone
       
notEql:     call    print
            byte    "String ", nl, 0
            push    rsi
            lea     rsi, source1
            call    printString
            pop     rsi
            call    print
            byte    nl, "does not contain the "
            ifidn   <&nPrefix>,<prfx>
            byte    "prefix", nl, 0
            else
            byte    "suffix", nl, 0
            endif
            call    printString
            call    print
            byte    nl, 0
            jmp     allDone
       
wasEql:     call    print
            byte    "String ", nl, 0
            push    rsi
            lea     rsi, source1
            call    printString
            pop     rsi
            call    print
            byte    nl, "should not contain the "
            ifidn   <&nPrefix>,<prfx>
            byte    "prefix", nl, 0
            else
            byte    "suffix", nl, 0
            endif
            call    printString
            call    print
            byte    nl, 0
            jmp     allDone
            
             
                                        
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
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage

; Check for the presence of those features before running.
;
; Leaf function 1 is available on all CPUs that support
; CPUID, no need to test for it.  

            mov     eax, 1
            cpuid
            and     ecx, SSE42      ;Test bits 19 & 20
            cmp     ecx, SSE42      ;Both must be set
            sete    hasSSE42
            
 
 
            tstPrfx prefix1, prfx, badPrfx, cmpsb prefix
            tstPrfx suffix1, sufx, badSufx, cmpsb suffix
            tstPrfx prefix2, prfx, badPrfx, SSE prefix
            tstPrfx suffix2, sufx, badSufx, SSE suffix
            
; Time the PCMPISTRI vesion here:

            cmp     hasSSE42, 1
            je      doPSTR
            
            call    print
            byte    "CPU does not support SSE42 "
            byte    "instructions, skipping prefix3"
            byte    nl, 0
            jmp     noSSE42

; Test variants that are pcmpistri-based:
            
doPSTR:     
            tstPrfx prefix3, prfx, badPrfx, pcmpistri prefix
            tstPrfx suffix3, sufx, badSufx, pcmpistri suffix


; Test the SSE code:

noSSE42:


                         
allDone:
            leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
