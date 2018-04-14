; hello-1.asm
; Output the message "Hello, low level world" on the display

        .model tiny                                 ; memory model used for COM
        .code                                       ; beginning of the code segment
        org    100h                                 ; initial counter value
start:  mov    ah,9                                 ; DOS's function number - in DX
        mov    dx,offset message                    ; string address - in DX
        int    21h                                  ; call the DOS system function
        ret                                         ; finish the COM program
message db     "Hello, World!",0Dh,0Ah,'$'          ; string to be displayed
        end    start                                ; The end of the program
