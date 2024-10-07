; Listing 18-4
;
; stringCpy function.

            option     casemap:none
            include    aoalib.inc
            include    string.inc
            includelib aoalib.lib

nl          =       10

            .const
ttlStr      byte    "Listing 18-4", 0

            .data
startTime   dword   ?
            
            
            
; Generate a whole bunch of strings for
; testing purposes.
;
; This pair of nested loop generates 255
; strings, with lengths from 1..255. The
; character data at each position is the
; index into the string (e.g., string5
; has the data 1, 2, 3, 4, 5, 0).

name0       byte    "name0", 0
            staticStr string0, 1

; Generate string1..string255:

strLength   =       1
            while   strLength lt 256
            local   nameStr
strName     catstr  <string>, %strLength
nameStr     catstr  <name>, %strLength

; Output the name of the string, e.g.,
;
;           strDcl  name1, 12, "name1"

            strDcl  nameStr, 12, txt2str(%strName)


; Output the string data. At least one
; byte of data. After the first byte,
; emit the index into the string, e.g.,
; 2, 3, 4, ...

            strBgn  %strName, %strLength+8
            byte    1
sIndex      =       2
            while   sIndex le strLength
            byte    sIndex
sIndex      =       sIndex + 1
            endm
            strEnd  %strName
            
                        
; Move on to the next string we're generating
; in the compile-time while loop.

strLength   =       strLength + 1
            endm  


            
; Generate destination strings for
;
;  destX        byte X+1 dup (0)
;
; The before and after labels are for bytes the
; test code uses to determine if the stringCpy
; procedure overwrites data before or after the
; string.

strLength   =       0
            while   strLength lt 256
            local   strName

strName     catstr  <dest>, %strLength
            staticStr strName, %strLength+8
            
strLength   =       strLength + 1
            endm  
            

            .code
            externdef time:proc
            
            
;**********************************************************
;            
; strCmp-
;
;   Simple strCmp, high performance is not needed here.
;
; RSI points at source 1
; RDI points at source 2
;
; Returns flags set according to string comparison result.

strCmp      proc
            push    rcx
            push    rsi
            push    rdi
            
            mov     ecx, [rsi-sohs].strObject.strLength
            cmp     ecx, [rdi-sohs].strObject.strLength
            jb      gotSmaller
            mov     ecx, [rdi-sohs].strObject.strLength
gotSmaller: inc     ecx     ;Include zero byte at end
            cld
    repe    cmpsb
                        
            pop     rdi
            pop     rsi
            pop     rcx
            ret
strCmp      endp
 
 
;**********************************************************
;
; testSC-
;
;  Macro to test the various string copy functions
;
; Arguments:
;
;  func     stringCpy function to call
;  txt      Text description of function
;
;  Executes specified stringCpy function 5,000,000 * 256 times
; so we can time its operation
;

testSC      macro   func, txt
            local   strCpyLp, allDone, badCpy, strOvfl 

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
strName     catstr  <string>, %lpCnt
destStr     catstr  <dest>, %lpCnt

            lea     rsi, strName     ;Just copy the string
            lea     rdi, destStr     ; to destStr
            call    func             ;Call stringCpy function.
            jc      strOvfl
lpCnt       =       lpCnt + 1
            endm
            
            dec     ebx
            jnz     strCpyLp
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            sub     eax, startTime  
            
            mov     edx, eax
            call    print
            byte    "&txt stringCpy time = %d seconds", nl, 0
       
       
; Before comparing strings, initialize all the dest
; data to a recognizable value:

initCnt     =       1
            while   initCnt lt 256
destStr     catstr  <dest>, %initCnt
            
; The initial value to write is 0ffh for
; all strings except string255; use 80h
; for that string. Also write this value to
; the beforeDestX and afterDestX variables:

            if      initCnt ne 255
            mov     al, 0ffh
            else
            mov     al, 80h
            endif
            
            lea     rdi, destStr
            mov     ecx, initCnt
            call    stringInit
    
initCnt     =       initCnt + 1
            endm
              
; Okay, generate code to test the copy operations:       
       
lpCnt       =       0
            while   lpCnt lt 256
destStr     catstr  <dest>, %lpCnt
strName     catstr  <string>, %lpCnt
nameStr     catstr  <name>, %lpCnt            

            lea     rsi, strName    ;Just copy the string
            lea     rdi, destStr    ; to destStr
            call    func            ;Call stringCpy function.
            jc      strOvfl

            lea     rsi, strName 
            lea     rdi, destStr
            call    strCmp
            
            lea     rdx, nameStr
            lea     rsi, strName
            lea     rdi, destStr
            
            jne     badCpy          ;Flags from strCmp
                        
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
            byte    "Bad stringCpy on %s, "
            byte    "src=%I64x, srcdata=%016I64x, "
            byte    "destdata=%016I64x, " 
            byte    "b4aftr:%04x", nl, 0
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

            testSC  stringCpy1, movsb
            testSC  stringCpy2, SSE

                         
allDone:    leave
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
