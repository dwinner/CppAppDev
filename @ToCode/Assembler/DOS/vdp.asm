; vdp.asm
; �襭�� �ࠢ����� ���-���-����
; x(t)'' = -x(t) + m(1-x(t)2)x(t)'
; � m = 0, 1, 2, 3, 4, 5, 6, 7, 8
;
; �ணࠬ�� �뢮��� �� �࠭ �襭�� � m = 1, ����⨥ ������ 0 - 8 ������� m
; Esc - ��室, �� ��㣠� ������ - ��㧠 �� ������ ����� �� Esc, 0 - 8
;
; ���������:
; TASM:
;  tasm /m vdp.asm
;  tlink /t /x vdp.obj
; MASM:
;  ml /c vdp.asm
;  link vdp.obj,,NUL,,,
;  exe2bin vdp.exe vdp.com
; WASM:
;  wasm vdp.asm
;  wlink file vdp.obj form DOS COM
;

	.model tiny
	.286		; ��� ������ pusha � popa
	.287		; ��� ������ FPU
	.code
	org 100h	; COM-�ணࠬ��

start	proc	near
	cld
	push	0A000h
	pop	es	; ���� ���������� � ES

	mov	ax,0012h
	int	10h	; ����᪨� ०�� 640x480x16

	finit		; ���樠����஢��� FPU

	xor	si, si	; SI �㤥� ᮤ�ঠ�� ���न���� t � ��������
			; �� 0 �� 640
	fld1			; 1
	fild word ptr hinv ; 32, 1
	fdiv			; h		(h = 1/hinv)
; ��⠭���� ��砫��� ���祭�� ��� _display:
; m = 1, x = h = 1/32, y = x' = 0
again: fild word ptr m	; m, h
	fld	st(1)		; x, m, h	(x = h)
	fldz			; y, x, m, h	(y = 0)
	call	_display	; �뢮���� �� �࠭ �襭��, ����
				; �� �㤥� ����� ������
g_key: mov	ah, 10h	; �⥭�� ������ � ���������
	int	16h		; ��� ����⮩ ������ � AL,
	cmp	al, 1Bh	; �᫨ �� Esc,
	jz	g_out		; ��� �� �ணࠬ��,
	cmp	al,'0'	; �᫨ ��� ����� '0',
	jb	g_key		; ��㧠/�������� ᫥���饩 ������,
	cmp	al,'8'	; �᫨ ��� ����� '8',
	ja	g_key		; ��㧠/�������� ᫥���饩 ������, 
	sub	al,'0'	; ����: AL = ��������� ���,
	mov	byte ptr m,al ; m = ��������� ��� 
	fstp	st(0)		; x, m, h
	fstp	st(0)		; m, h
	fstp	st(0)		; h
	jmp short again

g_out:	mov	ax,0003h	; ⥪�⮢� ०��
	int	10h
	ret			; ����� �ணࠬ��
start	endp

; ��楤�� display_
; ���� �� ����� ������, �뢮��� �襭�� �� �࠭, ����� ���� ��᫥ ������ ��
; 640 �祪
;
_display	proc	near
dismore:
	mov	bx,0		; ����� �।����� ���: 梥� = 0
	mov	cx,si
	shr	cx,1		; CX - ��ப�
	mov	dx,240
	sub	dx,word ptr ix[si] ; DX - �⮫���
	call	putpixel1b
	call	next_x	; ���᫨�� x(t) ��� ᫥���饣� t
	mov	bx,1		; �뢥�� ���: 梥� = 1
	mov	dx,240
	sub	dx,word ptr ix[si] ; DX - �⮫���
	call	putpixel1b
	inc	si
	inc	si		; SI = SI + 2 (���ᨢ ᫮�),
	cmp	si,640*2	; �᫨ SI ���⨣�� ���� ���ᨢ� IX
	jl	not_endscreen ; �ய����� ����
	sub	si,640*2	; ����⠢��� SI �� ��砫� ���ᨢ� IX
