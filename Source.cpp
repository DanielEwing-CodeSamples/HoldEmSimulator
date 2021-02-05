#include "Deck.h"
#include "Player.h"
#include<iostream>
#include<chrono>

using namespace std;

int main() {
	auto start = std::chrono::high_resolution_clock::now();
	double scoreCounter = 0;
	double tieCounter = 0;
	Deck deckOfCards;
	Player player1, player2;
	const Card pOneCardOne(13, "King", "Hearts");
	const Card pOneCardTwo(13, "King", "Diamonds");
	Card tempCard;
	void evaluatePlayerHand(Player & tempPlayer);
	int compareSimilarHands(Player playerX, Player playerY); // 0 = playerX loses, 1 = playerX ties, 2 = playerX wins.

	for (int i = 0; i < 10000; i++) {
		deckOfCards.shuffleDeck();
		player1.discardHand();
		player2.discardHand();
		player1.recieveDealtCard(pOneCardOne);
		player1.recieveDealtCard(pOneCardTwo);


		for (int i = 0; i < 2; i++) {
			tempCard = deckOfCards.dealCard();
			while (tempCard == pOneCardOne || tempCard == pOneCardTwo) {
				tempCard = deckOfCards.dealCard();
			}
			player2.recieveDealtCard(tempCard);
		}


		for (int j = 0; j < 5; j++) {
			tempCard = deckOfCards.dealCard();
			while (tempCard == pOneCardOne || tempCard == pOneCardTwo) { // dont double deal
				tempCard = deckOfCards.dealCard();
			}
			player1.recieveDealtCard(tempCard);
			player2.recieveDealtCard(tempCard);

		}
		evaluatePlayerHand(player1);
		evaluatePlayerHand(player2);

		cout << player1.getHandScore() << " " << player2.getHandScore() << " \n";

		if (player1.getHandScore() < player2.getHandScore()) {
			cout << "Outright lost Hand: " << i + 1 << " to another players hand score.\n";
		}
		else if (player1.getHandScore() > player2.getHandScore()) {
			scoreCounter++;
			cout << "Outright won hand: " << i + 1 << "\n";
		}
		else { // one or more players hold hands with equivalent values as player1. check for high cards amongst these players
			if (compareSimilarHands(player1, player2) == 0) {
				cout << "lost tie in hand: " << i + 1 << " to player 2.\n";
			}
			else if (compareSimilarHands(player1, player2) == 1) {   //NEED CHANGES HERE WHEN EVALUATION FUNCTIONS ARE COMPLETED. KICKERS WILL ALREADY EVALUATE THIS AND DETERMINE THE HAND WAS TIED. SEE CHECKPAIR()
				cout << "tied hand: " << i + 1 << ".\n";
				tieCounter++;
			}
			else {
				scoreCounter++;
				cout << "Won A Tie in hand: " << i + 1 << "\n";
			}
		}
	}

	cout << scoreCounter << " games won out of 10000 games.\n";
	cout << tieCounter << " games tied out of 10000 games.\n";
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsedTime = finish - start;
	std::cout << "Run Time per hand played: " << elapsedTime.count()/10 << " milliseconds.\n";
	system("pause");
	return 0;
}

