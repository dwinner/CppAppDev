; fidoh.asm
; ������� ���᪨� "�" �� ��⨭᪨� "H" �� ��� 䠩��� � ���७��� .TXT � 
; ⥪�饩 ��४�ਨ
;
; ���������:
; TASM:
; tasm /m fidoh.asm
; tlink /t /x fidoh.obj
; MASM:
; ml /c fidoh.asm
; link fidoh.obj,,NUL,,,
; exe2bin fidoh.exe fidoh.com
; WASM:
; wasm fidoh.asm
; wlink file fidoh.obj form DOS COM
;

	.model tiny
	.code
	org	100h		; COM-䠩�
start:
	mov	ah,4Eh	; ���� ��ࢮ�� 䠩��
	xor	cx,cx		; �� ��⥬��, �� ��४��� � �. �.
	mov	dx,offset filespec ; ��᪠ ��� ���᪠ � DS:DX
file_open:
	int	21h
	jc	no_more_files	; �᫨ CF = 1 - 䠩�� ���稫���

	mov	ax,3D02h	; ������ 䠩� ��� �⥭�� � �����
	mov	dx,80h+1Eh	; ᬥ饭�� DTA + ᬥ饭�� ����� 䠩��
	int	21h		; �� ��砫� DTA
	jc	find_next	; �᫨ 䠩� �� ������ - ��३� � 
				; ᫥���饬�

	mov	bx,ax		; �����䨪��� 䠩�� � BX
	mov	cx,1		; ���뢠�� ���� ����
	mov	dx,offset buffer ; ��砫� ���� - � DX
read_next:
	mov	ah,3Fh	; �⥭�� 䠩��
	int	21h
	jc	find_next	; �᫨ �訡�� - ��३� � ᫥���饬�
	dec	ax		; �᫨ AX = 0 - 䠩� ���稫�� -
	js	find_next	; ��३� � ᫥���饬�
	cmp	byte ptr buffer,8Dh ; �᫨ �� ��⠭� ���᪠� "�",
	jne	read_next	; ����� ᫥���騩 ����,
	mov	byte ptr buffer,48h ; ���� - ������� � ���� 
				; ��⨭��� �㪢� "H"

	mov	ax,4201h	; ��६����� 㪠��⥫� 䠩�� �� ⥪�饩
	dec	cx		; ����樨 ����� �� 1
	dec	cx		; CX = FFFFh
	mov	dx,cx		; DX = FFFFh
	int	21h

	mov	ah,40h	; ������� � 䠩�
	inc	cx
	inc	cx		; ���� ���� (CX = 1)
	mov	dx,offset buffer ; �� ���� � DS:DX
	int	21h
	jmp short read_next	; ����� ᫥���騩 ����

find_next:
	mov	ah,3Eh	; ������� �।��騩 䠩�
	int	21h

	mov	ah,4Fh	; ���� ᫥���騩 䠩�
	mov	dx,80h	; ᬥ饭�� DTA �� ��砫� PSP
	jmp short file_open

no_more_files:			; �᫨ 䠩�� ���稫���,
	ret			; ��� �� �ணࠬ��

filespec	db	'*.txt',0	; ��᪠ ��� ���᪠
buffer label byte			; ���� ��� �⥭��/����� - �� ���殬 
					; �ணࠬ��
	end	start
