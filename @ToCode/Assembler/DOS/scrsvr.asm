; scrsvr.asm
; �ਬ�� ���⮩ �����, ॠ�����饩 ��⥢�� ���������筮��� � DOS.
; ����ࠦ��� �� �࠭� ��� ������, ������騥�� ��砩�� ��ࠧ��, ������ �� 
; ������ �ࠢ��� ᢮� ����.
;
; ��।�� �ࠢ����� ����� ���ﬨ �� ࠡ�⠥� � ���� DOS Windows 95
;
; ���������:
; TASM:
;  tasm /m scrsvr.asm
;  tlink /t /x scrsvr.obj
; MASM:
;  ml /c scrsvr.asm
;  link scrsvr.obj,,NUL,,,
;  exe2bin scrsvr.exe scrsvr.com
; WASM:
;  wasm scrsvr.asm
;  wlink file scrsvr.obj form DOS COM
;

	.model	tiny
	.code
	.386			; ��� �ᯮ���� 32-���� ॣ�����
	org	100h		; COM-�ணࠬ��
start:
	mov	ax,13h	; �����०�� 13h
	int	10h		; 320x200x256

	call	init_threads	; ���樠����஢��� ��� ��ᯥ���
; � �⮣� ���� � �� �맮�� shutdown_threads �ᯮ������� ��� ��� � ����� � ⥬ 
; �� ����� � ����묨, �� � ࠧ�묨 ॣ���ࠬ� � �⥪���
; (� ॠ�쭮� ��⥬� ����� �� �� �맮� fork ��� �������筮� �㭪樨)

	mov	bx,1		; 梥� (ᨭ��)

	push	bp
	mov	bp,sp		; �������� �� ������� ��६���� � �⥪,
				; �⮡� ���ᯥ��� ������� �室������
	push	1		; ������� � X �� ������ 蠣�
x_inc		equ word ptr [bp-2]
	push	0		; ������� � Y �� ������ 蠣�
y_inc		equ word ptr [bp-4]
	push	128-4		; �⭮�⥫�� ���� ������ ���� line_coords
coords_head	equ word ptr [bp-6]
	push	0		; �⭮�⥫�� ���� 墮�� ���� line_coords
coords_tail	equ word ptr [bp-8]
	sub	sp,64*2	; line_coords - ����楢�� ���� ���न��� �祪
	mov	di,sp
	mov	cx,64
	mov	ax,10		; ��������� ��� ���न��⠬� (10, 10)
	push	ds
	pop	es
	rep stosw
line_coords	equ word ptr [bp-(64*2)-8]

	push	0A000h
	pop	es		; ES - ���� ����������

main_loop:		; �᭮���� 横�
	call display_line	; ����ࠧ��� ⥪�饥 ���ﭨ� ������

; �������� ���ࠢ����� �������� ��砩�� ��ࠧ��
	push	bx
	mov	ebx,50	; ����⭮��� ᬥ�� ���ࠢ����� 2/50
	call	z_random	; ������� ��砩��� �᫮ �� 0 �� 49
	mov	ax,word ptr x_inc
	mov	bx,word ptr y_inc
	test	dx,dx		; �᫨ �� �᫮ - 0,
	jz	rot_right	; ����୥� ���ࠢ�,
	dec	dx		; � �᫨ 1 -
	jnz	exit_rot	; ������
; �������
	neg	ax		; ������ �� 90 �ࠤ�ᮢ
	xchg	ax,bx		; dY = -dX, dX = dY
	jmp short exit_rot
rot_right:
	neg	bx		; ���ࠢ� �� 90 �ࠤ�ᮢ
	xchg	ax,bx		; dY = dX, dX = dY
exit_rot:
	mov	word ptr x_inc,ax	; ������� ���� ���祭�� ���६��⮢
	mov	word ptr y_inc,bx
	pop	bx		; ����⠭����� 梥� � BX

