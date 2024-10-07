; Listing 19-1
;
; BT and TEST cset membership tests

            include    aoalib.inc
            include    cset.inc
            includelib aoalib.lib

            .const
ttlStr      byte    "Listing 19-1", 0

            .data
startTime   dword   0

            staticCset emptySet
            
            .code
            externdef time:proc
            
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
            
; Time the BT instruction:

            xor     rcx, rcx        ;NULL argument to time
            call    time
            mov     startTime, eax   
            
            mov     rdx, 50000000   ;50,000,000
timeLp2:    mov     ecx, 0
timeLp:     mov     eax, ecx
            bt      dword ptr emptySet, eax
            inc     cl
            jnz     timeLp
            dec     rdx
            jnz     timeLp2
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            sub     eax, startTime  
            
            mov     edx, eax
            call    print
            byte    "BT time = %d seconds", nl, 0
            
; Time the TEST instruction:                         

            xor     rcx, rcx        ;NULL argument to time
            call    time
            mov     startTime, eax   
            
            mov     rdx, 50000000
timeLp3:    mov     ebx, 0
timeLp4:    mov     ecx, ebx
            mov     esi, ebx
            and     ecx, 7
            shr     esi, 3
            mov     eax, 1
            shl     eax, cl
            lea     rdi, emptySet
            test    al, byte ptr [rdi][rsi]

            inc     bl
            jnz     timeLp4
            dec     rdx
            jnz     timeLp3
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            sub     eax, startTime  
            
            mov     edx, eax
            call    print
            byte    "TEST time = %d seconds", nl, 0
                                     
allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
