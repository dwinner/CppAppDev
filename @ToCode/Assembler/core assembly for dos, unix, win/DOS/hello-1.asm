; hello-1.asm
; �뢮��� �� �࠭ ᮮ�饭�� "Hello World!" � �����蠥���
;
; ���������:
; TASM:
; tasm /m hello-1.asm
; tlink /t /x hello-1.obj
; MASM:
; ml /c hello-1.asm
; link hello-1.obj,,NUL,,,
; exe2bin hello-1.exe hello-1.com
; WASM
; wasm hello-1.asm
; wlink file hello-1.obj form DOS COM
;

	.model tiny		; ������ �����, �ᯮ��㥬�� ��� COM
	.code			; ��砫� ᥣ���� ����
	org	100h		; ��砫쭮� ���祭�� ���稪� - 100h
start:	mov	ah,9		; ����� �㭪樨 DOS - � AH
	mov	dx,offset message	; ���� ��ப� - � DX
	int	21h		; �맮� ��⥬��� �㭪樨 DOS
	ret			; �����襭�� COM-�ணࠬ��
message	db	'Hello World!',0Dh,0Ah,'$'	; ��ப�
	end	start		; ����� �ணࠬ��
