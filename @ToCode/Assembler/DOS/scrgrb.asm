; scrgrb.asm
; �������⭠� �ணࠬ��, ��࠭���� ����ࠦ���� � �࠭� � 䠩�.
; �����ন������ ⮫쪮 �����०�� 13h (320x200x256) � ⮫쪮 ���� 䠩�.
;
; HCI:
; ����⨥ Alt-G ᮧ���� 䠩� scrgrb.bmp � ⥪�饩 ��४�ਨ � ����ࠦ�����, 
; ��室��訬�� �� �࠭� � ������ ������ ������.
; ����� � ��������� ��ப�� /u ���㦠�� �ணࠬ�� �� �����
; 
; API:
; �ணࠬ�� �������� ����� ᢮������ �㭪�� ���뢠��� 2Dh (�஬� ���)
; � ᮮ⢥��⢨� � ᯥ�䨪�樥� AMIS 3.6
; �����ন����� ����㭪樨 AMIS: 00h, 02h, 03h, 04h, 05h
; �� ��ࠡ��稪� ���뢠��� ����஥�� � ᮮ⢥��⢨� � IMB ISP
;
; �������⭠� ���� �������� � ����� 1056 ���⮢, �᫨ ��������� EMS,
; � 66 160 ���⮢, �᫨ EMS �� �����㦥�
;
; ���������:
; TASM:
;  tasm /m scrgrb.asm
;  tlink /t /x scrgrb.obj
; MASM:
;  ml /c scrgrb.asm
;  link scrgrb.obj,,NUL,,,
;  exe2bin scrgrb.exe scrgrb.com
; WASM:
;  wasm scrgrb.asm
;  wlink file scrgrb.obj form DOS COM
;

	.model	tiny
	.code
	.186			; ��� ᤢ���� � ������ pusha/popa
	org	2Ch
envseg	dw	?	; ᥣ����� ���� ���㦥���
	org	80h
cmd_len	db	?	; ����� ��������� ��ப�
cmd_line	db	?	; ��������� ��ப�
	org	100h		; COM-�ணࠬ��
start:
	jmp	initialize	; ���室 �� ���樠���������� ����

; ��ࠡ��稪 ���뢠��� 09h (IRQ1)

int09h_handler	proc	far
		jmp short actual_int09h_handler	; �ய����� ISP
old_int09h	dd	?
		dw	424Bh
		db	00h
		jmp short hw_reset
		db	7 dup (0)
actual_int09h_handler:		; ��砫� ᮡ�⢥��� ��ࠡ��稪� INT 09h
		pushf
		call	dword ptr cs:old_int09h ; ᭠砫� �맢��� ���� 
; ��ࠡ��稪, �⮡� �� �����訫 �����⭮� 
; ���뢠��� � ��।�� ��� � ����

	pusha		; �� �����⭮� ���뢠��� - ����
	push	ds	; ��࠭��� �� ॣ�����
	push	es
	
	push	0040h
	pop	ds	; DS = ᥣ����� ���� ������ ������ BIOS
	mov	di,word ptr ds:001Ah	; ���� ������ ���� 
					; ����������,
	cmp	di,word ptr ds:001Ch	; �᫨ �� ࠢ�� ����� 
					; 墮��,
	je	exit_09h_handler	; ���� ����, � ��� ������ ��祣�,

	mov	ax,word ptr [di]	; ����: ����� ᨬ���,
	cmp	ah,22h		; �᫨ �� �� G (᪠�-��� 22h),
	jne	exit_09h_handler	; ���

	mov	al,byte ptr ds:0017h ; ���� ���ﭨ� ����������,
	test	al,08h		; �᫨ Alt �� �����,
	jz	exit_09h_handler	; ���,

	mov	word ptr ds:001Ch,di ; ����: ��⠭����� ���� 
	; ������ � 墮�� ���� ࠢ�묨, � ���� �������� ���

	call	do_grab	; �����⮢��� BMP-䠩� � ����ࠦ�����
	mov	byte ptr cs:io_needed,1	; ��⠭����� 䫠� 
					; �ॡ��饩�� ����� �� ���
	cli
	call	safe_check	; �஢����, ����� �� �맢��� DOS,
	jc	exit_09h_handler
	sti
	call	do_io		; �᫨ �� - ������� 䠩� �� ���

exit_09h_handler: 
	pop	es
	pop	ds	; ����⠭����� ॣ����� 
	popa
	iret		; � �������� � ��ࢠ���� �ணࠬ��
int09h_handler	endp

hw_reset:	retf 


; ��ࠡ��稪 INT 08h (IRQ0)

int08h_handler	proc	far
		jmp short actual_int08h_handler ; �ய����� ISP
