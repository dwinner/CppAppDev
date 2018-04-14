; pm4.asm
; �ਬ�� �ணࠬ��, �믮����饩 ��४��祭�� �����.
; ����᪠�� ��� �����, ��।��騥 �ࠢ����� ��� ���� 80 ࠧ, ����� �뢮��� 
; �� �࠭ ᨬ���� ASCII � ������让 ����প��
;
; ���������:
; TASM:
;  tasm /m pm4.asm
;  tlink /x /3 pm4.obj
; WASM:
;  wasm pm4.asm
;  wlink file pm4.obj form DOS
; MASM:
;  ml /c pm4.asm
;  link pm4.obj,,NUL,,,
;


	.386p
RM_seg segment para public 'CODE' use16
	assume cs:RM_seg,ds:PM_seg,ss:stack_seg
start:
; �����⮢��� ᥣ����� ॣ�����
	push	PM_seg
	pop	ds
; �஢����, �� ��室���� �� �� 㦥 � PM
	mov	eax,cr0
	test	al,1
	jz	no_V86
; ᮮ���� � ���
	mov	dx,offset v86_msg
err_exit:
	push	cs
	pop	ds
	mov	ah,9
	int	21h
	mov	ah,4Ch
	int	21h

; 㡥������, �� �� �� ��� Windows
no_V86:
	mov	ax,1600h
	int	2Fh
	test	al,al
	jz	no_windows
; ᮮ���� � ���
	mov	dx,offset win_msg
	jmp short err_exit

; ᮮ�饭�� �� �訡��� �� ����
v86_msg	db	"Running in V86 mode. Can't switch to PM$"
win_msg db	"Runnind under Windows. Can't switch to ring 0$"

; �⠪, �� �筮 ��室���� � ॠ�쭮� ०���
no_windows:
; ������ �࠭
	mov	ax,3
	int	10h
; ���᫨�� ���� ��� ��� ���ਯ�஢ ᥣ���⮢ ������
	xor	eax,eax
	mov	ax,RM_seg
	shl	eax,4
	mov	word ptr GDT_16bitCS+2,ax
	shr	eax,16
	mov	byte ptr GDT_16bitCS+4,al
	mov	ax,PM_seg
	shl	eax,4
	mov	word ptr GDT_32bitCS+2,ax
	mov	word ptr GDT_32bitSS+2,ax
	shr	eax,16
	mov	byte ptr GDT_32bitCS+4,al
	mov	byte ptr GDT_32bitSS+4,al
; ���᫨�� ������� ���� GDT
	xor	eax,eax
	mov	ax,PM_seg
	shl	eax,4
	push	eax
	add	eax,offset GDT
	mov	dword ptr gdtr+2,eax
; ����㧨�� GDT
	lgdt	fword ptr gdtr
; ���᫨�� ������� ���� ᥣ���⮢ TSS ���� ���� �����
	pop	eax
	push	eax
	add	eax,offset TSS_0
	mov	word ptr GDT_TSS0+2,ax
	shr	eax,16
	mov	byte ptr GDT_TSS0+4,al
	pop	eax
	add	eax,offset TSS_1
	mov	word ptr GDT_TSS1+2,ax
	shr	eax,16
	mov	byte ptr GDT_TSS1+4,al
; ������ A20
	mov	al,2
	out	92h,al
; ������� ���뢠���
	cli
; ������� NMI
	in	al,70h
	or	al,80h
	out	70h,al
; ��४������� � PM
	mov	eax,cr0
	or	al,1
	mov	cr0,eax
; ����㧨�� CS
	db	66h
	db	0EAh
	dd	offset PM_entry
	dw	SEL_32bitCS

RM_return:
; ��४������� � ॠ��� ०�� RM
	mov	eax,cr0
	and	al,0FEh
	mov	cr0,eax
; ����� ��।� �।�롮ન � ����㧨�� CS
	db	0EAh
	dw	$+4
	dw	RM_seg
; ����ந�� ᥣ����� ॣ����� ��� ॠ�쭮�� ०���
	mov	ax,PM_seg
	mov	ds,ax
	mov	es,ax
	mov	ax,stack_seg
	mov	bx,stack_l
	mov	ss,ax
	mov	sp,bx
; ࠧ���� NMI
	in	al,70h
	and	al,07FH
	out	70h,al
; ࠧ���� ���뢠���
	sti
; �������� �ணࠬ��
	mov	ah,4Ch
	int	21h
RM_seg ends

PM_seg segment para public 'CODE' use32
	assume	cs:PM_seg

; ⠡��� ��������� ���ਯ�஢
GDT	label	byte
		db	8 dup(0)
