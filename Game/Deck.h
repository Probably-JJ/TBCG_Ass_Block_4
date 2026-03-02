#pragma once
#include <string>

//just to remove errors, entire structure changed.
class Card {};

class Deck
{
private:

	//The Deck itself is just a linked list
	//each instance of the card is a node in the list
	struct Node
	{
		Card data;
		Node* next;

		Node(Card d) : data(d), next(nullptr) {}
	};
	
	Node* head;
	Node* tail;
	int deckSize;



public:
	//Deck needs to have at least one card in it to function
	Deck(Card initCard);
	~Deck();

	//pass in a copy of a card
	//it is added to the deck acording to its weight
	void AddCard(Card card);

	bool Remove(Card card);

	struct Iterator
	{
		Iterator(Node* node) : currentNode(node){}

		//Move To Next Node
		Iterator operator++();

		//Access Data in current node
		Card operator*();

		//Allows for iterators to be compaired to each other
		bool operator!=(const Iterator& other);
		bool operator==(const Iterator& other);

	private:
		Node* currentNode;
	};

	//returns an Iterator storing the Head
	Iterator Begin();

	//returns an Iterator storing Nullptr
	Iterator End();
};

