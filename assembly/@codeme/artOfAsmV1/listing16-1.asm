; Listing 16-1.asm
;
; A standalone assembly language version of 
; the ubiquitous "Hello, World!" program.

; Link in the windows win32 API:

            includelib kernel32.lib

; Here are the two Windows functions we will need
; to send "Hello, World!" to the standard console device:

            extrn __imp_GetStdHandle:proc
            extrn __imp_WriteFile:proc

            .code
hwStr       byte    "Hello World!"
hwLen       =       $-hwStr

; This is the honest-to-goodness assembly language
; main program:

main        proc
            
; On entry, stack is aligned at 8 mod 16. Setting aside 8
; bytes for "bytesWritten" ensures that calls in main have
; their stack aligned to 16 bytes (8 mod 16 inside function),
; as required by the Windows API (which __imp_GetStdHandle and
; __imp_WriteFile use -- they are written in C/C++)
            
            lea     rbx, hwStr
            sub     rsp, 8
            mov     rdi, rsp        ;Hold # of bytes written here.

; Note: must set aside 32 bytes (20h) for shadow registers for
; parameters (just do this once for all functions). Also, WriteFile
; has a 5th argument (which is NULL) so we must set aside 8 bytes
; to hold that pointer (and initialize it to zero). Finally, stack
; must always be 16-byte aligned, so reserve another 8 bytes of storage
; to ensure this.

            sub     rsp, 030h       ; Shadow storage for args (always 20h bytes)
                    
; handle = GetStdHandle( -11 );
; Single argument passed in ECX.
; handle returned in RAX.

            mov     rcx, -11    ; STD_OUTPUT
            call    qword ptr __imp_GetStdHandle ;Returns handle in RAX
                    
; WriteFile( handle, "Hello World!", 12, &bytesWritten, NULL );
; Zero out (set to NULL) "LPOverlapped" argument:
            
            xor     rcx, rcx
            mov     [rsp+4*8], rcx
            
            mov     r9, rdi         ;Address of "bytesWritten" in R9
            mov     r8d, hwLen      ;Length of string to write in R8D 
            lea     rdx, hwStr      ;Ptr to string data in RDX
            mov     rcx, rax        ;File handle passed in RCX
            call    qword ptr __imp_WriteFile
            
; Clean up stack and return:

            add     rsp, 38h
            ret
main        endp
            end