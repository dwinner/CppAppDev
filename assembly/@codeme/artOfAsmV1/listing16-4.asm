; Listing 16-4            
;
; File I/O demonstration:

            include    listing16-4.inc
            include    aoalib.inc   ;To get some constants
            includelib kernel32.lib ;File I/O library


            
            .const
prompt      byte    "Enter (text) filename:", 0
badOpenMsg  byte    "Could not open file", cr, nl, 0

            .data

inHandle    dword   ?
inputLn     byte    256 dup (0)

fileBuffer  byte    4096 dup (0)

            .code

; Activation record for Windows calls.
; Preserve all the volatile registers except RAX.

rcxSave     textequ <[rbp-8]>
rdxSave     textequ <[rbp-16]>
r8Save      textequ <[rbp-24]>
r9Save      textequ <[rbp-32]>
r10Save     textequ <[rbp-40]>
r11Save     textequ <[rbp-48]>
xmm0Save    textequ <[rbp-64]>
xmm1Save    textequ <[rbp-80]>
xmm2Save    textequ <[rbp-96]>
xmm3Save    textequ <[rbp-112]>
xmm4Save    textequ <[rbp-128]>
xmm5Save    textequ <[rbp-144]>
var1        textequ <[rbp-160]>

mkActRec    macro
            push    rbp
            mov     rbp, rsp
            sub     rsp, 256        ;includes shadow storage
            and     rsp, -16        ;Align to 16 bytes
            mov     rcxSave, rcx
            mov     rdxSave, rdx
            mov     r8Save, r8
            mov     r9Save, r9
            mov     r10Save, r10
            mov     r11Save, r11
            movdqu  xmm0Save, xmm0
            movdqu  xmm1Save, xmm1
            movdqu  xmm2Save, xmm2
            movdqu  xmm3Save, xmm3
            movdqu  xmm4Save, xmm4
            movdqu  xmm5Save, xmm5
            endm
            
rstrActRec  macro
            mov     rcx, rcxSave
            mov     rdx, rdxSave
            mov     r8, r8Save 
            mov     r9, r9Save 
            mov     r10, r10Save
            mov     r11, r11Save
            movdqu  xmm0, xmm0Save
            movdqu  xmm1, xmm1Save
            movdqu  xmm2, xmm2Save
            movdqu  xmm3, xmm3Save
            movdqu  xmm4, xmm4Save
            movdqu  xmm5, xmm5Save
            leave
            endm


; getStdOutHandle-
;
; Returns stdout handle in RAX

getStdOutHandle proc
                mkActRec
                mov     rcx, STD_OUTPUT_HANDLE
                call    __imp_GetStdHandle  ;Returns handle
                rstrActRec
                ret
getStdOutHandle endp
                
             

; getStdErrHandle-
;
; Returns stdout handle in RAX

getStdErrHandle proc
                mkActRec
                mov     rcx, STD_ERROR_HANDLE
                call    __imp_GetStdHandle  ;Returns handle
                rstrActRec
                ret
getStdErrHandle endp
                
             

; getStdInHandle-
;
; Returns stdin handle in RAX

getStdInHandle proc
               mkActRec
               mov     rcx, STD_INPUT_HANDLE
               call    __imp_GetStdHandle   ;Returns handle
               rstrActRec
               ret
getStdInHandle endp
                
             

; write-
;
;  Write data to a file handle.
;
; rax- file handle
; rsi- pointer to buffer to write
; rcx- length of buffer to write
;
; Returns:
;
; RAX- Number of bytes actually written
;      or -1 if there was an error
            
write       proc
            mkActRec
            
            mov     rdx, rsi        ;Buffer address
            mov     r8, rcx         ;Buffer length
            lea     r9, var1        ;BytesWritten
            mov     rcx, rax        ;Handle
            xor     r10, r10        ;lpOverlapped is passed
            mov     [rsp+4*8], r10  ; on the stack
            call    __imp_WriteFile
            test    rax, rax        ;See if error
            mov     rax, var1       ;BytesWritten
            jnz     rtnBytsWrtn     ;If RAX was not zero
            mov     rax, -1         ;Return error status

rtnBytsWrtn:
            rstrActRec
            ret
write       endp


; puts-
;
; Outputs a zero-terminated string to standard output device.
;
; RSI-      Address of string to print to standard output.

            .data
stdOutHnd   qword   0
hasSOHndl   byte    0

            .code
