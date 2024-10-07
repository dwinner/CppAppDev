; Listing 19-3
;
; BTR versus AND/NOT to remove a character from a cset.

            include    aoalib.inc
            include    cset.inc
	includelib aoalib.lib

            .const
ttlStr      byte    "Listing 19-3", 0

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
            
; Time the BTR instruction:

            xor     rcx, rcx        ;NULL argument to time
            call    time
            mov     startTime, eax   
            
            mov     rdx, 50000000   ;50,000,000
timeLp2:    mov     ecx, 0
timeLp:     mov     eax, ecx
            btr     dword ptr emptySet, eax
            inc     cl
            jnz     timeLp
            dec     rdx
            jnz     timeLp2
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            sub     eax, startTime  
            
            mov     edx, eax
            call    print
            byte    "BTR time = %d seconds", nl, 0
            
; Time the AND/NOT implementation:                         

            xor     rcx, rcx        ;NULL argument to time
            call    time
            mov     startTime, eax   
            
            mov     rdx, 50000000
timeLp3:    mov     ebx, 0
timeLp4:    mov     esi, ebx
            mov     ecx, ebx
            shr     esi, 3
            and     ecx, 7
            mov     al, 1
            lea     rdi, emptySet
            shl     al, cl
            not     al
            and      byte ptr [rdi][rsi], al 

            inc     bl
            jnz     timeLp4
            dec     rdx
            jnz     timeLp3
            
            xor     rcx, rcx        ;NULL argument to time
            call    time
            sub     eax, startTime  
            
            mov     edx, eax
            call    print
            byte    "AND/NOT time = %d seconds", nl, 0
            
                         
allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
