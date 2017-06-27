#include "deck.h"

Deck::Deck(bool init)
{	
	head = NULL;
	top = 0;
	num_cards = 0;
	if(init){
		char suit = 'H';
		for(int i = 1; i < 14; ++i){
			add(Card(suit, i));
		}
		suit = 'D';
		for(int i = 1; i < 14; ++i){
			add(Card(suit, i));
		}
		suit = 'C';
		for(int i = 1; i < 14; ++i){
			add(Card(suit, i));
		}
		suit = 'S';
		for(int i = 1; i < 14; ++i){
			add(Card(suit, i));
		}
	}
	srand(time(0));
}


Deck::Deck(const Deck & source)
{
	num_cards = source.num_cards;
	top = source.top;
	copy(head, source.head);

}

Deck & Deck::operator=(const Deck & source){
    if(this == &source)
        return *this;
    num_cards = source.num_cards;
	top = source.top;
	//If head, delete the cards in this deck
	removeAll();
	copy(head, source.head);
}

bool Deck::copy(node * & head, node * source){
	if(!source){
		head = NULL;
		return false;
	}
	head = new node;
	head -> cards = new Card[MAX];
	for(int i = 0; i < MAX; ++i){
		head -> cards[i].copy(source -> cards[i]);
	}
	return copy(head -> next, source -> next) && true;
}

Deck::~Deck()
{
	removeAll();
}

//Pop function
Card * Deck::draw()
{
	if(!head){
		return NULL;
	}
	--top;
	--num_cards;
	Card * ret = new Card(head -> cards[top]);
	if(top == 0){
		node * temp = head;
		head = head -> next;
		delete [] temp -> cards;
		delete temp;
		top = MAX;
	}
	return ret;
}

//Push function
bool Deck::add(const Card& to_add)
{
	if(!head || top == MAX) {
		node * temp = head;
		head = new node;
		head -> cards = new Card[MAX];
		head -> next = temp;
		top = 0;
	}
	head -> cards[top].copy(to_add);
	++top;
	++num_cards;
	return true;
}

Card * Deck::peek()
{
	if(!head)return NULL;
	return new Card(head->cards[top - 1]);
}

void Deck::display(){
	if(!head){
		cout << "Nothing to display! " <<endl;
		return ;
	}
	for(int i = 0; i < top; ++i){
		head -> cards[i].display();
			cout << " \n";
	}
	node * current = head -> next;
	while(current){
		for(int i = 0; i < MAX; ++i){
			current -> cards[i].display();
			cout << " \n";
		}	
		current = current -> next;
	}
}

bool Deck::shuffle()
{	
	int size = num_cards;
	Card ** shuffle = new Card * [num_cards];	
	for(int i = 0; i < size; ++i){
		shuffle[i] = draw();
	}

	int j = 0;
	bool added = false;

	for(int i = 0; i < size; ++i){
		j = rand() % size;
		added = false;
		for(;j <= size && !added; ++j){
			j = j % size;
			if(shuffle[j]){
				add(*shuffle[j]);
				delete shuffle[j];
				shuffle[j] = NULL;
				added = true;
			}
		}
	}

	delete [] shuffle;
}


bool Deck::remove(const Card c){
	if(!head)
		return false;
	Card * replacement = peek();
	node * current = head;
	bool found = false;
	for(int i = 0; i < top && !found; ++i){
		found = current->cards[i].compare(c);
		if(found){  
            delete replacement;
            replacement = draw();
			current->cards[i].copy(*replacement);
			delete replacement;
			replacement = NULL;
		}
	}
	if(found) return found;
	while(current->next && !found){
		current = current -> next;
		for(int i = 0; i < MAX && !found; ++i){
			found = current -> cards[i].compare(c);
			if(found){
                delete replacement;
                replacement = draw();
				current->cards[i].copy(*replacement);
			}
		}
	}
	delete replacement;
	replacement = NULL;
	return found;
}


void Deck::removeAll(){
	if(head){
		node * temp;
		while(head){
			temp = head -> next;
			delete [] head -> cards;
			delete head;
			head = temp;
		}
	}
	num_cards = 0;
	top = 0;
}

Card * Deck::npcPlay(const Card & top_c){
    if(!head) return NULL;
    Card * found = NULL;
    node * cur = head -> next;
    for(int i = 0; i < top && !found; ++i){
        if(head -> cards[i].isPlayable(top_c)){
            found = new Card(head -> cards[i]);
            remove(*found);
        }
    }
    while(!found && cur){
        for(int i = 0; i < MAX && !found; ++i){
            if(cur -> cards[i].isPlayable(top_c)){
                 found = new Card(cur -> cards[i]);
                 remove(*found);
            }
        }
        cur = cur->next;
    }
    return found;
}

char Deck::maxSuit(){
    if(!head) return 'H';
    int suitCount[4];
    for(int i = 0; i < 4; ++i){
        suitCount[i] = 0;
    }
    node * cur = head;
    for(int i = 0; i < top; ++i){
        switch(cur -> cards[i].Suit()){
            case 'H':
                ++suitCount[0];
                break;
            case 'D':
                ++suitCount[1];
                break;
            case 'S':
                ++suitCount[2];
                break;
            case 'C':
                ++suitCount[4];
                break;
            default:
                cerr << "WHAT THE FUCK IS THIS SUIT EVEN??? " << cur->cards[i].Suit() << endl;
        }

    }
    cur = cur -> next;
    while(cur){
        for(int i = 0; i < MAX; ++i){
            switch(cur -> cards[i].Suit()){
                case 'H':
                    ++suitCount[0];
                    break;
                case 'D':
                    ++suitCount[1];
                    break;
                case 'S':
                    ++suitCount[2];
                    break;
                case 'C':
                    ++suitCount[4];
                    break;
                default:
                    cerr << "WHAT THE FUCK IS THIS SUIT EVEN??? " << cur->cards[i].Suit() << endl;
            }

        }
        cur = cur -> next;
    }
    int max = 0;
    for(int i = 1; i < 4; ++i){
        if(suitCount[i] > suitCount[max])
            max = i;
    }
    switch(max){
        case 0:
            return 'H';
        case 1:
            return 'D';
        case 2:
            return 'S';
        case 3:
            return 'C';
    }
}

