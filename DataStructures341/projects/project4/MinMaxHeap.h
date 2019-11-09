#ifndef _MIN_MAX_HEAP_H_
#define _MIN_MAX_HEAP_H_

#include <iostream>
#include <string>
#include <stdexcept>

template <typename T>
struct Item {

    T m_data;
    int m_twinIndex;

};

template <typename T>
struct FunctionPtr {

    typedef bool (*funcPtr)(const Item<T> lhs, const Item<T> rhs);

};

template <typename T>
static bool minCompare(const Item<T> lhs, const Item<T> rhs);

template <typename T>
static bool maxCompare(const Item<T> lhs, const Item<T> rhs);


template <typename T>
class Heap{

    template <typename A>
    friend class MinMaxHeap;

private:
    Heap(int capacity = 0);
    Heap(const Heap<T>& other);
    ~Heap();
    const Heap<T>& operator=(const Heap<T>& rhs);
    
    int bubbleUp(int index, Item<T> e);
    void trickleDown(int index, Item<T> r);
    void deleteAt(int index);
    T deleteFirst();
    void newTwin(int index);
    
    void copyHelper(const Heap<T>& other);
    bool atTop(int index){ return index / 2 == 0; }
    bool atBottom(int index){ return index * 2 > m_size; }
    
    
    int m_capacity;
    int m_size;
    Item<T>* m_array;
    Heap* m_twin;
    
    typename FunctionPtr<T>::funcPtr m_compare;
};  


template <typename T>
class MinMaxHeap {

public:
    MinMaxHeap(int capacity = 0);
    ~MinMaxHeap();
    MinMaxHeap(const MinMaxHeap<T>& other);
    const MinMaxHeap<T>& operator=(const MinMaxHeap<T>& rhs);
    
    void insert(const T& data);
    T deleteMin();
    T deleteMax();
    void locateMin(int pos, T& data, int& index);
    void locateMax(int pos, T& data, int& index);
    
    void dump();
    int size();


private:
    Heap<T>* m_min;
    Heap<T>* m_max;
};


#endif

#include "MinMaxHeap.cpp"
