; stringAlloc.asm
;
;  Allocates storage for a string object on the
; heap (by calling the C Standard Library malloc
; function). Then it initializes the string object
; and returns a pointer to that object.
;
; Entry:
;
;           EAX     maximum size of string (characters).
;
; Exit:
;           RAX     Pointer to allocated and initialize
;                   string.
;
; Error:
;           Returns NULL in EAX if there was a memory
;           allocation error.

            include string.inc

            .code
            externdef malloc:proc   ;C stdlib
            
stringAlloc proc

; May need to change these if operating on AVX
; CPU and you want to preserve YMM registers.

xmm0Save    textequ <[rbp-16]>
xmm1Save    textequ <[rbp-32]>
xmm2Save    textequ <[rbp-48]>
xmm3Save    textequ <[rbp-64]>
xmm4Save    textequ <[rbp-80]>
xmm5Save    textequ <[rbp-96]>

; Because this code calls a Microsoft ABI function,
; we need to save all the volatile registers so
; we can restore their values later.

            push    rbx
            push    rcx
            push    rdx
            push    r8
            push    r9
            push    r10
            push    r11
            push    rbp
            mov     rbp, rsp
            sub     rsp, 512        ;Shadow area, reg save area.
            and     rsp, -16        ;16-byte align.
            
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
            movdqu  xmm2Save, xmm2
            movdqu  xmm3Save, xmm3
            movdqu  xmm4Save, xmm4
            movdqu  xmm5Save, xmm5
            
; Save original maxLength count so we
; can fill in the string object's maxLength
; later.

            mov     ebx, eax        ;Zero extends into rbx!

; Add 63 bytes to maxLength. This allows for:
;
; 16 bytes: For the strObject structure at the start of string.
; 1  byte:  For the zero-terminating byte
; 15 bytes: For padding before the object to ensure the whole
;             structure is 16-byte aligned
; 15 bytes: For padding at the end of the structure to ensure
;             that it is (at least) a multiple of 16 bytes long.
; 16 bytes: Always have an extra 16 bytes at the end to allow
;           unaligned accesses of 16 bytes starting with the
;           very last character in the string.

            add     eax, 63
            mov     ecx, eax        ;Zero extends into RCX
            call    malloc          ;C stdlib function
            test    rax, rax        ;Test for error return.
            jz      allDone
            
            mov     rdx, rax        ;Save allocation pointer
            add     rax, 15         ;Align on 16-byte boundary.
            and     rax, -16
            
; Save away the original allocation pointer:

            mov     [rax].strObject.allocPtr, rdx
            
; Save away the maximum length:

            mov     [rax].strObject.maxLength, ebx
            
; Initialize string length to zero:

            mov     [rax].strObject.strLength, 0
            
; Emit the zero-terminating byte:

            mov     [rax].strObject.charData, 0
            
; Return a pointer to the character data, not the
; beginning of the string structure:

            
            lea     rax, [rax].strObject.charData
            
allDone:    movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            movdqu  xmm3, xmm3Save
            movdqu  xmm4, xmm4Save
            movdqu  xmm5, xmm5Save
            leave
            pop     r11
            pop     r10
            pop     r9
            pop     r8
            pop     rdx
            pop     rcx
            pop     rbx
            ret
            

stringAlloc endp
            end
