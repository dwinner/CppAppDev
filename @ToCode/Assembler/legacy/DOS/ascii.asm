; ascii.asm
; �������⭠� �ணࠬ�� ��� ��ᬮ�� � ����� ASCII-ᨬ�����
; HCI:
;	Alt-A - ��⨢��� �ணࠬ��
;	������ �ࠢ����� ����஬ - �롮� ᨬ����
;	Enter - ��室 �� �ணࠬ�� � ������ ᨬ����
;	Esc - ��室 �� �ணࠬ�� ��� ����� ᨬ����
; API:
;	�ணࠬ�� �������� ����� ᢮������ �㭪�� ���뢠��� 2Dh
;	� ᮮ⢥��⢨� � ᯥ�䨪�樥� AMIS 3.6
;	�����ন������ �㭪樨 AMIS 00h, 02h, 03h, 04h � 05h
;	��ࠡ��稪� ���뢠��� ����஥�� � ᮮ⢥��⢨� � IMB ISP
;
; ���������:
; TASM:
; tasm /m ascii.asm
; tlink /t /x ascii.obj
; MASM:
; ml /c ascii.asm
; link ascii.obj,,NUL,,,
; exe2bin ascii.exe ascii.com
; WASM:
; wasm ascii.asm
; wlink file ascii.obj form DOS COM

; ���� ���孥�� ������ 㣫� ���� (23-� ������ � ���쥩 ��ப�)
START_POSITION	equ (80*2+23)*2

		.model	tiny
		.code
		.186			; ��� ᤢ���� � ������ pusha/popa
		org	2Ch
envseg		dw	?		; ᥣ����� ���� ���㦥��� DOS
		org	100h		; ��砫� COM-�ணࠬ��

start:
		jmp	initialize	; ���室 �� ���樠���������� ����

hw_reset9:	retf			; ISP: ��������� hw_reset
;
; ��ࠡ��稪 ���뢠��� 09h (IRQ1)
;
int09h_handler	proc	far
		jmp short actual_int09h_handler; ISP: �ய����� ����
old_int09h	dd	?			; ISP: ���� ��ࠡ��稪
		dw	424Bh			; ISP: ᨣ�����
		db	00h			; ISP: ����� ��ࠡ��稪
		jmp short hw_reset9		; ISP: ������� jmp �� hw_reset
		db	7 dup (0)		; ISP: ��१�ࢨ஢���
actual_int09h_handler:	; ��砫� ��ࠡ��稪� INT 09h

; ���砫� �맮��� �।��騩 ��ࠡ��稪, �⮡� ���� BIOS ����������� 
; ��ࠡ���� ���뢠��� �, �᫨ �� ���� ����⨥ ������, �������� ��� � 
; ���������� ����, ⠪ ��� �� ���� �� 㬥�� ࠡ���� � ���⠬� ���������� � 
; ����஫��� ���뢠���
		pushf
		call	dword ptr cs:old_int09h

; �� �⮬� ����� ��ࠡ��稪 INT 2Dh ������ ��� ������� IRET ��� �����⨢�樨 
; �ணࠬ��
disable_point	label byte

		pusha		; �� �����⭮� ���뢠��� - ����
		push	ds	; ��࠭��� �� ॣ�����
		push	es
		cld		; ��� ������ ��ப���� ��ࠡ�⪨

		push	0B800h
		pop	es	; ES = ᥣ����� ���� ����������
		push	0040h
		pop	ds	; DS = ᥣ����� ���� ������ ������ BIOS
		mov	di,word ptr ds:001Ah	; ���� ������ ���� 
					; ����������
		cmp	di,word ptr ds:001Ch ; �᫨ �� ࠢ�� ����� 墮��,
		je	exit_09h_handler	; ���� ����, � ��� ������ ��祣�
		; (���ਬ��, �᫨ ���뢠��� ��諮 �� ���᪠��� ������),

		mov	ax,word ptr [di]	; ����: ����� ᨬ��� �� ������ 
						; ����

		cmp	byte ptr cs:we_are_active,0 ; �᫨ �ணࠬ�� 
						; 㦥 ��⨢�஢��� - 
		jne	already_active ; ��३� � ��ࠡ�⪥ ��५�� � �. �.

		cmp	ah,1Eh		; �᫨ ���⠭��� ������ �� A
		jne	exit_09h_handler	; (᪠� ��� 1Eh) - ���,

		mov	al,byte ptr ds:0017h ; ����: ����� ���� 
						; ���ﭨ� ����������,
		test	al,08h		; �᫨ �� ����� �� Alt,
		jz	exit_09h_handler	; ���,

		mov	word ptr ds:001Ch,di ; ����: ��⠭����� ����
					; ������ � 墮�� ���� ��������묨,
					; ����⨢ ��� ⥬ ᠬ� ��� ���⮩

		call	save_screen	; ��࠭��� ������� �࠭�, ������ 
					; ���஥� �ᯫ뢠�饥 ����
		push	cs
		pop	ds		; DS = ��� ᥣ����� ����
		call	display_all	; �뢥�� �� �࠭ ���� �ணࠬ��

		mov	byte ptr we_are_active,1 ; ��⠭����� 䫠�
		jmp short exit_09h_handler ; � ��� �� ��ࠡ��稪�

