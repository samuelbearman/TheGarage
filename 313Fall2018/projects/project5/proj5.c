/*
 * File: proj5.c
 */

#include <stdio.h>  // These libraries are needed for the qsort function and printf
#include <stdlib.h>
#include "book.h"


/* Declare external function/asm subroutine for book comparison */
extern int bookcmp(const books *, const books *);

// A function pointer is defined below to typecast the book comparison function above within qsort
// man qsort explains why one of the parameters is a function pointer
typedef int (*cmpfunc)(const void *, const void *);

/*
 * sort_books -- See project notes for more information
 * Takes array and length of book structs and sorts them within the array
 * Parameters: book[], int
 * Return: none
 */
void sort_books(books* allBooks, int numBooks)
{
  qsort(allBooks, numBooks, sizeof(books), (cmpfunc) &bookcmp); // sorts all the books based on out function ptr

  for (int i = 0; i < numBooks; i++) {
    printf("%s\n", allBooks[i].title);  // printf to print out titles 
  }  
}