; ��६�饭�� ������ �� ���� ������ ���।
	mov	di,word ptr coords_head	; DI - ���� ������
	mov	cx,word ptr line_coords[di]	; CX-��ப�
	mov	dx,word ptr line_coords[di+2]	; DX-�⮫���
	add	cx,word ptr y_inc		; �������� ���६����
	add	dx,word ptr x_inc
	add	di,4			; DI - ᫥����� �窠 � ����,
	and	di,127		; �᫨ DI > 128, DI = DI-128
	mov	word ptr coords_head,di	; ⥯��� ������ �����
	mov	word ptr line_coords[di],cx	; ������� �� ���न����
	mov	word ptr line_coords[di+2],dx
	mov	di,word ptr coords_tail	; ������ ���� 墮��
	add	di,4				; ��६����� ��� �� ����
	and	di,127			; ������ ���।
	mov	word ptr coords_tail,di		; � ������� �� ����

; ��㧠
; ��-�� �ᮡ�����⥩ ��襣� ��ᯥ��� (�. ����) �� �� ����� ���짮������ 
; ���뢠���� BIOS ��� ����, ���⮬� ᤥ���� ���� ���⮩ 横�. ����� 横�� 
; �ਤ���� �������� � ����ᨬ��� �� ᪮��� ������
	mov	cx,-1
	loop	$		; 65 535 ������ loop
	mov	cx,-1
	loop	$
	mov	cx,-1
	loop	$

	mov	ah,1
	int	16h		; �᫨ �� �뫮 ����� ������� ������, 
	jz	main_loop	; �த������ �᭮���� 横�,
	mov	ah,0		; ���� - ������ �������
	int	16h
	leave			; �᢮������ �⥪ �� �������� ��६�����
	call	shutdown_threads	; �몫���� ���������筮���
; � �⮣� ������ � ��� ᭮�� ⮫쪮 ���� �����
	mov	ax,3		; �����०�� 3
	int	10h		; 80x24
	int	20h		; ����� �ணࠬ��

; ��楤�� �뢮�� �窨 �� �࠭ � ०��� 13h
; CX = ��ப�, DX = �⮫���, BL = 梥�, ES = A000h
putpixel proc	near
	push	di
	lea	ecx,[ecx*4+ecx]	; CX = ��ப� * 5
	shl	cx,6		; CX = ��ப� * 5 * 64 = ��ப� * 320
	add	dx,cx		; DX = ��ப� * 320 + �⮫��� = ����
	mov	di,dx
	mov	al,bl
	stosb			; ������� ���� � �����������
	pop	di
	ret
putpixel endp

; ��楤�� display_line
; �뢮��� �� �࠭ ���� ������ �� ���न��⠬ �� ����楢��� ���� line_coords
display_line	proc near
	mov	di,word ptr coords_tail	; ����� �뢮� � 墮��,
continue_line_display:
	cmp	di,word ptr coords_head	; �᫨ DI ࠢ�� ����� ������,
	je	line_displayed		; �뢮� �����稫��,
	call	display_point		; ���� - �뢥�� ��� �� �࠭
	add	di,4			; ��⠭����� DI �� ᫥������ ���
	and	di,127
	jmp short continue_line_display ; � ⠪ �����
line_displayed:
	call	display_point
	mov	di,word ptr coords_tail	; �뢥�� ��� � 墮��
	push	bx
	mov	bx,0			; �㫥�� 梥⮬,
	call	display_point	; � ���� �����
	pop	bx
	ret
display_line endp

; ��楤�� display_point
; �뢮��� ��� �� ���� line_coords � �����ᮬ DI
display_point	proc	near
	mov	cx,word ptr line_coords[di]	; ��ப�
	mov	dx,word ptr line_coords[di+2]	; �⮫���
	call	putpixel			; �뢮� �窨
	ret
display_point	endp

; ��楤�� z_random
; �⠭����� ��������� ������� ��砩��� �ᥫ (����⨬���஢����)
; ����: EBX - ���ᨬ��쭮� �᫮
; �뢮�: EDX - �᫮ �� 0 �� EBX-1
z_random:
	push	ebx
	cmp	byte ptr zr_init_flag,0	; �᫨ �� �� ��뢠��,
	je	zr_init			; ���樠����஢�����,
	mov	eax,zr_prev_rand	; ���� - 㬭����� �।��饥
