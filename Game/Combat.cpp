#include "combat.h"

Combat::Combat(int health, int damage) : maxHealth(health), attackDamage(damage), currentHealth(maxHealth), target(nullptr)
{
	
}

Combat::~Combat()
{

}

void Combat::TurnAction(Combat* other)
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

void Combat::SetTarget(Combat* other)
{
	target = other;
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

Combat* Combat::GetTarget()
{
	return target;
}
