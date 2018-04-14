; tieload.asm
; �ਬ�� ����१����⭮� �ணࠬ�� - �����稪, ���࠭��騩 �஢��� ��஫� 
; ��� ��� �������� Lucasarts:
; "X-Wing", "X-Wing: Imperial Pursuit", "B-Wing",
; "Tie Fighter", "Tie Fighter: Defender of the Empire"
;
; ���������:
; TASM:
;  tasm /m tieload.asm
;  tlink /t /x tieload.obj
; MASM:
;  ml /c tieload.asm
;  link tieload.obj,,NUL,,,
;  exe2bin tieload.exe tieload.com
; WASM:
;  wasm tieload.asm
;  wlink file tieload.obj form DOS COM
;

	.model	tiny
	.code
	.386			; ��� ������� LSS
	org	100h		; COM-�ணࠬ��
start:
; �᢮������ ������ ��᫥ ���� �ணࠬ�� (+ �⥪)
	mov	sp,length_of_program	; ��७��� �⥪
	mov	ah,4Ah		; �㭪�� DOS 4Ah
	mov	bx,par_length	; ࠧ��� � ��ࠣ���
	int	21h			; �������� ࠧ��� �뤥������ �����

; ��������� ���� EPB, ᮤ�ঠ騥 ᥣ����� ����
	mov	ax,cs
	mov	word ptr EPB+4,ax
	mov	word ptr EPB+8,ax
	mov	word ptr EPB+0Ch,ax
	
; ����㧨�� �ணࠬ�� ��� �믮������
	mov	bx,offset EPB		; ES:BX - EPB
	mov	dx,offset filename1	; DS:DX - ��� 䠩�� (TIE.EXE)
	mov	ax,4B01h			; �㭪�� DOS 4B01h
	int	21h				; ����㧨�� ��� �믮������
	jnc	program_loaded		; �᫨ TIE.EXE �� ������,
	mov	byte ptr XWING,1		; ��⠭����� 䫠� ��� find_passwd
	mov	ax,4B01h
	mov	dx,offset filename2	; � ���஡����� BWING.EXE,
	int	21h
	jnc	program_loaded		; �᫨ �� �� ������,
	mov	ax,4B01h
	mov	dx,offset filename3	; ���஡����� XWING.EXE,
	int	21h
	jc	error_exit		; �᫨ � �� �� ������ (��� �� ����㦠���� 
		; �� �����-����� ��㣮� ��稭�) - ��� � ᮮ�饭��� �� �訡��

program_loaded:
; ��楤�� �஢�ન ��஫� �� ��室���� �����।�⢥��� � �ᯮ��塞�� 䠩�� 
; tie.exe, bwing.exe ��� xwing.exe, � �����㦠���� ����� �� ���૥� front.ovl, 
; bfront.ovl ��� frontend.ovl ᮮ⢥��⢥���. ���� �������, �믮����騥 �⥭�� 
; �� �⮣� ���૥�, � ��⠭����� �� ��� ��� ��ࠡ��稪 find_passwd
	cld
	push	cs
	pop	ax
	add	ax,par_length
	mov	ds,ax
	xor	si,si		; DS:SI - ���� ��ࠣ�� ��᫥ ���� ��襩 
				; �ணࠬ�� (� ���� ��砫� ������, � ������ 
				; �뫠 ����㦥�� �������㥬�� �ணࠬ��)
	mov	di,offset read_file_code ; ES:DI - ��� ��� �ࠢ�����
	mov	cx,rf_code_l		; CX - ��� �����
	call	find_string		; ���� ����,
	jc	error_exit2		; �᫨ �� �� ������ - ��� � ᮮ�饭��� 
					; �� �訡��
; �������� 6 ���⮢ �� ���������� ���� ��������� call find_passwd � nop
	mov	byte ptr [si], 9Ah	; CALL (���쭨�)
	mov	word ptr [si+1], offset find_passwd
	mov	word ptr [si+3], cs
	mov	byte ptr [si+5],90h	; NOP

