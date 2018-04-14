; lfbfire.asm
; �ணࠬ��, ࠡ����� � SVGA �� ����� ��������� ���஢��� ���� (LFB),
; ����������� �⠭����� ������ �����樨 �������.
; �ॡ���� �����প� LFB ��������⮩ (��� ����㦥��� ����� univbe)
; ��� �������樨 ����室�� DOS-����⥫�
;
; ���������:
; WASM:
; wasm lfbfire.asm
; DOS4G/W:
;   wlink file lfbfire.obj form os2 le op stub=wstub.exe
; PMODE/W:
;   wlink file lfbfire.obj form os2 le op stub=pmodew.exe
; ZRDX:
;   wlink file lfbfire.obj form os2 ls op stub=zrdx.exe
; WDOSX:
;   wlink file lfbfire.obj form os2 le op stub=wdosxle.exe
;
; TASM:
; tasm /m lfbfire.asm
; WDOSX:
;   tlink32 -Tpe lfbfire.obj
;   stubit lfbfire.exe
; DOS32:
;   dlink lfbfire.obj
;
; MASM:
;  ml /c lfbfire.asm
; WDOSX:
;  link ...
;  stubit lfbfire.exe
; DOS32:
;  dlink lfbfire.obj
;
; PMODE/tran, 386power, System64, Raw32 � ��㣨� �p����� ��������� ���� �
; ���⮬� �� p��ᬠ�p�������
;


	.486p			; ��� ������� xadd
	.model flat		; �᭮���� ������ ����� � ���饭��� ०���
	.code
	assume fs:nothing	; �㦭� ⮫쪮 ��� MASM
_start:
	jmp	short	_main
	db	'WATCOM'		; �㦭� ⮫쪮 ��� DOS/4GW

; ��砫� �ணࠬ��
; �� �室� ���筮 CS, DS � SS 㪠�뢠�� �� ���� � �� �� ᥣ���� � ����⮬ 4 ��
; ES 㪠�뢠�� �� ᥣ���� � PSP �� 100h ���⮢
; ��⠫�� ॣ����� �� ��।�����

_main:
	sti			; ���� 䫠� ���뢠��� �� ��।����,
	cld			; �� ������ 㦥 � 䫠�� ���ࠢ�����

	mov	ax,0100h	; �㭪�� DPMI 0100h
	mov	bx,100h	; ࠧ��� � 16-������ ��ࠣ���
	int	31h		; �뤥���� ���� ����� ���� 1 ��
	jc	DPMI_error
	mov	fs,dx		; FS - ᥫ���� ��� �뤥������� �����

; ������� ���� ��饩 ���ଠ樨 � VBE 2.0 (�. ����� Error! Reference source not found.)
	mov	dword ptr fs:[0],'2EBV'	; ᨣ����� VBE2 � ��砫� �����
	mov	word ptr v86_eax,4F00h	; �㭪�� VBE 00h
	mov	word ptr v86_es,ax	; ᥣ����, �뤥����� DPMI
	mov	ax,0300h	; �㭪�� DPMI 300h
	mov	bx,0010h	; ����� ���뢠��� 10h
	xor	ecx,ecx
	mov	edi,offset v86_regs
	push	ds
	pop	es		; ES:EDI - ������� v86_regs
	int	31h		; ������� ����� ���ଠ�� VBE2
	jc	DPMI_error
	cmp	byte ptr v86_eax,4Fh	; �஢�ઠ �����প� VBE
	jne	VBE_error

	movzx	ebp,word ptr fs:[18]	; ��ꥬ SVGA-����� � EBP
	shl	ebp,6				; � ���������

; ������� ���ଠ�� � �����०��� 101h
	mov	word ptr v86_eax,4F01h	; ����� �㭪樨 INT 10h
	mov	word ptr v86_ecx,101h	; ०�� 101h - 640x480x256
					; ES:EDI � �� ᠬ�
	mov	ax,0300h	; �㭪�� DPMI 300h - ����� ���뢠���
	mov	bx,0010h	; INT 10h
	xor	ecx,ecx
	int	31h		; ������� ����� � ०���
	jc	DPMI_error
	cmp	byte ptr v86_eax,4Fh
	jne	VBE_error
	test	byte ptr fs:[0],80h ; ��� 7 ���� ��ਡ�⮢ = 1 - LFB ����
	jz	LFB_error

; ����஥��� ���ਯ�� ᥣ����, ����뢠�饣� LFB
; �����
	mov	eax,ebp		; ����������� � ���������
	shl	eax,10		; ⥯��� � �����
	dec	eax			; ����� = ࠧ��� - 1
	shr	eax,12		; ����� � 4-���������� �������
	mov	word ptr videodsc+0,ax	; ������� ���� 15 - 0 �����
	shr	eax,8
	and	ah,0Fh
	or	byte ptr videodsc+6,ah	; � ���� 19 - 16 �����
