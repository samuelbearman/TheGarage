#ifndef CHAIN_HASH_TABLE_CPP
#define CHAIN_HASH_TABLE_CPP

#include "ChainHashTable.h"
#include <iostream>

// Overloaded Constructor, only constructor, defaults to a size of 101
template <typename T>
ChainHashTable<T>::ChainHashTable(unsigned int (*hashFunc)(const T&), int n) {

    m_table = new std::list<T>[n];
    m_capacity = n;
    m_size = 0;
    this->hashFunc = hashFunc;

}

// Destructor for ChainHashTable
template <typename T>
ChainHashTable<T>::~ChainHashTable() {

    delete [] m_table;
    m_table = NULL;

}

// Copy constructor
template <typename T>
ChainHashTable<T>::ChainHashTable(ChainHashTable& rhs) {

    m_capacity = rhs.m_capacity;
    m_size = rhs.m_size;
    this->hashFunc = rhs.hashFunc;

    m_table = new std::list<T>[m_capacity];

    typename std::list<T>::iterator it;
    for (int i = 0; i < m_capacity; i++) {
        for (it = rhs.m_table[i].begin(); it != rhs.m_table[i].end(); ++it) {
            m_table[i] = rhs.m_table[i]; 
        }
    }
}

// overloaded '=' operator
template <typename T>
const ChainHashTable<T>& ChainHashTable<T>::operator=(ChainHashTable<T>& rhs) {

    m_capacity = rhs.m_capacity;
    m_size = rhs.m_size;
    this->hashFunc = rhs.hashFunc;

    m_table = new std::list<T>[m_capacity];

    typename std::list<T>::iterator it;
    for (int i = 0; i < m_capacity; i++) {
        for (it = rhs.m_table[i].begin(); it != rhs.m_table[i].end(); ++it) {
            m_table[i] = rhs.m_table[i]; 
        }
    }
}

// insert
// inserts new data into the ChainHashTable using a chaining method
template <typename T>
bool ChainHashTable<T>::insert(const T &data) {


    if (m_size == m_capacity) {
        throw std::out_of_range("Hash Table is FULL");
    }
    unsigned int hashCode = this->hashFunc(data) % m_capacity;

    if (find(data)) {
        return false;
    } else {
        m_size++; 
        m_table[hashCode].push_front(data); 
        return true;
    }
}

// find
// takes in templated data and finds whether it is in the HashTable or not
// returns a boolean, true if found, false if not
template <typename T>
bool ChainHashTable<T>::find(const T &data) {

    unsigned int hashCode = this->hashFunc(data) % m_capacity;

    typename std::list<T>::iterator it;
    for (it = m_table[hashCode].begin(); it != m_table[hashCode].end(); ++it) {
        if (*it == data) {
            return true;
        }
    }
    return false;
}

// remove
// removes data from the hash table, lazy deletes it instead of actually removing data
template <typename T>
T ChainHashTable<T>::remove(const T &data, bool &found) {

    unsigned int hashCode = this->hashFunc(data) % m_capacity;
    if (find(data)) {
        m_table[hashCode].remove(data);
        found = true;
        m_size--;
        return data;
    } else {
        found = false;
        return data;
    }
}

// dump
// shows contents of the hash table
// only used for debugging
template <typename T>
void ChainHashTable<T>::dump() {

    std::cout << "ChainHashTable dump; size: " << m_capacity << " buckets: " << std::endl; 
    for (int i = 0; i < m_capacity; i++) {
        std::cout << "[" << i << "]: ";
        typename std::list<T>::iterator it;
        for (it = m_table[i].begin(); it != m_table[i].end(); ++it) {
            std::cout << *it << ", ";

        }
        std::cout << std::endl;
    }
    std::cout << "Total items: " << m_size << std::endl;
}

// at
// given an index in the hashtable, will return 1 if an item is there and 0 if not
// will push any elements to the vector 'contents'
template <typename T>
int ChainHashTable<T>::at(int index, std::vector<T> &contents) {


    if (index < 0 || index > m_capacity) {
        throw std::out_of_range ("Index is too big or too small");
    }

    if (m_table[index].size() == 0) {
        return 0;
    } else {
        typename std::list<T>::iterator it;
        for (it = m_table[index].begin(); it != m_table[index].end(); ++it) {
            contents.push_back(*it); 
        }
        return m_table[index].size();
    }

}

#endif
