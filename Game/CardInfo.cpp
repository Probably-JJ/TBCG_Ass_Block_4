#include "CardInfo.h"
#include "Object.h"
#include "ICard.h"
#include <sstream>

#include "DamageCard.h"
#include "HealCard.h"
#include "SingleCombatant.h"



CardInfo::CardInfo(const Object& mouse) : cardName("NO_NAME"), /*target(nullptr),*/ card(nullptr), cardWeight(1), mouseRef(mouse)
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
	std::string cardType, filePath;
	int cardValue;

	//card Weight is currently ignored due to decksystem not being built
	iss >> cardName >> cardType >> cardValue >> cardWeight >> filePath;

	if (cardType == "DamageCard")
	{
		card = new DamageCard(cardValue, mouseRef, filePath.c_str(), 128);
		return card;
	}
	else if (cardType == "HealCard")
	{
		card = new HealCard(cardValue, mouseRef, filePath.c_str(), 128);
		return card;
	}
}