; ����
	mov	eax,ebp		; ����������� � ���������
	shl	eax,10		; � �����
	mov	edx,dword ptr fs:[40]	; 䨧��᪨� ���� LFB
	mov	cx,dx
	shld	ebx,edx,16		; �������� ��� � CX:DX,
	mov	di,ax
	shld	esi,eax,16		; � ࠧ��� - � SI:DI
	mov	ax,800h		; � �맢��� �㭪�� DPMI 0800h
	int	31h			; �⮡ࠧ��� 䨧��᪨� ���� � �������
	jc	DPMI_error
	shrd	edx,ebx,16		; ��७��� ����祭�� ������� ����
	mov	dx,cx			; �� BS:CX � EDX
	mov	word ptr videodsc+2,dx	; � ������� ���� 15 - 0 ����
	shr	edx,16
	mov	byte ptr videodsc+4,dl	; ���� 23 - 16
	mov	byte ptr videodsc+7,dh	; � ���� 31 - 24
; �ࠢ�
	mov	bx,cs
	lar	cx,bx			; ������ �ࠢ� ��襣� ᥣ����
	and	cx,6000h		; � ��७��� ���� DPL
	or	byte ptr videodsc+5,ch	; � ����騩�� ���ਯ��

; �������� ��� ���ਯ�� � LDT � ������� ᥫ����
	mov	cx,1		; ������� ���� ���� ���ਯ��
	mov	ax,0		; � DPMI
	int	31h
	jc	DPMI_error
	mov	word ptr videosel,ax	; ������� ��� ᥫ����

	push	ds
	pop	es
	mov	edi,offset videodsc ; ES:EDI - ���� ��襣� ���ਯ��
	mov	bx,ax			; BX - �뤠��� ��� ᥫ����
	mov	ax,0Ch		; �㭪�� DPMI 0Ch
	int	31h		; ����㧨�� ���ਯ�� � LDT
	jc	DPMI_error	; ⥯��� � videosel ����� ᥫ���� �� LFB

; ��४��祭�� � ०�� 4101h (101h + LFB)
	mov word ptr v86_eax,4F02h	; 4F02h - ��⠭����� SVGA-०��
	mov word ptr v86_ebx,4101h	; ०�� 4101h = 101h + LFB
	mov	edi,offset v86_regs	; ES:EDI - ������� v86_regs
	mov	ax,0300h	; �㭪�� DPMI 300h
	mov	bx,0010h	; ����� ���뢠��� 10h
	xor	ecx,ecx
	int	31h

	mov	ax,word ptr videosel	; AX - ��� ᥫ����
enter_flame:	; � �ਤ�� �ࠢ����� � ᥫ���஬ � ax �� A000h:0000, 
		; �᫨ �ந��諠 �訡�� � �� VBE-�㭪樨
mov	es,ax	; ES - ᥫ���� ���������� ��� LFB

; ��� ��稭����� ��楤�� �����樨 �������

; ������� ������� ��� �������
	xor	edi,edi	; ����� ����� ������� � ���� ES:0000
	xor	ecx,ecx
palette_gen:
	xor	eax,eax	; 梥� ��稭����� � 0, 0, 0
	mov	cl,63		; �᫮ ���祭�� ��� ����� ����������
palette_l1:
	stosb		; ������� ����
	inc	eax	; 㢥����� ����������
	cmpsw		; �ய����� ��� ����
	loop	palette_l1 ; � ⠪ 64 ࠧ�

	push	edi
	mov	cl,192
palette_l2:
	stosw		; ������� ��� ����
	inc	di	; � �ய����� ����
	loop	palette_l2 ; � ⠪ 192 ࠧ� (�� ���� �������)
	pop	edi	; ����⠭����� EDI
	inc	di
	jns	palette_gen

; ������ ᣥ���஢���, ������� �� � ॣ����� VGA DAC (�. ����� Error! Reference source not found.)
	mov	al,0		; ����� � ॣ���� 0
	mov	dx,03C8h	; ������� ॣ���� �� ������
	out	dx,al
	push	es
	push	ds	; �������� ���⠬� ES � DS
	pop	es
	pop	ds
	xor	esi,esi
	mov	ecx,256*3	; ����� �� 256 ॣ���஢
	mov	edx,03C9h	; � ���� ������ VGA DAC
	rep outsb
	push	es
	push	ds	; �������� ���⠬� ES � DS
	pop	es
	pop	ds

; �᭮���� 横� - ������� �������, ���� �� �㤥� ����� �� ������,
	xor	edx,edx		; ������ ���� ࠢ�� ���
	mov	ebp,7777h		; �� �᫮
	mov	ecx,dword ptr scr_width	; �ਭ� �࠭�
main_loop:
	push	es		; ��࠭��� ES
	push	ds
	pop	es		; ES = DS - �� ࠡ�⠥� ⮫쪮 � ���஬
; ������� ������� (������᪨� ������)
	inc	ecx
	mov	edi,offset buffer
	mov	ebx,dword ptr scr_height
	shr	ebx,1
	dec	ebx
	mov	esi,scr_width
