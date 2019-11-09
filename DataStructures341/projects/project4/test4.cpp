// File: test4.cpp
//
// CMSC 341 Spring 2017 Project 4
//
// Check inserta and deleteMin 
// with MinMaxHeap instantiated with int.
//
// This is a bigger test.
// Also MinMaxHeap is check against STL multiset.
//
// Should compile with:  g++ test4.cpp
//

#include <iostream>
#include <set>
#include <stdlib.h>
#include "MinMaxHeap.h"
using namespace std ;


template <typename T>
void sanityCheck(MinMaxHeap<T>& H) {
   int n = H.size() ;
   T minKey, maxKey, leftKey, rightKey ;
   int minPos, maxPos, pos ;
   
   bool passed=true ;

//   cout << "Sanity Check minHeap...\n" ;

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


//   cout << "Sanity Check maxHeap...\n" ;

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
      cout << "Passed sanityCheck()\n" ;
   } else {
      cout << "*** Failed sanityCheck()\n" ;
   }
}


template <typename T>
void checkAgainstSet(MinMaxHeap<T>& H, multiset<T>& origS) {
   multiset<T> S ;  
   typename multiset<T>::iterator it ;

   int n = H.size() ;
   int pos ;
   int key ;

   bool passed = true ;

   S = origS ;  // make copy

   if ( n != S.size() ) {
      passed = false ;
      cout << "Heap and multiset sizes do not match!\n" ;
      cout << "   Heap size = " << n << endl ;
      cout << "   Set size  = " << S.size() << endl ;
   }


   for (int i=1 ; i <= n ; i++) {
      H.locateMin(i,key,pos) ;
      it = S.find(key) ;
      if (it == S.end()) {
        passed = false ;
	cout << "Key " << key << " in the min-heap but not in the multiset.\n" ;
      } else {
        S.erase(it) ;
      }
   }

   if (S.size() > 0) {
      cout << "There are " << S.size() 
           << " items in multiset that not in the min-heap.\n" ;
      for (it=S.begin() ; it != S.end() ; it++) {
         cout << *it << " " ;
      }
      cout << endl ;
   }


   S = origS ;  // start over

   for (int i=1 ; i <= n ; i++) {
      H.locateMax(i,key,pos) ;
      it = S.find(key) ;
      if (it == S.end()) {
        passed = false ;
	cout << "Key " << key << " in the max-heap but not in the multiset.\n" ;
      } else {
        S.erase(it) ;
      }
   }

   if (S.size() > 0) {
      cout << "There are " << S.size() 
           << " items in multiset that not in the max-heap.\n" ;
      for (it=S.begin() ; it != S.end() ; it++) {
         cout << *it << " " ;
      }
      cout << endl ;
   }

   if (passed) {
      cout << "Passed check against multiset\n" ;
   } else {
      cout << "***Failed check against multiset\n" ;
   }

}


int main() {

   srand(4178012351) ;

   MinMaxHeap<int> H(1000) ;
   multiset<int> S ;
   multiset<int>::iterator it ;
   int key ;
   bool passed ;

   for (int i=0 ; i < 500 ; i++) {
      key = rand() % 100 ;
      // cout << "Insert key = " << key << endl ;
      H.insert(key) ;
      S.insert(key) ;
   }
   sanityCheck(H) ;
   checkAgainstSet(H,S) ;

   passed = true ;
   for (int i=0 ; i < 450 ; i++) {
      key = H.deleteMin() ;
      if (key != *S.begin()) {
         passed = false ;
         cout << "deleteMin() returns key that is not the smallest key!\n" ;
      } else {
         S.erase(S.begin()) ;
      }
   }

   sanityCheck(H) ;

   if (passed) {
      checkAgainstSet(H,S) ;
   } else {
      cout << "***Failed deleteMin() test!\n" ;
      cout << "Skipped check against multiset\n" ;
   }

}
