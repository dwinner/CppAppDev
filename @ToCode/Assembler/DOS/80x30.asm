; 80x30.asm
; ��ॢ���� �࠭ � ⥪�⮢� ०�� 80x30 (ࠧ��� ᨬ����� 8x16)
; (Norton Commander 5.0 � �⫨稥 ��, ���ਬ��, FAR ����⠭�������� ०�� �� 
; ����砭�� �ணࠬ��, �� ��� ����� ��������, �᫨ �।���⥫쭮 ������
; Alt-F9)
;
; ���������:
; TASM:
; tasm /m 80x30.asm
; tlink /t /x 80x30.obj
; MASM:
; ml /c 80x30.asm
; link 80x30.obj,,NUL,,,
; exe2bin 80x30.exe 80x30.com
; WASM:
; wasm 80x30.asm
; wlink file 80x30.obj form DOS COM
;

		.model tiny
		.code
		.186		; ��� ������� outsw
		org	100h	; COM-�ணࠬ��
start:
		mov	ax,3	; ��⠭����� ०�� 03h (80x25),
		int	10h	; �⮡� ⮫쪮 ����� ������訥 ���������

		mov	dx,3CCh	; ���� 3CCh: ॣ���� �뢮�� (MOR) �� �⥭��
		in	al,dx
		mov	dl,0C2h	; ���� 03C2h: ॣ���� �뢮�� (MOR) �� ������
		or	al,0C0h	; ��⠭����� ����୮�� 1, 1 - ��� 480 ��ப
		out	dx,al

		mov	dx,03D4h		; DX = ���� 03D4h: ������ CRT
		mov	si,offset crt480	; DS:SI = ���� ⠡���� ������ ��� CRT
		mov	cx,crt480_l		; CX = �� ࠧ���
		rep outsw	; ��᫠�� �� ��⠭��������� ��ࠬ���� � �����
				; 03D4h � 03D5h

; ����� ���뢠�� ᮮ���� BIOS �� ���������� � �����०���
		push	0040h
		pop	es			; ES = 0040h
		mov	byte ptr es:[84h],29	; 0040h:0084h - �᫮ ��ப

		ret

; ����� ��� ����஫��� CRT � �ଠ� ������ � ����襬 ����, ����� �
; ���襬 - ��� ����� �� ����� ������� outsw
crt480		dw	0C11h	; ॣ���� 11h �ᥣ�� ���� �����뢠�� ����, ⠪ 
				; ��� ��� ��� 7 ࠧ�蠥� ������ � ��㣨� ॣ�����
		dw	0B06h,3E07h,0EA10h,0DF12h,0E715h,0416h
crt480_l = ($-crt480)/2
		end start
