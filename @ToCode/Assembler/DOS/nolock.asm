; nolock.asm
; ᠬ�� ���⪠� �ணࠬ�� ��� �몫�祭�� NumLock, CapsLock � ScrollLock
; ����᪠�� ��� ��ࠬ��஢
;
; ���������:
; TASM:
; tasm /m nolock.asm
; tlink /t /x nolock.obj
; MASM:
; ml /c nolock.asm
; link nolock.obj,,NUL,,,
; exe2bin nolock.exe nolock.com
; WASM:
; wasm nolock.asm
; wlink file nolock.obj form DOS COM
;

	.model	tiny
	.code
	org	100h	; COM-䠩�. AX �� ����᪥ COM-䠩�� ��� ��ࠬ��஢
			; � �������� ��ப� �ᥣ�� ࠢ�� 0
start:
	mov	ds,ax	; ⠪ �� ⥯��� DS = 0
	mov	byte ptr ds:0417h,al	; ���� ���ﭨ� ���������� 1 = 0
	ret		; ��室 �� �ணࠬ��
	end	start
