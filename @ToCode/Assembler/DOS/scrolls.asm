; scrolls.asm
; ����ࠦ��� � ࠧ�襭�� 1024x768x64�� ���襭�� �����, ����� ����� 
; ������ ��६���� �� �࠭� ��५���� ����� � ����.
;
; ���������:
; TASM:
;  tasm /m scrolls.asm
;  tlink /t /x scrolls.obj
; MASM:
;  ml /c scrolls.asm
;  link scrolls.obj,,NUL,,,
;  exe2bin scrolls.exe scrolls.com
; WASM:
;  wasm scrolls.asm
;  wlink file scrolls.obj form DOS COM
;
 
	.model	tiny
	.code
	.386		; �ᯮ������ ������� shrd
	org	100h	; COM-䠩�
start:
	mov	ax,4F01h	; ������� ���ଠ�� � �����०���
	mov	cx,116h	; 1024x768 64��
	mov	di,offset vbe_mode_buffer
	int	10h
; ����� ��� ������ ���饭� �஢�ઠ ������ ०���
	mov	ax,4F02h	; ��⠭����� ०��
	mov	bx,116h
	int	10h
	push	word ptr [vbe_mode_buffer+8]
	pop	es		; �������� � ES ���� ��砫� ���������� 
				; (���筮 A000h)
	cld

; �뢮� ����� �� �࠭

	mov	cx,-1		; ��砫쭮� ���祭�� 梥� (����)
	mov	si,100	; ��砫�� ࠤ���
	mov	bx,300	; ����� �⮫��
	mov	ax,200	; ����� ��ப�
main_loop:
	inc	si			; 㢥����� ࠤ��� ��㣠 �� 1
	inc	ax			; 㢥����� ����� ��ப�
	inc	bx			; 㢥����� ����� �⮫��
	call	fast_circle		; ���ᮢ��� ���
	sub	cx,0000100000100001b	; �������� 梥�
	cmp	si,350		; �᫨ �� �� ���ᮢ��� 250 ��㣮�
	jb	main_loop		; �த������
	xor	cx,cx		; ����: ����� ��� 梥�
	call	fast_circle	; ���ᮢ��� ��᫥���� ���

; ������� ��६�饭�� ����ࠦ���� �� �࠭� � ������� �㭪樨 4F07

	xor	bx,bx		; BX = 0 - ��⠭����� ��砫� �࠭�
	xor	dx,dx		; ����� ��ப� = 0
				; ����� �⮫�� � CX 㦥 ����
main_loop_2:
	mov	ax,4F07h
	int	10h		; ��६����� ��砫� �࠭�
	mov	ah,7		; ����� ������� ������� � ���������, ��� �� � 
	int	21h		; ��� �஢�ન �� Ctrl-Break,
	test	al,al		; �᫨ �� ���筠� ������ -
	jnz	exit_loop_2	; �������� �ணࠬ��,
	int	21h		; ����: ������� ���७�� ASCII-���,
	cmp	al,50h	; �᫨ �� ��५�� ����
	je	key_down
	cmp	al,48h	; ��� ����� - �맢��� ��ࠡ��稪,
	je	key_up
exit_loop_2:			; ���� - �������� �ணࠬ��
	mov	ax,3		; ⥪�⮢� ०��
	int	10h
	ret			; �������� COM-�ணࠬ��

key_down:			; ��ࠡ��稪 ������ ��५�� ����
	dec	dx		; 㬥����� ����� ��ப� ��砫� �࠭�,
	jns	main_loop_2	; �᫨ ���� �� ��������� - �த������ 横�,
; ���� (�᫨ ����� �� 0, � �⠫ -1) - 㢥�����
; ����� ��ப�
key_up:		; ��ࠡ��稪 ������ ��५�� �����
	inc	dx		; 㢥����� ����� ��ப� ��砫� �࠭�
	jmp short main_loop_2

