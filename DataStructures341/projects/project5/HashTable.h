#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>

template <typename T>
class HashTable {
public:
    virtual ~HashTable() {};

    // Functions in a standard hash table interface,
    // independent of implementation:
    virtual bool insert(const T &data) = 0;
    virtual bool find(const T &data) = 0;
    virtual T remove(const T &data, bool &found) = 0;

    // Functions for debugging and grading:
    virtual void dump() = 0;
    virtual int at(int index, std::vector<T> &contents) = 0;

    // Place to store pointer to hash code generating function
    unsigned int (*hashFunc)(const T &data);

    // There are no other data members that the different derived classes
    // would have in common
};

#endif
