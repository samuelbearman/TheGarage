; Convert user input to hexadecimal number.
;
; Assemble using NASM:  nasm -f elf64 hexConverter.asm
; Compile with gcc:     gcc hexConverter.o cfunc.c -o converter.out
;

%define STDIN         0
%define STDOUT        1
%define SYSCALL_EXIT  60
%define SYSCALL_READ  0
%define SYSCALL_WRITE 1
%define BUFLEN 		  21


        SECTION .data                   ; initialized data section

msg1:   db "Enter Number: "             ; user prompt
len1:   equ $-msg1                      ; length of first message

msg2:   db "Invalid Input!", 10         ; error message
len2:   equ $-msg2

msg3:   db "Hexadecimal value is: "     ; Feedback
len3:   equ $-msg3

msg4:   db 10      						; Linefeed
len4:   equ $-msg4

        SECTION .bss                 ; uninitialized data section
buf:    resb BUFLEN                  ; buffer for read
newstr: resb BUFLEN                  ; converted string
count:  resb 4                       ; reserve storage for user input bytes

        SECTION .text                ; Code section.
        global  main                 ; let gcc see entry point        
        extern printhex				 ; This routine is defined in the c function
        extern printf				 ; This routine will be utilized in the c function

main:	nop                          ; Entry point.
start:                               ; address for gdb

        ; prompt user for input
        ;
        mov rax, SYSCALL_WRITE       ; write function
        mov rdi, STDOUT              ; Arg1: file descriptor
        mov rsi, msg1                ; Arg2: addr of message
        mov rdx, len1                ; Arg3: length of message
        syscall                      ; 64-bit system call

        ; read user input
        ;
        mov rax, SYSCALL_READ        ; read function
        mov rdi, STDIN               ; Arg1: file descriptor
        mov rsi, buf                 ; Arg2: addr of message
        mov rdx, BUFLEN              ; Arg3: length of message
        syscall                      ; 64-bit system call

        ; error check
        ;
        mov [count], rax             ; save length of string read
        cmp rax, 0                   ; check if any chars read
        jle invalid                  ; <=0 chars read = not valid

		cmp rax, 21					 ; check if 21 characters were read
		je	read_OK					 ; 21 characters read, we are good
		cmp rax, 20					 ; check if 20 characters were read
		je	read_OK					 ; 20 characters read, we are good

invalid:mov rax, SYSCALL_WRITE       ; Or Print Error Message
        mov rdi, STDOUT              ; Arg1: file descriptor
        mov rsi, msg2                ; Arg2: addr of message
        mov rdx, len2                ; Arg3: length of message
        syscall                      ; 64-bit system call
        jmp     exit                 ; skip over rest


init:
									 ; printout the precursor message
		mov rax, SYSCALL_WRITE       ; Print Message
        mov rdi, STDOUT              ; Arg1: file descriptor
        mov rsi, msg3                ; Arg2: addr of message
        mov rdx, len3                ; Arg3: length of message
        syscall                      ; 64-bit system call

read_OK:

initialize:
        xor rax, rax                 ; zero out registers
        xor rcx, rcx
        xor rbx, rbx
        xor rdx, rdx
        xor r8, r8
        mov rbx, 10                  ; 10 for multiplier 
        mov rsi, buf                 ; hold position of input 
        mov r14, [count]             ; hold length of input
        sub r14, 2                   ; decrement counter by 2
    
convertInputToDigits:
   
        cmp rcx, r14                ; if counter equal to length of message
        je lastDigit                ; jump to last digit
        xor rax, rax                ; zero out rax
        mov al, [rsi+rcx]           ; get current char
        cmp al, '9'                 ; make sure it is a number char
        jg invalid
        cmp al, '0'
        jl invalid
        sub al, 0x30                ; convert to proper number
        add r8, rax                 ; add tha number to r8
        mov rax, r8                 ; mov numb back to rax
        mul rbx                     ; mutiply number by 10 
        mov r8, rax                 ; mov it back into r8
        inc rcx                     ; increment counter
        jmp convertInputToDigits    ; jump back to top of loop


lastDigit:
    
        xor rax, rax                ; zero out rax
        mov al, [rsi+rcx]           ; get last didgit
        cmp al, '9'                 ; make sure it is a number char
        jg invalid
        cmp al, '0'
        jl invalid
        sub al, 0x30                ; convert
        add r8, rax                 ; add to r8 register
        mov rdx, r8                 ; mov r8 register to rdx




        xor rcx, rcx                ; zero out counter
        xor r8, r8                  ; zero out r8
        mov rax, rdx                ; mov new number into rax

convertToHex:
        
        cmp rcx, r14                ; if rcx equals length of string
        je exit                     ; exit
        xor rdx, rdx                ; zero rdx
        mov rbx, 16                 ; mov 16 to rbx for divisor
        div rbx                     ; divide  
        cmp rdx, 9                  ; figure out if its a letter or number
        jge letter
        add rdx, 48
        mov rdi, rdx
        push rax
        push rcx
        call printhex               ; call printhex to print hex number
        pop rcx
        pop rax
        inc rcx                     ; increment counter
        jmp convertToHex            ;


letter:
        add rdx, 55
        mov rdi, rdx
        push rax
        push rcx
        call printhex
        pop rcx
        pop rax
        inc rcx
        jmp convertToHex


        ; final exit
        ;
exit:   mov 	rax, SYSCALL_EXIT
        mov 	rdi, 0               ; exit to shell
        syscall

