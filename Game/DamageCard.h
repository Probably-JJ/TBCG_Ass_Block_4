#pragma once
#include "ICard.h"
#include "Entity.h"

class DamageCard : public ICard
{
public:
	DamageCard(int damage);

	void Init() override;
	void Apply(Combat* target) override;

private:
	int m_damage;
};

