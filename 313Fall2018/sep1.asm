; File: sep1.asm
;
; File 1 for separate compilation example

global gvar1, _start
extern gvar2, add_these

        section .data

foo:    db      12h
gvar1:  dd      17h
lvar1:  dd      42h

        section .text
_start: mov     eax, [gvar1]
        mov     ebx, [gvar2]
        mov     ecx, [lvar1]

        call    add_these       ; gvar1 := eax+ebx+ecx
        mov     ebx, [gvar1]    ; store in return code

        mov 	rdi, 0          ; no error
        mov     rax, 60         ; sycall number for exit
        syscall		            ; bye-bye
