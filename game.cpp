#include "game.h"
		
crazy8s::crazy8s(int num, int numPlayers):the_deck(true){
    num_players = num;
    String temp_name;
    Card * temp_card;
    //Get the players
    players = new Player * [num];
    for(int i = 0; i < numPlayers; ++i){
        players[i] = new Player;
        cout << "Please enter the player's name: ";
        cin >> temp_name;
        cin.ignore(100, '\n');
        players[i]->set_name(temp_name);
    }

    //Initialize the NPCS
    String player_temp = "NPC Player ";
 
    for(int i = numPlayers; i < num; ++i){
        players[i] = new NPC;
        player_temp += 'I';
        players[i]->set_name(player_temp);
    }
    //Shuffle the deck and deal 7 cards to each player
    the_deck.shuffle();
    for(int i = 0; i < 7; ++i){
        for(int j = 0; j < num; ++j){
            temp_card = the_deck.draw();
            if(temp_card){
                players[j] -> draw(*temp_card);
                delete temp_card;
                temp_card = NULL;
            }
        }
    }
    temp_card = the_deck.draw();
    discard.add(*temp_card);
    delete temp_card;
    temp_card = NULL;
}


crazy8s::~crazy8s(){
    if(players){
        for(int i = 0; i < num_players; ++i){
            if(players[i])
                delete players[i];
        }
        delete [] players;
    }
}

void crazy8s::play(){
    greeting();
    int winner = -1;
    while(winner == -1){
        for(int i = 0; i < num_players && winner == -1; ++i){
            cout << "\n\n";
            if(turn(players[i]))
                winner = i;
        }
    }
    players[winner]-> display_name();
    cout << " has won!!! Congratulations, ";
    players[winner] -> display_name();
    cout << "!\n\n";
}

//Returns true if the player won
bool crazy8s::turn(Player * & player){
    //Tell the player it is their turn.
    bool ret = false;
    cout << "It is ";
    player -> display_name();
    cout << "'s turn." << endl;
    Card * top = discard.peek();
    Card * played = player->play(*top);
    if(played){//The player plays a card
        discard.add(*played);
        if(player->has_won()){
            ret = true;
        }
        player -> display_name();
        cout << " played ";
        played -> display();
        cout << endl;
    }
    else{//They have to draw
        player -> display_name();
        cout << " Draws. \n";
        played = the_deck.draw();
        if(!played){
            if(top)
                delete top;
            top = discard.draw();
            the_deck = discard;
            the_deck.shuffle();
            discard.removeAll();
            discard.add(*top);
           played = the_deck.draw();
        }
        player -> draw(*played);
    }
    if(top) delete top;
    if(played) delete played;
    return ret;
}

void crazy8s::greeting(){
    cout << "Welcome to Crazy 8s! The rules of play are as follows:" << endl;
    cout << "The top card of the discard pile will be displayed, " << endl
         << "as well as your hand. Choose a card from your hand that\n"
         << "matches either the suit or the value of the top card.\n"
         << "For any given turn, you may also play an 8, which is wild.\n"
         << "This allows you to change the suit that is in play.\n"
         << "\n\tHave fun and good luck! :D" << endl;
}


