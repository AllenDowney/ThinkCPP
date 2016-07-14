#ifndef _APQUEUE_H
#define _APQUEUE_H

// uncomment line below if bool not built-in type
// #include "bool.h"

// *******************************************************************
// Last Revised: 8-14-98
//
//  - commented out the #include "bool.h", dhj
//  - updated comments for constructor/descructor, dhj
//
// APCS queue class
// *******************************************************************

#include "apvector.h"                          // used to implement queue

template <class itemType>
class apqueue
{
  public:

  // constructors/destructor

    apqueue( );                                 // construct empty queue
    apqueue( const apqueue & q );                 // copy constructor
    ~apqueue( );                                // destructor

  // assignment

    const apqueue & operator = ( const apqueue & rhs );

  // accessors

    const itemType & front( )   const;        // return front (no dequeue)
    bool             isEmpty( ) const;        // return true if empty else false
    int              length( )  const;        // return number of elements in queue

  // modifiers

    void enqueue( const itemType & item );    // insert item (at rear)
    void dequeue( );                          // remove first element
    void dequeue( itemType & item );          // combine front and dequeue
    void makeEmpty( );                        // make queue empty

   private:
   
    int mySize;                    // # of elts currently in queue
    int myFront;                   // index of first element
    int myBack;                    // index of last element
    apvector<itemType> myElements; // internal storage for elements

        // private helper functions
    void DoubleQueue();              // double storage for myElements
    void Increment(int & val) const; // add one with wraparound 
};

// *******************************************************************
// Specifications for queue functions
//
// Any violation of a function's precondition will result in an error message
// followed by a call to exit.
//
// constructors/destructor
//
//  apqueue( )
//     postcondition: the queue is empty
//
//  apqueue( const apqueue & q )
//     postcondition: queue is a copy of q
//
//  ~apqueue( )
//     postcondition: queue is destroyed
//
// assignment
//
//  const apqueue & operator = ( const apqueue & rhs )
//     postcondition: normal assignment via copying has been performed
//
// accessors
//
//  const itemType & front( ) const
//     precondition: queue is [e1, e2, ..., en] with n >= 1
//     postcondition: returns e1
//
//  bool isEmpty( ) const
//     postcondition: returns true if queue is empty, false otherwise
//
//  int length( ) const
//     precondition: queue is [e1, e2, ..., en] with n >= 0
//     postcondition:  returns n
//
// modifiers:
//
//  void enqueue( const itemType & item )
//     precondition: queue is [e1, e2, ..., en] with n >= 0
//     postcondition: queue is [e1, e2, ..., en, item]
//
//  void dequeue( )
//     precondition: queue is [e1, e2, ..., en] with n >= 1
//     postcondition: queue is [e2, ..., en]
//
//  void dequeue( itemType & item )
//     precondition: queue is [e1, e2, ..., en] with n >= 1
//     postcondition:  queue is [e2, ..., en] and item == e1
//
//  void makeEmpty( )
//     postcondition: queue is empty
//
// Examples for use:
//
//    apqueue<int> iqueue;             // creates empty queue of integers
//    apqueue<double> dqueue           // creates empty queue of doubles

#include "apqueue.cpp"


#endif                                        


