%define STDOUT 1
%define SYSCALL_EXIT  60
%define SYSCALL_WRITE 1

    SECTION .data
;;; Here we declare initialized data. For example: messages, prompts,
;;; and numbers that we know in advance

gapString:      db "=========", 10
gapStringLen:   EQU $-gapString

; List of tests to be executed. Do not modify the values below
test1:          dq 6.01
test2:          dq 4.52
test3:          dq 8.90
test4:          dq 0.01
test5:          dq 5.34
test6:          dq 10.01
test7:          dq 7.43
test8:          dq 8.01
test9:          dq 9.01
test10:         dq 7.01

    SECTION .bss
;;; Here we declare uninitialized data. We're reserving space (and
;;; potentially associating names with that space) that our code
;;; will use as it executes. Think of these as "global variables"

    SECTION .text
;;; This is where our program lives.
global _start                                ; make start global so ld can find it
extern authorsForPrice

printGap:
        push rax
        push rbx
        push rcx
        push rdx

        mov rax, SYSCALL_WRITE
        mov rdi, STDOUT
        mov rsi, gapString
        mov rdx, gapStringLen
        syscall

        pop rdx
        pop rcx
        pop rbx
        pop rax
        ret

_start:                         ; the program actually starts here
                                ; comment out tests if you do not wish to run them all
        ;test1 
        fld qword [test1]       ; load st0, make sure this value is popped off the FPU stack on return
        call authorsForPrice
        call printGap

        ;test2
        fld qword [test2]       ; load st0
        call authorsForPrice
        call printGap

        ;test3 
        fld qword [test3]       ; load st0
        call authorsForPrice
        call printGap
        
        ;test4 
        fld qword [test4]       ; load st0
        call authorsForPrice
        call printGap

        ;test5 
        fld qword [test5]       ; load st0
        call authorsForPrice
        call printGap

        ;test6 
        fld qword [test6]       ; load st0
        call authorsForPrice
        call printGap

        ;test7 
        fld qword [test7]       ; load st0
        call authorsForPrice
        call printGap
        
        ;test8 
        fld qword [test8]       ; load st0
        call authorsForPrice
        call printGap

        ;test9
        fld qword [test9]       ; load st0
        call authorsForPrice
        call printGap
        
        ;test10
        fld qword [test10]       ; load st0
        call authorsForPrice
        call printGap
        

        ;; call sys_exit to finish things off
exit:   mov     rax, SYSCALL_EXIT       ; exit function
        mov     rdi, 0                  ; exit to shell
        syscall
