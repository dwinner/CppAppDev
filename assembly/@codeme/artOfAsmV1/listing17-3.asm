
; Listing 17-3
;
; strcpy functions

            include    zstrings.inc
            include    aoalib.inc
            includelib aoalib.lib


            .const
ttlStr      byte    "Listing 17-3", 0
            

            .data
startTime   dword   ?
hasSSE42    byte    0 ;True if CPU supports SSE4.2 instrs

; mkStr-
;
; Convert a text object to a string literal

mkStr       macro   textObject
strLiteral  textequ <"&textObject">
            exitm   strLiteral
            endm
            
; Generate a whole bunch of strings for
; testing purposes.
;
; This pair of nested loop generates 255
; strings, with lengths from 1..255. The
; character data at each position is the
; index into the string (e.g., string5
; has the data 1, 2, 3, 4, 5, 0).

name0       byte    "name0", 0
string0     byte    0

; Generate string1..string255:

strLength   =       1
            while   strLength lt 256
            local   nameStr
strName     catstr  <string>, %strLength
nameStr     catstr  <name>, %strLength

; Output the name of the string, e.g.,
;
;  name1    byte    "name1", 0

nameStr     byte    mkStr(%strName), 0


; Output the string data. At least one
; byte of data. After the first byte,
; emit the index into the string, e.g.,
; 2, 3, 4, ...

strName     byte    1
sIndex      =       2
            while   sIndex le strLength
            byte    sIndex
sIndex      =       sIndex + 1
            endm

; Zero-terminate the string:
            
            byte    0
            
; Move on to the next string we're generating
; in the compile-time while loop.

strLength   =       strLength + 1
            endm  


; Emit string data to hold the destination strings:
; Note that test code overwrites data from 
; beforeDest0 to afterDest255, so only dest string
; stuff should go in between.
            
beforeDest0 byte    0
dest0       byte    0
afterDest0  byte    0
            byte    0

; Generate destination strings for
;
;  beforeDestX  byte 0
;  destX        byte X+1 dup (0)
;  afterDestX   byte 0
;               byte 0 ;Extra 0 byte, just because...
;
; The before and after labels are for bytes the
; test code uses to determine if the strcpy
; procedure overwrites data before or after the
; string.

strLength   =       1
            while   strLength lt 256

strName     catstr  <beforeDest>, %strLength
strName     byte    0
strName     catstr  <dest>, %strLength
strName     byte    strLength+1 dup (0)
strName     catstr  <afterDest>, %strLength
strName     byte    0
            byte    0
            
strLength   =       strLength + 1
            endm  


            .code

;**********************************************************
;            
; strcmp-
;
;   Naive strcmp, high performance is not needed here.
;
; RSI points at source 1
; RDI points at source 2
;
; Returns AL=0 if equal, AL=1 if not equal.

strcmp      proc
            push    rsi
            push    rdi
            
strcmpLp:   mov     al, [rsi]
            cmp     al, 0
            je      testEq
            cmp     al, [rdi]
            jne     strNE
            inc     rsi
            inc     rdi
            jmp     strcmpLp
            
testEq:     cmp     al, [rdi]
            je      strIsEq
            
strNE:      mov     al, 1   ;non-zero works fine
strIsEq:    pop     rdi
            pop     rsi
            ret
strcmp      endp




;**********************************************************
;
; testSC-
;
;  Macro to test the various string copy functions
;
; Arguments:
;
;  func     strcpy function to call
;  srcReg   Register holding source address
;  destReg  Register holding destination address
;  txt      Text description of function
;
;  Executes specified strcpy function 5,000,000 * 256 times
; so we can time its operation
;

testSC      macro   func, srcReg, destReg, txt
            local   strCpyLp, allDone, badCpy 
            local   overwroteB4, overwroteAftr

            call    print
            byte    "Timing &func", nl, 0
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            mov     startTime, eax  ;Save starting time

; Call the string copy function over and over again:

            mov     ebx, 5000000
strCpyLp:

; Generate 256 calls to the string length function, one
; for each of the 256 strings created earlier (lengths
; 0..255):

lpCnt       =       0
            while   lpCnt lt 256
            local   strName, destStr
