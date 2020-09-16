; tsr.asm
; �ਬ�� ���ᨢ��� १����⭮� �ணࠬ��
; ����頥� 㤠����� 䠩��� �� ��᪥, 㪠������ � ��������� ��ப�, �ᥬ 
; �ணࠬ���, �ᯮ����騬 �।�⢠ DOS
;
; ���������:
; TASM:
;  tasm /m tsr.asm
;  tlink /t /x tsr.obj
; MASM:
;  ml /c tsr.asm
;  link tsr.obj,,NUL,,,
;  exe2bin tsr.exe tsr.com
; WASM:
;  wasm tsr.asm
;  wlink file tsr.obj form DOS COM


	.model	tiny
	.code
	org	2Ch
envseg	dw	?	; ᥣ����� ���� ����� ���㦥��� DOS
	org	80h
cmd_len	db	?	; ����� ��������� ��ப�
cmd_line	db	?	; ��砫� ��������� ��ப�
	org	100h		; COM-�ணࠬ��

start:
old_int21h:
	jmp short initialize ; �� ������� �������� 2 ����, ⠪ ��
	dw	0		; ����� � �⨬� ���� ���⠬� ����稬
				; old_int21h dd ?
int21h_handler	proc	far	; ��ࠡ��稪 ���뢠��� 21h
	pushf			; ��࠭��� 䫠��
	cmp	ah,41h	; �᫨ �맢��� �㭪�� 41h (㤠���� 
	je	fn41h	; 䠩�)
	cmp	ax,7141h ; ��� 7141h (㤠���� 䠩� � ������ ������)
	je	fn41h		; ����� ��� ��ࠡ��稪,
	jmp short not_fn41h	; ���� - ��।��� �ࠢ����� 
				; �।��饬� ��ࠡ��稪�
fn41h:
	push	ax		; ��࠭��� �������㥬�
	push	bx		; ॣ�����
	mov	bx,dx
	cmp	byte ptr ds:[bx+1],':' ; �᫨ ��ன ᨬ���
				; ASCIZ-��ப�, ��।����� INT 21h,
				; �����稥 - ���� ᨬ��� ������ ���� 
				; ������ ��᪠,
	je	full_spec
	mov	ah,19h	; ����: 
	int	21h		; �㭪�� DOS 19h - ��।����� ⥪�騩 
				; ���
	add	al,'A'	; �८�ࠧ����� ����� ��᪠ � ��������� 
			; �㪢�
	jmp short compare	; ��३� � �ࠢ�����
full_spec:
	mov	al,byte ptr [bx] ; AL = ��� ��᪠ �� ASCIZ-��ப�
	and	al,11011111b ; �८�ࠧ����� � ��������� �㪢�
compare:
	cmp	al,byte ptr cs:cmd_line[1] ; �᫨ ��᪨
	je	access_denied	; ᮢ������ - ������� �����,
	pop	bx			; ����: ����⠭�����
	pop	ax			; ॣ�����
not_fn41h:
	popf				; � 䫠��
	jmp	dword ptr cs:old_int21h	; � ��।��� �ࠢ����� 
					; �।��饬� ��ࠡ��稪� INT 21h
access_denied:
	pop	bx		; ����⠭����� ॣ�����
	pop	ax
	popf
	push	bp
	mov	bp,sp
	or	word ptr [bp+6],1	; ��⠭����� 䫠� ��७��
			; (��� 0) � ॣ���� 䫠���, ����� �����⨫� 
			; ������� INT � �⥪ ��। ���ᮬ ������
	pop	bp
	mov	ax,5		; �������� ��� �訡��
				; "����� ����饭"
	iret			; �������� � �ணࠬ��
int21h_handler	endp

initialize	proc near
	cmp	byte ptr cmd_len,3 ; �஢���� ࠧ��� ��������� ��ப�
	jne	not_install	; (������ ���� 3 - �஡��, ���, �����稥)
	cmp	byte ptr cmd_line[2],':' ; �஢���� ��⨩ ᨬ��� 
	jne	not_install	; ��������� ��ப� (������ ���� �����稥)
	mov	al,byte ptr cmd_line[1]
	and	al,11011111b	; �८�ࠧ����� ��ன
				; ᨬ��� � ��������� �㪢�
	cmp	al,'A'		; �஢����, �� �� ��
	jb	not_install		; ����� 'A' � �� �����
	cmp	al,'Z'		; 'Z'
	ja	not_install		; �᫨ ��� ���� �� ��� �᫮���
	; �� �믮������ - �뤠�� ���ଠ�� � �ணࠬ�� � ���,
	; ���� - ����� ��楤��� ���樠����樨

	mov	ax,3521h		; AH = 35h, AL = ����� ���뢠���
	int	21h			; ������� ���� ��ࠡ��稪� INT 21h
	mov	word ptr old_int21h,bx	; � �������� ��� � old_int21h
	mov	word ptr old_int21h+2,es

	mov	ax,2521h		; AH = 25h, AL = ����� ���뢠���
	mov	dx,offset int21h_handler ; DS:DX - ���� ��襣� 
					; ��ࠡ��稪�
	int	21h			; ��⠭����� ��ࠡ��稪 INT 21h

	mov	ah,49h		; AH = 49h
	mov	es,word ptr envseg ; ES = ᥣ����� ���� ����� � ��襩 
				; ������ ���㦥��� DOS
	int	21h			; �᢮������ ������ ��-��� ���㦥���

	mov	dx,offset initialize ; DX - ���� ��ࢮ�� ���� �� ���殬
					; १����⭮� ��� �ணࠬ��
	int	27h			; �������� �믮������, ��⠢��� 
					; १����⮬

not_install:
	mov	ah,9			; AH = 09h
	mov	dx,offset usage	; DS:DX = ���� ��ப� � ���ଠ樥� �� 
					; �ᯮ�짮����� �ணࠬ��
	int	21h			; �뢮� ��ப� �� �࠭
	ret				; ��ଠ�쭮� �����襭�� �ணࠬ��

; ⥪��, ����� �뤠�� �ணࠬ�� �� ����᪥ � ���ࠢ��쭮� ��������� ��ப��:
usage	db	'Usage: tsr.com D:',0Dh,0Ah
	db	'Denies delete on drive D:',0Dh,0Ah
	db	'$'

initialize	endp
	end	start
