#include "CardInfo.h"
#include "Object.h"
#include "ICard.h"
#include <sstream>

#include "DamageCard.h"
#include "HealCard.h"
#include "SingleCombatant.h"



CardInfo::CardInfo(const Object& mouse, const char* imagePath, int size) : Entity(0, 0, mouse, imagePath, size), cardName("NO_NAME"), /*target(nullptr),*/ card(nullptr), cardWeight(1)
{
	Init();
}

CardInfo::~CardInfo()
{
	//if (target != nullptr)
	//{
	//	delete target;
	//	target = nullptr;
	//}

	if (card != nullptr)
	{
		delete card;
		card = nullptr;
	}
}

void CardInfo::Init()
{
	visualComponent = CreateVisual(filePath);
	visualComponent->SetShouldCollide(true);
}

#pragma region Getters
std::string CardInfo::GetCardName()
{
	return cardName;
}

ICard* CardInfo::GetCard()
{
	return card;
}

int CardInfo::GetCardWeight()
{
	return cardWeight;
}

//ITarget* CardInfo::GetTarget()
//{
//	return target;
//}
#pragma endregion

ICard* CardInfo::Build(std::string parsedFileLine)
{
	//File Structure: Name CardType Value CardWeight
	std::istringstream iss(parsedFileLine);
	std::string cardType;
	int cardValue;

	iss >> cardName >> cardType >> cardValue >> cardWeight;

	if (cardType == "DamageCard")
	{
		card = new DamageCard(cardValue);
		return card;
	}
	else if (cardType == "HealCard")
	{
		card = new HealCard(cardValue);
		return card;
	}
}

