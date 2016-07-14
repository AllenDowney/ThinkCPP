#include <iostream.h>
#include <math.h>
#include <assert.h>

class Complex
{
  double real, imag;
  double mag, theta;
  bool cartesian, polar;

public:
  void calculateCartesian ();
  void calculatePolar ();

  Complex () { cartesian = false;  polar = false; }

  Complex (double r, double i)
  {
    real = r;  imag = i;
    cartesian = true;  polar = false;
  }

  void printCartesian ();
  void printPolar ();

  double getReal ();
  double getImag ();
  double getMag ();
  double getTheta ();

  void setCartesian (double r, double i);
  void setPolar (double m, double t);
};

void Complex::setCartesian (double r, double i)
{
  real = r;  imag = i;
  cartesian = true;  polar = false;
}

void Complex::setPolar (double m, double t)
{
  mag = m;  theta = t;
  cartesian = false;  polar = true;
}


void Complex::calculateCartesian ()
{
  if (polar == false) {
    cout <<
      "calculateCartesian failed because polar representation is invalid"
	 << endl;
    exit (1);
  }
  real = mag * cos (theta);
  imag = mag * sin (theta);
  cartesian = true;
}

void Complex::calculatePolar ()
{
  assert (cartesian);
  mag = sqrt (real* real + imag * imag);
  theta = atan2 (imag, real);
  polar = true;
}

void Complex::printCartesian ()
{
  cout << getReal() << " + " << getImag() << "i" << endl;
}

void Complex::printPolar ()
{
  cout << getMag() << " e^ " << getTheta() << "i" << endl;
}


Complex add (Complex& a, Complex& b)
{
  double real = a.getReal() + b.getReal();
  double imag = a.getImag() + b.getImag();
  Complex sum (real, imag);
  return sum;
}

Complex mult (Complex& a, Complex& b)
{
  double mag = a.getMag() * b.getMag();
  double theta = a.getTheta() + b.getTheta();
  Complex product;
  product.calculatePolar();
  product.setPolar (mag, theta);
  return product;
}

double Complex::getReal ()
{
  if (cartesian == false) calculateCartesian ();
  return real;
}

double Complex::getImag ()
{
  if (cartesian == false) calculateCartesian ();
  return imag;
}

double Complex::getMag ()
{
  if (polar == false) calculatePolar ();
  return mag;
}

double Complex::getTheta ()
{
  if (polar == false) calculatePolar ();
  return theta;
}

void main ()
{
  Complex c1 (2.0, 3.0);
  Complex c2 (3.0, 4.0);

  c1.printPolar();
  c2.printPolar();

  Complex sum = add (c1, c2);
  sum.printCartesian();

  Complex product = mult (c1, c2);
  product.printPolar();
  product.printCartesian();
}
