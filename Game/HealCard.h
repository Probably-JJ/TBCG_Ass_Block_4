#pragma once
#include "ICard.h"
#include "Entity.h"


class Object;
class HealCard : public ICard, public Entity
{
public:
	HealCard(int healValue, const Object& mouse, const char* imagePath, int size);

	void Init() override;
	void Apply(Combat* target) override;

private:
	int m_healAmount;
	bool played;
};

