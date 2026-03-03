#include "HealCard.h"
#include "Combat.h"

HealCard::HealCard(int healValue) : m_healAmount(healValue)
{
	Init();
}

void HealCard::Init()
{

}

void HealCard::Apply(Combat* target)
{
	target->TakeDamage(-m_healAmount);
}
