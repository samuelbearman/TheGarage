; File: twopass.asm
;
; Demonstrating a two-pass assembler

        section .data
x:      db      87h
y:      dw      1492h
zalias: equ $
z:      dd      17762001h

calc:   equ (x-y)*2
x4:     equ x+1

        section .text
        global _start

_start: mov     eax, [zalias]
        mov     bx, [y]
        mov     cx, [x4]
        cmp     bx, cx
        jne     error

OK:     add     ax, bx
        mov     [x], al
        mov     rdi, 0          ; no error

done:   
        mov     rax, 60         ; syscall number for exit
        syscall

error:  mov     rdi, 17         ; abnormal exit
        jmp     done


