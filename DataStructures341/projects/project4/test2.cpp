// File: test2.cpp
//
// CMSC 341 Spring 2017 Project 4
//
// Check insert, deleteMin and deleteMax 
// with MinMaxHeap instantiated with string.
//
// Should compile with:  g++ test2.cpp
//

#include <iostream>
#include <string>
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
   MinMaxHeap<string> H(25) ;
   H.insert("jkl") ;
   H.insert("yz_") ;
   H.insert("abc") ;
   H.insert("mno") ;
   H.insert("vwx") ;
   H.insert("pqr") ;
   H.insert("ghi") ;
   H.insert("def") ;
   H.insert("stu") ;

   H.dump() ;
   sanityCheck(H) ;

   string answer ;
   answer = H.deleteMin() ;
   cout << "Min item " << answer << " removed from MinMax Heap\n" ;

   answer = H.deleteMax() ;
   cout << "Max item " << answer << " removed from MinMax Heap\n" ;

   H.dump() ;
   sanityCheck(H) ;
}
