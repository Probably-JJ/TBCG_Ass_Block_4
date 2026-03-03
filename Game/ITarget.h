#pragma once

class ICard;
class ITarget
{
public:
	virtual void ApplyCard(ICard* card) = 0;
};

