; File: subroutine.asm
;
; example of subroutines in assembly language.

%define STDOUT 1
%define SYSCALL_EXIT  60
%define SYSCALL_WRITE 1

        SECTION .data                   ; initialized data section

msg1:   db "Hello World", 10, 0         ; C-style \0 terminated string

msg2:   db "Good-bye, blue sky", 10, 0

msg3:	db "Value of RBP is: %x",10,0
msg4: 	db "Value addressed by RBP is: %x",10,0

        SECTION .text
        global main                     ; make start global so ld can find it
        extern myfunction
        extern printf

main:                                   ; this gets called from code in crt0
                                        ;; argc and argv are available on our stack$
pstart:                                 ; address for gdb
	mov	rbx, 10			; check to see if data is preserved
	mov	rax, 15			; check to see if data is preserved
        mov	rcx, 40
                                        ; printf
        mov rdi, rsp                    ; set first parameter (rsp)
        mov rsi, [rsp]                  ; set second parameter (value at rsp)
        mov rax, 0                      ; No XMM registers
        call myfunction                 ; call c routine
                                        ; printf
        mov rdi, rbp                    ; set first parameter (rbp)
        mov rsi, [rbp]                  ; set second parameter (value at rbp)
        mov rax, 0                      ; No XMM registers
        call myfunction                 ; call c routine

	mov     rdi, msg1               ; print first string
        call    print

        mov     rdi, msg2               ; print second string
        call    print

        ; final exit
        ;
pexit:  mov     rax, SYSCALL_EXIT       ; exit function
        mov     rdi, 0                  ; exit to shell
        syscall


; Subroutine print
; writes null-terminated string with address in rdi
;
print:
        ; find \0 character and count length of string
        ;
        push rdi                	; save rdi in stack
                                        ; printf
        mov rdi, rbp                    ; set first parameter (rbp)
        mov rsi, [rbp]                  ; set second parameter (value at rbp)
        mov rax, 0                      ; No XMM registers
        call myfunction                 ; call c routine

	pop	rdi
	mov	rax, rdi		; copy rdi into rax for printing out later
	mov	rdx, 0			; initialize count

count:  cmp     [rdi], byte 0           ; null char?
        je      end_count
        inc     rdx                     ; update index & count
        inc     rdi
        jmp     short count
end_count:

        ; make syscall to write
        ; rdx already has length of string
        ;
        mov rsi, rax                 ; Arg2: addr of message
        mov rax, SYSCALL_WRITE       ; write function
        mov rdi, STDOUT              ; Arg1: file descriptor
        syscall                      ; 64-bit system call
        ret                             

; end of subroutine

