#pragma once
#ifndef Deck_h
#define Deck_h

#include "Card.h"
#include<vector>

class Deck :
	private Card {

public:
	Deck();
	void printDeck(); // test function
	void shuffleDeck();
	Card dealCard(); // deals a copy of the top card to the player, places the original on the bottom of the deck.

private:
	vector<Card> deckOfCards;
};



#endif Deck_h