#ifndef CARD
#define CARD

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "../StringClass/String.h"
using namespace std;
	

class Card{
	public:
		Card();
		Card(const Card &);
		Card(char suit, int val);
		~Card();

        Card & operator=(const Card &);


		void display();
		bool copy(const Card);
		bool compareSuit(const Card);
		int compareVal(const Card);
		bool compare(const Card);//Compares the two cards to see if they are the same
		bool read();//Reads a card from the user

        //Checks if the card is an 8
		bool is8();

        //Checks if it matches value or suit of the card
        bool isPlayable(const Card);
        
        //Getters
        char Suit();
        int Val();

	private:
		char suit;
		int val;

		String getSuit();
		String getValue();
};
		

#endif //CARD
