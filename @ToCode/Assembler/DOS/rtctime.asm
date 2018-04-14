; rtctime.asm
; �뢮� �� �࠭ ⥪�饩 ���� � �६��� �� RTC
;
; ���������:
; TASM:
;  tasm /m rtctime.asm
;  tlink /t /x rtctime.obj
; MASM:
;  ml /c rtctime.asm
;  link rtctime.obj,,NUL,,,
;  exe2bin rtctime.exe rtctime.com
; WASM:
;  wasm rtctime.asm
;  wlink file rtctime.obj form DOS COM
;


	.model	tiny
	.code
	.186		; ��� shr al,4
	org	100h	; COM-�ணࠬ��
start:
	mov	al,0Bh	; CMOS 0Bh - �ࠢ���騩 ॣ���� B
	out	70h,al	; ���� 70h - ������ CMOS
	in	al,71h	; ���� 71h - ����� CMOS
	and	al,11111011b	; ���㫨�� ��� 2 (�ଠ �ᥫ - BCD)
	out	71h,al		; � ������� ���⭮

	mov	al,32h		; CMOS 32h - ��� ���訥 ���� ����
	call	print_cmos		; �뢮� �� �࠭
	mov	al,9			; CMOS 09h - ��� ����訥 ���� ����
	call	print_cmos
	mov	al,'-'		; �����
	int	29h			; �뢮� �� �࠭
	mov	al,8			; CMOS 08h - ⥪�騩 �����
	call	print_cmos
	mov	al,'-'		; �� ���� �����
	int	29h
	mov	al,7			; CMOS 07h - ����
	call	print_cmos
	mov	al,' '		; �஡��
	int	29h
	mov	al,4			; CMOS 04h - ��
	call	print_cmos
	mov	al,'h'		; �㪢� "h"
	int	29h
	mov	al,' '		; �஡��
	int	29h
	mov	al,2		; CMOS 02h - �����
	call	print_cmos
	mov	al,':'		; �����稥
	int	29h
	mov	al,0h		; CMOS 00h - ᥪ㭤�
	call	print_cmos
	ret

; ��楤�� print_cmos
; �뢮��� �� �࠭ ᮤ�ন��� �祩�� CMOS � ����஬ � AL
; ��⠥�, �� �᫮, �⠥��� �� CMOS, ��室���� � �ଠ� BCD
print_cmos proc near
	out	70h,al	; ��᫠�� AL � ������� ���� CMOS
	in	al,71h	; ������ �����
	push	ax
	shr	al,4		; �뤥���� ���訥 ���� ���
	add	al,'0'	; �������� ASCII-��� ���� 0
	int	29h		; �뢥�� �� �࠭
	pop	ax
	and	al,0Fh	; �뤥���� ����訥 ���� ���
	add	al,30h	; �������� ASCII-��� ���� 0
	int	29h		; �뢥�� �� �࠭
	ret
print_cmos endp
	end	start
