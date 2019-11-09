; GPR tranfers
; Assemble using NASM
;
        SECTION .text                   ; Code section.
        global _start
_start: nop                             ; Entry point.
        mov     rax, 1                  ; rax register
        mov     rbx, 0xA000000000000002 ; rbx register
        mov     rcx, 3                  ; rcx register
        mov     rdx, 4                  ; rdx register
        mov     rsi, 5                  ; rsi register
        mov     rdi, 6                  ; rdi register
        mov     rbp, 7                  ; rbp register
        mov     rsp, 8                  ; rsp register
        mov     r8,  9                  ; r8 register
        mov     r9,  10                 ; r9 register
        mov     r10, 11                 ; r10 register
        mov     r11, 12                 ; r11 register
        mov     r12, 13                 ; r12 register
        mov     r13, 14                 ; r13 register
        mov     r14, 15                 ; r14 register
        mov     r15, 16                 ; r15 register

        mov     rbx, 0                  ; exit code, 0=normal
        mov     rax, 60                 ; Exit.
        syscall                         ; Call kernel.