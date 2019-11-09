#include "SortedSquareList.h"
#include "SSLColumn.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

// SortedSquareList constructor, defaults to 2x2 list
SortedSquareList::SortedSquareList() {
    
    m_capacity = 4; 
    m_size = 0;
    m_start = 0;
    m_end = 0;
    m_colInfo = new int[2];
    m_cols = new SSLColumn*[2];

    for( int i = 0; i < 2; i++) {
        m_cols[i] = new SSLColumn(2);
    }
}

// Copy Constructor for SortedSquareList, makes deep copy of list
SortedSquareList::SortedSquareList( const SortedSquareList& other) {
    m_capacity = other.m_capacity;
    m_size = other.m_size;
    m_start = other.m_start;
    m_end = other.m_end;
    m_colInfo = new int[other.m_capacity / 2];
    m_cols = new SSLColumn*[2];

    for(int i = 0; i < (m_capacity / 2); i++) {
        m_cols[i] = new SSLColumn(m_capacity / 2);
        m_colInfo[i] = other.m_colInfo[i];
    }
}

// SortedSquareList destructor
SortedSquareList::~SortedSquareList() {

    for(int i = 0; i < (m_capacity / 2); i++) {
        delete m_cols[i];
    }
    delete m_colInfo;
}

// SortedSquareList assignment operator
// DID NOT FINISH
const SortedSquareList & SortedSquareList::operator=(const SortedSquareList& rhs) {

    m_capacity = rhs.m_capacity;
    m_size = rhs.m_size;
    m_start = rhs.m_start;
    m_end = rhs.m_end;
    m_colInfo = new int[rhs.m_capacity / 2];
    m_cols = new SSLColumn*[2];

    for(int i = 0; i < (m_capacity / 2); i++) {
        m_cols[i] = new SSLColumn(m_capacity / 2);
        m_colInfo[i] = rhs.m_colInfo[i];
    }
    return *this;
}

// add fuction that adds user data into the correct place in the list
// DID NOT FINISH
void SortedSquareList::add(int data) {

    if(m_size == 0 || m_size == 1) {
        m_cols[m_start]->add(data);
        m_size++;
        m_colInfo[m_start]++;
    } else {
        if(m_cols[m_start]->findAt(0) < data) {
            m_start = (m_start + (m_capacity / 2) - 1) % (m_capacity / 2);
            m_cols[m_start]->add(data);
            m_size++;
            m_colInfo[m_start]++;
        } else if(m_cols[m_start]->findAt(-1) > data) {
            m_cols[m_end]->add(data);
            m_end = (m_end + (m_capacity / 2) - 1) % (m_capacity / 2);

        }
    }
}

// Find function finds the location of a given piece of data in list
// DID NOT FINISH
int SortedSquareList::find(int data) {

    int p = binarySearch(data);
    return p;
}

// FindAt find the position of given index
int SortedSquareList::findAt(int pos) {

    int p = 0;
    for(int i = 0; i < (m_capacity / 2); i++) {
        if (pos < m_colInfo[i]) {
            p = m_cols[i]->findAt(pos) + i;
            break;
        }
    }
    return p;
}

// removes a piece of data from list, finds using binary search
// DID NOT FINISH
bool SortedSquareList::remove(int data) {

    int p = binarySearch(data);
    if (p == -1) {
        return false;
    } else {
        
        return true;
    }

}

// returns the current capacity of the list
int SortedSquareList::capacity() {

    return m_capacity;

}

// returns the current size of the list
int SortedSquareList::size() {

    return m_size;
}

// dumps the content of the list in order
// DID NOT FINISH
void SortedSquareList::dump() { 
    
}

// binarySearch for finding appropriate column
// DID NOT FINISH
int SortedSquareList::binarySearch(int val) {
    
}