zr_cont:
	mul	rnd_number		; �� �����⥫�
	div	rnd_number2		; � ࠧ������ �� ����⥫�,
	mov	zr_prev_rand,edx	; ���⮪ �� ������� - ����� �᫮
	pop	ebx
	mov	eax,edx
	xor	edx,edx
	div	ebx			; ࠧ������ ��� �� ���ᨬ��쭮�
	ret				; � ������ ���⮪ � EDX
zr_init:
	push	0040h			; ���樠������ �������
	pop	fs			; 0040h:006Ch - 
	mov	eax,fs:[006Ch]	; ���稪 ���뢠��� ⠩��� BIOS,
	mov	zr_prev_rand,eax	; �� � �㤥� ���� ��砩�� �᫮�
	mov	byte ptr zr_init_flag,1
	jmp	zr_cont
rnd_number	dd	16807		; �����⥫�
rnd_number2	dd	2147483647	; ����⥫�
zr_init_flag	db	0	; 䫠� ���樠����樨 �������
zr_prev_rand	dd	0	; �।��饥 ��砩��� �᫮

; ����� ��稭����� ��� ��ᯥ���, ���ᯥ稢��饣� ���������筮���

; ������� ������, � ���ன �� �࠭�� ॣ����� ��� ������ ���
thread_struc struc
_ax	dw	?
_bx	dw	?
_cx	dw	?
_dx	dw	?
_si	dw	?
_di	dw	?
_bp	dw	?
_sp	dw	?
_ip	dw	?
_flags	dw	?
thread_struc ends	

; ��楤�� init_threads
; ���樠������� ��ࠡ��稪 ���뢠��� 08h � �������� ��������, ����뢠�騥
; ��� ���
init_threads	proc	near
	pushf
	pusha
	push	es
	mov	ax,3508h		; AH = 35h, AL = ����� ���뢠���
	int	21h			; ��।����� ���� ��ࠡ��稪�
	mov	word ptr old_int08h,bx	; ��࠭��� ���
	mov	word ptr old_int08h+2,es
	mov	ax,2508h		; AH = 25h, AL = ����� ���뢠���
	mov	dx,offset int08h_handler	; ��⠭����� ���
	int	21h
	pop	es
	popa		; ⥯��� ॣ����� � ��, �� � �� �맮�� ��楤���
	popf

	mov	thread1._ax,ax	; ��������� ��������
	mov	thread2._ax,ax	; thread1 � thread2,
	mov	thread1._bx,bx	; � ������ �࠭���� ᮤ�ন���
	mov	thread2._bx,bx	; ��� ॣ���஢ (�஬� ᥣ������ -
	mov	thread1._cx,cx	; ��� � �⮬ �ਬ�� �� ����������)
	mov	thread2._cx,cx
	mov	thread1._dx,dx
	mov	thread2._dx,dx
	mov	thread1._si,si
	mov	thread2._si,si
	mov	thread1._di,di
	mov	thread2._di,di
	mov	thread1._bp,bp
	mov	thread2._bp,bp
	mov	thread1._sp,offset thread1_stack+512
	mov	thread2._sp,offset thread2_stack+512
	pop	ax		; ���� ������ (⥯��� �⥪ ����)
	mov	thread1._ip,ax
	mov	thread2._ip,ax
	pushf
	pop	ax		; 䫠��
	mov	thread1._flags,ax
	mov	thread2._flags,ax
	mov	sp,thread1._sp	; ��⠭����� �⥪ ��� 1
	jmp	word ptr thread1._ip	; � ��।��� �� �ࠢ�����
init_threads	endp

current_thread db 1		; ����� ⥪�饩 ���

; ��ࠡ��稪 ���뢠��� INT08h (IRQ0)
; ��४��砥� ���
int08h_handler proc far
	pushf			; ᭠砫� �맢��� ���� ��ࠡ��稪
	db 9Ah		; ��� ������� call far
