; cat.asm
; ������� ��ꥤ������� ᮤ�ন��� ��� 䠩���, 㪠������ � ��������� ��ப�, � 
; �⠭����� �뢮�. ����� ��� 㪠�뢠�� ᯨ᮪ 䠩���, ⠪ � �ᯮ�짮���� ��᪨ 
; (ᨬ���� "*" � "?") � ����� ��� ��᪮�쪨� ��ࠬ����,
; ���ਬ��:
; cat header *.txt footer > all-texts ����頥� ᮤ�ন��� 䠩��
; header, ��� 䠩��� � ���७��� .txt � ⥪�饩 ��४�ਨ, � 䠩�� 
; footer � 䠩� all-texts
; ������ ����� 䠩��� �� �ᯮ�������, �訡�� �����������
;
; ���������:
; TASM:
; tasm /m cat.asm
; tlink /t /x cat.obj
; MASM:
; ml /c cat.asm
; link cat.obj,,NUL,,,
; exe2bin cat.exe cat.com
; WASM:
; wasm cat.asm
; wlink file cat.obj form DOS COM
;


		.model tiny
		.code
		org 80h			; �� ᬥ饭�� 80h �� ��砫� PSP ��室����:
cmd_length	db ?			; ����� ��������� ��ப�
cmd_line	db ?			; � ᠬ� ��������� ��ப�
		org 100h		; ��砫� COM-�ணࠬ�� - 100h �� ��砫� PSP
start:
		cld			; ��� ������ ��ப���� ��ࠡ�⪨
		mov	bp,sp		; ��࠭�� ⥪���� ���設� �⥪� � BP
		mov	cl,cmd_length
		cmp	cl,1		; �᫨ ��������� ��ப� ���� -
		jle	show_usage	; �뢥�� ���ଠ�� � �ணࠬ�� � ���

		mov	ah,1Ah	; �㭪�� DOS 1Ah
		mov	dx,offset DTA
		int	21h		; ��६����� DTA (�� 㬮�砭�� ��� ᮢ������
					; � ��������� ��ப�� PSP)

; �८�ࠧ����� ᯨ᮪ ��ࠬ��஢ � PSP:81h ᫥���騬 ��ࠧ��:
; ����� ��ࠬ��� �����稢����� �㫥� (ASCIZ-��ப�)
; ���� ��� ��ࠬ��஢ ��������� � �⥪ � ���浪� �����㦥���
; � ��६����� argc �����뢠���� �᫮ ��ࠬ��஢

		mov	cx,-1		; ��� ������ ࠡ��� � ��ப���
		mov	di,offset cmd_line ; ��砫� ��������� ��ப� � ES:DI

find_param:
		mov	al,' '		; �᪠�� ���� ᨬ���,
		repz scasb		; �� ��騩�� �஡����
		dec	di		; DI - ���� ��砫� ��।���� ��ࠬ���
		push	di		; �������� ��� � �⥪
		inc	word ptr argc	; � 㢥����� argc �� ����
		mov	si,di		; SI = DI ��� ᫥���饩 ������� lodsb
scan_params:
		lodsb			; ������ ᫥���騩 ᨬ��� �� ��ࠬ���,
		cmp	al,0Dh	; �᫨ �� 0Dh - �� �� ��᫥���� ��ࠬ���
		je	params_ended	; � �� ���稫��,
		cmp	al,20h	; �᫨ �� 20h - ��� ��ࠬ��� ���稫��,
		jne	scan_params	; �� ����� ���� ��

		dec	si		; SI - ���� ���� ��᫥ ���� ��ࠬ���
		mov	byte ptr [si],0	; ����襬 � ���� 0
		mov	di,si		; DI = SI ��� ������� scasb
		inc	di		; DI - ᫥���騩 ��᫥ ��� ᨬ���
		jmp short find_param	; �த����� ࠧ��� ��������� ��ப�

params_ended:
		dec	si		; SI - ���� ���� ��᫥ ���� ��᫥�����
		mov	byte ptr [si],0	; ��ࠬ��� - ������� � ���� 0


; ����� ��ࠬ��� ���ਭ������� ��� 䠩� ��� ��᪠ ��� ���᪠ 䠩���
; �� �������� 䠩�� �뢮����� �� stdout. �᫨ ��ࠬ��� - �� ��� 䠩��, � 
; �訡�� ����������

		mov	si,word ptr argc ; SI - �᫮ ��⠢���� ��ࠬ��஢
