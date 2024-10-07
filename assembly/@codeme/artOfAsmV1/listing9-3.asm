; Listing 9-3
;
; Numeric to hex string functions

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 9-3", 0
fmtStr1     byte    "qtoStr: Value=%I64x, string=%s"
            byte    nl, 0
            
            .data
buffer      byte    20 dup (?)
            
            .code
            externdef printf:proc
            
; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp






; qtoStr-
;
;  Converts the qword in RAX to a string of hexadecimal
; characters and stores them at the buffer pointed at
; by RDI. Buffer must have room for at least 17 bytes.
; This function zero-terminates the string.

hexChar             byte    "0123456789ABCDEF"

qtoStr      proc
            push    rdi
            push    rcx
            push    rdx
            push    rax             ;Leaves LO dword at [rsp]
                            
            lea     rcx, hexChar

            xor     edx, edx        ;Zero extends!
            shld    rdx, rax, 4
            shl     rax, 4
            mov     dl, [rcx][rdx*1] ;Table lookup
            mov     [rdi], dl
                            
; Emit bits 56-59:

            xor     edx, edx
            shld    rdx, rax, 4
            shl     rax, 4
            mov     dl, [rcx][rdx*1]
            mov     [rdi+1], dl
                            
; Emit bits 52-55:

            xor     edx, edx
            shld    rdx, rax, 4
            shl     rax, 4
            mov     dl, [rcx][rdx*1]
            mov     [rdi+2], dl
            
; Emit bits 48-51:

            xor     edx, edx
            shld    rdx, rax, 4
            shl     rax, 4
            mov     dl, [rcx][rdx*1]
            mov     [rdi+3], dl
            
; Emit bits 44-47:

            xor     edx, edx
            shld    rdx, rax, 4
            shl     rax, 4
            mov     dl, [rcx][rdx*1]
            mov     [rdi+4], dl
                            
; Emit bits 40-43:

            xor     edx, edx
            shld    rdx, rax, 4
            shl     rax, 4
            mov     dl, [rcx][rdx*1]
            mov     [rdi+5], dl
            
; Emit bits 36-39:

            xor     edx, edx
            shld    rdx, rax, 4
            shl     rax, 4
            mov     dl, [rcx][rdx*1]
            mov     [rdi+6], dl
            
; Emit bits 32-35:

            xor     edx, edx
            shld    rdx, rax, 4
            shl     rax, 4
            mov     dl, [rcx][rdx*1]
            mov     [rdi+7], dl
            
; Emit bits 28-31:

            xor     edx, edx
            shld    rdx, rax, 4
            shl     rax, 4
            mov     dl, [rcx][rdx*1]
            mov     [rdi+8], dl
            
; Emit bits 24-27:

            xor     edx, edx
            shld    rdx, rax, 4
            shl     rax, 4
            mov     dl, [rcx][rdx*1]
            mov     [rdi+9], dl
            
; Emit bits 20-23:

            xor     edx, edx
            shld    rdx, rax, 4
            shl     rax, 4
            mov     dl, [rcx][rdx*1]
            mov     [rdi+10], dl
            
; Emit bits 16-19:

            xor     edx, edx
            shld    rdx, rax, 4
            shl     rax, 4
            mov     dl, [rcx][rdx*1]
            mov     [rdi+11], dl
            
; Emit bits 12-15:

            xor     edx, edx
            shld    rdx, rax, 4
            shl     rax, 4
            mov     dl, [rcx][rdx*1]
            mov     [rdi+12], dl
            
; Emit bits 8-11:

            xor     edx, edx
            shld    rdx, rax, 4
            shl     rax, 4
            mov     dl, [rcx][rdx*1]
            mov     [rdi+13], dl
            
; Emit bits 4-7:

            xor     edx, edx
            shld    rdx, rax, 4
            shl     rax, 4
            mov     dl, [rcx][rdx*1]
            mov     [rdi+14], dl
            
; Emit bits 0-3:

            xor     edx, edx
            shld    rdx, rax, 4
            shl     rax, 4
            mov     dl, [rcx][rdx*1]
            mov     [rdi+15], dl
            
; Zero-terminate string:

            mov     byte ptr [rdi+16], 0
            


            pop     rax
            pop     rdx
            pop     rcx
            pop     rdi
            ret
qtoStr      endp



            
; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rdi
            push    rbp
            mov     rbp, rsp
            sub     rsp, 64         ;Shadow storage
            
; Because all the (x)toStr functions preserve RDI,
; we only need to do the following once:
 
            lea     rdi, buffer
            
            
; Demonstrate call to qtoStr:

            mov     rax, 0aa55FF0022334455h
            call    qtoStr
            
            lea     rcx, fmtStr1
            mov     rdx, rax
            mov     r8, rdi
            call    printf

            
            leave
            pop     rdi
            ret     ;Returns to caller
        
asmMain     endp
            end