#include <iostream>
#include <cmath>

double pi = acos (-1);

double absoluteValue (double x) {
  if (x < 0) {
    return -x;
  } else if (x >= 0) {
    return x;
  }
}

double area (double radius) {
  double pi = acos (-1.0);
  double area = pi * radius * radius;
  return area;
}

double distance (double x1, double y1, double x2, double y2) {
  double dx = x2 - x1;
  double dy = y2 - y1;
  double dsquared = dx*dx + dy*dy;
  double result = sqrt (dsquared);
  return result;
}

double area (double xc, double yc, double xp, double yp) {
  return area (distance (xc, yc, xp, yp));
} 

bool isSingleDigit (int x)
{
  return (x >= 0 && x < 10);
}

int factorial (int n)
{
  if (n == 0) {
    return 1;
  } else {
    int recurse = factorial (n-1);
    int result = n * recurse;
    return result;
  }
}

void main ()
{
  bool fred;
  fred = true;
  bool testResult = false;

  double a = area (1.0, 2.0, 4.0, 6.0);
  cout << a << endl;

  cout << isSingleDigit (2) << endl;
  bool bigFlag = !isSingleDigit (17);

  cout << factorial (3) << endl;
}