; �������� ����㦥���� �ணࠬ��
; ���� ������� �ࠢ���� ��砫�� ���祭�� � ॣ����� ��� EXE-�ணࠬ�� � 
; ��������� ������� ���� �� PSP
	mov	ah,51h	; �㭪�� DOS 51h
	int	21h		; BX = PSP-ᥣ���� ����㦥���� �ணࠬ��
	mov	ds,bx		; �������� ��� � DS
	mov	es,bx		; � ES. ��������� ⠪�� ���� PSP:
	mov	word ptr ds:[0Ah],offset exit_without_msg
	mov	word ptr ds:[0Ch],cs	; "���� ������" 
	mov	word ptr ds:[16h],cs	; � "���� PSP �।��"
	lss	sp,dword ptr cs:EPB_SSSP ; ����㧨�� SS:SP
	jmp	dword ptr cs:EPB_CSIP	; � ��।��� �ࠢ����� �� 
					; ��� �室� �ணࠬ��

XWING	db	0	; 1/0: ⨯ ����� X-wing/Tie-fighter

EPB	dw	0	; ����᪠��� 䠩� ����砥� �।� DOS �� tieload.com,
	dw	0080h,?	; � ��������� ��ப�,
	dw	005Ch,?	; � ���� FCB,
	dw	006Ch,?	; � ��ன FCB
EPB_SSSP	dd	?	; ��砫�� SS:SP - ���������� DOS
EPB_CSIP	dd	?	; ��砫�� CS:IP - ���������� DOS

filename1	db	'tie.exe',0	; ᭠砫� �஡㥬 �������� ��� 䠩�,
filename2	db	'bwing.exe',0	; ��⮬ ���
filename3	db	'xwing.exe',0	; � ��⮬ ���

; ᮮ�饭�� �� �訡���
error_msg	db	'ERROR: could not find TIE.EXE, BWING.EXE,'
		db	'or XWING.EXE',0Dh,0Ah,'$'
error_msg2	db	'ERROR: initial patch failed',0Dh,0Ah,'$'

; �������, �믮����騥 �⥭�� ���૥����� 䠩�� � tie.exe/bwing.exe/xwing.exe:
read_file_code:
	db	33h,0D2h	; xor dx,dx
	db	0B4h,3Fh	; mov ah,3Fh
	db	0CDh,21h	; int 21h
	db	72h		; jz (�� ࠧ�� ���� � xwing � tie)
rf_code_l = $-read_file_code

; �������, ��뢠�騥 ��楤��� �஢�ન ��஫�.
; ��������� ����� ������ ����砥��� � � ��㣨� �����, ���⮬� find_passwd 
; �㤥� �믮����� �������⥫�� �஢�ન
passwd_code:
	db	89h,46h,0FCh	; mov [bp-4],ax
	db	89h,56h,0FEh	; mov [bp-2],dx
	db	52h			; push dx
	db	50h			; push ax
	db	9Ah			; call far
passwd_l = $-passwd_code

error_exit:
	mov	dx,offset error_msg ; �뢮� ᮮ�饭�� �� �訡�� 1
	jmp short exit_with_msg
error_exit2:
	mov	dx,offset error_msg2 ; �뢮� ᮮ�饭�� �� �訡�� 2
exit_with_msg:
	mov	ah,9		; �㭪�� DOS 09h
	int	21h		; �뢥�� ��ப� �� �࠭
exit_without_msg:		; � ⠪�� ��।����� �ࠢ����� ��᫥ 
; �����襭�� ����㦥���� �ணࠬ�� (��� ���� �� ���ᠭ � 
; ���� PSP "���� ������")
	mov	ah,4Ch		; �㭪�� DOS 4Ch
	int	21h		; ����� �ணࠬ��


; ��� ��楤��� ��뢠�� �ணࠬ�� tie.exe/bwing.exe/xwing.exe ����� ࠧ, ����� 
; ��� �믮���� �⥭�� �� ���૥����� 䠩��
find_passwd	proc	far
; �믮����� �� �������, ����� �� �������� �� call find_passwd
	xor dx,dx
	mov ah,3Fh	; �㭪�� DOS 3Fh
	int 21h	; �⥭�� �� 䠩�� ��� ���ன�⢠

deactivation_point: ; �� �⮬� ����� �� ����襬 ��� ������� RETF, 
; ����� ��� ����� �㤥� �믮�����
	pushf		; ��࠭�� 䫠��
	push	ds	; � ॣ�����
	push	es
	pusha

	push	cs
	pop	es
	mov	si,dx	; DS:DX - ��砫� ⮫쪮 �� ���⠭���� ���⪠ 
			; ���૥����� 䠩��
	mov	di,offset passwd_code ; ES:DI - ��� ��� �ࠢ�����
	dec	si		; �祭� ᪮� �� ��� 㢥��稬 ���⭮
