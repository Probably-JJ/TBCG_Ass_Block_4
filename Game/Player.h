#pragma once
#include "Entity.h"
#include "Combat.h"

class TextObject;

class Player : public Entity, public Combat
{
	enum ACTION
	{
		NA,
		ACTION1,
		ACTION2
	};



public:
	Player(int X, int Y, const Object& mouse, int health, int damage, const char* imagePath, int size);
	~Player();

	void Init() override;

	void Update() override;
	
	void SelectAction();

	void TurnAction(Combat* other) override; //the action the player selects through choosing their card to play 

	void TakeDamage(int damage) override;

	void SetDamage(int damage) override;

	//returns a bool, checks if the player has taken their choice of action
	bool GetActionMade();

	//used to reset the actionMade bool to false
	void ResetActionMade();

private:
	TextObject* healthDataObj;
	TextObject* damageObj;
	ACTION _action;
	Object* testAction1;
	Object* testAction2;

	ACTION selectedAction;
	bool actionTaken;

	std::string textData;
	bool showingData;
};

