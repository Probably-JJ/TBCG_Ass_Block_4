#include "DamageCard.h"
#include "Combat.h"

DamageCard::DamageCard(int damage) : m_damage(damage)
{
	Init();
}

void DamageCard::Init()
{

}

void DamageCard::Apply(Combat* target)
{
	target->TakeDamage(m_damage);
}
