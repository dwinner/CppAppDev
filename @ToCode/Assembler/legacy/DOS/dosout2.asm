; dosout2.asm
; �뢮��� �� �࠭ ��ப� "This function can print $",
; �ᯮ���� �뢮� � STDERR, ⠪ �� �� ����� ��७��ࠢ��� � 䠩�.
;
; ���������:
; TASM:
; tasm /m dosout2.asm
; tlink /t /x dosout2.obj
; MASM:
; ml /c dosout2.asm
; link dosout2.obj,,NUL,,,
; exe2bin dosout2.exe dosout2.com
; WASM
; wasm dosout2.asm
; wlink file dosout2.obj form DOS COM
;

	.model	tiny
	.code
	org	100h			; ��砫� COM-䠩��
start:
	mov	ah,40h		; ����� �㭪樨 DOS
	mov	bx,2			; ���ன�⢮ STDERR
	mov	dx,offset message	; DS:DX - ���� ��ப�
	mov	cx,message_length	; CX - ����� ��ப�
	int	21h
	ret			; �����襭�� COM-䠩��

message	db	'This function can print $'
message_length = $-message	; ����� ��ப� = ⥪�騩 ���� �����
				; ���� ��砫� ��ப�
	end	start
