; dirout.asm
; �뢮��� �� �࠭ �� ASCII-ᨬ���� ��� �᪫�祭��,
; �ᯮ���� ��אַ� �뢮� �� �࠭
;
; ���������:
; TASM:
; tasm /m dirout.asm
; tlink /t /x dirout.obj
; MASM:
; ml /c dirout.asm
; link dirout.obj,,NUL,,,
; exe2bin dirout.exe dirout.com
; WASM
; wasm dirout.asm
; wlink file dirout.obj form DOS COM
;

		.model	tiny
		.code
		.386		; �㤥� �ᯮ�짮������ ॣ���� EAX � ������� STOSD
		org	100h	; ��砫� COM-䠩��
start:
		mov	ax,0003h
		int	10h		; �����०�� 3 (���⪠ �࠭�)
		cld			; ��ࠡ�⪠ ��ப � ��אַ� ���ࠢ�����
					; �����⮢�� ������ ��� �뢮�� �� �࠭
		mov	eax,1F201F00h	; ���� ᨬ��� 00 � ��ਡ�⮬ 1Fh,
					; ��⥬ �஡�� (20h) � ��ਡ�⮬ 1Fh
		mov	bx,0F20h	; �஡�� � ��ਡ�⮬ 0Fh
		mov	cx,255		; �᫮ ᨬ����� ����� 1
		mov	di,offset ctable	; ES:DI - ��砫� ⠡����
cloop:
		stosd			; ������� ᨬ��� � �஡�� � ⠡���� ctable
		inc	al		; AL ᮤ�ন� ᫥���騩 ᨬ���

		test	cx,0Fh		; �᫨ CX �� ��⥭ 16,
		jnz	continue_loop	; �த������ 横�,
		push	cx		; ����: ��࠭��� ���祭�� ���稪�
		mov	cx,80-32	; �᫮ ��⠢���� �� ���� ��ப� ᨬ�����
		xchg	ax,bx
		rep	stosw		; ��������� ���⮪ ��ப� �஡�����
					; � ��ਡ�⮬ 0F
		xchg	bx,ax		; ����⠭����� ���祭�� EAX
		pop	cx		; ����⠭����� ���祭�� ���稪�
continue_loop:
		loop	cloop

		stosd			; ������� ��᫥���� (256-�) ᨬ��� � �஡��

; ᮡ�⢥��� �뢮� �� �࠭
		mov	ax,0B800h	; ᥣ����� ���� ����������
		mov	es,ax
		xor	di,di		; DI = 0, ���� ��砫� ���������� � ES:DI
		mov	si,offset ctable ; ���� ⠡���� � DS:SI
		mov	cx,15*80+32	; 15 ��ப �� 80 ᨬ�����, ��᫥���� ��ப� - 32
		rep	movsw		; ᪮��஢��� ⠡���� ctable � �����������
		ret			; �����襭�� COM-䠩��

ctable:				; ����� ��� �뢮�� �� �࠭ ��稭����� �ࠧ�
				; �� ���殬 䠩��. � EXE-䠩�� ⠪�� �����
				; ��।����� � ᥣ���� .data?
	end	start
