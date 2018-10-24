; timer.asm
; ���������� ���墠� ���뢠��� ��⥬���� ⠩���: �뢮� ⥪�饣� �६��� 
; � ����� 㣫� �࠭�
;
; ���������:
; TASM:
;  tasm /m timer.asm
;  tlink /t /x timer.obj
; MASM:
;  ml /c timer.asm
;  link timer.obj,,NUL,,,
;  exe2bin timer.exe timer.com
; WASM:
;  wasm timer.asm
;  wlink file timer.obj form DOS COM
;


	.model	tiny
	.code
	.186			; ��� pusha/popa � ᤢ����
	org	100h
start	proc	near
; ��࠭��� ���� �।��饣� ��ࠡ��稪� ���뢠��� 1Ch
	mov	ax,351Ch	; AH = 35h, AL = ����� ���뢠���
	int	21h		; �㭪�� DOS: ��।����� ���� ��ࠡ��稪� 
	mov	word ptr old_int1Ch,bx		; ���뢠��� 
	mov	word ptr old_int1Ch+2,es	; (�����頥��� � ES:BX)
; ��⠭����� ��� ��ࠡ��稪
	mov	ax,251Ch	; AH = 25h, AL = ����� ���뢠���
	mov	dx,offset int1Ch_handler ; DS:DX - ���� ��ࠡ��稪�
	int	21h		; ��⠭����� ��ࠡ��稪 ���뢠��� 1Ch

; ����� ࠧ��頥��� ᮡ�⢥��� �ணࠬ��, ���ਬ�� �맮� command.com
	mov	ah,1
	int	21h		; �������� ������ �� ���� �������
; ����� �ணࠬ��

; ����⠭����� �।��騩 ��ࠡ��稪 ���뢠��� 1�h
	mov	ax,251Ch		; AH = 25h, AL = ����� ���뢠���
	mov	dx,word ptr old_int1Ch+2
	mov	ds,dx
	mov	dx,word ptr cs:old_int1Ch ; DS:DX - ���� ��ࠡ��稪�
	int	21h

	ret

old_int1Ch dd	? ; ����� �࠭���� ���� �।��饣� ��ࠡ��稪�
start_position	dw 0	; ������ �� �࠭�, � ������ �뢮����� ⥪�饥 
			; �६�
start	endp

; ��ࠡ��稪 ��� ���뢠��� 1Ch
; �뢮��� ⥪�饥 �६� � ������ start_position �� �࠭� (⮫쪮 � ⥪�⮢�� 
; ०���)

int1Ch_handler	proc	far
	pusha		; ��ࠡ��稪 �����⭮�� ���뢠���
	push	es	; ������ ��࠭��� ��� ॣ�����
	push	ds

	push	cs	; �� �室� � ��ࠡ��稪 �����⭮ ⮫쪮 ���祭��
	pop	ds	; ॣ���� CS
	mov	ah,02h	; �㭪�� 02h ���뢠��� 1Ah:
	int	1Ah		; �⥭�� �६��� �� RTC
	jc	exit_handler ; �᫨ ��� ������ - � ��㣮� ࠧ

; AL = �� � BCD-�ଠ�
	call	bcd2asc	; �८�ࠧ����� � ASCII
	mov	byte ptr output_line[2],ah ; �������� �� �
	mov	byte ptr output_line[4],al ; ��ப� output_line

	mov	al,cl		; CL = ����� � BCD-�ଠ�
	call	bcd2asc
	mov	byte ptr output_line[10],ah
	mov	byte ptr output_line[12],al

	mov	al,dh		; DH = ᥪ㭤� � BCD-�ଠ�
	call	bcd2asc
	mov	byte ptr output_line[16],ah
	mov	byte ptr output_line[18],al

	mov	cx,output_line_l	; �᫮ ���⮢ � ��ப� - � CX
	push	0B800h
	pop	es			; ���� � ����������
	mov	di,word ptr start_position ; � ES:DI
	mov	si,offset output_line ; ���� ��ப� � DS:SI
	cld
	rep movsb			; ᪮��஢��� ��ப�
exit_handler:
	pop	ds		; ����⠭����� �� ॣ�����
	pop	es
	popa
	jmp	cs:old_int1Ch ; ��।��� �ࠢ����� �।��饬� 
				; ��ࠡ��稪�

; ��楤�� bcd2asc
; �८�ࠧ�� ������ ���� 㯠��������� BCD-�᫠ � AL � ASCII-ᨬ��� � AH,
; � ������� ���� - � ASCII-ᨬ��� � AL
bcd2asc		proc	near
	mov	ah,al
	and	al,0Fh	; ��⠢��� ����訥 4 ��� � AL
	shr	ah,4		; ᤢ����� ���訥 4 ��� � AH
	or	ax,3030h	; �८�ࠧ����� � ASCII-ᨬ����
	ret
bcd2asc		endp

; ��ப� " 00h 00:00" � ��ਡ�⮬ 1Fh (���� �� ᨭ��) ��᫥ ������� ᨬ����
output_line	db	' ',1Fh,'0',1Fh,'0',1Fh,'h',1Fh
		db	' ',1Fh,'0',1Fh,'0',1Fh,':',1Fh
		db	'0',1Fh,'0',1Fh,' ',1Fh
output_line_l	equ $-output_line

int1Ch_handler	endp

end	start
