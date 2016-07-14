#ifndef _APSTACK_H
#define _APSTACK_H

// uncomment line below if bool not built-in type
// #include "bool.h"

// *******************************************************************
//  Last Revised: 8/14/98
//
//  - commented out the #include "bool.h", dhj
//  - abort -->> exit
//
// APCS stack class
// *******************************************************************

#include "apvector.h"                  // used for stack implementation

template <class itemType>
class apstack
{
  public:
    
  // constructors/destructor

    apstack( );                            // construct empty stack
    apstack( const apstack & s );          // copy constructor
    ~apstack( );                           // destructor

  // assignment

    const apstack & operator = ( const apstack & rhs );

  // accessors

    const itemType & top( )      const;   // return top element (NO pop)
    bool             isEmpty( )  const;   // return true if empty, else false
    int              length( )   const;   // return number of elements in stack

  // modifiers

    void push( const itemType & item );   // push item onto top of stack
    void pop( );                          // pop top element
    void pop( itemType & item );          // combines pop and top
    void makeEmpty( );                    // make stack empty (no elements)

  private:

    int myTop;                            // index of top element
    apvector<itemType> myElements;        // storage for stack
};

  // **********************************************************************
  //
  // Specifications for stack functions
  //
  // Any violation of a function's precondition will result in an error message
  // followed by a call to exit.
  //
  //
  // constructors/destructor
  //
  //  apstack( )
  //    postcondition: the stack is empty
  //
  //  apstack( const apstack & s )
  //    postcondition: stack is a copy of s
  //
  //  ~apstack( )
  //    postcondition: stack is destroyed
  //
  // assignment
  //
  //  const apstack & operator = ( const apstack & rhs )
  //    postcondition: normal assignment via copying has been performed
  //
  // accessors
  //
  //  const itemType & top( ) const
  //    precondition: stack is [e1, e2, ... en] with n >= 1
  //    postcondition: returns en
  //
  //  bool isEmpty( ) const
  //     postcondition: returns true if stack is empty, false otherwise
  //
  //  int length( ) const
  //     postcondition: returns # of elements currently in stack
  //
  // modifiers
  //
  //  void push( const itemType & item )
  //     precondition: stack is [e1, e2...en] with  n >= 0
  //     postcondition: stack is [e1, e2, ... en, item]
  //
  //  void pop( )
  //     precondition: stack is [e1, e2, ... en] with n >= 1
  //     postcondition: stack is [e1, e2, ... e(n-1)]
  //
  //
  //  void pop(itemType & item )
  //     precondition: stack is [e1,e2,...en] with n >= 1
  //     postcondition: stack is [e1,e2,...e(n-1)] and item == en
  //
  //  void makeEmpty( )
  //     postcondition:  stack is empty
  //
  //  Examples of variable definition 
  //
  //    apstack<int> istack;                    // creates empty stack of integers
  //    apstack<double> dstack;                 // creates empty stack of doubles
  //

#include "apstack.cpp"

#endif 


