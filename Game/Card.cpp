#include "Card.h"
#include "Combat.h"
#include "Object.h"
#include "Player.h"

Card::Card(CARDTYPE type, int cardWeight, int cardStrength, Player* player,int X, int Y, const Object& mouse, const char* imagePath, int size)
	: Entity(X, Y, mouse, imagePath, size), _type(type), cardWeight(cardWeight), cardStrength(cardStrength), _player(player)
{
	Initilise();
}

void Card::Initilise()
{
	visualComponent = CreateVisual(filePath);
	visualComponent->SetShouldCollide(true);

	//space for expansion on more complex cards
}

void Card::CardFunction(Combat* t)
{
	if (_type == ATTACK)
	{
		t->TakeDamage(cardStrength);
	}
	else if (_type == HEAL)
	{
		_player->TakeDamage(-cardStrength);
	}
}

int Card::GetCardWeight()
{
	return cardWeight;
}
