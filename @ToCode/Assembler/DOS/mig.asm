; mig.asm
; 横���᪨ ��४��砥� ᢥ⮤���� ����������
;
; ���������:
; TASM:
; tasm /m mig.asm
; tlink /t /x mig.obj
; MASM:
; ml /c mig.asm
; link mig.obj,,NUL,,,
; exe2bin mig.exe mig.com
; WASM:
; wasm mig.asm
; wlink file mig.obj form DOS COM
;


	.model	tiny
	.code
org	100h		; COM-�ணࠬ��

start	proc near
	mov	ah,2		; �㭪�� 02 ���뢠��� 1Ah
	int	1Ah		; ������� ⥪�饥 �६�
	mov	ch,dh		; ��࠭��� ⥪���� ᥪ㭤� � CH
	mov	cl,0100b	; CL = ���ﭨ� ᢥ⮤����� ����������

main_loop:
	call	change_LEDs	; ��⠭����� ᢥ⮤���� � ᮮ⢥��⢨� � CL

	shl	cl,1		; ᫥���騩 ᢥ⮤���,
	test	cl,1000b	; �᫨ ������ ��諠 � ��� 3,
	jz	continue
	mov	cl,0001b		; ������ �� � ��� 0,
continue:
	mov	ah,1		; �஢����, �� �뫠 �� ����� ������,
	int	16h
	jnz	exit_loop	; �᫨ �� - ��� �� �ணࠬ��
	push	cx
	mov	ah,2		; �㭪�� 02 ���뢠��� 1Ah
	int	1Ah		; ������� ⥪�饥 �६�
	pop	cx
	cmp	ch,dh		; �ࠢ���� ⥪���� ᥪ㭤� � DH � CH
	mov	ch,dh		; ᪮��஢��� �� � �� ��砥,
	je	continue	; �᫨ �� �뫠 � �� ᠬ�� ᥪ㭤� - �� 
; ��४����� ᢥ⮤����,
	jmp short main_loop	; ���� - ��४����� ᢥ⮤����

exit_loop:
	mov	ah,0		; ��室 �� 横�� - �뫠 ����� ������
	int	16h		; ����� ��
	ret			; � �������� �ணࠬ��
start	endp

; ��楤�� change_LEDs
; ��⠭�������� ���ﭨ� ᢥ⮤����� ���������� � ᮮ⢥��⢨� � �᫮� � CL
change_LEDs	proc	near
	call	wait_KBin	; �������� ���������� ���뫪� �������
	mov	al,0EDh
	out	60h,al	; ������� ���������� EDh
	call	wait_KBin	; �������� ���������� ���뫪� ������� 
	mov	al,cl
	out	60h,al	; ����� ���ﭨ� ᢥ⮤�����
	ret
change_LEDs	endp

; ��楤�� wait_KBin
; �������� ���������� ����� ������� ��� ����������
wait_KBin	proc	near
	in	al,64h	; ������ ᫮�� ���ﭨ�
	test	al,0010b	; ��� 1 ࠢ�� 1?
	jnz	wait_KBin	; �᫨ ��� - �����,
	ret			; �᫨ �� - ���
wait_KBin	endp
	end	start