; � ��।����� �ࠢ�����, �᫨ �ணࠬ�� 㦥 ��⨢�஢���.
; �� �⮬ ES = B800h, DS = 0040h, DI = ���� ������ ���� ����������,
; AX = ᨬ��� �� ������ ����
already_active:
		mov	word ptr ds:001Ch,di ; ��⠭����� ����
					; ������ � 墮�� ���� ��������묨,
					; ����⨢ ��� ⥬ ᠬ� ��� ���⮩
		push	cs
		pop	ds		; DS = ��� ᥣ����� ����

		mov	al,ah	; ������� cmp al, ? ���� ������ cmp ah, ?
		mov	bh,byte ptr current_char ; ����� �뤥������� � 
				; ����� ������ ASCII-ᨬ����,
		cmp	al,48h	; �᫨ ����� ��५�� ����� (᪠�-��� 48h),
		jne	not_up
		sub	bh,16		; 㬥����� ����� ᨬ���� �� 16,
not_up:		cmp	al,50h		; �᫨ ����� ��५�� ���� (᪠�-��� 50h),
		jne	not_down
		add	bh,16		; 㢥����� ����� ᨬ���� �� 16,
not_down:	cmp	al,4Bh		; �᫨ ����� ��५�� �����,
		jne	not_left
		dec	bh		; 㬥����� ����� ᨬ���� �� 1,
not_left:	cmp	al,4Dh		; �᫨ ����� ��५�� ��ࠢ�,
		jne 	not_right
		inc	bh		; 㢥����� ����� ᨬ���� �� 1,
not_right:	cmp	al,1Ch		; �᫨ ����� Enter (᪠�-��� 1Ch),
		je	enter_pressed	; ��३� � ��� ��ࠡ��稪�
		dec	al		; �᫨ �� ����� ������ Esc (᪠�-��� 1),
		jnz	exit_with_display ; ��� �� ��ࠡ��稪�, ��⠢�� 
					; ���� ��襩 �ணࠬ�� �� �࠭�,
exit_after_enter:			; ����:
		call	restore_screen	; ���� ��� ���� � �࠭�,
		mov	byte ptr we_are_active,0 ; ���㫨�� 䫠� 
						; ��⨢����,
		jmp	short exit_09h_handler	; ��� �� ��ࠡ��稪�
 
exit_with_display:			; ��室 � ��࠭����� ���� (��᫥ 
					; ������ ��५��)
		mov	byte ptr current_char,bh ; ������� ����� 
					; ���祭�� ⥪�饣� ᨬ����
		call	display_all	; ����ᮢ��� ����

exit_09h_handler:		; ��室 �� ��ࠡ��稪� INT 09h
		pop	es
		pop	ds	; ����⠭����� ॣ�����
		popa
		iret		; � �������� � ��ࢠ���� �ணࠬ��

we_are_active	db	0	; 䫠� ��⨢����: ࠢ�� 1, �᫨
				; �ணࠬ�� ��⨢��
current_char	db	37h	; ����� ASCII-ᨬ����, �뤥������� � 
				; ����� ������

; � ��।����� �ࠢ�����, �᫨ � ��⨢��� ���ﭨ� �뫠 ����� Enter
enter_pressed:
		mov	ah,05h		; �㭪�� 05h
		mov	ch,0		; CH = 0
		mov	cl,byte ptr current_char ; CL = ASCII-���
		int	16h		; �������� ᨬ��� � ���� ����������
		jmp short exit_after_enter ; ��� �� ��ࠡ��稪�, 
					; ��ॢ ����

