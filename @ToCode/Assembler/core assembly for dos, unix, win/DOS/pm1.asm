; pm1.asm
; �ணࠬ��, ������������� ࠡ��� � ᥣ���⠬� � ���饭��� ०���,
; ��४��砥��� � ������ flat, �믮���� �뢮� �� �࠭ � �����頥��� � DOS
;
; ���������:
; TASM:
;  tasm /m pm1.asm
;  tlink /x /3 pm1.obj
; MASM:
;  ml /c pm1.asm
;  link pm1.obj,,NUL,,,
; WASM:
;  wasm pm1.asm
;  wlink file pm1.obj form DOS

	.386p		; 32-���� ���饭�� ०�� ����� � 80386

; 16-���� ᥣ����, � ���஬ ��室���� ��� ��� �室� � ��室� �� ���饭���� 
; ०���
RM_seg segment para public 'code' use16
	assume CS:RM_seg,SS:RM_stack
start:
; �����⮢��� ᥣ����� ॣ�����
	push	cs
	pop	ds
; �஢����, �� ��室���� �� �� 㦥 � PM
	mov	eax,cr0
	test	al,1
	jz	no_V86
; ᮮ���� � ���
	mov	dx,offset v86_msg
err_exit:
	mov	ah,9
	int	21h
	mov	ah,4Ch
	int	21h
v86_msg db	"Running in V86 mode. Can't switch to PM$"
win_msg db	"Runnind under Windows. Can't switch to ring 0$"

; ����� ����, �� Windows 95 ������ ���, �� PE = 0?
no_V86:
	mov	ax,1600h		; �㭪�� 1600h
	int	2Fh			; ���뢠��� ���⨯�����,
	test	al,al			; �᫨ AL = 0,
	jz	no_windows		; Windows �� ����饭�
; ᮮ���� � ���, �᫨ �� ��� Windows
	mov	dx,offset win_msg
	jmp short err_exit

; �⠪, �� �筮 ��室���� � ॠ�쭮� ०���
no_windows:
; �᫨ �� ᮡ�ࠥ��� ࠡ���� � 32-��⭮� �������, �⮨� ������ A20
	in	al,92h
	or	al,2
	out	92h,al
; ���᫨�� ������� ���� ��⪨ PM_entry
	xor	eax,eax
	mov	ax,PM_seg		; AX - ᥣ����� ���� PM_seg
	shl	eax,4			; EAX - ������� ���� PM_seg
	add	eax,offset PM_entry ; EAX - ������� ���� PM_entry
	mov	dword ptr pm_entry_off,eax ; ��࠭��� ���
; ���᫨�� ���� ��� GDT_16bitCS � GDT_16bitDS
	xor	eax,eax
	mov	ax,cs			; AX - ᥣ����� ���� RM_seg
	shl	eax,4			; EAX - ������� ���� RM_seg
	push	eax
	mov	word ptr GDT_16bitCS+2,ax	; ���� 15 - 0
	mov	word ptr GDT_16bitDS+2,ax
	shr	eax,16
	mov	byte ptr GDT_16bitCS+4,al	; � ���� 23 - 16
	mov	byte ptr GDT_16bitDS+4,al 
; ���᫨�� ��᮫��� ���� ��⪨ GDT
	pop	eax			; EAX - ������� ���� RM_seg
	add	ax,offset GDT	; EAX - ������� ���� GDT
	mov	dword ptr gdtr+2,eax	; ������� ��� ��� GDTR
; ����㧨�� ⠡���� ��������� ���ਯ�஢
	lgdt	fword ptr gdtr
; ������� ���뢠���
	cli
; ������� ����᪨�㥬�� ���뢠���
	in	al,70h
	or	al,80h
	out	70h,al
; ��४������� � ���饭�� ०��
	mov	eax,cr0
	or	al,1
	mov	cr0,eax
; ����㧨�� ���� ᥫ���� � ॣ���� CS
	db	66h		; ��䨪� ��������� ࠧ�來��� ���࠭��
	db	0EAh		; ��� ������� ���쭥�� jmp
pm_entry_off dd	?	; 32-��⭮� ᬥ饭��
	dw	SEL_flatCS	; ᥫ����


