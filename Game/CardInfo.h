#pragma once
#include <string>
#include "Entity.h"

class ICard;
class ITarget;
class CardInfo : public Entity
{
public:
	CardInfo(const Object& mouse, const char* imagePath, int size);

	void Init();
	void Build(std::string parsedFileLine);
	//create getters and setters


private:
	std::string cardName;
	ITarget* target;
	ICard* card;
	int cardWeight;

};

