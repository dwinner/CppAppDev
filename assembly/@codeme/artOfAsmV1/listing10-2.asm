; Listing 10-1
;
; Real string to floating-point conversion

        option  casemap:none

false       =       0
true        =       1
tab         =       9
nl          =       10

            .const
ttlStr      byte    "Listing 10-1", 0
fmtStr1     byte    "strToR10: str='%s', value=%e", nl, 0
           
table	byte	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"

            .data
r8Val       real8   ?

            
            .code
            externdef printf:proc
            
; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp


; Used for debugging:

print       proc
            push    rax
            push    rbx
            push    rcx
            push    rdx
            push    r8
            push    r9
            push    r10
            push    r11
            
            push    rbp
            mov     rbp, rsp
            sub     rsp, 40
            and     rsp, -16
            
            mov     rcx, [rbp+72]   ;Return address
            call    printf
            
            mov     rcx, [rbp+72]
            dec     rcx
skipTo0:    inc     rcx
            cmp     byte ptr [rcx], 0
            jne     skipTo0
            inc     rcx
            mov     [rbp+72], rcx
            
            leave
            pop     r11
            pop     r10
            pop     r9
            pop     r8
            pop     rdx
            pop     rcx
            pop     rbx
            pop     rax
            ret
print       endp



            
                    
            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbx
            push    rbp
            mov     rbp, rsp
            sub     rsp, 56         ;Shadow storage
            
	lea	rbx, table
	xor	rax, rax
	xlat
	mov	rdx, rax
	call	print
	byte	"a=%c", nl, 0
 

             
allDone:    leave
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end