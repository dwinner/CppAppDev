; mousedr.asm
; ����� �� �࠭� ���� ����� � ���栬� � �������, 㪠�뢠���� �����
;
; ���������:
; TASM:
; tasm /m mousedr.asm
; tlink /t /x mousedr.obj
; MASM:
; ml /c mousedr.asm
; link mousedr.obj,,NUL,,,
; exe2bin mousedr.exe mousedr.com
; WASM:
; wasm mousedr.asm
; wlink file mousedr.obj form DOS COM
;

	.model	tiny
	.code
	org	100h		; COM-䠩�
	.186			; ��� ������� shr cx,3
start:
	mov	ax,12h
	int	10h		; �����०�� 640x480
	mov	ax,0		; ���樠����஢��� ����
	int	33h
	mov	ax,1		; �������� ����� ���
	int	33h

	mov	ax,000Ch	; ��⠭����� ��ࠡ��稪 ᮡ�⨩ ���
	mov	cx,0002h	; ᮡ�⨥ - ����⨥ ����� ������
	mov	dx,offset handler ; ES:DX - ���� ��ࠡ��稪�
	int	33h

	mov	ah,0		; �������� ������ �� ������
	int	16h
	mov	ax,000Ch
	mov	cx,0000h	; 㤠���� ��ࠡ��稪 ᮡ�⨩ ���
	int	33h
	mov	ax,3		; ⥪�⮢� ०��
	int	10h
	ret			; ����� �ணࠬ��

; ��ࠡ��稪 ᮡ�⨩ ���: �� ��ࢮ� ����⨨ �뢮��� ��� �� �࠭,
; �� ������ ���쭥�襬 �맮�� �஢���� ����� ����� �� �।��饩 �窨 � 
; ⥪�饩

handler:
	push	0A000h
	pop	es		; ES - ��砫� ���������� 
	push	cs
	pop	ds		; DS - ᥣ���� ���� � ������ �⮩ �ணࠬ��
	push	cx		; CX (X-���न���) � 
	push	dx		; DX (Y-���न���) ���ॡ����� � ����

	mov	ax,2		; ������ ����� ��� ��। �뢮��� �� �࠭
	int	33h

	cmp	word ptr previous_X,-1	; �᫨ �� ���� �맮�,
	je	first_point		; ⮫쪮 �뢥�� ���,

	call	line_bresenham		; ���� - �஢��� �����
exit_handler:
	pop	dx			; ����⠭����� CX � DX
	pop	cx
	mov	previous_X,cx		; � ��������� �� ��� �।��騥
	mov	previous_Y,dx		; ���न����

	mov	ax,1		; �������� ����� ���
	int	33h

	retf			; ��室 �� ��ࠡ��稪� - ������� RETF

first_point:
	call	putpixel1b	; �뢮� ����� �窨 (�� ��ࢮ� �맮��)
	jmp short exit_handler


; ��楤�� �ᮢ���� ��אַ� ����� � �ᯮ�짮������ �����⬠ �१��堬�
; ����: CX,DX - X, Y ����筮� �窨
; previous_X,previous_Y - X, Y ��砫쭮� �窨
 
line_bresenham:
	mov	ax,cx
	sub	ax,previous_X	; AX = ����� �஥�樨 ��אַ� �� ��� X
	jns	dx_pos			; �᫨ AX ����⥫�� - 
	neg	ax				; ᬥ���� ��� ����, ��祬
	mov	word ptr X_increment,1	; ���न��� X �� �뢮��
	jmp short dx_neg			; ��אַ� �㤥� ���,
dx_pos:	mov	word ptr X_increment,-1 ; � ���� - 㬥�������

dx_neg:	mov	bx,dx
	sub	bx,previous_Y	; BX = ����� �஥�樨 ��אַ� �� ��� Y
	jns	dy_pos			; �᫨ BX ����⥫�� - 
	neg	bx				; ᬥ���� ��� ����, ��祬
	mov	word ptr Y_increment,1	; ���न��� Y �� �뢮��
	jmp short dy_neg			; ��אַ� �㤥� ���,
