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

void processLine (const apstring& line, Set& cities, apmatrix<int>& distances)
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
  int dist = convertToInt (distString);

  int index1 = cities.add (city1);
  int index2 = cities.add (city2);

  distances[index1][index2] = dist;
  distances[index2][index1] = dist;
}

void main ()
{
  apstring name;
  apstring line;
  int x;
  ifstream infile ("distances");
  ofstream outfile ("temp");
  Set cities (2);

  apmatrix<int> distances (50, 50, 0);

  if (infile.good() == false || outfile.good() == false) {
    cout << "Unable to open one of the files." << endl;
    exit (1);
  }

  while (true) {
    getline (infile, line);
    if (infile.eof()) break;
    processLine (line, cities, distances);
  }


  for (int i=0; i<cities.getNumElements(); i++) {
    cout << cities.getElement(i) << "\t";

    for (int j=0; j<=i; j++) {
      cout << distances[i][j] << "\t";
    }
    cout << endl;
  }

  cout << "\t";
  for (int i=0; i<cities.getNumElements(); i++) {
    cout << cities.getElement(i) << "\t";
  }
  cout << endl;
}

