; term2.asm
; �������쭠� �ନ���쭠� �ணࠬ��, �ᯮ������ ���뢠���
; ��室 - Alt-X
;
; ���������:
; TASM:
;  tasm /m term2.asm
;  tlink /t /x term2.obj
; MASM:
;  ml /c term2.asm
;  link term2.obj,,NUL,,,
;  exe2bin term2.exe term2.com
; WASM:
;  wasm term2.asm
;  wlink file term2.obj form DOS COM
;

	.model	tiny
	.code
	.186
	org	100h	; COM-�ணࠬ��

; ᫥���騥 ���� ��४⨢� ��।�����, ��� ������ ��᫥����⥫쭮�� ���� 
; ᪮�����஢��� �ணࠬ�� (������� �஢�ப �� �믮������ - �� ����᪠�� ��� 
; �ਬ��, �᫨ � ��� ��� ������ �� ᮮ⢥�����饬 �����). ����쭠� �ணࠬ�� 
; ������ ��।����� ����� ���� �� ���䨣��樮����� 䠩�� ��� �� ��������� 
; ��ப�
COM		equ 02F8h	; ����� �������� ���� (COM2)
IRQ		equ 0Bh	; ����� ���뢠��� (INT 0Bh ��� IRQ3)
E_BITMASK	equ 11110111b	; ��⮢�� ��᪠ ��� ࠧ�襭�� IRQ3
D_BITMASK	equ 00001000b	; ��⮢�� ��᪠ ��� ����饭�� IRQ3

start:
	call	init_everything	; ���樠������ ����� � ������
main_loop:	; �᭮���� 横�
; ॠ�쭠� �ନ���쭠� �ணࠬ�� � �⮬ 横�� �㤥� �뢮���� ����� �� ���� 
; �ਥ�� (������塞��� �� ��ࠡ��稪� ���뢠���) �� �࠭, �᫨ ���� ���筠� 
; ࠡ��, � 䠩�, �᫨ ����뫠���� 䠩�, ��� ��ࠡ��뢠�� ���-� ��-��㣮��. � 
; ��襬 �ਬ�� �� �ᯮ��㥬 �᭮���� 横� ��� ����� ᨬ�����, ��� ���� �� 
; ������ �� ��ࠡ��稪� ���뢠��� �� ����������
	mov	ah,8		; �㭪�� DOS 08h
	int	21h		; �⥭�� � ��������� � ��� ��,
	test	al,al		; �᫨ ������ ����� ᨬ���,
	jnz	send_char	; ��᫠�� ���,
	int	21h		; ���� - ����� ���७�� ASCII-���,
	cmp	al,2Dh	; �᫨ �� �� Alt-X,
	jne	main_loop	; �த������ 横�,

	call	shutdown_everything	; ���� - ����⠭����� �� � 
					; ��室��� ���ﭨ�
	ret		; � �������� �ணࠬ��

send_char:		; ���뫪� ᨬ���� � �����
; ����쭠� �ନ���쭠� �ணࠬ�� ������ ����� ⮫쪮 ��������� ᨬ��� � ���� 
; ��।��, �, �᫨ ��� ���� �� ����, ࠧ���� ���뢠��� "ॣ���� ��।�� 
; ����". ���� ��諥� ᨬ��� ������� � ����
	mov	dx,COM	; ॣ���� THR
	out	dx,al
	jmp short main_loop

old_irq	dd	? ; ����� �㤥� �࠭����� ���� ��ண� ��ࠡ��稪�


; ��饭�� ��ࠡ��稪 ���뢠��� �� ��᫥����⥫쭮�� ����

irq_handler	proc	far
	pusha		; ��࠭��� ॣ�����
	mov	dx,COM+2	; ������ ॣ���� �����䨪�樨
	in	al,dx		; ���뢠���
repeat_handler:
	and	ax,00000110b ; ���㫨�� �� ����, �஬� 1 � 2,
	mov	di,ax		; �⢥��騥 �� 4 �᭮��� ���樨
	call	word ptr cs:handlers[di] ; ��ᢥ��� �맮� ��楤��� 
					; ��� ��ࠡ�⪨ ���樨
	mov	dx,COM+2	; �� ࠧ ������ ॣ���� �����䨪�樨 
	in	al,dx		; ���뢠���,
	test	al,1		; �᫨ ����訩 ��� �� 1,
	jz	repeat_handler	; ���� ��ࠡ���� �� ���� ���뢠���,
	mov	al,20h	; ���� - �������� �����⭮� ���뢠���
	out	20h,al	; ���뫪�� ������� EOI (�. 1.2.10)
	popa
	iret    
; ⠡��� ���ᮢ ��楤��, ���㦨����� ࠧ�� ��ਠ��� ���뢠���
handlers	dw	offset line_h, offset trans_h
		dw	offset recv_h, offset modem_h

; �� ��楤�� ��뢠���� �� ��������� ���ﭨ� �����
line_h	proc	near
	mov	dx,COM+5	; ���� �� �㤥� ���⠭ LSR,
	in	al,dx		; ���뢠��� �� ��⠥��� �����訢訬��
; ����� ����� �஢����, �� ��稫���, �, ���ਬ��, ��ࢠ�� ���, �᫨ 
; �����㦥�� ���ﭨ� BREAK
	ret
line_h	endp
; �� ��楤�� ��뢠���� �� �ਥ�� ����� ������
recv_h	proc	near
	mov	dx,COM	; ���� �� �㤥� ���⠭ RBR,
	in	al,dx		; ���뢠��� �� ��⠥��� �����訢訬��
; ����� ᫥��� �������� �ਭ��� ���� � ���� �ਥ�� ��� �᭮���� �ணࠬ��, 
; �� �� ���� �ࠧ� �뢥��� ��� �� �࠭
	int	29h	; �뢮� �� �࠭
	ret
recv_h	endp
; �� ��楤�� ��뢠���� �� ����砭�� ��।�� ������
trans_h	proc	near
; ����� ᫥��� ������� � THR ᫥���騩 ᨬ��� �� ���� ��।�� �, �᫨ 
; ���� ��᫥ �⮣� ����뢠���� ����� - ������� ��� ⨯ ���뢠���
	ret
trans_h	endp
; �� ��楤�� ��뢠���� �� ��������� ���ﭨ� ������
modem_h	proc	near
	mov	dx,COM+6	; ���� MCR �� �㤥� ���⠭,
	in	al,dx		; ���뢠��� �� ��⠥��� �����訢訬��
; ����� ����� ��।����� ���ﭨ� ������ � ������� ��㡪�, ��।����� 
; ����� ����饩 � ��१������, � �. �.
	ret
modem_h	endp
irq_handler	endp


; ���樠������ �ᥣ�, �� �ॡ���� ���樠����஢���

init_everything	proc	near
; ��⠭���� ��襣� ��ࠡ��稪� ���뢠���
	mov	ax,3500h+IRQ	; AH = 35h, AL = ����� ���뢠���
	int	21h			; ������� ���� ��ண� ��ࠡ��稪�
	mov	word ptr old_irq,bx	; � ��࠭��� � old_irq
	mov	word ptr old_irq+2,es
	mov	ax,2500h+IRQ	; AH = 25h, AL = ����� ���뢠���
	mov	dx,offset irq_handler	; DS:DX - ��� ��ࠡ��稪
	int	21h		; ��⠭����� ���� ��ࠡ��稪
; ����� �� ॣ����� ����
	mov	dx,COM+1	; ॣ���� IER
	mov	al,0
	out	dx,al		; ������� �� ���뢠���
	mov	dx,COM+4	; MCR
	out	dx,al		; ����� �� ����� ������ � 0
	mov	dx,COM+5	; � �믮����� �⥭�� �� LSR,
	in	al,dx
	mov	dx,COM+0	; �� RBR
	in	al,dx
	mov	dx,COM+6	; � �� MSR,
	in	al,dx		; �� �� ��砩, �᫨ ��� ������� �����﫨��, 
	mov	dx,COM+2	; � ⠪�� ��᫠�� 0 � ॣ���� FCR,
	mov	al,0		; �⮡� �몫���� FIFO
	out	dx,al

; ��⠭���� ᪮��� COM-����
	mov	dx,COM+3	; ������� � ॣ���� LCR
	mov	al,80h	; �� �᫮ � ���訬 ��⮬ 1
	out	dx,al
	mov	dx,COM+0	; ⥯��� ������� � ॣ���� DLL
	mov	al,2		; ����訩 ���� ����⥫� ᪮���,
	out	dx,al
	mov	dx,COM+1	; � � DLH -
	mov	al,0		; ���訩 ����
	out	dx,al		; (�� ����ᠫ� 0002h - ᪮���� ���� 57 600)

; ���樠������ �����
	mov	dx,COM+3	; ������� ⥯��� � LCR
	mov	al,0011b	; �᫮, ᮮ⢥�����饥 ०��� 8N1
	out	dx,al		; (�������� ��� �ᯮ��㥬���)
; ���樠������ ������
	mov	dx,COM+4	; ������� � ॣ���� MCR
	mov	al,1011b	; ��⮢�� ����, ��⨢������� DTR, RTS
	out	dx,al		; � OUT2
; ����� ᫥��� �믮����� �஢��� �� ����稥 ������ �� �⮬ ����� (���� 
; ॣ���� MSR, ���� �� ���� ��⠭������ ����� CTS � DSR ��� �� ������� �६�), 
; � ��⥬ ��᫠�� � ����� (� ���� �������� � ���� ��।��) ���樠���������� 
; ��ப�, ���ਬ�� 'ATZ',0Dh

; ࠧ�襭�� ���뢠���
	mov	dx,COM+1	; ������� � IER - ��⮢�� ����, ࠧ������
	mov	al,1101b	; �� ���뢠���, �஬� "ॣ���� ��।�� ����"
	out	dx,al
	in	al,21h		; ������ OCW1 (�. 1.2.10)
	and	al,E_BITMASK	; ࠧ��᪨஢��� ���뢠���
	out	21h,al		; ������� OCW1
	ret
init_everything endp


; �����饭�� �ᥣ� � ��室��� ���ﭨ�
shutdown_everything	proc	near
; ����饭�� ���뢠���
	in	al,21h		; ������ OCW1
	or	al,D_BITMASK	; ����᪨஢��� ���뢠���
	out	21h,al		; ������� OCW1
	mov	dx,COM+1	; ������� � ॣ���� IER
	mov	al,0		; ����
	out	dx,al
; ��� ����� ������ DTR � CTS
	mov	dx,COM+4	; ������� � ॣ���� MCR
	mov	al,0		; ����
	out	dx,al
; ����⠭������� �।��饣� ��ࠡ��稪� ���뢠���
	mov	ax,2500h+IRQ	; AH = 25h AL = ����� ���뢠���
	lds	dx,old_irq		; DS:DX - ���� ��ࠡ��稪�
	int	21h
	ret
shutdown_everything	endp
	end	start