old_int08h	dd	?
		dw	424Bh
		db	00h
		jmp short hw_reset 
		db	7 dup (0)
actual_int08h_handler:		; ᮡ�⢥��� ��ࠡ��稪
		pushf
		call	dword ptr cs:old_int08h	; ᭠砫� �맢��� �⠭����� 
	; ��ࠡ��稪, �⮡� �� �����訫 �����⭮� ���뢠��� 
	; (���� ��� �� �����襭�, ������ �� ��᪥ ����������)
	pusha
	push	ds
	cli		; ����� �� �஢�મ� ������쭮� ��६����� 
			; � �ਭ�⨥� �襭�� �� �� ���祭�� - 
			; �� ����୮ �室���� �������, ���뢠��� 
			; ������ ���� ����饭�
	cmp	byte ptr cs:io_needed,0	; �஢����,
	je	no_io_needed	; �㦭� �� ����� �� ���

	call	safe_check		; �஢����,
	jc	no_io_needed	; ����� �� ����� �� ���
	sti			; ࠧ���� ���뢠��� �� �६� �����

	call	do_io		; ������ �� ���
no_io_needed:
	pop	ds
	popa
	iret
int08h_handler	endp


; ��ࠡ��稪 INT 13h
; �����ন���� 䫠� ������� INT 13h, ����� ⮦� ���� �஢����� ��। 
; ������� �� ���

int13h_handler	proc	far
	jmp short actual_int13h_handler	; �ய����� ISP
old_int13h	dd	?
		dw	424Bh
		db	00h
		jmp short hw_reset
		db	7 dup (0)
actual_int13h_handler:		; ᮡ�⢥��� ��ࠡ��稪
		pushf
		inc	byte ptr cs:bios_busy	; 㢥����� ���稪 
						; ������� INT 13h
		cli
		call	dword ptr cs:old_int13h
		pushf
		dec	byte ptr cs:bios_busy	; 㬥����� ���稪
		popf
		ret	2	; ������ ������� IRET, �� ����⠭��������� 
		; 䫠�� �� �⥪�, ⠪ ��� ��ࠡ��稪 INT 13h �����頥� ������� 
		; १����� � ॣ���� 䫠���, � �� � ��� �����, �࠭�饩�� � 
		; �⥪�. �� ⮦� �����蠥��� �������� ret 2
int13h_handler	endp


; ��ࠡ��稪 INT 28h
; ��뢠���� DOS, ����� ��� ������� ����� � ���������� � �㭪�ﬨ DOS ����� 
; ���짮������

int28h_handler	proc	far
		jmp short actual_int28h_handler	; �ய����� ISP
old_int28h	dd	?
		dw	424Bh
		db	00h
		jmp short hw_reset
		db	7 dup (0)
actual_int28h_handler:
		pushf
	push	di
	push	ds
	push	cs
	pop	ds
	cli
	cmp	byte ptr io_needed,0	; �஢����,
	je	no_io_needed2	; �㦭� �� ����� �� ���
	lds	di,dword ptr in_dos_addr
	cmp	byte ptr [di+1],1	; �஢����,
	ja	no_io_needed2 ; ����� �� ����� �� ��� (䫠� 
			; ������� DOS �� ������ ���� ����� 1)
	sti
	call	do_io		; ������ �� ���
no_io_needed2:
	pop	ds
	pop	di
	popf
	jmp	dword ptr cs:old_int28h	; ���室 �� ���� 
				; ��ࠡ��稪 INT 28h
int28h_handler	endp

; ��楤�� do_grab
; ����頥� � ���� ������� � ᮤ�ন��� ����������, �ନ��� BMP-䠩�.
; ��⠥�, �� ⥪�騩 �����०�� - 13h
do_grab	proc	near
	push	cs
	pop	ds

	call	ems_init	; �⮡ࠧ��� ��� ���� � ���� EMS

	mov	dx,word ptr cs:buffer_seg
	mov	es,dx		; �������� ᥣ���� � ���஬ � ES � DS
	mov	ds,dx		; ��� ᫥����� 蠣�� ��楤���

	mov	ax,1017h	; �㭪�� 1017h - �⥭�� ������� VGA
	mov	bx,0		; ��稭�� � ॣ���� ������� 0,
	mov	cx,256	; �� 256 ॣ���஢
	mov	dx,BMP_header_length ; ��砫� ������� � BMP
	int	10h		; ������ࢨ� BIOS

