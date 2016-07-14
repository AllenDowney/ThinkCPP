#include <iostream>

void newLine ()
{
  cout << endl;
}

void threeLine ()
{
  newLine ();  newLine ();  newLine ();
}

void nLines (int n) {
  if (1) {
    // cout << endl;
    nLines (n-1);
  }
}

void main ()
{
  cout << "First Line." << endl;
  nLines (3);
  cout << "Second Line." << endl;
}

