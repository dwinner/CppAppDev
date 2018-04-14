; wavdma.asm
; �p���p �p��p����, �p���p뢠�饩 䠩� C:\WINDOWS\MEDIA\TADA.WAV
; �� ��㪮��� ��p� �p� ����� DMA
;
; ���������:
; TASM:
;  tasm /m wavdma.asm
;  tlink /t /x wavdma.obj
; MASM:
;  ml /c wavdma.asm
;  link wavdma.obj,,NUL,,,
;  exe2bin wavdma.exe wavdma.com
; WASM:
;  wasm wavdma.asm
;  wlink file wavdma.obj form DOS COM
;
FILESPEC equ 'c:\windows\media\tada.wav' ; ������� �� c:\windows\tada.wav
					 ; ��� ����� ���ᨩ windows
SBPORT	equ 220h
; SBDMA	equ 1		; ��楤�� program_dma ���⠭� ⮫쪮 �� ����� 1
SBIRQ	equ 5		; ⮫쪮 IRQ0-IRQ7
	.model	tiny
	.code
	.186
	org	100h		; COM-�ணࠬ��
start:
	call	dsp_reset	; ���樠������ DSP
	jc	no_blaster
	mov	bl,0D1h		; ������� 0D1h
	call	dsp_write	; ������� ���
	call	open_file	; ������ 䠩� � ����
	call	hook_sbirq	; ���墠��� ���뢠���
	mov	bl,40h		; ������� 40h
	call	dsp_write	; ��⠭���� ᪮��� ��।��
	mov	bl,0B2h		; ����⠭� ��� 11025Hz/Stereo
	call	dsp_write
	call	program_dma	; ���� DMA-��।��� ������

main_loop:			; �᭮���� 横�
	cmp	byte ptr finished_flag,0
	je	main_loop	; ��室 ����� ���� finished_flag = 1

	call	restore_sbirq	; ����⠭����� ���뢠���
no_blaster:
	ret

old_sbirq	dd	?	; ���� ��ண� ��ࠡ��稪�
finished_flag	db	0	; 䫠� ����砭�� ࠡ���
filename	db	FILESPEC,0	; ��� 䠩��

; ��ࠡ��稪 ���뢠��� ��㪮��� �����
; ��⠭�������� 䫠� finished_flag � 1
sbirq_handler	proc	far
	push	ax
	mov	byte ptr cs:finished_flag,1	; ��⠭����� 䫠�
	mov	al,20h		; ��᫠�� ������� EOI
	out	20h,al		; � ����஫��� ���뢠���
	pop	ax
	iret
sbirq_handler	endp

; ��楤�� dsp_reset
; ��� � ���樠������ DSP
dsp_reset proc near
	mov	dx,SBPORT+6 ; ���� 226h - ॣ���� ��� DSP
	mov	al,1	; ������ � ���� ������� ����᪠�� ���樠������
	out	dx,al
	mov	cx,40	; �������� ��㧠
dsploop:
	in	al,dx
	loop	dsploop
	mov	al,0	; ������ ��� �����蠥� ���樠������
	out	dx,al	; ⥯��� DSP ��⮢ � ࠡ��

	add	dx,8	; ���� 22Eh - ��� 7 �� �⥭�� 㪠�뢠�� �� ��������
	mov	cx,100	; ���� ����� DSP
check_port:
	in	al,dx	; ���⠥� ���ﭨ� ���� �����
	and	al,80h	; �᫨ ��� 7 ����
	jz	port_not_ready	; ���� ��� �� ��⮢
	sub	dx,4	; ����: ���� 22Ah - �⥭�� ������ �� DSP
	in	al,dx
	add	dx,4	; ���� ᭮�� 22Eh 
	cmp	al,0AAh	; �஢�ਬ, �� DSP �����頥� 0AAh �� �⥭�� - 
			; �� ᨣ��� ��� ��⮢���� � ࠡ��
	je	good_reset
port_not_ready:
	loop	check_port ; ������� �஢��� �� 0AAh 100 ࠧ 
bad_reset:
	stc		; �᫨ Sound Blaster �� �⪫�������
	ret		; �������� � CF=1
good_reset:
	clc		; �᫨ ���樠������ ��諠 �ᯥ譮
	ret		; �������� � CF=0
dsp_reset endp

; ��楤�� dsp_write
; ���뫠�� ���� �� BL � DSP
dsp_write proc near
	mov	dx,SBPORT+0Ch ; ���� 22Ch - ���� ������/������ DSP
write_loop:		; ������� ��⮢���� ���� ����� DSP
	in	al,dx	; ���⠥� ���� 22Ch
	and	al,80h	; � �஢�ਬ ��� 7
	jnz	write_loop ; �᫨ �� �� ���� - ������� ���
	mov	al,bl	; ����:
	out	dx,al	; ���� �����
	ret
dsp_write endp

