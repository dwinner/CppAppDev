; ungetch.asm
; ������ � ���� ���������� ������� DIR ⠪, �⮡� ��� �믮������� �ࠧ� ��᫥
; �����襭�� �ணࠬ��
;
; ���������:
; TASM:
;  tasm /m ungetch.asm
;  tlink /t /x ungetch.obj
; MASM:
;  ml /c ungetch.asm
;  link ungetch.obj,,NUL,,,
;  exe2bin ungetch.exe ungetch.com
; WASM:
;  wasm ungetch.asm
;  wlink file ungetch.obj form DOS COM
;

	.model	tiny
	.code
	org	100h	; COM-䠩�
start:
	mov	cl,'d'	; CL = ASCII-��� �㪢� "d"
	call	ungetch
	mov	cl,'i'	; ASCII-��� �㪢� "i"
	call	ungetch
	mov	cl,'r'	; ASCII-��� �㪢� "r"
	call	ungetch
	mov	cl,0Dh	; ��ॢ�� ��ப�
ungetch:
	mov	ah,5	; AH = ����� �㭪樨
	mov	ch,0	; CH = 0 (᪠�-��� �������)
	int	16h	; �������� ᨬ��� � ����
	ret		; �������� �ணࠬ��

	end	start
