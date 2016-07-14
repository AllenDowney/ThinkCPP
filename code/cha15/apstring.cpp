// *******************************************************************
//  Revised: January 13, 1998,  <= and >= redefined using ! and <
//                              operator += now takes constant
//                              amortized time for adding one char
//
//  Revised: November 19, 1998, replaced assert with exit: operator[]
//                              changed operator >> and getline
//                              so no limit on size of strings read
//
//  APCS string class  IMPLEMENTATION
//
//  see apstring.h for complete documentation of functions
//
//  string class consistent with a subset of the standard C++ string class
//  as defined in the draft ANSI standard
// *******************************************************************

#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include "apstring.h"

const int npos = -1;

apstring::apstring()
// postcondition: string is empty
{
    myLength = 0;
    myCapacity = 1;
    myCstring = new char[myCapacity];
    myCstring[0] = '\0';           // make c-style string zero length
}


apstring::apstring(const char * s)
//description:   constructs a string object from a literal string
//               such as "abcd"
//precondition:  s is '\0'-terminated string as used in C
//postcondition: copy of s has been constructed
{
    assert (s != 0);               // C-string not NULL?

    myLength = strlen(s);
    myCapacity = myLength + 1;      // make room for '\0'
    myCstring = new char[myCapacity];
    strcpy(myCstring,s);
}

apstring::apstring(const apstring & str)
//description:   copy constructor
//postcondition: copy of str has been constructed
{
    myLength = str.length();
    myCapacity = myLength + 1;
    myCstring = new char[myCapacity];
    strcpy(myCstring,str.myCstring);
}

apstring::~apstring()
//description:   destructor
//postcondition: string is destroyed
{
    delete[] myCstring;                // free memory
}

const apstring& apstring::operator =(const apstring & rhs)
//postcondition: normal assignment via copying has been performed
{
    if (this != &rhs)                             // check aliasing
    {
        if (myCapacity < rhs.length() + 1)        // more memory needed?
        {
            delete[] myCstring;                   // delete old string
            myCapacity = rhs.length() + 1;        // add 1 for '\0'
            myCstring = new char[myCapacity];
        }
        myLength = rhs.length();
        strcpy(myCstring,rhs.myCstring);
    }
    return *this;
}


const apstring& apstring::operator = (const char * s)
//description:   assignment from literal string such as "abcd"
//precondition:  s is '\0'-terminated string as used in C
//postcondition: assignment via copying of s has been performed
{

    int len = 0;                         // length of newly constructed string
    assert(s != 0);                      // make sure s non-NULL
    len = strlen(s); // # of characters in string

    // free old string if necessary

    if (myCapacity < len + 1)
    {
   delete[] myCstring;  // delete old string
   myCapacity = len + 1;   // add 1 for '\0'
   myCstring = new char[myCapacity];
    }
    myLength = len;
    strcpy(myCstring,s);
    return *this;
}

const apstring& apstring::operator = (char ch)
//description:   assignment from character as though single char string
//postcondition: assignment of one-character string has been performed
{
    if (myCapacity < 2)
    {
        delete [] myCstring;
        myCapacity = 2;
        myCstring = new char[myCapacity];
    }
    myLength = 1;
    myCstring[0] = ch;  // make string one character long
    myCstring[1] = '\0';
    return *this;
}

int apstring::length( ) const
//postcondition: returns # of chars in string
{
    return myLength;
}

const char * apstring::c_str() const
//description:   convert string into a '\0'-terminated string as
//               used in C for use with functions
//               that have '\0'-terminated string parameters.
//postcondition: returns the equivalent '\0'-terminated string
{
    return myCstring;
}

char& apstring::operator[](int k)
// precondition:  0 <= k < length()
// postcondition: returns copy of the kth character
// note:          if this reference is used to write a '\0'
//                subsequent results are undefined
{
    if (k < 0 || myLength <= k)
    {
        cerr << "index out of range: " << k << " string: " << myCstring
            << endl;
        exit(1);
    }
    return myCstring[k];
}

char apstring::operator[](int k) const
// precondition:  0 <= k < length()
// postcondition: returns copy of the kth character
{
    if (k < 0 || myLength <= k)
    {
        cerr << "index out of range: " << k << " string: " << myCstring
            << endl;
        exit(1);
    }
    return myCstring[k];
}

ostream& operator <<(ostream & os, const apstring & str)
//postcondition: str is written to output stream os
{
    return os << str.c_str();
}

istream& operator >>(istream & is, apstring & str)
//precondition:  input stream is open for reading
//postcondition: the next string from input stream is has been read
//               and stored in str
{
    char ch;
    str = "";    // empty string, will build one char at-a-time
    is >> ch;    // whitespace skipped, first non-white char in ch
    
    if (! is.fail())
    {
        do
        {
            str += ch;
            is.get(ch);
        } while (! is.fail() && ! isspace(ch));
        
        if (isspace(ch))    // put whitespace back on the stream
        {
            is.putback(ch);     
        }
    }
    
    return is;
}


