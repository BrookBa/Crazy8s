#include "deck.h"

#ifndef PLAYER
#define PLAYER

class Player{
	public:
		Player();

		virtual Card * play(Card top);
		void draw(Card & to_add);
		void display_name();
		void set_name(String new_name);
        bool has_won();
	protected:
		Deck hand;
		String name;
};

class NPC: public Player{
	public:
		Card * play(Card top);
};

#endif //PLAYER
