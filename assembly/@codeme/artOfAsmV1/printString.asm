; printString-
;
;  A "helper" function that prints a string in mixed
; ASCII/Hexadecimal format for debugging purposes.
;
; On Entry:
;
;   RSI- points at the string to print.

            include    string.inc
	include	   aoalib.inc
	includelib aoalib.lib

            .code
printString proc
            push    rcx
            push    rdx
            push    rsi
            
            call    print
            byte    "'", 0
            
            mov     ecx, [rsi-sohs].strObject.strLength
            test    ecx, ecx
            jz      endOfString
            
prtString:  movzx   edx, byte ptr [rsi]
            
            cmp     dl, 20h
            je      lastHex
            jb      asHex
            cmp     dl, 80h
            jae     asHex
            call    print
            byte    "%c", 0
            jmp     charDone
            
asHex:      call    print
            byte    " %02x", 0
            jmp     charDone
            
lastHex:    call    print
            byte    " %02x ", 0
charDone:   inc     rsi
            dec     rcx
            jnz     prtString
            
endOfString:
            call    print
            byte    "'", nl, 0
            
            pop     rsi
            pop     rdx
            pop     rcx     
            ret
printString endp
            end
