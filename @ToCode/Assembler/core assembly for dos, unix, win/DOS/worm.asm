; worm.asm
; ��� "��⮭" (��� "����", ��� "����"). ��ࠢ����� �����⢫���� �����蠬� 
; �ࠢ����� ����஬, ��⮭ ��������, �᫨ �� ��室�� �� ������ ��� ������
; �࠭��� �࠭� ��� ᠬ����ᥪ�����.
;
; ���������:
; TASM:
; tasm /m worm.asm
; tlink /t /x worm.obj
; MASM:
; ml /c worm.asm
; link worm.obj,,NUL,,,
; exe2bin worm.exe worm.com
; WASM:
; wasm worm.asm
; wlink file worm.obj form DOS COM
;

	.model tiny
	.code
	.186				; ��� ������� push 0A00h
	org	100h			; COM-䠩�
start:
	mov	ax,cs			; ⥪�騩 ᥣ����� ���� ����
	add	ax,1000h		; 1000h = ᫥���騩 ᥣ����,
	mov	ds,ax			; ����� �㤥� �ᯮ�짮������
; ��� ���ᮢ ������ � 墮��
	push	0A000h		; 0A000h - ᥣ����� ����
	pop	es			; ���������� (� ES)
	mov	ax,13h		; ����᪨� ०�� 13h
	int	10h

	mov	di,320*200
	mov	cx,600h		; ��������� ���� ����������,
; ��������� �� �।����� 
	rep	stosb			; �࠭�, ���㫥�묨 ���祭�ﬨ
; (�⮡� ��⮭ �� ᬮ� ��� �� 
; �।��� �࠭�)
	xor	si,si			; ��砫�� ���� 墮�� � DS:SI
	mov	bp,10			; ��砫쭠� ����� ��⮭� - 10
	jmp	init_food		; ᮧ���� ����� ���
main_cycle:
; �ᯮ�짮����� ॣ���஢ � �⮩ �ணࠬ��:
; AX - ࠧ��筮�
; BX - ���� ������, 墮�� ��� ��� �� �࠭�
; CX - 0 (���襥 ᫮�� �᫠ ����ᥪ㭤 ��� �㭪樨 ����প�)
; DX - �� �ᯮ������ (����������� ��楤�ன random)
; DS - ᥣ���� ������ �ணࠬ�� (᫥���騩 ��᫥ ᥣ���� ����)
; ES - �����������
; DS:DI - ���� ������
; DS:SI - ���� 墮��
; BP - ������筠� ����� (��⮭ ����, ���� BP > 0, BP 㬥��蠥��� �� ������ 蠣�,
; ���� �� �⠭�� �㫥�)

	mov	dx,20000		; ��㧠 - 20 000 ����ᥪ㭤
	mov	ah,86h		; (CX = 0 ��᫥ REP STOSB � 
				; ����� �� �������)
	int	15h			; ����প�

	mov	ah,1			; �஢�ઠ ���ﭨ� ����������
	int	16h
	jz	short no_keypress	; �᫨ ������ �� ����� - 
	xor	ah,ah			; AH = 0 - ����� ᪠�-���
	int	16h			; ����⮩ ������ � AH,
	cmp	ah,48h		; �᫨ �� ��५�� �����,
	jne	short not_up
	mov	word ptr cs:move_direction,-320 ; �������� 
; ���ࠢ����� �������� �� "�����",
not_up:
	cmp	ah,50h		; �᫨ �� ��५�� ����,
	jne	short not_down
	mov	word ptr cs:move_direction,320 ; ��������
; ���ࠢ����� �������� �� "����",
not_down:
	cmp	ah,4Bh		; �᫨ �� ��५�� �����,
	jne	short not_left
	mov	word ptr cs:move_direction,-1 ; ��������
; ���ࠢ����� �������� �� "�����",
not_left:
	cmp	ah,4Dh		; �᫨ �� ��५�� ��ࠢ�,
	jne	short no_keypress
	mov	word ptr cs:move_direction,1 ; ��������
				; ���ࠢ����� �������� �� "��ࠢ�",
no_keypress:
	and	bp,bp			; �᫨ ��⮭ ���� (BP > 0),
	jnz	short advance_head ; �ய����� ��࠭�� 墮��,
	lodsw				; ����: ����� ���� 墮�� �� 
					; DS:SI � AX � 㢥����� SI �� 2
	xchg	bx,ax
	mov	byte ptr es:[bx],0	; ����� 墮�� �� �࠭�,
	mov	bx,ax
	inc	bp			; 㢥����� BP, �⮡� ᫥����� 
					; ������� ���㫠 ��� � 0,
