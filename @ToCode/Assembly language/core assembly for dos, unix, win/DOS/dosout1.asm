; dosout1.asm
; �뢮��� �� �࠭ �� ASCII-ᨬ����
;
; ���������:
; TASM:
; tasm /m dosout1.asm
; tlink /t /x dosout1.obj
; MASM:
; ml /c dosout1.asm
; link dosout1.obj,,NUL,,,
; exe2bin dosout1.exe dosout1.com
; WASM
; wasm dosout1.asm
; wlink file dosout1.obj form DOS COM
;

	.model	tiny
	.code
	org	100h		; ��砫� COM-䠩��
start:
	mov	cx,256 	; �뢥�� 256 ᨬ�����
	mov	dl,0		; ���� ᨬ��� - � ����� 00
	mov	ah,2		; ����� �㭪樨 DOS "�뢮� ᨬ����"
cloop: int	21h		; �맮� DOS
	inc	dl		; 㢥��祭�� DL �� 1 - ᫥���騩 ᨬ���,
	test	dl,0Fh	; �᫨ DL �� ��⥭ 16
	jnz	continue_loop	; �த������ 横�,
	push	dx		; ����: ��࠭��� ⥪�騩 ᨬ���
	mov	dl,0Dh	; �뢥�� CR
	int	21h
	mov	dl,0Ah	; �뢥�� LF
	int	21h
	pop	dx		; ����⠭����� ⥪�騩 ᨬ���
continue_loop:
	loop	cloop	; �த������ 横�

	ret		; �����襭�� COM-䠩��
	end	start
