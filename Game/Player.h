#pragma once
#include "Entity.h"
#include "Combat.h"

class TextObject;

class Player : public Entity, public Combat
{
	enum ACTION
	{
		ACTION1,
		ACTION2
	};



public:
	Player(int X, int Y, const Object& mouse, int health, int damage, const char* imagePath, int size);
	~Player();

	void Init() override;

	void Update() override;
	
	void TurnAction(Combat* other) override; //the action the player selects through choosing their card to play 

	void TakeDamage(int damage) override;

	void SetDamage(int damage) override;

private:
	TextObject* healthObj;
	TextObject* damageObj;
	ACTION _action;
	Object* testAction1;
	Object* testAction2;




	std::string textData;
	bool showingData;
};