istream & getline(istream & is, apstring & str)
//description:   reads a line from input stream is into the string str
//precondition:  input stream is open for reading
//postcondition: chars from input stream is up to '\n' have been read
{

    char ch;
    str = "";     // empty string, will build one char at-a-time
    
    while (is.get(ch) && ch != '\n')
    {
        str += ch;
    }
    
    return is;
}

const apstring& apstring::operator +=(const apstring & str)
//postcondition: concatenates a copy of str onto this string
{

    apstring copystring(str);         // copy to avoid aliasing problems

    int newLength = length() + str.length(); // self + added string
    int lastLocation = length();      // index of '\0'

    // check to see if local buffer not big enough
    if (newLength >= myCapacity)
    {
        myCapacity = newLength + 1;
   if (str.length() == 1)  // special case for catenating one char
   {                       // make room for future catenations
       myCapacity *= 2;
   }
        char * newBuffer = new char[myCapacity];
        strcpy(newBuffer,myCstring); // copy into new buffer
        delete [] myCstring;       // delete old string
        myCstring = newBuffer;
    }

    // now catenate str (copystring) to end of myCstring
    strcpy(myCstring+lastLocation,copystring.c_str() );
    myLength = newLength;           // update information

    return *this;
}

const apstring & apstring::operator += ( char ch )
// postcondition: concatenates a copy of ch onto this string
{
    apstring temp;   // make string equivalent of ch
    temp = ch;
    *this += temp;
    return *this;
}

apstring operator +(const apstring & lhs, const apstring & rhs)
// postcondition: returns concatenation of lhs with rhs
{
    apstring result(lhs);  // copies lhs to result
    result += rhs;   // catenate rhs
    return result;   // returns a copy of result
}

apstring operator + ( char ch, const apstring & str )
// postcondition: returns concatenation of ch with str
{
    apstring result; // make string equivalent of ch
    result = ch;
    result += str;
    return result;
}

apstring operator + ( const apstring & str, char ch )
// postcondition: returns concatenation of str with ch
{
    apstring result(str);
    result += ch;
    return result;
}


apstring apstring::substr(int pos, int len) const
//description:   extract and return the substring of length len starting
//               at index pos
//precondition:  this string represents c0, c1, ..., c(n-1)
//               0 <= pos <= pos + len - 1 < n.
//postcondition: returns the string that represents
//               c(pos), c(pos+1), ..., c(pos+len-1)
//
{
    if (pos < 0)                       // start at front when pos < 0
    {
       pos = 0;
    }

    if (pos >= myLength) return "";     // empty string

    int lastIndex = pos + len - 1;      // last char's index (to copy)
    if (lastIndex >= myLength)          // off end of string?
    {
        lastIndex = myLength-1;
    }

    apstring result(*this);               // make sure enough space allocated

    int j,k;
    for(j=0,k=pos; k <= lastIndex; j++,k++)
    {
        result.myCstring[j] = myCstring[k];
    }
    result.myCstring[j] = '\0';         // properly terminate C-string
    result.myLength = j;                // record length properly
    return result;
}

int apstring::find(const apstring & str)  const
//description:   find the first occurrence of the string str within this
//               string and return the index of the first character.  If
//               str does not occur in this string, then return npos.
//precondition:  this string represents c0, c1, ..., c(n-1)
//               str represents s0, s1, ...,s(m-1)
//postcondition: if s0 == ck0, s1 == ck1, ..., s(m-1) == ck(m-1) and
//               there is no j < k0 such that s0 = cj, ...., sm == c(j+m-1),
//               then returns k0;
//               otherwise returns npos
{
    int len = str.length();
    int lastIndex = length() - len;
    int k;
    for(k=0; k <= lastIndex; k++)
    {
        if (strncmp(myCstring + k,str.c_str(),len) == 0) return k;
    }
    return npos;
}

int apstring::find( char ch ) const
// description:   finds the first occurrence of the character ch within this
//                string and returns the index.  If ch does not occur in this
//                string, then returns npos.
// precondition:  this string represents c0, c1, ..., c(n-1)
// postcondition: if ch == ck, and there is no j < k such that ch == cj
//                then returns k;
//                otherwise returns npos
{
    int k;
    for(k=0; k < myLength; k++)
    {
        if (myCstring[k] == ch)
        {
       return k;
   }
    }
    return npos;
}


bool operator == ( const apstring & lhs, const apstring & rhs )
{
    return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator != ( const apstring & lhs, const apstring & rhs )
{
    return ! (lhs == rhs);
}

bool operator <  ( const apstring & lhs, const apstring & rhs )
{
    return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator <= ( const apstring & lhs, const apstring & rhs )
{
    return !( rhs < lhs );
}
bool operator >  ( const apstring & lhs, const apstring & rhs )
{
    return rhs < lhs;
}

bool operator >= ( const apstring & lhs, const apstring & rhs )
{
    return ! ( lhs < rhs );
}