; ��楤�� hook_sbirq
; ���墠�뢠�� ���뢠��� ��㪮��� ����� � ࠧ�蠥� ���
hook_sbirq proc	near
	mov	ax,3508h+SBIRQ	; AH=35h, AL=����� ���뢠���
	int	21h		; ����稬 ���� ��ண� ��ࠡ��稪�
	mov	word ptr old_sbirq,bx	; � ��࠭�� ���
	mov	word ptr old_sbirq+2,es
	mov	ax,2508h+SBIRQ	; AH=25h, AL=����� ���뢠���
	mov	dx,offset sbirq_handler	; ��⠭���� ���� ��ࠡ��稪
	int	21h
	mov	cl,1
	shl	cl,SBIRQ
	not	cl		; ����ந� ��⮢�� ����
	in	al,21h		; ���⠥� OCW1
	and	al,cl		; ࠧ�訬 ���뢠���
	out	21h,al		; ����襬 OCW1
	ret
hook_sbirq endp

; ��楤�� restore_sbirq
; ����⠭���� ��ࠡ��稪 � ����⨬ ���뢠���
restore_sbirq	proc near
	mov	ax,3508h+SBIRQ	; AH=25h AL=����� ���뢠���
	lds	dx,dword ptr old_sbirq
	int	21h		; ����⠭���� ��ࠡ��稪
	mov	cl,1
	shl	cl,SBIRQ	; ����ந� ��⮢�� ����
	in	al,21h		; ���⠥� OCW1
	or	al,cl		; ����⨬ ���뢠���
	out	21h,al		; ����襬 OCW1
	ret
restore_sbirq	endp

; ��楤�� open_file
; ���뢠�� 䠩� filename � ������� ��㪮�� ����� �� ����, ���� ��
; �� - tada.wav, � ���� buffer
open_file proc near
	mov	ax,3D00h	; AH=3Dh AL=00
	mov	dx,offset filename	; DS:DX - ASCIZ-��ப� � ������ 䠩��
	int	21h		; ������ 䠩� ��� �⥭��
	jc	error_exit	; �᫨ �� 㤠���� ������ 䠩� - ���
	mov	bx,ax		; �����䨪��� 䠩�� � BX
	mov	ax,4200h	; AH=42h, AL=0
	mov	cx,0		; CX:DX - ����� ���祭�� 㪠��⥫�
	mov	dx,38h	; �� �⮬� ����� ��稭����� ����� � tada.wav
	int	21h		; ��६��⨬ 䠩���� 㪠��⥫�
	mov	ah,3Fh		; AH=3Fh
	mov	cx,27459 ; �� - ����� ������ � 䠩�� tada.wav
	push	ds
	mov	dx,ds
	and	dx,0F000h	; ��஢�塞 ���� �� �࠭��� 4K-��࠭���
	add	dx,1000h	; ��� DMA
	mov	ds,dx
	mov	dx,0		; DS:DX - ���� ����
	int	21h		; �⥭�� 䠩��
	pop	ds
	ret
error_exit:			; �᫨ �� 㤠���� ������ 䠩�
	mov	ah,9		; AH=09h
	mov	dx,offset notopenmsg	; DS:DX = ���� ᮮ�饭�� �� �訡��
	int	21h		; �뢮� ��ப� �� �࠭
	int	20h		; ����� �ணࠬ��
notopenmsg	db	'Could not open file',0Dh,0Ah	; ᮮ�饭�� �� �訡��
		db	'Exiting',0Dh,0Ah,'$'
open_file endp

; ��楤�� program_dma
; ����ࠨ���� ����� 1 DMA
program_dma proc near
	mov	al,5	; ����᪨�㥬 ����� 1
	out	0Ah,al
	xor	al,al	; ���㫨� ����稪
	out	0Ch,al
	mov	al,49h	; ��⠭���� ०�� ��।��
			; (�ᯮ���� 59h ��� ��⮨��樠����樨)
	out	0Bh,al

	push	cs
	pop	dx
	and	dh,0F0h
	add	dh,10h	; ���᫨� ���� ����

	xor	ax,ax
	out	02h,al	; ����襬 ����訥 8 ���
	out	02h,al	; ����襬 ᫥���騥 8 ���
	mov	al,dh
	shr	al,4
	out	83h,al	; ����襬 ���訥 4 ���

	mov	ax,27459	; ����� ������ � tada.wav
	dec	ax		; DMA �ॡ�� �����-1
	out	03h,al		; ����襬 ����訥 8 ��� �����
	mov	al,ah
	out	03h,al		; ����襬 ���訥 8 ��� �����
	mov	al,1
	out	0Ah,al		; ᭨��� ���� � ������ 1

	mov	bl,14h		; ������� 14h
	call	dsp_write	; 8-��⭮� ���⮥ DMA-���ந��������
	mov	bx,27459	; ࠧ��� ������ � tada.wav
	dec	bx		; ����� 1
	call	dsp_write	; ����襬 � DSP ����訥 8 ��� �����
	mov	bl,bh
	call	dsp_write	; � ���訥
	ret
program_dma endp
	end	start
