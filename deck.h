#include "card.h"


#ifndef DECK
#define DECK

const int MAX = 5;

struct node{
	Card * cards;
	node * next;
};

class Deck{
	public:
		Deck(bool init = false);
		Deck(const Deck &);
        Deck & operator=(const Deck &);
		~Deck();

		Card * draw();
		bool add(const Card&);
		Card * peek();
		bool shuffle();
		void display();
		bool remove(const Card);
		void removeAll();

        Card * npcPlay(const Card & top);
        char maxSuit();

	private:
		node * head;
		int top;
		int num_cards;
		bool copy(node * & head, node * source);

};

/*
class Hand: public Deck{
	public:
		
};
*/

#endif //DECK