dy_pos:	mov	word ptr Y_increment,-1	; � ���� - 㬥�������
dy_neg:
	shl	ax,1		; 㤢���� ���祭�� �஥�権,
	shl	bx,1		; �⮡� �������� ࠡ��� � ����楫묨 �᫠��

	call	putpixel1b	; �뢥�� ����� ��� (��ﬠ� ������ ��
; CX,DX � previous_X,previous_Y
	cmp	ax,bx		; �᫨ �஥��� �� ��� X �����, 祬 �� Y:
	jna	dx_le_dy
	mov	di,ax		; DI �㤥� 㪠�뢠��, � ����� ��஭� ��
	shr	di,1		; �⪫������� �� �����쭮� ��אַ�
	neg	di		; ��⨬��쭮� ��砫쭮� ���祭�� DI:
	add	di,bx		; DI = 2 * dy - dx.
cycle:
	cmp	cx,word ptr previous_X	; �᭮���� 横� �믮������,
	je	exit_bres		; ���� X �� �⠭�� ࠢ�� previous_X
	cmp	di,0				; �᫨ DI > 0,
	jl	fractlt0
	add	dx,word ptr Y_increment	; ��३� � ᫥���饬� Y
	sub	di,ax				; � 㬥����� DI �� 2 * dx
fractlt0:
	add	cx,word ptr X_increment	; ᫥���騩 X (�� ������ 蠣�)
	add	di,bx			; 㢥����� DI �� 2 * dy
	call	putpixel1b		; �뢥�� ���
	jmp short cycle		; �த������ 横�

dx_le_dy:			; �᫨ �஥��� �� ��� Y �����, 祬 �� X
	mov	di,bx
	shr	di,1
	neg	di		; ��⨬��쭮� ��砫쭮� ���祭�� DI:
	add	di,ax		; DI = 2 * dx - dy
cycle2:
	cmp	dx,word ptr previous_Y	; �᭮���� 横� �믮������,
	je	exit_bres		; ���� Y �� �⠭�� ࠢ�� previous_Y,
	cmp	di,0				; �᫨ DI > 0
	jl	fractlt02
	add	cx,word ptr X_increment	; ��३� � ᫥���饬� X
	sub	di,bx				; � 㬥����� DI �� 2 * dy
fractlt02:
	add	dx,word ptr Y_increment	; ᫥���騩 Y (�� ������ 蠣�)
	add	di,ax			; 㢥����� DI �� 2 * dy
	call	putpixel1b		; �뢥�� ���
	jmp short cycle2		; �த������ 横�
exit_bres:
	ret				; ����� ��楤���

; ��楤�� �뢮�� �窨 �� �࠭ � ०���, �ᯮ����饬 ���� ��� ���
; �࠭���� ������ ���ᥫ�. 
; DX = ��ப�, CX = �⮫���
; �� ॣ����� ��࠭�����

putpixel1b:
	pusha			; ��࠭��� ॣ�����
	xor	bx,bx
	mov	ax,dx		; AX = ����� ��ப�
	imul	ax,ax,80	; AX = ����� ��ப� * �᫮ ���⮢ � ��ப�
	push	cx
	shr	cx,3		; CX = ����� ���� � ��ப�
	add	ax,cx		; AX = ����� ���� � ����������
	mov	di,ax		; �������� ��� � SI � DI ��� ������
	mov	si,di		; ��ப���� ��ࠡ�⪨

	pop	cx		; CX ᭮�� ᮤ�ন� ����� �⮫��
	mov	bx,0080h
	and	cx,07h	; ��᫥���� �� ��� CX = 
; ���⮪ �� ������� �� 8 = 
; ����� ��� � ����, ���� �ࠢ� ������
	shr	bx,cl		; ⥯��� � BL ��⠭����� � 1 �㦭� ���
	lods	es:byte ptr some_label	; AL = ���� �� ����������
	or	ax,bx		; ��⠭����� �뢮���� ��� � 1
; �⮡� ����� ���ᥫ� � �࠭�, ��� ������� OR ����� �������� �� 
; not bx
; and ax,bx
; ��� ���� ���樠����஢��� BX �� �᫮� 0080h, � �᫮� FF7Fh � �ᯮ�짮���� 
; ⮫쪮 and
	stosb			; � ��୥� ���� �� ����
	popa			; ����⠭���� ॣ�����
	ret			; �����

previous_X	dw	-1	; �।���� X-���न���
previous_Y	dw	-1	; �।���� Y-���न��� 
Y_increment	dw	-1	; ���ࠢ����� ��������� Y
X_increment	dw	-1	; ���ࠢ����� ��������� X
some_label:			; ��⪠, �ᯮ��㥬�� ��� ��८�।������ 
; ᥣ����-���筨�� ��� lods � DS �� ES
	end	start

