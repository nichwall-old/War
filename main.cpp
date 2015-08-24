// C++ version to be a bit faster

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int cardsForTieBreak = 3;
std::vector<int> player1;
std::vector<int> player2;

std::vector<int> shuffleDeck(std::vector<int> cards, int suitCount) {
	std::vector<int> deck;
	// Assign cards to deck
	for (int i=0; i<suitCount; i++) {
		for (unsigned int j=0; j<cards.size(); j++) {
			deck.push_back(cards.at(j));
		}
	}
	
	// Shuffle the cards
	for (int i=0; i<1000000; i++) {
		// Random number 1
		// Random number 2
		int first = rand()%52;
		int second = rand()%52;
		
		int temp = deck.at(first);
		deck.at(first) = deck.at(second);
		deck.at(second) = temp;
	}
	
	return deck;
}
std::vector<int> shuffleDeck(std::vector<int> cards) {
	return shuffleDeck(cards, 4);
}

int dealCards(std::vector<int> deck) {
	if ( deck.size() % 2 != 0 ) {
		return -1;
	}
	for (unsigned int i=0; i<deck.size(); i++) {
		if ( i%2 == 0 ) {
			player1.push_back(deck.at(i));
		} else {
			player2.push_back(deck.at(i));
		}
	}
	return 0;
}

int playerHasWon() {
	if ( player1.size() == 0) {
		return 2;
	} else if (player2.size() == 0) {
		return 1;
	} else {
		return 0;
	}
}

int checkWinner(unsigned int cardIndexToCheck) {
	// Check that we aren't checking outside of the deck.
	// If it's outside of only one deck, the other player wins
	// Otherwise, both take their opponents first card
	if ( (cardIndexToCheck >= player1.size()) && (cardIndexToCheck < player2.size()) ) {
		return 2;
	} else if ( (cardIndexToCheck < player1.size()) && (cardIndexToCheck >= player2.size()) ) {
		return 1;
	} else if ( (cardIndexToCheck >= player1.size()) && (cardIndexToCheck >= player2.size()) ) {
		return -1;
	}
	int p1 = player1.at(cardIndexToCheck);
	int p2 = player2.at(cardIndexToCheck);
	
	// Check if they're equal
	if ( p1 == p2 ) {
		return 0;
	}
	// Check if Ace / 2 combination
	if ( (p1 == 2) && (p2 == 14) ) {
		p2 = 1;
	} else if ( (p2 == 2) && (p1 == 2) ) {
		p1 = 1;
	}
	
	if ( p1 > p2 ) {
		return 1;
	} else {
		return 2;
	}
}

std::string displayGraph() {
	std::string outStr = "";
	for (unsigned int i=0; i<player1.size(); i++) {
		outStr += "#";
	}
	for (unsigned int i=0; i<player2.size(); i++) {
		outStr += ".";
	}
	return outStr;
}

int main() {
	// Open file to write to
	std::ofstream logger;
	logger.open("log.txt");
	
	// Initialize randomness
	srand( time(NULL));
	
	// Create decks
	std::vector<int> baseCards = {2,3,4,5,6,7,8,9,10,11,12,13,14};
	std::vector<int> deck = shuffleDeck(baseCards);
	
	// Deal cards
	int dealSuccess = dealCards(deck);
	printf("Cards dealt\n");
	
	unsigned int iterationCount = 0;
	
	// Check that we have an even number of cards
	if ( dealSuccess == 0 ) {
		while (playerHasWon() == 0) {
			iterationCount++;
			// Check who wins the top card
			int winner = checkWinner(0);
			int cardsWon = 1;
			// Break ties!
			while ( winner < 1 ) {
				cardsWon += 3;
				winner = checkWinner(cardsWon-1);
				if (winner == -1) {
					cardsWon = 1;
				}
			}
			for (int i=0; i<cardsWon; i++) {
				switch (winner) {
					case -1:
						if (player1.size() != 0) {
							player2.push_back(player1.at(0));
							// Remove player 1 card
							player1.erase(player1.begin(), player1.begin()+1);
						}
					case 1:
						if (player2.size() != 0) {
							player1.push_back(player2.at(0));
							// Remove player 2 card
							player2.erase(player2.begin(), player2.begin()+1);
						}
						break;
					case 2:
						if (player1.size() != 0) {
							player2.push_back(player1.at(0));
							// Remove player 1 card
							player1.erase(player1.begin(), player1.begin()+1);
						}
					default:
						break;
				}
			}
			printf("%d\t",iterationCount);
			std::cout << displayGraph() << "\n";
			logger << displayGraph() << "\n";
		}
		printf("Player %d has won!\n",playerHasWon());
		printf("Took %d iterations to win\n",iterationCount);
	} else {
		printf("oopsie, error probably\n");
	}
	
	logger.close();
	return 0;
}
