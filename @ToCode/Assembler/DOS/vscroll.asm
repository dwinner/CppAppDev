; vscroll.asm
; ������� �ப��⪠ �࠭� �� ���⨪���. ��室 - ������ Esc
;
; ���������:
; TASM:
;  tasm /m vscroll.asm
;  tlink /t /x vscroll.obj
; MASM:
;  ml /c vscroll.asm
;  link vscroll.obj,,NUL,,,
;  exe2bin vscroll.exe vscroll.com
; WASM:
;  wasm vscroll.asm
;  wlink file vscroll.obj form DOS COM
;

	.model	tiny
	.code
	.186		; ��� push 0B400h
	org 100h	; COM-�ணࠬ��
start: 
	push	0B800h
	pop	es 
	xor	si,si		; ES:SI - ��砫� ����������
	mov	di,80*25*2	; ES:DI - ��砫� ��ன ��࠭��� ����������
	mov	cx,di 
	rep movs es:any_label,es:any_label	; ᪮��஢��� ����� 
						; ��࠭��� �� �����
	mov	dx,03D4h 	; ���� 03D4h: ������ CRT
screen_loop:	; 横� �� �࠭��
	mov	cx,80*12*2	; CX = ��砫�� ���� - ���� �।��� �࠭�
line_loop:		; 横� �� ��ப��
	mov	al,0Ch	; ॣ���� 0Ch - ���訩 ���� ��砫쭮�� ����
	mov	ah,ch		; ���� ������ - CH
	out	dx,ax		; �뢮� � ����� 03D4, 03D5
	inc	ax		; ॣ���� 0Dh - ����訩 ���� ��砫쭮�� ����
	mov	ah,cl 	; ���� ������ - CL
	out	dx,ax		; �뢮� � ����� 03D4, 03D5

	mov	bx,15		; ���稪 ����� � ��ப�
	sub	cx,80		; ��६����� ��砫�� ���� �� ��砫� 
				; �।��饩 ��ப� (⠪ ��� �� �������� ����)
pel_loop:	; 横� �� ����� � ��ப�
	call	wait_retrace	; ��������� ���⭮�� 室� ���

	mov	al,8		; ॣ���� 08h - �롮� ����� ����� � ��ࢮ� 
				; ��ப�, � ���ன ��稭����� �뢮� ����ࠦ���� 
	mov	ah,bl		; (����� ����� �� BL)
	out	dx,ax

	dec	bx		; 㬥����� �᫮ �����,
	jge	pel_loop	; �᫨ ����� ��� = ��� - ��ப� �� �� 
				; �ப��⨫��� �� ���� � 横� �� ����� �த��������

	in	al,60h	; ������ ᪠�-��� ��᫥����� ᨬ����,
	cmp	al,81h 	; �᫨ �� 81h (���᪠��� ������ Esc),
	jz	done		; ��� �� �ணࠬ��,

	cmp	cx,0		; �᫨ �� �� �ப��⨫�� 楫� �࠭,
	jge	line_loop	; �த������ 横� �� ��ப��,
	jmp short screen_loop	; ����: �த������ 横� �� �࠭��

done:				; ��室 �� �ணࠬ��
	mov	ax,8		; ������� � ॣ���� CRT 08h
	out	dx,ax		; ���� 00 (�������� ᤢ��� �� ���⨪���),
	add	ax,4		; � ⠪�� 00 � ॣ���� 0Ch
	out	dx,ax
	inc	ax		; � 0Dh (��砫�� ���� ᮢ������ �
	out	dx,ax		; ��砫�� ����������)
	ret

wait_retrace	proc	near
	push	dx
	mov	dx,03DAh 
VRTL1:	in	al,dx		; ���� 03DAh - ॣ���� ISR1
	test	al,8
	jnz	VRTL1		; ��������� ���� ⥪�饣� ���⭮�� 室� ���,
VRTL2:	in	al,dx
	test	al,8
	jz	VRTL2		; � ⥯��� ��砫� ᫥���饣�
	pop	dx
	ret
wait_retrace endp
any_label label byte	; ��⪠ ��� ��८�।������ ᥣ���� � movs
	end	start
