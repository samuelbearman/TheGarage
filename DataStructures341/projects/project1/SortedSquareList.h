// file: SortedSquareList.h
//
// UMBC CMSC 341 Spring 2018 Project 1
//
// Header file for Sorted Square List
// See project description for details.
//
// Unless otherwise noted, any position argument is relative to
// the stored data, and not an absolute index into the underlying array.
//

#ifndef _SORTEDSQUARELIST_H_
#define _SORTEDSQUARELIST_H_

#include "SSLColumn.h" 

class SortedSquareList {

public:
   // default constructor
   SortedSquareList() ;

   // copy constructor
   SortedSquareList(const SortedSquareList& other) ;

   // destructor
   ~SortedSquareList() ;

   // overloaded assignment operator
   // We can copy into differently-sized square list, as long as it is large
   // enough to hold all of the actual stored data.
   const SortedSquareList& operator=(const SortedSquareList& rhs) ;

   // Adds item to correct position in square list, based on sort order.
   // Must grow dynamically allocated structures if we run out of room;
   // REQUIREMENT: must execute in O(sqrt(n)) time, where n is
   // number of items currently stored.
   void add(int data) ;

   // returns position of item in list, -1 if not found.
   // REQUIREMENT: must execute in O(log(n)) time
   int find(int data);

   // Retrieves value at index pos in square list, based on total sort order.
   // Throws exception if pos beyond end
   // REQUIREMENT: must execute in O(log(n)) time
   int findAt(int pos);

   // Finds and removes item from square list.
   // Returns true if data found, false otherwise.
   // REQUIREMENT: must execute in O(sqrt(n)) time
   bool remove(int data);

   // return maximum number of active items this square list can hold with
   // current allocation
   int capacity();

   // Total number of items in the square list as a whole, across all columns.
   int size();

   // debugging function, prints out contents of data structure
   void dump();

   // grading function used to examine private data members.
   bool inspect (SSLColumn** &buf, int &cap, int &size, int &start, int &end);

private :
   // Top-level array of pointers to SSLColumns.
   // Each entry of the array is a pointer.
   SSLColumn **m_cols;
   int *m_colInfo;  // Useful for caching some info about each column
   int m_capacity;  // length of the allocated space pointed by m_cols
   int m_size;      // number of active columns in top-level buffer
   // index of first active column in the top-level buffer(virtual index 0);
   int m_start;
   int m_end;      // index AFTER last active column in top-level buffer

  // STUDENT-ADDED MEMBERS HERE


   int binarySearch(int val);
  // END STUDENT-ADDED MEMBERS

};

#endif

