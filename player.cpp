#include "player.h"

Player::Player(){
}

Card * Player::play(Card top){
	Card to_play;
	cout << "Here is your hand: " << endl;
	hand.display();
	cout << "\nThe top card is a ";
	top.display();
	cout << endl << endl;

	bool got_card = false;
	while(!got_card){
		if(!to_play.read()){
			return NULL;
		}
		if(!to_play.is8() && !to_play.compareSuit(top) && !to_play.compareVal(top))
			cout << "You cannot play that card." <<endl;
		else if(!hand.remove(to_play))
			cout << "That card is not in your hand!" << endl;
		else
			got_card = true;
	}
	if(to_play.is8()){
		char suit;
		cout << "What suit would you like to call? (H/D/C/S) ";
		cin >>suit;
        suit = toupper(suit);
		return new Card(suit, 8);
	}
	return new Card(to_play);
}

void Player::draw(Card & to_add){
	hand.add(to_add);	
}

void Player::display_name(){
	cout << name;
}

void Player::set_name(String new_name){
	name = new_name;
}
	
bool Player::has_won(){
    Card * temp = hand.peek();
    if(!temp)
        return true;
    delete temp;
    return false;
}

Card * NPC::play(Card top){
    Card * to_play = hand.npcPlay(top);
    if(to_play && to_play -> is8()){
       return new Card(hand.maxSuit(), 8);
    }
    return to_play;
}