; ��楤�� save_screen
; ��࠭�� � ���� screen_buffer ᮤ�ন��� ������ �࠭�, ������ ���஥� 
; ��� ����

save_screen	proc	near
		mov	si,START_POSITION
		push	0B800h		; DS:SI - ��砫� �⮩ ������ � 
		pop	ds		; ����������
		push	es
		push	cs
		pop	es
		mov	di,offset screen_buffer	; ES:DI - ��砫� ���� � 
						; �ணࠬ��
		mov	dx,18		; DX = ���稪 ��ப
save_screen_loop:
		mov	cx,33		; CX = ���稪 ᨬ����� � ��ப�
		rep movsw		; ᪮��஢��� ��ப� � �࠭� � ����
		add	si,(80-33)*2 ; 㢥����� SI �� ��砫� ᫥���饩 
					; ��ப�
		dec	dx		; 㬥����� ���稪 ��ப,
		jnz	save_screen_loop ; �᫨ �� �� ���� - �த������ 
		pop	es		; 横�
		ret
save_screen	endp

; ��楤�� restore_screen
; ����⠭�������� ᮤ�ন��� ������ �࠭�, ������ ����뢠�� ��� 
; �ᯫ뢠�饥 ���� ����묨 �� ���� screen_buffer

restore_screen	proc	near
						; ES:DI - ��砫� ������
		mov	di,START_POSITION	; � ����������
		mov	si,offset screen_buffer	; DS:SI - ��砫� ����
		mov	dx,18			; ���稪 ��ப
restore_screen_loop:
		mov	cx,33		; ���稪 ᨬ����� � ��ப�
		rep movsw		; ᪮��஢��� ��ப�
		add	di,(80-33)*2 ; 㢥����� DI �� ��砫� ᫥���饩 
					; ��ப�
		dec	dx		; 㬥����� ���稪 ��ப,
		jnz	restore_screen_loop ; �᫨ �� �� ���� - �த������
		ret
restore_screen	endp


; ��楤�� display_all
; �뢮��� �� �࠭ ⥪�饥 ���ﭨ� �ᯫ뢠�饣� ���� ��襩 �ணࠬ��

display_all	proc	near

; 蠣 1: ������ ���祭�� ⥪�饣� �뤥������� ���� � ������ ��ப� ����
		mov	al,byte ptr current_char ; AL = ��࠭�� ����
		push	ax
		shr	al,4			; ���訥 ���� ����
		cmp	al,10			; �� �������,
		sbb	al,69h			; �८�ࠧ��騥 ���� � AL
		das				; � �� ASCII-��� (0 - 9, A - F)
		mov	byte ptr hex_byte1,al ; ������� ᨬ��� �� ��� 
						; ���� � ������ ��ப�
		pop	ax
		and	al,0Fh			; ����訥 ���� ���
		cmp	al,10			; � �� �८�ࠧ������
		sbb	al,69h
		das
		mov	byte ptr hex_byte2,al	; ������� ������� ����

; 蠣 2: �뢮� �� �࠭ ����. �뫮 �� ��� �࠭��� ��� ��� ���ᨢ � �뢮���� 
; �������� movsw, ��� � ���� � ��楤�� restore_screen, �� ⠪�� ���ᨢ ������ 
; �� 1190 ���⮢ � १����⭮� ���. ��� �⮩ ��� ��楤��� display_all - �ᥣ� 
; 69 ���⮢.
; 蠣 2.1: �뢮� ��ࢮ� ��ப�
		mov	ah,1Fh			; ��ਡ�� ���� �� ᨭ��
		mov	di,START_POSITION	; ES:DI - ���� � ����������
		mov	si,offset display_line1 ; DS:SI - ���� ��ப�
		mov	cx,33			; ���稪 ᨬ����� � ��ப�
display_loop1:	mov	al,byte ptr [si]	; ������ ᨬ��� � AL
		stosw			; � �뢥�� ��� � ��ਡ�⮬ �� AH
		inc	si		; 㢥����� ���� ᨬ���� � ��ப�
		loop	display_loop1

; 蠣 2.2: �뢮� ᮡ�⢥��� ⠡����
		mov	dx,16		; ���稪 ��ப
		mov	al,-1		; �뢮���� ᨬ���
display_loop4:			; 横� �� ��ப��
		add	di,(80-33)*2	; 㢥����� DI �� ��砫� 
		push	ax		; ᫥���饩 ��ப�
		mov	al,0B3h
		stosw			; �뢥�� ���� ᨬ��� (0B3h)
		pop	ax
		mov	cx,16		; ���稪 ᨬ����� � ��ப�
