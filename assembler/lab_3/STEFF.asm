.386
.MODEL FLAT
EXTERN _ROOT:DWORD

.DATA
X DD ? ;0.8
TX DD ?
FX DD ?
OLDFX DD ?
A DD 0.1
B DD 0.55

.CODE
; args: ST(0) -- x
; ret:	ST(0) -- founded root
FUNC PROC
	 ; tg(0.55 * x + 0.1) – x^2 
	 ; in postfix notation:
	 ; 0.1 0.55 x * + tg() x x * -
	 FLD A
	 FLD B
	 FLD X
	 FMULP
	 FADDP
	 FPTAN
	 FSTP ST
	 FLD X
	 FLD X
	 FMULP
	 FSUBP
	 FSTP FX
	RET
FUNC ENDP

STEP PROC
	; x – f(x) * f(x) / (f(x + f(x)) – f(x))
	; in postfix notation:
	; x fx fx * - x fx + f() fx - /
	; x fx fx * x fx + f() fx - / -
	FLD X
	FLD FX
	FLD FX
	FMULP
	FLD X
	FLD FX
	FADDP
	; save all needed regs in stack
	; should save vars before function call
	PUSH X
	; load new value to x equal to (x + f(x))
	FSTP X
	PUSH FX
	CALL FUNC
	FLD FX
	; restore var values
	POP FX
	POP X
	FLD FX
	FSUBP
	FDIVP
	FSUBP
	FSTP X
	RET
STEP ENDP

; args:	ECX -- number of iterations to do
;		EDX -- init condition
; ret:	_ROOT -- founded root
@STEFF@8 PROC
	PUSH EBP
	MOV EBP, ESP
	MOV EAX, [EBP] + 8
	MOV X, EAX
	FINIT
	CONT:
		CALL FUNC
		CALL STEP
	LOOP CONT
	PUSH EAX
	MOV EAX, X
	MOV _ROOT, EAX
	POP EAX
	POP EBP
	RET 4
@STEFF@8 ENDP
END

; TODO: how to clear co-proc registers (a.k.a. circled stack)?