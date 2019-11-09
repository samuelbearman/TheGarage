#ifndef _MIN_MAX_HEAP_CPP_
#define _MIN_MAX_HEAP_CPP_


#include "MinMaxHeap.h"


// Function Pointers below


template <typename T>
static bool minCompare(const Item<T> lhs, const Item<T> rhs){
    return (lhs.m_data <= rhs.m_data);
}

template <typename T>
static bool maxCompare(const Item<T> lhs, const Item<T> rhs){
    return (lhs.m_data >= rhs.m_data);
}


// MinMaxHeap STuff below


// Default constructor
// builds the MinMaxHeap
template <typename T>
MinMaxHeap<T>::MinMaxHeap(int capacity) {

    m_min = new Heap<T>(capacity);
    m_max = new Heap<T>(capacity);
    
    m_min->m_twin = m_max;
    m_max->m_twin = m_min;
    
    m_min->m_compare = &minCompare;
    m_max->m_compare = &maxCompare;

}

// Destructor
// Deletes MinMaxHeap
template <typename T>
MinMaxHeap<T>::~MinMaxHeap() {
  
    delete m_min;
    delete m_max;
    m_min = NULL;
    m_max = NULL;

}

//Copy constructor
template <typename T>
MinMaxHeap<T>::MinMaxHeap(const MinMaxHeap<T>& other) {
  
    m_min = new Heap<T>(*other.m_min);
    m_max = new Heap<T>(*other.m_max);
    
    m_min->m_twin = m_max;
    m_max->m_twin = m_min;

}

// Overloaded Assignment Operator
template <typename T>
const MinMaxHeap<T>& MinMaxHeap<T>::operator=(const MinMaxHeap<T>& rhs) {
  
    if (this == &rhs){
        return rhs;
    }
    
    *m_min = *rhs.m_min;
    *m_max = *rhs.m_max;

}

// Size
// returns current size of the MinMaxHeap
template <typename T>
int MinMaxHeap<T>::size() {
  
    return m_min->m_size;

}

// insert
// Inserts a new value into both the Min and Max heaps
// updates and corrects heaps
template <typename T>
void MinMaxHeap<T>::insert(const T& data) {
  
    if (m_min->m_size + 1 > m_min->m_capacity){
        throw std::out_of_range("Heap is FULL");
    }
    
    Item<T> minItem, maxItem;
    minItem.m_data = data;
    maxItem.m_data = data;
    
    m_min->m_size++;
    int iMin = m_min->bubbleUp(m_min->m_size, minItem);
    maxItem.m_twinIndex = iMin;
    
    m_max->m_size++;
    int iMax = m_max->bubbleUp(m_max->m_size, maxItem);
    m_max->m_twin->m_array[iMin].m_twinIndex = iMax;

}


// Deletes the min item from top of min heap
// also removes same item from max heap
template <typename T>
T MinMaxHeap<T>::deleteMin() { return m_min->deleteFirst(); }


// Deletes the max item from top of max heap
// also removes same item from min heap
template <typename T>
T MinMaxHeap<T>::deleteMax() { return m_max->deleteFirst(); }



// Dump
// Used for debugging
// prints contents of MinMaxHeap
template <typename T>
void MinMaxHeap<T>::dump() { 

    std::cout << "\n... MinMaxHeap::dump() ..." << std::endl;
    std::cout << "\n------------Min Heap------------" << std::endl;
    std::cout << "size = " << m_min->m_size << ", " << "capacity = " << m_min->m_capacity << std::endl;
    for (int i = 1; i <= m_min->m_size; i++){
        std::cout << "Heap[" << i << "] = " << '(' << m_min->m_array[i].m_data << ',' << m_min->m_array[i].m_twinIndex << ")\n";
    }
    std::cout << "\n------------Max Heap------------" << std::endl;
    std::cout << "size = " << m_max->m_size << ", " << "capacity = " << m_max->m_capacity << std::endl;
    for (int i = 1; i <= m_max->m_size; i++){
        std::cout << "Heap[" << i << "] = " << '(' << m_max->m_array[i].m_data << ',' << m_max->m_array[i].m_twinIndex << ")\n";
    }
    std::cout << "--------------------------------" << std::endl;

}

// locateMin
// passes values by reference and finds the location of the min value
template <typename T>
void MinMaxHeap<T>::locateMin(int pos, T& data, int& index) {
  
    if (pos > m_min->m_size || pos < 1) {
        throw std::out_of_range("Position is out of bounds.");
    }
    
    data = m_min->m_array[pos].m_data;
    index = m_min->m_array[pos].m_twinIndex;

}