; ��ॢ��� ������� �� �ଠ�, � ���஬ �� �����뢠�� �㭪�� 1017h
; (�� ���� �� 梥�, � ������ ���� 6 ���稬�� ��⮢)
; � �ଠ�, �ᯮ��㥬� � BMP-䠩���
; (4 ���� �� 梥�, � ������ ���� 8 ���稬�� ��⮢)
	std		; �������� �� ���� � ��砫�
	mov	si,BMP_header_length+256*3-1	; SI - ����� 3-���⭮� 
						; �������
	mov	di,BMP_header_length+256*4-1	; DI - ����� 4-���⭮� 
						; �������
	mov	cx,256		; CX - �᫮ 梥⮢
adj_pal: mov	al,0
	stosb			; ������� �⢥��� ���� (0)
	lodsb			; ������ ��⨩ ����
	shl	al,2		; ����⠡�஢��� �� 8 ��⮢
	push	ax
	lodsb			; ������ ��ன ����
	shl	al,2		; ����⠡�஢��� �� 8 ��⮢
	push	ax
	lodsb			; ������ ��⨩ ����
	shl	al,2		; ����⠡�஢��� �� 8 ��⮢
	stosb			; � ������� �� �� ����
	pop	ax		; � ���⭮� ���浪�
	stosb
	pop	ax
	stosb
	loop	adj_pal

; ����஢���� ���������� � BMP.
; � �ଠ� BMP ��ப� ����ࠦ���� �����뢠���� �� ��᫥���� � ��ࢮ�, ⠪ �� 
; ���� ���� ᮮ⢥����� ������� ������ ���ᥫ�
	cld			; �������� �� ��砫� � ����� (�� ��ப�)
	push	0A000h
	pop	ds
	mov	si,320*200	; DS:SI - ��砫� ��᫥���� ��ப� �� �࠭�
	mov	di,bfoffbits	; ES:DI - ��砫� ������ � BMP
	mov	dx,200		; ���稪 ��ப
bmp_write_loop:
	mov	cx,320/2 	; ���稪 ᨬ����� � ��ப�
	rep movsw		; ����஢��� 楫묨 ᫮����, ⠪ ����॥
	sub	si,320*2 	; ��ॢ��� SI �� ��砫� �।��饩 ��ப�
	dec	dx		; 㬥����� ���稪 ��ப,
	jnz	bmp_write_loop	; �᫨ 0 - ��� �� 横��

	call	ems_reset	; ����⠭����� ���ﭨ� EMS �� �맮�� do_grab
	ret
do_grab	endp


; ��楤�� do_io
; ᮧ���� 䠩� � �����뢠�� � ���� ᮤ�ন��� ����

do_io		proc	near
	push cs
	pop ds

	mov	byte ptr io_needed,0 ; ����� 䫠� �ॡ��饩�� 
				; ����� �� ���

	call	ems_init	; �⮡ࠧ��� � ���� EMS ��� ����
	
	mov	ah,6Ch	; �㭪�� DOS 6Ch
	mov	bx,2		; ����� - �� �⥭��/������
	mov	cx,0		; ��ਡ��� - ����� 䠩�
	mov	dx,12h	; �������� 䠩�, �᫨ �� �������,
				; ᮧ������, �᫨ ���
	mov	si,offset filespec	; DS:SI - ��� 䠩��
	int	21h		; ᮧ����/������ 䠩�
	mov	bx,ax		; �����䨪��� 䠩�� - � BX

	mov	ah,40h	; �㭪�� DOS 40h
	mov	cx,bfsize	; ࠧ��� BMP-䠩��
	mov	ds,word ptr buffer_seg
	mov	dx,0		; DS:DX - ���� ��� 䠩��
	int	21h		; ������ � 䠩� ��� ���ன�⢮

	mov	ah,68h	; ����� ���� �� ���
	int	21h

	mov	ah,3Eh	; ������� 䠩�
	int	21h

	call	ems_reset

	ret
do_io		endp


; ��楤�� ems_init
; �᫨ ���� �ᯮ����� � EMS - �����⠢������ ��� ��� �⥭��/�����

ems_init proc near

	cmp	dx,word ptr ems_handle	; �᫨ �� �ᯮ������ EMS
	cmp	dx,0 		; (EMS-�����䨪���� ��稭����� � 1),
	je	ems_init_exit		; ��祣� �� ������

	mov	ax,4700h	; �㭪�� EMS 47h
	int	67h		; ��࠭��� EMS-���⥪��

	mov	ax,4100h	; �㭪�� EMS 41h
	int	67h		; ��।����� ���� ���� EMS
	mov	word ptr buffer_seg,bx	; ��࠭��� ���

	mov	ax,4400h	; �㭪�� EMS 44h
	mov	bx,0		; ��稭�� � ��࠭��� 0,
	int	67h		; �⮡ࠧ��� ��࠭��� EMS � ����
	mov	ax,4401h
	inc	bx
	int	67h		; ��࠭�� 1
	mov	ax,4402h
	inc	bx
	int	67h		; ��࠭�� 2
	mov	ax,4403h
	inc	bx
	int	67h		; ��࠭�� 3
