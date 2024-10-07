
; Listing 12-10
;
; Creating a bit mask with blsi and dec 

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 12-10", 0

Masks       equ     this word
            word    not 0111b,            not 00111000b    
            word    not 000111000000b,    not 1110b
            word    not 01110000b,        not 001110000000b   
            word    not 00011100b,        not 11100000b
	
	.data
i	dword	5
AO3Bobjects byte	(200*3)/8 + 2 dup (?)   ; "+2" handles
                                         	; truncation.

            include getTitle.inc
            include print.inc

            .code
            
; Here is the "asmMain" function.

            public  asmMain
asmMain     proc
            push    rbx
            push    rsi
            push    rdi
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage

            mov     eax, 7          ;Value to store
            
            mov     ebx, i          ; Get the index into the array.
            mov     ecx, ebx        ; Use LO 3 bits as index
            and     ecx, 111b       ; into Masks table.
            lea     r8, Masks
            mov     dx, [r8][rcx*2] ; Get bit mask.
        
; Convert index into the array into a bit index.
; To do this, multiply the index by 3:
        
            lea     rbx, [rbx+rbx*2]
        
; Divide by 8 to get the byte index into ebx
; and the bit index (the remainder) into ecx:
        
            shrd    ecx, ebx, 3
            shr     ebx, 3
            rol     ecx, 3
     
; Grab the bits and clear those we're inserting.

            lea     r8, AO3Bobjects
            and     dx, [r8][ rbx*1 ]  

; Put our 3 bits in their proper location.

            shl     ax, cl

; Merge bits into destination.
                      
            or      dx, ax
	 
;Store back into memory.
 
            mov     [r8][rbx*1], dx
            
            mov     edx, dword ptr AO3Bobjects
            call    print
            byte    "value:%x", nl, 0
	                         
allDone:    leave
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
