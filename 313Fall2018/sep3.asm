; File: sep3.asm
;
; File 3 for separate compilation example

extern _start, add_these

	section .data

lvar1:	dd	03h	; same name as other lvar1, OK

	section .text
test3:				; no regs altered!
	cmp	[lvar1], dword 7
	jne	_start
	jmp	add_these