RM_return:	; � ��।����� �ࠢ����� �� ��室� �� ���饭���� ०���
; ��४������� � ॠ��� ०��
	mov	eax,cr0
	and	al,0FEh
	mov	cr0,eax
; ����� ��।� �।�롮ન � ����㧨�� CS ॠ��� ᥣ����� ���ᮬ
	db	0EAh	; ��� ���쭥�� jmp
	dw	$+4	; ���� ᫥���饩 �������
	dw	RM_seg	; ᥣ����� ���� RM_seg
; ࠧ���� NMI
	in	al,70h
	and	al,07FH
	out	70h,al
; ࠧ���� ��㣨� ���뢠���
	sti
; ��������� ������ �� ������
	mov	ah,0
	int	16h
; ��� �� �ணࠬ��
	mov	ah,4Ch
	int	21h

; ⥪�� ᮮ�饭�� � ��ਡ�⠬�, ����� �� �㤥� �뢮���� �� �࠭
message	db	'H',7,'e',7,'l',7,'l',7,'o',7,' ',7,'f',7
	db	'r',7,'o',7,'m',7,' ',7,'3',7,'2',7,'b',7
	db	'i',7,'t',7,' ',7,'P',7,'M',7
message_l = $-message			; ����� � �����
rest_scr = (80*25*2-message_l)/4	; ����� ��⠢襩�� ��� �࠭� � 
; ������� ᫮���
; ⠡��� ��������� ���ਯ�஢
GDT	label	byte
; �㫥��� ���ਯ�� (��易⥫쭮 ������ ���� �� ��ࢮ� ����)
		db	8 dup(0)
; 4 �� ���, DPL = 00:
GDT_flatCS	db	0FFh,0FFh,0,0,0,10011010b,11001111b,0
; 4 �� �����, DPL = 00:
GDT_flatDS	db	0FFh,0FFh,0,0,0,10010010b,11001111b,0
; 64-��������� ���, DPL = 00:
GDT_16bitCS	db 0FFh,0FFh,0,0,0,10011010b,0,0
; 64-��������� �����, DPL = 00:
GDT_16bitDS	db 0FFh,0FFh,0,0,0,10010010b,0,0
GDT_l = $-GDT		; ࠧ��� GDT

gdtr	dw	GDT_l-1	; 16-���� ����� GDT
	dd	?	; ����� �㤥� 32-���� ������� ���� GDT

; �������� ��� ᥫ���஢ (�� ᥫ����� ��� GDT, � RPL = 00)
SEL_flatCS equ	00001000b
SEL_flatDS equ	00010000b
SEL_16bitCS equ	00011000b
SEL_16bitDS equ	00100000b

RM_seg ends

; 32-���� ᥣ����, ᮤ�ঠ騩 ���, ����� �㤥� �ᯮ������� � ���饭��� 
; ०���
PM_seg segment para public 'CODE' use32
	assume	cs:PM_seg
PM_entry:
; ����㧨�� ᥣ����� ॣ����� (�஬� SS ��� ������)
	mov	ax,SEL_16bitDS
	mov	ds,ax
	mov	ax,SEL_flatDS
	mov	es,ax
; �뢮� �� �࠭
	mov	esi,offset message	; DS:ESI - ᮮ�饭��
	mov	edi,0B8000h			; ES:EDI - �����������
	mov	ecx,message_l		; ECX - �����
	rep movsb			; �뢮� �� �࠭
	mov	eax,07200720h	; ��� ᨬ���� 20h � ��ਡ�⠬� 07
	mov	ecx,rest_scr	; ���⮪ �࠭� / 2
	rep stosd			; ������ ���⮪ �࠭�
; ����㧨�� � CS ᥫ���� 16-��⭮�� ᥣ���� RM_seg
	db	0EAh			; ��� ���쭥�� jmp
	dd	offset RM_return	; 32-��⭮� ᬥ饭��
	dw	SEL_16bitCS		; ᥫ����
PM_seg	ends

; ᥣ���� �⥪� - �ᯮ������ ��� � 16-��⭮�, ⠪ � � 32-��⭮� ०����;
; ⠪ ��� �� �� �ண��� SS, �� �� �६� ��⠢���� 16-����
RM_stack segment para stack 'STACK' use16
	db	100h dup(?)
RM_stack ends
	end	start
