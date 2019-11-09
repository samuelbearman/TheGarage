#ifndef PROBE_HASH_TABLE_H
#define PROBE_HASH_TABLE_H


#include "HashTable.h"

#define FLAG_DELETE -1
#define FLAG_EMPTY 0
#define FLAG_FULL 1

// Helper class used as the values for the array
template <typename T>
class HashTableEntry {
public:

    T m_data;
    int m_flag;
    int m_hash;
};


template <typename T>
class ProbeHashTable: public HashTable <T> {
public:

    ProbeHashTable(unsigned int (*hashFunc)(const T&), int n=101);
    virtual ~ProbeHashTable();
    ProbeHashTable (ProbeHashTable& other);
    const ProbeHashTable&operator=(ProbeHashTable& rhs);
    virtual bool insert(const T &data);
    virtual bool find(const T &data);
    virtual T remove(const T &data, bool &found);
    virtual void dump();
    virtual int at(int index, std::vector<T> &contents);

private:

    HashTableEntry<T>* m_table;
    int m_size;
    int m_capacity;
};

#endif

#include "ProbeHashTable.cpp"
