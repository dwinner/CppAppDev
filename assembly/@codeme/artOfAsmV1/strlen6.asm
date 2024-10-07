            
;***************************************************************
;            
; strlen6.asm
;
;  String length using the PCMPISTRI function.
; This variant 16-byte aligns the RSI register
; before entering the main loop to avoid accessing
; a new MMU page while loading 16 bytes that contain
; the zero-terminating byte (i.e., if the zero byte
; is within 15 bytes of the end of the current MMU
; page).
;
; RSI-      Points at string
;
; Returns:
;
; RAX-      String Length

            include zstrings.inc

            .code
strlen6     proc
xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>

            sub     rsp, 32
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
            push    rcx
            push    rsi
            
            pxor    xmm0, xmm0      ;Zero out XMM0
            

; Force RSI to the start of the current 16-byte block.

            mov       rax, rsi
            and       rsi, -16      ;0fff...f0h
            and       rax, 0fH      ;Offset to start of data
            shl       rax, 4        ; for index into maskOut0s
            lea       rcx, maskOut0s
            movdqu    xmm1, [rsi]   ;Get bytes to check
            por       xmm1, [rcx][rax*1] ;Remove garbage
             
            
            pcmpistri xmm0, xmm1, EqualEach
            jz        ComputeLen    ; Quit, if zero byte
                                
 
sl4Lp:      add     rsi, 16

; Fetch next 16 bytes of string and see if any one
; of them is zero. Note that zero flag is set if
; any byte pointed at by RSI is zero.

            pcmpistri xmm0, [rsi], EqualEach
            jnz     sl4Lp
            
; Compute length of string as the number of
; 16-byte blocks we've skipped plus the index
; to the zero byte:

ComputeLen:
 
            mov     rax, rsi        ;Current 16-byte blk adrs.
            sub     rax, [rsp]      ;Original string pointer.
            add     rax, rcx        ;Add in index
            pop     rsi
            pop     rcx
            movdqu  xmm1,   xmm1Save
            movdqu  xmm0,   xmm0Save
            add     rsp, 32
            ret
strlen6     endp
            end