#pragma once
#include "ICard.h"
#include "Entity.h"


class Object;
class DamageCard : public ICard, public Entity
{
public:
	DamageCard(int damage, const Object& mouse, const char* imagePath, int size);

	void Init() override;
	void Apply(Combat* target) override;
	Object* GetObject() override;
	int GetCardType() override;
	bool GetPlayed() override;
	void Reset() override;

private:
	int m_damage;
	int played;
};

