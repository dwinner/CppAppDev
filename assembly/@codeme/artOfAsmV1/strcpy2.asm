; strcpy2.asm
;
;  String copy using the PCMPISTRI instruction
;
; On entry:
;
;  RSI-     Points at source string
;  RDI-     Points at destination buffer.

            include zstrings.inc
            
            .code

strcpy2     proc
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

            dec     rsi     
            jmp     testAlign
                            
alignLoop:  mov     al, [rsi]
            mov     [rdi][rsi*1], al
            cmp     al, 0
            je      allDone
            
testAlign:  inc     rsi
            mov     rax, rsi
            and     rax, 0fh
            jnz     alignLoop
            
            sub     rsi, 16         ;Due to add below
            jmp     sc4Lp
            
            align   dword
sc4Lp:      add     rsi, 16

; Fetch next 16 bytes of string and see if any one
; of them is zero. Note that zero flag is set if
; any byte pointed at by RSI is zero.

            movdqa  xmm1, [rsi]
            pcmpistri xmm0, xmm1, EqualEach
            jz      endOfStr
            
; Didn't have a zero-terminating byte in the
; current block so copy the data to the
; destination. Note: we don't have to worry about
; overwriting data beyond the end of the string
; here because we haven't yet reached the end
; of the string.

            movdqu  [rdi][rsi*1], xmm1
            jmp     sc4Lp
            
; Okay, we found a zero byte in the current
; block of 16 bytes. Only copy data up to
; the zero byte. Note that RCX contains the
; index of the zero byte. Increment this by
; 1 so this is the number of bytes to copy
; (including the zero byte).

endOfStr:
            call    copy16

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
strcpy2     endp
            end
