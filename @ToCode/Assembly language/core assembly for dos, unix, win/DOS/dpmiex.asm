; dpmiex.asm
; �믮���� ��४��祭�� � ���饭�� ०�� �।�⢠�� DPMI
;
; ���������:
; TASM:
; tasm /m dpmiex.asm
; tlink /x /3 dpmiex.obj
; MASM:
; ml /c dpmiex.asm
; link dpmiex.obj,,NUL,,,
; WASM:
; wasm /D_WASM_ dpmiex.asm
; wlink file dpmiex.obj form DOS


	.386		; 32-���� ���饭�� ०�� ����� � 80386

; 16-���� ᥣ���� - � ��� �믮������ �����⮢�� � ���室 � ���饭�� 
; ०��
RM_seg	segment	byte	public	use16
	assume	cs:RM_seg, ds:PM_seg, ss:RM_stack

; �窠 �室� �ணࠬ��
RM_entry:
; �஢���� ����稥 DPMI
	mov	ax,1687h	; ����� 1678h
	int	2Fh		; ���뢠��� ���⨯�����,
	test	ax,ax		; �᫨ AX �� ����,
	jnz	DPMI_error	; �ந��諠 �訡�� (DPMI ���������),
	test	bl,1		; �᫨ �� �����ন������ 32-���� ०�� 
	jz	DPMI_error	; ��� ⮦� ��祣� ������

; �����⮢��� ������ ���� ��� ����� ���ਯ�஢
	mov	eax,PM_seg
	mov	ds,ax		; DS - ᥣ����� ���� PM_seg
	shl	eax,4		; EAX - ������� ���� ��砫� ᥣ���� PM_seg
	mov	dword ptr PM_seg_addr,eax
	or	dword ptr GDT_flatCS+2,eax ; ���ਯ�� ��� CS
	or	dword ptr GDT_flatDS+2,eax ; ���ਯ�� ��� DS

; ��࠭��� ���� ��楤��� ��४��祭�� DPMI
	mov	word ptr DPMI_ModeSwitch,di
	mov	word ptr DPMI_ModeSwitch+2,es

; ES ������ 㪠�뢠�� �� ������� ������ ��� ��४��祭�� ०����
; � ��� ��� �㤥� ᮢ������ � ��砫�� ���饣� 32-��⭮�� �⥪�
	add	eax,offset DPMI_data	; �������� � EAX ᬥ饭��
	shr	eax,4			; � �ॢ���� � ᥣ����� ����
	inc	ax
	mov	es,ax

; ��३� � ���饭�� ०��
	mov	ax,1	; AX = 1 - �� �㤥� 32-�ਫ�������
ifdef _WASM_
	db	67h	; ���ࠢ�� ��� wasm
endif
	call	dword ptr DPMI_ModeSwitch
	jc	DPMI_error	; �᫨ ��४��祭�� �� �ந��諮 - ���

; ⥯��� �� ��室���� � ���饭��� ०���, �� ������ ��� ᥣ���⮢ 
; ��⠭������ �� 64 ��, � ࠧ�來��� ᥣ���⮢ �� 16 ��⮢. ��� ���� �����⮢��� ��� 
; 32-����� ᥫ���� � ����⮬ 4 �� - ���� ��� ���� � ���� ��� ������

	push	ds
	pop	es	; ES ����� �� ᥣ���⮬ PSP � ����⮬ 100h ���⮢
	mov	edi,offset GDT		; EDI - ���� ⠡���� GDT
; 横� �� �ᥬ ���ਯ�ࠬ � ��襩 GDT,
	mov	edx,1	; ������ �ᥣ� ��� (0, 1)
sel_loop:
	xor	ax,ax	; �㭪�� DPMI 00
	mov	cx,1
	int	31h	; ᮧ���� ������� ���ਯ��
	mov	word ptr selectors[edx*2],ax	; ��࠭��� ᥫ���� � 
	mov	bx,ax					; ⠡���� selectors 
	mov	ax,000Ch	; �㭪�� DPMI 0Ch
	int	31h		; ��⠭����� ᥫ����
	add	di,8		; EDI - ᫥���騩 ���ਯ��
	dec	dx
	jns	sel_loop

; ����㧨�� ᥫ���� ᥣ���� ���� � CS �� ����� ������� RETF
	push	dword ptr Sel_flatCS	; ᥫ���� ��� CS
