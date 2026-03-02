#include "CardInfo.h"
#include "Object.h"

CardInfo::CardInfo(const Object& mouse, const char* imagePath, int size) : Entity(0, 0, mouse, imagePath, size)
{
	Init();
}

void CardInfo::Init()
{
	visualComponent = CreateVisual(filePath);
	visualComponent->SetShouldCollide(true);
}

void CardInfo::Build(std::string parsedFileLine)
{
	//convert pFL into iss
	//pass iss into the different statements to build each card for use
	//like in prev mod
}

