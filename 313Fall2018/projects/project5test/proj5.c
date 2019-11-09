/*
 * File: proj5.c
 */

#include <stdio.h>                 //Why are these libraries included here?
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
  qsort(allBooks, numBooks, sizeof(books), (cmpfunc) &bookcmp);

  for (int i = 0; i < numBooks; i++) {
    printf("%s\n", allBooks[i].title);
  }  
  //print the list of book titles here using a for loop
  //format conversion specifier for printf should be "%s\n"
}
