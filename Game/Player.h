#pragma once
#include "Entity.h"
#include "Combat.h"

class TextObject;

class Player : public Entity, public Combat
{
public:
	Player(int X, int Y, const Object& mouse, int health, int damage, const char* imagePath, int size);

	void Init() override;

	void Update() override;
	
	void TurnAction() override; //the action the player selects through choosing their card to play 

	void TakeDamage(int damage) override;

	void SetDamage(int damage) override;

private:
	TextObject* healthObj;
	TextObject* damageObj;

	std::string textData;
	bool showingData;
};

