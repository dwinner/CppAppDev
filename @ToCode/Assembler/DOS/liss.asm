; liss.asm
; ��ந� 䨣��� ���ᠦ�, �ᯮ���� ��䬥⨪� � 䨪�஢����� ����⮩ � 
; ������� ⠡���� ��ᨭ�ᮢ
; ������ ���ᠦ� - ᥬ���⢮ �ਢ��, ���������� ��ࠬ����᪨�� ��ࠦ���ﬨ
; x(t) = cos(SCALE_V * t)
; y(t) = sin(SCALE_H * t)
;
; �⮡� ����� ����� 䨣���, ������� ��ࠬ���� SCALE_H � SCALE_V
; ��� ����஥��� ����������� 䨣�� 㤠��� ��ப� add di,512 � ��楤��
; move_point
;
; ���������:
; TASM:
; tasm /m liss.asm
; tlink /t /x liss.obj
; MASM:
; ml /c liss.asm
; link liss.obj,,NUL,,,
; exe2bin liss.exe liss.com
; WASM:
; wasm liss.asm
; wlink file liss.obj form DOS COM
;


	.model	tiny
	.code
	.386		; ���� �ᯮ�짮������ 32-���� ॣ�����
	org	100h	; COM-�ணࠬ��

SCALE_H	equ	3	; �᫮ ��ਮ��� � 䨣�� �� ��ਧ��⠫�
SCALE_V	equ	5	; �᫮ ��ਮ��� �� ���⨪���

start	proc	near
	cld			; ��� ������ ��ப���� ��ࠡ�⪨

	mov	di,offset cos_table ; ���� ��砫� ⠡���� ��ᨭ�ᮢ
	mov	ebx,16777137 ; 224 * cos(360/2048) - ��࠭�� ���᫥����
	mov	cx,2048	; �᫮ ����⮢ ��� ⠡����
	call	build_table	; ����ந�� ⠡���� ��ᨭ�ᮢ

	mov	ax,0013h	; ����᪨� ०��
	int	10h		; 320x200x256

	mov	ax,1012h	; ��⠭����� ����� ॣ���஢ ������� VGA,
	mov	bx,70h	; ��稭�� � ॣ���� 70h
	mov	cx,4		; ���� ॣ����
	mov	dx,offset palette ; ���� ⠡���� 梥⮢
	int	10h

	push	0A000h	; ᥣ����� ���� ����������
	pop	es		; � ES

main_loop:
	call	display_picture ; ����ࠧ��� ��� � ᫥���

	mov	dx,5000
	xor	cx,cx
	mov	ah,86h
	int	15h		; ��㧠 �� CX:DX ����ᥪ㭤

	mov	ah,11h	; �஢����, �뫠 �� ����� ������,
	int	16h
	jz	main_loop	; �᫨ ��� - �த������ �᭮���� 横�

	mov	ax,0003h	; ⥪�⮢� ०��
	int	10h		; 80x24

	ret			; ����� �ணࠬ��
start	endp

; ��楤�� build_table
; ��ந� ⠡���� ��ᨭ�ᮢ � �ଠ� � 䨪�஢����� ����⮩ 8:24
; �� ४��७⭮� ��㫥 cos(xk) = 2 * cos(span/steps) * cos(xk-1) - cos(xk-2),
; ��� span - ࠧ��� ������, �� ���ன ��������� ��ᨭ��� (���ਬ�� 360),
; � steps - �᫮ 蠣��, �� ����� ࠧ�������� �������
; ����: DS:DI = ���� ⠡����
;	DS:[DI] = 224
;	EBX = 224 * cos(span/steps)
;	CX = �᫮ ����⮢ ⠡����, ����� ���� ���᫨��
; �뢮�: ⠡��� ࠧ��஬ CX * 4 ���� ���������
; ������������: DI,CX,EAX,EDX

build_table	proc	near
	mov	dword ptr [di+4],ebx ; ��������� ��ன ����� ⠡����
	sub	cx,2			; ��� ����� 㦥 ���������
	add	di,8
	mov	eax,ebx
build_table_loop:
	imul	ebx			; 㬭����� cos(span/steps) �� cos(xk-1)
	shrd	eax,edx,23		; ���ࠢ�� ��-�� ����⢨� � 䨪�஢�����
; ����⮩ 8:24 � 㬭������ �� 2
	sub	eax,dword ptr [di-8] ; ���⠭�� cos(xk-2)
	stosd				; ������ १���� � ⠡����
	loop	build_table_loop
	ret
build_table	endp

; ��楤�� display_picture
; ����ࠦ��� ��� � ᫥���

display_picture	proc	near

	call	move_point	; ��६����� ���

	mov	bp,73h	; ⥬��-��� 梥� � ��襩 ������
	mov	bx,3		; �窠, �뢥������ �� 蠣� �����
	call	draw_point	; ����ࠧ��� ��
	dec	bp		; 72h - ��� 梥� � ��襩 ������
	dec	bx		; �窠, �뢥������ ��� 蠣� �����
	call	draw_point	; ����ࠧ��� ��
	dec	bp		; 71h - ᢥ⫮-��� 梥� � ��襩 ������
	dec	bx		; �窠, �뢥������ ���� 蠣 �����
	call	draw_point	; ����ࠧ��� ��
	dec	bp		; 70h - ���� 梥� � ��襩 ������ 
	dec	bx		; ⥪��� �窠
	call	draw_point	; ����ࠧ��� ��
	ret