ems_init_exit:
	ret
ems_init endp


; ��楤�� ems_reset
; ����⠭�������� ���ﭨ� EMS
ems_reset proc near
	mov	dx,word ptr cs:ems_handle
	cmp	dx,0
	je	ems_reset_exit

	mov	ax,4800h	; �㭪�� EMS 48h
	int	67h		; ����⠭����� EMS-���⥪��
ems_reset_exit:
	ret
ems_reset endp


; ��楤�� safe_check
; �����頥� CF = 0, �᫨ � ����� ������ ����� ���짮������ �㭪�ﬨ DOS,
; � CF = 1, �᫨ �����
safe_check	proc	near
	push	es
	push	cs
	pop	ds

	les	di,dword ptr in_dos_addr ; ���� 䫠��� ������� DOS,
	cmp	word ptr es:[di],0	; �᫨ ���� �� ��� �� 0,
	pop	es
	jne	safe_check_failed	; ���짮������ DOS �����,

	cmp	byte ptr bios_busy,0 ; �᫨ �믮������ ���뢠��� 13h,
	jne	safe_check_failed	; ⮦� �����

	clc		; CF = 0
	ret
safe_check_failed:
	stc		; CF = 1
	ret
safe_check	endp

in_dos_addr	dd	?	; ���� 䫠��� ������� DOS
io_needed	db	0	; 1, �᫨ ���� ������� 䠩� �� ���
bios_busy	db	0	; 1, �᫨ �믮������ ���뢠��� INT 13h
buffer_seg	dw	0	; ᥣ����� ���� ���� ��� 䠩��
ems_handle	dw	0	; �����䨪��� EMS
filespec	db	'scrgrb.bmp',0	; ��� 䠩��


; ��ࠡ��稪 INT 2Dh

hw_reset2D:	retf
int2Dh_handler	proc	far
		jmp short actual_int2Dh_handler	; �ய����� ISP
old_int2Dh	dd	?
		dw	424Bh
		db	00h
		jmp short hw_reset2D
		db	7 dup (0)
actual_int2Dh_handler:		; ᮡ�⢥��� ��ࠡ��稪
		db	80h,0FCh	; ��砫� ������� CMP AH, �᫮
mux_id	db	?		; �����䨪��� �ணࠬ��,
		je	its_us	; �᫨ ��뢠�� � �㦨� AH - �� �� ���
		jmp	dword ptr cs:old_int2Dh
its_us:
	cmp	al,06		; �㭪樨 AMIS 06h � ���
	jae	int2D_no	; �� �����ন������
	cbw			; AX = ����� �㭪樨
	mov	di,ax		; DI = ����� �㭪樨
	shl	di,1		;  * 2, ⠪ ��� jumptable - ⠡��� ᫮�
	jmp	word ptr cs:jumptable[di]	; ���室 �� 
					; ��ࠡ��稪 �㭪樨
jumptable	dw	offset int2D_00,offset int2D_no
		dw	offset int2D_02,offset int2D_no
		dw	offset int2D_04,offset int2D_05

int2D_00: ; �஢�ઠ ������
	mov	al,0FFh	; ��� ����� �����
	mov	cx,0100h	; ����� ���ᨨ �ணࠬ�� 1.0
	push	cs
	pop	dx		; DX:DI - ���� AMIS-ᨣ������
	mov	di,offset amis_sign
	iret
int2D_no: ; �������ন������ �㭪��
	mov	al,00h	; �㭪�� �� �����ন������
	iret

unload_failed:	; � ��।����� �ࠢ�����, �᫨ ��� ���� �� ����஢ 
		; ���뢠��� �� ���墠祭 ���-� ��᫥ ���,
	mov	al,01h	; ���㧪� �ணࠬ�� �� 㤠����
	iret
int2D_02: ; ���㧪� �ணࠬ�� �� �����
	cli		; ����᪨� ���⮪
	push	0
	pop	ds	; DS - ᥣ����� ���� ⠡���� ����஢ 
				; ���뢠���
	mov	ax,cs	; ��� ᥣ����� ����
; �஢����, �� �� ���墠祭�� ���뢠��� ��-�०���� 㪠�뢠�� �� ���
; ���筮 �����筮 �஢���� ⮫쪮 ᥣ����� ���� (DOS �� ����㧨� ����� 
; �ணࠬ�� � ��訬 ᥣ����� ���ᮬ)
	cmp	ax,word ptr ds:[09h*4+2]
	jne	unload_failed
	cmp	ax,word ptr ds:[13h*4+2]
	jne	unload_failed
	cmp	ax,word ptr ds:[08h*4+2]
	jne	unload_failed
	cmp	ax,word ptr ds:[28h*4+2]
	jne	unload_failed
	cmp	ax,word ptr ds:[2Dh*4+2]
	jne	unload_failed

	push	bx		; ���� ������ - � �⥪
	push	dx

