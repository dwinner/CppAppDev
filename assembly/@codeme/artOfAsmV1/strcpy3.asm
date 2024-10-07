; strcpy3-
;
;  String copy using the SSE instructions
;
; On entry:
;
;  RSI-     Points at source string
;  RDI-     Points at destination buffer.

            include zstrings.inc
            
            .code
strcpy3     proc
            push    rdi
            push    rsi
            push    rcx
            push    rax
            sub     rsp, 32
            movdqu  [rsp], xmm0
            movdqu  [rsp+16], xmm1 
            
; We need an XMMsrc1 register. The value
; doesn't matter but as we're searching
; for a zero byte, we may as well set
; xmm0 to all zeroes:

            pxor    xmm0, xmm0      ;Zero out XMM0
            
; Combine RSI and RDI so that we only have
; to increment RSI in the loop:

            sub     rdi, rsi
            
; Before we do anything else, we need to
; align RSI to a 16-byte boundary. This
; serves a couple purposes:
;
; 1. It allows us to load data from
;    memory using the movdqa instruction
;    which significantly speeds up the
;    algorithm.
;
; 2. It allows us to ignore the possibility
;    of crossing an MMU page boundary when
;    the current 16-byte block contains a
;    zero (and we're loading data beyond
;    the end of the string). Because RSI
;    is 16-byte aligned, the entire 16-
;    byte block will be in the same page
;    in memory.
;
; The drawback to this is that we have
; to manually copy the first 0..15 bytes
; using scalar instructions (slow). As
; a large percentage of strings are short,
; this impacts performance.
;           
; Note: If the following loop encounters
; a zero byte, it turns out that the
; zero byte gets written to memory twice-
; once by the following code and once by
; the movsb later. Small price to pay
; to avoid an extra jump (or convoluted
; code) in the loop below.  
            
            dec     rsi     
            jmp     testAlign
                            
alignLoop:  mov     al, [rsi]
            mov     [rdi][rsi*1], al
            cmp     al, 0
            je      allDone
            
testAlign:  inc     rsi
            test    rsi, 0fh
            jnz     alignLoop
            jmp     enterLp
            
            align   dword
sc4Lp:      movdqu  [rdi][rsi*1], xmm2
            add     rsi, 16

; Fetch next 16 bytes of string and see if any one
; of them is zero. Note that zero flag is set if
; any byte pointed at by RSI is zero.

enterLp:    movdqa    xmm1, [rsi]
            movdqa    xmm2, xmm1
            pcmpeqb   xmm1, xmm0

; There is a zero byte somewhere in the current block
; of 16 bytes. Copy all the data up to (and including)
; the zero byte, then we're done.

            pmovmskb  rax, xmm1
            test      eax, eax
            jz        sc4Lp
            bsf       rcx, rax 
            call      copy16            

; Restore registers and leave:

allDone:    
            movdqu  xmm1, [rsp+16]
            movdqu  xmm0, [rsp]
            add     rsp, 32
            pop     rax
            pop     rcx
            pop     rsi
            pop     rdi
            ret             
strcpy3     endp
            end
