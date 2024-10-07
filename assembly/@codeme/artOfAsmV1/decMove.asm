; decMove.asm
;
; Decrementing move (also known as moveRight).
; Moves a block of memory from a lower address
; to a higher address.
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
decMove     proc
            cmp     rcx, 48         ;If greater than 48 bytes
            jae     sseMove         ; use SSE instructions.

; If fewer than 48 bytes, just use an MOVSB instruction
; and avoid all the overhead of using the SSE instructions.

            lea     rsi, [rsi][rcx*1-1]     ;Point at end.
            lea     rdi, [rdi][rcx*1-1]     ;Point at end.
            std
    rep     movsb
            cld             ;System assumes direction is clear
            ret

; If moving 48 bytes or more, then use SSE instructions
; to copy the data.
            
sseMove:    sub     rsp, 32         ;Preserve XMM0 and XMM1.
            movdqu  [rsp], xmm0
            movdqu  [rsp+16], xmm1
            
            lea     rsi, [rsi][rcx*1-32]    ;Point at end.
            lea     rdi, [rdi][rcx*1-32]    ;Point at end.
            sub     rdi, rsi        ;So we only have to dec RSI.
            sub     rcx, 32
moveLp:     movdqu  xmm0, [rsi]
            movdqu  xmm1, [rsi+16]
            movdqu  [rdi][rsi*1], xmm0
            movdqu  [rdi+16][rsi*1], xmm1
            sub     rsi, 32         ;Skip to next block of bytes.
            sub     rcx, 32         ;Sets flags like CMP.
            jae     moveLp
            add     rcx, 32         ;Make up for original sub.
            add     rsi, 32
            
; If there are 16 bytes or more left to copy, move 16 of them
; using XMM0.

            cmp     rcx, 16
            jb      useMovsb
            
            sub     rsi, 16
            sub     rcx, 16
            movdqu  xmm0, [rsi]
            movdqu  [rdi][rsi*1], xmm0
            
useMovsb:   add     rdi, rsi        ;Restore RDI pointer
            jrcxz   allDone         ;Quit if RCX=0
            dec     rsi
            dec     rdi
            std
    rep     movsb                   ;Copy remaining bytes
            cld                     ;Return return clear


allDone:    
            movdqu  xmm0, [rsp]
            movdqu  xmm1, [rsp+16]
            add     rsp, 32
            ret
decMove     endp
            end
