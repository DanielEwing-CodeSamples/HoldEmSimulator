#include "Card.h"
//overloaded operators at the bottom

Card::Card() {
	cardName = "test";
	cardSuit = "test";
	cardValue = 0;
}

Card::Card(int value, string name, string suit) {
	cardValue = value;
	cardName = name;
	cardSuit = suit;
}

string Card::getCardName() {
	return cardName;
}

string Card::getCardSuit() {
	return cardSuit;
}

int Card::getCardValue() {
	return cardValue;
}

void Card::printCard() {
	if(cardValue!= 14)
		cout << "The " << cardName << " of " << cardSuit << ". It's Card Value is " << cardValue << ".\n";
	else
		cout << "The " << cardName << " of " << cardSuit << ". It's Card Value is " << cardValue << ", or 1 if this would give a player a 5 high straight( Ace, 2, 3, 4, 5.)\n";
}

bool operator==(Card cardOne, Card cardTwo) {
		if (cardOne.getCardName() == cardTwo.getCardName() && cardOne.getCardSuit() == cardTwo.getCardSuit()) {
			return true;
		}
		else return false;
}
bool operator!=(Card cardOne, Card cardTwo) {
	if (cardOne.getCardName() != cardTwo.getCardName() || cardOne.getCardSuit() != cardTwo.getCardSuit()) {
		return true;
	}
	else return false;
}