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
		BOSS,
		OTHER
	};

	Enemy(int X, int Y, const Object& mouse, int health, int damage, const char* imagePath, int size, TYPE enemyType);
	~Enemy();

	void Init() override;

	void Update() override;

	void TurnAction(Combat* other) override;

	void TakeDamage(int damage) override;

	bool GetIgnore();

	//sets the enemy to be ignored
	void Ignore();

	//resets the health of the enemy
	//resets the ignore of the enemy
	void ResetEnemy();

	void Hide();

private:
	TextObject* healthObj;
	std::string textData;
	TYPE tag;

	bool ignore;
};

