Project Description

************************************************************************
0. Files:
************************************************************************

Makefile	- Makes the binaries for the provided assembly file
ReadMe.txt	- This file
textSearch.asm	- The file you will be modifying and handing in
typescript  - If you have not met all test cases/code does not compile etc.
any other supporting files

List expected inputs/outputs

************************************************************************
1. Expected inputs/outputs
************************************************************************

Test 1

Enter search string: K

Text you search appears at  0 characters after the first.

Test 2

Enter search string: Rider

Text you search appears at  7 characters after the first.

Test 3

Enter search string: er,

Text you searched for, appears at  253 characters after the first.

Test 4

Enter search string: ht.

Text you searched for, appears at  287 characters after the first.

Test 5

Enter search string: anger

Text you searched for, appears at  39 characters after the first.

Test 6

Enter search string: criminals who operate above the law

Text you searched for,  appears at  206 characters after the first.

Test 7 

Enter search string: cent

Text you searched for,  appears at  159 characters after the first.

Test 8

Enter search string: Knight Rider,

Text you searched for,  appears at  243 characters after the first.

Test 9

Enter search string: rider

String not found!

Test 10

Enter search string: random@3456

String not found!

************************************************************************
2. How to compile and use this project
************************************************************************

Compilation

nasm -f elf64 -g -F dwarf textSearch.asm
ld -o textSearch textSearch.o

Usage

./textSearch

************************************************************************
3. Functionality (describe your contributions here)
************************************************************************

This program uses a naive string alogrith to identify patterns in a given string. The user enters a string and it will return either the character number where it finds a pattern or if not found will return 'not found'

************************************************************************
4. Limitations (if any)
************************************************************************

N/A all test cases pass


************************************************************************
5. Applications (your thoughts) of this project
************************************************************************

Assembly Looping structures and conditional statements