strName     catstr  <string>, %lpCnt
destStr     catstr  <dest>, %lpCnt

            lea     srcReg, strName  ;Just copy the string
            lea     destReg, destStr ; to destStr
            call    func             ;Call strcpy function.
lpCnt       =       lpCnt + 1
            endm
            
            dec     ebx
            jnz     strCpyLp
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            sub     eax, startTime  
            
            mov     edx, eax
            call    print
            byte    "&txt strcpy time = %d seconds", nl, 0
       
       
; Before comparing strings, initialize all the dest
; data to a recognizable value:

            mov     beforeDest0, 0ffh
            mov     afterDest0, 0ffh
            mov     dest0, 0ffh

initCnt     =       1
            while   initCnt lt 256
            local   strName, destStr,b4Dest,aftrDest
b4Dest      catstr  <beforeDest>, %initCnt
destStr     catstr  <dest>, %initCnt
aftrDest    catstr  <afterDest>, %initCnt
            
; The initial value to write is 0ffh for
; all strings except string255; use 80h
; for that string. Also write this value to
; the beforeDestX and afterDestX variables:

            if      initCnt ne 0ffh
            mov     al, 0ffh
            else
            mov     al, 80h
            endif
            mov     b4Dest, al
            mov     aftrDest, al
            
            lea     rdi, destStr
            mov     rcx, initCnt+1  ;Include zero terminator
    rep     stosb
    
initCnt     =       initCnt + 1
            endm
              
; Okay, generate code to test the copy operations:       
       
lpCnt       =       0
            while   lpCnt lt 256
            local   strName, destStr,b4Dest,aftrDest
b4Dest      catstr  <beforeDest>, %lpCnt
destStr     catstr  <dest>, %lpCnt
aftrDest    catstr  <afterDest>, %lpCnt
strName     catstr  <string>, %lpCnt
nameStr     catstr  <name>, %lpCnt

            if      lpCnt ne 0ffh
            mov     al, 0ffh
            else
            mov     al, 80h
            endif
            mov     b4Dest, al
            mov     aftrDest, al
            

            lea     srcReg, strName  ;Just copy the string
            lea     destReg, destStr ; to destStr
            call    func             ;Call strcpy function.

            lea     rsi, strName 
            lea     rdi, destStr
            call    strcmp
            
            lea     rdx, nameStr
            lea     rsi, strName
            lea     rdi, destStr
            lea     rbx, aftrDest   
            cmp     al, 0
            jne     badCpy
            
            if      lpCnt ne 0ffh
            cmp     b4Dest, 0ffh
            jne     overwroteB4
            cmp     aftrDest, 0ffh
            jne     overwroteAftr
            else
            cmp     b4Dest, 80h
            jne     overwroteB4
            cmp     aftrDest, 80h
            jne     overwroteAftr
            endif
            
lpCnt       =       lpCnt + 1
            endm
            
            jmp     allDone
            
badCpy:     mov     r8, rsi
            mov     r9, [rsi]
            mov     r10, [rdi]
            movzx   r11, byte ptr [rdi-1]
            shl     r11, 8
            mov     r11b, [rbx] 
            call    print
            byte    "Bad strcpy on %s, src=%I64x, srcdata=%016I64x, destdata=%016I64x, " 
            byte    "b4aftr:%04x", nl, 0
            jmp     allDone

overwroteB4:
            call    print
            byte    "Bad strcpy on %s, overwrote before", nl, 0
            jmp     allDone

overwroteAftr:
            call    print
            byte    "Bad strcpy on %s, overwrote after", nl, 0

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
            sub     rsp, 64         ;Shadow storage
            and     rsp, -16
 
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
            
            
            
; Time the strcpy1 function (naive version):

            testSC  strcpy1, rsi, rdi, naive
            
            cmp     hasSSE42, 1
            je      doPCMP
            
            call    print
            byte    "CPU does not support SSE42 "
            byte    "instructions, skipping strcpy2"
            byte    nl, 0
            jmp     noSSE42
            
doPCMP:     testSC  strcpy2, rsi, rdi, pcmpistri
 
noSSE42:    testSC  strcpy3, rsi, rdi, SSE
            testSC  strcpy, rcx, rdx, C stdlib           

allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
