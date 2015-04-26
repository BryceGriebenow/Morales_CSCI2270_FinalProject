//Deck.cpp
//Contributors: Ben Roberts, Cory Morales, Bryce Griebenow

#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <random>
#include <cstdlib>
#include <ctime>
//#include <chrono>
#include "Deck.h"


using namespace std;

int Player::sumHand()
{
	sum = 0;
	hasAce=false;
	for(int i=0; i<5;i++)
	{
		if(hand[i] != NULL)
		{
			if(hand[i]->number > 1 && hand[i]->number <11)
			{
				sum += hand[i]->number;
			}
			else if(hand[i]->number == 1 && !hasAce)
			{
			    hasAce=true;
				if(sum > 10)
				{
					sum += 1;
				}
				else if(sum == 10)
				{
					sum = 21;
				}
				else
				{
                    sum += 11;//There will be bugs with this. If they bust, the ace should change to mean 1.
				}
			}
			else if(hand[i]->number == 1 && hasAce)
			{
			    sum+=1;
			}
			else if(hand[i]->number >10)
			{
				sum += 10;
			}
		}
	}
	if(sum>21&&hasAce)
        sum-=10;
	return sum;
}

Deck::Deck(int numPlayers)
{
	//players[numPlayers];
	for(int i=0;i<numPlayers;i++)
	{
		players[i].sum =0;
		for(int j=0; j<5; j++)
		{
			players[i].hand[j] = NULL;
		}
	}
	topCard =0;
	for(int i=0;i<4;i++)
	{
		for(int j=1;j<14;j++)
		{
			Card *c = new Card;
			c->number = j;
			c->suit = i;
			//decklist[13*i+j-1].number = j;
			//decklist[13*i+j-1].suit = i;
			decklist.push_back(c);
			//decklist[13*i+j-1].shuffled = false;
		}
	}
}

void Deck::shuffleDeck()
{
	//Probably horribly inefficient method:
	/*vector<Card> shuffledDeck;
	for(int i=0;i<52;i++)
	{
		int cardIndex = rand()%52;
		while(unshuffledDeck[cardIndex].shuffled = true)
		{
			cardIndex = rand()%52;
		}
		shuffledDeck[i]=unshuffledDeck[cardIndex];
	}*/

	/*
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();//found this method at http://www.cplusplus.com/reference/algorithm/shuffle/
	shuffle(decklist.begin(),decklist.end(),std::default_random_engine(seed));
	*///Something is wrong with this method, so I'll try another one that uses vectors instead of arrays.

	srand(unsigned(time(0)));
	random_shuffle(decklist.begin(), decklist.end());
}

void Deck::DealCards(int numPlayers)
{
	for(int i=0; i<numPlayers;i++)
	{
		if(topCard == 52)
		{
			cout << "Unable to deal. Ran out of cards.";
		}
		else
		{
			players[i].hand[0] = decklist[topCard];
			topCard++;
			players[i].hand[1] = decklist[topCard];
			topCard++;
			players[i].sum=players[i].sumHand();
			for (int j=2; j<5;j++)
			{
				players[i].hand[j] = NULL;
			}

		}
	}
}

/*void PrintHand(Player p)
{

}*/
bool Deck::hit(int playerInt)
{
	Player *p = new Player;
	p = &players[playerInt];
	int i = 2;
	while(p->hand[i]!= NULL)
	{
		i++;
	}
	p->hand[i] = decklist[topCard];
	topCard++;
	if(p->sumHand() < 21)
	{
		return true;
	}
	else if(p->sumHand() == 21)
	{
		//win(p);
		cout<<"YOU WIN"<<endl;
		return false;
	}
	else
	{
	    cout<<"you drew a "<<p->hand[i]->number<<" of "<<p->hand[i]->suit<<" and busted"<<endl;
		//bust(p);
		return false;
	}
}

void Deck::peek(){}
void Deck::declare(){}
void Deck::dealer(){}
Deck::~Deck(){}


