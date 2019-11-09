; File: rep.asm
; 
; Demonstrates the use of the REP prefix with
; string instructions.
;
; This program does no I/O. Use gdb to examine its effects.
;
%define SYSCALL_EXIT  60

	SECTION	.data			        ; Data section

msg:	db "Hello, world", 10		; The string to print.
len: 	equ $-msg

	SECTION .text			; Code section.
	global _start
_start: nop				    ; Entry point.

find:	mov	al, 'o'			; look for an 'o'
		mov	rdi, msg		; here
		mov	rcx, len		; limit repetitions
		cld				    ; auto inc rdi
		repne scasb			; while (al != [rdi])
		jnz	not_found		; 
		mov	bl, [rdi-1]		; what did we find?
not_found:

erase:	mov	rdi, msg		; where?
		mov	rcx, len		; how many bytes?
		mov	al, '?'			; with which char?
		cld				    ; auto inc rdi
		rep stosb

exit:   mov rax, SYSCALL_EXIT       ; exit function
        mov rdi, 0                  ; exit to shell
        syscall

