; pm2.asm
; �ணࠬ��, ������������� ��ࠡ��� �������� ���뢠��� � ���饭��� 
; ०���, ��४��砥��� � 32-���� ���饭�� ०�� � �������� ������� 
; ⥪�� �� ����� ������ �� 1 �� +. ����⨥ Backspace ��ࠥ� �।��騩 
; ᨬ���, ����⨥ Esc - ��室 �� �ணࠬ��.
;
; ��������� TASM:
;	tasm /m /D_TASM_ pm2.asm
; (���, ��� ���ᨩ 3.x, �����筮 tasm /m pm2.asm)
;	tlink /x /3 pm2.obj
; ��������� WASM:
;	wasm /D pm2.asm
;	wlink file pm2.obj form DOS

; ��ਠ��� ⮣�, ��� ࠧ�� ��ᥬ����� �����뢠�� ᬥ饭�� �� 32-��⭮��
; ᥣ���� � 16-����� ��६�����
ifdef _TASM_
so	equ	small offset		; TASM 4.x
else
so	equ	offset			; WASM
endif
; ��� MASM, ��-��������, �ਤ���� ��������� ��譨� ���, ����� �८�ࠧ�� 
; ᬥ饭��, �ᯮ��㥬� � IDT

	.386p
RM_seg segment para public 'CODE' use16
	assume cs:RM_seg,ds:PM_seg,ss:stack_seg
start:
; ������ �࠭
	mov	ax,3
	int	10h
; �����⮢��� ᥣ����� ॣ�����
	push	PM_seg
	pop	ds
; �஢����, �� ��室���� �� �� 㦥 � PM
	mov	eax,cr0
	test	al,1
	jz	no_V86
; ᮮ���� � ���
	mov	dx,so v86_msg
err_exit:
	mov	ah,9
	int	21h
	mov	ah,4Ch
	int	21h
; ����� ����, �� Windows 95 ������ ���, �� PE = 0?
no_V86:
	mov	ax,1600h
	int	2Fh
	test	al,al
	jz	no_windows
; ᮮ���� � ���
	mov	dx,so win_msg
	jmp short err_exit

; �⠪, �� �筮 ��室���� � ॠ�쭮� ०���
no_windows:
; ���᫨�� ���� ��� ��� �ᯮ��㥬�� ���ਯ�஢ ᥣ���⮢
	xor	eax,eax
	mov	ax,RM_seg
	shl	eax,4
	mov	word ptr GDT_16bitCS+2,ax ; ����� 16bitCS �㤥� RM_seg
	shr	eax,16
	mov	byte ptr GDT_16bitCS+4,al
	mov	ax,PM_seg
	shl	eax,4
	mov	word ptr GDT_32bitCS+2,ax ; ����� ��� 32bit* �㤥�
	mov	word ptr GDT_32bitSS+2,ax	; PM_seg
	mov	word ptr GDT_32bitDS+2,ax
	shr	eax,16
	mov	byte ptr GDT_32bitCS+4,al
	mov	byte ptr GDT_32bitSS+4,al
	mov	byte ptr GDT_32bitDS+4,al
; ���᫨�� ������� ���� GDT
	xor	eax,eax
	mov	ax,PM_seg
	shl	eax,4
	push	eax
	add	eax,offset GDT
	mov	dword ptr gdtr+2,eax
; ����㧨�� GDT
	lgdt	fword ptr gdtr
; ���᫨�� ������� ���� IDT
	pop	eax
	add	eax,offset IDT
	mov	dword ptr idtr+2,eax
; ����㧨�� IDT
	lidt	fword ptr idtr
; �᫨ �� ᮡ�ࠥ��� ࠡ���� � 32-��⭮� �������, �⮨� ������ A20
	in	al,92h
	or	al,2
	out	92h,al
; �⪫���� ���뢠���
	cli
; ������ NMI,
	in	al,70h
	or	al,80h
	out	70h,al
; ��३� � PM
	mov	eax,cr0
	or	al,1
	mov	cr0,eax
; ����㧨�� SEL_32bitCS � CS
	db	66h
	db	0EAh
	dd	offset PM_entry
	dw	SEL_32bitCS