old_int08h dd	0	; ���� ��ண� ��ࠡ��稪�
; ��।�����, �ந��諮 �� ���뢠��� � ������ �ᯮ������ ��襩 ��� ��� 
; ������-� ��ࠡ��稪� ��㣮�� ���뢠���. �� �����, ⠪ ��� �� �� ᮡ�ࠥ��� 
; �������� �ࠢ����� ⮬�, ���� ��ࢠ� ⠩���, �� �ࠩ��� ��� ᥩ��. 
; ������ ���⮬� ����� ���짮������ ���뢠��ﬨ ��� ����থ� � ���� ����� � 
; ���⮬� �ணࠬ�� �� ࠡ�⠥� � ���� DOS (Windows 95)
	mov	save_di,bp	; ��࠭��� BP
	mov	bp,sp
	push	ax
	push	bx
	pushf
	mov	ax,word ptr [bp+2] ; ������ ᥣ������ ���� 
	mov	bx,cs			; ���⭮�� ����
	cmp	ax,bx		; �ࠢ���� �� � CS,
	jne	called_far	; �᫨ ��� �� ᮢ������ - ���,
	popf
	pop	bx		; ���� - ����⠭����� ॣ�����
	pop	ax
	mov	bp,save_di

	mov	save_di,di	; ��࠭��� DI, SI
	mov	save_si,si
	pushf			; � 䫠��
; ��।�����, � ����� ��� �� ����� ���� ��।��� �ࠢ�����,
	cmp byte ptr current_thread,1 ; �᫨ � ��ࢮ�,
	je thread1_to_thread2		; ��३� �� thread1_to_thread2,
	mov byte ptr current_thread,1	; �᫨ � 2 �� 1, ������� � ����� 1
	mov	si,offset thread1	; � ��⠭����� SI � DI
	mov	di,offset thread2	; �� ᮮ⢥�����騥 ��������,
	jmp short order_selected
thread1_to_thread2:			; �᫨ � 1 �� 2,
	mov	byte ptr current_thread,2 ; ������� � ����� ��� 2
	mov	si,offset thread2	; � ��⠭����� SI � DI
	mov	di,offset thread1
order_selected:

; ������� �� ⥪�騥 ॣ����� � �������� �� ����� [DI]
; � ����㧨�� �� ॣ����� �� �������� �� ����� [SI]
; ����� � SI � DI:
	mov	ax,[si]._si	; ��� MASM �� ��ࠦ���� [reg]._reg ����
	push	save_si	; �������� �� (thread_struc ptr [reg])._reg
	pop	[di]._si
	mov	save_si,ax
	mov	ax,[si]._di
	push	save_di
	pop	[di]._di
	mov	save_di,ax
; ⥯��� �� �᭮��� ॣ�����
	mov	[di._ax],ax
	mov	ax,[si._ax]
	mov	[di._bx],bx
	mov	bx,[si._bx]
	mov	[di._cx],cx
	mov	cx,[si._cx]
	mov	[di._dx],dx
	mov	dx,[si._dx]
	mov	[di._bp],bp
	mov	bp,[si._bp]
; 䫠��
	pop	[di._flags]
	push	[si._flags]
	popf
; ���� ������
	pop	[di._ip]	; ���� ������ �� �⥪�
	add	sp,4		; CS � 䫠�� �� �⥪� - ⥯��� �� ����
; ��४����� �⥪�
	mov	[di._sp],sp
	mov	sp,[si._sp]
	push	[si._ip]	; ���� ������ � �⥪ (㦥 ����)
	mov	di,save_di	; ����㧨�� DI � SI
	mov	si,save_si
	retn		; � ��३� �� ����� � �⥪�
; �ࠢ����� ���室�� �, �᫨ ���뢠��� �ந��諮 � �㦮� ����
called_far:
	popf		; ����⠭����� ॣ�����
	pop	bx
	pop	ax
	mov	bp,save_di
	iret		; � �������� ��ࠡ��稪
int08h_handler endp

save_di	dw	?	; ��६���� ��� �६������ �࠭����
save_si	dw	?	; ॣ���஢

; ��楤�� shutdown_threads
; �몫�砥� ��ᯥ���
shutdown_threads proc near
	mov	ax,2508h	; �����筮 ���� ����⠭����� ���뢠���
	lds	dx,dword ptr old_int08h
	int	21h
	ret
shutdown_threads endp

; �������, ����뢠��� ����� ����
thread1 thread_struc <>
; � �����,
thread2 thread_struc <>
; �⥪ ��ࢮ� ���
thread1_stack db 512 dup(?)
; � ��ன
thread2_stack db 512 dup(?)
end start
