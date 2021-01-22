#include<vector>
#include"Card.h"
#ifndef Player_h
#define Player_h

#pragma once
class Player
{
public:
	Player();
	Player(Card _tempCardOne, Card _tempCardTwo);

	void recieveDealtCard(Card tempCard);
	void discardHand();
	void evaluateHandScore();
	void printHand(); // test function. 
	void sortHand();

	bool checkPair();
	bool checkTwoPair();
	bool checkThreeOfAKind();
	bool checkFourOfAKind();
	bool checkFullHouse();
	bool checkStraight();
	bool checkFlush();
	bool checkStraightFlush();


	int getHandScore();
	int getHighCardValue();
	int getPairValue();
	int getTwoPairValue();
	int getThreeKindValue();
	int getFourKindValue();
	int getFullHouseOver();
	int getFullHouseUnder();
	int getStraightHighValue();
	int getFlushHighValue();
	int getKickerValue();
	bool getHasFlush();



private:
	int kickerValue; // used for evaulation of equivalent hands. such as two pair which are both aces and tens. The kicker is the highest card not in the two pair. This can come from either the table or the hand.
	int pairValue; // also used for the low pair value for a two pair hand.
	int twoPairValue; // high pair value for a two pair hand.
	int threeKindValue;
	int fourKindValue;
	int fullHouseOver; // the pair of cards for a full house.
	int fullHouseUnder; // the 3 of a kind cards for a full house.
	int flushHighValue; // highest card in the flush.
	int straightHighValue; // highest card in the straight.
	int numOfCardsArr[13]; //used for hand evaluation. position 0 is number of Twos in the hand and on the table. 1 is Three's...... 12 is Aces.
	int handScore;   //used for hand evaluation. 0 is high card, 1 is a pair, .....
	int highCardValue; //used for hand evaluation. players with the same handscore will use this to detemine the winner. whoever was dealt the higher value card wins.
	bool hasFlush; //used for hand evaluation. if this is true, if this value is true, sets the hand score value. 

	vector<Card> playerHand;

};

#endif Player_h