; latency.asm
; ������� �।��� �६�, ��室�饥 ����� ������� ���뢠���� � ����᪮� 
; ᮮ⢥�����饣� ��ࠡ��稪�. �뢮��� �।��� �६� � ����ᥪ㭤�� ��᫥ 
; ������ �� ������ (�� ᠬ�� ���� � 1/1 193 180)
; �ணࠬ�� �ᯮ���� 16-���� �㬬��� ��� ������, ⠪ �� ����� ������ 
; ������ १�����, �᫨ ��������� ����� ��᪮�쪨� �����
;
; ���������:
; TASM:
; tasm /m latency.asm
; tlink /t /x latency.obj
; MASM:
; ml /c latency.asm
; link latency.obj,,NUL,,,
; exe2bin latency.exe latency.com
; WASM:
; wasm latency.asm
; wlink file latency.obj form DOS COM
;

	.model tiny
	.code
	.386		; ��� ������� shld
	org	100h	; COM-�ணࠬ��
start:
	mov	ax,3508h	; AH = 35h, AL = ����� ���뢠���
	int	21h		; ������� ���� ��ࠡ��稪�
	mov	word ptr old_int08h,bx	; � ������� ��� � old_int08h
	mov	word ptr old_int08h+2,es
	mov	ax,2508h	; AH = 25h, AL = ����� ���뢠���
	mov	dx,offset int08h_handler ; DS:DX - ���� ��ࠡ��稪�
	int	21h		; ��⠭����� ��ࠡ��稪
; � �⮣� ������ � ��६����� latency ������������� �㬬�
	mov	ah,0
	int	16h		; ��㧠 �� ������ �� ������

	mov	ax,word ptr latency	; �㬬� � AX
	cmp	word ptr counter,0 ; �᫨ ������� ������ ����������,
	jz	dont_divide		; �������� ������� �� ����
	xor	dx,dx			; DX = 0
	div	word ptr counter	; ࠧ������ �㬬� �� �᫮ ����������
dont_divide:
	call	print_ax		; � �뢥�� �� �࠭

	mov	ax,2508h		; AH = 25h, AL = ����� ���뢠���
	lds	dx,dword ptr old_int08h	; DS:DX = ���� ��ࠡ��稪�
	int	21h			; ����⠭����� ���� ��ࠡ��稪
	ret				; ����� �ணࠬ��

latency	dw	0		; �㬬� ����থ�
counter	dw	0		; �᫮ �맮��� ���뢠���

; ��ࠡ��稪 ���뢠��� 08h (IRQ0)
; ��।���� �६�, ��襤襥 � ������ �ࠡ��뢠��� IRQ0
int08h_handler	proc	far
	push	ax	; ��࠭��� �ᯮ��㥬� ॣ����
	mov	al,0	; 䨪��� ���祭�� ���稪� � ������ 0
	out	43h,al	; ���� 43h: �ࠢ���騩 ॣ���� ⠩���
; ⠪ ��� ��� ����� ���樠��������� BIOS ��� 16-��⭮�� �⥭��/�����, ��㣨� 
; ������� �� �ॡ�����
	in	al,40h		; ����訩 ���� ���稪�
	mov	ah,al		; � AH
	in	al,40h		; ���訩 ���� ���稪� � AL
	xchg	ah,al		; �������� �� ���⠬�
	neg	ax		; ������ ��� ����, ⠪ ��� ���稪 㬥��蠥���,
	add	word ptr cs:latency,ax	; �������� � �㬬�
	inc	word ptr cs:counter	; 㢥����� ���稪 ����������
	pop	ax
	db	0EAh		; ������� jmp far
old_int08h	dd	0	; ���� ��ண� ��ࠡ��稪�
int08h_handler	endp

; ��楤�� print_ax
; �뢮��� AX �� �࠭ � ��⭠����筮� �ଠ�
print_ax proc near
	xchg	dx,ax		; DX = AX
	mov	cx,4		; �᫮ ��� ��� �뢮��
shift_ax:
	shld	ax,dx,4		; ������� � AL ��।��� ����
	rol	dx,4		; 㤠���� �� �� DX
	and	al,0Fh		; ��⠢��� � AL ⮫쪮 ��� ����
	cmp	al,0Ah		; �� �������, ��ॢ���騥
	sbb	al,69h		; ��⭠������� ���� � AL
	das			; � ᮮ⢥�����騩 ASCII-���
	int	29h		; �뢮� �� �࠭
	loop	shift_ax	; ������� ��� ��� ���
	ret
print_ax endp
	end start
