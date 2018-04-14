; rot13.asm
; �ࠩ��� ᨬ���쭮�� ���ன�⢠, �뢮��騩 ���뫠��� ��� ᨬ���� �� �࠭
; ��᫥ �믮������ ��� ���� �८�ࠧ������ ROT13.
; (������ �㪢� ������᪮�� ��䠢�� ᬥ頥��� �� 13 ����権)
; ����������� ⮫쪮 �㭪樨 ����� � ���ன�⢮
; 
; �ਬ�� �ᯮ�짮�����:
; copy encrypted.txt $rot13
;
; ���������:
; TASM:
;  tasm /m rot13.asm
;  tlink /x rot13.obj
; MASM:
;  ml /c rot13.asm
;  link rot13.obj
; WASM:
;  wasm rot13.asm
;  wlink file rot13.obj form DOS
;
;
; ����㧪� - �� CONFIG.SYS
; DEVICE=c:\rot13.exe
; �᫨ rot13.exe ��室���� � ��४�ਨ C:\
;
	.model small	; ������ ��� EXE-䠩��
	.code
	.186		; ��� pusha/popa
	org	0	; ��� �ࠩ��� ��稭����� � CS:0000
	dd	-1	; ���� ᫥���饣� �ࠩ���
	dw	0A800h	; ��ਡ��� ��襣� ���ன�⢠
	dw	offset strategy	; ���� ��楤��� ���⥣�� 
	dw	offset interrupt	; ���� ��楤��� ���뢠���
	db	'$ROT13',20h,20h	; ��� ���ன�⢠, ����������� 
					; �஡����� �� ���쬨 ᨬ�����

request	dd	?	; � ��楤�� ���⥣�� �㤥� ����� ���� 
			; ���� �����

; ⠡��� ���ᮢ ��ࠡ��稪�� ��� ��� ������
command_table	dw	offset init			; 00h
		dw	3 dup(offset unsupported)	; 01, 02, 03
		dw	2 dup(offset read)		; 04, 05
		dw	2 dup(offset unsupported)	; 06, 07
		dw	2 dup(offset write)		; 08h, 09h
		dw	6 dup(offset unsupported)	; 0Ah, 0Bh, 0Ch, 0Dh, 0Eh, 0Fh
		dw	offset write			; 10h
		dw	2 dup(offset invalid)		; 11h, 12h
		dw	offset unsupported 		; 13h
		dw	3 dup(offset invalid)		; 14h, 15h, 16h
		dw	3 dup(offset unsupported)	; 17h, 18h, 19h

; ��楤�� ���⥣�� - ���� � � �� ��� ��� �ࠩ��஢
strategy proc far
	mov	word ptr cs:request,bx
	mov	word ptr cs:request+2,es
	ret
strategy endp

; ��楤�� ���뢠���
interrupt	proc	far
	pushf
	pusha			; ��࠭��� ॣ�����
	push	ds		; � �� ��直� ��砩 䫠��
	push	es

	push	cs
	pop	ds		; DS = ��� ᥣ����� ����
	les	si,dword ptr request	; ES:SI = ���� ���� �����
	xor	bx,bx
	mov	bl,byte ptr es:[si+2]	; BX = ����� �㭪樨
	cmp	bl,19h	; �஢����, �� ������� � �।���� 00 - 19h,
	jbe	command_ok
	call	invalid	; �᫨ ��� - ��� � �訡���
	jmp short interrupt_end
command_ok:			; �᫨ ������� ��室���� � �।���� 00 - 19h,
	shl	bx,1		; 㬭����� �� �� 2, �⮡� ������� ᬥ饭�� � 
; ⠡��� ᫮� command_table,
	call	word ptr command_table[bx]	; � �맢��� ��ࠡ��稪
interrupt_end:
	cmp	al,0		; AL = 0, �᫨ �� �뫮 �訡��,
	je	no_error
	or	ah,80h	; �᫨ �뫠 �訡�� - ��⠭����� ��� 15 � AX,
