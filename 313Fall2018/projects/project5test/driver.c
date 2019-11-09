/*
 * File: driver.c
 */

#include<stdio.h>                             //Why are these libraries included here?
#include<stdlib.h>
#include<string.h>
#include "book.h"

char gapString[] = {"========="};             //Test case separator

books library[50];                            //Library of books

extern void sort_books(books allbooks[], int numBooks); //External reference to sort_books function defined in proj5.c

int main(){

  FILE *ifp ;                                   //File handle
  char lineRead[100];                           //Stores a single line read from current test file
  char digitString[2] = {'0','\0'};             //Numeric distinction between test files
  char tenString[3] = {'1','0','\0'};           //Special case of test10.dat
  char endString[5] = {'.','d','a','t','\0'};   //Extension for test file
  int numBooks = 0;                             //Keeps track of number of books in each test
  
  int tempItr,readItr;                          //Temporary variables for iterators
  char tempBuf[5];                              //Temporary Buffer, stores year of publication as a string

  for(int testItr=1;testItr<=10;testItr++){
        char baseString[15] = "test";
        numBooks = 0;
        /* try to open the file for writing, check if successful */
        /* if it wasn't exit gracefully */
          if(testItr<10){
              digitString[0] = digitString[0]+1;      //Construct test file name string
              strcat(baseString,digitString);
              strcat(baseString,endString);
          }else{                                      //Special case 
              strcat(baseString,tenString);           //Construct test file name string
              strcat(baseString,endString);
          }

        ifp = fopen(baseString, "r") ;                //Now open the file for reading
        if (ifp == NULL) {
            printf ("Error opening %s\n",baseString);
            exit (-1);
        }

        while(!feof(ifp)){                            //feof returns non-zero if end of file has been encountered
            /* read from the file using fprintf formats */
            fscanf(ifp, "%[^\n]\n", lineRead);        //Read one line
            readItr=0;
            //Title
            for(tempItr=0;lineRead[readItr]!=',';tempItr++)
               library[numBooks].title[tempItr] = lineRead[readItr++];
            library[numBooks].title[tempItr] = '\0';
            readItr++;
            //Author
            for(tempItr=0;lineRead[readItr]!=',';tempItr++)
               library[numBooks].author[tempItr] = lineRead[readItr++];
            library[numBooks].author[tempItr] = '\0';
            readItr++;
            //Year of Publication - four characters - use atoi
            for(tempItr=0;tempItr<4;tempItr++)
               tempBuf[tempItr] = lineRead[readItr++];
            tempBuf[tempItr] = '\0';
            library[numBooks].year = atoi(tempBuf);
            numBooks++;
        }
        fclose(ifp);                                 /* close the file when finished writing */

        //call the sort_books function here
        sort_books(library,numBooks); //Observe parameter ordering here, and use this as a clue to specify the argument list for sort_books 
        printf("%s\n",gapString);  //Print the seperator string
  }
}
