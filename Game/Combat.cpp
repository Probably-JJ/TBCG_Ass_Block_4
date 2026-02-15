#include "combat.h"

Combat::Combat(int health, int damage) : maxHealth(health), attackDamage(damage), currentHealth(maxHealth) {}

void Combat::TurnAction()
{
	std::cout << "No Functionality Set" << std::endl;
}
#pragma region Getters and Setters

int Combat::GetMaxHealth()
{
	return maxHealth;
}

int Combat::GetCurrentHealth()
{
	return currentHealth;
}

int Combat::GetAttackDamage()
{
	return attackDamage;
}

void Combat::SetCurrentHealth(int health)
{
	currentHealth = health;
}

void Combat::SetDamage(int damage)
{
	attackDamage = damage;
}

#pragma endregion