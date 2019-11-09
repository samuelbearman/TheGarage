; floatSimple.asm   
;
; compile  nasm -f elf64 -l floatSimple.lst  floatSimple.asm 
; link     gcc -o floatSimple  floatSimple.o
; run      ./floatSimple

%define SYSCALL_EXIT  60

extern printf

    SECTION .data
fnr1    dq    1.2
fnr2    dq    2.3
fnr3    dq     3.4
outstr    db    "%cResult is %e",10,0       ;%c is ignored here

    SECTION .bss

qnr1    resq    1

    SECTION .text
    global main                             ;must be declared for gcc

;; just like main in C -- if linking with gcc, must be main, otherwise does not have to.

main: 
                                            ;tell linker entry point
;; put your code here

    push    rbp                             ; Align stack by pushing in 8 bytes

    finit                                   ; Initialize the FPU and clear errors

    fld    qword [ fnr1 ]                   ; st0 :  1.19999999999999995559

    fld    qword [ fnr2 ]                   ; st0 :  2.29999999999999982236
                                            ; st1 :  1.19999999999999995559

    fadd    st0,st1                         ; st0 :  3.49999999999999977796
                                            ; st1 :  1.19999999999999995559

    fld    qword [ fnr3 ]                   ; st0 :  3.39999999999999991118
                                            ; st1 :  3.49999999999999977796
                                            ; st2 :  1.19999999999999995559

    fadd    st0,st1                         ; st0 :  6.89999999999999968914
                                            ; st1 :  3.49999999999999977796
                                            ; st2 :  1.19999999999999995559

    fstp    qword [ qnr1 ]                  ; st0 :  3.49999999999999977796
                                            ; st1 :  1.19999999999999995559


    mov     rdi,  outstr                    ; Format
    mov     rsi,  0                         ; Dummy data as second argument
    movq    xmm0, qword [ qnr1 ]            ; Need to use xmm registers for storing floaing point data
    mov     rax,  1                         ; Number of XMM registers
    call    printf                          ; Call printf

    pop     rbp                             ; pop out stack alignment frame

;; The final part of the program must be a call to the operating system to exit
;;; the program.
    
    mov     rdi,0                           ;successful termination of program
    mov     rax, SYSCALL_EXIT               ;system call number (sys_exit)
    syscall                                 ;call kernel