no_error:
	or	ah,01h	; � �� ��砥 ��⠭����� ��� 8
	mov	word ptr es:[si+3],ax	; � ������� ᫮�� ���ﭨ� 
	pop	es
	pop	ds
	popa
	popf
	ret
interrupt	endp

; ��ࠡ��稪 ������, �।�����祭��� ��� ������ ���ன��
unsupported	proc	near
	xor	ax,ax	; �� �������� ������� �訡��
	ret
unsupported	endp

; ��ࠡ��稪 ������ �⥭��
read	proc	near
	mov	al,0Bh	; ���� �訡�� �⥭��
	ret
read	endp

; ��ࠡ��稪 ����������� ������
invalid	proc	near
	mov	ax,03h	; �訡�� "�������⭠� �������"
	ret
invalid	endp

; ��ࠡ��稪 �㭪権 �����
write	proc	near
	push	si
	mov	cx,word ptr es:[si+12h]	; ����� ���� � CX,
	jcxz	write_finished	; �᫨ �� 0 - ��� ������ ��祣�
	lds	si,dword ptr es:[si+0Eh] ; ���� ���� � DS:SI

; �믮����� ROT13-�८�ࠧ������ ��� ���஬
	cld
rot13_loop:			; 横� �� �ᥬ ᨬ����� ����
	lodsb			; AL = ᫥���騩 ᨬ��� �� ���� � ES:SI

	cmp	al,'A'		; �᫨ �� ����� 'A',
	jl	rot13_done		; �� �� �㪢�,
	cmp	al,'Z'		; �᫨ �� ����� 'Z',
	jg	rot13_low		; ����� ����, �� �����쪠� �㪢�,
	cmp	al,('A'+13)		; ����: �᫨ �� ����� 'A' + 13,
	jge	rot13_dec		; ������ �� ���� 13,
	jmp short rot13_inc	; 	� ���� - ���������
rot13_low:
	cmp	al,'a'		; �᫨ ᨬ��� ����� 'a',
	jl	rot13_done		; �� �� �㪢�,
	cmp	al,'z'		; �᫨ ᨬ��� ����� 'z',
	jg	rot13_done		; � �� ᠬ��,
	cmp	al,('a'+13)		; ����: �᫨ �� ����� 'a' + 13,
	jge	rot13_dec		; ������ �� ���� 13, ����:
rot13_inc:
	add	al,13		; �������� 13 � ���� ᨬ����,
	jmp short rot13_done
rot13_dec:
	sub	al,13		; ������ 13 �� ���� ᨬ����,
rot13_done:
	int	29h		; �뢥�� ᨬ��� �� �࠭
	loop	rot13_loop	; � ������� ��� ��� ᨬ�����

write_finished:
	xor	ax,ax		; ᮮ����, �� �訡�� �� �뫮
	pop	si
	ret
write	endp

; ��楤�� ���樠����樨 �ࠩ���
init	proc	near
	mov	ah,9		; �㭪�� DOS 09h
	mov	dx,offset load_msg ; DS:DX - ᮮ�饭�� �� ��⠭����
	int	21h		; �뢮� ��ப� �� �࠭
	mov	word ptr es:[si+0Eh],offset init ; ������� ����
	mov	word ptr es:[si+10h],cs	; ���� १����⭮� ���
	xor	ax,ax		; �訡�� �� �ந��諮
	ret
init	endp

; ᮮ�饭�� �� ��⠭���� �ࠩ���
load_msg db	'ROT13 device driver loaded',0Dh,0Ah,'$'

start:			; �窠 �室� EXE-�ணࠬ��
	push	cs
	pop	ds
	mov	dx,offset exe_msg	; DS:DX - ���� ��ப�
	mov	ah,9		; �㭪�� DOS
	int	21h		; �뢮� ��ப� �� �࠭
	mov	ah,4Ch	; �㭪�� DOS 4Ch
	int	21h		; �����襭�� EXE-�ணࠬ��
; ��ப�, ����� �뢮����� �� ����᪥ �� �� CONFIG.SYS
exe_msg	db	'This file is loaded as a device driver from CONFIG.SYS'
	db	0Dh,0Ah,'$'

	.stack

	end	start
