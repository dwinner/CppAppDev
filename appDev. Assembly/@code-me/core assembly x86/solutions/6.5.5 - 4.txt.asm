.386
.model flat, stdcall
.stack 4096
ExitProcess PROTO, dwExitCode:DWORD

.data
sum DWORD 0
sample DWORD 50
array DWORD 10, 60, 20, 33, 72, 89, 45, 65, 72, 18
ArraySize = ($ - Array) / TYPE array

.code
main PROC

mov eax, 0; sum
mov edx, sample
mov ecx, ArraySize
mov edi, offset array

L1 : 
cmp [edi], edx
jg L3
jmp L4
L3 : 
add eax, [edi]
L4 :
add edi, type array
loop L1
mov sum, eax

INVOKE ExitProcess, 0
main ENDP
end main