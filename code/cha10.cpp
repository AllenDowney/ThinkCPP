#include <iostream.h>
#include <stdlib.h>
#include "apvector.h"

apvector<int> randomVector (int n) {
  apvector<int> vec (n);
  for (int i = 0; i<vec.length(); i++) {
    vec[i] = random () % 10;
  }
  return vec;
}

void printVector (apvector<int> vec) {
  for (int i = 0; i<vec.length(); i++) {
    cout << vec[i];
  }
}

int howMany (apvector<int> vec, int value) {
  int count = 0;
  for (int i=0; i< vec.length(); i++) {
    if (vec[i] == value) count++;
  }
  return count;
}

void main ()
{
  int numValues = 100000;

  srandom (17);
  apvector<int> vector = randomVector (numValues);
  apvector<int> histogram (10, 0);

  for (int i = 0; i<numValues; i++) {
    int index = vector[i];
    histogram[index]++;
  }

  for (int i = 0; i<10; i++) {
    cout << i << "\t" << histogram[i] << endl;
  }

}