// loacteMax
// passes values by reference and finds the location of the max value
template <typename T>
void MinMaxHeap<T>::locateMax(int pos, T& data, int& index) {

    if (pos > m_max->m_size || pos < 1) {
        throw std::out_of_range("Position is out of bounds.");
    }
    
    data = m_max->m_array[pos].m_data;
    index = m_max->m_array[pos].m_twinIndex;

}



// Heap stuff Below


// Default constructor for a Heap
template <typename T>
Heap<T>::Heap(int capacity) {

    m_capacity = capacity; 
    m_size = 0;
    m_array = new Item<T>[m_capacity + 1];

}


// Heap Destructor 
// deletes values in a given heap
template <typename T>
Heap<T>::~Heap() {

    delete [] m_array;
    m_array = NULL;

}

// copyHelper
// Made to help copy constructor and assignment operator
template <typename T>
void Heap<T>::copyHelper(const Heap<T>& other) {

    m_array = new Item<T>[m_capacity + 1];
    for (int i = 1; i <= m_size; i++){
        m_array[i] = other.m_array[i];
    }

}

// Heap Copy Constructor
template <typename T>
Heap<T>::Heap(const Heap<T>& other) {

    m_capacity = other.m_capacity;
    m_size = other.m_size;
    m_compare = other.m_compare; 
    m_twin = NULL;
    copyHelper(other);

}

// Heap Assignment Operator
template <typename T>
const Heap<T>& Heap<T>::operator=(const Heap<T>& rhs) {

    if (this == &rhs){
        return rhs;
    }
    
    m_capacity = rhs.m_capacity;
    m_size = rhs.m_size;
    m_compare = rhs.m_compare;
    
    this->~Heap();
    
    copyHelper(rhs);

}

// newTwin
// takes in a index for a node and sets its new Twin's index
template <typename T>
void Heap<T>::newTwin(int index) {

    int newIndex = m_array[index].m_twinIndex;
    m_twin->m_array[newIndex].m_twinIndex = index;

}

// bubbleUp
// operation used in insertion for moving a value up the heap 
template <typename T>
int Heap<T>::bubbleUp(int index, Item<T> item) {

    if (atTop(index)) {
        m_array[index] = item;
        return index;
    }
    
    if (m_compare(m_array[index / 2], item)) {
        m_array[index] = item;
        return index;
    } else {
        m_array[index] = m_array[index / 2];
        newTwin(index);
        return bubbleUp(index / 2, item);
    }

}

// trickleDown
// operation used in insertion for moving a value down the heap
template <typename T>
void Heap<T>::trickleDown(int index, Item<T> item) {
  
    Item<T> child;
    int childIndex;
    
    if (atBottom(index)){
        m_array[index] = item;
        newTwin(index);
        return;
    
    } else {
    
        if (index * 2 == m_size){
            child = m_array[m_size];
            childIndex = m_size;
      
        } else {
    
            if (m_compare(m_array[index * 2], m_array[index * 2 + 1])) {
                child = m_array[index * 2];
                childIndex= index * 2;
         
            } else {
                child = m_array[index * 2 + 1];
                childIndex = index * 2 + 1;
            }
        }
    }
    
    if (m_compare(item, child)) {
        m_array[index] = item;
        newTwin(index);
        return;
    }
    
    m_array[index] = child;
    newTwin(index);
    trickleDown(childIndex, item);
}



// deleteAt
// deletes a value at a given index in a heap
template <typename T>
void Heap<T>::deleteAt(int index) {

    Item<T> temp = m_array[m_size];
    --m_size;
    
    if (index == m_size + 1){
        return;
    }
    
    if (atTop(index)){
        trickleDown(index, temp);
    } else if (atBottom(index)) {
        int newIndex = bubbleUp(index, temp);
        newTwin(newIndex);
    } else if (m_compare(temp,m_array[index / 2])) {
        int newIndex = bubbleUp(index, temp);
        newTwin(newIndex);
    } else {
        trickleDown(index, temp);
    }

}


// deleteFirst
// Deletes the first value in a given heap
template <typename T>
T Heap<T>::deleteFirst() {

    if (m_size == 0) {
        throw std::out_of_range("Heap is EMPTY");
    }
    Item<T> newItem = m_array[m_size];
    Item<T> temp = m_array[1];
    --m_size;
    trickleDown(1, newItem);
    m_twin->deleteAt(temp.m_twinIndex);
    
    return temp.m_data;

}



#endif