advance_head:
	dec	bp			; 㬥����� BP, ⠪ ��� ��⮭ 
; ���� �� 1, �᫨ ��࠭�� 墮�� �뫮 �ய�饭�, ��� �⮡� ������ ��� � 0 - � 
; ��㣮� ��砥
	add	bx,word ptr cs:move_direction
; bx = ᫥����� ���न��� ������
	mov	al,es:[bx]	; �஢���� ᮤ�ন��� �࠭� � �窥 �
				; �⮩ ���न��⮩,
	and	al,al		; �᫨ ⠬ ��祣� ���,
	jz	short move_worm	; ��।������ ������,
	cmp	al,0Dh		; �᫨ ⠬ ���,
	je	short grow_worm	; 㢥����� ����� ��⮭�,
	mov	ax,3			; ���� - ��⮭ 㬥�,
	int	10h			; ��३� � ⥪�⮢� ०��
	retn				; � �������� �ணࠬ��

move_worm:
	mov	[di],bx	; �������� ���� ������ � DS:DI
	inc	di
	inc	di		; � 㢥����� DI �� 2,
	mov	byte ptr es:[bx],09	; �뢥�� ��� �� �࠭,
	cmp	byte ptr cs:eaten_food,1 ; �᫨ �।��騬 
					; 室�� �뫠 �ꥤ��� ���,
	je	if_eaten_food	; ᮧ���� ����� ���,
	jmp	short main_cycle	; ���� - �த������ �᭮���� 
					; 横�

grow_worm:
	push	bx			; ��࠭��� ���� ������
	mov	bx,word ptr cs:food_at	; bx - ���� ���
	xor	ax,ax			; AX = 0 
	call	draw_food		; ����� ���
	call	random		; AX - ��砩��� �᫮
	and	ax,3Fh		; AX - ��砩��� �᫮ �� 0 �� 63
	mov	bp,ax			; �� �᫮ �㤥� �������� � 
					; ����� ��⮭�
	mov	byte ptr cs:eaten_food,1 ; ��⠭����� 䫠�
				; ��� �����樨 ��� �� ᫥���饬 室�
	pop	bx		; ����⠭����� ���� ������ BX
	jmp	short move_worm	; ��३� � �������� ��⮭�

if_eaten_food:		; ���室 �, �᫨ ��� �뫠 �ꥤ���
	mov	byte ptr cs:eaten_food,0 ; ����⠭����� 䫠�
init_food:			; ���室 � � ᠬ�� ��砫�
	push	bx			; ��࠭��� ���� ������
make_food:
	call	random		; AX - ��砩��� �᫮
	and	ax,0FFFEh		; AX - ��砩��� �⭮� �᫮
	mov	bx,ax			; BX - ���� ���� ��� ���
	xor	ax,ax
	cmp	word ptr es:[bx],ax	; �᫨ �� �⮬� ����� 
					; ��室���� ⥫� ��⮭�
	jne	make_food	; �� ࠧ ᣥ���஢��� ��砩�� ����
	cmp	word ptr es:[bx+320],ax ; �᫨ �� ��ப� ���� 
					; ��室���� ⥫� ��⮭�
	jne	make_food		; � �� ᠬ��
	mov	word ptr cs:food_at,bx	; �������� ���� ���� 
					; ��� � food_at,
	mov	ax,0D0Dh		; 梥� ��� � AX
	call	draw_food		; ���ᮢ��� ��� �� �࠭�
	pop	bx
	jmp	main_cycle


; ��楤�� draw_food
; ����ࠦ��� ���� �窨 �� �࠭� - ��� �� ����� BX � ��� �� ᫥���饩
; ��ப�. ���� ��ࢮ� �窨 �� ���� - AL, ��ன - AH


draw_food:	mov	es:[bx],ax
		mov	word ptr es:[bx+320],ax
		retn


; ������� ��砩���� �᫠
; �����頥� �᫮ � AX, ��������� DX

random:	mov	ax,word ptr cs:seed
	mov	dx,8E45h
	mul	dx
	inc	ax
	mov	cs:word ptr seed,ax
	retn

; ��६����

eaten_food		db	0
move_direction	dw	1	; ���ࠢ����� ��������: 1 - ��ࠢ�,
				; -1 - �����, 320 - ����, -320 - �����
seed:				; �� �᫮ �࠭���� �� ���殬, �ணࠬ��
food_at	equ seed+2		; � �� - �� �।��騬
	end	start
