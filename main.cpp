#include "game.h"

int main(){
    int numPlayers, numPeople;
    cout << "Lets play a game! Please enter the number of players: ";
    cin >> numPlayers;
    cin.ignore();
    cout << "\nExcellent! Now please enter how many human players you have: ";
    cin >> numPeople;
    cin.ignore();
    crazy8s new_game(numPlayers, numPeople);
    new_game.play();
//	Player a_player;
//	Deck the_deck;
//	Card * a_card;
//	the_deck.shuffle();
//	for(int i = 0; i < 7; ++i){
//		a_card = the_deck.draw();
//		if(!a_card) cout <<"fuuuuck";
//		a_player.draw(*a_card);
//		delete a_card;
//		a_card = NULL;
//	}
//	a_card = the_deck.draw();
//	if(!a_card) cout <<"fuuuuck";
//	a_card = a_player.play(*a_card);
//	if(a_card){
//		cout << "The card the player played is " <<endl;
//		a_card -> display();
//		cout << endl;
//	}
	return 0;
}
