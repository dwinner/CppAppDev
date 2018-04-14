; pm0.asm
; �ணࠬ��, �믮������ ���室 � ���饭�� ०�� � ���������� ������.
; ����⠥� � DOS � ॠ�쭮� ०��� � � DOS-���� Windows 95 (Windows 
; ���墠�뢠�� �᪫�祭��, ��������騥 �� ����⪥ ���室� � ���饭�� 
; ०�� �� V86, � �������� ��� ࠡ����, �� ⮫쪮 �� �������쭮� �஢�� 
; �ਢ������)
;
; ���������:
; TASM:
;  tasm /m pm0.asm
;  tlink /x /t pm0.obj
; MASM:
;  ml /c pm0.asm
;  link pm0.obj,,NUL,,,
;  exe2bin pm0.exe pm0.com
; WASM:
;  wasm pm0.asm
;  wlink file pm0.obj form DOS COM
;

	.model	tiny
	.code
	.386p		; �� ��� �ਬ��� ����⠭� �� 80386
	org	100h	; �� COM-�ணࠬ��
start:
; �����⮢��� ᥣ����� ॣ�����
	push	cs
	pop	ds		; DS - ᥣ���� ������ (� ����) ��襩 �ணࠬ��
	push	0B800h
	pop	es		; ES - ᥣ���� ����������
; �஢����, ��室���� �� �� 㦥 � ���饭��� ०���
	mov	eax,cr0	; ������ ॣ���� CR0
	test	al,1		; �஢���� ��� PE,
	jz	no_V86	; �᫨ �� ���� - �� ����� �த������,
; ���� - ᮮ���� �� �訡�� � ���
	mov	ah,9		; �㭪�� DOS 09h
	mov	dx,offset v86_msg	; DS:DX - ���� ��ப�
	int	21h		; �뢮� �� �࠭
	ret			; ����� COM-�ணࠬ��
; (ࠧ �� ���饭�� ०��, � ���஬ ࠡ�⠥� ��� DOS-
; �ணࠬ��, �� ������ ���� ०�� V86)
v86_msg	db	"Running in V86 mode. Can't switch to PM$"

; � ��।����� �ࠢ�����, �᫨ �� ����饭� � ॠ�쭮� ०���
no_V86:
; ������� ���뢠���
	cli
; ������� ����᪨�㥬�� ���뢠���
	in	al,70h	; ������� ���� CMOS
	or	al,80h	; ��⠭���� ��� 7 � ��� ����頥� NMI
	out	70h,al
; ��३� � ���饭�� ०��
	mov	eax,cr0	; ������ ॣ���� CR0
	or	al,1	; ��⠭����� ��� PE,
	mov	cr0,eax	; � �⮣� ������ �� � ���饭��� ०���
; �뢮� �� �࠭
	xor	di,di			; ES:DI - ��砫� ����������
	mov	si,offset message	; DS:SI - �뢮���� ⥪��
	mov	cx,message_l
	rep movsb		; �뢮� ⥪��
	mov	ax,0720h	; �஡�� � ��ਡ�⮬ 07h
	mov	cx,rest_scr	; ��������� �⨬ ᨬ����� ���⮪ �࠭�
	rep stosw
; ��४������� � ॠ��� ०��
	mov	eax,cr0	; ������ CR0
	and	al,0FEh	; ����� ��� PE
	mov	cr0,eax	; � �⮣� ������ ������ ࠡ�⠥� � ॠ�쭮� 
			; ०���
; ࠧ���� ����᪨�㥬�� ���뢠���
	in	al,70h	; ������� ���� CMOS
	and	al,07FH	; ��� ��� 7 �⬥��� �����஢���� NMI
	out	70h,al
; ࠧ���� ���뢠���
	sti
; ��������� ������ �� ������
	mov	ah,0
	int	16h
; ��� �� COM-�ணࠬ��
	ret
; ⥪�� ᮮ�饭�� � ��ਡ�⮬ ��᫥ ������� ᨬ���� ��� ��אַ�� �뢮�� �� �࠭
message	db	'H',7,'e',7,'l',7,'l',7,'o',7,' ',7,'f',7
	db	'r',7,'o',7,'m',7,' ',7,'P',7,'M',7
; ��� ����� � �����
message_l = $-message
; ����� ��⠢襩�� ��� �࠭� � ᫮���
rest_scr = (80*25)-(2*message_l)
	end	start
