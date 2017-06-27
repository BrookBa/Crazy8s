#include "card.h"

Card::Card():suit('C'), val(1){}

Card::Card(const Card &c):suit(c.suit), val(c.val){}

Card::Card(char s, int v): suit(s), val(v){}
Card::~Card(){}

void Card::display(){
	String value(getValue());
	String Suit(getSuit());
	if(value.is_empty() || Suit.is_empty())
		cerr << "Error displaying card.";
	else		
		cout << value << " of " << Suit;
}


bool Card::copy(const Card c){
	suit = c.suit;
	val = c.val;
	return true;
}

bool Card::compareSuit(const Card c){
	return c.suit == suit;
}
int Card::compareVal(const Card c){
	return val == c.val;
}

bool Card::read(){	
	 char in[5];
	 cout << "Please enter the card. Enter the value as an integer, "
	 	  << "followed by the first letter of the suit. " << endl;
	 cout << "The values of face cards are as follows: " << endl
	 	  << "\tJack = J\n\tQueen = Q\n\tKing = K\n\tAce = A\n"
		  << "example, the Queen of Hearts would be QH\n";
	 cout << "If you cannot play, enter \"draw\"" << endl;
	 cin >> in;
	 if(!strcmp(in, "draw"))
	 	return false;
	 else if(strlen(in) == 2){
        suit = toupper(in[1]);
        if(isdigit(in[0])){
		    val = atoi(&in[0]);
		    return true;
        }
        in[0] = toupper(in[0]);
        switch(in[0]){  
            case 'A':
                val = 1;
                break;
            case 'J':
                val = 11;
                break;
            case 'Q':
                val = 12;
                break;
            case 'K':
                val = 13;
                break;
        }
        return true;
	 }
	 else if(strlen(in) == 3){
		suit = toupper(in[2]);
		in[2] = '\0';
		val = atoi(in);
		return true;
	 }
	 return false;
}


bool Card::compare(const Card c){
	return c.val == val && c.suit == suit;
}

String Card::getSuit(){
	switch(suit){
		case 'H':
			return String("♥️");
		case 'S':
			return String("♠️");
		case 'C':
			return String("♣️");
		case 'D':
			return String("♦️");
		default:
			return String("ERROR");
	}
}

String Card::getValue(){
	switch(val){
		case 1:
			return String("Ace");
		case 2:
			return String("2");
		case 3:
			return String("3");
		case 4:
			return String("4");
		case 5:
			return String("5");
		case 6:
			return String("6");
		case 7:
			return String("7");
		case 8:
			return String("8");
		case 9:
			return String("9");
		case 10:
			return String("10");
		case 11:
			return String("Jack");
		case 12:
			return String("Queen");
		case 13:
			return String("King");
		defualt:
			return String("ERROR");
	}
}
bool Card::is8(){
	return val == 8;
}

bool Card::isPlayable(const Card c){
    if(compareSuit(c) || compareVal(c) || is8())
        return true;
    return false;
}

char Card::Suit(){
    return suit;
}

int Card::Val(){
    return val;
}


Card & Card::operator=(const Card & c){
   if(&c == this)
       return *this;
   suit = c.suit;
   val = c.val;
   return *this;
}
