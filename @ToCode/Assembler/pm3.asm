; pm3.asm
; �ணࠬ��, ������������� ��࠭���� ������.
; ��७��� ���� �� ��࠭��, ��⠢����� �����������, � ��⠥��� �������
; �࠭
;
; ���������:
; TASM:
;  tasm /m pm3.asm
;  tlink /x /3 pm3.obj
; MASM:
;  ml /c pm3.asm
;  link pm3.obj,,NUL,,,
; WASM:
;  wasm pm3.asm
;  wlink file pm3.obj form DOS
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
; ������ �࠭ � ��४������� � �㦭� �����०��
	mov	ax,13h
	int	10h
; ���᫨�� ���� ��� ��� ���ਯ�஢
	xor	eax,eax
	mov	ax,RM_seg
	shl	eax,4
	mov	word ptr GDT_16bitCS+2,ax
	shr	eax,16
	mov	byte ptr GDT_16bitCS+4,al
	mov	ax,PM_seg
	shl	eax,4
	mov	word ptr GDT_32bitCS+2,ax
	shr	eax,16
	mov	byte ptr GDT_32bitCS+4,al
; ���᫨�� ������� ���� GDT
	xor	eax,eax
	mov	ax,PM_seg
	shl	eax,4
	push	eax
	add	eax,offset GDT
	mov	dword ptr gdtr+2,eax
; ����㧨�� GDT
	lgdt	fword ptr gdtr
; ������ A20 - � �⮬ �ਬ�� �� �㤥� ���짮������ ������� ��� 1 ��
	mov	al,2
	out	92h,al
; �⪫���� ���뢠���
	cli
; � NMI
	in	al,70h
	or	al,80h
	out	70h,al
; ��३� � ���饭�� ०�� (���� ��� ��࠭�筮� ����樨)
	mov	eax,cr0
	or	al,1
	mov	cr0,eax
; ����㧨�� CS
	db	66h
	db	0EAh
	dd	offset PM_entry
	dw	SEL_32bitCS


RM_return:
; ��४������� � ॠ��� ०�� � �⪫�祭��� ��࠭�筮� ����樨
	mov	eax,cr0
	and	eax,7FFFFFFEh
	mov	cr0,eax
; ����� ��।� � ����㧨�� CS
	db	0EAh
	dw	$+4
	dw	RM_seg
; ����㧨�� ��⠫�� ॣ�����
	mov	ax,PM_seg
	mov	ds,ax
	mov	es,ax
; ࠧ���� NMI
	in	al,70h
	and	al,07FH
	out	70h,al
; ࠧ���� ��㣨� ���뢠���
	sti
; ��������� ������ ������
	mov	ah,1
	int	21h
; ��४������� � ⥪�⮢� ०��
	mov	ax,3
	int	10h
; � �������� �ணࠬ��
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
gdt_size = $-GDT
gdtr	dw	gdt_size-1	; �� �����
	dd	?		; � ����
SEL_flatDS equ	001000b ; ᥫ���� 4-�������⭮�� ᥣ���� ������
SEL_16bitCS equ	010000b ; ᥫ���� ᥣ���� ���� RM_seg
SEL_32bitCS equ	011000b ; ᥫ���� ᥣ���� ���� PM_seg

; �窠 �室� � 32-���� ���饭�� ०��
PM_entry:
; ����㧨�� ᥣ����� ॣ�����, ������ �⥪
	xor	eax,eax
	mov	ax,SEL_flatDS
	mov	ds,ax
	mov	es,ax
; ᮧ���� ��⠫�� ��࠭��
	mov	edi,00100000h	; ��� 䨧��᪨� ���� - 1 ��
	mov	eax,00101007h	; ���� ⠡���� 0 = 1 �� + 4 ��
	stosd			; ������� ���� ����� ��⠫���
	mov	ecx,1023	; ��⠫�� ������ ��⠫��� -
	xor	eax,eax	;�㫨
	rep stosd
; ��������� ⠡���� ��࠭�� 0
	mov	eax,00000007h	; 0 - ���� ��࠭��� 0
	mov	ecx,1024	; �᫮ ��࠭�� � ⠡���
	page_table:
	stosd			; ������� ����� ⠡����
	add	eax,00001000h	; �������� � ����� 4096 ���⮢
	loop page_table		; � ������� ��� ��� ����⮢
; �������� ���� ��⠫��� ��࠭�� � CR3
	mov	eax,00100000h	; ������ ���� = 1 ��
	mov	cr3,eax
; ������� ��࠭���� ������,
	mov	eax,cr0
	or	eax,80000000h
	mov	cr0,eax
; � ⥯��� �������� 䨧��᪨� ���� ��࠭��� A1000h �� A2000h
	mov	eax,000A2007h
	mov	es:00101000h+0A1h*4,eax
; �᫨ ���������஢��� �।��騥 ��� �������, ᫥���騥 ���� ������� 
; ������� ���� �࠭ ᨭ�� 梥⮬, �� ��-�� ⮣�, �� �� ��६��⨫� ���� 
; ��࠭���, ��⠥��� ��� ���⮪
	mov	ecx,(320*200)/4	; ࠧ��� �࠭� � ������� ᫮���
	mov	edi,0A0000h		; ������� ���� ��砫� ����������
	mov	eax,01010101h	; ��� ᨭ��� 梥� � VGA - 1
	rep stosd
; �������� � ॠ��� ०��
	db	0EAh
	dd	offset RM_return
	dw	SEL_16bitCS
PM_seg ends

; ������� �⥪� - �ᯮ������ ��� 16-����
stack_seg segment para stack 'STACK'
stack_start	db	100h dup(?)
stack_seg ends
	end start
