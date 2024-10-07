; Listing 3-1
;
; Demonstrate address expressions

        option  casemap:none

nl      =       10  ;ASCII code for newline


                .const
ttlStr          byte    'Listing 3-1', 0
fmtStr1		byte	'i[0]=%d ', 0
fmtStr2		byte	'i[1]=%d ', 0
fmtStr3		byte	'i[2]=%d ', 0		
fmtStr4		byte	'i[3]=%d',nl, 0



        .data
i	byte    0, 1, 2, 3

        .code
        externdef printf:proc

; Return program title to C++ program:

         public getTitle
getTitle proc
         lea rax, ttlStr
         ret
getTitle endp


        
; Here is the "asmMain" function.

        
        public  asmMain
asmMain proc
	push	rbx
                           
; "Magic" instruction offered without
; explanation at this point:

        sub     rsp, 48


	lea	rcx, fmtStr1
	movzx	rdx, i[0]
	call	printf
                
	lea	rcx, fmtStr2
	movzx	rdx, i[1]
	call	printf
                
	lea	rcx, fmtStr3
	movzx	rdx, i[2]
	call	printf
                
	lea	rcx, fmtStr4
	movzx	rdx, i[3]
	call	printf	
	
                

        add     rsp, 48
	pop	rbx
        ret     ;Returns to caller
asmMain endp
        end