not_endscreen:
	mov	dx,5000
	xor	cx,cx
	mov	ah,86h
	int	15h		; ��㧠 �� CX:DX ����ᥪ㭤

	mov	ah,11h
	int	16h		; �஢����, �뫠 �� ����� ������,
	jz	dismore	; �᫨ ��� - �த������ �뢮� �� �࠭,
	ret			; ���� - �������� ��楤���
_display	endp

; ��楤�� next_x
; �஢���� ���᫥��� �� ��㫠�:
; y = y + h(m(1-x^2)y-x)
; x = x + hy
; ����: st = y, st(1) = x, st(2) = m, st(3) = h
; �뢮�: st = y, st(1) = x, st(2) = m, st(3) = h, x * 100 �����뢠���� � ix[si]
next_x	proc	near
	fld1			; 1, y, x, m, h
	fld	st(2)		; x, 1, y, x, m, h
	fmul	st,st(3)	; x2, 1, y, x, m, h
	fsub			; (1-x2), y, x, m, h
	fld	st(3)		; m, (1-x2), y, x, m, h
	fmul			; M, y, x, m, h		(M = m(1-x2))
	fld	st(1)		; y, M, y, x, m, h
	fmul			; My, y, x, m, h
	fld	st(2)		; x, My, y, x, m, h
	fsub			; My-x, y, x, m, h
	fld	st(4)		; h, My-x, y, x, m, h
	fmul			; h(My-x), y, x, m, h
	fld	st(1)		; y, h(My-x), y, x, m, h
	fadd			; Y, y, x, m, h		(Y = y + h(My-x))
	fxch			; y, Y, x, m, h
	fld	st(4)		; h, y, Y, x, m, h
	fmul			; yh, Y, x, m, h
	faddp	st(2),st	; Y, X, m, h		(X = x  +  hy)
	fld	st(1)		; X, Y, X, m, h
	fild	word ptr c_100	; 100, X, Y, X, m, h
	fmul		; 100X, Y, X, m, h
	fistp	word ptr ix[si]	; Y, X, m, h
	ret
next_x	endp

; ��楤�� �뢮�� �窨 �� �࠭ � ०���, �ᯮ����饬 1 ��� �� ���ᥫ�
; DX = ��ப�, CX = �⮫���, ES = A000h, BX = 梥� (1 - ����, 0 - ���)
; �� ॣ����� ��࠭�����

putpixel1b	proc	near
	pusha			; ��࠭��� ॣ�����
	push	bx
	xor	bx,bx
	mov	ax,dx		; AX = ����� ��ப�
	imul	ax,ax,80	; AX = ����� ��ப� * �᫮ ���⮢ � ��ப�
	push	cx
	shr	cx,3		; CX = ����� ���� � ��ப�
	add	ax,cx		; AX = ����� ���� � ����������
	mov	di,ax		; �������� ��� � DI � SI
	mov	si,di 

	pop	cx		; CX ᭮�� ᮤ�ন� ����� �⮫��
	mov	bx,0080h
	and	cx,07h	; ��᫥���� �� ��� CX = 
; ���⮪ �� ������� �� 8 =
; ����� ��� � ����, ���� �ࠢ� ������
	shr	bx,cl		; ⥯��� � BL ��⠭����� � 1 �㦭� ���
	lods	es:byte ptr ix	; AL = ���� �� ����������
	pop	dx
	dec	dx		; �஢���� 梥�:
	js	black		; �᫨ 1 -
	or	ax,bx		; ��⠭����� �뢮���� ��� � 1,
	jmp	short	white
black:	not	bx	; �᫨ 0 - 
	and	ax,bx		; ��⠭����� �뢮���� 梥� � 0,
white:
	stosb			; � ������ ���� �� ����
	popa			; ����⠭����� ॣ�����
	ret			; �����
putpixel1b	endp


m	dw	1		; ��砫쭮� ���祭�� m
c_100	dw	100		; ����⠡ �� ���⨪���
hinv	dw	32		; ��砫쭮� ���祭�� 1/h 
ix:				; ��砫� ���� ��� ���祭�� x(t)
				; (�ᥣ� 1280 ���⮢ �� ���殬 �ணࠬ��)
	end	start
