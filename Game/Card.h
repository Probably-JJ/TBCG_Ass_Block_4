#pragma once
#include "Entity.h"

class Combat;
class Player;

class Card : public Entity
{
public:
	//this could be changed later for having each card type being a child class of this card class
	//with how simple the cards are in this version of the game, however it is not required as everything will run and read well
	//anything beyond 5 different cards would push the requirement for that structure more
	enum CARDTYPE
	{
		ATTACK,
		HEAL
	};


	Card(CARDTYPE type, int cardWeight, int cardStrength, Player* player, int X, int Y, const Object& mouse, const char* imagePath, int size);

	void Initilise();

	//t = target
	//Executes card functionality
	void CardFunction(Combat* t);

	int GetCardWeight();


private:
	CARDTYPE _type;
	int cardWeight;
	int cardStrength;

	Player* _player
};

