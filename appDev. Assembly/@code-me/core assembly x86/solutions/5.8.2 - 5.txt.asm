; 5.8.2 Algorithm workbench - 5 - how to display subroutine s return address

.386
.model flat, stdcall
.stack 4096
ExitProcess PROTO, dwExitCode:DWORD

.data
array DWORD 1000h, 2000h, 3000h, 4000h

.code
main PROC

mov eax, 1
call subrout

INVOKE ExitProcess, 0
main ENDP

subrout proc
mov ebx, [esp]
ret
subrout endp

END main