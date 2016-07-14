// *******************************************************************
//  Last Revised: 8/14/98
//                abort changed to exit, dhj
//
//  September 1, 1997 -- APCS matrix class  IMPLEMENTATION
//
//  see matrix.h for complete documentation of functions
//
//  extends vector class to two-dimensional matrices
// *******************************************************************

#include "apmatrix.h"
#include <stdlib.h>
#include <iostream.h>

template <class itemType>
apmatrix<itemType>::apmatrix()
        : myRows(0),
          myCols(0),
          myMatrix(0)
     
// postcondition: matrix of size 0x0 is constructed, and therefore
//                will need to be resized later
{

}
template <class itemType>
apmatrix<itemType>::apmatrix(int rows,int cols)      
        : myRows(rows),
          myCols(cols),
          myMatrix(rows)
     
// precondition: 0 <= rows and 0 <= cols
// postcondition: matrix of size rows x cols is constructed
{
    int k;
    for(k=0; k < rows; k++)
    {
        myMatrix[k].resize(cols);
    }
}

template <class itemType>
apmatrix<itemType>::apmatrix(int rows, int cols, const itemType & fillValue)
        : myRows(rows),
          myCols(cols),
          myMatrix(rows)
     
// precondition: 0 <= rows and 0 <= cols
// postcondition: matrix of size rows x cols is constructed
//                all entries are set by assignment to fillValue after
//                default construction
//     
{
    int j,k;
    for(j=0; j < rows; j++)
    {
        myMatrix[j].resize(cols);
        for(k=0; k < cols; k++)
        {
            myMatrix[j][k] = fillValue;
        }
    }
}

template <class itemType>
apmatrix<itemType>::apmatrix(const apmatrix<itemType> & mat)
    : myRows(mat.myRows),
      myCols(mat.myCols),
      myMatrix(mat.myRows)
     
// postcondition: matrix is a copy of mat
{
    int k;
    // copy elements
    for(k = 0; k < myRows; k++)
    {
        // cast to avoid const problems (const -> non-const)
        myMatrix[k] = (apvector<itemType> &) mat.myMatrix[k];
    }   
}

template <class itemType>
apmatrix<itemType>::~apmatrix ()
// postcondition: matrix is destroyed
{
    // vector destructor frees everything
}

template <class itemType>
const apmatrix<itemType> &
apmatrix<itemType>::operator = (const apmatrix<itemType> & rhs)
// postcondition: normal assignment via copying has been performed
//                (if matrix and rhs were different sizes, matrix has 
//                been resized to match the size of rhs)     
{
    if (this != &rhs)                    // don't assign to self!
    {
        myMatrix.resize(rhs.myRows);     // resize to proper # of rows
        myRows = rhs.myRows;             // set dimensions
        myCols = rhs.myCols;
        
        // copy rhs
        int k;
        for(k=0; k < myRows; k++)
        {
       myMatrix[k] = rhs.myMatrix[k];
        }
    }
    return *this;       
}

template <class itemType>
int apmatrix<itemType>::numrows() const
// postcondition: returns number of rows
{
    return myRows;
}

template <class itemType>
int apmatrix<itemType>::numcols() const
// postcondition: returns number of columns
{
    return myCols;
}


template <class itemType>
void apmatrix<itemType>::resize(int newRows, int newCols)
// precondition: matrix size is rows X cols,
//               0 <= newRows and 0 <= newCols
// postcondition: matrix size is newRows X newCols;
//                for each 0 <= j <= min(rows,newRows) and
//                for each 0 <= k <= min(cols,newCols), matrix[j][k] is
//                a copy of the original; other elements of matrix are
//                initialized using the default constructor for itemType
//                Note: if newRows < rows or newCols < cols,
//                      elements may be lost
//
{
    int k;
    myMatrix.resize(newRows);

    for(k=0; k < newRows; k++)
    {
        myMatrix[k].resize(newCols);
    }
    myRows = newRows;
    myCols = newCols;
}

template <class itemType>
const apvector<itemType> & 
apmatrix<itemType>::operator [] (int k) const
// precondition: 0 <= k < number of rows
// postcondition: returns k-th row     
{
    if (k < 0 || myRows <= k)
    {
        cerr << "Illegal matrix index: " << k << " max index = ";
        cerr << myRows-1 << endl;       
        exit(1);
    }    
    return myMatrix[k];
}

template <class itemType>
apvector<itemType> & 
apmatrix<itemType>::operator [] (int k)
// precondition: 0 <= k < number of rows
// postcondition: returns k-th row
{
    if (k < 0 || myRows <= k)
    {
        cerr << "Illegal matrix index: " << k << " max index = ";
        cerr << myRows-1 << endl;       
        exit(1);
    }    
    return myMatrix[k];
}







