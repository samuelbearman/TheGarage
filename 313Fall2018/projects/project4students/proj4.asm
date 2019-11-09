;;; layout of the structure
%define TITLE_OFFSET 0
%define AUTHOR_OFFSET 48
%define PRICE_OFFSET 96
%define YEAR_OFFSET 104
%define NEXT_OFFSET 112

;;; our usual system call stuff
%define STDOUT 1
%define SYSCALL_EXIT  60
%define SYSCALL_WRITE 1

    SECTION .data
;;; Here we declare initialized data. For example: messages, prompts,
;;; and numbers that we know in advance

newline:        db 10

    SECTION .bss
;;; Here we declare uninitialized data. We're reserving space (and
;;; potentially associating names with that space) that our code
;;; will use as it executes. Think of these as "global variables"

    SECTION .text
;;; This is where our program lives.
global _start                               ; make start global so ld can find it
extern library
global authorsForPrice

printNewline:
        push rax
        push rbx
        push rcx
        push rdx
        push rsi

        mov rax, SYSCALL_WRITE
        mov rdi, STDOUT
        mov rsi, newline
        mov rdx, 1
        syscall

        pop rsi
        pop rdx
        pop rcx
        pop rbx
        pop rax
        ret

;;; rax should point to the string. on return, rax is the length
stringLength:
;;; Students: Feel free to use this code in your submission but you
;;; must add comments explaining the code to prove that you
;;; know how it works.

        push rsi
        mov rsi, rax
        mov rax, 0

loopsl:
        cmp [rsi], byte 0
        je endsl

        inc rax
        inc rsi
        jmp loopsl

endsl:
        pop rsi
        ret

;;; this label will be called as a subroutine by the code in driver.asm
authorsForPrice:
        ;; protect the registers we use
        
        push rax
        push rbx
        push rcx
        push rdx
        push rsi

        ;; print the first author in the library
        mov rsi, [library]
        
printName:

        lea rax, [rsi + AUTHOR_OFFSET]  ; Load-Effective-Address computes the address in
                                        ; the brackets and returns it instead of looking it up.

        call stringLength               ; after this, RAX will have the length of the author name

        mov rdx, rax                    ; copy it to the count register for the system call
        mov rax, SYSCALL_WRITE
        mov rdi, STDOUT
        lea rcx, [rsi + AUTHOR_OFFSET]
        push rsi                        ; preserve RSI
        mov rsi, rcx
        syscall

        pop rsi                         ; restore RSI

        call printNewline
        
cleanUp:
        fstp st0                        ; pop off top of stack

        pop rsi
        pop rdx
        pop rcx
        pop rbx
        pop rax
        
        ret
