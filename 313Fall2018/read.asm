; reads four characters of input from stdin and prints it out
; beware of buffer overflows!
; nasm -f el64 read.asm
; ld -o read read.o

%define STDIN         0
%define STDOUT        1
%define SYSCALL_EXIT  60
%define SYSCALL_READ  0
%define SYSCALL_WRITE 1
%define BUFLEN        4
%define LF            10

        SECTION .bss
buf:    resb BUFLEN                  ; reserve buffer having BUFLEN bytes
count:  resd 1                       ; reserve storage for user input bytes

        SECTION .text
        global _start

_start: nop                          ; begin here

reread: mov rax, SYSCALL_READ        ; read function
        mov rdi, STDIN               ; Arg1: file descriptor
        mov rsi, buf                 ; Arg2: addr of message
        mov rdx, BUFLEN              ; Arg3: length of message
        syscall                      ; 64-bit system call
            
        mov [count], rax             ; save count for later
        cmp rax, 0                   ; check if any chars read
        je  exit                     ; No chars read, exit

                                     ; print what we got from sys_read
        mov rax, SYSCALL_WRITE       ; write function
        mov rdi, STDOUT              ; Arg1: file descriptor
        mov rsi, buf                 ; Arg2: addr of message
        mov rdx, [count]             ; Arg3: length of message
        syscall                      ; 64-bit system call

                                     ; if the last byte we printed is a linefeed, we're done
                                     ; if not, there must be more to read
        cmp byte [rsi + rdx - 1], LF ; compare to linefeed
        jne reread

exit:   mov rax, SYSCALL_EXIT
        mov rdi, 0                   ; exit to shell
        syscall