; ��楤�� �뢮�� �窨 �� �࠭ � 16-��⭮� �����०���
; ����: DX = ����� ��ப�, BX = ����� �⮫��, ES = A000, CX = 梥�
; ��������� AX
putpixel16b:
	push	dx
	push	di
	xor	di,di
	shrd	di,dx,6	; DI = ����� ��ப� * 1024 mod 65 536
	shr	dx,5		; DX = ����� ��ப� / 1024 * 2
	inc	dx
	cmp	dx,current_bank	; �᫨ ����� ����� ��� �뢮����� �窨
	jne	bank_switch	; �⫨砥��� � ⥪�饣� - ��४����� �����
switched:
	add	di,bx		; �������� � DI ����� �⮫��
	mov	ax,cx		; 梥� � AX
	shl	di,1		; DI = DI * 2, ⠪ ��� ������ ���� � ᫮���
	stosw			; �뢥�� ��� �� �࠭
	pop	di		; ����⠭����� ॣ�����
	pop	dx
	ret
bank_switch:		; ��४��祭�� �����
	push	bx
	xor	bx,bx		; BX = 0 -> ��⠭����� ��砫� �࠭�
	mov	current_bank,dx	; ��࠭��� ���� ����� ⥪�饣� �����
	call	dword ptr [vbe_mode_buffer+0Ch]	; ��४����� 
; ����
	pop	bx
	jmp	short switched

; ������ �ᮢ���� ��㣠, �ᯮ���� ⮫쪮 ᫮�����, ���⠭�� � ᤢ���.
; (��饭�� ������ �஬����筮� �窨)
; ����: SI = ࠤ���, CX = 梥�, AX = ����� �⮫�� 業�� ��㣠, BX = ����� ��ப�
; 業�� ��㣠
; ��������� DI, DX
fast_circle:
	push	si
	push	ax
	push	bx
	xor	di,di		; DI - �⭮�⥫쭠� X-���न��� ⥪�饩 �窨
	dec	di		; (SI - �⭮�⥫쭠� Y-���न���, ��砫쭮� 
	mov	ax,1		; ���祭�� - ࠤ���)
	sub	ax,si		; AX - ������ (��砫쭮� ���祭�� 1-������)
circle_loop:
	inc	di		; ᫥���騩 X (��砫쭮� ���祭�� - 0)
	cmp	di,si		; 横� �த��������, ���� X < Y
	ja	exit_main_loop

	pop	bx		; BX = ����� ��ப� 業�� ��㣠
	pop	dx		; DX = ����� �⮫�� 業�� ��㣠
	push	dx
	push	bx

	push	ax		; ��࠭��� AX (putpixel16b ��� �������)
	add	bx,di		; �뢮� ���쬨 �祪 �� ���㦭���:
	add	dx,si
	call	putpixel16b	; 業��_X + X, 業��_Y + Y
	sub	dx,si
	sub	dx,si
	call	putpixel16b	; 業��_X + X, 業��_Y - Y
	sub	bx,di
	sub	bx,di
	call	putpixel16b	; 業��_X - X, 業��_Y - Y
	add	dx,si
	add	dx,si
	call	putpixel16b	; 業��_X - X, 業��_Y + Y
	sub	dx,si
	add	dx,di
	add	bx,di
	add	bx,si
	call	putpixel16b	; 業��_X + Y, 業��_Y + X
	sub	dx,di
	sub	dx,di
	call	putpixel16b	; 業��_X + X, 業��_Y - X
	sub	bx,si
	sub	bx,si
	call	putpixel16b	; 業��_X - Y, 業��_Y - X
	add	dx,di
	add	dx,di
	call	putpixel16b	; 業��_X - Y, 業��_Y + X
	pop	ax

	test	ax,ax		; �᫨ ������ ������⥫��
	js	slop_negative
	mov	dx,di
	sub	dx,si
	shl	dx,1
	inc	dx
	add	ax,dx		; ������  = ������ + 2(X - Y) + 1
	dec	si		; Y = Y - 1
	jmp	circle_loop
slop_negative:		; �᫨ ������ ����⥫��
	mov	dx,di
	shl	dx,1
	inc	dx
	add	ax,dx		; ������ = ������ + 2X + 1
	jmp	circle_loop	; � Y �� ���������
exit_main_loop:
	pop	bx
	pop	ax
	pop	si
	ret

current_bank	dw	0	; ����� ⥪�饣� �����
vbe_mode_buffer:		; ��砫� ���� ������ � �����०���
	end	start