RM_return:
; ��३� � RM
	mov	eax,cr0
	and	al,0FEh
	mov	cr0,eax
; ����� ��।� � ����㧨�� CS ॠ��� �᫮�
	db	0EAh
	dw	$+4
	dw	RM_seg
; ��⠭����� ॣ����� ��� ࠡ��� � ॠ�쭮� ०���
	mov	ax,PM_seg
	mov	ds,ax
	mov	es,ax
	mov	ax,stack_seg
	mov	bx,stack_l
	mov	ss,ax
	mov	sp,bx
; ����㧨�� IDTR ��� ॠ�쭮�� ०���
	mov	ax,PM_seg
	mov	ds,ax
	lidt	fword ptr idtr_real
; ࠧ���� NMI
	in	al,70h
	and	al,07FH
	out	70h,al
; ࠧ���� ���뢠���
	sti
; � ���
	mov	ah,4Ch
	int	21h
RM_seg ends

; 32-���� ᥣ����
PM_seg segment para public 'CODE' use32
	assume	cs:PM_seg

; ⠡���� GDT � IDT ������ ���� ��஢����, ⠪ �� �㤥� �� ࠧ����� � 
; ��砫� ᥣ����
GDT	label	byte
		db	8 dup(0)
; 32-���� 4-��������� ᥣ���� � ����� = 0
GDT_flatDS	db	0FFh,0FFh,0,0,0,10010010b,11001111b,0
; 16-���� 64-��������� ᥣ���� ���� � ����� RM_seg
GDT_16bitCS	db	0FFh,0FFh,0,0,0,10011010b,0,0
; 32-���� 4-��������� ᥣ���� ᮤ� � ����� PM_seg
GDT_32bitCS	db	0FFh,0FFh,0,0,0,10011010b,11001111b,0
; 32-���� 4-��������� ᥣ���� ������ � ����� PM_seg
GDT_32bitDS	db	0FFh,0FFh,0,0,0,10010010b,11001111b,0
; 32-���� 4-��������� ᥣ���� ������ � ����� stack_seg
GDT_32bitSS	db	0FFh,0FFh,0,0,0,10010010b,11001111b,0
gdt_size = $-GDT
gdtr	dw	gdt_size-1	; ����� GDT
	dd	?		; ������� ���� GDT
; ����� ��� ᥫ���஢
SEL_flatDS equ	001000b
SEL_16bitCS equ	010000b
SEL_32bitCS equ	011000b
SEL_32bitDS equ 100000b
SEL_32bitSS equ 101000b

; ⠡��� ���ਯ�஢ ���뢠��� IDT
IDT	label	byte
; �� �� ���ਯ��� ����� ⨯ 0Eh - 32-���� �� ���뢠���
; INT 00 - 07
	dw	8 dup(so int_handler,SEL_32bitCS,8E00h,0)
; INT 08 (irq0)
	dw	so irq0_7_handler,SEL_32bitCS,8E00h,0
; INT 09 (irq1)
	dw	so irq1_handler,SEL_32bitCS,8E00h,0
; INT 0Ah - 0Fh (IRQ2 - IRQ8)
	dw	6 dup(so irq0_7_handler,SEL_32bitCS,8E00h,0)
; INT 10h - 6Fh
	dw	97 dup(so int_handler,SEL_32bitCS,8E00h,0)
; INT 70h - 78h (IRQ8 - IRQ15)
	dw	8 dup(so irq8_15_handler,SEL_32bitCS,8E00h,0)
; INT 79h - FFh
	dw	135 dup(so int_handler,SEL_32bitCS,8E00h,0)
idt_size = $-IDT			; ࠧ��� IDT
idtr	dw	idt_size-1		; ����� IDT
	dd	?			; ������� ���� ��砫� IDT
; ᮤ�ন��� ॣ���� IDTR � ॠ�쭮� ०���
idtr_real dw	3FFh,0,0

; ᮮ�饭�� �� �訡��� �� ����
v86_msg	db	"Running in V86 mode. Can't switch to PM$"
win_msg db	"Runnind under Windows. Can't switch to ring 0$"

; ⠡��� ��� ��ॢ��� 0E ᪠�-����� � ASCII
scan2ascii	db	0,1Bh,'1','2','3','4','5','6','7','8','9','0','-','=',8
screen_addr	dd	0	; ⥪��� ������ �� �࠭�

