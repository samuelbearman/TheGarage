; File: sep2.asm
;
; File 2 for separate compilation example

global gvar2, add_these
extern gvar1

        section .data

bar:    dw      07h
gvar2:  dd      03h
lvar1:  dd      02h     ; same name as other lvar1, OK

        section .text
add_these:                              ; no regs altered!
        mov     [gvar1], dword 0        ; clear destination
        add     [gvar1], eax
        add     [gvar1], ebx
        add     [gvar1], ecx
        ret
