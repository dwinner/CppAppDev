; netenum.asm
; ���᮫쭮� �ਫ������ ��� win32, �������饥 �⥢� ������
;
; ��������� MASM
;  ml /c /coff /Cp netenum.asm
;  link netenum.obj /subsystem:console
;
; ��������� TASM
;  tasm /m /x /ml /D_TASM_ netenum.asm
;  tlink32 -Tpe -ap -c netenum.obj
;
; ��������� WASM
; wasm netenum.asm
; wlink file netenum.obj form windows nt runtime console
;

include def32.inc
include kernel32.inc
include mpr.inc

	.386
	.model flat
	.const
greet_message	db	'Example win32 console program',0Dh,0Ah,0Dh,0Ah,0
error1_message	db	0Dh,0Ah,'Could not get current user name',0Dh,0Ah,0
error2_message	db	0Dh,0Ah,'Could not enumerate',0Dh,0Ah,0
good_exit_msg	db	0Dh,0Ah,0Dh,0Ah,'Normal termination',0Dh,0Ah,0
enum_msg1	db	0Dh,0Ah,'Local ',0
enum_msg2	db	' remote - ',0
	.data
user_name	db	'List of connected resources for user '
user_buff	db	64 dup (?)	; ���� ��� WNetGetUser
user_buff_l	dd	$-user_buff	; ࠧ��� ���� ��� WNetGetUser
enum_buf_l	dd	1056	; ����� enum_buf � �����
enum_entries	dd	1	; �᫮ ����ᮢ, ���஥ � �� ���������
	.data?
enum_buf	NTRESOURCE <?,?,?,?,?,?,?,?>	; ���� ��� WNetEnumResource
		dd	256 dup (?)		; 1024 ���� ��� ��ப
message_l	dd	?		; ��६����� ��� WriteConsole
enum_handle	dd	?		; �����䨪��� ��� WNetEnumResource
	.code
_start:
; ����稬 �� ��⥬� �����䨪��� ���� �뢮�� stdout
	push	STD_OUTPUT_HANDLE
	call	GetStdHandle	; �����頥� �����䨪��� STDOUT � eax
	mov	ebx,eax		; � �� �㤥� �࠭��� ��� � EBX
; �뢥��� ��ப� greet_message �� �࠭
	mov	esi,offset greet_message
	call	output_string
; ��।���� ��� ���짮��⥫�, ���஬� �ਭ������� ��� �����
	mov	esi,offset user_buff
	push	offset user_buff_l	; ���� ��६����� � ������ ����
	push	esi			; ���� ����
	push	0			; NULL
	call	WNetGetUser
	cmp	eax,NO_ERROR		; �᫨ �ந��諠 �訡��
	jne	error_exit1		; ���
	mov	esi,offset user_name	; ���� - �뢥��� ��ப� �� �࠭
	call	output_string

; ���� ����᫥��� �⥢�� ����ᮢ
	push	offset enum_handle	; �����䨪��� ��� WNetEnumResource
	push	0
	push	RESOURCEUSAGE_CONNECTABLE ; �� ��ᮥ���塞� ������
	push	RESOURCETYPE_ANY	; ������ ��� ⨯�
	push	RESOURCE_CONNECTED	; ⮫쪮 ��ᮥ����� ᥩ��
	call	WNetOpenEnum		; ����� ����᫥���
	cmp	eax,NO_ERROR		; �᫨ �ந��諠 �訡��
	jne	error_exit2		; ���
; 横� ����᫥��� ����ᮢ
enumeration_loop:
	push	offset enum_buf_l	; ����� ���� � �����
	push	offset enum_buf		; ���� ����
	push	offset enum_entries	; �᫮ ����ᮢ
	push	dword ptr enum_handle	; �����䨪��� �� WNetOpenEnum
	call	WNetEnumResource
	cmp	eax,ERROR_NO_MORE_ITEMS	; �᫨ ��� �����稫���
	je	end_enumeration		; �������� ����᫥���
	cmp	eax,NO_ERROR		; �᫨ �ந��諠 �訡��
	jne	error_exit2		; ��� � ᮮ�饭��� �� �訡��
; �뢮� ���ଠ樨 ����� �� �࠭
	mov	esi,offset enum_msg1	; ��ࢠ� ���� ��ப�
	call	output_string		; �� ���᮫�
	mov	esi,dword ptr enum_buf.lpLocalName ; �����쭮� ��� ���ன�⢠
	call	output_string		; �� ���᮫�
	mov	esi,offset enum_msg2	; ���� ���� ��ப�
	call	output_string		; �� ���᮫�
	mov	esi,dword ptr enum_buf.lpRemoteName ; 㤠�񭭮� ��� ���ன�⢠
	call	output_string		; �㤠 ��

	jmp short enumeration_loop	; �த����� ����᫥���
; ����� 横��
end_enumeration:
	push	dword ptr enum_handle
	call	WNetCloseEnum		; ����� ����᫥���

	mov	esi,offset good_exit_msg
exit_program:
	call	output_string		; �뢥��� ��ப�
	push	0		; ��� ��室�
	call	ExitProcess	; ����� �ணࠬ��
; ��室� ��᫥ �訡��
error_exit1:
	mov	esi,offset error1_message
	jmp short exit_program
error_exit2:
	mov	esi,offset error2_message
	jmp	short exit_program


; ��楤��� output_string
; �뢮��� �� �࠭ ��ப�
; ����: esi - ���� ��ப�
;	ebx - �����䨪��� stdout ��� ��㣮�� ���᮫쭮�� ����
output_string proc near
; ��।���� ����� ��ப�
	cld
	xor	eax,eax
	mov	edi,esi
	repne	scasb
	dec	edi
	sub	edi,esi
; ���� �� �� ���᮫�
	push	0
	push	offset message_l ; ᪮�쪮 ���� �뢥���� �� ���᮫�
	push	edi		 ; ᪮�쪮 ���� ���� �뢥�� �� ���᮫�
	push	esi		; ���� ��ப� ��� �뢮�� �� ���᮫�
	push	ebx		; �����䨪��� ���� �뢮��
	call	WriteConsole	; WriteConsole(hConsoleOutput,lpvBuffer,cchToWrite,lpcchWritten,lpvReserved)
	ret
output_string endp

end	_start



