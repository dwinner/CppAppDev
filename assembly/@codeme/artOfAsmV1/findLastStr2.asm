; findLastStr2.asm
;
;  findLastStr function using pcmpistri instruction.
;
; RSI-      Points at haystack (string to search through).
; RAX-      Offset to "fence" position in string.
; RDI-      Points at needle (string to search for)
;
; Returns:
;
; RAX-      Offset of match in string, or -1 if no match.
;
; ZF = 1    If matched.
; ZF = 0    If no match.


	include	string.inc
	
            .code
findLastStr2 proc

fence        textequ <r15>

xmm0Save     textequ <[rsp]>
xmm1Save     textequ <[rsp+16]>
xmm2Save     textequ <[rsp+32]>

             push    rbp    ;Just used as a gen-purpose reg.
             push    rbx
             push    rcx
             push    rdi
             push    rsi
             push    r15
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
            
; Compute the address of the fence -- the lowest address
; in memory we will compare against.

            lea     fence, [rsi][rax*1]

; Load the first 16 characters of the needle into XMM0:

            movdqa  xmm0, xmmword ptr [rdi]
            
; Zero-length needle always matches the end of the string.

            mov     ecx, [rsi-sohs].strObject.strLength
            lea     rsi, [rsi][rcx*1]
            cmp     byte ptr [rdi], 0
            jz     ndlHasNull

; The last possible match position in the haystack is
; RSI + haystack_length - needle_length. Initialize
; the pointer into the haystack to that location:
            
            mov     ecx, [rdi-sohs].strObject.strLength
            sub     rsi, rcx

; Compare 1st 16 bytes of the needle against the
; current haystack position. 

cmp1stNdl:  movdqu    xmm1, xmmword ptr [rsi]
            pcmpistri xmm0, xmm1, EqualOrder
            jc        foundEnd

; If no match, move back 16 bytes.

noMatchHay: sub       rsi, 16
            cmp       rsi, fence    ;At fence?
            ja        cmp1stNdl

; If there are 16 or fewer bytes left, make one additional
; comparison at the start of the haystack.

tryAtFence: mov       rsi, fence
            movdqu    xmm1, xmmword ptr [fence]
            pcmpistri xmm0, xmm1, EqualOrder
            jnc       matchFailed ;Will be before haystack.
            
; We're at the fence string.
; We've matched some number of characters in the first
; 16 bytes (starting at RSI+RCX).
; See if the whole needle matches.
; Assumption: match rarely occurs at fence, so just use
; cmpsb here rather than the complexity of pcmpistri.

            add     rsi, rcx
            mov     rbx, rsi        ;Save match posn
            mov     ecx, [rdi-sohs].strObject.strLength
            cld
    repe    cmpsb                   ;Compare strings
            mov     rsi, rbx
            je      ndlHasNull      ;Branch if match
            jmp     matchFailed     ;If no match.
            
            
; Matched substring, or found a zero byte in haystack.
; ECX contains the index to the start of the match.

foundEnd:   mov     eax, ecx      ;Zero extends!
            add     rsi, rcx      ;Point at start of match.
            
; Grab the next 16 bytes from the needle and haystack.
; Then compare them.

            lea       rbx, [rsi-16] ;RBX moves ahead in haystk.
            lea       rbp, [rdi-16] ;RBP moves ahead in needle.

cmpNdlHay:  add       rbx, 16
            add       rbp, 16
            movdqu    xmm1, xmmword ptr [rbx]
            movdqu    xmm2, xmmword ptr [rbp]
            pcmpistri xmm2, xmm1, EqualOrder
            jno       noMatchHay    ;OF set if match at posn 0.
            jns       cmpNdlHay     ;SF set if NULL in XMM2
            
; Successful matches come down here.
;
; ndlHasNull:  RSI points at the matching character.

ndlHasNull:  mov    rax, rsi
             movdqu xmm0, xmm0Save
             movdqu xmm1, xmm1Save
             movdqu xmm2, xmm2Save
             add    rsp, 48
             pop    r15
             pop    rsi
             sub    rax, rsi
             pop    rdi
             pop    rcx
             pop    rbx
             pop    rbp
             cmp    eax, eax        ;ZF=1
             ret
              
matchFailed: movdqu xmm0, xmm0Save
             movdqu xmm1, xmm1Save
             movdqu xmm2, xmm2Save
             add    rsp, 48
             pop    r15
             pop    rsi
             pop    rdi
             pop    rcx
             pop    rbx
             pop    rbp
             or     rax, -1         ;ZF=0
             ret

findLastStr2 endp
             end
