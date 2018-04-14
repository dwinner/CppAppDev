; dosin2.asm
; ����ࠦ��� ���⠬��� F, ���஥ ����� ��६���� �� �࠭� �����蠬� 
; �ࠢ����� ����஬ � ����� �����蠬� X � Z. ��室 �� �ணࠬ�� - Esc.
;
; ���������:
; TASM:
; tasm /m dosin2.asm
; tlink /t /x dosin2.obj
; MASM:
; ml /c dosin2.asm
; link dosin2.obj,,NUL,,,
; exe2bin dosin2.exe dosin2.com
; WASM
; wasm dosin2.asm
; wlink file dosin2.obj form DOS COM
;


line_length = 7		; �᫮ ᨬ����� � ��ப� ����ࠦ����
number_of_lines = 4	; �᫮ ��ப

	.model	tiny
	.code
	org	100h	; ��砫� COM-䠩��
start:
	cld		; ���� �ᯮ�짮������ ������� ��ப���� ��ࠡ�⪨
	mov	ax,0B800h	; ���� ��砫� ⥪�⮢�� ����������
	mov	es,ax		; � ES
	mov	ax,0003h
	int	10h		; ⥪�⮢� ०�� 03 (80x25)
	mov	ah,02h		; ��⠭����� �����
	mov	bh,0
	mov	dh,26		; �� ��ப� 26, � ���� �� �।��� �࠭�
	mov	dl,1
	int	10h		; ⥯��� ����� �� �࠭� ���

	call	update_screen	; �뢥�� ����ࠦ����

; �᭮���� 横� ���� ����������
main_loop:
	mov	ah,08h	; ����� ᨬ��� � ����������
	int	21h		; ��� ��, � ���������, � �஢�મ� �� Ctrl-Break
	test	al,al		; �᫨ AL = 0
	jz	eASCII_entered	; ������ ᨬ��� ���७���� ASCII
	cmp	al,1Bh		; ����: �᫨ ������ ᨬ��� 1Bh (Esc),
	je	key_ESC		; ��� �� �ணࠬ��,
	cmp	al,'Z'		; �᫨ ������ ᨬ��� Z,
	je	key_Z			; ��३� �� ��� ��ࠡ��稪
	cmp	al,'z'		; � �� ��� z
	je	key_Z
	cmp	al,'X'		; �᫨ ������ ᨬ��� X,
	je	key_X		; ��३� �� ��� ��ࠡ��稪
	cmp	al,'x'		; � �� ��� x
	je	key_X
	jmp short main_loop	; ����� ᫥������ �������

eASCII_entered:		; �� ������ ���७�� ASCII-ᨬ���
	int	21h		; ������� ��� ��� (������ �맮� �㭪樨)
	cmp	al,48h	; ��५�� �����
	je	key_UP
	cmp	al,50h	; ��५�� ����
	je	key_DOWN
	cmp	al,4Bh	; ��५�� �����
	je	key_LEFT
	cmp	al,4Dh	; ��५�� ��ࠢ�
	je	key_RIGHT
	jmp short main_loop	; ����� ᫥������ �������
;
; ��ࠡ��稪� ����⨩ ������
;
key_ESC:			; Esc
	ret				; �������� COM-�ணࠬ��
key_UP:			; ��५�� �����
	cmp	byte ptr start_row,0	; �᫨ ����ࠦ���� �� ���孥�
					; ��� �࠭�,
	jna	main_loop		; ����� ᫥������ �������,
	dec	byte ptr start_row ; ���� - 㬥����� ����� ��ப�,
	call	update_screen	; �뢥�� ����� ����ࠦ����
	jmp short main_loop	; � ����� ᫥������ �������

key_DOWN:			; ��५�� ����
	cmp	byte ptr start_row,25-number_of_lines ; �᫨ 
					; ����ࠦ���� �� ������ ��� �࠭�,
	jnb	main_loop		; ����� ᫥������ �������,
	inc	byte ptr start_row ; ���� - 㢥����� ����� ��ப�,
	call	update_screen	; �뢥�� ����� ����ࠦ����
	jmp short main_loop	; � ����� ᫥������ �������

key_LEFT:		; ��५�� �����
	cmp	byte ptr start_col,0	; �᫨ ����ࠦ���� �� ����� ��� 
					; �࠭�,
	jna	main_loop	; ����� ᫥������ �������,
	dec	byte ptr start_col	; ���� - 㬥����� �����, �⮫��
	call	update_screen	; �뢥�� ����� ����ࠦ����
	jmp short main_loop	; � ����� ᫥������ �������

key_RIGHT:		; ��५�� ��ࠢ�
	cmp	byte ptr start_col,80-line_length ; �᫨
				; ����ࠦ���� �� �ࠢ�� ��� �࠭�,
	jnb	main_loop	; ����� ᫥������ �������,
	inc	byte ptr start_col	; ���� - 㢥����� ����� �⮫��
	call	update_screen	; �뢥�� ����� ����ࠦ����
	jmp short main_loop	; � ����� ᫥������ �������

