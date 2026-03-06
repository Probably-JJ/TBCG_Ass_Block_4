//#pragma once
//#include "LinkedList.h"
//
////due to time constraints i had to cut out this part of my game.
////the idea was that this class could handle all the logic of both building the deck and playing the cards
//
//
//class CardInfo;
//class ICard;
//class DeckManager
//{
//public:
//	DeckManager();
//	~DeckManager();
//
//
//	//populates the deck with the Initial Cards
//	void BuildDeck();
//
//	void AddCard(CardInfo* card);
//	
//	//Randomly Draw 4 cards from the current deck
//	void DrawHand();
//
//	//place all the drawn cards on screen
//	void DisplayHand();
//
//	void RemoveCard();
//
//	//Returns the deck storing all the cards available in the deck when full
//	//This deck never has cards removed from it.
//	LinkedList<ICard*> GetTrueDeck();
//
//	//returns the deck that is being used by the player
//	//this deck is what the player draws from, cards are removed from this deck
//	LinkedList<ICard*> GetCurrentDeck();
//
//
//private:
//	LinkedList<ICard*>* m_storedDeck;
//
//	LinkedList<ICard*>* m_gameDeck;
//
//	ICard* m_hand[4];
//};
//
