; File: index2.asm
; 
; This program demonstrates the use of an indexed addressing mode
; to access array elements.
;
; This program has no I/O. Use the debugger to examine its effects.
;
	SECTION	.data			; Data section

arr:	dd 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ; ten 32-bit words
base:	equ arr - 4

	SECTION .text			; Code section.
	global _start
_start: nop				; Entry point.

	; Add 5 to each element of the array stored in arr. Simulate:
	;
	;  for (i = 0 ; i < 10 ; i++) {
	;     arr[i] += 5 ;
	;  }

init1:	mov	rcx, 0			; ecx simulates i
loop1:	cmp	rcx, 10			; i < 10 ?
		jge	done1
		add	[rcx*4+arr], dword 5	; arr[i] += 5
		inc	rcx				; i++
		jmp	loop1
done1:

	; more idiomatic for an assembly language program
init2:	mov	rcx, 9			; last array element's index
loop2:  add	[rcx*4+arr], dword 5 	
		dec	rcx
		jge	loop2			; again if ecx >= 0


	; another way 
init3:	mov	rdi, base		; base computed at load time
		mov	rcx, 10			; for(i=10 ; i>0 ; i--)
loop3:  add	[rdi+rcx*4], dword 5 	
		loop loop3			; loop = dec rcx, jne

alldone:
		mov	rdi, 0			; exit code, 0=normal
		mov	rax, 60			; Exit.
		syscall 			; Call kernel.