next_file_from_param:
		dec	bp
		dec	bp		; BP - ���� ᫥���饣� ���� ��ࠬ���
	
		dec	si		; 㬥����� �᫮ ��⠢���� ��ࠬ��஢,
		js	no_more_params	; �᫨ ��� �⠫� ����⥫�� - ��

		mov	dx,word ptr [bp] ; DS:DX - ���� ��।���� ��ࠬ���

		mov	ah,4Eh		; �㭪�� DOS 4Eh
		mov	cx,0100111b	; �᪠�� �� 䠩��, �஬� ��४�਩ � ��⮪ ⮬�
		int	21h		; ���� ���� 䠩�
		jc	next_file_from_param ; �᫨ �ந��諠 �訡�� - 䠩�� ���

		call	output_found	; �뢥�� �������� 䠩� �� stdout

find_next:
		mov	ah,4Fh		; �㭪�� DOS 4Fh
		mov	dx,offset DTA	; ���� ��襩 ������ DTA
		int	21h		; ���� ᫥���騩 䠩�
		jc	next_file_from_param	; �᫨ �訡�� - 䠩�� ���稫���
	
		call	output_found	; �뢥�� �������� 䠩� �� stdout

		jmp short find_next	; �த������ ���� 䠩���

no_more_params:
		mov	ax,word ptr argc
		shl	ax,1
		add	sp,ax		; 㤠���� �� �⥪� 2 * argc ���⮢
					; (� ���� ���� ᯨ᮪ ���ᮢ
					; ��ࠬ��஢ ��������� ��ப�)
		ret			; ����� �ணࠬ��


; ��楤�� show_usage
; �뢮��� ���ଠ�� � �ணࠬ��
;
show_usage:
		mov	ah,9		; �㭪�� DOS 09h
		mov	dx,offset usage
		int	21h		; �뢥�� ��ப� �� �࠭
		ret			; ��室 �� ��楤���

; ��楤�� output_found
; �뢮��� � stdout 䠩�, ��� ���ண� ��室���� � ������ DTA

output_found:
		mov	dx,offset DTA+1Eh ; ���� ASCIZ-��ப� � ������ 䠩��
		mov	ax,3D00h	; �㭪�� DOS 3Dh
		int	21h		; ������ 䠩� (al = 0 - ⮫쪮 �� �⥭��),
		jc	skip_file	; �᫨ �訡�� - �� �ண��� ��� 䠩�
		mov	bx,ax		; �����䨪��� 䠩�� - � BX
		mov	di,1		; DI �㤥� �࠭��� �����䨪��� STDOUT
do_output:
		mov	cx,1024	; ࠧ��� ����� ��� �⥭�� 䠩��
		mov	dx,offset DTA+45 ; ���� ��� �⥭��/����� �ᯮ�������� �� 
					; ���殬 DTA
		mov	ah,3Fh	; �㭪�� DOS 3Fh
		int	21h		; ������ 1024 �� 䠩��,
		jc	file_done	; �᫨ �訡�� - ������� 䠩�
		mov	cx,ax		; �᫮ ॠ�쭮 ���⠭��� ���⮢ � CX,
		jcxz	file_done	; �᫨ �� �� ���� - ������� 䠩�

		mov	ah,40h		; �㭪�� DOS 40h
		xchg	bx,di		; BX = 1 - ���ன�⢮ STDOUT
		int	21h		; �뢮� ���⠭���� �᫠ ���⮢ � STDOUT
		xchg	di,bx		; ������ �����䨪��� 䠩�� � BX
		jc	file_done	; �᫨ �訡�� - ������� 䠩�
		jmp short do_output	; �த������ �뢮� 䠩��
file_done:
		mov	ah,3Eh		; �㭪�� DOS 3Eh
		int	21h		; ������� 䠩�
skip_file:
		ret			; ����� ��楤��� output_found

usage		db	'cat.asm v1.0',0Dh,0Ah
		db	'concatenate and print files to stdout',0Dh,0Ah
		db	'usage: cat filename.ext, ...',0Dh,0Ah
		db	'(filenames can contain wildcards)',0Dh,0Ah,'$'

argc		dw	0		; �᫮ ��ࠬ��஢ (������ ���� 0 �� ���� 
					; �ணࠬ��!)

DTA:				; ������� DTA ��稭����� �ࠧ� �� ���殬 䠩��, � 
				; �ࠧ� �� �������� DTA ��稭����� 
				; 1024-����� ���� ��� �⥭�� 䠩��
		end start
