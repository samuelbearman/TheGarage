	SECTION .data

Msg: db "The number is: %d",10,0

	SECTION .text
	global main                     ; make start global so ld can find it
	extern printf

main:                          		; this gets called from code in crt0
					;; argc and argv are available on our stack if we want them

        				;; printf("The number is: %d", 15);
        mov rdi, Msg			; set first parameter (format)
        mov rsi, 15			; set second parameter (number 15)
	mov rax, 0
        call printf

	mov rdi, 0
        mov rax, 60              	; exit
        syscall
