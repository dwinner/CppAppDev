; picinit.asm
; �믮���� ������ ���樠������ ����� ����஫��஢ ���뢠���
; � �⮡ࠦ����� ���뢠��� IRQ0 - IRQ7 �� ������ INT 50h - 57h
; �ணࠬ�� ��⠥��� १����⭮� � ������ ���⪨� ��� ��᫥ ������� IRQ1
;
; ����⠭������� ����� ��ࠡ��稪�� ���뢠��� � ��२��樠������ 
; ����஫��� � �०��� ���ﭨ� ���饭�
;
; ���������:
; TASM:
;  tasm /m picinit.asm
;  tlink /t /x picinit.obj
; MASM:
;  ml /c picinit.asm
;  link picinit.obj,,NUL,,,
;  exe2bin picinit.exe picinit.com
; WASM:
;  wasm picinit.asm
;  wlink file picinit.obj form DOS COM
;

	.model	tiny
	.code
org	100h		; COM-�ணࠬ��

PIC1_BASE	equ	50h	; �� ��� ���� ��楤�� pic_init ��७���
				; IRQ0 - IRQ7
PIC2_BASE	equ	70h	; �� ��� ���� ��楤�� pic_init ��७���
				; IRQ8 - IRQ15

start:
	jmp end_of_resident	; ���室 �� ��砫� ���⠫��樮���� 
				; ���

irq0_handler: ; ��ࠡ��稪 IRQ0 (���뢠��� �� ��⥬���� ⠩���)
	push	ax
	in	al,61h
	and	al,11111100b	; �몫�祭�� ��������
	out	61h,al
	pop	ax
	int	08h		; ���� ��ࠡ��稪 IRQ0
	iret		; �� ��᫠� EOI, ⠪ �� �������� ����� iret
irq1_handler:		; ��ࠡ��稪 IRQ1 (���뢠��� �� ����������)
	push	ax
	in	al,61h
	or	al,00000011b	; ����祭�� ��������
	out	61h,al
	pop	ax
	int	09h			; ���� ��ࠡ��稪 IRQ1
	iret
irq2_handler:			; � ⠪ �����
	int	0Ah
	iret
irq3_handler:
	int	0Bh
	iret
irq4_handler:
	int	0Ch
	iret
irq5_handler:
	int	0Dh
	iret
irq6_handler:
	int	0Eh
	iret
irq7_handler:
	int	0Fh
	iret

end_of_resident:		; ����� १����⭮� ���
	call	hook_pic1_ints	; ��⠭���� ���� ��ࠡ��稪��
				; INT 50h - 57h
	call	init_pic	; ��२��樠������ ����஫��� ���뢠���
	mov	dx,offset end_of_resident
	int	27h		; ��⠢��� ��� ���� ��ࠡ��稪� १�����묨

; ��楤�� init_pic
; �믮���� ���樠������ ����� ����஫��஢ ���뢠���,
; �⮡ࠦ�� IRQ0 - IRQ7 �� PIC1_BASE - PIC1_BASE+7,
; � IRQ8 - IRQ15 �� PIC2_BASE - PIC2_BASE+7
; ��� ������ � �⠭���⭮� ���ﭨ� �맢��� � 
; PIC1_BASE = 08h
; PIC2_BASE = 70h
init_pic	proc	near
	cli
	mov	al,00010101b	; ICW1
	out	20h,al
	out	0A0h,al
	mov	al,PIC1_BASE	; ICW2 ��� ��ࢮ�� ����஫���
	out	21h,al
	mov	al,PIC2_BASE	; ICW2 ��� ��ண� ����஫���
	out	0A1h,al
	mov	al,04h		; ICW3 ��� ��ࢮ�� ����஫���
	out	21h,al
	mov	al,02h		; ICW3 ��� ��ண� ����஫��� 
	out	0A1h,al
	mov	al,00001101b	; ICW4 ��� ��ࢮ�� ����஫��� 
	out	21h,al
	mov	al,00001001b	; ICW4 ��� ��ண� ����஫��� 
	out	0A1h,al
	sti
	ret
init_pic	endp

; ���墠� ���뢠��� �� PIC1_BASE �� PIC1_BASE+7
hook_pic1_ints	proc near
	mov	ax,2500h+PIC1_BASE
	mov	dx,offset irq0_handler
	int	21h
	mov	ax,2501h+PIC1_BASE
	mov	dx,offset irq1_handler
	int	21h
	mov	ax,2502h+PIC1_BASE
	mov	dx,offset irq2_handler
	int	21h
	mov	ax,2503h+PIC1_BASE
	mov	dx,offset irq3_handler
	int	21h
	mov	ax,2504h+PIC1_BASE
	mov	dx,offset irq4_handler
	int	21h
	mov	ax,2505h+PIC1_BASE
	mov	dx,offset irq5_handler
	int	21h
	mov	ax,2506h+PIC1_BASE
	mov	dx,offset irq6_handler
	int	21h
	mov	ax,2507h+PIC1_BASE
	mov	dx,offset irq7_handler
	int	21h
	ret
hook_pic1_ints	endp

	end start
