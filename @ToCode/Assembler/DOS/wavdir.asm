; wavdir.asm
; ���ந������ 䠩� c:\windows\media\tada.wav, �� �ᯮ���� DMA
; ��ଠ�쭮 ࠡ�⠥� ⮫쪮 ��� DOS � ॠ�쭮� ०���
; (� ���� �� � ���� DOS (Windows) � �� ��� EMM386, QEMM ��� ��㣨�� 
; ������묨 �ணࠬ����)
;
; ���������:
; TASM:
;  tasm /m wavdir.asm
;  tlink /t /x wavdir.obj
; MASM:
;  ml /c wavdir.asm
;  link wavdir.obj,,NUL,,,
;  exe2bin wavdir.exe wavdir.com
; WASM:
;  wasm wavdir.asm
;  wlink file wavdir.obj form DOS COM
;

FILESPEC equ 'c:\windows\media\tada.wav' ; ��� 䠩�� tada.wav � 
			; ����� ��⥬ (������� �� c:\windows\tada.wav ��� 
			; ����� ���ᨩ Windows)
SBPORT equ 220h	; ������ ���� ��㪮��� ����� (�������, �᫨ � ��� �� 
		; �⫨砥���)

	.model	tiny
	.code
	.186			; ��� pusha/popa 
org	100h		; COM-�ணࠬ��
start:
	call	dsp_reset	; ��� � ���樠������ DSP
	jc	no_blaster
	mov	bl,0D1h	; ������� DSP D1h 
	call	dsp_write	; ������� ���
	call	open_file	; ������ � ������ tada.wav
	call	hook_int8	; ���墠��� ���뢠��� ⠩���
	mov	bx,5		; ����⥫� ⠩��� ��� ����� 22 050 Hz
				; (�� ᠬ�� ���� ᮮ⢥����� 23 867 Hz)
	call	reprogram_pit	; ��९ணࠬ��஢��� ⠩���

main_loop:			; �᭮���� 横�
	cmp	byte ptr finished_flag,0
	je	main_loop	; �믮������, ���� finished_flag ࠢ�� ���

	mov	bx,0FFFFh	; ����⥫� ⠩��� ��� ����� 18,2 Hz
	call	reprogram_pit	; ��९ணࠬ��஢��� ⠩���
	call	restore_int8	; ����⠭����� IRQ0
no_blaster:
	ret

buffer_addr	dw	offset buffer	; ���� ⥪�饣� ��ࠥ���� ����
old_int08h	dd	?		; ���� ��ࠡ��稪 INT 08h (IRQ0)
finished_flag	db	0	; 䫠� �����襭��
filename	db	FILESPEC,0	; ��� 䠩�� tada.wav � ����� ��⥬

; ��ࠡ��稪 INT 08h (IRQ0)
; ���뫠�� ����� �� ���� � ��㪮��� �����
int08h_handler	proc	far
	pusha			; ��࠭��� ॣ�����
	cmp	byte ptr cs:finished_flag,1 ; �᫨ 䫠� 㦥 1,
	je	exit_handler		; ��祣� �� ������,
	mov	di,word ptr cs:buffer_addr ; ����: DI = ���� ⥪�饣� 
					; ����
	mov	bl,10h		; ������� DSP 10h
	call	dsp_write		; �����।�⢥��� 8-���� �뢮�
	mov	bl,byte ptr cs:[di] ; BL = ���� ������ ��� �뢮��
	call	dsp_write
	inc	di			; DI = ���� ᫥���饣� ����
	cmp	di,offset buffer+27459	; 27 459 - ����� ��㪠 � tada.wav,
	jb	not_finished		; �᫨ ���� ���� �ன���,
	mov	byte ptr cs:finished_flag,1 ; ��⠭����� 䫠� � 1,
not_finished:				; ����:
	mov	word ptr cs:buffer_addr,di ; ��࠭��� ⥪�騩 ����
exit_handler:
	mov	al,20h		; �������� ��ࠡ��稪 �����⭮�� ���뢠���,
	out	20h,al		; ��᫠� ��ᯥ���� EOI (�. ��. 1.2.10)
	popa			; ����⠭����� ॣ�����
	iret
int08h_handler	endp

; ��楤�� dsp_reset
; ��� � ���樠������ DSP
dsp_reset proc near
	mov	dx,SBPORT+6 ; ���� 226h - ॣ���� ��� DSP
	mov	al,1	; ������ ������� � ���� ��稭��� ���樠������
	out	dx,al
	mov	cx,40	; �������� ��㧠
dsploop:
	in	al,dx
	loop	dsploop
	mov	al,0	; ������ ��� �����蠥� ���樠������
	out	dx,al	; ⥯��� DSP ��⮢ � ࠡ��
; �஢����, ���� �� DSP �����
	add	dx,8	; ���� 22Eh - ���ﭨ� ���� �⥭�� DSP
	mov	cx,100
