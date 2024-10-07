; Listing 4-5
;
; Demonstration of lack of type
; checking in assembly language
; pointer access

          option  casemap:none

nl        =       10
maxLen    =     256

          .const
ttlStr    byte    "Listing 4-5", 0
prompt	  byte	  "Input a string: ", 0
fmtStr    byte    "%d: Hex value of char read: %x", nl, 0
        
          .data
bufPtr    qword   ?
bytesRead qword   ?
        
        .code
        externdef readLine:proc
        externdef printf:proc
        externdef malloc:proc
        externdef free:proc


; Return program title to C++ program:

         public getTitle
getTitle proc
         lea rax, ttlStr
         ret
getTitle endp

; Here is the "asmMain" function.

        
        public  asmMain
asmMain proc
        push    rbx     ;Preserve RBX

; "Magic" instruction offered without
; explanation at this point:

        sub     rsp, 40

; C standard library malloc function
; Allocate sufficient characters
; to hold a line of text input
; by the user:

        mov     rcx, maxLen     ; Allocate 256 bytes
        call    malloc
        mov     bufPtr, rax     ; Save pointer to buffer
        
; Read a line of text from the user and place in
; the newly allocated buffer:

	lea	rcx, prompt	; Prompt user to input
	call	printf		;  a line of text.

        mov     rcx, bufPtr     ; Pointer to input buffer
        mov     rdx, maxLen     ; Maximum input buffer length
        call    readLine        ; Read text from user
        cmp     rax, -1         ; Skip output if error
        je      allDone
        mov     bytesRead, rax  ;Save number of chars read
        
; Display the data input by the user:

        xor     rbx, rbx        ;Set index to zero
dispLp: mov     r9, bufPtr      ;Pointer to buffer
        mov     rdx, rbx        ;Display index into buffer
        mov     r8d, [r9+rbx*1] ;Read dword rather than byte!
        lea     rcx, fmtStr
        call    printf
        
        inc     rbx             ;Repeat for each char in buffer
        cmp     rbx, bytesRead
        jb      dispLp

; Free the storage by calling
; C standard library free function.
;
; free( bufPtr );

allDone:
        mov     rcx, bufPtr
        call    free


        add     rsp, 40
        pop     rbx     ;Restore RBX
        ret     ;Returns to caller
asmMain endp
        end