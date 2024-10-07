; Listing 1-8
;
; An assembly language program that demonstrate returning
; a function result to a C++ program.

        option  casemap:none

nl      =       10  ;ASCII code for newline
maxLen  =       256 ;Maximum string size + 1

         .data  
titleStr byte    'Listing 1-8', 0
prompt   byte    'Enter a string: ', 0
fmtStr   byte    "User entered: '%s'", nl, 0

; "input" is a buffer having "maxLen" bytes. This program 
; will read a user string into this buffer.
;
; The "maxLen dup (?)" operand tells MASM to make "maxLen" 
; duplicate copies of a byte, each of which is uninitialized.
 
input    byte   maxLen dup (?)

        .code

        externdef   printf:proc
        externdef   readLine:proc


; The C++ function calling this assembly language module 
; expects a function named "getTitle" that returns a pointer 
; to a string as the function result. This is that function:

         public getTitle
getTitle proc

; Load address of "titleStr" into the RAX register (RAX holds 
; the function return result) and return back to the caller:

         lea rax, titleStr
         ret
getTitle endp

        
; Here is the "asmMain" function.

        
        public  asmMain
asmMain proc
        sub     rsp, 56
                

; Call the readLine function (written in C++) to read a line 
; of text from the console.
;
; int readLine( char *dest, int maxLen )
;
; Pass a pointer to the destination buffer in the RCX register.
; Pass the maximum buffer size (max chars + 1) in EDX.
; This function ignores the readLine return result.
; Prompt the user to enter a string:

        lea     rcx, prompt
        call    printf


; Ensure the input string is zero terminated (in the event 
; there is an error):

        mov     input, 0
        
; Read a line of text from the user:

        lea     rcx, input
        mov     rdx, maxLen
        call    readLine
        
; Print the string input by the user by calling printf:

        lea     rcx, fmtStr
        lea     rdx, input
        call    printf
 
        add     rsp, 56
        ret     ;Returns to caller
        
asmMain endp
        end