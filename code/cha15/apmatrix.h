#ifndef _APMATRIX_H
#define _APMATRIX_H

#include "apvector.h"

// *******************************************************************
// Last Revised: 8/14/98
//               changed abort() to exit(1), dhj
//
// APCS matrix class
//
// extends apvector.h to two dimensional "safe" (range-checked) matrices
// examples are given at the end of this file
// *******************************************************************

template <class itemType>
class apmatrix
{
  public:

  // constructors/destructor
    apmatrix( );                                      // default size 0 x 0
    apmatrix( int rows, int cols );                   // size rows x cols
    apmatrix( int rows, int cols,
            const itemType & fillValue );           // all entries == fillValue
    apmatrix( const apmatrix & mat );                   // copy constructor
    ~apmatrix( );                                     // destructor

  // assignment
    const apmatrix & operator = ( const apmatrix & rhs );

  // accessors
    int numrows( ) const;                             // number of rows
    int numcols( ) const;                             // number of columns

  // indexing
    const apvector<itemType> & operator [ ] ( int k ) const;  // range-checked indexing
    apvector<itemType> & operator [ ] ( int k );              // range-checked indexing

  // modifiers
    void resize( int newRows, int newCols );   // resizes matrix to newRows x newCols
                                               // (can result in losing values)
  private:

    int myRows;                             // # of rows (capacity)
    int myCols;                             // # of cols (capacity)
    apvector<apvector<itemType> > myMatrix; // the matrix of items
};


// *******************************************************************
// Specifications for matrix functions
//
// To use this class, itemType must satisfy the same constraints
// as forvector class.
//
// Any violation of a function's precondition will result in an error  message
// followed by a call to exit.
//
// constructors/destructor
//
//  apmatrix( );
//     postcondition: matrix of size 0x0 is constructed, and therefore
//                    will need to be resized later
//
//  apmatrix( int rows, int cols );
//     precondition: 0 <= rows and 0 <= cols
//     postcondition: matrix of size rows x cols is constructed
//
//  apmatrix( int rows, int cols, const itemType & fillValue );
//     precondition: 0 <= rows and 0 <= cols
//     postcondition: matrix of size rows x cols is constructed
//                    all entries are set by assignment to fillValue after
//                    default construction
//
//  apmatrix( const apmatrix<itemType> & mat );
//     postcondition: matrix is a copy of mat
//
//  ~apmatrix( );
//     postcondition: matrix is destroyed
//
// assignment
//
//  const apmatrix & operator = ( const apmatrix & rhs );
//     postcondition: normal assignment via copying has been performed
//                    (if matrix and rhs were different sizes, matrix has 
//                    been resized to match the size of rhs)
//
// accessors
//
//  int numrows( ) const;
//     postcondition: returns number of rows
//
//  int numcols( ) const;
//     postcondition: returns number of columns
//
// indexing
//
//  const apvector<itemType> & operator [ ] ( int k ) const;
//     precondition: 0 <= k < number of rows
//     postcondition: returns k-th row
//
//  apvector<itemType> & operator [ ] ( int k );
//     precondition: 0 <= k < number of rows
//     postcondition: returns k-th row
//
// modifiers
//
//  void resize( int newRows, int newCols );
//     precondition: matrix size is rows X cols,
//                   0 <= newRows and 0 <= newCols
//     postcondition: matrix size is newRows X newCols;
//                    for each 0 <= j <= min(rows,newRows) and
//                    for each 0 <= k <= min(cols,newCols), matrix[j][k] is
//                    a copy of the original; other elements of matrix are
//                    initialized using the default constructor for itemType
//                    Note: if newRows < rows or newCols < cols,
//                          elements may be lost
//
//  Examples of use:
//
//     apmatrix<double> dmat( 100, 80 );       // 100 x 80 matrix of doubles
//     apmatrix<double> dzmat( 100, 80, 0.0 ); // initialized to 0.0
//     apmatrix<apstring> smat( 300, 1 );      // 300 strings
//     apmatrix<int> imat;                     // has room for 0 ints

#include "apmatrix.cpp"
#endif


