#pragma once
#include "Entity.h"
#include "Combat.h"

class TextObject;

class Enemy : public Entity, public Combat
{
public:

	enum TYPE //this could later be used to assign different sprites
	{
		ATTACKER,
		HEALER,
		BOSS
	};

	Enemy(int X, int Y, const Object& mouse, int health, int damage, const char* imagePath, int size, TYPE enemyType);
	~Enemy();

	void Init() override;

	void Update() override;

	void TurnAction(Combat* other) override;

	void TakeDamage(int damage) override;

private:
	TextObject* healthObj;
	std::string textData;
	TYPE tag;
};

