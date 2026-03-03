#pragma once
#include "ICard.h"


class DamageCard : public ICard
{
public:
	DamageCard(int damage);

	void Init() override;
	void Apply(Combat* target) override;

private:
	int m_damage;
};