; ����⠭����� ���� ��ࠡ��稪� ���뢠���
	mov	ax,2509h
	lds	dx,dword ptr cs:old_int09h
	int	21h
	mov	ax,2513h
	lds	dx,dword ptr cs:old_int13h
	int	21h
	mov	ax,2508h
	lds	dx,dword ptr cs:old_int08h
	int	21h
	mov	ax,2528h
	lds	dx,dword ptr cs:old_int28h
	int	21h
	mov	ax,252Dh
	lds	dx,dword ptr cs:old_int2Dh
	int	21h

	mov	dx,word ptr cs:ems_handle ; �᫨ �ᯮ������ 
	cmp	dx,0				; EMS
	je	no_ems_to_unhook
	mov	ax,4500h	; �㭪�� EMS 45h
	int	67h		; �᢮������ �뤥������ ������
	jmp short ems_unhooked
no_ems_to_unhook:
ems_unhooked:

; ᮡ�⢥��� ���㧪� १�����
	mov	ah,51h	; �㭪�� DOS 51h
	int	21h		; ������� ᥣ����� ���� PSP 
				; ��ࢠ����� ����� (� ������ ��砥
				; PSP ����� ��襩 �ணࠬ��, ����饭��� � ���箬 /u)
	mov	word ptr cs:[16h],bx	; �������� ��� � ����
				; "ᥣ����� ���� �।��" � ��襬 PSP
	pop	dx	; ����⠭����� ���� ������ �� �⥪�
	pop	bx
	mov	word ptr cs:[0Ch],dx ; � �������� ��� � ����
	mov	word ptr cs:[0Ah],bx ; "���� ���室� �� 
					; �����襭�� �ணࠬ��" � ��襬 PSP
	push	cs
	pop	bx		; BX = ��� ᥣ����� ���� PSP
	mov	ah,50h	; �㭪�� DOS 50h
	int	21h		; ��⠭����� ⥪�騩 PSP
; ⥯��� DOS ��⠥� ��� १����� ⥪�饩 �ணࠬ���, � scrgrb.com /u - 
; �맢��襬 ��� ����ᮬ, ���஬� � ��।��� �ࠢ����� ��᫥ �맮�� 
; ᫥���饩 �㭪樨
	mov	ax,4CFFh	; �㭪�� DOS 4Ch
	int	21h		; �������� �ணࠬ��

int2D_04: ; ������� ᯨ᮪ ���墠祭��� ���뢠���
	mov	dx,cs		; ᯨ᮪ � DX:BX
	mov	bx,offset amis_hooklist
	iret
int2D_05: ; ������� ᯨ᮪ ������ ������
	mov	al,0FFh	; �㭪�� �����ন������
	mov	dx,cs		; ᯨ᮪ � DX:BX
	mov	bx,offset amis_hotkeys
	iret
int2Dh_handler	endp

; AMIS: ᨣ����� ��� १����⭮� �ணࠬ��
amis_sign	db	"Cubbi   "	; 8 ���⮢
		db	"ScrnGrab"	; 8 ���⮢
		db	"Simple screen grabber using EMS",0

; AMIS: ᯨ᮪ ���墠祭��� ���뢠���
amis_hooklist	db	09h
		dw	offset int09h_handler
		db	08h
		dw	offset int08h_handler
		db	28h
		dw	offset int28h_handler
		db	2Dh
		dw	offset int2Dh_handler
; AMIS: ᯨ᮪ ������ ������
amis_hotkeys	db	1
		db	1
		db	22h	; ᪠�-��� ������ (G)
		dw	08h	; �ॡ㥬� 䫠�� ����������
		dw	0
		db	1

; ����� १����⭮� ���
; ��砫� ��楤��� ���樠����樨

initialize	proc near
		jmp short initialize_entry_point ; �ய��⨬ ࠧ���� 
; ��ਠ��� ��室� ��� ��⠭���� १�����, ����饭�� ����� 
; ��⮬�, �� �� ��� ��।��� �ࠢ����� ������� �᫮����� 
; ���室�, ����騥 ���⪨� ࠤ��� ����⢨�

exit_with_message:
		mov	ah,9	; �㭪�� �뢮�� ��ப� �� �࠭
		int	21h
		ret		; ��室 �� �ணࠬ��

