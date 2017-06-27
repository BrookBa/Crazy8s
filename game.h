#include "player.h"
#ifndef GAME
#define GAME

class crazy8s{
	public:
		crazy8s(int num=2, int players=1);
		~crazy8s();

		void play();

	private:
		Deck the_deck;
		Player ** players;
		Deck discard;
		int num_players;

		bool turn(Player *&);
		void greeting();

};



#endif //GAME
