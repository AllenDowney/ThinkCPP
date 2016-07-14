#include <fstream.h>
#include <iostream.h>
#include <stdlib.h>
#include <ctype.h>
#include "apstring.h"
#include "apvector.h"
#include "apmatrix.h"

class Set {
private:
  apvector<apstring> elements;
  int numElements;

public:
  Set () { numElements = 0; }
  Set (int n);

  int find (const apstring& s) const;
  int add (const apstring& s);
  apstring getElement (int i) const;
  int getNumElements () const;
};

Set::Set (int n)
{
  apvector<apstring> temp (n);
  elements = temp;
  numElements = 0;
}

int Set::find (const apstring& s) const
{
  for (int i=0; i<numElements; i++) {
    if (elements[i] == s) return i;
  }
  return -1;
}

int Set::add (const apstring& s)
{
  // if the element is already in the set, return its index
  int index = find (s);
  if (index != -1) return index;

  // if the apvector is full, double its size
  if (numElements == elements.length()) {
    elements.resize (elements.length() * 2);
  }

  // add the new elements and return its index
  index = numElements;
  elements[index] = s;
  numElements++;
  return index;
}

apstring Set::getElement (int i) const
{
  if (i < numElements) {
    return elements[i];
  } else {
    cout << "Set index out of range." << endl;
    exit (1);
  }
}

int Set::getNumElements () const
{
  return numElements;
}

class DistMatrix {
private:
  Set cities;
  apmatrix<int> distances;

public:
  DistMatrix (int rows);

  void add (const apstring& city1, const apstring& city2, int dist);
  int distance (int i, int j) const;
  int distance (const apstring& city1, const apstring& city2) const;
  apstring cityName (int i) const;
  int numCities () const;
  void print ();
};

DistMatrix::DistMatrix (int rows)
{
  Set set (rows);
  cities = set;
  apmatrix<int> matrix (rows, rows);
  distances = matrix;
}

void DistMatrix::add (const apstring& city1, const apstring& city2, int dist)
{
  int index1 = cities.add (city1);
  int index2 = cities.add (city2);

  if (index1 >= distances.numrows() || index1 >= distances.numcols()) {
    distances.resize (distances.numrows()*2, distances.numcols()*2);
  }
  if (index2 >= distances.numrows() || index2 >= distances.numcols()) {
    distances.resize (distances.numrows()*2, distances.numcols()*2);
  }
  distances[index1][index2] = dist;
  distances[index2][index1] = dist;
}


int DistMatrix::distance (int i, int j) const
{
  if (i < cities.getNumElements() &&
      j < cities.getNumElements()) {
    return distances[i][j];
  } else {
    cout << "DistMatrix index out of range." << endl;
    exit (1);
  }
}


int DistMatrix::distance (const apstring& city1, const apstring& city2) const
{
  int index1 = cities.find (city1);
  int index2 = cities.find (city2);

  if (index1 == -1 || index2 == -1) {
    cout << "DistMatrix unknown city." << endl;
    exit (1);
  }
  return distance (index1, index2);
}

apstring DistMatrix::cityName (int i) const
{
  return cities.getElement (i);
}

int DistMatrix::numCities () const
{
  return cities.getNumElements ();
}

void DistMatrix::print ()
{
  for (int i=0; i<numCities(); i++) {
    cout << cityName(i) << "\t";

    for (int j=0; j<=i; j++) {
      cout << distance (i, j) << "\t";
    }
    cout << endl;
  }

  cout << "\t";
  for (int i=0; i<numCities(); i++) {
    cout << cityName(i) << "\t";
  }
  cout << endl;
}


int find (const apstring& s, char c, int i)
{
  while (i<s.length()) {
    if (s[i] == c) return i;
    i = i + 1;
  }
  return -1;
}

int convertToInt (const apstring& s)
{
  apstring digitString = "";

  for (int i=0; i<s.length(); i++) {
    if (isdigit (s[i])) {
      digitString += s[i];
    }
  }
  return atoi (digitString.c_str());
}

void processLine (const apstring& line, DistMatrix& distances)
{
  // the character we are looking for is a quotation mark
  char quote = '\"';

  // store the indices of the quotation marks in a vector
  apvector<int> quoteIndex (4);

  // find the first quotation mark using the built-in find
  quoteIndex[0] = line.find (quote);

  // find the other quotation marks using the find from Chapter 7
  for (int i=1; i<4; i++) {
    quoteIndex[i] = find (line, quote, quoteIndex[i-1]+1);
  }

  // break the line up into substrings
  int len1 = quoteIndex[1] - quoteIndex[0] - 1;
  apstring city1 = line.substr (quoteIndex[0]+1, len1);
  int len2 = quoteIndex[3] - quoteIndex[2] - 1;
  apstring city2 = line.substr (quoteIndex[2]+1, len2);
  int len3 = line.length() - quoteIndex[2] - 1;
  apstring distString = line.substr (quoteIndex[3]+1, len3);
  int distance = convertToInt (distString);

  distances.add (city1, city2, distance);
}

void main ()
{
  apstring line;
  ifstream infile ("distances");

  DistMatrix distances (2);

  if (infile.good() == false) {
    cout << "Unable to open one of the files." << endl;
    exit (1);
  }

  while (true) {
    getline (infile, line);
    if (infile.eof()) break;
    processLine (line, distances);
  }

  distances.print ();
}