already_loaded:	; �᫨ �ணࠬ�� 㦥 ����㦥�� � ������
	cmp	byte ptr unloading,1	; �᫨ �� �� �뫨 �맢��� � /u
	je	do_unload
	mov	dx,offset already_msg
	jmp short exit_with_message

no_more_mux:	; �᫨ ᢮����� �����䨪��� INT 2Dh �� ������
	mov	dx,offset no_more_mux_msg
	jmp short exit_with_message

cant_unload1:	; �᫨ ����� ���㧨�� �ணࠬ��
	mov	dx,offset cant_unload1_msg
	jmp short exit_with_message

do_unload:	; ���㧪� १�����: �� ��।�� �ࠢ����� � AH ᮤ�ন� 
		; �����䨪��� �ணࠬ�� - 1
	inc	ah
	mov	al,02h		; AMIS-�㭪�� ���㧪� १�����
	mov	dx,cs			; ���� ������
	mov	bx,offset exit_point	; � DX:BX
	int	2Dh	; �맮� ��襣� १����� �१ ���⨯�����

	push	cs	; �᫨ �ࠢ����� ��諮 � - ���㧪� �� �ந��諠
	pop	ds
	mov	dx,offset cant_unload2_msg
	jmp short exit_with_message

exit_point:	; �᫨ �ࠢ����� ��諮 � - ���㧪� �ந��諠
	push	cs
	pop	ds
	mov	dx,offset unloaded_msg
	push	0		; �⮡� �ࠡ�⠫� ������� RET ��� ��室�
	jmp short exit_with_message

initialize_entry_point:	; � ��।����� �ࠢ����� � ᠬ�� ��砫�
	cld

	cmp	byte ptr cmd_line[1],'/'
	jne	not_unload
	cmp	byte ptr cmd_line[2],'u' ; �᫨ ��� �맢��� � /u,
	jne	not_unload
	mov	byte ptr unloading,1	; ���㧨�� १�����
not_unload:

	mov	ah,9
	mov	dx,offset usage ; �뢮� ��ப� � ���ଠ樥� � �ணࠬ��
	int	21h

	mov	ah,-1		; ᪠��஢���� �� FFh �� 01h
more_mux:
	mov	al,00h	; �㭪�� AMIS 00h - �஢�ઠ ������ १�����
	int	2Dh		; ���⨯����୮� ���뢠���
	cmp	al,00h	; �᫨ �����䨪��� ᢮�����,
	jne	not_free
	mov	byte ptr mux_id,ah ; ������ ��� �ࠧ� � ��� ��ࠡ��稪�,
	jmp short next_mux
not_free:
	mov	es,dx		; ���� - ES:DI = ���� AMIS-ᨣ������ 
				; �맢��襩 �ணࠬ��
	mov	si,offset amis_sign ; DS:SI = ���� ��襩 ᨣ������
	mov	cx,16		; �ࠢ��� ���� 16 ���⮢,
	repe	cmpsb
	jcxz	already_loaded	; �᫨ ��� �� ᮢ������,
next_mux:
	dec	ah		; ��३� � ᫥���饬� �����䨪����,
	jnz	more_mux	; �᫨ �� 0

free_mux_found:
	cmp	byte ptr unloading,1 ; � �᫨ ��� �맢��� ��� ���㧪�,
	je	cant_unload1	; � �� ��諨 � - �ணࠬ�� ��� � 
				; �����,
	cmp	byte ptr mux_id,0	; �᫨ �� �⮬ mux_id �� �� 0,
	je	no_more_mux		; �����䨪���� ���稫���

; �஢�ઠ ������ ���ன�⢠ EMMXXXX0
	mov	dx,offset ems_driver
	mov	ax,3D00h
	int	21h		; ������ 䠩�/���ன�⢮
	jc	no_emmx
	mov	bx,ax
	mov	ax,4400h
	int	21h		; IOCTL: ������� ���ﭨ� 䠩��/���ன�⢠
	jc	no_ems
	test	dx,80h	; �᫨ ���訩 ��� DX = 0, EMMXXXX0 - 䠩�
	jz	no_ems
