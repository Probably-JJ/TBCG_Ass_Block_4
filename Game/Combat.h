#pragma once
#include <iostream>

class Combat
{
public:
	Combat(int health, int damage);

	virtual void TurnAction();
	virtual void TakeDamage(int damage); //Acts as a setter for current health
	virtual void SetDamage(int damage); //overload for so can be displayed by player

	bool QueryDead();
	
	int GetMaxHealth();
	int GetCurrentHealth();
	int GetAttackDamage();


private:
	int maxHealth;
	int currentHealth;
	int attackDamage;
};

