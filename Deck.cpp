#include "Deck.h"
#include<time.h>
#include<iostream> 

//Completely Modular Class. Usable for any card game.


Deck::Deck() {
	for (int i = 0; i < 4; i++) {
		string tempSuit;
		if (i == 0) {
			tempSuit = "Spades";
		}
		else if (i == 1) {
			tempSuit = "Diamonds";
		}
		else if (i == 2) {
			tempSuit = "Clubs";
		}
		else if (i == 3) {
			tempSuit = "Hearts";
		}
		deckOfCards.push_back(Card(2, "Two", tempSuit));
		deckOfCards.push_back(Card(3, "Three", tempSuit));
		deckOfCards.push_back(Card(4, "Four", tempSuit));
		deckOfCards.push_back(Card(5, "Five", tempSuit));
		deckOfCards.push_back(Card(6, "Six", tempSuit));
		deckOfCards.push_back(Card(7, "Seven", tempSuit));
		deckOfCards.push_back(Card(8, "Eight", tempSuit));
		deckOfCards.push_back(Card(9, "Nine", tempSuit));
		deckOfCards.push_back(Card(10, "Ten", tempSuit));
		deckOfCards.push_back(Card(11, "Jack", tempSuit));
		deckOfCards.push_back(Card(12, "Queen", tempSuit));
		deckOfCards.push_back(Card(13, "King", tempSuit));
		deckOfCards.push_back(Card(14, "Ace", tempSuit));

	}
}

void Deck::printDeck() {
	for (vector<Card>::iterator iter = deckOfCards.begin(); iter != deckOfCards.end(); iter++) {
		iter->printCard();
	}
	cout << "\n\n\n";
}


void Deck::shuffleDeck() {
	srand(time(0));
	for (int i = 0; i < deckOfCards.size(); i++) {
		int random = rand() % (deckOfCards.size());
		swap(deckOfCards[i], deckOfCards[random]);
	}
}

Card Deck::dealCard() {								
	Card tempCard = deckOfCards.front();		
	deckOfCards.push_back(deckOfCards.front());
	deckOfCards.erase(deckOfCards.begin());
	return tempCard;
}

