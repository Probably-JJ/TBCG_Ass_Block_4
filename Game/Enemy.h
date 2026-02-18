#pragma once
#include "Entity.h"
#include "Combat.h"

class TextObject;

class Enemy : public Entity, public Combat
{
public:
	Enemy(int X, int Y, Object mouse, int health, int damage, const char* imagePath, int size);

	//overried to allow for extra init for combat
	void Init() override;

	void Update() override;

	void TurnAction() override;

	void TakeDamage(int damage) override;

	void SetDamage(int damage) override;

	void showHealth(); //enemy will always show their current health but never their other stats

private:
	TextObject* healthObj;
	std::string textData;
};