display_picture	endp

; ��楤�� draw_point
; ����: BP - 梥�
; 	BX - ᪮�쪮 蠣�� ����� �뢮������ �窠
;
draw_point proc near
	movzx	cx,byte ptr point_x[bx] ; X-���न���
	movzx	dx,byte ptr point_y[bx]	; Y-���न���
	call	putpixel_13h	; �뢮� �窨 �� �࠭
	ret
draw_point endp

; ��楤�� move_point
; ������ ���न���� ��� ᫥���饩 �窨, ������� ���न���� �祪, 
; �뢥������ ࠭��

move_point proc near
	inc	word ptr time
	and	word ptr time,2047	; �� ��� ������� �࣠������
; ���稪 � ��६����� time, ����� 
; ��������� �� 0 �� 2047 (7FFh)

	mov	eax,dword ptr point_x	; ����� ���न���� �祪 
	mov	ebx,dword ptr point_y	; (�� ����� �� ���)
	mov	dword ptr point_x[1],eax ; � ������� �� � ᤢ����
	mov	dword ptr point_y[1],ebx ; 1 ����

	mov	di,word ptr time	; 㣮� (��� �६�) � DI
	imul	di,di,SCALE_H	; 㬭����� ��� �� SCALE_H
	and	di,2047		; ���⮪ �� ������� �� 2048
	shl	di,2			; ⠪ ��� � ⠡��� 4 ���� �� ��ᨭ��
	mov	ax,50			; ����⠡ �� ��ਧ��⠫�
	mul	word ptr cos_table[di+2] ; ��������� �� ��ᨭ��. 
; ������ ���襥 ᫮�� (ᬥ饭�� + 2) �� 
; ��ᨭ��, ����ᠭ���� � �ଠ� 8:24, 
; 䠪��᪨ �ந�室�� 㬭������ �� ��ᨭ�� � 
; �ଠ� 8:8
	mov	dx,0A000h	; 320/2 (X 業�� �࠭�) � �ଠ� 8:8
	sub	dx,ax		; �ᯮ������ 業�� 䨣��� � 業�� �࠭�
	mov	byte ptr point_x,dh ; � ������� ����� ⥪���� ���

	mov	di,word ptr time	; 㣮� (��� �६�) � DI 
	imul	di,di,SCALE_V	; 㬭����� ��� �� SCALE_V
	add	di,512		; �������� 90 �ࠤ�ᮢ, �⮡� �������� 
; ��ᨭ�� �� ᨭ��. ��� ��� � ��� 2048
; 蠣�� �� 360 �ࠤ�ᮢ, 90 �ࠤ�ᮢ - �� 
; 512 蠣��
	and	di,2047		; ���⮪ �� ������� �� 2048,
	shl	di,2			; ⠪ ��� � ⠡��� 4 ���� �� ��ᨭ��
	mov	ax,50			; ����⠡ �� ���⨪���
	mul	word ptr cos_table[di+2] ; 㬭������ �� ��ᨭ��
	mov	dx,06400h	; 200/2 (Y 業�� �࠭�) � �ଠ� 8:8
	sub	dx,ax		; �ᯮ������ 業�� 䨣��� � 業�� �࠭�
	mov	byte ptr point_y,dh ; � ������� ����� ⥪���� ���
	ret
move_point endp

; putpixel_13h
; ��楤�� �뢮�� �窨 �� �࠭ � ०��� 13h
; DX = ��ப�, CX = �⮫���, BP = 梥�, ES = A000h
putpixel_13h	proc	near
	push	di
	mov	ax,dx	; ����� ��ப�
	shl	ax,8	; 㬭����� �� 256
	mov	di,dx
	shl	di,6	; 㬭����� �� 64
	add	di,ax	; � ᫮���� - � ��, �� � 㬭������ �� 320
	add	di,cx	; �������� ����� �⮫��
	mov	ax,bp
	stosb		; ������� � �����������
	pop	di
	ret
putpixel_13h	endp

point_x	db	0FFh,0FFh,0FFh,0FFh ; X-���न���� �窨 � 墮��
point_y	db	0FFh,0FFh,0FFh,0FFh ; Y-���न���� �窨 � 墮��
	db	?	; ���⮩ ���� - �㦥� ��� ������ ᤢ��� ���न��� 
			; �� ���� ����
time	dw	0		; ��ࠬ��� � �ࠢ������ ���ᠦ� - �६� ��� 㣮�

palette	db	3Fh,3Fh,3Fh	; ����
	db	30h,30h,30h	; ᢥ⫮-���
	db	20h,20h,20h	; ���
	db	10h,10h,10h	; ⥬��-���

cos_table	dd	1000000h ; ����� ��稭����� ⠡��� ��ᨭ�ᮢ
	end	start
