; Listing 5-11
;
; Demonstration passing parameters in the code stream.

        option  casemap:none

nl          =       10
stdout      =       -11

            .const
ttlStr      byte    "Listing 5-11", 0
        
            .data
soHandle    qword   ?
bWritten    dword   ?
        
            .code
            
            ; Magic equates for Windows API calls:
            
            extrn __imp_GetStdHandle:qword
            extrn __imp_WriteFile:qword

; Return program title to C++ program:

            public  getTitle
getTitle    proc
            lea     rax, ttlStr
            ret
getTitle    endp


; Here's the print procedure.
; It expects a zero-terminated string
; to follow the call to print.


print       proc
            push    rbp
            mov     rbp, rsp
            and     rsp, -16        ;Ensure stack 16-byte aligned
            sub     rsp, 48         ; Set up stack for MS ABI
            
; Get the pointer to the string immediately following the
; call instruction and scan for the zero-terminating byte.
            
            mov     rdx, [rbp+8]     ;Return address is here
            lea     r8, [rdx-1]      ;R8 = return address - 1
search4_0:  inc     r8               ;Move on to next char
            cmp     byte ptr [R8], 0 ;At end of string?
            jne     search4_0
            
; Fix return address and compute length of string:

            inc     r8               ;Point at new return address
            mov     [rbp+8], r8      ;Save return address
            sub     r8, rdx          ;Compute string length
            dec     r8               ;Don't include 0 byte
            
; Call WriteFile to print the string to the console
;
; WriteFile( fd, bufAdrs, len, &bytesWritten );
;
; Note: pointer to the buffer (string) is already
; in RDX. The len is already in R8. Just need to
; load the file descriptor (handle) into RCX:

            mov     rcx, soHandle    ;Zero extends!
            lea     r9, bWritten    ;Address of "bWritten" in R9
            call    __imp_WriteFile

            leave
            ret
print       endp
 

; Here is the "asmMain" function.

        
            public  asmMain
asmMain     proc
            push    rbp
            mov     rbp, rsp
            sub     rsp, 40
        
; Call getStdHandle with "stdout" parameter
; in order to get the standard output handle
; we can use to call write. Must set up
; soHandle before first call to print procedure

            mov     ecx, stdout     ;Zero-extends!
            call    __imp_GetStdHandle
            mov     soHandle, rax   ;Save handle    

; Demonstrate passing parameters in code stream
; by calling the print procedure:

            call    print
            byte    "Hello, World!", nl, 0

; Clean up, as per Microsoft ABI:

            leave
            ret     ;Returns to caller
        
asmMain     endp
            end