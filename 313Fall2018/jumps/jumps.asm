;File: jumps.asm
;
;Demonstrating near and short jumps
;

	SECTION .text
	global _start
_start: nop
	;initialize
start:	mov rax,17	; rax = 17
	cmp rax,42	; 17-42 is

	jge exit	; exit if 17 >= 42
	jge short exit
	jge near exit

	jmp exit
	jmp short exit
	jmp near exit

exit:	mov rdi,0	; exit code, 0=normal
        mov rax,60	; exit system routine
	syscall		; call kernel