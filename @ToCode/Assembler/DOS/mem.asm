; mem.asm
; ᮮ�頥� ࠧ��� �����, ����㯭�� �१ EMS � XMS
;
; ���������:
; TASM:
; tasm /m mem.asm
; tlink /t /x mem.obj
; MASM:
; ml /c mem.asm
; link mem.obj,,NUL,,,
; exe2bin mem.exe mem.com
; WASM:
; wasm mem.asm
; wlink file mem.obj form DOS COM
;


	.model	tiny
	.code
	.186		; ��� ������ ᤢ��� �� 4
	org	100h	; COM-�ணࠬ��
start:
	cld		; ������� ��ப���� ��ࠡ�⪨ ���� �믮������� ���।

; �஢�ઠ ������ EMS

	mov	dx,offset ems_driver ; ���� ASCIZ-��ப� "EMMXXXX0"
	mov	ax,3D00h
	int	21h		; ������ 䠩� ��� ���ன�⢮
	jc	no_emmx	; �᫨ �� 㤠���� ������ - EMS ���
	mov	bx,ax		; �����䨪��� � BX
	mov	ax,4400h
	int	21h		; IOCTL: �஢���� ���ﭨ� 䠩��/���ன�⢠
	jc	no_ems	; �᫨ �� �ந��諠 �訡��,
	test	dx,80h	; �஢���� ���訩 ��� DX,
	jz	no_ems	; �᫨ �� - 0, EMMXXXX0 - 䠩� � ⥪�饩 
			; ��४�ਨ

; ��।������ ���ᨨ EMS

	mov	ah,46h
	int	67h		; ������� ����� EMS
	test	ah,ah
	jnz	no_ems	; �᫨ EMS �뤠� �訡�� - �� �⮨� �த������ � 
			; ��� ࠡ����
	mov	ah,al
	and	al,0Fh	; AL = ����� ���
	shr	ah,4		; AH = ������ ���
	call	output_version	; �뤠�� ��ப� � ����� ���ᨨ EMS

; ��।������ ����㯭�� EMS-�����
	mov	ah,42h
	int	67h		; ������� ࠧ��� ����� � 16-���������� ��࠭���
	shl	dx,4		; DX = ࠧ��� ����� � ���������
	shl	bx,4		; BX = ࠧ��� ᢮������ ����� � ���������
	mov	ax,bx
	mov	si,offset ems_freemem	; ���� ��ப� ��� output_info
	call	output_info	; �뤠�� ��ப� � ࠧ���� �����

no_ems:
	mov	ah,3Eh
	int	21h		; ���஥� 䠩�/���ன�⢮ EMMXXXX0
no_emmx:

; �஢�ઠ ������ XMS

	mov	ax,4300h
	int	2Fh		; �஢�ઠ XMS,
	cmp	al,80h	; �᫨ AL �� ࠢ�� 80h,
	jne	no_xms	; XMS ���������,
	mov	ax,4310h	; ����:
	int	2Fh		; ������� ��� �室� XMS
	mov	word ptr entry_pt,bx	; � ��࠭��� �� � entry_pt
	mov	word ptr entry_pt+2,es	; (���襥 ᫮�� - �� ���襬�
					; �����!)
	push	ds
	pop	es			; ����⠭����� ES

; ��।������ ���ᨨ XMS
	mov	ah,00
	call	dword ptr entry_pt ; �㭪�� XMS 00h - ����� ���ᨨ
	mov	byte ptr mem_version,'X' ; �������� ����� �㪢� ��ப�
				; "EMS detected" �� 'X'
	call	output_version	; �뤠�� ��ப� � ����� ���ᨨ XMS

; ��।������ ����㯭�� XMS-�����
	mov	ah,08h
	xor	bx,bx
	call	dword ptr entry_pt	; �㭪�� XMS 08h

	mov	byte ptr totalmem,'X' ; �������� ����� �㪢� ��ப�
					; "EMS total" �� 'X'
	mov	si,offset xms_freemem ; ��ப� ��� output_info

; �뢮� ᮮ�饭�� �� �࠭:
; DX - ��ꥬ �ᥩ �����
; AX - ��ꥬ ᢮������ �����
; SI - ���� ��ப� � ᮮ�饭��� � ᢮������ ����� (ࠧ�� ��� EMS � XMS)

output_info:
	push	ax
	mov	ax,dx		 ; ��ꥬ �ᥩ ����� � AX
	mov	bp,offset totalmem ; ���� ��ப� - � BP
	call	output_info1 ; �뢮�
	pop	ax		; ��ꥬ ᢮������ ����� - � AX
	mov	bp,si		; ���� ��ப� � BP

output_info1:			; �뢮�
	mov	di,offset hex2dec_word

; hex2dec
; �८�ࠧ�� 楫�� ����筮� �᫮ � AX
; � ��ப� �������� ASCII-��� � ES:DI, �����稢������� ᨬ����� '$'

	mov	bx,10	; ����⥫� � BX
	xor	cx,cx	; ���稪 ��� � 0
divlp:	xor	dx,dx
	div	bx	; ࠧ������ �८�ࠧ㥬�� �᫮ �� 10
	add	dl,'0' ; �������� � ����� ASCII-��� ���
	push	dx	; ������� ����祭��� ���� � �⥪
	inc	cx	; 㢥����� ���稪 ���
	test	ax,ax	; �, �᫨ �� ����, �� ������,
	jnz	divlp	; �த������ ������� �� 10
store:
	pop	ax	; ����� ���� �� �⥪�
	stosb		; ������� �� � ����� ��ப� � ES:DI
	loop	store	; �த������ ��� ��� CX-���
	mov	byte ptr es:[di],'$' ; ������� "$" � ����� ��ப�

	mov	dx,bp	; DX - ���� ��ࢮ� ��� ��ப�
	mov	ah,9
	int	21h	; �㭪�� DOS 09h - �뢮� ��ப�
	mov	dx,offset hex2dec_word ; DX - ���� ��ப� � ������� 
				; �᫮�
	int	21h	; �뢮� ��ப�
	mov	dx,offset eol	; DX - ���� ��᫥���� ��� ��ப�
	int	21h	; �뢮� ��ப�

no_xms:	ret		; ����� �ணࠬ�� � ��楤�� output_info
			; � output_info1


; �뢮� ���ᨨ EMS/XMS
; AX - ����� � ��㯠�������� BCD-�ଠ�

output_version:
	or	ax,3030h	; �८�ࠧ������ ��㯠��������� BCD � ASCII
	mov	byte ptr major,ah ; ����� ��� � major
	mov	byte ptr minor,al	; ������ ��� � minor
	mov	dx,offset mem_version ; ���� ��砫� ��ப� - � DX
	mov	ah,9
	int	21h			; �뢮� ��ப�
	ret

ems_driver	db	'EMMXXXX0',0	; ��� �ࠩ��� ��� �஢�ન EMS
mem_version	db	'EMS version '	; ᮮ�饭�� � ����� ���ᨨ
major		db	'0.'		; ���� ����� �⮩
minor		db	'0 detected ',0Dh,0Ah,'$'; � �⮩ ��ப ����
					; �������� ॠ��묨 ����ࠬ� ���ᨩ
totalmem	db	'EMS total memory: $'
ems_freemem	db	'EMS free memory: $'
eol		db	'K',0Dh,0Ah,'$'	; ����� ��ப�
xms_freemem	db	'XMS largest free block: $'

entry_pt:				; � �����뢠���� �窠 �室� XMS
hex2dec_word equ entry_pt+4	; ���� ��� �����筮� ��ப�
	end	start
