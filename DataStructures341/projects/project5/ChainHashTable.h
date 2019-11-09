#ifndef CHAIN_HASH_TABLE_H
#define CHAIN_HASH_TABLE_H

#include "HashTable.h"
#include <list>

template <typename T>
class ChainHashTable: public HashTable <T> {
public:

    ChainHashTable(unsigned int (*hashFunc)(const T&), int n=101);
    virtual ~ChainHashTable();
    ChainHashTable (ChainHashTable& other);
    const ChainHashTable&operator=(ChainHashTable& rhs);
    virtual bool insert(const T &data);
    virtual bool find(const T &data);
    virtual T remove(const T &data, bool &found);
    virtual void dump();
    virtual int at(int index, std::vector<T> &contents);

private:

    std::list<T>* m_table; 
    int m_size;
    int m_capacity;
};

#endif

#include "ChainHashTable.cpp"
