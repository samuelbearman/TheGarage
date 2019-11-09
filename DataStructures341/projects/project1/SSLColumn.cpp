#include "SSLColumn.h"
#include <iostream>
#include <stdexcept>

// Default Constructor for SSLColumn
SSLColumn::SSLColumn(int n ) {

    m_data = new int[n];
    m_capacity = n;
    m_size = 0;
    m_start = 0;
    m_end = 0;

}

// Copy Constructor fo SSLColumn
SSLColumn::SSLColumn(const SSLColumn& other) {

    
    m_data = new int[other.m_capacity];
    for( int i = 0; i < m_capacity; i++) {
        m_data[i] = other.m_data[i];
    }
    m_capacity = other.m_capacity;
    m_size = other.m_size;
    m_start = other.m_start;
    m_end = other.m_end;
    

}

//Destructor for SSLColumn
SSLColumn::~SSLColumn() {

    //delete m_data;

}

// Assignment Operator for SSLColumn
const SSLColumn & SSLColumn::operator=(const SSLColumn& rhs) {

    m_data = new int[rhs.m_capacity]; 
    for( int i = 0; i < m_capacity; i++) {
        m_data[i] = rhs.m_data[i];
    }
    m_capacity = rhs.m_capacity;
    m_size = rhs.m_capacity;
    m_start = rhs.m_start;
    m_end = rhs.m_end;
    return *this;

}

// Function that take in a number to add to the column
// adds in specific order and shifts data properly
void SSLColumn::add(int data) {

    int temp = 0;
    int newVal = data;

    for (int i = 0; i < m_capacity; i++) {
        int index = (m_start + i) % m_capacity;
        if (m_data[index] > newVal || m_data[index] == 0) {
            temp = m_data[index];
            m_data[index] = newVal;
            newVal = temp;
        }
    }
    m_end = (m_end + m_capacity + 1) % m_capacity;
    m_size++;
}

// addFirst is used by User, doesnt check to see if in sorted order
// Adds given number to begining of list
void SSLColumn::addFirst(int data) {

    if(m_size == m_capacity) {
        //throw
        std::cout << "buffer full" << std::endl;
    } else {
        m_start = (m_start + m_capacity - 1) % m_capacity;
        m_data[m_start] = data;
        m_size++;
    }

}

// addLast is used by User, doesnt check to see if in sorted order
// Adds given number to end of list
void SSLColumn::addLast(int data) {

    if(m_size == m_capacity) {
        //throw
        std::cout << "buffer full" << std::endl;
    } else {

        m_data[m_end] = data;
        m_end = (m_end + m_capacity + 1) % m_capacity;
        m_size++;
    }
}

// Finds data in the list using Binary Search
int SSLColumn::find(int data) {

    int p = binarySearch(data);

    return p;
}

// returns number at given index
int SSLColumn::findAt(int pos) {

    if (pos == -1) {
        return m_data[(m_end + m_capacity - 1) % m_capacity];
    }
    if(pos < -1 || pos > m_capacity) {
        throw std::range_error("outside of scope");
        return -1;
    } else {
        return m_data[pos];
    }
}

// removes a number from the list and shifts data to proper place
int SSLColumn::remove(int data) {

    if( m_start == m_end) {
        throw std::underflow_error("buffer empty");
    }
    int p = binarySearch(data);

    m_data[p] = 0;
    for(int i = p; i < m_capacity - 1; i++) {
            m_data[i] = m_data[i + 1];
            m_data[i + 1] = 0;
    }
    m_size--;
    m_end = (m_end + m_capacity - 1) % m_capacity;
    return p;
}

// Used by user, removes first element of list
int SSLColumn::removeFirst(void) {

    if(m_size == 0) {
        throw std::underflow_error("buffer empty");
    }
    int removed = m_data[m_start];
    m_data[m_start] = 0;
    m_start = (m_start + m_capacity + 1) % m_capacity;
    m_size--;
    return removed; 

}

// Used by user, removes last element of list
int SSLColumn::removeLast(void) {

    if(m_size == 0) {
        std::cout << "already empty" << std::endl;
    } 
    int removed = m_data[m_start];
    m_end = (m_end + m_capacity - 1) % m_capacity;
    m_data[m_end] = 0;
    m_size--;
    return removed; 

}

// Returns the current capacity of the list
int SSLColumn::capacity() {
    
    return m_capacity;
}

// Returns the current size of the list
int SSLColumn::size() {

    return m_size;
}

// Shows the contents of the list currently in order
void SSLColumn::dump() {

    int items = 0;
    if(m_size != 0) {
        for(int i = m_start; i <= m_capacity;) {
            if(items == m_size && items != 0) {
                std::cout << " }";
                break;
            }
            if(i == m_start) {
                std::cout << "{ ";
            }
            if(m_data[i] > -1) {
                items++;
                std::cout << m_data[i];
            } 
            i++;
            i = (i + m_capacity) % m_capacity;
            if(m_data[i] != 0 && items != m_size && i != m_start) {
                std::cout << ", ";
            }
        }
    }
}

// Binary Search fuction used to find data in list
int SSLColumn::binarySearch(int val) {

    int start = m_start;
    int end = m_size;
    int mid = (start + end) / 2;

    while(start <= end && m_data[mid] != val) {
        if(m_data[mid] < val) {
            start = mid + 1;
        } else if (m_data[mid] > val) {
            end = mid - 1;
        } else {
            return mid;
        }
        mid = (start + end) / 2;
    }
    if(m_data[mid] == val) {
        return mid;
    } else {
        return -1;
    }
}