puts        proc
            push    rax
            push    rcx
            cmp     hasSOHndl, 0
            jne     hasHandle

            call    getStdOutHandle
            mov     stdOutHnd, rax
            mov     hasSOHndl, 1

; Compute the length of the string:
            
hasHandle:  mov     rcx, -1
lenLp:      inc     rcx
            cmp     byte ptr [rsi][rcx*1], 0
            jne     lenLp
            
            mov     rax, stdOutHnd
            call    write

            pop     rcx
            pop     rax
            ret
puts        endp


; newLn-
;
; Outputs a newline sequence to the standard output device:

newlnSeq    byte    cr, nl

newLn       proc
            push    rax
            push    rcx
            push    rsi
            cmp     hasSOHndl, 0
            jne     hasHandle
            
            call    getStdOutHandle
            mov     stdOutHnd, rax
            mov     hasSOHndl, 1

hasHandle:  lea     rsi, newlnSeq
            mov     rcx, 2
            mov     rax, stdOutHnd
            call    write
                                            
            pop     rsi
            pop     rcx
            pop     rax
            ret
newLn       endp
            

; read-
;
;  Read data from a file handle.
;
; eax- file handle
; rdi- pointer to buffer receive data
; ecx- length of data to read
;
; Returns:
;
; RAX- Number of bytes actually read
;      or -1 if there was an error
            
read        proc
            mkActRec
            
            mov     rdx, rdi        ;Buffer address
            mov     r8, rcx         ;Buffer length
            lea     r9, var1        ;BytesRead
            mov     rcx, rax        ;Handle
            xor     r10, r10        ;lpOverlapped is passed
            mov     [rsp+4*8], r10  ; on the stack
            call    __imp_ReadFile
            test    rax, rax        ;See if error
            mov     rax, var1       ;BytesRead
            jnz     rtnBytsRead     ;If RAX was not zero
            mov     rax, -1         ;Return error status

rtnBytsRead:
            rstrActRec
            ret
read        endp


; open-
;
;  Open existing file for reading or writing:
;
; rsi- Pointer to filename string (zero terminated)
; rax- File access flags
;      (GENERIC_READ, GENERIC_WRITE, or
;       "GENERIC_READ + GENERIC_WRITE")
;
; Returns:
;
; RAX- Handle of open file (or INVALID_HANDLE_VALUE if there
;      was an error opening the file).

open        proc
            mkActRec
            
            mov     rcx, rsi        ;Filename
            mov     rdx, rax        ;Read/Write access
            xor     r8, r8          ;Exclusive access
            xor     r9, r9          ;No special security
            mov     r10, OPEN_EXISTING ;Open an existing
            mov     [rsp+4*8], r10     ; file 
            mov     r10, FILE_ATTRIBUTE_NORMAL
            mov     [rsp+5*8], r10
            mov     [rsp+6*8], r9   ;NULL template file
            call    __imp_CreateFileA
            rstrActRec
            ret
open        endp


; openNew-
;
;  Creates a new file and opens it for writing:
;
; rsi- Pointer to filename string (zero terminated)
;
; Returns:
;
; RAX- Handle of open file (or INVALID_HANDLE_VALUE if there
;      was an error opening the file).

openNew     proc
            mkActRec
            
            mov     rcx, rsi                ;Filename
            mov     rdx, GENERIC_WRITE+GENERIC_WRITE ;Access
            xor     r8, r8                  ;Exclusive access
            xor     r9, r9                  ;No security
            mov     r10, CREATE_ALWAYS      ;Open a new file
            mov     [rsp+4*8], r10 
            mov     r10, FILE_ATTRIBUTE_NORMAL
            mov     [rsp+5*8], r10
            mov     [rsp+6*8], r9           ;NULL template
            call    __imp_CreateFileA
            rstrActRec
            ret
openNew     endp


; closeHandle-
;
; Closes a file specified by a file handle.
;
; RAX- Handle of file to close.

closeHandle proc
            mkActRec
            
            call    __imp_CloseHandle       

            rstrActRec
            ret
closeHandle endp




; getLastError-
;
;  Returns the error code of the last Windows error.
;
; On Return-
;
;  RAX-     Error code

getLastError proc
             mkActRec
             call   __imp_GetLastError
             rstrActRec
             ret
getLastError endp


; stdin_read-
;
; Reads data from the standard input.
;
; RDI- Buffer to receive data
; RCX- Buffer count (note that data input will
;      stop on a newline character if that
;      comes along before RCX characters have
;      been read).
;
; Returns:
;
; RAX- -1 if error, bytes read if successful.       

