// File: p2comptest.cpp
//
// UMBC Spring 2018 CMSC 341 Project 2
// 
// Check that implementation of SqList has every
// function required in the project description.
//
// Version: Feb 26 2018
//

#include <iostream> 
#include "SqList.h"
#include "INode.h"
#include "DNode.h"
#include "Int341.h"

using namespace std;


void SqList::inspector() {

    cout << "\n\n=============================================\n";
    cout << "SqList::inspector() report\n";
    cout << "=============================================\n";

    bool errorFound = false;

    int n = numItems();

    list<INode>::iterator it, next_it;
    DNode *dp, *end_dp;


    // Calculate total number of items in data structure
    // If they implemented correctly, the first index node should
    // grant access to the entire data-level list.
    //
    int sum = 0;
    if (m_iList.size()) {
	for (dp = m_iList.begin()->m_dNode; dp != NULL; dp = dp->m_next) {
	    ++sum;
	}
    }

    // report on size()
    //
    if (n == sum) {
	cout << "numItems() correct\n";
    } else {
	errorFound = true;
	cout << "*** numItems() wrong! " << endl 
	     << "    numItems() = " << n << endl 
	     << "    data count = " << sum << endl; 
    }

    // special case if no items
    //
    if (m_iList.size() == 0) {
	cout << "Empty SqList, nothing more to check\n"; 
	return;
    }


    // Run down the outer list and check if there are any
    // of these errors: empty list, list too long, adjacent
    // short lists.
    //
    int prevSize, currSize;
    bool prevIsShort = false;
    bool currIsShort;
    int prevVal;
   
    int index = 0;
   
    prevVal = m_iList.begin()->m_dNode->m_data.m_data;

    for(it = m_iList.begin(); it != m_iList.end(); it++) {
	next_it = it;

	if (++next_it == m_iList.end()) {
	    end_dp = NULL;
	} else {
	    end_dp = next_it->m_dNode;
	}
       
	for (currSize = 0, dp = it->m_dNode; dp != end_dp; dp = dp->m_next) {
	    if (prevVal > it->m_dNode->m_data.m_data) {
		errorFound = true;
		cout << "*** val " << prevVal << "> next val " <<
		    it->m_dNode->m_data.m_data << endl;
	    }
	    prevVal = it->m_dNode->m_data.m_data;
	    ++currSize;
	}

	if (currSize == 0) {    // empty?
	    errorFound = true;
	    currIsShort = true;
	    cout << "*** Inner list " << index << " empty! " << endl;

	} else if ( (currSize-1)*(currSize-1) > 4*n ) {   // too long?
	    errorFound = true;
	    cout << "*** Inner list " << index << " too long! " << endl 
		 << "    inner list size  = " << currSize << endl 
		 << "    sum of sizes = " << n << endl; 

	} else if ( 4*(currSize+1)*(currSize+1) <= n) {  // too short?
	    currIsShort = true;
	    if (prevIsShort) {  // adjacent shorts?
		errorFound = true;
		cout << "*** Adjacent short inner lists found! " << endl 
		     << "    sum of sizes = " << n << endl 
		     << "    inner list " << index-1 << " has size  = " << prevSize << endl  
		     << "    inner list " << index << " has size  = " << currSize << endl;
	    }
	} else {
	    currIsShort = false;
	}
	prevSize = currSize;
	prevIsShort = currIsShort;
	index++;
    }

    if (!errorFound) {
	cout << "No errors found!\n";
    }

    cout << "=============================================\n";
   
}



int main() {
    SqList S;
    int i;
    Int341 result;

    Int341::m_debug = false;

    // Use add and remove functions
    //
    // First, do 100 additions to tail
    for (i = 1000; i < 2000; i += 10) {
	S.add(Int341(i));
    }
    // Then, do 100 additions to head
    for (i = 990; i >= 0; i -= 10) {
	S.add(Int341(i)) ;
    }

    for (i = 0; i < 50; i++) {
	result = S.removeAt(0); 
    }
    for (i=149; i >= 100; --i) {
	result = S.removeAt(i); 
    }

    S.dump();
    Int341::report();
    S.inspector();

    S.add(Int341(506));
    S.add(Int341(561));
    for (int i=5; i < 12; i+=3) {
	result = S.removeAt(i);
    }
    result = S.remove(Int341(650));
    result = S.remove(Int341(690));

    S.dump();
    Int341::report();
    S.inspector();

    SqList T(S);
    SqList U;
    U = T;

    U.dump();

    for(int i=0; i < U.numItems(); i++) {
	cout << "U[" << i << "] = " << U[i].m_data << endl;
    }
    for(int i=0; i < U.numItems(); i+=7) {
	U[i] = 5 + U[i].m_data; 
	cout << "U[" << i << "] = " << U[i].m_data << endl;
    }

    Int341 stuff(1000);
    int pos = U.indexOf(stuff);
    if (pos >= 0) {
	cout << "Found " << stuff.m_data << " in index " << pos << endl;
    } else {
	cout << "Did not find " << stuff.m_data << endl;
    }

    stuff = Int341(99999);
    pos = U.indexOf(stuff);
    if (pos >= 0) {
	cout << "Found " << stuff.m_data << " in index " << pos << endl;
    } else {
	cout << "Did not find " << stuff.m_data << endl;
    }


    U.dump();
    Int341::report();

    U.inspector();

    return 0;
}
