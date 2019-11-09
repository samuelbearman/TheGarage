Project Description

************************************************************************
0. Files:
************************************************************************

Makefile	- Makefile for easy compilation
ReadMe.txt	- This file
atbash.asm	- Main Assembly file for atbash

List expected inputs/outputs

************************************************************************
1. Expected inputs/outputs
************************************************************************

Test 1

Enter string: abcdef

Original: abcdef

Convert:  zyxwvu

Test 2

Enter string: AbCdEfGhI

Original: AbCdEfGhI

Convert:  ZyXwVuTsR

Test 3

Enter string: NoPqRsTuV

Original: NoPqRsTuV

Convert:  MlKjIhGfE

Test 4

Enter string: 1+1=Two

Original: 1+1=Two

Convert:  1+1=Gdl

Test 5

Enter string: retriever@umbc.edu

Original: retriever@umbc.edu

Convert:  ivgirvevi@fnyx.vwf

Test 6

Enter string: 1 One 2 Two 3 Three 4 Four 5 Five 6 Six

Original: 1 One 2 Two 3 Three 4 Four 5 Five 6 Six

Convert:  1 Lmv 2 Gdl 3 Gsivv 4 Ulfi 5 Urev 6 Hrc

Test 7 (Note: In this test, only the enter key was input)

Enter string: 

Original: 

Convert:  

Test 8

Enter string: 'quotes!'

Original: 'quotes!'

Convert:  'jflgvh!'

Test 9

Enter string: arithmetic+-%^&*

Original: arithmetic+-%^&*

Convert:  zirgsnvgrx+-%^&*

Test 10

Enter string: <special#$(characters)>

<special#$(characters)>Original: <special#$(characters)>

<special#$(characters)>Convert:  <hkvxrzo#$(xszizxgvih)>

************************************************************************
2. How to compile and use this project
************************************************************************

Compilation

nasm -f elf64 -g -F dwarf atbash.asm
ld -o atbash atbash.o

Usage

./atbash

************************************************************************
3. Functionality (describe your contributions here)
************************************************************************

This program will loop through all characters individually and establish
if they are reside between a - z or A - Z, then based on that convert, 
using a function, to get the cipher translation. 


************************************************************************
4. Limitations (if any)
************************************************************************

N/A all test cases pass


************************************************************************
5. Applications (your thoughts) of this project
************************************************************************

Learning about basic looping structures and ASCII table manipulation
