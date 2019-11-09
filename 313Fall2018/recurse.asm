; File: recursive.asm
;
; example of subroutines in assembly language.

%define STDOUT 1
%define SYSCALL_EXIT  60
%define SYSCALL_WRITE 1

        SECTION .data                   ; initialized data section

msg1:   db "Hello World", 10, 0         ; C-style \0 terminated string

msg2:   db 10, "Good-bye, blue sky", 10, 0

char:   db 0, 0                         ; single char followed by \0


        SECTION .text                   ; Code section.
        global  _start                  ; let loader see entry point

_start: nop                             ; Entry point.
pstart:                                 ; address for gdb

        mov     rdi, msg1               ; print first string
        mov     rax, 0                  ; No XMM registers
        call    print

        mov     al, '5'
        call    recurse

        mov     rdi, msg2               ; print second string
        mov     rax, 0                  ; No XMM registers
        call    print


        ; final exit
        ;
pexit:  mov     rax, SYSCALL_EXIT       ; exit function
        mov     rdi, 0                   ; exit to shell
        syscall


; A recursive subroutine
; counts down to '0'
; parameter stored in register al

recurse:
        cmp     al, '0'                 ; don't go below '0'
        jae     rcont   
        ret                             ; go back       

rcont:  push    ax                      ; save al 
        dec     al                      ; param for recursive call
        call    recurse                 ; recursively count down
        pop     ax                      ; restore count 
        mov     [char], al              ; prepare string for printing
        mov     rdi, char               ; parameter for print subroutine
        mov     rax, 0                  ; No XMM registers
        call    print
        ret


; Subroutine print
; writes null-terminated string with address in rdi
;
print:
        ; find \0 character and count length of string
        ;
        mov     rax, rdi                ; save rdi in rax
        mov     rdx, 0                  ; initialize count

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
