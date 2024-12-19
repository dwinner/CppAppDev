; dllrus.asm
; DLL ��� win32 - ��४���஢騪 �� koi8 � cp1251
;
; ���������
; MASM:
;  ml /c /coff /Cp /D_MASM_ dllrus.asm
;  link dllrus.obj @dllrus.lnk
; ᮤ�ন��� dllrus.lnk:
;	/DLL
;	/entry:start
;	/subsystem:windows
;	/export:koi2win_asm
;	/export:koi2win
;	/export:koi2wins_asm
;	/export:koi2wins
;
; TASM:
;  tasm /m /ml /D_TASM_ dllrus.asm
;  tlink32 -Tpd -c dllrus.obj,,,,dllrus.def
; ᮤ�ন��� 䠩�� dllrus.def:
;	EXPORTS koi2win_asm koi2win koi2wins koi2wins_asm
;
; WASM:
;  wasm dllrus.asm
;  wlink @dllrus.dir
; ᮤ�ন��� 䠩�� dllrus.dir:
;	file dllrus.obj
;	form windows nt DLL
;	exp koi2win_asm,koi2win,koi2wins_asm,koi2wins
;


		.386
		.model flat
; �㭪樨, ��।��塞� � �⮬ DLL
ifdef _MASM_
	 public _koi2win_asm@0	; koi2win_asm - ��४������ ᨬ��� � AL
	 public _koi2win@4	; CHAR WINAPI koi2win(CHAR symbol)
	 public _koi2wins_asm@0	; koi2wins_asm - ��४������ ��ப� � [EAX]
	 public _koi2wins@4	; VOID WINAPI koi2win(CHAR * string)
else
	 public koi2win_asm	; � �� �㭪樨 ��� TASM � WASM
	 public koi2win
	 public koi2wins_asm
	 public koi2wins
endif

		.const
; ⠡��� ��� ��ॢ��� ᨬ���� �� ����஢�� KOI8-r (RFC1489)
; � ����஢�� Windows (cp1251)
; ⠡��� ⮫쪮 ��� ᨬ����� 80h - FFh
; (� ���� ���� �㤥� ������ 80h �� ᨬ����, �८�ࠧ����� ��� �������� xlat
; � ᭮�� �������� 80h)
k2w_tbl		db	16 dup(0)	; ᨬ����, �� �������騥 � cp1251, 
		db	16 dup(0)	; ��४��������� � 80h
		db	00h, 00h, 00h, 38h, 00h, 00h, 00h, 00h
		db	00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
		db	00h, 00h, 00h, 28h, 00h, 00h, 00h, 00h
		db	00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
		db	7Eh, 60h, 61h, 76h, 64h, 65h, 74h, 63h
		db	75h, 68h, 69h, 6Ah, 6Bh, 6Ch, 6Dh, 6Eh
		db	6Fh, 7Fh, 70h, 71h, 72h, 73h, 66h, 62h
		db	7Ch, 7Bh, 67h, 78h, 7Dh, 79h, 77h, 7Ah
		db	5Eh, 40h, 41h, 56h, 44h, 45h, 54h, 43h
		db	55h, 48h, 49h, 4Ah, 4Bh, 4Ch, 4Dh, 4Eh
		db	4Fh, 5Fh, 50h, 51h, 52h, 53h, 46h, 42h
		db	5Ch, 5Bh, 47h, 58h, 5Dh, 59h, 57h, 5Ah

		.code
; ��楤�� DLLEntry. ����砥� �� ��ࠬ��� - �����䨪���, ��稭� �맮��
; � ��१�ࢨ஢���� ��ࠬ���. ��� �� �㦥� �� ���� �� ���
_start@12:
		mov	al,1	; ���� ������ ���㫥��� �᫮ � EAX
		ret	12

; ��楤�� BYTE WINAPI koi2win(BYTE symbol) -
; �窠 �室� ��� �맮�� �� C
ifdef _MASM_
_koi2win@4	proc
else
 koi2win	proc
endif
		pop	ecx	; ����� ���� � ECX
		pop	eax	; ��ࠬ��� � ECX (⥯��� �⥪ ��饭 �� ��ࠬ��஢!)
		push	ecx	; ����� ���� ������ � �⥪ ��� RET
; ����� ��� ������� RET - �ࠢ����� ��।����� ᫥���饩 ��楤��
ifdef _MASM_
_koi2win@4	endp
else
 koi2win	endp
endif
; ��楤�� koi2win_asm
; �窠 �室� ��� �맮�� �� ��ᥬ������ �ணࠬ�
; ����: AL - ��� ᨬ���� � KOI
; �뢮�: AL - ��� �⮣� �� ᨬ���� � WIN
ifdef _MASM_
_koi2win_asm@0	proc
else
 koi2win_asm	proc
endif
		test	al,80h		; �᫨ ᨬ��� ����� 80h (���訩 ��� 0),
		jz	dont_decode		; �� ��४���஢���,
		push	ebx			; ���� - 
		mov	ebx,offset k2w_tbl
		sub	al,80h		; ������ 80h,
		xlat				; ��४���஢���
		add	al,80h		; � �ਡ����� 80h,
		pop	ebx
dont_decode:
		ret				; ���
ifdef _MASM_
_koi2win_asm@0	endp
else
 koi2win_asm	endp
endif

; VOID koi2wins(BYTE * koistring) -
; �窠 �室� ��� �맮�� �� C
ifdef _MASM_
_koi2wins@4	proc
else
 koi2wins	proc
endif
		pop	ecx	; ���� ������ �� �⥪�
		pop	eax	; ��ࠬ��� � EAX
		push	ecx	; ���� ������ � �⥪
ifdef _MASM_
_koi2wins@4	endp
else
 koi2wins	endp
endif
; �窠 �室� ��� �맮�� �� ��ᥬ����:
; ����: EAX - ���� ��ப�, ������ ���� �८�ࠧ����� �� KOI � WIN
; 
ifdef _MASM_
_koi2wins_asm@0 proc
else
 koi2wins_asm	proc
endif
		push	esi	; ��࠭��� ॣ�����, ����� ����� ��������
		push	edi
		push	ebx
		mov	esi,eax	; �ਥ���� ��ப
		mov	edi,eax	; � ���筨� ᮢ������
		mov	ebx,offset k2w_tbl
decode_string:
		lodsb				; ������ ����,
		test	al,80h		; �᫨ ���訩 ��� 0,
		jz	dont_decode2	; �� ��४���஢���,
		sub	al,80h		; ���� - ������ 80h,
		xlat				; ��४���஢���
		add	al,80h		; � �������� 80h
dont_decode2:
		stosb			; ������ ���� �� ����,
		test	al,al		; �᫨ ���� - �� ����,
		jnz	decode_string	; �த������
		pop	ebx
		pop	edi
		pop	esi
		ret
ifdef _MASM_
_koi2wins_asm@0 endp
else
 koi2wins_asm	endp
endif
		end	_start@12
