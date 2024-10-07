; stringFree:
;
;  Deallocates a string allocated on the heap with
; strAlloc. Quietly returns if the strPtr field
; of the string object contains NULL. 
;
; Entry:
;
;           RAX     Pointer to string data allocated
;                   with strAlloc
;

            include string.inc

            .code
            externdef free:proc
            
stringFree  proc

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
            
; Get the original allocation pointer. Note: RAX points
; 16 bytes beyond the start of the strObject data structure,
; hence the -sohs (strObject header size, which is 16) component:

            mov     rcx, [rax-sohs].strObject.allocPtr
            
; This is a bit of defensive programming (optional). Set the 
; allocPtr to NULL after fetching its value. In the *near* 
; future should the code attempt to free this string again, 
; the NULL pointer will help prevent memory management system 
; failures (freeing the same block twice can lead to catastrophic 
; failure). Note, of course, that if the application continues to 
; use this dangling pointer, writing a zero at this point won't 
; help (a future memory allocation request could overwrite this 
; NULL pointer). However, this will help in some circumstances 
; and is probably worth the expense of an extra instruction.

            mov     [rax-sohs].strObject.allocPtr, 0        

; If the allocation pointer was NULL, quietly
; return to caller:

            test    rcx, rcx
            jz      allDone
            
; Okay, all the C standard library free pointer
; to reclaim the storage:

            call    free    ;Pointer already in RCX.
                    
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
stringFree  endp
            end