search_for_pwd:	; � �⮬ 横�� �������� �宦����� �⠫������ ���� 
		; �஢������� �� �筮� ᮮ⢥��⢨� ���� �஢�ન ��஫�
	inc	si	; ��楤�� find_string �����頥� DS:SI 㪠�뢠�騬 �� 
			; ��砫� ���������� ���� - �⮡� �᪠�� �����, ���� 
			; 㢥����� SI ��� �� �� 1
	mov	cx,passwd_l	; ����� �⠫������ ����
	call	find_string	; ���� ��� � �����,
	jc	pwd_not_found	; �᫨ �� �� ������ - ���
; find_string ��諠 ��।��� �宦����� ��襣� �⠫������ ���� �맮�� 
; ��楤��� - �஢�ਬ, �筮 �� �� �맮� ��楤��� �஢�ન ��஫�
	cmp	byte ptr [si+10],00h	; ��� ���� ������ ���� 00
	jne	search_for_pwd
	cmp	byte ptr cs:XWING,1	; � ��砥 X-wing/B-wing
	jne	check_for_tie
	cmp	word ptr [si+53],0774h	; ������� je ������ ���� �����,
	jne	search_for_pwd
	jmp short pwd_found
check_for_tie:				; � � ��砥 Tie Fighter - 
	cmp	word ptr [si+42],0774h	; �����
	jne	search_for_pwd
pwd_found:	; �⠪, �맮� ��楤��� �஢�ન ��஫� ������ - �⪫���� ���
	mov	word ptr ds:[si+8],9090h	; NOP NOP
	mov	word ptr ds:[si+10],9090h	; NOP NOP
	mov	byte ptr ds:[si+12],90h		; NOP
; � ����⨢�஢��� ���� ��楤��� find_passwd
	mov	byte ptr cs:deactivation_point,0CBh	; RETF

pwd_not_found:
	popa		; ����⠭����� ॣ�����
	pop	es
	pop	ds
	popf		; � 䫠��
	ret		; � ������ �ࠢ����� � �ணࠬ��
find_passwd	endp

; ��楤�� find_string
; �믮���� ���� ��ப� �� ��������� ���� �� ���� �ᥩ ��饩 �����
; ����: ES:DI - ���� �⠫����� ��ப�
; 	CX - �� �����
; 	DS:SI - ����, � ���ண� ��稭��� ����
; �뢮�: CF = 1, �᫨ ��ப� �� �������,
; ����: CF = 0 � DS:SI - ����, � ���ண� ��稭����� ��������� ��ப�

find_string	proc	near
	push	ax
	push	bx
	push	dx	; ��࠭��� ॣ�����

do_cmp: mov	dx,1000h	; ���� ������� �� 1000h (4096 ���⮢)
cmp_loop:
	push	di
	push	si
	push	cx
	repe cmpsb		; �ࠢ���� DS:SI � ��ப��
	pop	cx
	pop	si
	pop	di
	je	found_code	; �᫨ ᮢ������� - ��� � CF = 0,
	inc	si		; ���� - 㢥����� DS:SI �� 1
	dec	dx		; 㬥����� ���稪 � DX
	jne	cmp_loop	; �, �᫨ �� �� ����, �த������
; �ன��� ��।��� 4-��������� ����
	sub	si,1000h	; 㬥����� SI �� 1000h
	mov	ax,ds
	inc	ah		; � 㢥����� DS �� 1
	mov	ds,ax
	cmp	ax,9000h	; �᫨ �� ���ࠫ��� �� 
	jb	do_cmp	; ᥣ���⭮�� ���� 9000h - 

	pop	dx		; ����⠭����� ॣ�����
	pop	bx
	pop	ax
	stc			; ��⠭����� CF = 1
	ret			; � ���
; � ��।����� �ࠢ�����, �᫨ ��ப� �������
found_code:
	pop	dx	; ����⠭����� ॣ�����
	pop	bx
	pop	ax
	clc			; ��⠭����� CF = 0
	ret			; � ���
find_string	endp

end_of_program:
length_of_program = $-start+100h+100h ; ����� �ணࠬ�� � �����
par_length = length_of_program + 0Fh
par_length = par_length/16		; ����� �ணࠬ�� � ��ࠣ���
	end start
