// *******************************************************************
//  Last Revised: 8/14/98
//
//  APCS queue class  IMPLEMENTATION
//
//  queue implemented using the APCS vector class
//  based on queue class in Mark Weiss' : Algorithms, Data Structures,
//                                        and Problem Solving with C++
// *******************************************************************



#include "apqueue.h"
#include <stdlib.h>

const int QDEFAULT_SIZE = 10;        // default initial queue size


template <class itemType>
apqueue<itemType>::apqueue()
   : mySize(0),     
     myFront(0),
     myBack( -1 ),
     myElements(QDEFAULT_SIZE)

// postcondition: the queue is empty     
{

}


template <class itemType>
apqueue<itemType>::apqueue(const apqueue<itemType> & q)
    : mySize(q.mySize),      
      myFront(q.myFront),
      myBack(q.myBack),
      myElements(q.myElements)
      
// postcondition: queue is a copy of q     
{
    
}

template <class itemType>
apqueue<itemType>::~apqueue()
// postcondition: queue is destroyed     
{
    // vector destructor takes care of memory
}

template <class itemType>
const apqueue<itemType> &
apqueue<itemType>::operator=(const apqueue<itemType> & rhs)
// postcondition: normal assignment via copying has been performed     
{
    if( this != &rhs) 
    {   
        mySize = rhs.mySize;               // copy all fields of rhs
        myElements.resize(rhs.myElements.length());  // resize storage
        myFront = 0;
        myBack = mySize - 1;               // index from 0 .. mySize - 1

        int k;
        int rhsk = rhs.myFront;
        
        for(k=0; k < mySize; k++)
        {
            myElements[k] = rhs.myElements[rhsk];
            Increment(rhsk);
        }
    }    
    return *this;
}

template <class itemType>
const itemType &
apqueue<itemType>::front() const
// precondition: queue is [e1, e2, ..., en] with n >= 1
// postcondition: returns e1
{
    return myElements[myFront];
}

template <class itemType>
bool
apqueue<itemType>::isEmpty() const
// postcondition: returns true if queue is empty, false otherwise
{
    return mySize == 0;
}

template <class itemType>
int
apqueue<itemType>::length() const
// precondition: queue is [e1, e2, ..., en] with n >= 0
// postcondition:  returns n
{
    return mySize;
}


template <class itemType>
void
apqueue<itemType>::enqueue(const itemType & item)
// precondition: queue is [e1, e2, ..., en] with n >= 0
// postcondition: queue is [e1, e2, ..., en, item]     
{
    if (mySize >= myElements.length()) // grow if necessary to add element
    {
        DoubleQueue();
    }
    
    Increment(myBack);                // add element at back of queue
    myElements[myBack] = item;
    mySize++;
}


template <class itemType>
void
apqueue<itemType>::dequeue()
// precondition: queue is [e1, e2, ..., en] with n >= 1
// postconditions:  queue is [e2, ..., en] and item == e1
{
    if (isEmpty())
    {
        cerr << "dequeue from empty queue" << endl;
        exit(1);
    }
    
    mySize--;                       // one fewer element
    Increment(myFront);
}


template <class itemType>
void
apqueue<itemType>::dequeue(itemType & item)
// precondition: queue is [e1, e2, ..., en] with n >= 1
// postcondition:  queue is [e2, ..., en] and item == e1
{
    if (isEmpty())
    {
        cerr << "dequeue from empty queue" << endl;
        exit(1);
    }
    item = myElements[myFront];
    mySize--;                       // one fewer element
    Increment(myFront);    
}

template <class itemType>
void
apqueue<itemType>::makeEmpty()
// postcondition: queue is empty
{
    mySize = 0;
    myFront = 0;
    myBack = -1;
}


template <class itemType>
void
apqueue<itemType>::Increment( int & val ) const
// postcondition: val increased by one relative to size of myElements
//                i.e., wraps to 0 after reaching capacity of vector storage
{
    val++;
    if (val >= myElements.length() )
    {        val = 0;
    }
}


template <class itemType>
void
apqueue<itemType>::DoubleQueue()
// precondition: queue = e1, e2, ..., en, size = n, capacity = m
// postcondition: queue = e1, e2, ..., en, size = n, capacity = 2*m      
{
    // this could be made more efficient by doing the copy
    // in place (without the temporary vector temp)
    
    apvector<itemType> temp(myElements.length()*2);   // new storage
    int j,k=myFront;                                  // copy to 0..
    for(j=0; j < mySize; j++)
    {
        temp[j] = myElements[k];
        Increment(k);
    }
    myElements = temp;     // reset private vars to mirror new storage
    myFront = 0;
    myBack = mySize-1;
}
