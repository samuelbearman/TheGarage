// File: p2timetest2.cpp
//
// UMBC Spring 2018 CMSC 341 Project 2
// 
// Timing runs to show expected O(n^(1.5)) running time.
//

#include <iostream> 
#include "SqList.h"
#include "Int341.h"

using namespace std ;


int main() {
   SqList S ;
   int n =  30000;

   Int341::m_debug = false ;

   // add lots of items
   //
   // First, to tail of list
   for (int i = 1; i <= 2 * n; i++) {
     S.add(Int341(i));
   }
   // Then add to head
   for (int i = 1; i <= 2 * n; i++) {
     S.add(Int341(-i));
   }

   // remove half
   //
   // First, from head
   Int341 result ;
   for (int i = 1; i <= n; i++) {
     S.removeAt(0);
   }
   // Then, from tail
   for (int i = 1; i <= n; i++) {
     S.removeAt(n * 3 - i);
   }

   return 0 ;
}
