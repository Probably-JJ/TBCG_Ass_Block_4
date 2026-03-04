#include "DeckManager.h"

DeckManager::DeckManager() : m_storedDeck(new LinkedList<ICard*>), m_gameDeck(new LinkedList<ICard*>), m_hand{nullptr, nullptr, nullptr, nullptr}
{

}

DeckManager::~DeckManager()
{
	//delete lists
	//delete hand
}

void DeckManager::BuildDeck()
{
	//call add card for the cards
}

void DeckManager::AddCard(CardInfo* card)
{
	//for card weight
	//add nodes of said card to both lists
}

void DeckManager::DrawHand()
{
	//hide current cards if hand isnt empty
	//empty hand
	//random select 4 card nodes from current deck
}

void DeckManager::DisplayHand()
{
	//for each card in hand
	//set collide to true
	//set display to true
	//position correctly

}

void DeckManager::RemoveCard()
{
	//check all of hand cards for if played == true
	//call remove on the node that matches that card
}
