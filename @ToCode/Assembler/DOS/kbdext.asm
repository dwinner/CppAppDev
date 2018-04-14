; kbdext.asm
; �ࠩ��� ᨬ���쭮�� ���ன�⢠, 㢥��稢��騩 ���� ���������� �� BUF_SIZE 
; (256 �� 㬮�砭��) ᨬ�����
;
; ���������:
; TASM:
; tasm /m kbdext.asm
; tlink /x kbdext.obj
; exe2bin kbdext.exe kbdext.sys
; MASM:
; ml /c kbdext.asm
; link kbdext.obj,,NUL,,,
; exe2bin kbdext.exe kbdext.sys
; WASM:
; wasm kbdext.asm
; wlink file kbdext.obj name kbdext.sys form DOS com
;
BUF_SIZE	equ	256		; ���� ࠧ��� ����

	.model	tiny
	.186			; ��� ᤢ���� � push 0040h
	.code
	org	0		; �ࠩ��� ��稭����� � CS:0000
start:
; ��������� �ࠩ���
	dd	-1		; ���� ᫥���饣� �ࠩ��� - FFFFh:FFFFh
				; ��� ��᫥�����
	dw	8000h		; ��ਡ���: ᨬ���쭮� ���ன�⢮, ��祣� �� 
				; �����ন����
	dw	offset strategy	; ���� ��楤��� ���⥣��
	dw	offset interrupt	; ���� ��楤��� ���뢠���
	db	'$$KBDEXT'	; ��� ���ன�⢠ (�� ������ ᮢ������ � 
				; �����-����� ������ 䠩��)

request	dd	?	; ����� ��楤�� ���⥣�� ��࠭�� ���� 
			; ���� ����� 
buffer	db	BUF_SIZE*2 dup (?) ; � �� - ��� ���� ���� 
				; ���������� ࠧ��஬ BUF_SIZE ᨬ����� (��� 
				; ���� �� ᨬ���)

; ��楤�� ���⥣��
; �� �室� ES:BX = ���� ���� �����
strategy	proc	far
	mov	cs:word ptr request,bx		; ��࠭��� ��� ���� ���
	mov	cs:word ptr request+2,es	; ��楤��� ���뢠���
	ret
strategy	endp

; ��楤�� ���뢠���
interrupt	proc	far
	push	ds			; ��࠭��� ॣ�����
	push	bx
	push	ax
	lds	bx,dword ptr cs:request ; DS:BX - ���� �����
	mov	ah,byte ptr [bx+2]	; ������ ����� �������,
	or	ah,ah			; �᫨ ������� 00h (���樠������),
	jnz	exit
	call	init			; ���㦨�� ��,
					; ����:
exit:	mov	ax,100h			; ��⠭����� ��� 8 (������� ���㦥��)
	mov	word ptr [bx+3],ax	; � ᫮�� ���ﭨ� �ࠩ���
	pop	ax			; � ����⠭����� ॣ�����
	pop	bx
	pop	ds
	ret
interrupt	endp


; ��楤�� ���樠����樨
; ��뢠���� ⮫쪮 ࠧ �� ����㧪� �ࠩ���
init	proc	near
	push	cx
	push	dx

	mov	ax,offset buffer
	mov	cx,cs		; CX:AX - ���� ��襣� ���� ����������
	cmp	cx,1000h	; �᫨ CX ᫨誮� �����,
	jnc	too_big	; �� ���� ����㦠����,
	shl	cx,4		; ����: 㬭����� ᥣ����� ���� �� 16,
	add	cx,ax		; �������� ᬥ饭�� - ����稫�� ������� ����
	sub	cx,400h	; ������ ������� ���� ��砫� ������ BIOS

	push	0040h
	pop	ds
	mov	bx,1Ah			; DS:BX = 0040h:001Ah - ���� ������
	mov	word ptr [bx],cx	; ������� ���� ���� ������� ����
	mov	word ptr [bx+2],cx	; �� �� ���� ���� 墮��
	mov	bl,80h			; DS:BX = 0040h:0080h - ���� ��砫� ����
	mov	word ptr [bx],cx	; ������� ���� ���� ��砫�
	add	cx,BUF_SIZE*2		; �������� ࠧ���
	mov	word ptr [bx+2],cx	; � ������� ���� ���� ����

	mov	ah,9			; �㭪�� DOS 09h
	mov	dx,offset succ_msg	; DS:DX - ���� ��ப�
	push	cs			; � ᮮ�饭��� �� �ᯥ譮� ��⠭����
	pop	ds
	int	21h			; �뢮� ��ப� �� �࠭

	lds	bx,dword ptr cs:request	; DS:BX - ���� �����
	mov	ax,offset init
	mov	word ptr [bx+0Eh],ax	; CS:AX - ᫥���騩 ���� ��᫥
	mov	word ptr [bx+10h],cs	; ���� १����⭮� ���
	jmp short done			; ����� ��楤��� ���樠����樨

; � ��।����� �ࠢ�����, �᫨ �� ����㦥�� ᫨誮� ����� � �����
too_big:
	mov	ah,9			; �㭪�� DOS 09h
	mov	dx,offset fail_msg	; DS:DX - ���� ��ப�
	push	cs			; � ᮮ�饭��� � ���ᯥ譮�
	pop	ds			; ��⠭����
	int	21h			; �뢮� ��ப� �� �࠭

	lds	bx,dword ptr cs:request	; DS:BX - ���� �����
	mov	word ptr [bx+0Eh],0	; ������� ���� ��砫� �ࠩ���
	mov	word ptr [bx+10h],cs	; � ���� "���� ��ࢮ�� 
					; �᢮���������� ����"
done:	pop	dx
	pop	cx
	ret
init	endp
; ᮮ�饭�� �� �ᯥ譮� ��⠭����
succ_msg	db	'Keyboard extender loaded',0Dh,0Ah,'$'
; ᮮ�饭�� � ���ᯥ譮� ��⠭����
fail_msg	db	'Too many drivers in memory - '
		db	'put kbdext.sys first '
		db	'in config.sys',0Dh,0Ah,'$'
	end	start