; �뤥���� ������ ��� ���� � EMS
	mov	ax,4100h	; �㭪�� EMS 41h
	int	67h		; ������� ���� ���� EMS
	mov	bp,bx		; ��࠭��� ��� ���� � BP
	mov	ax,4300h	; �㭪�� EMS 43h
	mov	bx,4		; ��� ���� 4 * 16 K�
	int	67h		; �뤥���� EMS-������ (�����䨪��� � DX),
	cmp	ah,0		; �᫨ �ந��諠 �訡�� (��墠⪠ �����?),
	jnz	ems_failed	; �� �㤥� ���짮������ EMS,
	mov	word ptr ems_handle,dx ; ����: ��࠭��� �����䨪��� 
				; ��� १�����
	mov	ax,4400h	; �㭪�� 44h - �⮡ࠧ��� EMS-��࠭��� � ����
	mov	bx,0
	int	67h		; ��࠭�� 0
	mov	ax,4401h
	inc	bx
	int	67h		; ��࠭�� 1
	mov	ax,4402h
	inc	bx
	int	67h		; ��࠭�� 2
	mov	ax,4403h
	inc	bx
	int	67h		; ��࠭�� 3

	mov	ah,9
	mov	dx,offset ems_msg ; �뢥�� ᮮ�饭�� �� ��⠭���� � EMS
	int	21h

	mov	ax,bp
	jmp short ems_used

ems_failed:
no_ems:			; �᫨ EMS ��� ��� �� �� ࠡ�⠥�,
	mov	ah,3Eh
	int	21h		; ������� 䠩�/���ன�⢮ EMMXXXX0,
no_emmx:
; ������ ����� ������
	mov	ah,9
	mov	dx,offset conv_msg ; �뢮� ᮮ�饭�� �� �⮬
	int	21h

	mov	sp,length_of_program+100h+200h ; ��७��� �⥪
	
	mov	ah,4Ah		; �㭪�� DOS 4Ah
next_segment = length_of_program+100h+200h+0Fh
next_segment = next_segment/16	; ⠪�� ������ �㦭� ⮫쪮 ��� 
; WASM, ��⠫�� ��ᥬ���ࠬ �� 
; ����� �뫮 ������� � ���� �����
	mov	bx,next_segment	; 㬥����� ������� ������, ��⠢�� 
		; ⥪���� ����� ��襩 �ணࠬ�� +100h 
		; �� PSP +200h �� �⥪
	int	21h

	mov	ah,48h		; �㭪�� 48h - �뤥���� ������
bfsize_p = bfsize+0Fh
bfsize_p = bfsize_p/16
	mov	bx,bfsize_p	; ࠧ��� BMP-䠩�� 320x200x256 � 16-������
	int	21h		; ��ࠣ���

ems_used:
	mov	word ptr buffer_seg,ax	; ��࠭��� ���� ���� ��� 
					; १�����

; ᪮��஢��� ��������� BMP-䠩�� � ��砫� ����
	mov	cx,BMP_header_length
	mov	si,offset BMP_header
	mov	di,0
	mov	es,ax
	rep movsb

; ������� ���� 䫠�� ������� DOS � 䫠�� ����᪮� �訡�� (����, �� 
; ����� DOS ���� 3.0)
	mov	ah,34h		; �㭪�� 34h - ������� 䫠� �������
	int	21h
	dec	bx			; 㬥����� ���� �� 1, �⮡� �� 㪠�뢠� 
					; �� 䫠� ����᪮� �訡��,
	mov	word ptr in_dos_addr,bx
	mov	word ptr in_dos_addr+2,es ; � ��࠭��� ��� ��� १�����

; ���墠� ���뢠���
	mov	ax,352Dh		; AH = 35h, AL = ����� ���뢠���
	int	21h			; ������� ���� ��ࠡ��稪� INT 2Dh
	mov	word ptr old_int2Dh,bx	; � �������� ��� � old_int2Dh
	mov	word ptr old_int2Dh+2,es
	mov	ax,3528h		; AH = 35h, AL = ����� ���뢠���
	int	21h			; ������� ���� ��ࠡ��稪� INT 28h
	mov	word ptr old_int28h,bx	; � �������� ��� � old_int28h
	mov	word ptr old_int28h+2,es
	mov	ax,3508h		; AH = 35h, AL = ����� ���뢠���
	int	21h			; ������� ���� ��ࠡ��稪� INT 08h
	mov	word ptr old_int08h,bx	; � �������� ��� � old_int08h
	mov	word ptr old_int08h+2,es
	mov	ax,3513h		; AH = 35h, AL = ����� ���뢠���
	int	21h			; ������� ���� ��ࠡ��稪� INT 13h
	mov	word ptr old_int13h,bx	; � �������� ��� � old_int13h
	mov	word ptr old_int13h+2,es
	mov	ax,3509h		; AH = 35h, AL = ����� ���뢠���
	int	21h			; ������� ���� ��ࠡ��稪� INT 09h
	mov	word ptr old_int09h,bx	; � �������� ��� � old_int09h
	mov	word ptr old_int09h+2,es

	mov	ax,252Dh		; AH = 25h, AL = ����� ���뢠���
	mov	dx,offset int2Dh_handler ; DS:DX - ���� ��ࠡ��稪�
	int	21h			; ��⠭����� ���� ��ࠡ��稪 INT 2Dh
	mov	ax,2528h		; AH = 25h, AL = ����� ���뢠���
	mov	dx,offset int28h_handler ; DS:DX - ���� ��ࠡ��稪�
	int	21h			; ��⠭����� ���� ��ࠡ��稪 INT 28h
	mov	ax,2508h		; AH = 25h, AL = ����� ���뢠���
	mov	dx,offset int08h_handler ; DS:DX - ���� ��ࠡ��稪�
	int	21h			; ��⠭����� ���� ��ࠡ��稪 INT 08h
	mov	ax,2513h		; AH = 25h, AL = ����� ���뢠���
	mov	dx,offset int13h_handler ; DS:DX - ���� ��ࠡ��稪�
	int	21h			; ��⠭����� ���� ��ࠡ��稪 INT 13h
	mov	ax,2509h		; AH = 25h, AL = ����� ���뢠���
	mov	dx,offset int09h_handler ; DS:DX - ���� ��ࠡ��稪�
	int	21h			; ��⠭����� ���� ��ࠡ��稪 INT 09h

