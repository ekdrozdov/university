.386
.MODEL FLAT, STDCALL
OPTION CASEMAP: NONE
	; прототипы внешних функций (процедур) описываются директивой EXTERN, 
	; после знака @ указывается общая длина передаваемых параметров,
	; после двоеточия указывается тип внешнего объекта – процедура
EXTERN  GetStdHandle@4: PROC
EXTERN  WriteConsoleA@20: PROC
EXTERN  CharToOemA@8: PROC
EXTERN  ReadConsoleA@20: PROC
	; функция выхода из программы
EXTERN  ExitProcess@4: PROC
	; функция определения длины строки
EXTERN  lstrlenA@4: PROC
	; т.к. число параметров функции не фиксировано,
	; используется соглашение, согласно которому очищает стек 
	; вызывающая процедура
EXTERN  wsprintfA: PROC

	; сегмент данных
.DATA

	; выводимая строка, в конце добавлены
	; управляющие символы: 13 – возврат каретки, 10 – переход на новую 
	; строку, 0 – конец строки; с использованием директивы DB
	; резервируется массив байтов
STRN DB "Введите строку: ",13,10,0
	; строка со списком форматов для функции wsprintfA
FMT DB "Число %d", 0
	; дескриптор ввода; директива DD резервирует память объемом
	; 32 бита (4 байта), знак «?» используется для неинициализированных данных
DIN DD ?
	; дескриптор вывода
DOUT DD ?
	; буфер для вводимых/выводимых строк длиной 200 байтов
BUF  DB 200 dup (?)
	; переменная для количества выведенных символов
LENS DD ?

	; сегмент кода 
.CODE

	; начало описания процедуры с именем MAIN
MAIN PROC
	; перекодируем строку STRN:
	; командой MOV значение второго операнда
	; перемещается в первый, OFFSET – операция, возвращающая адрес
MOV  EAX, OFFSET STRN

	; параметры функции помещаются в стек командой PUSH
PUSH EAX
PUSH EAX
	; вызов функции
CALL CharToOemA@8
	; перекодируем строку FMT
MOV  EAX, OFFSET FMT
PUSH EAX 
PUSH EAX
	; вызов функции
CALL CharToOemA@8
PUSH -10
	; получим дескриптор ввода
CALL GetStdHandle@4
	; переместить результат из регистра EAX 
	; в ячейку памяти с именем DIN
	; получим дескриптор вывода
MOV DIN, EAX 	
PUSH -11
CALL GetStdHandle@4
MOV DOUT, EAX 
	; определим длину строки STRN
	; в стек помещается адрес строки
PUSH OFFSET STRN
	; длина в EAX
	; вызов функции WriteConsoleA для вывода строки STRN
CALL lstrlenA@4
	; в стек помещается 5-й параметр
PUSH 0
	; 4-й параметр
PUSH OFFSET LENS
	; 3-й параметр
PUSH EAX
	; 2-й параметр
PUSH OFFSET STRN
	; 1-й параметр
PUSH DOUT
	; ввод строки
CALL WriteConsoleA@20
	; в стек помещается 5-й параметр
PUSH 0
	; 4-й параметр
	; обратите внимание: LENS больше числа введенных
	; символов на два, дополнительно введенные символы: 13 – возврат каретки и 
	; 10 – переход на новую строку
	; вывод полученной строки
PUSH OFFSET LENS
	; 3-й параметр
PUSH 200
	; 2-й параметр
PUSH OFFSET BUF
	; 1-й параметр
PUSH DIN
CALL ReadConsoleA@20 
PUSH 0
PUSH OFFSET LENS
	; длина вводимой строки
PUSH LENS
PUSH OFFSET BUF
PUSH DOUT
CALL WriteConsoleA@20
	; вывод числа 123 в буфер BUF
PUSH 123
PUSH OFFSET FMT
PUSH OFFSET BUF
CALL wsprintfA
	; очистка стека от параметров (изменение регистра ESP 
	; на 3*4 = 12 байтов)
ADD	ESP, 12
	; вывод строки с числом 123
PUSH 0
PUSH OFFSET LENS
PUSH EAX
PUSH OFFSET BUF
PUSH DOUT
	; небольшая задержка
CALL WriteConsoleA@20
	; помещение в регистр ECX – счетчик цикла –
	; большого значения
MOV ECX,03FFFFFFFH
	; цикл без тела
L1: LOOP L1
	; выход из программы
	; параметр: код выхода
PUSH 0
CALL ExitProcess@4
	; завершение описания процедуры с именем MAIN
MAIN ENDP
	; завершение описания модуля с указанием первой выполняемой процедуры
END MAIN
