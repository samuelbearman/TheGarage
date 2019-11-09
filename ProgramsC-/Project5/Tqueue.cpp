/*
 * Name: Samuel Bearman
 * File: Tqueue.cpp CMSC 202, Fall 2017
 * Date: 12/1/17
 * Section: 14
 * Email: bearman1@umbc.edu
 *
 * Description: This .cpp file is the data structure 'Queue' Class. It is templated so it can
 * take anykid of class and any size queue. It has a copy constructor and an assigment operator
 * so it can full function like a data structure.
 * */

#ifndef TQUEUE_H
#define TQUEUE_H

#include <iostream>
#include <cstdlib>
using namespace std;

template <class T, int N>
class Tqueue {
public:
  //Name: Tqueue - Default Constructor
  //Precondition: None (Must be templated)
  //Postcondition: Creates a queue using dynamic array
  Tqueue(); //Default Constructor
  //Precondition: Existing Tqueue
  //Postcondition: Copies an existing Tqueue
  Tqueue( const Tqueue<T,N>& x ); //Copy Constructor
  //Name: Destructor
  //Precondition: Existing Tqueue
  //Postcondition: Destructs existing Tqueue
  ~Tqueue(); //Destructor
  //Name: enqueue
  //Precondition: Existing Tqueue
  //Postcondition: Adds item to back of queue
  void enqueue(T data); //Adds item to queue (to back)
  //Name: dequeue
  //Precondition: Existing Tqueue
  //Postcondition: Removes item from front of queue
  void dequeue(T &); //Removes item from queue (from front)
  //Name: queueFront
  //Precondition: Existing Tqueue
  //Postcondition: Retrieve front (does not remove it)
  void queueFront(T &);    // Retrieve front (does not remove it)
  //Name: isEmpty
  //Precondition: Existing Tqueue
  //Postcondition: Returns 1 if queue is empty else 0
  int isEmpty(); //Returns 1 if queue is empty else 0
  //Name: isFull
  //Precondition: Existing Tqueue
  //Postcondition: Returns 1 if queue is full else 0
  int isFull(); //Returns 1 if queue is full else 0
  //Name: size
  //Precondition: Existing Tqueue
  //Postcondition: Returns size of queue
  int size(); //Returns size of queue
  //Name: Overloaded assignment operator
  //Precondition: Existing Tqueue
  //Postcondition: Sets one Tqueue to same as a second Tqueue using =
  Tqueue<T,N>& operator=( const Tqueue<T,N> &y); //Overloaded assignment operator for queue
  //Name: Overloaded [] operator
  //Precondition: Existing Tqueue
  //Postcondition: Returns object from Tqueue using []
  T& operator[] (int x);//Overloaded [] operator to pull data from queue
  // getFront
  // retrives the current front of the queue
  int getFront();
  // getBack
  // retrives the current back of the queue
  int getBack();
private:
  T* m_data; //Data of the queue (Must be dynamically allocated array)
  int m_front; //Front of the queue
  int m_back; //Back of the queue
  int m_size; //Current size of the queue
};

//**** Add class definition below ****

// queueFront
// returns the current front of the queue
template <class T, int N> void Tqueue<T,N>::queueFront(T &data) {

    cout << m_data[m_front];

}

// Overloaded [] operator
// Allows the use of [] to get each individual index of the array
template <class T, int N> T& Tqueue<T,N>::operator[](int x) {

    return m_data[x];

}

// Overloaded = operator
// Allows the queue to be easily equated to another queue
template <class T, int N> Tqueue<T,N> & Tqueue<T,N>::operator=(const Tqueue<T,N> &y) {

    // creates new array and iterates over old array and inputs values
    m_data = new T[N];
    for(int i = 0; i < N; i++) {
        m_data[i] = *y.m_data;
    } 
    m_front = y.m_front;
    m_back = y.m_back;
    m_size = y.m_size;
    return *this;
}

// Tqueue Constructor
// Sets all value of queue to default values
template <class T , int N> Tqueue<T,N>::Tqueue() {
   
    // Sets all values to default values
    m_data = new T[N];
    m_front = 0;
    m_back = 0;
    m_size = 0;

}

// Tqueue Compy Constructor
// Allows a new queue to be created from a previous queue in the declartion of new queue
template <class T , int N> Tqueue<T,N>::Tqueue( const Tqueue<T,N>& x ){

    // creates new array and iterates over old array and inputs values 
    m_data = new T[N];
    for(int i = 0; i < N; i++) {
        m_data[i] = *x.m_data;
    }
    m_front = x.m_front;
    m_back = x.m_back;
    m_size = x.m_size;

}

// Tqueue destructor
// deallocates the memory of the array
template <class T , int N> Tqueue<T,N>::~Tqueue() {

    delete[] m_data;

}

// enqueue
// Takes in a templates data type and queues it into the queue
template <class T , int N> void Tqueue<T,N>::enqueue(T data) {

    // Takes parameters and sets them in queue
    if(isFull() == 1) {
        cout << "Queue is full" << endl;
        
    } else {
        m_data[m_back] = data;
        m_back = (m_back + 1) % N; 
        m_size++;
    }

}

// dequeue
// dequeues the front of the queue
template <class T , int N> void Tqueue<T,N>::dequeue(T &data) {

    // takes parameter and sets to front of queue and dequeues it
    if(isEmpty() == 1) {
        cout << "Queue is empty" << endl;
    } else {
        data = m_data[m_front];
        m_front = (m_front + 1) % N;
        m_size--;
    }
}

// isFull
// returns value based on whether the queue is full or not
template <class T, int N> int Tqueue<T,N>::isFull() {

    if(size() == N) {
        return 1;
    } else { 
        return 0;
    }
}

// isEmpty
// returns value based on whether the queue is empty or not
template <class T, int N> int Tqueue<T,N>::isEmpty() {

   if(size() == 0) {
       return 1;
   } else {
       return 0;
   }
}

// size
// returns the current size of the queue
template <class T, int N> int Tqueue<T,N>::size() {

    return m_size;

}

// getFront
// returns the current front value
template <class T, int N> int Tqueue<T,N>::getFront() {

    return m_front;

}

// getBack
// returns the current back value
template <class T, int N> int Tqueue<T,N>::getBack() {

    return m_back;

}
#endif
