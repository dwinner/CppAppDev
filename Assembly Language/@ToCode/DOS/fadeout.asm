; fadeout.asm
; �믮���� ������� ��襭�� �࠭�
;
; ���������:
; TASM:
; tasm /m fadeout.asm
; tlink /t /x fadeout.obj
; MASM:
; ml /c fadeout.asm
; link fadeout.obj,,NUL,,,
; exe2bin fadeout.exe fadeout.com
; WASM:
; wasm fadeout.asm
; wlink file fadeout.obj form DOS COM
;


	.model tiny
	.code
	.186			; ��� ������ insb/outsb
	org	100h		; COM-�ணࠬ��
start:
	cld			; ��� ������ ��ப���� ��ࠡ�⪨
	mov	di,offset palettes
	call	read_palette	; ��࠭��� ⥪���� �������, �⮡� 
				; ����⠭����� � ᠬ�� ���� �ணࠬ��,
	mov	di,offset palettes+256*3
	call	read_palette	; � ⠪�� ������� �� ���� ����� 
				; ⥪�饩 �������, ������ �㤥� 
				; ������஢���

	mov	cx,64	; ���稪 横�� ��������� �������
main_loop:
	push	cx
	call	wait_retrace	; ��������� ��砫� ���⭮�� 室� ���
	mov	di,offset palettes+256*3
	mov	si,di
	call	dec_palette	; 㬥����� �મ��� ��� 梥⮢
	call	wait_retrace	; ��������� ��砫� ᫥���饣� 
	mov	si,offset palettes+256*3	; ���⭮�� 室� ���
	call	write_palette	; ������� ����� �������
	pop	cx
	loop	main_loop	; 横� �믮������ 64 ࠧ� - �����筮 ��� 
; ���㫥��� ᠬ��� �મ�� 梥� (���ᨬ��쭮� 
; ���祭�� 6-��⭮� ���������� - 63)
	mov	si,offset palettes
	call	write_palette	; ����⠭����� ��ࢮ��砫��� �������
	ret			; ����� �ணࠬ��

; ��楤�� read_palette
; ����頥� ������� VGA � ��ப� �� ����� ES:DI
read_palette	proc	near
	mov	dx,03C7h	; ���� 03C7h - ������ DAC/०�� �⥭��
	mov	al,0		; ��稭��� � �㫥���� 梥�
	out	dx,al
	mov	dl,0C9h		; ���� 03C9h - ����� DAC
	mov	cx,256*3	; ������ 256 * 3 ����
	rep insb		; � ��ப� �� ����� ES:DI
	ret
read_palette	endp

; ��楤�� write_palette
; ����㦠�� � DAC VGA ������� �� ��ப� �� ����� DS:SI
write_palette	proc	near
	mov	dx,03C8h	; ���� 03C8h - ������ DAC/०�� �����
	mov	al,0		; ��稭��� � �㫥���� 梥�
	out	dx,al
	mov	dl,0C9h		; ���� 03C9h - ����� DAC
	mov	cx,256*3	; ����襬 256 * 3 ����
	rep outsb		; �� ��ப� � DS:SI
	ret
write_palette	endp

; ��楤�� dec_palette
; 㬥��蠥� ���祭�� ������� ���� �� 1 � ����饭��� (� ����, ��᫥ ⮣� ��� 
; ���� �⠭������ ࠢ�� ���, �� ����� �� 㬥��蠥���) �� ��ப� � DS:SI � 
; �����뢠�� १���� � ��ப� � DS:SI

dec_palette	proc	near
	mov	cx,256*3	; ����� ��ப� 256 * 3 ����
dec_loop:
	lodsb			; ������ ����,
	test	al,al		; �᫨ �� ����,
	jz	already_zero	; �ய����� ᫥������ �������
	dec	ax		; 㬥����� ���� �� 1
already_zero:
	stosb			; ������� ��� ���⭮
	loop	dec_loop	; ������� 256 * 3 ࠧ�
	ret
dec_palette	endp

; ��楤�� wait_retrace
; �������� ��砫� ᫥���饣� ���⭮�� 室� ���
wait_retrace	proc	near
	push	dx
	mov	dx,03DAh 
VRTL1:	in	al,dx		; ���� 03DAh - ॣ���� ISR1
	test	al,8
	jnz	VRTL1		; ��������� ���� ⥪�饣� ���⭮�� 室� ���,
VRTL2:	in	al,dx
	test	al,8
	jz	VRTL2		; � ⥯��� ��砫� ᫥���饣�
	pop	dx
	ret
wait_retrace endp

palettes:			; �� ���殬 �ணࠬ�� �� �࠭�� ��� ����� 
				; ������� - �ᥣ� 1,5 K�
end start
