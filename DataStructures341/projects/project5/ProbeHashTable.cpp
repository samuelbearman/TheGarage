#ifndef PROBE_HASH_TABLE_CPP
#define PROBE_HASH_TABLE_CPP

#include "ProbeHashTable.h"
#include <iostream>

// Overloaded Constructor
template <typename T>
ProbeHashTable<T>::ProbeHashTable(unsigned int (*hashFunc)(const T&), int n) {

    m_table = new HashTableEntry<T>[n];
    m_capacity = n;
    m_size = 0;
    this->hashFunc = hashFunc;

}

// Destructor 
template <typename T>
ProbeHashTable<T>::~ProbeHashTable() { 
        
    delete [] m_table;
    m_table = NULL;

}

// Copy Constructor
template <typename T>
ProbeHashTable<T>::ProbeHashTable(ProbeHashTable& rhs) {

    m_capacity = rhs.m_capacity;
    m_size = rhs.m_size;
    this->hashFunc = rhs.hashFunc; 

    m_table = new HashTableEntry<T>[m_capacity];

    for (int i = 0; i < m_capacity; i++) {
        m_table[i].m_flag = rhs.m_table[i].m_flag;
        m_table[i].m_data = rhs.m_table[i].m_data;
        m_table[i].m_hash = rhs.m_table[i].m_hash;
    }
}

// Overloaded '=' operator
template <typename T>
const ProbeHashTable<T>& ProbeHashTable<T>::operator=(ProbeHashTable<T>& rhs) {

    m_capacity = rhs.m_capacity;
    m_size = rhs.m_size;
    this->hashFunc = rhs.hashFunc; 

    m_table = new HashTableEntry<T>[m_capacity];

    for (int i = 0; i < m_capacity; i++) {
        m_table[i].m_flag = rhs.m_table[i].m_flag;
        m_table[i].m_data = rhs.m_table[i].m_data;
        m_table[i].m_hash = rhs.m_table[i].m_hash;
    }
}

// insert
// inserts new data into hash table using the linear probing technique
template <typename T>
bool ProbeHashTable<T>::insert(const T &data) {

// insertion process
// start by hashing data value 
// try and insert at hashed point
// if empty, insert into spot
// if not loop and probe until spot is found

    if (m_size == m_capacity) { 
        throw std::out_of_range("Hash table is FULL");
    }

    unsigned int hashCode = this->hashFunc(data) % m_capacity;


    if (m_table[hashCode].m_flag == FLAG_EMPTY || m_table[hashCode].m_flag == FLAG_DELETE) {
        m_table[hashCode].m_data = data;
        m_table[hashCode].m_flag = FLAG_FULL;
        m_table[hashCode].m_hash = hashCode;
        m_size++;
        return true;
    } 
    if(m_table[hashCode].m_flag == FLAG_FULL) {

        bool stillProbing = true;
        int incrementer = (int) hashCode;
        incrementer = (incrementer + 1) % m_capacity;
        while (stillProbing) {
            if (m_table[incrementer].m_flag == FLAG_EMPTY || m_table[incrementer].m_flag == FLAG_DELETE) {
                m_table[incrementer].m_data = data;
                m_table[incrementer].m_flag = FLAG_FULL;
                m_table[incrementer].m_hash = hashCode;
                m_size++;
                return true;
                stillProbing = false;
            }
            incrementer = (incrementer + 1) % m_capacity;
        }
    }
}

// find
// finds given data, returns true if found, false if not
template <typename T>
bool ProbeHashTable<T>::find(const T &data) {

    unsigned int hashCode = this->hashFunc(data) % m_capacity;
    
    if (m_table[hashCode].m_flag == FLAG_EMPTY)
        return false;

    if (m_table[hashCode].m_data == data) 
        return true;

    bool stillProbing = true;
    int incrementer = (int) hashCode;
    incrementer = (incrementer + 1) % m_capacity;
    
    while (stillProbing) {

        if (m_table[incrementer].m_flag == FLAG_EMPTY) 
            return false;

        if (m_table[incrementer].m_data == data) 
            return true;
        


        incrementer = (incrementer + 1) % m_capacity;
    }
}

// remove
// removes items from hash table, sets boolean 'found' to true if found, false if not
// returns back the data
template <typename T>
T ProbeHashTable<T>::remove(const T &data, bool &found) {


    unsigned int hashCode = this->hashFunc(data) % m_capacity;


    if (m_table[hashCode].m_data == data) {
        m_table[hashCode].m_flag = FLAG_DELETE; 
        found = true;
        m_size--;
        return m_table[hashCode].m_data;
    } else {
        bool stillProbing = true;
        int incrementer = (int) hashCode;
        incrementer = (incrementer + 1) % m_capacity;

        while (stillProbing) {

            if (m_table[incrementer].m_flag == FLAG_EMPTY) {
                found = false;
                return data;
            }

            if (m_table[incrementer].m_data == data) {
                m_table[incrementer].m_flag = FLAG_DELETE;
                found = true;
                m_size--;
                return m_table[incrementer].m_data;
            }
            incrementer = (incrementer + 1) % m_capacity;
        }
    }
}

// dump
// dumps contents of the hash table, used for debugging only
template <typename T>
void ProbeHashTable<T>::dump() {

    std::cout << "ProbeHashTable dump; size: " << m_capacity << " buckets" << std::endl;
    for (int i = 0; i < m_capacity; i++) {
        std::cout << "[" << i << "]: ";
        if (m_table[i].m_flag == FLAG_FULL) {
            std::cout << m_table[i].m_data << " (" << m_table[i].m_hash << ")" << std::endl;
        } else if (m_table[i].m_flag == FLAG_DELETE) {
            std::cout << "DELETED" << std::endl;
        } else if (m_table[i].m_flag == FLAG_EMPTY) {
            std::cout << "EMPTY" << std::endl;
        } else {
            std::cout << std::endl;
        }
    }
    std::cout << "Total items: " << m_size << std::endl;
}

// at
// given a specific index, finds if there is a value at that index
// returns 1 if there is data, 0 if not
// pushes all data found at given index to 'contents' vector
template <typename T>
int ProbeHashTable<T>::at(int index, std::vector<T> &contents) {

    if (index < 0 || index > m_capacity) {
        throw std::out_of_range ("Index is too big or too small");
    }

    if (m_table[index].m_flag == FLAG_FULL) {
        contents.push_back(m_table[index].m_data);
        return 1;
    } else {
        return 0; 
    }
}

#endif
