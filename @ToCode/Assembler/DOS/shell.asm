; shell.asm
; �ணࠬ��, �믮������ �㭪樨 ���������� ��������
; (��뢠��� command.com ��� ��� ������, �஬� exit). ��� ��⪮�� ��ப� 
;
; ���������:
; TASM:
;  tasm /m shell.asm
;  tlink /t /x shell.obj
; MASM:
;  ml /c shell.asm
;  link shell.obj,,NUL,,,
;  exe2bin shell.exe shell.com
; WASM:
;  wasm shell.asm
;  wlink file shell.obj form DOS COM
;

	.model	tiny
	.code
	.186
	org	100h		; COM-�ணࠬ��

prompt_end	equ	'$'	; ��᫥���� ᨬ��� � �ਣ��襭�� � �����

start:
	mov	sp,length_of_program+100h+200h ; ��६�饭�� �⥪� �� 200h
		; ��᫥ ���� �ணࠬ�� (�������⥫�� 100h - ��� PSP)

	mov	ah,4Ah
stack_shift=length_of_program+100h+200h
	mov	bx,stack_shift shr 4+1
	int	21h	; �᢮����� ��� ������ ��᫥ ���� �ணࠬ�� � �⥪�

; �������� ���� EPB, ᮤ�ঠ騥 ᥣ����� ����
	mov	ax,cs
	mov	word ptr EPB+4,ax	; ᥣ����� ���� ��������� ��ப�
	mov	word ptr EPB+8,ax	; ᥣ����� ���� ��ࢮ�� FCB
	mov	word ptr EPB+0Ch,ax ; ᥣ����� ���� ��ண� FCB

main_loop:

; ����஥��� � �뢮� �ਣ��襭�� ��� �����

	mov	ah,19h		; �㭪�� DOS 19h
	int	21h			; ��।����� ⥪�騩 ���
	add	al,'A'		; ⥯��� AL = ASCII-��� ��᪠ (A, B, C...)
	mov	byte ptr drive_letter,al ; �������� ��� � ��ப�
	mov	ah,47h		; �㭪�� DOS 47h
	mov	dl,00
	mov	si,offset pwd_buffer
	int	21h			; ��।����� ⥪���� ��४���
	mov	al,0			; ���� ���� (����� ⥪�饩 ��४�ਨ)
	mov	di,offset prompt_start	; � ��ப� � �ਣ��襭���
	mov	cx,prompt_l
	repne scasb
	dec	di			; DI - ���� ���� � �㫥�

	mov	dx,offset prompt_start	; DS:DX - ��ப� �ਣ��襭��
	sub	di,dx			; DI - ����� ��ப� �ਣ��襭��
	mov	cx,di
	mov	bx,1			; stdout
	mov	ah,40h
	int	21h			; �뢮� ��ப� � 䠩� ��� ���ன�⢮
	mov	al,prompt_end
	int	29h		; �뢮� ��᫥����� ᨬ���� � �ਣ��襭��

; ������� ������� �� ���짮��⥫�
	mov	ah,0Ah		; �㭪�� DOS 0Ah
	mov	dx,offset command_buffer
	int	21h			; ����஢���� ����

	mov	al,0Dh		; �뢮� ᨬ���� CR
	int	29h
	mov	al,0Ah		; �뢮� ᨬ���� LF
	int	29h			; (CR � LF ����� - ��ॢ�� ��ப�)

	cmp	byte ptr command_buffer+1,0 ; �᫨ ������� ����� ��ப�,
	je	main_loop		; �த������ �᭮���� 横�

; �஢����, ���� �� ��������� ������� �������� 'exit'

	mov	di,offset command_buffer+2 ; ���� ��������� ��ப�
	mov	si,offset cmd_exit ; ���� �⠫����� ��ப� 'exit',0Dh
	mov	cx,cmd_exit_l	; ����� �⠫����� ��ப�
	repe cmpsb			; �ࠢ���� ��ப�
	jcxz	got_exit		; �᫨ ��ப� ������� - �믮����� exit

; ��।��� ��⠫�� ������� ��������� DOS (COMMAND.COM)
	xor	cx,cx
	mov	si,offset command_buffer+2 ; ���� ��������� ��ப�
	mov	di,offset command_text	; ��ࠬ���� ��� command.com
	mov	cl,byte ptr command_buffer+1 ; ࠧ��� ��������� ��ப�
	inc	cl			; ����� 0Dh � ����
	rep movsb			; ᪮��஢��� ��ப�
	mov	ax,4B00h		; �㭪�� DOS 4Bh
	mov	dx,offset command_com	; ���� ASCIZ-��ப� � ���ᮬ
	mov	bx,offset EPB
	int	21h			; �ᯮ����� �ணࠬ��

	jmp short main_loop	; �த������ �᭮���� 横�
got_exit:
	int	20h			; ��室 �� �ணࠬ�� (ret �����, ��⮬� 
					; �� �� ��६�頫� �⥪)

cmd_exit	db	'exit',0Dh	; ������� 'exit'
cmd_exit_l	equ	$-cmd_exit	; �� �����

prompt_start	db	'tinyshell:'	; ���᪠��� ��� �����
drive_letter	db	'C:'
pwd_buffer	db	64 dup (?)	; ���� ��� ⥪�饩 ��४�ਨ
prompt_l	equ $-prompt_start ; ���ᨬ��쭠� ����� ���᪠���

command_com	db	'C:\COMMAND.COM',0	; ��� 䠩��

EPB		dw	0000	; �ᯮ�짮���� ⥪�饥 ���㦥���
		dw	offset commandline,0 ; ���� ��������� ��ப�
		dw	005Ch,0,006Ch,0 ; ���� FCB, ��।����� DOS 
					; ��襩 �ணࠬ�� �� ����᪥ (�� ᠬ�� ����
					; ��� �� �ᯮ�������)

commandline	db	125		; ���ᨬ��쭠� ����� ��������� ��ப�
		db	' /C '	; ���� /C ��� COMMAND.COM
command_text	db	122 dup (?)	; ���� ��� ��������� ��ப�

command_buffer	db 122	; ����� ��稭����� ���� ��� �����
length_of_program equ 124+$-start	; ����� �ணࠬ�� + ����� 
					; ���� ��� �����
	end	start
