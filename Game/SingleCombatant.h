#pragma once
#include "ITarget.h"

class ICard;
class Combat;
class SingleCombatant : public ITarget
{
public:
	SingleCombatant(Combat* targ);

	void ApplyCard(ICard* card) override;

private:
	Combat* m_target;
};

