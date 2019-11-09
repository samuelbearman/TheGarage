Project Description

************************************************************************
0. Files:
************************************************************************

ReadMe.txt	- This file
hexConverter.asm	- The file you will be modifying and handing in
typescript  - If you have not met all test cases/code does not compile etc.
any other supporting files

List expected inputs/outputs

************************************************************************
1. Expected inputs/outputs
************************************************************************

Test 2

Enter Number: afadf

Invalid Input!


Test 3

Enter Number: 245453

Invalid Input!


Test 4

Enter Number: afdg dbdgbsgbfnnhnfhnh45647637

Invalid Input!


Test 5

Enter Number: 3564276575375787dfjhfdjdtj

Invalid Input!

************************************************************************
2. How to compile and use this project
************************************************************************

Compilation

nasm -f elf64 -g -F dwarf hexConverter.asm
gcc -g hexConverter.o cfunc.c -o converter.out

Usage

./converter.out

************************************************************************
3. Functionality (describe your contributions here)
************************************************************************

This program is supposed to return, based on user input, the equvalent
of the hexadecimal number. If anything than numbers are inputed, then 
it returns 'Not valid input'. Unfortunately the program does not work 
correctly.

************************************************************************
4. Limitations (if any)
************************************************************************

These tests do not pass

Test 1

Enter Number: 18446744073709551615

Hexadecimal value is: FFFFFFFFFFFFFFFF

Test 6


Enter Number: 1107895634578278122

Hexadecimal value is: F600935B33E86EA



Test 7 

Enter Number: 9223372036854775808

Hexadecimal value is: 8000000000000000


Test 8

Enter Number: 12683270251100288260

Hexadecimal value is: B0040718331CB504


Test 9

Enter Number: 15683272751237288260

Hexadecimal value is: D9A62D79450FD144


Test 10

Enter Number: 9346678735677288564

Hexadecimal value is: 81B612CA0DBDF074


************************************************************************
5. Applications (your thoughts) of this project
************************************************************************

The trickiest part is the conversion and the divisons and multiplications
for conversion can throw things off.
