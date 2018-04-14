; timer.asm
; ���������� ���墠� ���뢠��� ��⥬���� ⠩���: �뢮� �६���
; � ���孥� ����� 㣫� �࠭� � �����६����� ࠡ�⮩ 襫��
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
	.186		; ��� pusha/popa � ᤢ����
	org	100h	; COM-�ணࠬ��
start	proc	near

; ��࠭���� ���� �।��饣� ��ࠡ��稪� ���뢠��� 1Ch
	push es
	mov	ax,351Ch	; AH=35h, AL=����� ���뢠���
	int	21h
	mov	word ptr old_int1Ch,bx
	mov	word ptr old_int1Ch+2,es
	pop es
; ��⠭���� ��襣� ��ࠡ��稪�
	mov	ax,251Ch	; AH=25h, AL=����� ���뢠���
	mov	dx,offset int1Ch_handler ; DS:DX - ���� ��ࠡ��稪�
	int	21h		; ��⠭����� ��ࠡ��稪 ���뢠��� 1Ch

; ᮡ�⢥��� �ணࠬ��
	mov	sp,length_of_program+100h+200h ; ��६��⨬ �⥪ �� 200h ��᫥
			; ���� �ணࠬ�� (������⥫�� 100h - ��� PSP)
	mov	ah,4Ah
	mov	bx,((length_of_program+100h+200h) shr 4)+1
	int	21h	; �᢮����� ��� ������ ��᫥ ���� �ணࠬ�� � �⥪�
; �������� ���� EPB, ᮤ�ঠ騥 ᥣ����� ����
	mov	ax,cs
	mov	word ptr EPB+4,ax	; ᥣ����� ���� ��������� ��ப�
	mov	word ptr EPB+8,ax	; ᥣ����� ���� ��ࢮ�� FCB
	mov	word ptr EPB+0Ch,ax	; ᥣ����� ���� ��ண� FCB

	mov	ax,4B00h		; �㭪�� DOS 4Bh
	mov	dx,offset command_com	; ���� ASCIZ-��ப� � ������ command.com
	mov	bx,offset EPB
	int	21h			; �ᯮ����� �ணࠬ��
call print_al
; ����� �ணࠬ��

; ����⠭������� �।��饣� ��ࠡ��稪� ���뢠��� 1Ch
	mov	ax,251Ch
	mov	dx,word ptr cs:old_int1Ch+2
	mov	ds,dx
	mov	dx,word ptr cs:old_int1Ch
	int	21h

	int	20h

old_int1Ch dd	?	; ����� �࠭���� ���� �।��饣� ��ࠡ��稪�
command_com	db	'C:\COMMAND.COM',0	; ��� 䠩��
EPB		dw	0000	; �ᯮ�짮���� ⥪�饥 ���㦥���
		dw	offset commandline,0	; ���� ��������� ��ப�
		dw	005Ch,0,006Ch,0	; ���� FCB, ��।����� ��襩 �ணࠬ��
commandline	db	01,20h,0Dh

start_position	dw 0	; ������ �� �࠭�, � ������ �뢮����� �६�

start	endp

; ��ࠡ��稪 ��� ���뢠��� 1Ch
; �뢮��� ⥪�饥 �६� � ����樨 start_position
;
int1Ch_handler	proc	far
		pusha		; ��ࠡ��稪 �����⭮�� ���뢠���
		push	es	; ������ ��࠭��� ��� ॣ�����
		push	ds

		push	cs	; �� �室� � ��ࠡ��稪 ��।��� ⮫쪮 CS
		pop	ds
		mov	ah,02h		; �㭪�� 02h ���뢠��� 1Ah:
		int	1Ah		; �⥭�� �६��� �� RTC
		jc	exit_handler	; �᫨ ��� ������ - � ��㣮� ࠧ

					; AL = �᫮ �ᮢ � BCD �ଠ�
		call	bcd2asc		; �८�ࠧ����� � ASCII ᨬ����
		mov	byte ptr output_line[2],ah ; �������� �� � ��ப�
		mov	byte ptr output_line[4],al ; output_line

		mov	al,cl		; CL = �᫮ ����� � BCD �ଠ�
		call	bcd2asc
		mov	byte ptr output_line[10],ah
		mov	byte ptr output_line[12],al

		mov	al,dh		; DH = �᫮ ᥪ㭤 � BCD �ଠ�
		call	bcd2asc
		mov	byte ptr output_line[16],ah
		mov	byte ptr output_line[18],al
	
		mov	cx,output_line_l	; �᫮ ���� � ��ப� � CX
		push	0B800h
		pop	es			; ���� � ����������
		mov	di,word ptr start_position ; � ES:SI
		mov	si,offset output_line	; ���� ��ப� � DS:DI
		cld
		rep movsb			; ᪮��஢��� ��ப�
exit_handler:
		pop	ds		; ����⠭����� �� ॣ�����
		pop	es
		popa
		jmp	cs:old_int1Ch	; ��।��� �ࠢ����� �।��饬�
					; ��ࠡ��稪�

; ��楤�� bcd2asc
; �८�ࠧ�� ������ ���� 㯠��������� BCD-�᫠ � AL � ASCII ᨬ��� � AH,
; � ������� ���� � ASCII ᨬ��� � AL
bcd2asc		proc	near
		mov	ah,al
		and	al,0Fh		; ��⠢��� ����訥 4 ��� � AL
		shr	ah,4		; ᤢ����� ���訥 4 ��� � AH 
		or	ax,3030h	; �८�ࠧ����� � ASCII-ᨬ����
		ret
bcd2asc		endp


output_line	db	' ',1Fh,'0',1Fh,'0',1Fh,'h',1Fh ; ��ப� " 00h 00:00 "
		db	' ',1Fh,'0',1Fh,'0',1Fh,':',1Fh	; � ��ਡ�⮬ 1Fh
		db	'0',1Fh,'0',1Fh,' ',1Fh		; ��᫥ ������� ᨬ����
output_line_l	equ $-output_line

int1Ch_handler	endp

print_al:
	mov	dh,al
	and	dh,0Fh		; DH - ����訥 4 ���
	shr	al,4		; AL - ���訥
	call	print_nibble	; �뢥�� ������ ����
	mov	al,dh		; ⥯��� AL ᮤ�ন� ����訥 4 ���
print_nibble:		; ��楤�� �뢮�� 4 ��� (��⭠����筮� ����)
	cmp	al,10		; �� �������, ��ॢ���騥 ���� � AL
	sbb	al,69h		; � ᮮ⢥����騩 ASCII ���
	das			; (�. ���ᠭ�� ������� das)

	mov	dl,al		; ��� ᨬ���� � DL
	mov	ah,2		; ����� �㭪樨 DOS � AH 
	int	21h		; �뢮� ᨬ����
	ret		; ��� ret ࠡ�⠥� ��� ࠧ�

length_of_program equ $-start
	end	start
