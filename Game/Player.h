#pragma once
#include "Entity.h"
#include "Combat.h"
#include "TextObject.h"

class Player : public Entity, public Combat
{
public:
	Player(int X, int Y, const Object& mouse, int health, int damage, const char* imagePath);

	//overried to allow for extra init for combat
	void Init() override;


	//the action the player selects through choosing their card to play 
	void TurnAction() override;

	void OnMouse() override;

	void Update() override;

private:
	Object* CreateVisual(const char* filepath) override;
	//TextObject health;
	//TextObject damage;
};

