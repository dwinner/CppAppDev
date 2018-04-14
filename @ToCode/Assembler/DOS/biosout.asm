; biosout.asm
; �뢮��� �� �࠭ �� ASCII-ᨬ���� ��� �᪫�祭��
;
; ���������:
; TASM:
; tasm /m biosout.asm
; tlink /t /x biosout.obj
; MASM:
; ml /c biosout.asm
; link biosout.obj,,NUL,,,
; exe2bin biosout.exe biosout.com
; WASM
; wasm biosout.asm
; wlink file biosout.obj form DOS COM
;

		.model	tiny
		.code
		org	100h	; ��砫� COM-䠩��
start:
		mov	ax,0003h
		int	10h	; �����०�� 3 (���⪠ �࠭� � ��⠭���� ����� � 0,0)
		mov	dx,0	; DH � DL ���� �ᯮ�짮������ ��� �࠭���� ���������
				; �����. ��砫쭮� ��������� - 0,0
		mov	si,256	; SI �㤥� ���稪�� 横��
		mov	al,0	; ���� ᨬ��� - � ����� 00h
		mov	ah,9	; ����� ������㭪樨 "�뢮� ᨬ���� � ��ਡ�⮬"
		mov	cx,1	; �뢮����� ���� ᨬ��� �� ࠧ
		mov	bl,00011111b	; ��ਡ�� ᨬ���� - ���� �� ᨭ��
cloop:
		int	10h	; �뢥�� ᨬ��� �� �࠭

		push	ax	; ���࠭��� ⥪�騩 ᨬ��� � ����� �㭪樨
		mov	ah,2	; ����� ������㭪樨 2 - �������� ��������� �����
		inc	dl	; �������� ⥪�騩 �⮫��� �� 1
		int	10h	; ��६����� �����
		mov	ax,0920h ; AH = 09, AL = 20h (ASCII-��� �஡���)
		int	10h	; �뢥�� �஡��
		mov	ah,2	; ����� ������㭪樨 2
		inc	dl	; �������� �⮫��� �� 1
		int	10h	; ��६����� �����
		pop	ax	; ����⠭����� ����� �㭪樨 � ah � ⥪�騩 ᨬ��� � al
	
		inc	al	; �������� AL �� 1 - ᫥���騩 ᨬ���
		test	al,0Fh	; �᫨ AL �� ��⥭ 16,
		jnz	continue_loop ; �த������ 横�,

		push	ax	; ���� ��࠭��� ����� �㭪樨 � ⥪�騩 ᨬ���
		mov	ah,2	; ����� ������㭪樨 2
		inc	dh	; �������� ����� ��ப� �� 1
		mov	dl,0	; �⮫��� = 0
		int	10h	; ��⠭����� ����� �� ��砫� ᫥���饩 ��ப�
		pop	ax	; ����⠭����� ����� ������㭪樨 � ⥪�騩 ᨬ���

continue_loop:
		dec	si	; �������� SI �� 1, �᫨ �� �� �⠫ �㫥� - �த������
		jnz	cloop	; CX �ᯮ������ ����� 横��, ⠪ �� �����
				; �ᯮ�짮���� ������� LOOP ��� ��� �࣠����樨
        
		ret		; �����襭�� COM-䠩��
		end	start