animate_flame:
	mov	ax,[edi+esi*2-1]	; ���᫨�� �।��� ���祭�� 梥�
	add	al,ah			; � ������ �窥 (EDI) �� ���祭�� 
	setc	ah			; 梥� � �窥 ᫥�� � �� ��� ��ப� 
	mov	dl,[edi+esi*2+1]	; ����, �ࠢ� � �� ��� ��ப� ����
	add	ax,dx
	mov	dl,[edi+esi*4]	; � �� ���� ��ப� ����,
	add	ax,dx			; ��祬 ��ࢮ� ���祭��
	shr	ax,2			; ������஢���
	jz	already_zero	; 㬥����� �મ��� 梥� 
	dec	ax
already_zero:
	stosb			; ������� ���� 梥� � ����
	add	eax,edx
	shr	eax,1
	mov	byte ptr [edi+esi-1],al
	loop	animate_flame
	mov	ecx,esi
	add	edi,ecx
	dec	ebx
	jnz	animate_flame

; �ᥢ����砩��� ����᪠ ����� �࠭�, ����� �㦨� ������஬ �������
generator_bar:
	xadd	bp,ax
	stosw
	stosw
	loop	generator_bar

	pop	es	; ����⠭����� ES ��� �뢮�� �� �࠭
; �뢮� ������� �� �࠭
	xor	edi,edi		; ES:EDI - LFB
	push	esi
	add	esi,offset buffer	; DS:ESI - ����
	mov	ecx,dword ptr scr_size ; ࠧ��� ���� � ������� ᫮���
	rep	movsd			; ᪮��஢��� ���� �� �࠭
	pop	esi

	mov	ah,1		; �᫨ �� �뫠 �����
	int	16h		; ������� ������,
	jz	main_loop	; �த������ �᭮���� 横�,
	mov	ah,0		; ���� -
	int	16h		; ����� ��� �������

exit_all:
	mov	ax,03h	; ����⠭����� ⥪�⮢� ०��
	int	10h
	mov	ax,4C00h	; AH = 4Ch
	int	21h		; ��室 �� �ணࠬ�� ��� ����⥫�� DOS

; ࠧ���� ��ࠡ��稪� �訡��
DPMI_error:	; �訡�� �� �믮������ ����� �� �㭪権 DPMI
	mov	edx,offset DPMI_error_msg
	mov	ah,9
	int	21h			; �뢥�� ᮮ�饭�� �� �訡��
	jmp short exit_all	; � ���
VBE_error:	; �� �����ন������ VBE
	mov	edx,offset VBE_error_msg
	mov	ah,9
	int	21h		; �뢥�� ᮮ�饭�� �� �訡��
	jmp short start_with_vga	; � �ᯮ�짮���� VGA
LFB_error:	; �� �����ন������ LFB
	mov	edx,offset LFB_error_msg
	mov	ah,9		; �뢥�� ᮮ�饭�� �� �訡��
	int	21h
start_with_vga:
	mov	ah,0		; ��������� ������ �� ������
	int	16h
	mov	ax,13h	; ��४������� � �����०�� 13h
	int	10h		; 320x200x256
	mov	ax,2		; �㭪�� DPMI 0002h
	mov	bx,0A000h	; ����ந�� ���ਯ�� ��� ॠ�쭮��
	int	31h		; ᥣ����
	mov	dword ptr scr_width,320	; ��⠭����� ��ࠬ����
	mov	dword ptr scr_height,200		; ०���
	mov	dword ptr scr_size,320*200/4
	jmp enter_flame		; � ��३� � �������

	.data
; ࠧ���� ᮮ�饭�� �� �訡���
VBE_error_msg	db	'VBE 2.0 error',0Dh,0Ah
		db	'Will use VGA 320x200 mode'
		db	0Dh,0Ah,'$'
DPMI_error_msg	db	'DPMI error$'
LFB_error_msg	db	'Linear Framebuffer not '
		db	'availiable',0Dh,0Ah
		db	'Will use VGA 320x200 mode'
		db	0Dh,0Ah,'$'
; ��ࠬ���� �����०���
scr_width	dd	640
scr_height	dd	480
scr_size	dd	640*480/4
; �������, �ᯮ��㥬�� �㭪樥� DPMI 0300h
v86_regs label byte
v86_edi	dd	0
v86_esi	dd	0
v86_ebp	dd	0
v86_res	dd	0
v86_ebx	dd	0
v86_edx	dd	0
v86_ecx	dd	0
v86_eax	dd	0
v86_flags	dw	0
v86_es	dw	0
v86_ds	dw	0
v86_fs	dw	0
v86_gs	dw	0
v86_ip	dw	0
v86_cs	dw	0
v86_sp	dw	0
v86_ss	dw	0
; ���ਯ�� ᥣ����, ᮮ⢥�����饣� LFB
videodsc	dw	0	; ���� 15 - 0 �����
		dw	0	; ���� 15 - 0 ����
		db	0	; ���� 16 - 23 ����
		db	10010010b	; �����
		db	10000000b	; ���� 16 - 19 ����� � ��㣨� ����
		db	0	; ���� 24 - 31 ����
; ᥫ���� ᥣ����, ����뢠�饣� LFB
videosel	dw	0
	.data?
; ���� ��� �࠭�
buffer	db	640*483 dup(?)
; �⥪
	.stack	1000h
	end	_start

