; hello-2.asm
; �뢮��� �� �࠭ ᮮ�饭�� "Hello World!" � �����蠥���
;
; ���������:
; TASM:
; tasm /m hello-2.asm
; tlink /x hello-2.obj
; MASM:
; ml /c hello-2.asm
; link hello-2.obj
; WASM:
; wasm hello-2.asm
; wlink file hello-2.obj form DOS
;
	.model	small	; ������ �����, �ᯮ��㥬�� ��� EXE
	.stack	100h	; ᥣ���� �⥪� ࠧ��஬ � 256 ���⮢
	.code
start:	mov	ax,DGROUP	; ᥣ����� ���� ��ப� message
	mov	ds,ax		; ����頥��� � DS
	mov	dx,offset message
	mov	ah,9
	int	21h		; �㭪�� DOS "�뢮� ��ப�"
	mov	ax,4C00h
	int	21h		; �㭪�� DOS "�������� �ணࠬ��"
	.data
message	db	'Hello World!',0Dh,0Ah,'$'
	end	start

