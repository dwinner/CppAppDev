; Listing 11-2
;
; Test for AVX2 Instructions

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 11-2", 0
           

            .data
maxFeature  dword   ?
VendorID    byte    14 dup (0)

            
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

            xor     eax, eax
            cpuid
            mov     maxFeature, eax
            mov     dword ptr VendorID, ebx 
            mov     dword ptr VendorID[4], edx 
            mov     dword ptr VendorID[8], ecx
            
            lea     rdx, VendorID
            mov     r8d, eax
            call    print
            byte    "CPUID(0): Vendor ID='%s', max feature=0%xh", nl, 0
            
            
; Leaf function 1 is available on all CPUs that support
; CPUID, no need to test for it. 

            mov     eax, 1
            cpuid
            mov     r8d, edx
            mov     edx, ecx
            call    print
            byte    "cpuid(1), ECX=%08x, EDX=%08x", nl, 0
            
; Most likely, leaf function 7 is supported on all modern CPUs
; (e.g., x86-64), but we'll test its availability nonetheless.

            cmp     maxFeature, 7
            jb      Unsupported
            
            mov     eax, 7
            xor     ecx, ecx
            cpuid
            mov     edx, ebx
            mov     r8d, ecx
            call    print
            byte    "cpuid(1), EBX=%08x, ECX=%08x", nl, 0
            
; Test for extended bit manipulation instructions 
; (BMI1 and BMI2):

            and     ebx, 108h       ;Test bits 3 & 8
            cmp     ebx, 108h       ;Both must be set
            jne     Unsupported
            call    print
            byte    "CPU supports BMI1 & BMI2", nl, 0
            jmp     allDone 
             

Unsupported:
            call    print
            byte    "CPU does not support BMI1 & BMI2 "
            byte    "instructions", nl, 0
             
allDone:    leave
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end