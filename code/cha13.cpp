#include <iostream.h>
#include <stdlib.h>
#include "apstring.h"
#include "apvector.h"

struct Deck;

struct Card
{
  int suit, rank;

  Card ();
  Card (int s, int r);

  void print () const;
  bool isGreater (const Card& c2) const;
  int find (const Deck& deck) const;
};

struct Deck {
  apvector<Card> cards;

  Deck ();
  Deck (int n);
  void print () const;
  int find (const Card& card) const;
  void swapCards (int i, int j);
  void shuffle ();
  int findLowestCard (int low, int high) const;
  void sort ();
  Deck subdeck (int low, int high) const;
};

// card constructors

Card::Card () { 
  suit = 0;  rank = 0;
}

Card::Card (int s, int r) { 
  suit = s;  rank = r;
}

// card member functions

void Card::print () const
{
  apvector<apstring> suits (4, "narf");
  suits[0] = "Clubs";
  suits[1] = "Diamonds";
  suits[2] = "Hearts";
  suits[3] = "Spades";

  apvector<apstring> ranks (14, "narf");
  ranks[1] = "Ace";
  ranks[2] = "2";
  ranks[3] = "3";
  ranks[4] = "4";
  ranks[5] = "5";
  ranks[6] = "6";
  ranks[7] = "7";
  ranks[8] = "8";
  ranks[9] = "9";
  ranks[10] = "10";
  ranks[11] = "Jack";
  ranks[12] = "Queen";
  ranks[13] = "King";

  cout << ranks[rank] << " of " << suits[suit] << endl;
}

bool equals (const Card& c1, const Card& c2)
{
  return ((c1.rank == c2.rank) && (c1.suit == c2.suit));
}

bool Card::isGreater (const Card& c2) const
{
  // first check the suits
  if (suit > c2.suit) return true;
  if (suit < c2.suit) return false;

  // if the suits are equal, check the ranks
  if (rank > c2.rank) return true;
  if (rank < c2.rank) return false;

  // if the ranks are also equal, return false
  return false;
}

apvector<Card> buildDeck ()
{
  apvector<Card> deck (52);

  int index = 0;
  for (int suit = 0; suit <= 3; suit++) {
    for (int rank = 1; rank <= 13; rank++) {
      deck[index].suit = suit;
      deck[index].rank = rank;
      index++;
    }
  }
  return deck;
}

int findBisect (const Card& card, const apvector<Card>& deck,
		int low, int high) {

  cout << low << ", " << high << endl;

  if (high < low) return -1;

  int mid = (high + low) / 2;

  if (equals (deck[mid], card)) return mid;

  if (deck[mid].isGreater (card)) {
    return findBisect (card, deck, low, mid-1);
  } else {
    return findBisect (card, deck, mid+1, high);
  }
}

Deck::Deck (int n)
{
  apvector<Card> temp (n);
  cards = temp;
}

Deck::Deck ()
{
  apvector<Card> temp (52);
  cards = temp;

  int i = 0;
  for (int suit = 0; suit <= 3; suit++) {
    for (int rank = 1; rank <= 13; rank++) {
      cards[i].suit = suit;
      cards[i].rank = rank;
      i++;
    }
  }
}

void Deck::print () const {
  for (int i = 0; i < cards.length(); i++) {
    cards[i].print ();
  }
}

int find (const Card& card, const Deck& deck) {
  for (int i = 0; i < deck.cards.length(); i++) {
    if (equals (deck.cards[i], card)) return i;
  }
  return -1;
}


int Deck::find (const Card& card) const {
  for (int i = 0; i < cards.length(); i++) {
    if (equals (cards[i], card)) return i;
  }
  return -1;
}

int Card::find (const Deck& deck) const {
  for (int i = 0; i < deck.cards.length(); i++) {
    if (equals (deck.cards[i], *this)) return i;
  }
  return -1;
}

int randomInt (int low, int high)
{
  return low + random() % (high-low+1);
}

void Deck::swapCards (int i, int j)
{
  Card temp = cards[i];
  cards[i] = cards[j];
  cards[j] = temp;
}

void Deck::shuffle ()
{
  for (int i=0; i<cards.length(); i++) {
    int j = randomInt (i, 51);
    swapCards (i, j);
  }
}

int Deck::findLowestCard (int low, int high) const
{
  int mindex = low;

  for (int i=low+1; i<=high; i++) {
    if (cards[mindex].isGreater (cards[i])) {
      mindex = i;
    }
  }
  return mindex;
}

void Deck::sort ()
{
  for (int i=0; i<cards.length(); i++) {
    int j = findLowestCard (i, 51);
    swapCards (i, j);
  }
}

Deck Deck::subdeck (int low, int high) const {
  Deck sub (high-low+1);
	
  for (int i = 0; i<sub.cards.length(); i++) {
    sub.cards[i] = cards[low+i];
  }
  return sub;
}

void main ()
{
  Card card;
  Deck deck;

  //deck.shuffle ();
  //deck.print ();

  Deck hand = deck.subdeck (0, 4);
  hand.print ();

  card = deck.cards[13];
  cout << find (card, deck) << endl;
  cout << deck.find (card) << endl;
  cout << card.find (deck) << endl;
}
