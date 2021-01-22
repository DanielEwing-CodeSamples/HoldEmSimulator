#include "Player.h"
#include<algorithm>

Player::Player() {
	for (int i = 0; i < 13; i++) {
		numOfCardsArr[i] = 0;
	}
	handScore = 0;
	highCardValue = 0;
	hasFlush = false;
	pairValue = 0; 
	twoPairValue = 0;
	threeKindValue = 0;
	fourKindValue = 0;
	fullHouseOver = 0;
	fullHouseUnder = 0;
	flushHighValue = 0;
	straightHighValue = 0;
	kickerValue = 0;
}
Player::Player(Card _tempCardOne, Card _tempCardTwo) {
	recieveDealtCard(_tempCardOne);
	recieveDealtCard(_tempCardTwo);
	for (int i = 0; i < 13; i++) {
		if (_tempCardOne.getCardValue() == i + 2) {
			numOfCardsArr[i]++;
		}
		if (_tempCardTwo.getCardValue() == i + 2) {
			numOfCardsArr[i]++;
		}
	}
	handScore = 0;
	highCardValue = 0;
	hasFlush = false;
	pairValue = 0;
	twoPairValue = 0;
	threeKindValue = 0;
	fourKindValue = 0;
	fullHouseOver = 0;
	fullHouseUnder = 0;
	flushHighValue = 0;
	straightHighValue = 0;
	kickerValue = 0;
}

int Player::getHandScore() {
	return handScore;
}
int Player::getHighCardValue() {
	return highCardValue;
}
bool Player::getHasFlush() {
	return hasFlush;
}
int Player::getPairValue() {
	return pairValue;
}
int Player::getTwoPairValue() {
	return twoPairValue;
}
int Player::getThreeKindValue() {
	return threeKindValue;
}
int Player::getFourKindValue() {
	return fourKindValue;
}
int Player::getFullHouseOver() {
	return fullHouseOver;
}
int Player::getFullHouseUnder() {
	return fullHouseUnder;
}
int Player::getStraightHighValue() {
	return straightHighValue;
}
int Player::getFlushHighValue() {
	return flushHighValue;
}
int Player::getKickerValue() {
	return kickerValue;
}


void Player::recieveDealtCard(Card tempCard) {
	if (tempCard.getCardValue() > highCardValue) 
		highCardValue = tempCard.getCardValue();
	for (int i = 0; i < 13; i++) {
		if (tempCard.getCardValue() == (i + 2)) {
			numOfCardsArr[i] ++;
		}
	}
	playerHand.push_back(tempCard);
}
void Player::printHand() {
	if (playerHand.empty() == true) {
		cout << "Your Hand is empty.\n";
		return;
	}
	for (int j = 0; j < 13; j++) {
		if (numOfCardsArr[j] != 0) {
			if (numOfCardsArr[j] == 1) {
				cout << "You have " << numOfCardsArr[j] << " card with a value of " << j + 2 << ".\n";
			}
			else {
				cout << "You have " << numOfCardsArr[j] << " cards with a value of " << j + 2 << ".\n";
			}
		}
	}
	int i = 1;
	for (vector<Card>::iterator iter = playerHand.begin(); iter != playerHand.end(); iter++) {
		cout << "Card " << i << ": ";
		iter->printCard();
		i++;
	}
	cout << "Hand score: " << handScore << ", and kicker Value: " << kickerValue << ".\n";
}
void Player::discardHand() {
	playerHand.erase(playerHand.begin(), playerHand.end());
	for (int i = 0; i < 13; i++) {
		numOfCardsArr[i] = 0;
	}
	handScore = 0;
	highCardValue = 0;
	hasFlush = false;
	pairValue = 0;
	twoPairValue = 0;
	threeKindValue = 0;
	fourKindValue = 0;
	fullHouseOver = 0;
	fullHouseUnder = 0;
	flushHighValue = 0;
	straightHighValue = 0;
	kickerValue = 0;
}

void Player::sortHand() {
	sort(playerHand.begin(), playerHand.end());		
}


