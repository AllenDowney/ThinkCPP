#include <iostream.h>
#include <stdlib.h>
#include "apmatrix.h"

void main ()
{
  apmatrix<double> matrix (4, 4, 0.0);

  for (int row = 0; row<matrix.numrows(); row++) {
    for (int col = 0; col<matrix.numcols(); col++) {
      cout << matrix[row][col] << "\t";
    }
    cout << endl;
  }
}
