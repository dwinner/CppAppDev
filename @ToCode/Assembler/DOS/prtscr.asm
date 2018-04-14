; prtscr.asm
; �ᯥ���� ᮤ�ন��� �࠭� �� �ਭ��
;
; ���������:
; TASM:
;  tasm /m prtscr.asm
;  tlink /t /x prtscr.obj
; MASM:
;  ml /c prtscr.asm
;  link prtscr.obj,,NUL,,,
;  exe2bin prtscr.exe prtscr.com
; WASM:
;  wasm prtscr.asm
;  wlink file prtscr.obj form DOS COM
;

	.model	tiny
	.code
	.186		; ��� ������� push 0B800h
	org	100h	; ��砫� COM-䠫�
start:
	mov	ah,1
	mov	dx,0		; ���� LPT1
	int	17h		; ���樠����஢��� �ਭ��,
	cmp	ah,90h		; �᫨ �ਭ�� �� ��⮢,
	jne	printer_error	; �뤠�� ᮮ�饭�� �� �訡��,
	push	0B800h		; ����:
	pop	ds		; DS = ᥣ���� ���������� � ⥪�⮢�� ०���
	xor	si,si		; SI = 0
	mov	cx,80*40	; CX = �᫮ ᨬ����� �� �࠭�
	cld			; ��ப��� ����樨 ���।
main_loop:
	lodsw			; AL - ᨬ���, AH - ��ਡ��, SI = SI + 2
	mov	ah,0		; AH - ����� �㭪樨
	int	17h		; �뢮� ᨬ���� �� AL �� �ਭ��
	loop	main_loop
	ret			; �������� �ணࠬ��

printer_error:
	mov	dx,offset msg	; ���� ᮮ�饭�� �� �訡�� � DS:DX
	mov	ah,9
	int	21h		; �뢮� ��ப� �� �࠭
	ret

msg	db	'printer on LPT1 busy or offline$'
	end	start

