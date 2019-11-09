; External functions
extern _printf

; Global functions
global	getMessageLength
global	alterMessage
global	printMessage
global	_main

; Global variables
section .data
message:
	db "abcd", 0

; Code
section .text

getMessageLength:
	push	ebp
	mov		ebp,	esp			; setup a stack frame
	
	mov		eax,	message		; store address of message into eax (caller saved, so we are allowed to modify it)
	jmp		getMessageLength_loop2
	getMessageLength_loop:
	add		eax,	1			; next character
	getMessageLength_loop2:
	cmp		[eax],	byte 0		; is dereferenced character at eax the string's NULL truncator?
	jnz		getMessageLength_loop
	
	sub		eax,	message		; subtract message from eax to get the difference from the byte that was 0 and the start (string length)
	leave						; restore the stack back to how it was
	ret							; returns with message length in eax

alterMessage:
	push	ebp
	mov		ebp,	esp			; setup a stack frame
	
	mov		ecx,	message		; store address of message into ecx
	call	getMessageLength
	add		eax,	ecx			; eax holds the end of the message
	
	alterMessage_loop:
	mov		bl,		byte [ecx]	; bl (lowest byte of ebx) will hold the dereferenced byte at ecx
	add		bl,		1			; add one to this
	mov		[ecx],	byte bl		; put the modified character back into memory at location ecx
	
	add		ecx,	1			; go to the next character
	cmp		ecx,	eax
	jnz		alterMessage_loop	; if we have not reached the final character, repeat
	
	leave						; restore the stack back to how it was
	ret

printMessage:
	push	ebp
	mov		ebp,	esp			; save the stack before calling a function with arguments
	
	mov		eax,	message		; put address of message into eax (because we can't directly put it into the stack)
	;lea		eax, [message]	; equivalent to the above opcode
	mov		[esp],	eax			; put eax into dereferenced stack pointer (first parameter for an int or pointer)
	call	_printf
	
	;add esp, 4					; equivalent to below opcode (in this situation)
	leave						; restore the stack back to how it was
	ret

_main:
	call	alterMessage
	call	printMessage
	
	mov		eax,	0
	ret							; return 0
