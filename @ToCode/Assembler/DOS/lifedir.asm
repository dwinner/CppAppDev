; lifedir.asm
; ��� "�����" �� ���� 320x200, �ᯮ������ �뢮� �� �࠭ �।�⢠�� BIOS
;
; ���������:
; TASM:
; tasm /m lifedir.asm
; tlink /x lifedir.obj
; MASM:
; ml /c lifedir.asm
; link lifedir.obj
; WASM:
; wasm lifedir.asm
; wlink file lifedir.obj form DOS
;

	.model small
	.stack	100h	; �� ������� �⥪� - ��� EXE-�ணࠬ�
	.code
	.186			; ��� ������ shl al,4 � shr al,4
start:
	push	FAR_BSS	; ᥣ����� ���� ���� � DS
	pop	ds

;
; ���������� ���ᨢ� �祥� �ᥢ����砩�묨 ���祭�ﬨ
;
	xor	ax,ax
	int	1Ah		; �㭪�� AH = 0 INT 1Ah: ������� ⥪�饥 �६�
; DX ⥯��� ᮤ�ন� �᫮ ᥪ㭤, ��襤��
; � ������ ����祭�� ��������, ���஥
; �ᯮ������ ��� ��砫쭮� ���祭�� �������
; ��砩��� �ᥫ
	mov	di,320*200+1	; ���ᨬ���� ����� �祩��
fill_buffer:
	imul	dx,4E35h	; ���⮩ ������� ��砩��� �ᥫ
	inc	dx		; �� ���� ������
	mov	ax,dx		; ⥪�饥 ��砩��� �᫮ ��������� � AX
	shr	ax,15		; �� ���� ��⠢����� ⮫쪮 ���� ���,
	mov	byte ptr [di],al	; � � ���ᨢ ��������� 00, �᫨ �祩��
; ����, � 01, �᫨ ��ᥫ���
	dec	di		; ᫥����� �祩��
	jnz	fill_buffer	; �த������ 横�, �᫨ DI �� �⠫ ࠢ�� ���

	mov	ax,0013h	; ����᪨� ०�� 320x200, 256 梥⮢
	int	10h

; �᭮���� 横�

new_cycle:

; ��� 1: ��� ������ �祩�� �������� �᫮ �ᥤ�� � �����뢠���� � ���訥 4 
; ��� �⮩ �祩��

	mov	di,320*200+1	; ���ᨬ���� ����� �祩��
step_1:
	mov	al,byte ptr [di+1]	; � AL �������� �㬬� 
	add	al,byte ptr [di-1]	; ���祭�� ���쬨 �ᥤ��� �祥�,
	add	al,byte ptr [di+319]	; �� �⮬ � ������ ����� 
	add	al,byte ptr [di-319]	; ���� ������������� �᫮ 
	add	al,byte ptr [di+320]	; �ᥤ��
	add	al,byte ptr [di-320]
	add	al,byte ptr [di+321]
	add	al,byte ptr [di-321]
	shl	al,4			; ⥯��� ���訥 ���� ��� AL - �᫮
					; �ᥤ�� ⥪�饩 �祩��
	or	byte ptr [di],al	; �������� �� � ���訥 ���� ��� 
					; ⥪�饩 �祩��
	dec	di		; ᫥����� �祩��
	jnz	step_1	; �த������ 横�, �᫨ DI �� �⠫ ࠢ�� ���


; ��� 2: ��������� ���ﭨ� �祥� � ᮮ⢥��⢨� � ����祭�묨 � 蠣� 1 
; ���祭�ﬨ �᫠ �ᥤ��


	mov	di,320*200+1	; ���ᨬ���� ����� �祩��
flip_cycle:
	mov	al,byte ptr [di]	; ����� �祩�� �� ���ᨢ�
	shr	al,4			; AL = �᫮ �ᥤ��
	cmp	al,3			; �᫨ �᫮ �ᥤ�� = 3,
	je	birth			; �祩�� ��ᥫ����,
	cmp	al,2			; �᫨ �᫮ �ᥤ�� = 2,
	je	f_c_continue	; �祩�� �� ���������,
	mov	byte ptr [di],0	; ���� - �祩�� ��������
	jmp	short f_c_continue
birth:
	mov	byte ptr [di],1
f_c_continue:
	and	byte ptr [di],0Fh	; ���㫨�� �᫮ �ᥤ�� � ����� ���� 
					; �祩��
	dec	di			; ᫥����� �祩��
	jnz	flip_cycle

;
; �뢮� ���ᨢ� �� �࠭ ���� ����஢����� � �����������

	push	0A000h			; ���� ����������
	pop	es			; � ES
	mov	cx,320*200		; �᫮ �祥�
	mov	di,cx			; ���⮢� ���� � ���������� 320*200
	mov	si,cx			; ���⮢� ���� � ���ᨢ� -
	inc	si			; 320*200+1
	rep movsb			; �믮����� ����஢����

	mov	ah,1			; �᫨ �� ����� ������
	int	16h
	jz	new_cycle		; ᫥���騩 蠣 �����

	mov	ax,0003h		; ����: ����⠭����� ⥪�⮢� ०��
	int	10h
	mov	ax,4C00h		; � �������� �ணࠬ��
	int	21h

	.fardata?		; ᥣ���� ���쭨� �����樠����஢����� ������
	db	320*200+1 dup(?)	; ᮤ�ন� ���ᨢ �祥�
	end start
