; Listing 3-2
;
; // Type checking errors

        option  casemap:none

	  .data
pointer   typedef qword
b         byte    ?
d         dword   ?
pByteVar  pointer offset b[2]
pDWordVar pointer offset d+4

        .code

; Here is the "asmMain" function.

        
        public  asmMain
asmMain proc

	mov	rax, pByteVar
	mov	rbx, pDWordVar
	
asmMain endp
        end