.386
.MODEL FLAT, STDCALL
OPTION CASEMAP: NONE
	; ��������� ������� ������� (��������) ����������� ���������� EXTERN, 
	; ����� ����� @ ����������� ����� ����� ������������ ����������,
	; ����� ��������� ����������� ��� �������� ������� � ���������
EXTERN  GetStdHandle@4: PROC
EXTERN  WriteConsoleA@20: PROC
EXTERN  CharToOemA@8: PROC
EXTERN  ReadConsoleA@20: PROC
	; ������� ������ �� ���������
EXTERN  ExitProcess@4: PROC
	; ������� ����������� ����� ������
EXTERN  lstrlenA@4: PROC
	; �.�. ����� ���������� ������� �� �����������,
	; ������������ ����������, �������� �������� ������� ���� 
	; ���������� ���������
EXTERN  wsprintfA: PROC

	; ������� ������
.DATA

	; ��������� ������, � ����� ���������
	; ����������� �������: 13 � ������� �������, 10 � ������� �� ����� 
	; ������, 0 � ����� ������; � �������������� ��������� DB
	; ������������� ������ ������
STRN DB "������� ������: ",13,10,0
	; ������ �� ������� �������� ��� ������� wsprintfA
FMT DB "����� %d", 0
	; ���������� �����; ��������� DD ����������� ������ �������
	; 32 ���� (4 �����), ���� �?� ������������ ��� �������������������� ������
DIN DD ?
	; ���������� ������
DOUT DD ?
	; ����� ��� ��������/��������� ����� ������ 200 ������
BUF  DB 200 dup (?)
	; ���������� ��� ���������� ���������� ��������
LENS DD ?

	; ������� ���� 
.CODE

	; ������ �������� ��������� � ������ MAIN
MAIN PROC
	; ������������ ������ STRN:
	; �������� MOV �������� ������� ��������
	; ������������ � ������, OFFSET � ��������, ������������ �����
MOV  EAX, OFFSET STRN

	; ��������� ������� ���������� � ���� �������� PUSH
PUSH EAX
PUSH EAX
	; ����� �������
CALL CharToOemA@8
	; ������������ ������ FMT
MOV  EAX, OFFSET FMT
PUSH EAX 
PUSH EAX
	; ����� �������
CALL CharToOemA@8
PUSH -10
	; ������� ���������� �����
CALL GetStdHandle@4
	; ����������� ��������� �� �������� EAX 
	; � ������ ������ � ������ DIN
	; ������� ���������� ������
MOV DIN, EAX 	
PUSH -11
CALL GetStdHandle@4
MOV DOUT, EAX 
	; ��������� ����� ������ STRN
	; � ���� ���������� ����� ������
PUSH OFFSET STRN
	; ����� � EAX
	; ����� ������� WriteConsoleA ��� ������ ������ STRN
CALL lstrlenA@4
	; � ���� ���������� 5-� ��������
PUSH 0
	; 4-� ��������
PUSH OFFSET LENS
	; 3-� ��������
PUSH EAX
	; 2-� ��������
PUSH OFFSET STRN
	; 1-� ��������
PUSH DOUT
	; ���� ������
CALL WriteConsoleA@20
	; � ���� ���������� 5-� ��������
PUSH 0
	; 4-� ��������
	; �������� ��������: LENS ������ ����� ���������
	; �������� �� ���, ������������� ��������� �������: 13 � ������� ������� � 
	; 10 � ������� �� ����� ������
	; ����� ���������� ������
PUSH OFFSET LENS
	; 3-� ��������
PUSH 200
	; 2-� ��������
PUSH OFFSET BUF
	; 1-� ��������
PUSH DIN
CALL ReadConsoleA@20 
PUSH 0
PUSH OFFSET LENS
	; ����� �������� ������
PUSH LENS
PUSH OFFSET BUF
PUSH DOUT
CALL WriteConsoleA@20
	; ����� ����� 123 � ����� BUF
PUSH 123
PUSH OFFSET FMT
PUSH OFFSET BUF
CALL wsprintfA
	; ������� ����� �� ���������� (��������� �������� ESP 
	; �� 3*4 = 12 ������)
ADD	ESP, 12
	; ����� ������ � ������ 123
PUSH 0
PUSH OFFSET LENS
PUSH EAX
PUSH OFFSET BUF
PUSH DOUT
	; ��������� ��������
CALL WriteConsoleA@20
	; ��������� � ������� ECX � ������� ����� �
	; �������� ��������
MOV ECX,03FFFFFFFH
	; ���� ��� ����
L1: LOOP L1
	; ����� �� ���������
	; ��������: ��� ������
PUSH 0
CALL ExitProcess@4
	; ���������� �������� ��������� � ������ MAIN
MAIN ENDP
	; ���������� �������� ������ � ��������� ������ ����������� ���������
END MAIN