bool Player::checkPair() {
	for (int i = 12; i >= 0; i--) {
		if (numOfCardsArr[i] >= 1) {
			if (numOfCardsArr[i] >= 2 && pairValue == 0) {  // this will be overridden during the check for 3 of a kind. which only comes after a successful pair check.
				pairValue = i + 2;
				handScore = 1;
				if (kickerValue != 0)
					return true;
			}
			else if (numOfCardsArr[i] >= 1 && kickerValue == 0) {
				kickerValue = i + 2;
				if (handScore == 1)
					return true;
			}				
		}
	}
	if (handScore == 1)
		return true;
	return false;
}
bool Player::checkTwoPair(){
	int numOfPairsIter = 0;
	for (int i = 12; i >= 0; i--) {
		if (numOfCardsArr[i] >= 2) {
			if (numOfPairsIter == 0) { // first pair found, set the value for the highest value pair.
				twoPairValue = i + 2;
				numOfPairsIter++;
			}
			else if (numOfPairsIter == 1) { // second pair found, set value for the lower value pair
				pairValue = i + 2;
				numOfPairsIter++;
			}
		}
	}
	if (numOfPairsIter == 2) { // two pairs exist
		for (int i = 12; i >= 0; i--) {
			if (numOfCardsArr[i] > 0 && i + 2 != twoPairValue && i + 2 != pairValue) { // conditions met for kicker, set value and return true;
				kickerValue = i + 2;
				handScore = 2;
				return true;  
			}
		}
	}
	else
		return false;
}
bool Player::checkThreeOfAKind() {
	for (int i = 12; i >= 0; i--) {
		if (numOfCardsArr[i] >= 3) {
			if (threeKindValue == 0) {
				handScore = 3;
				threeKindValue = i + 2;
			}
		}
	}
	if (threeKindValue != 0) {
		for (int i = 12; i >= 0; i--) {
			if (numOfCardsArr[i] > 0 && i + 2 != threeKindValue && threeKindValue == 0) { // all conditions for kicker value met. set the kicker. 
				kickerValue = i + 2;
			}
		}
		return true;
	}
	else
		return false;
}
bool Player::checkFullHouse() { // no kicker exists for full houses.
	if (checkThreeOfAKind() == true && checkTwoPair() == true) {
		handScore = 6;
		fullHouseUnder = threeKindValue;
		if (twoPairValue != threeKindValue) {
			fullHouseOver = twoPairValue;
			return true;
		}
		else {
			fullHouseOver = pairValue;
			return true;
		}
	}
	else {
		return false;
	}
}
bool Player::checkFourOfAKind() { // no kickers since players cant get a tie in a four of a kind.
	for (int i = 0; i < 13; i++) {
		if (numOfCardsArr[i] == 4) {
			fourKindValue = i + 2;
			handScore = 7;
			return true;
		}
	}
	return false;
} 
bool Player::checkStraight() {
	int consequtiveCardsIter = 0;
	if (numOfCardsArr[0] >= 1 && numOfCardsArr[1] >= 1 && numOfCardsArr[2] >= 1 && numOfCardsArr[3] >= 1 && numOfCardsArr[12] >= 1) {
		straightHighValue = 5;
		handScore = 4;
		return true;
	}
	for (int i = 8; i >= 0 ; i--) { // iterate backwards to find highest value straight first. 
		if (numOfCardsArr[i] >= 1 && numOfCardsArr[i+1] >= 1 && numOfCardsArr[i+2] >= 1 && numOfCardsArr[i+3] >= 1 && numOfCardsArr[i+4] >= 1) {
			straightHighValue = i + 6;
			handScore = 4;
			return true;
		}
	}
	return false;
}
bool Player::checkFlush() {
	int spadeCounter = 0, heartCounter = 0, diamondCounter = 0, clubCounter = 0;
	int spadeHighValue = 0, heartHighValue = 0, diamondHighValue = 0, clubHighValue = 0;
	for (vector<Card>::iterator iter = playerHand.begin(); iter != playerHand.end(); iter++) {
		if (iter->getCardSuit() == "Spades") {
			if (iter->getCardValue() > spadeHighValue) {
				spadeHighValue = iter->getCardValue();
			}
			spadeCounter++;
		}
		else if (iter->getCardSuit() == "Hearts") {
			if (iter->getCardValue() > heartHighValue) {
				heartHighValue = iter->getCardValue();
			}
			heartCounter++;
		}
		else if (iter->getCardSuit() == "Diamonds") {
			if (iter->getCardValue() > diamondHighValue) {
				diamondHighValue = iter->getCardValue();
			}
			diamondCounter++;
		}
		
		else if (iter->getCardSuit() == "Clubs") {
			if (iter->getCardValue() > clubHighValue) {
				clubHighValue = iter->getCardValue();
			}
			clubCounter++;
		}		
	}
	if (spadeCounter >= 5) {
		flushHighValue = spadeHighValue;
		handScore = 5;
		return true;
	}
	else if (heartCounter >= 5) {
		flushHighValue = spadeHighValue;
		handScore = 5;
		return true;
	}
	else if (diamondCounter >= 5) {
		flushHighValue = diamondHighValue;
		handScore = 5;
		return true;
	}
	else if (clubCounter >= 5) {
		flushHighValue = clubHighValue;
		handScore = 5;
		return true;
	}
	else {
		return false;
	}
}


bool Player::checkStraightFlush() {
	sortHand();
	string tempString = "";
	int tempInt = 0;
	int conseqCardsCounter = 0;
	for (vector<Card>::iterator iter = playerHand.begin(); iter != playerHand.end() - 1; iter++) {
		if (conseqCardsCounter == 4) {
			if ((iter)->getCardValue() == 14) {
				handScore = 9;
				straightHighValue = 14;
				cout << "ROYAL flush found!!!\n";
				system("pause");
				printHand();
				system("pause");
				return true;
			}
			else {
				handScore = 8;
				straightHighValue = (iter - 1)->getCardValue();
				return true;
			}
		}
		else if (iter->getCardValue() == (iter + 1)->getCardValue() - 1 && iter->getCardSuit() == (iter + 1)->getCardSuit())  {
			conseqCardsCounter++;
		}
		else conseqCardsCounter = 0;				
	}

	return false;
}