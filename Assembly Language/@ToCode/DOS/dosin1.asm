; dosin1.asm
; ��ॢ���� �����筮� �᫮ � ��⭠����筮�
;
; ���������:
; TASM:
; tasm /m dosin1.asm
; tlink /t /x dosin1.obj
; MASM:
; ml /c dosin1.asm
; link dosin1.obj,,NUL,,,
; exe2bin dosin1.exe dosin1.com
; WASM
; wasm dosin1.asm
; wlink file dosin1.obj form DOS COM
;

	.model	tiny
	.code
	.286		; ��� ������� shr al,4
	org	100h	; ��砫� COM-䠩��
start:
	mov	dx,offset message1
	mov	ah,9
	int	21h		; �뢥�� �ਣ��襭�� � ����� message1
	mov	dx,offset buffer
	mov	ah,0Ah
	int	21h		; ����� ��ப� ᨬ����� � ����
	mov	dx,offset crlf
	mov	ah,9
	int	21h		; ��ॢ�� ��ப�

; ��ॢ�� �᫠ � ASCII-�ଠ� �� ���� � ����୮� �᫮ � AX
	xor	di,di		; DI = 0 - ����� ���� � ����
	xor	ax,ax		; AX = 0 - ⥪�饥 ���祭�� १����
	mov	cl,blength
	xor	ch,ch
	xor	bx,bx
	mov	si,cx		; SI - ����� ����
	mov	cl,10		; CL = 10, �����⥫� ��� MUL
asc2hex:
	mov	bl,byte ptr bcontents[di]
	sub	bl,'0'	; ��� = ��� ���� - ��� ᨬ���� "0"
	jb	asc_error	; �᫨ ��� ᨬ���� �� �����, 祬 ��� "0",
	cmp	bl,9		; ��� �����, 祬 "9",
	ja	asc_error	; ��� �� �ணࠬ�� � ᮮ�饭��� �� �訡��,
	mul	cx		; ����: 㬭����� ⥪�騩 १���� �� 10,
	add	ax,bx		; �������� � ���� ����� ����,
	inc	di		; 㢥����� ���稪
	cmp	di,si		; �᫨ ���稪+1 ����� �᫠ ᨬ����� -
	jb	asc2hex	; �த������
; (���稪 ��⠥��� �� 0)

; �뢮� �� �࠭ ��ப� message2
	push	ax		; ��࠭��� १���� �८�ࠧ������
	mov	ah,9
	mov	dx,offset message2
	int	21h
	pop	ax

; �뢮� �� �࠭ �᫠ �� ॣ���� AX
	push	ax
	xchg	ah,al		; �������� � AL ���訩 ����
	call	print_al	; �뢥�� ��� �� �࠭
	pop	ax		; ����⠭����� � AL ����訩 ����
	call	print_al	; �뢥�� ��� �� �࠭

	ret		; �����襭�� COM-䠩��

asc_error:
	mov	dx,offset err_msg
	mov	ah,9
	int	21h		; �뢥�� ᮮ�饭�� �� �訡��
	ret			; � �������� �ணࠬ��


; ��楤�� print_al.
; �뢮��� �� �࠭ �᫮ � ॣ���� AL � ��⭠����筮� �ଠ�
; ��������� ���祭�� ॣ���஢ AX � DX


print_al:
	mov	dh,al
	and	dh,0Fh		; DH - ����訥 4 ���
	shr	al,4		; AL - ���訥
	call	print_nibble	; �뢥�� ������ ����
	mov	al,dh		; ⥯��� AL ᮤ�ন� ����訥 4 ���
print_nibble:		; ��楤�� �뢮�� 4 ��� (��⭠����筮� ����)
	cmp	al,10		; �� �������, ��ॢ���騥 ���� � AL
	sbb	al,69h		; � ᮮ⢥�����騩 ASCII-���
	das			; (�. ���ᠭ�� ������� DAS)

	mov	dl,al		; ��� ᨬ���� � DL
	mov	ah,2		; ����� �㭪樨 DOS � AH
	int	21h		; �뢮� ᨬ����
	ret		; ��� RET ࠡ�⠥� ��� ࠧ� - ���� ࠧ ��� ������ ��
; ��楤��� print_nibble, �맢����� ��� ���襩 ����,
; � ��ன ࠧ - ��� ������ �� print_al

message1 db	'Enter decimal number: $'
message2 db	'Hex number is: $'
err_msg	db	'Bad number entered'
crlf	db	0Dh,0Ah,'$'
buffer	db	6		; ���ᨬ���� ࠧ��� ���� �����
blength	db	?		; ࠧ��� ���� ��᫥ ���뢠���
bcontents:			; ᮤ�ন��� ���� �ᯮ�������� ��
				; ���殬 COM-䠩��
end	start
