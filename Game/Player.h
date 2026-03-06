#pragma once
#include "Entity.h"
#include "Combat.h"

//I am unhappy with how this structure works. In future I would change it so Entity and Combat both are parent classes to a "CombatEntity" class
//The reason for this change is due to how much shared information both the enemies and player have 
//However their parent classes do not share this nore do either of them require these functions
//There is also a large amount of cross over in their stored variables too.

class ICard;
class TextObject;
class Player : public Entity, public Combat
{
	enum ACTION
	{
		NA,
		ACTION1,
		ACTION2,
		CARD
	};

	enum CARDTYPES
	{
		DAMAGECARD = 1,
		HEALCARD = 2
	};


public:
	Player(int X, int Y, const Object& mouse, int health, int damage, const char* imagePath, int size);
	~Player();

	void Init() override;

	void Update() override;
	
	//Where the Player selects their action
	void SelectAction();
	void SelectAction(ICard* card);

	//Where the Selected Action gets played
	void TurnAction(Combat* other) override;

	void TakeDamage(int damage) override;

	void SetDamage(int damage) override;

	//returns a bool, checks if the player has taken their choice of action
	bool GetActionMade();

	//used to reset the actionMade bool to false
	void ResetActionMade();

	void Hide();

private:
	TextObject* healthDataObj;
	TextObject* healthObj;
	TextObject* damageObj;
	ACTION _action;
	Object* testAction1;
	Object* testAction2;

	ACTION selectedAction;
	bool actionTaken;

	std::string textData;
	bool showingData;

	ICard* selectedCard;
};