display_loop3:		; 横� �� ᨬ����� � ��ப�
		inc	al		; ᫥���騩 ASCII-ᨬ���
		stosw			; �뢥�� ��� �� �࠭
		push	ax
		mov	al,20h		; �뢥�� �஡��
		stosw
		pop	ax
		loop	display_loop3	; � ⠪ 16 ࠧ
		push	ax
		sub	di,2		; �������� ����� �� 1 ᨬ���
		mov	al,0B3h		; � �뢥�� 0B3h �� ���� ��᫥�����
		stosw			; �஡���
		pop	ax
		dec	dx		; 㬥����� ���稪 ��ப
		jnz	display_loop4

; 蠣 2.3: �뢮� ��᫥���� ��ப�
		add	di,(80-33)*2	; 㢥����� DI �� ��砫� ᫥���饩 
					; ��ப�
		mov	cx,33		; ���稪 ᨬ����� � ��ப�
		mov	si,offset display_line2 ; DS:SI - ���� ��ப�
display_loop2:	mov	al,byte ptr [si] ; ������ ᨬ��� � AL
		stosw			; �뢥�� ��� � ��ਡ�⮬ �� �࠭
		inc	si		; 㢥����� ���� ᨬ���� � ��ப�
		loop	display_loop2

; 蠣 3: ���ᢥ⪠ (��������� ��ਡ��) � ⥪�饣� �뤥������� ᨬ����
		mov	al,byte ptr current_char ; AL = ⥪�騩 ᨬ���
		mov	ah,0
		mov	di,ax
		and	di,0Fh ; DI = ���⮪ �� ������� �� 16 (����� � ��ப�)
		shl	di,2	; 㬭����� ��� �� 2, ⠪ ��� �� �࠭� 
				; �ᯮ������ ᫮�� �� ᨬ���, � �� ࠧ �� 2,
				; ⠪ ��� ����� ᨬ������ - �஡���
		shr	ax,4	; AX = ��⭮� �� ������� �� 16 (����� ��ப�)
		imul	ax,ax,80*2 ; 㬭����� ��� �� ����� ��ப� �� �࠭�,
		add	di,ax	; ᫮���� ��,
		add	di,START_POSITION+2+80*2+1 ; �������� ���� 
			; ��砫� ���� + 2, �⮡� �ய����� ���� �⮫���,
			; + 80 * 2, �⮡� �ய����� ����� ��ப�, + 1, �⮡� 
			; ������� ���� ��ਡ��, � �� ᨬ����
		mov	al,071h		; ��ਡ�� - ᨭ�� �� �஬
		stosb			; �뢮� �� �࠭

		ret
display_all	endp

int09h_handler	endp		; ����� ��ࠡ��稪� INT 09h


; ���� ��� �࠭���� ᮤ�ন���� ��� �࠭�, ����� ����뢠���� ��訬 �����
screen_buffer	db	1190 dup(?)

; ��ࢠ� ��ப� ����
display_line1	db	0DAh,11 dup (0C4h),'* ASCII *',11 dup (0C4h),0BFh

; ��᫥���� ��ப� ����
display_line2	db	0C0h,11 dup (0C4h),'* Hex '
hex_byte1	db	?		; ����� ��� ⥪�饣� ����
hex_byte2	db	?		; ������ ��� ⥪�饣� ����
		db	' *',10 dup (0C4h),0D9h

hw_reset2D:	retf			; ISP: ��������� hw_reset
;
; ��ࠡ��稪 ���뢠��� INT 2Dh
; �����ন���� �㭪樨 AMIS 3.6 00h, 02h, 03h, 04h � 05h
int2Dh_handler	proc	far
		jmp short actual_int2Dh_handler ; ISP: �ய����� ����
old_int2Dh	dd	?			; ISP: ���� ��ࠡ��稪
		dw	424Bh			; ISP: ᨣ�����
		db	00h			; ISP: �ணࠬ���� ���뢠���
		jmp short hw_reset2D		; ISP: ������� jmp �� hw_reset
		db	7 dup (0)		; ISP: ��१�ࢨ஢���
actual_int2Dh_handler:		; ��砫� ᮡ�⢥��� ��ࠡ��稪� INT 2Dh
		db	80h,0FCh	; ��砫� ������� CMP AH, �᫮