void evaluatePlayerHand(Player& tempPlayer) { //eliminates unnessecary searches. 
	if (tempPlayer.checkPair() == true) {
		if (tempPlayer.checkTwoPair() == true) {
			if (tempPlayer.checkThreeOfAKind() == true) {
				tempPlayer.checkFullHouse();
			}
		}
		else if (tempPlayer.checkThreeOfAKind() == true) {
			tempPlayer.checkFourOfAKind();
		}
	}
	tempPlayer.checkFlush();
	tempPlayer.checkStraight();
	if (tempPlayer.checkFlush() != false && tempPlayer.checkStraight() != false) {
		tempPlayer.checkStraightFlush();
	}
}
int compareSimilarHands(Player playerX, Player playerY) { // 0 = playerX loses, 1 = playerX ties, 2 = playerX wins.	
	if (playerX.getHandScore() == 0) { // high card
		if (playerX.getHighCardValue() > playerY.getHighCardValue())
			return 2;
		else if (playerX.getHighCardValue() == playerY.getHighCardValue())
			return 1;
		else return 0;
	}
	else if (playerX.getHandScore() == 1) { // pair
		if (playerX.getPairValue() > playerY.getPairValue())
			return 2;
		else if (playerX.getPairValue() == playerY.getPairValue()) {
			if (playerX.getKickerValue() > playerY.getKickerValue())
				return 2;
			else if (playerX.getKickerValue() == playerY.getKickerValue())
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else if (playerX.getHandScore() == 2) { // two pair
		if (playerX.getTwoPairValue() > playerY.getTwoPairValue()) {
			return 2;
		}
		else if (playerX.getTwoPairValue() == playerY.getTwoPairValue()) { // high value pair ties.
			if (playerX.getPairValue() > playerY.getPairValue()) { // low value pair wins tie for playerX
				return 2;
			}
			else if (playerX.getPairValue() < playerY.getPairValue()) { // low value pair loses tie for playerX
				return 0;
			}
			else { // kickers determine winner
				if (playerX.getKickerValue() > playerY.getKickerValue()) { // kicker wins for playerX
					return 2;
				}
				else if (playerX.getKickerValue() < playerY.getKickerValue()) { // kicker loses for playerX
					return 0;
				}
				else //players tie.
					return 1;
			}
		}
		else { // playerX loses hand to high pair value.
			return 0;
		}
	}
	else if (playerX.getHandScore() == 3) { // three of a kind
		if (playerX.getThreeKindValue() > playerY.getThreeKindValue()) {
			return 2;
		}
		else if (playerX.getThreeKindValue() == playerY.getThreeKindValue()) { // evaluate kickers
			if (playerX.getKickerValue() > playerY.getKickerValue()) {
				return 2;
			}
			else if (playerX.getKickerValue() == playerY.getKickerValue()) {
				return 1;
			}
			else
				return 0;
		}
		else {
			return 0;
		}
	}
	else if (playerX.getHandScore() == 4) { //straight, no kicker exists, the straight with the highest card wins.
		if (playerX.getStraightHighValue() > playerY.getStraightHighValue()) {
			return 2;
		}
		else if (playerX.getStraightHighValue() == playerY.getStraightHighValue()) {
			return 1;
		}
		else return 0;

	}
	else if (playerX.getHandScore() == 5) { // flush, no kicker exists, rank hands based off of highest card in the flush, if thats a tie then compare the next highest card until one player beats another. 
		if (playerX.getFlushHighValue() > playerY.getFlushHighValue()) {
			return 2;
		}
		else if (playerX.getFlushHighValue() == playerY.getFlushHighValue()) {
			return 1;
		}
		else return 0;
	}
	else if (playerX.getHandScore() == 6) { //full house, no kicker used to evalute two different full houses. compare 3 of a kind and if those are == then compare the pair. if both are == then its a draw.
		if (playerX.getFullHouseUnder() > playerY.getFullHouseUnder()) { // best 3 of a kind wins.
			return 2;
		}
		else if (playerX.getFullHouseUnder() == playerY.getFullHouseUnder()) { // 3 of a kind is a tie, best pair wins.
			if (playerX.getFullHouseOver() > playerY.getFullHouseOver()) {
				return 2;
			}
			else if (playerX.getFullHouseOver() == playerY.getFullHouseOver()) { // pairs tie, players tie this hand.
				return 1;
			}
			else return 0;
		}
		else
			return 0;
	}
	else if (playerX.getHandScore() == 7) { // 4 kind, no kickers since two players cant have the same 4 of a kind. 
		if (playerX.getFourKindValue() > playerY.getFourKindValue()) {
			return 2;
		}
		else if (playerX.getFourKindValue() > playerY.getFourKindValue()) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (playerX.getHandScore() == 8) {

	}
	else if (playerX.getHandScore() == 9) { // royal flush
	}

	return 0;
}