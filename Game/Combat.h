#pragma once
#include <iostream>

class Combat
{
public:
	Combat(int health, int damage);

	virtual void TurnAction();
	bool QueryDead();
	
	int GetMaxHealth();
	int GetCurrentHealth();
	int GetAttackDamage();

	void SetCurrentHealth(int health);
	void SetDamage(int damage);

private:
	int maxHealth;
	int currentHealth;
	int attackDamage;
};

