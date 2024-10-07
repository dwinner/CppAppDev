; findStr2.asm
;
;  findStr function using pcmpistri instruction.
;
; RSI-      Points at haystack (string to search through).
; RAX-      Offset to begin search.
; RDI-      Points at needle (string to search for).
;
; Returns:
;
; RAX-      Offset into string where needle was found,
;           -1 if not found.
;
; ZF=1      If found needle.
; ZF=0      If needle not found.

	include	string.inc

            .code
findStr2    proc

xmm0Save    textequ <[rsp]>
xmm1Save    textequ <[rsp+16]>
xmm2Save    textequ <[rsp+32]>

            push    rbp     ;Just used as a gen-purpose reg.
            push    rbx
            push    rcx
            push    rdi
            push    rsi
            sub     rsp, 48
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
            movdqu  xmm2Save, xmm2
            
; If the starting offset plus the needle length is beyond 
; the end of the string, then we must always fail:

            mov     ecx, [rdi-sohs].strObject.strLength
            add     ecx, eax
            cmp     ecx, [rsi-sohs].strObject.strLength
            ja      matchFailed

; If needle is empty string, always succeed:
            
            mov     bh, [rdi] ;1st needle char.
            cmp     bh, 0
            jz      ndlHasNull

; Adjust start of search to include offset into haystack.

            add     rsi, rax

; Load first 16 bytes of needle into XMM0 (needle is
; 16-byte aligned!)

            movdqa  xmm0, xmmword ptr [rdi]

; Compare 1st 16 bytes of the needle against the
; current haystack position:

            sub       rsi, 16
cmpNdl1st:  add       rsi, 16
ndl1st:     movdqu    xmm1, xmmword ptr [rsi]
            pcmpistri xmm0, xmm1, EqualOrder
            ja        cmpNdl1st            
            jnc       matchFailed   ;If zero byte found.
            
; We've matched the first part of the needle against the
; haystack characters. Now let's see if the rest of the
; needle matches. RCX contains the index to the start of 
; the match.

            add       rsi, rcx      ;Point at start of match.       
            lea       rdx, [rsi-16] ;RDX moves ahead in haystk.
            lea       rbp, [rdi-16] ;RBP moves ahead in needle.

; Grab the next 16 bytes from the needle and haystack.
; Then compare them.

cmpNdlHay:  add       rdx, 16
            add       rbp, 16
            movdqu    xmm1, xmmword ptr [rdx]       ;Haystack
            movdqu    xmm2, xmmword ptr [rbp]       ;Needle
            pcmpistri xmm2, xmm1, EqualOrder
            jno       noMatchHay    ;OF set if match at posn 0.
            jns       cmpNdlHay     ;SF set if NULL in XMM2

ndlHasNull: mov     rax, rsi        ;RSI=start of match.
            movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            add     rsp, 48
            pop     rsi
            sub     rax, rsi        ;Compute offset.
            pop     rdi
            pop     rcx
            pop     rbx
            pop     rbp
            cmp     eax, eax        ;ZF=1
            ret

noMatchHay: inc     rsi     ;Move ahead one character and try
            jmp     ndl1st  ; to match 16 bytes again.

matchFailed:movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            add     rsp, 48
            pop     rsi
            pop     rdi
            pop     rcx
            pop     rbx
            pop     rbp
            or      rax, -1         ;ZF=0
            ret

findStr2    endp
            end