; �窠 �室� � 32-���� ���饭�� ०��
PM_entry:
; ��⠭����� 32-���� �⥪ � ��㣨� ॣ�����
	mov	ax,SEL_flatDS
	mov	ds,ax
	mov	es,ax
	mov	ax,SEL_32bitSS
	mov	ebx,stack_l
	mov	ss,ax
	mov	esp,ebx
; ࠧ���� ���뢠���
	sti
; � ���� � ���� 横�
	jmp short $

; ��ࠡ��稪 ���筮�� ���뢠���
int_handler:
	iretd
; ��ࠡ��稪 �����⭮�� ���뢠��� IRQ0 - IRQ7
irq0_7_handler:
	push	eax
	mov	al,20h
	out	20h,al
	pop	eax
	iretd
; ��ࠡ��稪 �����⭮�� ���뢠��� IRQ8 - IRQ15
irq8_15_handler:
	push	eax
	mov	al,20h
	out	0A1h,al
	pop	eax
	iretd
; ��ࠡ��稪 IRQ1 - ���뢠��� �� ����������
irq1_handler:
	push	eax	; �� �����⭮� ���뢠��� - ��࠭��� ॣ�����
	push	ebx
	push	es
	push	ds
	in	al,60h		; ������ ᪠�-��� ����⮩ ������,
	cmp	al,0Eh		; �᫨ �� �����, 祬 ���ᨬ���� 
	ja	skip_translate	; ���㦨����� ����, - �� ��ࠡ��뢠��,
	cmp	al,1			; �᫨ �� Esc,
	je	esc_pressed		; ��� � ॠ��� ०��,
	mov	bx,SEL_32bitDS	; ����:
	mov	ds,bx		; DS:EBX - ⠡��� ��� ��ॢ��� ᪠�-����
	mov	ebx,offset scan2ascii	; � ASCII
	xlatb			; �८�ࠧ�����
	mov	bx,SEL_flatDS
	mov	es,bx				; ES:EBX - ���� ⥪�饩 
	mov	ebx,screen_addr		; ����樨 �� �࠭�, 
	cmp	al,8		; �᫨ �� �뫠 ����� Backspace,
	je	bs_pressed
	mov	es:[ebx+0B8000h],al	; ��᫠�� ᨬ��� �� �࠭,
	add	dword ptr screen_addr,2	; 㢥����� ���� ����樨 �� 2,
	jmp short skip_translate
bs_pressed:			; ����:
	mov	al,' '	; ���ᮢ��� �஡��
	sub	ebx,2		; � ����樨 �।��饣� ᨬ����
	mov	es:[ebx+0B8000h],al
	mov	screen_addr,ebx	; � ��࠭��� ���� �।��饣� ᨬ���� 
skip_translate:			; ��� ⥪�騩 
; ࠧ���� ࠡ��� ����������
	in	al,61h
	or	al,80h
	out	61h,al
; ��᫠�� EOI ����஫���� ���뢠���
	mov	al,20h
	out	20h,al
; ����⠭����� ॣ����� � ���
	pop	ds
	pop	es
	pop	ebx
	pop	eax
	iretd

; � ��।����� �ࠢ����� �� ��ࠡ��稪� IRQ1, �᫨ ����� Esc
esc_pressed:
; ࠧ���� ࠡ��� ����������, ��᫠�� EOI � ����⠭����� ॣ�����
	in	al,61h
	or	al,80h
	out	61h,al
	mov	al,20h
	out	20h,al
	pop	ds
	pop	es
	pop	ebx
	pop	eax
; �������� � ॠ��� ०��
	cli
	db	0EAh
	dd	offset RM_return
	dw	SEL_16bitCS
PM_seg ends

; ������� �⥪�. �ᯮ������ ��� 16-���� � 16-��⭮� ��� �ணࠬ�� � ��� 
; 32-���� (�१ ᥫ���� SEL_32bitSS) � 32-��⭮� ���.
stack_seg segment para stack 'STACK'
stack_start	db	100h dup(?)
stack_l = $-stack_start	; ����� �⥪� ��� ���樠����樨 ESP
stack_seg ends
	end start
