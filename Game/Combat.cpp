#include "combat.h"

Combat::Combat(int health, int damage) : maxHealth(health), attackDamage(damage), currentHealth(maxHealth) {}

void Combat::TurnAction()
{
	std::cout << "No Functionality Set" << std::endl;
}

void Combat::TakeDamage(int damage)
{
	currentHealth -= damage;
}

void Combat::SetDamage(int damage)
{
	attackDamage = damage;
}

bool Combat::QueryDead()
{
	return (currentHealth <= 0);
}

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
