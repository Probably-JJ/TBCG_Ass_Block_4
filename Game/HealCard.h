#pragma once
#include "ICard.h"


class HealCard : public ICard
{
public:
	HealCard(int healValue);

	void Init() override;
	void Apply(Combat* target) override;

private:
	int m_healAmount;
};

