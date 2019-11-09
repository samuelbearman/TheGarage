
;
; Assemble using NASM
;
        SECTION .data                   ; Data section

msg:    db "Hello, world", 10           ; The string to print.
len:    equ $-msg

        SECTION .text                   ; Code section.
        global _start
_start: nop                             ; Entry point.
        mov     rdx, len                ; Arg 3: length of string.
        mov     rsi, msg                ; Arg 2: pointer to string.
        mov     rdi, 1                  ; Arg 1: file descriptor.
        mov     rax, 1                  ; Write.
        syscall

        mov     rdi, 0                  ; exit code, 0=normal
        mov     rax, 60                  ; Exit.
        syscall
        