mux_id		db	?		; �����䨪��� �ணࠬ��
		je	its_us		; �᫨ ��뢠�� � �㦨� AH - �� �� ���
		jmp	dword ptr cs:old_int2Dh
its_us:
		cmp	al,06		; �㭪樨 06h � ���
		jae	int2D_no	; �� �����ন������
		cbw			; AX = ����� �㭪樨
		mov	di,ax		; DI = ����� �㭪樨
		shl	di,1		; 㬭����� ��� �� 2, ⠪ ��� jumptable - 
					; ⠡��� ᫮�
		jmp	word ptr cs:jumptable[di] ; ��ᢥ��� ���室 
						; �� ��ࠡ��稪� �㭪権
jumptable	dw	offset int2D_00,offset int2D_no
		dw	offset int2D_02,offset int2D_03
		dw	offset int2D_04,offset int2D_05

int2D_00:			; �஢�ઠ ������
		mov	al,0FFh		; ��� ����� �����
		mov	cx,0100h	; ����� ���ᨨ 1.0
		push	cs
		pop	dx		; DX:DI - ���� AMIS-ᨣ������
		mov	di,offset amis_sign
		iret
int2D_no:			; �������ন������ �㭪��
		mov	al,00h	; �㭪�� �� �����ন������
		iret
int2D_02:			; ���㧪� �ணࠬ��
		mov	byte ptr cs:disable_point,0CFh ; ������� ��� 
				; ������� IRET �� ����� disable_point � ��ࠡ��稪 INT 09h
		mov	al,04h	; �ணࠬ�� �����⨢�஢���, �� ᠬ� 
				; ���㧨���� �� �����
		mov	bx,cs	; BX - ᥣ����� ���� �ணࠬ��
		iret
int2D_03: 		; ����� �� ��⨢����� ��� "�ᯫ뢠���" �ணࠬ�
		cmp	byte ptr we_are_active,0 ; �᫨ ���� 㦥 ��
		je	already_popup		; �࠭�,
		call	save_screen		; ��࠭��� ������� �࠭�,
		push	cs
		pop	ds
		call	display_all		; �뢥�� ����
		mov	byte ptr we_are_active,1 ; � ������� 䫠�
already_popup:
		mov	al,03h	; ��� 03: �ணࠬ�� ��⨢���஢���
		iret

int2D_04: 		; ������� ᯨ᮪ ���墠祭��� ���뢠���
		mov	dx,cs		; ᯨ᮪ � DX:BX
		mov	bx,offset amis_hooklist
		iret
int2D_05:		 ; ������� ᯨ᮪ "������" ������
		mov	al,0FFh	; �㭪�� �����ন������
		mov	dx,cs		; ᯨ᮪ � DX:BX
		mov	bx,offset amis_hotkeys
		iret
int2Dh_handler	endp

; AMIS: ᨣ����� ��� १������� �ணࠬ�
amis_sign	db	"Cubbi   "	; 8 ���⮢ - ��� ����
		db	"ASCII   "	; 8 ���⮢ - ��� �ணࠬ��
		db	"ASCII display and input utility",0 ; ASCIZ-
					; �������਩ �� ����� 64 ���⮢
; AMIS: ᯨ᮪ ���墠祭��� ���뢠���
amis_hooklist	db	09h
		dw	offset int09h_handler
		db	2Dh
		dw	offset int2Dh_handler

; AMIS: ᯨ᮪ ������ ������
amis_hotkeys	db	01h 	; ������ �஢������� ��᫥ �⠭���⭮�� 
				; ��ࠡ��稪� INT 09h
		db	1	; �᫮ ������
		db	1Eh	; ᪠�-��� ������ (A)
		dw	08h	; �ॡ㥬� 䫠�� (�� Alt)
		dw	0	; ����饭�� 䫠��
		db	1	; ������ ���⠥���

; ����� १����⭮� ���
; ��砫� ��楤��� ���樠����樨

initialize	proc near
		mov	ah,9
		mov	dx,offset usage	; �뢥�� ���ଠ�� � �ணࠬ��
		int	21h

; �஢����, �� ��⠭������ �� 㦥 ��� �ணࠬ��
		mov	ah,-1		; ᪠��஢���� ����஢ �� FFh �� 00h
more_mux:
		mov	al,00h		; �㭪�� 00h - �஢�ઠ ������
		int	2Dh		; ���⨯����୮� ���뢠��� AMIS,
		cmp	al,00h		; �᫨ �����䨪��� ᢮�����,
		jne	not_free
		mov	byte ptr mux_id,ah ; ������� ��� ����� ��אַ � ��� 
					; ��ࠡ��稪� int 2Dh,
		jmp short next_mux