GDT_flatDS	db	0FFh,0FFh,0,0,0,10010010b,11001111b,0
GDT_16bitCS	db	0FFh,0FFh,0,0,0,10011010b,0,0
GDT_32bitCS	db	0FFh,0FFh,0,0,0,10011010b,11001111b,0
GDT_32bitSS	db	0FFh,0FFh,0,0,0,10010010b,11001111b,0
; ᥣ���� TSS ����� 0 (32-���� ᢮����� TSS)
GDT_TSS0	db	067h,0,0,0,0,10001001b,01000000b,0
; ᥣ���� TSS ����� 1 (32-���� ᢮����� TSS)
GDT_TSS1	db	067h,0,0,0,0,10001001b,01000000b,0
gdt_size = $-GDT
gdtr	dw	gdt_size-1	; ࠧ��� GDT
	dd	?		; ���� GDT
; �ᯮ��㥬� ᥫ�����
SEL_flatDS equ	001000b
SEL_16bitCS equ	010000b
SEL_32bitCS equ	011000b
SEL_32bitSS equ	100000b
SEL_TSS0 equ	101000b
SEL_TSS1 equ	110000b

; ᥣ���� TSS_0 �㤥� ���樠����஢��, ��� ⮫쪮 �� �믮���� ��४��祭��
; �� ��襩 �᭮���� �����. ����筮, �᫨ �� �� ᮡ�ࠫ��� �ᯮ�짮����
; ��᪮�쪮 �஢��� �ਢ������, � �㦭� �뫮 �� ���樠����஢��� �⥪�
TSS_0	db	68h dup(0)
; ᥣ���� TSS_1. � ���� �㤥� �믮������� ��४��祭��, ⠪ �� ���� 
; ���樠����஢��� ��, �� ����� ���ॡ�������:
TSS_1	dd	0,0,0,0,0,0,0,0			; ���, �⥪�, CR3
	dd	offset task_1			; EIP
; ॣ����� ��饣� �����祭��
	dd	0,0,0,0,0,stack_l2,0,0,0B8140h	; (ESP � EDI) 
; ᥣ����� ॣ����� 
	dd	SEL_flatDS,SEL_32bitCS,SEL_32bitSS,SEL_flatDS,0,0
	dd	0		; LDTR
	dd	0		; ���� ⠡���� �����-�뢮��

; �窠 �室� � 32-���� ���饭�� ०��
PM_entry:
; �����⮢��� ॣ�����
	xor	eax,eax
	mov	ax,SEL_flatDS
	mov	ds,ax
	mov	es,ax
	mov	ax,SEL_32bitSS
	mov	ebx,stack_l
	mov	ss,ax
	mov	esp,ebx
; ����㧨�� TSS ����� 0 � ॣ���� TR
	mov	ax,SEL_TSS0
	ltr	ax
; ⮫쪮 ⥯��� ��� �ணࠬ�� �믮����� �� �ॡ������ � ���室� � 
; ���饭�� ०��

	xor	eax,eax
	mov	edi,0B8000h	; DS:EDI - ���� ��砫� �࠭�
task_0:
	mov	byte ptr ds:[edi],al	; �뢥�� ᨬ��� AL �� �࠭
; ���쭨� ���室 �� TSS ����� 1
	db	0EAh
	dd	0
	dw	SEL_TSS1
	add	edi,2		; DS:EDI - ���� ᫥���饣� ᨬ����
	inc	al		; AL - ��� ᫥���饣� ᨬ����,
	cmp	al,80		; �᫨ �� 80,
	jb	task_0	; ��� �� 横��
; ���쭨� ���室 �� ��楤��� ��室� � ॠ��� ०��
	db	0EAh
	dd	offset RM_return
	dw	SEL_16bitCS

; ����� 1
task_1:
	mov	byte ptr ds:[edi],al	; �뢥�� ᨬ��� �� �࠭
	inc	al			; 㢥����� ��� ᨬ����
	add	edi,2			; 㢥����� ���� ᨬ����
; ��४������� �� ������ 0
	db	0EAh
	dd	0
	dw	SEL_TSS0
; � �㤥� ��室��� �ࠢ�����, ����� ����� 0 ��筥� �믮����� ���室
; �� ������ 1 �� ��� �����, �஬� ��ࢮ��
	mov	ecx,02000000h	; �������� ��㧠, �������� �� ᪮���
	loop	$		; ������
	jmp task_1

PM_seg ends

stack_seg segment para stack 'STACK'
stack_start	db	100h dup(?)	; �⥪ ����� 0
stack_l = $-stack_start
stack_task2	db	100h dup(?)	; �⥪ ����� 1
stack_l2 = $-stack_start
stack_seg ends
	end start
