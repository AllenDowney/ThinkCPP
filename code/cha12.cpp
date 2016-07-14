#include <iostream.h>
#include <stdlib.h>
#include "apstring.h"
#include "apvector.h"

enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };

enum Rank { ACE=1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
TEN, JACK, QUEEN, KING };

struct Card
{
  Rank rank;
  Suit suit;

  Card ();
  Card (Suit s, Rank r);

  void print () const;
  bool isGreater (const Card& c2) const;
};

Card::Card () { 
  suit = CLUBS;  rank = TWO;
}

Card::Card (Suit s, Rank r) { 
  suit = s;  rank = r;
}

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
  for (Suit suit = CLUBS; suit <= SPADES; suit = Suit(suit+1)) {
    for (Rank rank = ACE; rank <= KING; rank = Rank(rank+1)) {
      deck[index].suit = suit;
      deck[index].rank = rank;
      index++;
    }
  }
  return deck;
}

void printDeck (const apvector<Card>& deck) {
  for (int i = 0; i < deck.length(); i++) {
    deck[i].print ();
  }
}

int find (const Card& card, const apvector<Card>& deck) {
  for (int i = 0; i < deck.length(); i++) {
    if (equals (deck[i], card)) return i;
  }
  return -1;
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

void main ()
{
  Card card (DIAMONDS, JACK);
  apvector<Card> deck = buildDeck ();

  int index = findBisect (card, deck, 0, deck.length()-1);
  cout << "I found the card at index = " << index << endl;
  cout << "The card we were looking for is the ";
  card.print();
  cout << "The card we we found is the ";
  deck[index].print();

  char symbol = '+';

  switch (suit) {
  case CLUBS:  return "Clubs";
  case DIAMONDS:  return "Diamonds";
  case HEARTS:  return "Hearts";
  case SPADES:  return "Spades";
  default:  return "Not a valid suit";
  }

}