ifdef _WASM_
	db	066h
endif
	push	offset PM_entry	; EIP
	db	066h		; ��䨪� ࠧ��� ���࠭��
	retf			; �믮����� ���室 � 32-���� ᥣ����

; � ��।����� �ࠢ�����, �᫨ �ந��諠 �訡�� �� ���樠����樨 DPMI
; (���筮, �᫨ DPMI ���� ���)
DPMI_error:
	push	cs
	pop	ds
	mov	dx,offset nodpmi_msg
	mov	ah,9h			; �뢮� ��ப� �� �࠭
	int	21h
	mov	ah,4Ch		; ����� EXE-�ணࠬ��
	int	21h
nodpmi_msg	db	'DPMI Error$'
RM_seg	ends

; ᥣ���� PM_seg ᮤ�ন� ���, ����� � �⥪ ��� ���饭���� ०���
PM_seg	segment	byte	public	use32
	assume	cs:PM_seg,ds:PM_seg,ss:PM_seg

; ⠡��� ���ਯ�஢
GDT	label	byte
; ���ਯ�� ��� CS
GDT_flatCS	db	0FFh,0FFh,0h,0h,0h,0FAh,0CFh,0h
; ���ਯ�� ��� DS
GDT_flatDS	db	0FFh,0FFh,0h,0h,0h,0F2h,0CFh,0h

; �窠 �室� � 32-���� ०�� - ����㦥� ⮫쪮 CS
PM_entry:
	mov	ax,word ptr Sel_flatDS	; ᥫ���� ��� ������
	mov	ds,ax	; � DS
	mov	es,ax	; � ES
	mov	ss,ax	; � � SS
	mov	esp,offset PM_stack_bottom ; � ��⠭���� �⥪

;============================================================
; ��� ��稭����� ⥪�� ᮡ�⢥��� �ணࠬ��
; �ணࠬ�� ࠡ�⠥� � ������ ����� flat � ���㫥��� �����
; ���� CS, DS, ES � SS ᮢ������ � ࠢ�� ��������� ����� ��砫� PM_seg 
; �� ������ - 4 ��

	mov	ax,0300h			; �㭪�� DPMI 0300h
	mov	bx,0021h			; ���뢠��� DOS 21h
	xor	ecx,ecx			; �⥪ �� ����஢���
	mov	edi,offset v86_regs	; ES:EDI - ���� v86_regs
	int	31h				; �맢��� ���뢠���

	mov	ah,4Ch	; �� �����⢥��� ᯮᮡ
	int	21h		; �ࠢ��쭮 �������� DPMI-�ணࠬ��

hello_msg	db	"Hello from 32-bit protected mode!$"

v86_regs:	; ���祭�� ॣ���஢ ��� �㭪樨 DPMI 0300h
		dd	0,0,0,0,0	; EDI, ESI, EBP, 0, EBX
v_86_edx	dd	offset hello_msg	; EDX
		dd	0		; ECX
v86_eax		dd	0900h		; EAX (AH = 09h, �뢮� ��ப� �� �࠭)
		dw	0,0		; FLAGS, ES
v86_ds		dw	PM_seg	; DS
		dw	0,0,0,0,0,0	; FS, GS, 0, 0, SP, SS

; ࠧ���� �६���� ��६����, �㦭� ��� ��४��祭�� ०����
DPMI_ModeSwitch	dd	?	; �窠 �室� DPMI
PM_seg_addr		dd	?	; ������� ���� ᥣ���� PM_seg 

; ���祭�� ᥫ���஢
selectors:
Sel_flatDS	dw	?
Sel_flatCS	dw	?

; �⥪ ��� ��襩 32-��⭮� �ணࠬ��
DPMI_data:	; � �६����� ������� ������ DPMI �����६����
	db 16384 dup (?)
PM_stack_bottom:
PM_seg	ends

; �⥪ 16-��⭮� �ணࠬ��, ����� �ᯮ���� DPMI-�ࢥ� �� ��४��祭�� 
; ०����
; Windows 95 �ॡ�� 16 ���⮢
; CWSDPMI �ॡ�� 32 ����
; QDPMI �ॡ�� 96 ���⮢
; �� �롥६ �� ���ᨬ��
RM_stack	segment byte stack 'stack' use16
	db	96 dup (?)
RM_stack	ends
	end	RM_entry	; �窠 �室� ��� DOS - RM_entry
