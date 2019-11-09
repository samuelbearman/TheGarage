; File: textSearch.asm
;
; This program demonstrates the use of an indexed addressing mode
; to access data within a record
;
; Assemble using NASM:  nasm -f elf64 textSearch.asm
; Link with ld:  ld textSearch.o -o textSearch
;

%define STDIN         0
%define STDOUT        1
%define SYSCALL_EXIT  60
%define SYSCALL_READ  0
%define SYSCALL_WRITE 1
%define BUFLEN        100

        SECTION .data                                   ; Data section
msg1:   db "Enter search string: "                      ; user prompt
len1:   equ $-msg1                                      ; length of message

msg2:   db 10, "Read error", 10                         ; error message
len2:   equ $-msg2                                      ; length of error message

msg3a:  db "Text you searched, appears at  "            ; String found message
len3a:  equ $-msg3a                                     ; length of message

msg3b:	db " characters after the first."               ; Remainder of string found message
len3b:	equ $-msg3b					; length of message

msg4:   db "String not found!", 10                      ; string not found message
len4:   equ $-msg4                                      ; length of message

endl:	db 10						; Linefeed

                                                        ; simulates a text file (record)
record:
row1:   db "Knight Rider a shadowy flight"
row2:   db "into the dangerous world of a"
        db " man who does not exist. Mich"
        db "ael Knight, a young loner on "
        db "a crusade to champion the cau"
        db "se of the innocent, the innoc"
        db "ent, the helpless in a world "
        db "of criminals who operate abov"
        db "e the law. Knight Rider, Keep"
        db " riding brave into the night."
rlen:   equ $-record
rowlen: equ row2 - row1

        SECTION .bss                                    ; uninitialized data section
buf:    resb BUFLEN                                     ; buffer for read
loc:    resb BUFLEN                                     ; buffer to store found location string
count:  resb 4                                          ; reserve storage for user input bytes

        SECTION .text                                   ; Code section.
        global _start
_start: nop                                             ; Entry point.

                                                        ; prompt user for input
                                                        ;
        mov rax, SYSCALL_WRITE                          ; write function
        mov rdi, STDOUT                                 ; Arg1: file descriptor
        mov rsi, msg1                                   ; Arg2: addr of message
        mov rdx, len1                                   ; Arg3: length of message
        syscall                                         ; 64-bit system call

                                                        ; read user input
                                                        ;
        mov rax, SYSCALL_READ                           ; read function
        mov rdi, STDIN                                  ; Arg1: file descriptor
        mov rsi, buf                                    ; Arg2: addr of message
        mov rdx, BUFLEN                                 ; Arg3: length of message
        syscall                                         ; 64-bit system call

                                                        ; error check
                                                        ;
        mov [count], rax                                ; save length of string read
        cmp rax, 0                                      ; check if any chars read
        jg  read_OK                                     ; >0 chars read = OK
        mov rax, SYSCALL_WRITE                          ; Or Print Error Message
        mov rdi, STDOUT                                 ; Arg1: file descriptor
        mov rsi, msg2                                   ; Arg2: addr of message
        mov rdx, len2                                   ; Arg3: length of message
        syscall                                         ; 64-bit system call
        jmp     exit                                    ; skip over rest

read_OK:                                                ; Input was accepted, now initialize

init:
        mov rcx, 0                              
        sub rax, 1
        mov r8, 291
        sub r8, rax
        mov rax, buf
        mov rdx, 0
        mov r13, [count]
        dec r13

outerLoop:
        cmp rcx, r8
        je nope
        mov rdx, 0 

innerLoop:
        cmp rdx, r13
        je  found
        mov al, [rdx+buf] 
        mov bl, [rdx+rcx+record]
        cmp al, bl
        jne innerLoopDone
        inc rdx
        jmp innerLoop

innerLoopDone:
        inc rcx
        jmp outerLoop


found:                                                  ; If string was found print location

                                                        ; Following is a snippet of code for
                                                        ; printing out the digits of a number if its more 
                                                        ; than one digit long
        mov     r10, 1                                  ; Keeps track of the number of digits to be printed
        mov     rdi, loc                                ; Store the address of location buffer
        mov     rax, rcx                                  ; Lets assume, that the location found 
                                                        ; was 212 characters from the first character
        mov     cl, 10                                  ; Print out its digits using a loop
        cmp     ax, 9                                   ; Is the number larger than a single digit?
        jg      digits                                  ; if so, jump to store the digits routine
        mov     rbx, rax                                ; Copy the value into rbx (Used later by a shifting out routine)
        add     bl, '0'                                 ; Add the ASCII character offset for numbers
        jmp     shOut                                   ; Shift out routine

digits:	div	cl                                      ; Divide by 10  (212/10 , Quotient (AH) - 21, Remainder (AL) - 2)
                                                        ; ... On the first iteration of this loop                          
	mov	bl, ah                                  ; Store the remainder in bl
	add	bl, '0'                                 ; Add the ASCII character offset for numbers
	shl	rbx, 8                                  ; Shift left the character, so that they can be shifted out in reverse 
	and 	ax, 0x00FF                              ; Clear out the remainder from the result
	inc	r10                                     ; R10 keeps track of the number of digits
	cmp	al, 0                                   ; See if we have any more digits to convert
	jnz	digits                                  ; If there are more, keep looping

shOut:
	mov	[rdi], bl                               ; move the first digit (now a character) into destination
	inc	rdi                                     ; update to next character position
	shr	rbx, 8                                  ; Shift out the next digit
	cmp	bl, 0                                   ; Check to see if we have shifted out all digits
	jnz	shOut                                   ; More digits? Keep looping

        mov rax, SYSCALL_WRITE                          ; Print Message
        mov rdi, STDOUT                                 ; Arg1: file descriptor
        mov rsi, msg3a                                  ; Arg2: addr of message
        mov rdx, len3a                                  ; Arg3: length of message
        syscall                                         ; 64-bit system call


        mov rax, SYSCALL_WRITE                          ; Write out location information
        mov rdi, STDOUT                                 ; Arg1: file descriptor
        mov rsi, loc                                    ; Arg2: addr of message
        mov rdx, r10                                    ; Arg3: length of message
        syscall                                         ; 64-bit system call

        mov rax, SYSCALL_WRITE                          ; Print remainder of Message
        mov rdi, STDOUT                                 ; Arg1: file descriptor
        mov rsi, msg3b                                  ; Arg2: addr of message
        mov rdx, len3b                                  ; Arg3: length of message
        syscall                                         ; 64-bit system call

        mov rax, SYSCALL_WRITE                          ; Write out string
        mov rdi, STDOUT                                 ; Arg1: file descriptor
        mov rsi, endl                                   ; Arg2: addr of message
        mov rdx, 1                                      ; Arg3: length of message
        syscall                                         ; 64-bit system call

        jmp exit

nope:                                                   ; String not found message
                                                        ;
        mov rax, SYSCALL_WRITE                          ; Print Message
        mov rdi, STDOUT                                 ; Arg1: file descriptor
        mov rsi, msg4                                   ; Arg2: addr of message
        mov rdx, len4                                   ; Arg3: length of message
        syscall                                         ; 64-bit system call


exit:   mov rax, SYSCALL_EXIT                           ; exit system call id
        mov rdi, 0                                      ; exit to shell
        syscall
