#include "SingleCombatant.h"
#include "CardInfo.h"
#include "Combat.h"
#include "ICard.h"

SingleCombatant::SingleCombatant(Combat* targ) : m_target(targ) {}

void SingleCombatant::ApplyCard(ICard* card)
{
	card->Apply(m_target);
}
