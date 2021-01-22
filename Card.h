#pragma once
#ifndef Card_h
#define Card_h

#include<string>
#include<iostream>

//completely modular class. usable for any card game. 

using namespace std;

class Card
{

private:
	int cardValue;		// assigned numerical value - jack, queen, and king are worth 10, aces are worth 11 or 1 if 11 casuses the player to exceed a combined card value of 21.
	string cardName;	// ace , king, queen, jack, ten, nine....two. 
	string cardSuit;    // spades, clubs, diamonds, hearts

public:
	Card();
	Card(int value, string name, string suit);

	void printCard();
	int getCardValue();
	string getCardName();
	string getCardSuit();

	bool friend operator==(Card cardOne, Card cardTwo);
	bool friend operator!=(Card cardOne, Card cardTwo);
	bool friend operator<(Card cardOne, Card cardTwo);
	bool friend operator>(Card cardOne, Card cardTwo);
};

#endif Card_h