check_port:
	in	al,dx		; ������ ���ﭨ� ����
	and	al,80h	; �஢���� ��� 7
	jz	port_not_ready	; �᫨ ���� - ���� �� �� ��⮢
	sub	dx,4	; ����: ���� 22Ah - �⥭�� ������ �� DSP
	in	al,dx
	add	dx,4	; � ᭮�� ���� 22Eh, 
	cmp	al,0AAh	; �᫨ ���⠫��� �᫮ AAh - DSP ���������
			; � ����⢨⥫쭮 ��⮢ � ࠡ��,
	je	good_reset
port_not_ready:
	loop	check_port ; �᫨ ��� - ������� �஢��� 100 ࠧ
bad_reset:
	stc		; � ᤠ����
	ret		; ��室 � CF = 1,
good_reset:
	clc		; �᫨ ���樠������ ��諠 �ᯥ譮
	ret		; ��室 � CF = 0
dsp_reset endp

; ��楤�� dsp_write
; ���뫠�� ���� �� BL � DSP
dsp_write proc near
	mov	dx,SBPORT+0Ch ; ���� 22Ch - ���� ������/������ DSP
write_loop:		; ��������� ��⮢���� ���� ����� DSP
	in	al,dx		; ������ ���� 22Ch
	and	al,80h	; � �஢���� ��� 7,
	jnz	write_loop ; �᫨ �� �� ���� - ��������� ��,
	mov	al,bl		; ����:
	out	dx,al		; ��᫠�� �����
	ret
dsp_write endp

; ��楤�� reprogram_pit
; ��९ணࠬ����� ����� 0 ��⥬���� ⠩��� �� ����� �����
; ����: BX = ����⥫� �����
reprogram_pit	proc	near
	cli		; ������� ���뢠���
	mov	al,00110110b ; ����� 0, ������ ����襣� � ���襣� ���⮢,
				; ०�� ࠡ��� 3, �ଠ� ���稪� - ������
	out	43h,al	; ��᫠�� �� � ॣ���� ������ ��ࢮ�� ⠩���
	mov	al,bl		; ����訩 ���� ����⥫� -
	out	40h,al	; � ॣ���� ������ ������ 0
	mov	al,bh		; � ���訩 ���� -
	out	40h,al	; �㤠 ��
	sti		; ⥯��� IRQ0 ��뢠���� � ���⮩ 1 193 180/BX Hz
	ret
reprogram_pit	endp

; ��楤�� hook_int8
; ���墠�뢠�� ���뢠��� INT 08h (IRQ0)
hook_int8 proc	near
	mov	ax,3508h	; AH = 35h, AL = ����� ���뢠���
	int	21h		; ������� ���� ��ண� ��ࠡ��稪�
	mov	word ptr old_int08h,bx	; ��࠭��� ��� � old_int08h
	mov	word ptr old_int08h+2,es
	mov	ax,2508h	; AH = 25h, AL = ����� ���뢠���
	mov	dx,offset int08h_handler ; DS:DX - ���� ��ࠡ��稪�
	int	21h		; ��⠭����� ��ࠡ��稪
	ret
hook_int8 endp

; ��楤�� restore_int8
; ����⠭�������� ���뢠��� INT 08h (IRQ0)
restore_int8	proc near
	mov	ax,2508h	; AH = 25h, AL = ����� ���뢠���
	lds	dx,dword ptr old_int08h ; DS:DX - ���� ��ࠡ��稪�
	int	21h		; ��⠭����� ���� ��ࠡ��稪
	ret
restore_int8	endp

; ��楤�� open_file
; ���뢠�� 䠩� filename � ������� ��㪮�� ����� �� ����, ���� ��� 䠩��� 
; tada.wav, � ���� buffer
open_file proc near
	mov	ax,3D00h	; AH = 3Dh, AL = 00
	mov	dx,offset filename ; DS:DX - ASCIZ-��� 䠩�� � ��⥬
	int	21h		; ������ 䠩� ��� �⥭��,
	jc	error_exit	; �᫨ �� 㤠���� ������ 䠩� - ���
	mov	bx,ax		; �����䨪��� 䠩�� � BX
	mov	ax,4200h	; AH = 42h, AL = 0
	mov	cx,0		; CX:DX - ����� ���祭�� 㪠��⥫�
	mov	dx,38h ; �� �⮬� ����� ��稭����� ����� � tada.wav
	int	21h		; ��६����� 䠩���� 㪠��⥫�
	mov	ah,3Fh	; AH = 3Fh
	mov	cx,27459 ; �� - ����� ��㪮��� ������ � 䠩�� tada.wav
	mov	dx,offset buffer ; DS:DX - ���� ����
	int	21h		; �⥭�� 䠩��
	ret
error_exit:			; �᫨ �� 㤠���� ������ 䠩�
	mov	ah,9		; AH = 09h
	mov	dx,offset notopenmsg ; DS:DX = ᮮ�饭�� �� �訡��
	int	21h		; ������ 䠩� ��� �⥭��
	int	20h		; ����� �ணࠬ��
notopenmsg	db	'Could not open file',0Dh,0Ah
		db	'Exiting',0Dh,0Ah,'$'
open_file endp

buffer:		; ����� ��稭����� ���� ������ 27 459 ���⮢
	end	start
