; 5.4.5 section review - question 11

include Irvine32.inc

.data
prompt byte "Enter a password: ", 0
array1 byte 20 dup (0)

.code
main PROC

; this section prints PROMPT message
mov edx, OFFSET prompt
call WriteString

; this section read users input
mov edx, OFFSET array1
mov ecx, SIZEOF array1
call ReadString

call WaitMsg
call Crlf
exit
main ENDP
END main