stdin_read  proc
            .data
hasStdInHnd byte    0
stdInHnd    qword   0
            .code
            mkActRec
            cmp     hasStdInHnd, 0
            jne     hasHandle
            
            call    getStdInHandle
            mov     stdInHnd, rax
            mov     hasStdInHnd, 1
            
hasHandle:  mov     rax, stdInHnd   ;Handle
            call    read
                                            
            rstrActRec
            ret
stdin_read  endp


; stdin_getc-
;
; Read a single character from the standard input.
; Returns character in AL register.

stdin_getc  proc
            push    rdi
            push    rcx
            sub     rsp, 8

            mov     rdi, rsp
            mov     rcx, 1
            call    stdin_read
            test    eax, eax        ;Error on read?
            jz      getcErr
            movzx   rax, byte ptr [rsp]     

getcErr:    add     rsp, 8
            pop     rcx
            pop     rdi                                     
            ret
stdin_getc  endp



; readLn-
; 
; Reads a line of text from the user.
; Automatically processes backspace characters
; (deleting previous characters, as appropriate).
; Line returned from function is zero terminated
; and does not include the ENTER key code (carriage
; return) or line feed.
;
; RDI-      Buffer to place line of text read from user.
; RCX-      Maximum buffer length
;
; Returns:
;
; RAX-      Number of characters read from the user
;           (does not include ENTER key).

readLn      proc
            push    rbx
            
            xor     rbx, rbx        ;Character count
            test    rcx, rcx        ;Allowable buffer is 0?
            je      exitRdLn
            dec     rcx             ;Leave room for 0 byte
readLp:
            call    stdin_getc      ;Read 1 char from stdin
            test    eax, eax        ;Treat error like ENTER
            jz      lineDone
            cmp     al, cr          ;Check for enter key
            je      lineDone
            cmp     al, nl          ;Check for newline code
            je      lineDone
            cmp     al, bs          ;Handle backspace character
            jne     addChar
            
; If a backspace character came along, remove the previous
; character from the input buffer (assuming there is a
; previous character).

            test    rbx, rbx        ;Ignore BS character if no
            jz      readLp          ; chars in the buffer
            dec     rbx
            jmp     readLp

; If a normal character (that we return to the caller),
; then add the character to the buffer if there is
; room for it (ignore the character if the buffer is full).
            
addChar:    cmp     ebx, ecx        ;See if we're at the
            jae     readLp          ; end of the buffer
            mov     [rdi][rbx*1], al ;Save char to buffer
            inc     rbx
            jmp     readLp

; When the user presses the ENTER key (or linefeed) key
; during input, come down here and zero terminate the string.

lineDone:   mov     byte ptr [rdi][rbx*1], 0        
            
exitRdLn:   mov     rax, rbx        ;Return char cnt in RAX
            pop     rbx
            ret
readLn      endp

                                            

         
;**********************************************************
;
; Here is the "asmMain" function.

            
        
            public  asmMain
asmMain     proc
            push    rbx
            push    rsi
            push    rdi
            push    r15
            push    rbp
            mov     rbp, rsp
            sub     rsp, 64         ;Shadow storage
            and     rsp, -16

; Get a filename from the user:

            lea     rsi, prompt
            call    puts

            lea     rdi, inputLn
            mov     rcx, lengthof inputLn
            call    readLn
            
; Open the file, read its contents, and display
; the contents to the standard output device

            lea     rsi, inputLn
            mov     rax, GENERIC_READ
            call    open

            cmp     eax, INVALID_HANDLE_VALUE
            je      badOpen
            
            mov     inHandle, eax
            
; Read the file 4,096 bytes at a time:

readLoop:   mov     eax, inHandle
            lea     rdi, fileBuffer
            mov     ecx, lengthof fileBuffer
            call    read
            test    eax, eax        ;EOF?
            jz      allDone
            mov     rcx, rax        ;Bytes to write
            
            call    getStdOutHandle
            lea     rsi, fileBuffer
            call    write
            jmp     readLoop
            
badOpen:    lea     rsi, badOpenMsg
            call    puts
            
allDone:    mov     eax, inHandle
            call    closeHandle
            
            
            leave
            pop     r15
            pop     rdi
            pop     rsi
            pop     rbx
            ret     ;Returns to caller
asmMain     endp
            end
