; File: bookcmp.asm
;
;Defines the bookcmp subroutine for use by the sort algorithm in sort_books.c
;
    
%define TITLE_OFFSET 0               ; Offset for title
%define AUTHOR_OFFSET 41             ; Offset for author
%define YEAR_OFFSET 64               ; Offset for year

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

    push rbx                         ; push to preserve rbx
    push rcx                         ; push to preserve rcx

    mov  ebx, dword [rdi + YEAR_OFFSET] ;load book1's Year into ebx
    mov  ecx, dword [rsi + YEAR_OFFSET] ;load book2's Year into ecx

    cmp ebx, ecx                        ;If book1 is greater jump, if less
    jne cmpDone

compareTitle:

    xor rdx, rdx                        ; Zero out rdx
    mov rdx, 0                          ; Move zero into rdx for incrementing

L1:
    xor rbx, rbx                        ; Zero out rbx
    xor rcx, rcx                        ; Zero out rcx

    mov ebx, dword [rdi + rdx + TITLE_OFFSET] ;letter of book1's title
    mov ecx, dword [rsi + rdx + TITLE_OFFSET] ;letter of book2's title 
  
     
    cmp bl, cl                          ; compare chars
    jg  L_gt                            ; if book1 char is greater jump to L_gt
    jl  L_lt                            ; if book1 char is less jump to L_lt
 
    inc rdx                             ; increment for next char
    jmp L1                              ; jump to loop around
   


cmpDone: 
    mov eax, -1
    jmp end 

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
