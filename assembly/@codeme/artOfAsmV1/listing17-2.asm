
; Listing 17-2
;
; memset functions


            include    zstrings.inc
            include    aoalib.inc
            includelib aoalib.lib

            .const
ttlStr      byte    "Listing 17-2", 0

            
            

            .data
startTime   dword   ?


; Include an extra byte at the beginning of the
; array so we can ensure that the memset function
; doesn't overwrite any data in front of the array:

Leader      byte    0

; What we want:
;   dataArray byte 1000000 dup (?)
;
; MASM has a design defect that assembles large
; static arrays like this very slowly. So we
; will cheat and use the following code. Note
; that the "org" directive sets the location
; counter to the value specified as the operand.
; "$" means "current location counter value.
; Therefore, "$+(1024*1024)-2" advances the location
; counter by 1 MB - 2 bytes. So our array
; (including the two bytes before and after
; the ORG directive) is 1 MB total bytes.

dataArray   byte    0
            org     $+(1024*1024)-2
            byte    0
            
; Include extra data at the end to
; use as a sentinel, to make sure the
; memset functions did not write any
; data beyond the array:

Sentinel    byte    0


            
            .code
            externdef time:proc
            externdef memset:proc
                        

;**********************************************************
;    
; A slow variant of memcmp to test the functions above
; to make sure they did their job.

memcmp      proc   
            cmp     Sentinel, 0
            jne     badSentinel
            
            cmp     Leader, 0
            jne     badLeader

            lea     rdi, dataArray
            mov     rcx, 1024*1024
mcLoop:     cmp     al, [rdi][rcx*1 - 1]
            jne     badCmp
            dec     rcx
            jnz     mcLoop
            
            call    print
            byte    "Memory compare successful", nl, 0
            ret

badCmp:     lea     rdx, [rcx-1]
            movzx   r8, al
            movzx   r9, byte ptr [rdi][rcx*1 - 1]
            call    print
            byte    "Error at offset %d, "
            byte    "expected %d, got %d", nl, 0
            ret
            
badSentinel:
            call    print
            byte    "Code overwrote a byte beyond the "
            byte    "end of the array.", nl, 0
            ret
            
badLeader:
            call    print
            byte    "Code overwrote a byte before the "
            byte    "start of the array.", nl, 0
            ret
memcmp      endp
            
;***********************************************************
;
; testMemset
;
;  A macro that generates test code for
; a variant of the memset function.
;
; Arguments:
;
;  func     The function to test
;  destReg  Register holding address of memory block
;  initReg  Register holding initial value for block
;  init     Initial value for block
;  cntReg   Register holding number of bytes
;  txt      Text description of function
;

testMemset  macro   func, destReg, initReg, init, cntReg, txt
            local   memsetLp, reset, allDone
            
            call    print
            byte    "Timing &func:", nl, 0
            
            mov     Leader, 0
            mov     Sentinel, 0
            xor     rcx, rcx        ;NULL argument to time
            call    time
            mov     startTime, eax  ;Save starting time
            
            mov     ebx, 1000000    ;1,000,000
reset:      lea     destReg, dataArray
            mov     cntReg, 1024*1024
memsetLp:   push    destReg
            push    cntReg
            mov     initReg, init
            call    func
            pop     cntReg
            pop     destReg
            dec     ebx
            jz      allDone
            inc     destReg
            dec     cntReg
            jz      reset
            jmp     memsetLp
allDone:
            xor     rcx, rcx        ;NULL argument to time
            call    time
            sub     eax, startTime  
            
            mov     edx, eax
            call    print
            byte    "&txt memset time = %d seconds", nl, 0
            
            mov     al, init
            call    memcmp
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

; Time the memset1 function (naive version):

            testMemset memset1, rdi, al,  1, rcx, naive         
            testMemset memset2, rdi, al,  2, rcx, stosb         
            testMemset memset3, rdi, al,  3, rcx, SSE         
            testMemset memset4, rdi, al,  1, rcx, AVX         
            testMemset memset,  rcx, rdx, 4, r8,  C stdlib         


allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
