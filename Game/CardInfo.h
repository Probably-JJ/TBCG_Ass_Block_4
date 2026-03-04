#pragma once
#include <string>
#include "Entity.h"


class ICard;
class ITarget;
class CardInfo : public Entity
{
public:
	CardInfo(const Object& mouse, const char* imagePath, int size);
	~CardInfo();
	void Init();

	std::string GetCardName();
	ICard* GetCard();
	int GetCardWeight();
	//ITarget* GetTarget(); removed for scoping reasons

	//Sets the values of the card with parsed in information
	//File Structure: Name CardType Value CardWeight
	ICard* Build(std::string parsedFileLine);


private:
	std::string cardName;
	//ITarget* target;
	ICard* card;
	int cardWeight;
};

