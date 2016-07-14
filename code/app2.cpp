#include <iostream>
#include "apstring.h"

int main ()
{
  apstring name;

  cout << "What is your name? ";
  cin >> name;
  cout << name << endl;


  cout << "What is your name? ";
  getline (cin, name);
  cout << name << endl;

  return 0;
}

