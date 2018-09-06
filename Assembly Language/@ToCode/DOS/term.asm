; term.asm
; ����� �ନ���쭠� �ணࠬ�� ��� ������ �� COM2. ��室 �� alt-X
;
; ���������:
; TASM:
;  tasm /m term.asm
;  tlink /t /x term.obj
; MASM:
;  ml /c term.asm
;  link term.obj,,NUL,,,
;  exe2bin term.exe term.com
; WASM:
;  wasm term.asm
;  wlink file term.obj form DOS COM
;


	.model	tiny
	.code
	org 100h	; ��砫� COM-䠩��
start:
	mov	ah,0			; ���樠����஢��� ����
	mov	al,11100011b	; 9600/8n1
	mov	dx,1			; ���� COM2
	int	14h

main_loop:
	mov	ah,2
	int	14h		; ������� ���� �� ������
	test	ah,ah		; �᫨ ��-����� ����祭�,
	jnz	no_input
	int	29h		; �뢥�� ��� �� �࠭
no_input:			; ����:
	mov	ah,1
	int	16h		; �஢����, �뫠 �� ����� ������,
	jz	main_loop	; �᫨ ��:
	mov	ah,8
	int	21h		; ����� �� ��� (��� �⮡ࠦ���� �� �࠭�),
	test	al,al		; �᫨ �� �����७�� ASCII-���,
	jnz	send_char	; ��३� � ���뫪� ��� � �����,
	int	21h		; ���� - ������� ���७�� ASCII-���,
	cmp	al,2Dh	; �᫨ �� alt-X,
	jne	send_char
	ret			; �������� �ணࠬ��
send_char:
	mov	ah,1
	int	14h		; ��᫠�� �������� ᨬ��� � �����
	jmp short main_loop	; �த������ �᭮���� 横�

	end start
