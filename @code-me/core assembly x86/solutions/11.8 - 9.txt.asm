; 11.8 - 9 - Last Access Date of a File

; FileDate procedure is created to obtain all data concerning file creation and manipulation.

;Please note how parameters are passed inside the procedure:
; if CreateFile is invoked in MAIN, then 1st parameter should be ADDR FILENAME.
; From the other side, if CreateFile is invoked inside of the procedure, then 1st parameter is only FILENAME.
; Idem for FileTimeToSystemTime (check 2nd parameter, it also should be ADDR if invoked in MAIN).

INCLUDE Irvine32.inc
INCLUDE Macros.inc
INCLUDE GraphWin.inc

FileDate proto,
NameOfFile: ptr byte,
TimeOfCreation: ptr SYSTEMTIME,
TimeOfLastAccess: ptr SYSTEMTIME,
TimeOfLastWrite: ptr SYSTEMTIME

; .386
; .model flat, stdcall
; .stack 4096
; ExitProcess proto, dwExitCode:dword

.data

filename byte "D:\irvine\part 11\Ex6.txt", 0

CreationTime1 SYSTEMTIME <>
LastAccessTime1 SYSTEMTIME <>
LastWriteTime1 SYSTEMTIME <>

.code
main PROC

invoke FileDate, addr filename, addr CreationTime1, addr LastAccessTime1, addr LastWriteTime1

exit
main ENDP

FileDate proc,
NameOfFile: ptr byte,
TimeOfCreation: ptr SYSTEMTIME,
TimeOfLastAccess: ptr SYSTEMTIME,
TimeOfLastWrite: ptr SYSTEMTIME
local FileHandle: handle, CreationTime: FILETIME, LastAccessTime: FILETIME, LastWriteTime: FILETIME

INVOKE CreateFile,
NameOfFile,
GENERIC_READ, 
DO_NOT_SHARE,
NULL,
OPEN_EXISTING, 
FILE_ATTRIBUTE_NORMAL,
0

mov FileHandle, eax

invoke GetFileTime, FileHandle, addr CreationTime, addr LastAccessTime, addr LastWriteTime

invoke FileTimeToSystemTime, addr CreationTime, TimeOfCreation
invoke FileTimeToSystemTime, addr LastAccessTime, TimeOfLastAccess
invoke FileTimeToSystemTime, addr LastWriteTime, TimeOfLastWrite

invoke CloseHandle, FileHandle
ret
FileDate endp

END main