; incMove.asm
;
; Incrementing move (also known as moveLeft).
; Moves a block of memory from a higher address
; to a lower address.
;
; RSI-      Pointer to source block
; RDI-      Pointer to destination block
; RCX-      Byte count
;
; Does not preserve RSI, RDI, nor RCX.
; Leaves the direction flag cleared.

            option     casemap:none
            include    string.inc
            include    aoalib.inc

            .code
incMove     proc
            cmp     rcx, 48         ;If greater than 48 bytes
            jae     sseMove         ; use SSE instructions.

; If fewer than 48 bytes, just use an MOVSB instruction
; and avoid all the overhead of using the SSE instructions.

            cld
    rep     movsb
            ret

; If moving 48 bytes or more, then use SSE instructions
; to copy the data.
            
sseMove:    sub     rsp, 32         ;Preserve XMM0 and XMM1.
            movdqu  [rsp], xmm0
            movdqu  [rsp+16], xmm1
            
            sub     rdi, rsi        ;So we only have to inc RSI.
            sub     rcx, 32         ;Helps with loop control.
moveLp:     movdqu  xmm0, [rsi]
            movdqu  xmm1, [rsi+16]
            movdqu  [rdi][rsi*1], xmm0
            movdqu  [rdi+16][rsi*1], xmm1
            add     rsi, 32         ;Skip to next block of bytes.
            sub     rcx, 32         ;Sets flags like CMP.
            jae     moveLp
            add     rcx, 32         ;Make up for earlier sub.
            
            cmp     rcx, 16
            jb      useMovsb
            
            movdqu  xmm0, [rsi]
            movdqu  [rdi][rsi*1], xmm0
            add     rsi, 16
            sub     rcx, 16
            
useMovsb:   jrcxz   allDone         ;Quit if RCX=0
            add     rdi, rsi        ;Restore RDI pointer
            cld
    rep     movsb                   ;Copy remaining bytes
                    

allDone:    movdqu  xmm0, [rsp]
            movdqu  xmm1, [rsp+16]
            add     rsp, 32
            ret
incMove     endp
            end
