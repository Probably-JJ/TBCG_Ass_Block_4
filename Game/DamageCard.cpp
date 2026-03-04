#include "DamageCard.h"
#include "Combat.h"
#include "Object.h"


DamageCard::DamageCard(int damage, const Object& mouse, const char* imagePath, int size) : Entity(0,0, mouse, imagePath, size), m_damage(damage), played(false)
{
	Init();
}

void DamageCard::Init()
{
	visualComponent = CreateVisual(filePath);
	visualComponent->SetShouldCollide(true);
	visualComponent->SetShouldDraw(false);
}

void DamageCard::Apply(Combat* target)
{
	target->TakeDamage(m_damage);
	played = true;
}
