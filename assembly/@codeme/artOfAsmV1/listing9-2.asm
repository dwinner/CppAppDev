; Listing 8-5
;
; Numeric to hex string functions

        option  casemap:none

nl          =       10

            .const
ttlStr      byte    "Listing 8-5", 0
fmtStr1     byte    "btoStr: Value=%I64x, string=%s"
            byte    nl, 0
            
fmtStr2     byte    "wtoStr: Value=%I64x, string=%s"
            byte    nl, 0
            
fmtStr3     byte    "dtoStr: Value=%I64x, string=%s"
            byte    nl, 0
            
fmtStr4     byte    "qtoStr: Value=%I64x, string=%s"
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


; btoh-
;
; This procedure converts the binary value
; in the AL register to 2 hexadecimal
; characters and returns those characters
; in the AH (HO hibble) and AL (LO nibble)
; registers. 

btoh        proc

            mov     ah, al    ;Do HO nibble first
            shr     ah, 4     ;Move HO nibble to LO
            or      ah, '0'   ;Convert to char
            cmp     ah, '9'+1 ;Is it 'A'..'F'?
            jb      AHisGood
            
; Convert 3ah..3fh to 'A'..'F'

            add     ah, 7

; Process the LO nibble here
            
AHisGood:   and     al, 0Fh   ;Strip away HO nibble
            or      al, '0'   ;Convert to char
            cmp     al, '9'+1 ;Is it 'A'..'F'?
            jb      ALisGood
            
; Convert 3ah..3fh to 'A'..'F'

            add     al, 7   
ALisGood:   ret
                        
btoh        endp



; btoStr-
;
;  Converts the byte in AL to a string of hexadecimal
; characters and stores them at the buffer pointed at
; by RDI. Buffer must have room for at least 3 bytes.
; This function zero-terminates the string.

btoStr      proc
            push    rax
            call    btoh            ;Do conversion here
            
; Create a zero-terminated string at [RDI] from the
; two characters we converted to hex format:

            mov     [rdi], ah
            mov     [rdi+1], al
            mov     byte ptr [rdi+2], 0
            pop     rax
            ret
btoStr      endp



; wtoStr-
;
;  Converts the word in AX to a string of hexadecimal
; characters and stores them at the buffer pointed at
; by RDI. Buffer must have room for at least 5 bytes.
; This function zero-terminates the string.

wtoStr      proc
            push    rdi
            push    rax     ;Note: leaves LO byte at [rsp]
            
; Use btoStr to convert HO byte to a string:

            mov     al, ah
            call    btoStr

            mov     al, [rsp]       ;Get LO byte
            add     rdi, 2          ;Skip HO chars
            call    btoStr
            
            pop     rax
            pop     rdi
            ret
wtoStr      endp


; dtoStr-
;
;  Converts the dword in EAX to a string of hexadecimal
; characters and stores them at the buffer pointed at
; by RDI. Buffer must have room for at least 9 bytes.
; This function zero-terminates the string.

dtoStr      proc
            push    rdi
            push    rax     ;Note: leaves LO word at [rsp]
            
; Use wtoStr to convert HO word to a string:

            shr     eax, 16
            call    wtoStr

            mov     ax, [rsp]       ;Get LO word
            add     rdi, 4          ;Skip HO chars
            call    wtoStr
            
            pop     rax
            pop     rdi
            ret
dtoStr      endp


; qtoStr-
;
;  Converts the qword in RAX to a string of hexadecimal
; characters and stores them at the buffer pointed at
; by RDI. Buffer must have room for at least 17 bytes.
; This function zero-terminates the string.

qtoStr      proc
            push    rdi
            push    rax     ;Note: leaves LO dword at [rsp]
            
; Use dtoStr to convert HO dword to a string:

            shr     rax, 32
            call    dtoStr

            mov     eax, [rsp]      ;Get LO dword
            add     rdi, 8          ;Skip HO chars
            call    dtoStr
            
            pop     rax
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
            
; Demonstrate call to btoStr:

            mov     al, 0aah
            call    btoStr
            
            lea     rcx, fmtStr1
            mov     edx, eax
            mov     r8, rdi
            call    printf
            
; Demonstrate call to wtoStr:

            mov     ax, 0a55ah
            call    wtoStr
            
            lea     rcx, fmtStr2
            mov     edx, eax
            mov     r8, rdi
            call    printf
            
; Demonstrate call to dtoStr:

            mov     eax, 0aa55FF00h
            call    dtoStr
            
            lea     rcx, fmtStr3
            mov     edx, eax
            mov     r8, rdi
            call    printf
            
; Demonstrate call to qtoStr:

            mov     rax, 1234567890abcdefh
            call    qtoStr
            
            lea     rcx, fmtStr4
            mov     rdx, rax
            mov     r8, rdi
            call    printf

            
            leave
            pop     rdi
            ret     ;Returns to caller
        
asmMain     endp
            end