; �᢮������ ������ ��-��� ���㦥��� DOS
	mov	ah,49h		; �㭪�� DOS 49h
	mov	es,word ptr envseg ; ES = ᥣ����� ���� ���㦥��� DOS
	int	21h			; �᢮������ ������

; ��⠢��� �ணࠬ�� १����⭮�
	mov	dx,offset initialize ; DX - ���� ��ࢮ�� ���� �� ���殬 
					; १����⭮� ���
	int	27h			; �������� �믮������, ��⠢��� 
					; १����⮬
initialize	endp

ems_driver	db	'EMMXXXX0',0	; ��� EMS-�ࠩ��� ��� �஢�ન

; ⥪��, ����� �뤠�� �ணࠬ�� �� ����᪥:
usage		db	'Screen Grab sample program for video mode'
		db	' 13h only ',0Dh,0Ah
		db	' Alt-G    - capture screen'
		db	' image',0Dh,0Ah
		db	' scrgrb.com /u - unload from'
		db	' memory',0Dh,0Ah
		db	'$'
; ⥪���, ����� �뤠�� �ணࠬ�� �� �ᯥ譮� �믮������:
ems_msg	db	'Loaded into EMS',0Dh,0Ah,'$'
conv_msg	db	'Loaded into conventional'
		db	' memory',0Dh,0Ah,'$'
unloaded_msg	db	'Unloaded successfully',0Dh,0Ah,'$'
; ⥪���, ����� �뤠�� �ணࠬ�� �� �訡���:
already_msg		db	'ERROR: Already loaded',0Dh,0Ah,'$'
no_more_mux_msg	db	'ERROR: Too many TSR programs'
		db	'loaded',0Dh,0Ah,'$'
cant_unload1_msg	db	"ERROR: Can't unload: program not found in memory",0Dh,0Ah,'$'
cant_unload2_msg	db	"ERROR: Can't unload: another TSR hooked interrupts",0Dh,0Ah,'$'
unloading	db	0	; 1, �᫨ ��� �����⨫� � ���箬 /u

; BMP-䠩� (��� ����ࠦ���� 320x200x256)
BMP_header	label	byte
; 䠩���� ���������
BMP_file_header	db	"BM"		; ᨣ�����
		dd	bfsize	; ࠧ��� 䠩��
		dw	0,0		; 0
		dd	bfoffbits ; ���� ��砫� BMP_data
				; ���ଠ樮��� ���������
BMP_info_header	dd	bi_size	; ࠧ��� BMP_info_header
		dd	320		; �ਭ�
		dd	200		; ����
		dw	1		; �᫮ 梥⮢�� ���᪮�⥩
		dw	8		; �᫮ ��⮢ �� ���ᥫ�
		dd	0		; ��⮤ ᦠ�� ������
		dd	320*200	; ࠧ��� ������
		dd	0B13h	; ࠧ�襭�� �� X (���ᥫ� �� ����)
		dd	0B13h	; ࠧ�襭�� �� Y (���ᥫ� �� ����)
		dd	0	; �᫮ �ᯮ��㥬�� 梥⮢ (0 - ��)
		dd	0	; �᫮ ������ 梥⮢ (0 - ��)
bi_size = $-BMP_info_header	; ࠧ��� BMP_info_header
BMP_header_length = $-BMP_header	; ࠧ��� ����� ����������
bfoffbits = $-BMP_file_header+256*4 ; ࠧ��� ���������� + ࠧ��� 
					; �������
bfsize = $-BMP_file_header+256*4+320*200 ; ࠧ��� ���������� + 
					; ࠧ��� ������� + ࠧ��� ������
length_of_program = $-start
		end	start