key_Z:			; ������ Z (��饭�� �����)
	mov	ax,current_screen ; ����� ����� ⥪�饣� ����ࠦ����
				; (���祭�� 0, 1, 2, 3),
	dec	ax		; 㬥����� ��� �� 1,
	jns	key_Z_ok	; �᫨ ����稫�� -1 (�������� ����),
	mov	ax,3		; AX = 3
key_Z_ok:
	mov	current_screen,ax ; ������� ����� ���⭮,
	call	update_screen	; �뢥�� ����� ����ࠦ����
	jmp	main_loop		; � ����� ᫥������ �������
key_X:			; ������ X (��饭�� ��ࠢ�)
	mov	ax,current_screen ; ����� ����� ⥪�饣� ����ࠦ����
				; (���祭�� 0, 1, 2, 3),
	inc	ax		; 㢥����� ��� �� 1,
	cmp	ax,4		; �᫨ ����� �⠫ ࠢ�� 4,
	jne	key_X_ok
	xor	ax,ax		; AX = 0
key_X_ok:
	mov	current_screen,ax ; ������� ����� ���⭮,
	call	update_screen	; �뢥�� ����� ����ࠦ����
	jmp	main_loop		; � ����� ᫥������ �������


; ��楤�� update_screen
; ��頥� �࠭ � �뢮��� ⥪�饥 ����ࠦ����
; ��������� ���祭�� ॣ���஢ AX, BX, CX, DX, SI, DI
update_screen:
	mov	cx,25*80	; �᫮ ᨬ����� �� �࠭�
	mov	ax,0F20h	; ᨬ��� 20h (�஡��) � ��ਡ�⮬ 0Fh
				; (���� �� �୮�)
	xor	di,di		; ES:DI = ��砫� ����������
	rep stosw		; ������ �࠭

	mov	bx,current_screen	; ����� ⥪�饣� ����ࠦ���� � BX
	shl	bx,1		; 㬭����� �� 2, ⠪ ��� screens - ���ᨢ ᫮�
	mov	si,screens[bx]	; �������� � BX ᬥ饭�� ��砫�
				; ⥪�饣� ����ࠦ���� �� ���ᨢ� 
				; screens,
	mov	ax,start_row	; ���᫨�� ���� ��砫�
	mul	row_length		; ����ࠦ���� � ����������
	add	ax,start_col	; (��ப� * 80 + �⮫���) * 2
	shl	ax,1
	mov	di,ax		; ES:DI - ��砫� ����ࠦ���� � 
				; ����������
	mov	ah,0Fh		; �ᯮ��㥬� ��ਡ�� - ���� �� �୮�
	mov	dx,number_of_lines ; �᫮ ��ப � ����ࠦ����
copy_lines:
	mov	cx,line_length	; �᫮ ᨬ����� � ��ப�
copy_1: lodsb			; ����� ASCII-��� � AL,
	stosw			; ������� ��� � �����������
				; (AL - ASCII, AH - ��ਡ��),
	loop	copy_1		; �뢥�� ⠪ �� ᨬ���� � ��ப�,
	add	di,(80-line_length)*2 ; ��ॢ��� DI �� ��砫�
				; ᫥���饩 ��ப� �࠭�,
	dec	dx			; �᫨ ��ப� �� �����稫��� -
	jnz	copy_lines		; �뢥�� ᫥������

	ret				; ����� ��楤��� update_screen

; ����ࠦ���� ���⠬��� F
screen1	db	'  ���ͻ'	; �뢮����� ����ࠦ����
	db	'�ͼ �ͼ'
	db	'�ͻ �  '
	db	'  �ͼ  '
screen2	db	'  �ͻ  '	; ������ �� 90 �ࠤ�ᮢ ��ࠢ�
	db	'�ͼ �ͻ'
	db	'���ͻ �'
	db	'    �ͼ'
screen3	db	'  �ͻ  '	; ������ �� 180 �ࠤ�ᮢ
	db	'  � �ͻ'
	db	'�ͼ �ͼ'
	db	'���ͼ  '
screen4	db	'�ͻ    '	; ������ �� 90 �ࠤ�ᮢ �����
	db	'� ���ͻ'
	db	'�ͻ �ͼ'
	db	'  �ͼ  '
; ���ᨢ, ᮤ�ঠ騩 ���� ��� ��ਠ�⮢ ����ࠦ����
screens	dw	screen1,screen2,screen3,screen4
current_screen	dw	0	; ⥪�騩 ��ਠ�� ����ࠦ����
start_row	dw	10	; ⥪��� ������ ��ப� ����ࠦ����
start_col	dw	37	; ⥪�騩 ���� �⮫���
row_length	db	80	; ����� ��ப� �࠭� ��� ������� MUL

	end	start
