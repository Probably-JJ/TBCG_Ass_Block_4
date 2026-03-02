#pragma once
#include "Entity.h"
#include "Combat.h"

//I am unhappy with how this structure works. In future I would change it so Entity and Combat both are parent classes to a "CombatEntity" class
//The reason for this change is due to how much shared information both the enemies and player have 
//However their parent classes do not share this nore do either of them require these functions
//There is also a large amount of cross over in their stored variables too.



//This new structure would also allow for each enemy to be its own class rather than sharing one 

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

