#include<iostream.h>

double add (double x, int y)
{
  cout << "Version 1" << endl;
  return x + y;
}

double add (int x, double y)
{
  cout << "Version 2" << endl;
  return x + y;
}

int main ()
{
  cout << add (3.0, 4) << endl;
  cout << add (5, 6.0) << endl;
  cout << add (7, 8) << endl;
  return 0;
}
