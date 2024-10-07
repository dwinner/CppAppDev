; Listing 5-3
;
; Preserving registers (failure) example


               option  casemap:none

nl             =       10

              .const
ttlStr        byte    "Listing 5-3", 0
space         byte    " ", 0
asterisk      byte    '*, %d', nl, 0
        
              .code
	      externdef printf:proc

; Return program title to C++ program:

              public getTitle
getTitle      proc
              lea rax, ttlStr
              ret
getTitle      endp



; print40Spaces-
; 
;  Prints out a sequence of 40 spaces
; to the console display.

print40Spaces proc
              sub  rsp, 48   ;"Magic" instruction
	      mov  ebx, 40
printLoop:    lea  rcx, space
 	      call printf
	      dec  ebx
	      jnz  printLoop ;Until ebx==0
	      add  rsp, 48   ;"Magic" instruction
              ret
print40Spaces endp


; Here is the "asmMain" function.

              public  asmMain
asmMain       proc
              push    rbx
		
; "Magic" instruction offered without
; explanation at this point:

              sub     rsp, 40

              mov     rbx, 20
astLp:        call    print40Spaces
              lea     rcx, asterisk
	      mov     rdx, rbx
	      call    printf
              dec     rbx
	      jnz     astLp

              add     rsp, 40
	      pop     rbx
              ret     ;Returns to caller
asmMain       endp
              end