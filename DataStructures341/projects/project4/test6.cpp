// File: test6.cpp
//
// CMSC 341 Spring 2017 Project 4
//
// Checking copy constructor and assignment operator.
//
// Should compile with: g++ test1.cpp
//

#include <iostream>
#include "MinMaxHeap.h"
using namespace std ;


template <typename T>
void sanityCheck(MinMaxHeap<T>& H) {
   int n = H.size() ;
   T minKey, maxKey, leftKey, rightKey ;
   int minPos, maxPos, pos ;
   
   bool passed=true ;

   cout << "Sanity Check minHeap...\n" ;

   for (int i=1 ; i<=n ; i++) {
      H.locateMin(i,minKey,maxPos) ; 
      H.locateMax(maxPos,maxKey,minPos) ; 
      
      if (minKey != maxKey) {
         passed = false ;
         cout << "Key mismatch at i = " << i << ": "
	      << "minKey = " << minKey << ", " 
	      << "minPos = " << minPos << ", " 
	      << "maxKey = " << maxKey << ", " 
	      << "maxPos = " << maxPos 
	      << endl ;
      }

      if (minPos != i) {
         passed = false ;
         cout << "Position mismatch at i = " << i << ": "
	      << "minKey = " << minKey << ", " 
	      << "minPos = " << minPos << ", " 
	      << "maxKey = " << maxKey << ", " 
	      << "maxPos = " << maxPos 
	      << endl ;
      }

      if (2*i <= n) {  // has left child
         H.locateMin(2*i,leftKey,pos) ;
	 if (leftKey < minKey) {  // left child smaller than root 
	    passed = false ;
	    cout << "Bad heap condition at i = " << i << ": "
		 << "root key = " << minKey << ", " 
		 << "left key = " << leftKey 
		 << endl ;
	 }
      }  

      if (2*i+1 <= n) {  // has right child
         H.locateMin(2*i+1,rightKey,pos) ;
	 if (rightKey < minKey) {  // right child smaller than root 
	    passed = false ;
	    cout << "Bad heap condition at i = " << i << ": "
		 << "root key = " << minKey << ", " 
		 << "right key = " << rightKey 
		 << endl ;
	 }
      }  

   }  // end of for (...)


   cout << "Sanity Check maxHeap...\n" ;

   for (int i=1 ; i<=n ; i++) {
      H.locateMax(i,maxKey,minPos) ; 
      H.locateMin(minPos,minKey,maxPos) ; 
      
      if (minKey != maxKey) {
         passed = false ;
         cout << "Key mismatch at i = " << i << ": "
	      << "minKey = " << minKey << ", " 
	      << "minPos = " << minPos << ", " 
	      << "maxKey = " << maxKey << ", " 
	      << "maxPos = " << maxPos 
	      << endl ;
      }

      if (maxPos != i) {
         passed = false ;
         cout << "Position mismatch at i = " << i << ": "
	      << "minKey = " << minKey << ", " 
	      << "minPos = " << minPos << ", " 
	      << "maxKey = " << maxKey << ", " 
	      << "maxPos = " << maxPos 
	      << endl ;
      }

      if (2*i <= n) {  // has left child
         H.locateMax(2*i,leftKey,pos) ;
	 if (leftKey > maxKey) {  // left child bigger than root 
	    passed = false ;
	    cout << "Bad heap condition at i = " << i << ": "
		 << "root key = " << maxKey << ", " 
		 << "left key = " << leftKey 
		 << endl ;
	 }
      }  

      if (2*i+1 <= n) {  // has right child
         H.locateMax(2*i,rightKey,pos) ;
	 if (rightKey > maxKey) {  // right child bigger than root 
	    passed = false ;
	    cout << "Bad heap condition at i = " << i << ": "
		 << "root key = " << maxKey << ", " 
		 << "right key = " << rightKey 
		 << endl ;
	 }
      }  
   }  // end of for (...)


   if (passed) {
      cout << "Passed sanityCheck().\n" ;
   } else {
      cout << "*** Failed sanityCheck().\n" ;
   }
}

int main() {
   MinMaxHeap<int> H(25) ;
   H.insert(5) ;
   H.insert(10) ;
   H.insert(7) ;
   H.insert(9) ;
   H.insert(6) ;
   H.insert(2) ;
   H.insert(16) ;
   H.insert(12) ;
   H.insert(11) ;

   cout << "Initial MinMax Heap\n" ;
   H.dump() ;
   sanityCheck(H) ;

   MinMaxHeap<int> *Gptr = new MinMaxHeap<int>(H) ;
   cout << "copied MinMax Heap\n" ;
   Gptr->dump();

   H.deleteMax() ;
   Gptr->deleteMin() ;
   cout << "\nH and *Gptr after deleteMax and deleteMin\n" ;
   sanityCheck(H) ;
   sanityCheck(*Gptr) ;

   delete Gptr ;

   cout << "\nH after Gptr deleted\n" ;
   H.deleteMin() ;
   H.deleteMax() ;
   sanityCheck(H) ;

   MinMaxHeap<int> K1(11) ;
   K1.insert(29) ;
   K1.insert(24) ;
   K1.insert(23) ;
   K1.insert(22) ;
   K1.insert(28) ;
   K1.insert(26) ;
   K1.insert(30) ;
   K1.insert(21) ;
   K1.insert(25) ;
   K1.insert(27) ;

   cout << "\nK1 after inserts\n" ;
   sanityCheck(K1) ;

   MinMaxHeap<int> K2(4) ;
   K2.insert(43) ;
   K2.insert(42) ;
   K2.insert(44) ;
   K2.insert(41) ;

   cout << "\nK2 after inserts\n" ;
   sanityCheck(K2) ;

   K2 = K1 ;
   K1.deleteMax() ;
   K2.insert(57) ;

   cout << "\nK1 & K2 after assignment, etc...\n" ;
   sanityCheck(K1) ;
   sanityCheck(K2) ;

}