not_free:
		mov	es,dx		; ���� - ES:DI = ���� �� AMIS-ᨣ������
		mov	si,offset amis_sign ; DS:SI = ���� ��襩 ᨣ������
		mov	cx,16		; �ࠢ���� ���� 16 ���⮢,
		repe	cmpsb
		jcxz	already_loaded ; �᫨ ��� �� ᮢ������,
next_mux:
		dec	ah		; ��३� � ᫥���饬� �����䨪����,
		jnz	more_mux	; ���� �� �� 0 (�� ᠬ�� ���� � �⮬ �ਬ�� 
			; ᪠��஢���� �ந�室�� �� FFh �� 01h, ⠪ ��� 0 
			; �� �ᯮ��㥬 ��� �ਧ��� ������⢨� 
			; ᢮������� ����� � ᫥���饩 ��ப�)
free_mux_found:
		cmp	byte ptr mux_id,0	; �᫨ �� ��祣� �� ����ᠫ�,
		je	no_more_mux		; �����䨪���� ���稫���

		mov	ax,352Dh		; AH = 35h, AL = ����� ���뢠���
		int	21h			; ������� ���� ��ࠡ��稪� INT 2Dh
		mov	word ptr old_int2Dh,bx	; � �������� ��� � old_int2Dh
		mov	word ptr old_int2Dh+2,es
		mov	ax,3509h		; AH = 35h, AL = ����� ���뢠���
		int	21h			; ������� ���� ��ࠡ��稪� INT 09h
		mov	word ptr old_int09h,bx	; � �������� ��� � old_int09h
		mov	word ptr old_int09h+2,es

		mov	ax,252Dh		; AH = 25h, AL = ����� ���뢠���
		mov	dx,offset int2Dh_handler ; DS:DX - ���� ��襣�
		int	21h			; ��ࠡ��稪�
		mov	ax,2509h		; AH = 25h, AL = ����� ���뢠���
		mov	dx,offset int09h_handler ; DS:DX - ���� ��襣�
		int	21h			; ��ࠡ��稪�

		mov	ah,49h			; AH = 49h
		mov	es,word ptr envseg ; ES = ᥣ����� ���� �।� DOS
		int	21h			; �᢮������ ������

		mov	ah,9
		mov	dx,offset installed_msg	; �뢮� ��ப� �� �ᯥ譮� 
		int	21h			; ���⠫��樨

		mov	dx,offset initialize	; DX - ���� ��ࢮ�� ���� �� 
						; ���殬 १����⭮� ���
		int	27h			; �������� �믮������, ��⠢��� 
						; १����⮬

; � ��।����� �ࠢ�����, �᫨ ��� �ணࠬ�� �����㦥�� � �����
already_loaded:
		mov	ah,9			; AH = 09h
		mov	dx,offset already_msg	; �뢥�� ᮮ�饭�� �� �訡��
		int	21h
		ret				; � ���������� ��ଠ�쭮

; � ��।����� �ࠢ�����, �᫨ �� 255 �㭪権 ���⨯����� ������ 
; १�����묨 �ணࠬ����
no_more_mux:
		mov	ah,9
		mov	dx,offset no_more_mux_msg
		int	21h
		ret

; ⥪��, ����� �뤠�� �ணࠬ�� �� ����᪥:
usage		db	'ASCII display and input program'
		db	' v1.0',0Dh,0Ah
		db	'Alt-A   - activation',0Dh,0Ah
		db	'Arrow keys - choose character',0Dh,0Ah
		db	'Enter   - enter character',0Dh,0Ah
		db	'Escape  - exit',0Dh,0Ah
		db	'$'
; ⥪��, ����� �뤠�� �ணࠬ��, �᫨ ��� 㦥 ����㦥��:
already_msg	db	'ERROR: Already loaded',0Dh,0Ah,'$'
; ⥪��, ����� �뤠�� �ணࠬ��, �᫨ �� �㭪樨 ���⨯����� ������:
no_more_mux_msg	db	'ERROR: Too many TSR programs'
		db	' loaded',0Dh,0Ah,'$'
; ⥪��, ����� �뤠�� �ணࠬ�� �� �ᯥ譮� ��⠭����:
installed_msg	db	'Installed successfully',0Dh,0Ah,'$'

initialize	endp
		end	start
