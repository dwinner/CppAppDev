; Listing 5-10
;
; Demonstrate passing parameters in registers


            option  casemap:none

            .data
staticVar   dword   ?

            .code
            externdef someFunc:proc
            
; strfill-  Overwrites the data in a string with a character.
;
;     RDI-  Pointer to zero-terminated string 
;           (e.g., a C/C++ string)
;      AL-  Character to store into the string

strfill     proc
            push    rdi     ; Preserve RDI because it changes
            
            
; While we haven't reached the end of the string

whlNot0:    cmp     byte ptr [rdi], 0
            je      endOfStr

; Overwrite character in string with the character
; passed to this procedure in AL

            mov     [rdi], al

; Move on to the next character in the string and
; repeat this process:

            inc     rdi
            jmp     whlNot0  
	          
endOfStr:   pop     rdi
            ret
strfill     endp
            end