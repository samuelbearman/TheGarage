; File: bookcmp.asm
;
;Defines the bookcmp subroutine for use by the sort algorithm in sort_books.c
;
    
%define TITLE_OFFSET 0
%define AUTHOR_OFFSET 41
%define YEAR_OFFSET 64

        SECTION .text                ; Code section.
        global  bookcmp              ; let loader see entry point

bookcmp:
    push   rbp                       ; push the base pointer
    mov    rbp, rsp                  ; move stack pointer onto rbp (Prologue)

    push   rdi                       ; push registers we want to use
    push   rsi
        
    mov    rdi, [rbp - 8]            ; move first book into rdi
    mov    rsi, [rbp - 16]           ; move second book into rsi
                                     ; fetch the year field
                                     ; and compare the year field to book1's
                                     ; If they're different, do not sort, treat the titles as lexicographically equivalent
    push rbx
    push rcx

    mov  ebx, dword [rdi + YEAR_OFFSET] ;load book1's Year into ebx
    mov  ecx, dword [rsi + YEAR_OFFSET] ;load book2's Year into ecx

    cmp ebx, ecx                        ;If book1 is greater jump, if less
    jg  L_gt 
    jl  L_lt
    jmp compareTitle 

compareTitle:
    xor rdx, rdx
    mov rdx, 0

L1:
    xor rbx, rbx
    xor rcx, rcx

    mov ebx, dword [rdi + rdx + TITLE_OFFSET] ;letter of book1's title
    mov ecx, dword [rsi + rdx + TITLE_OFFSET] ;letter of book2's title 
   
    cmp bl, cl
    jl  L_lt 
    jg  L_gt
 
    inc rdx
    jmp L1
    
L_lt:
    mov    rax, -1                   ; book1 is strictly less than book2
    jmp    end
    
L_eq:    
    mov    rax, 0                    ; book1 equals book2
    jmp    end
    
L_gt:    
    mov    rax, 1                    ; book1 is strictly greater than book2

    ;; Clean up and finish
end:    

    pop    rcx
    pop    rbx
    pop    rsi                       ; clean up
    pop    rdi
    leave                            ; Sets RSP to RBP and pops off RBP (Epilogue)
    ret
