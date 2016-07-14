#include <iostream>

struct Point {
  double x, y;
};

struct Rectangle {
  Point corner;
  double width, height;
};  

void printPoint (Point p)
{
  cout << "(" << p.x << ", " << p.y << ")" << endl;
}

void reflect (Point& p)
{
  double temp = p.x;
  p.x = p.y;
  p.y = temp;
}

double distance (Point p1, Point p2)
{
  double dx = p2.x - p1.x;
  double dy = p2.y - p1.y;
  return sqrt (dx*dx + dy*dy);
}

Point findCenter (Rectangle& box)
{
  double x = box.corner.x + box.width/2;
  double y = box.corner.y + box.height/2;
  Point result = {x, y};
  return result;
}

void swap (int& x, int& y)
{
  int temp = x;
  x = y;
  y = temp;
}

void main ()
{
  Rectangle box = { {0.0, 0.0}, 100, 200 };

  Point blank;
  blank = (Point){ 3.0, 4.0 };

  Point center = findCenter (box);
  printPoint (center);

  Point center2 = findCenter (box);
  printPoint (center2);

  reflect (center);
  printPoint (center);
  printPoint (center2);

  int i = 7;
  int j = 9;
  swap (i, j+1);
  cout << i << j << endl;
}

