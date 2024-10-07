; stringTokenize.asm
;
; Function that breaks up a string into
; component strings and fills an array
; with pointers to the components.
;
; On entry:
;
;  RSI-     Pointer to source string to scan.
;  RAX-     Offset into source string to begin scan.
;  RDI-     Pointer to pcset variable containing delimiter
;                       characters (used to break up the source string
;           into its components).
;  RBX-             Pointer to an array of pointers; this function
;           will fill in this array with pointers to the
;           component strings.
;  RCX-             Maximum number of elements in the array of
;           pointers.
;
; On Exit
;
;  RAX-     Number of elements created in the array of
;           pointers.
;
; CF=0      Successful operation.
; CF=1      Illegal operands on input, memory allocation
;           fault, or too many string components for the
;           destination array.
;
; Note:
;           If this function succeeds, it allocates storage for
;   all the component strings on the heap. It is the
;   caller's responsibility to free up those strings
;   (by calling stringFree) when it is done using those
;   strings.
;
;   If the function fails, it will clean up any allocated
;   strings on the heap.
;
;
; Change the following to 
;
;scanTo     textequ    <skipToCset>
;scanner    textequ    <skipCset>
;
; to avoid using SSE4.2 instructions.

scanTo          textequ        <fscanToCset>
scanner         textequ        <fscanCset>

substring      textequ         <substring2> ;Use SSE variant

               include    aoalib.inc
               include    cset.inc

            
               .code
            
stringTokenize proc
               push rbx
               push rcx
               push rsi
               push rdi
               push r13     ;Max components
               push r14     ;Will number of components
               push r15

               xor  r14, r14  ;Initialize component count
               mov  eax, eax  ;Clear RAX HO bits
               mov  r13d, ecx ;Need RCX for other things

; Check to see if the offset into the string is out of bounds:

            cmp     eax, [rsi-sohs].strObject.strLength
            jae     cleanFail

; Scan past any delimiter characters:
            
skipDelims:
            call    scanner
            
; If at end of source string, we're done:

            cmp     byte ptr [rsi][rax*1], 0
            je      success
            
            mov     r15, rax     ;Save component start offset
            call    scanTo       ;Scan to next delimiter char

            inc     r14          ;Bump component count
            cmp     r14, r13     ;Exceeded array size?
            jae     dirtyFail2
            
            push    rax          ;Save end of component
            mov     rcx, rax     ;End of component
            sub     rcx, r15     ;Component length
            mov     rax, rcx
            call    stringAlloc  ;Create storage for component
            jc      dirtyFail    ;If memory allocation error

; Need to copy the component (substring) from the source
; to the newly allocated storage on the heap. Note: code
; doesn't check for error code on return from substring
; because no error is possible (we control the input parameters
; and they are correct at this point).
            
            push    rdi                 ;Preserve cset ptr
            mov     rdi, rax            ;Destination address
            mov     [rbx][r14*8-8], rax ;Save ptr in dest array
            mov     rax, r15            ;Offset to component
            call    substring         ;RCX contains length
            pop     rdi               ;Restore cset ptr
            pop     rax               ;Restore component end
            jmp     skipDelims

; Branch here if we successfully created all the
; component strings (could be zero of them!)

success:    mov     rax, r14        ;Return count in RAX
            clc
            jmp     allDone    
                       
; Return down here if there is a failure of some sort:
;
; dirtyFail: there are strings allocated on the heap.
; This code must free them before leaving:

dirtyFail:     pop  rax             ;Clean up stack
               inc  r14             ;annul dec, below       
dirtyFail2:    dec  r14
               xor  rcx, rcx
dirtyFailLp:   cmp  rcx, r14
               jae  cleanFail
               mov  rax, [rbx][rcx*8]
               call stringFree
               inc  rcx
               jmp  dirtyFailLp
               
cleanFail:     stc
pushfq
allDone:       pop  r15
               pop  r14
               pop  r13
               pop  rdi
               pop  rsi
               pop  rcx
               pop  rbx
               ret
stringTokenize endp
               end
