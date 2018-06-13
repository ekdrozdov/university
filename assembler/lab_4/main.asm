.386
.MODEL FLAT
EXTERN  lstrlenA@4: PROC

TEXT DB 256 DUP (?)
STRING DB ?
CHAR DB

; "Hello, world!", 'l' -> "lHelo, world!"

PULLCH MACRO STRING:REQ CHAR:REQ
	; Find character in the string.
	; If character not found, terminate.
	; Remove it from string.
	; Add it to the beginning of the string.
ENDM