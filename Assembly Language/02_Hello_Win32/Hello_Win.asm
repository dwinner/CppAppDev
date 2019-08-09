TITLE       (.asm)
.386
.model flat, stdcall

ExitProcess PROTO,
   x:dword
WaitMsg PROTO
WriteString PROTO
Crlf PROTO

.data
   strHello BYTE "Hello World!",0
   
.code
main PROC
   mov EDX, OFFSET strHello   ; Аргументы для WriteString
   invoke WriteString         ; Вывод строки на консоль
   invoke Crlf                ; Перевод каретки
   invoke WaitMsg             ; Запрос для нажатия клавиши
   invoke ExitProcess,0       ; Корректное окончание программы
main ENDP

END main