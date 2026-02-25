#pragma once
#include <iostream>

class Combat
{
public:
	Combat(int health, int damage);
	~Combat();

	virtual void TurnAction(Combat* other);
	virtual void TakeDamage(int damage); //Acts as a setter for current health
	virtual void SetDamage(int damage); //overload for so can be displayed by player

	//returns true if player is dead
	bool QueryDead();
	void SetTarget(Combat* other);
	
	int GetMaxHealth();
	int GetCurrentHealth();
	int GetAttackDamage();
	Combat* GetTarget();


protected:
	int maxHealth;
	int currentHealth;
	int attackDamage;
	Combat* target;
};

