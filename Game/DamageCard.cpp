#include "DamageCard.h"
#include "Combat.h"
#include "Object.h"


DamageCard::DamageCard(int damage, const Object& mouse, const char* imagePath, int size) : Entity(1,1, mouse, imagePath, size), m_damage(damage), played(false)
{
	Init();
}

void DamageCard::Init()
{
	visualComponent = CreateVisual(filePath);
	visualComponent->SetShouldCollide(false);
	visualComponent->SetShouldDraw(false);
}

void DamageCard::Apply(Combat* target)
{
	target->TakeDamage(m_damage);
	played = true;
}

Object* DamageCard::GetObject()
{
	return visualComponent;
}

int DamageCard::GetCardType()
{
	return 1;
}

bool DamageCard::GetPlayed()
{
	return played;
}

void DamageCard::Reset()
{
	played = false;
}
