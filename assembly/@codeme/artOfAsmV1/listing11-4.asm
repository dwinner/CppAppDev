; Listing 11-4
;
; Performance test for packed versus unpacked
; instructions. This program times unaligned accesses. 

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 11-4", 0
           

dseg        segment align(64) 'DATA'

; Aligned data types:

            align   64
alignedData byte    64 dup (0)
dseg        ends



            
            .code
            externdef printf:proc
            
; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp


; Used for debugging:

print       proc
            push    rax
            push    rbx
            push    rcx
            push    rdx
            push    r8
            push    r9
            push    r10
            push    r11
            
            push    rbp
            mov     rbp, rsp
            sub     rsp, 40
            and     rsp, -16
            
            mov     rcx, [rbp+72]   ;Return address
            call    printf
            
            mov     rcx, [rbp+72]
            dec     rcx
skipTo0:    inc     rcx
            cmp     byte ptr [rcx], 0
            jne     skipTo0
            inc     rcx
            mov     [rbp+72], rcx
            
            leave
            pop     r11
            pop     r10
            pop     r9
            pop     r8
            pop     rdx
            pop     rcx
            pop     rbx
            pop     rax
            ret
print       endp



            
                    
            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbx
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage
            
            call    print
            byte    "Starting", nl, 0
            
            mov     rcx, 4000000000 ;4,000,000,000
rptLp:      mov     rbx, 15
rptLp2:
            movups  xmm0, xmmword ptr [rdx+rbx*1]
            movupd  xmm0, real8 ptr   [rdx+rbx*1]
            movdqu  xmm0, xmmword ptr [rdx+rbx*1]
            vmovups ymm0, ymmword ptr [rdx+rbx*1]
            vmovupd ymm0, ymmword ptr [rdx+rbx*1]
            vmovdqu ymm0, ymmword ptr [rdx+rbx*1]
            vmovups zmm0, zmmword ptr [rdx+rbx*1]
            vmovupd zmm0, zmmword ptr [rdx+rbx*1]
            dec     rbx
            jns     rptLp2

            dec     rcx
            jnz     rptLp
            
            call    print
            byte    "Done", nl, 0
             
allDone:    leave
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end