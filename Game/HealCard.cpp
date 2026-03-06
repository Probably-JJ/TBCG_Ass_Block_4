#include "HealCard.h"
#include "Combat.h"
#include "Object.h"


HealCard::HealCard(int healValue, const Object& mouse, const char* imagePath, int size) : Entity(0, 0, mouse, imagePath, size), m_healAmount(healValue), played(false)
{
	Init();
}

void HealCard::Init()
{
	visualComponent = CreateVisual(filePath);
	visualComponent->SetShouldCollide(true);
	visualComponent->SetShouldDraw(false);
}

void HealCard::Apply(Combat* target)
{
	target->TakeDamage(-m_healAmount);
	played = true;
}

Object* HealCard::GetObject()
{
	return GetDrawn();
}

int HealCard::GetCardType()
{
	return 2;
}

bool HealCard::GetPlayed()
{
	return played;
}

void HealCard::Reset()
{
	played = false;
}
