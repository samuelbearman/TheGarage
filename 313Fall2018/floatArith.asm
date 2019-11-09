; floatArith.asm   
;
; compile  nasm -f elf64 -l floatArith.lst  floatArith.asm 
; link     gcc -o floatArith  floatArith.o
; run      ./floatArith
;
; the output from running fltarith and fltarithc is:    
; c=5.0, a=3.000000e+00, b=4.000000e+00, c=5.000000e+00
; c=a+b, a=3.000000e+00, b=4.000000e+00, c=7.000000e+00
; c=a-b, a=3.000000e+00, b=4.000000e+00, c=-1.000000e+00
; c=a*b, a=3.000000e+00, b=4.000000e+00, c=1.200000e+01
; c=c/a, a=3.000000e+00, b=4.000000e+00, c=4.000000e+00
; a=i  , a=8.000000e+00, b=1.600000e+01, c=1.600000e+01
; a<=b , a=8.000000e+00, b=1.600000e+01, c=1.600000e+01
; b==c , a=8.000000e+00, b=1.600000e+01, c=1.600000e+01
;The file  fltarith.c  is:
;  #include <stdio.h>
;  int main()
;  { 
;    double a=3.0, b=4.0, c;
;    long int i=8;
;
;    c=5.0;
;    printf("%s, a=%e, b=%e, c=%e\n","c=5.0", a, b, c);
;    c=a+b;
;    printf("%s, a=%e, b=%e, c=%e\n","c=a+b", a, b, c);
;    c=a-b;
;    printf("%s, a=%e, b=%e, c=%e\n","c=a-b", a, b, c);
;    c=a*b;
;    printf("%s, a=%e, b=%e, c=%e\n","c=a*b", a, b, c);
;    c=c/a;
;    printf("%s, a=%e, b=%e, c=%e\n","c=c/a", a, b, c);
;    a=i;
;    b=a+i;
;    i=b;
;    c=i;
;    if(a<b) printf("%s, a=%e, b=%e, c=%e\n","a<=b ", a, b, c);
;    else    printf("%s, a=%e, b=%e, c=%e\n","a>b  ", a, b, c);
;    if(b==c)printf("%s, a=%e, b=%e, c=%e\n","b==c ", a, b, c);
;    else    printf("%s, a=%e, b=%e, c=%e\n","b!=c ", a, b, c);
;    return 0;
; }


%define SYSCALL_EXIT  60


extern printf                               ; the C function to be called

    
    SECTION  .data                          ; preset constants, writeable
a:     dq    3.0                            ; 64-bit variable a initialized to 3.0
b:     dq    4.0                            ; 64-bit variable b initializes to 4.0
i:     dq    8                              ; a 64 bit integer
five:  dq    5.0                            ; constant 5.0

msg1:  db "c=5.0",0                         ; operation 1
msg2:  db "c=a+b",0                         ; operation 2
msg3:  db "c=a-b",0                         ; operation 3
msg4:  db "c=a*b",0                         ; operation 4
msg5:  db "c=c/a",0                         ; operation 5
msg6:  db "a<=b ",0                         ; operation 6
msg7:  db "a>b  ",0                         ; operation 7
msg8:  db "b==c ",0                         ; operation 8
msg9:  db "b!=c ",0                         ; operation 9

fmt:   db "%s, a=%e, b=%e, c=%e",10,0       ; format string for printf
    
    SECTION .bss                            ; unitialized space
c:  resq    1                               ; reserve a 64-bit word

    SECTION .text                           ; instructions, code segment
    global  main                            ; for gcc standard linking

main:                                       ; label

    push   rbp                              ; Align stack by pushing in 8 bytes
lit5:                                       ; c=5.0;
    fld    qword [five]                     ; 5.0 constant
    fstp   qword [c]                        ; store into c
    mov    rsi, msg1                        ; string passed to macro
    call   printFL                          ; Call Float print function    

    
addb:                                       ; c=a+b;
    fld    qword [a]                        ; load a (pushed on flt pt stack, st0)
    fadd   qword [b]                        ; floating add b (to st0)
    fstp   qword [c]                        ; store into c (pop flt pt stack)
    mov    rsi, msg2                        ; string passed to macro
    call   printFL                          ; Call Float print function
    
subb:                                       ; c=a-b;
    fld    qword [a]                        ; load a (pushed on flt pt stack, st0)
    fsub   qword [b]                        ; floating subtract b (to st0)
    fstp   qword [c]                        ; store into c (pop flt pt stack)
    mov    rsi, msg3                        ; string passed to macro
    call   printFL                          ; Call Float print function
    
mulb:                                       ; c=a*b;
    fld    qword [a]                        ; load a (pushed on flt pt stack, st0)
    fmul   qword [b]                        ; floating multiply by b (to st0)
    fstp   qword [c]                        ; store product into c (pop flt pt stack)
    mov    rsi, msg4                        ; string passed to macro
    call   printFL                          ; Call Float print function
    
diva:                                       ; c=c/a;
    fld    qword [c]                        ; load c (pushed on flt pt stack, st0)
    fdiv   qword [a]                        ; floating divide by a (to st0)
    fstp   qword [c]                        ; store quotient into c (pop flt pt stack)
    mov    rsi, msg5                        ; string passed to macro
    call   printFL                          ; Call Float print function

intflt:                                     ; a=i;
    fild   qword [i]                        ; load integer as floating point
    fst    qword [a]                        ; store the floating point (no pop)
    fadd   st0                              ; b=a+i; 'a' as 'i'  already on flt stack
    fst    qword [b]                        ; store sum (no pop) 'b' still on stack
    fistp  qword [i]                        ; i=b; store floating point as integer
    fild   qword [i]                        ; c=i; load again from ram (redundant)
    fstp   qword [c]

cmpflt:    
    fld    qword [b]                        ; into st0, then pushed to st1
    fld    qword [a]                        ; in st0
    fcomip st0,st1                          ; a compare b, pop a
    jg     cmpfl2
    mov    rsi, msg6                        ; string passed to macro
    call   printFL                          ; Call Float print function
    jmp    cmpfl3

cmpfl2:    
    mov    rsi, msg7                        ; string passed to macro
    call   printFL                          ; Call Float print function

cmpfl3:
    fld    qword [c]                        ; should equal [b]
    fcomip st0,st1
    jne    cmpfl4
    mov    rsi, msg8                        ; string passed to macro
    call   printFL                          ; Call C function    
    jmp    exit

cmpfl4:
    mov    rsi, msg9                        ; string passed to macro
    call   printFL                          ; Call C function
    jmp    exit

printFL:
    push   rbp                              ; Align stack by pushing in 8 bytes
    
    mov    rdi, fmt                         ; address of format string
    movq   xmm0, qword [a]                  ; first floating point in fmt
    movq   xmm1, qword [b]                  ; second floating point
    movq   xmm2, qword [c]                  ; third floating point
    mov    rax, 3                           ; 3 floating point arguments to printf
    call   printf                           ; Call C function    
    
    pop    rbp                              ; pop out stack alignment frame
    ret

;; The final part of the program must be a call to the operating system to exit
;;; the program.
exit:
    pop    rbp                              ; pop out stack alignment frame
    mov    rdi,0                            ;successful termination of program
    mov    rax, SYSCALL_EXIT                ;system call number (sys_exit)
    syscall                                 ;call kernel
