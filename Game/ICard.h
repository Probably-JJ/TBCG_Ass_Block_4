#pragma once

class Combat;
class Object;
class ICard
{
public:
	virtual void Init() = 0;
	virtual void Apply(Combat* target) = 0;
	virtual Object* GetObject() = 0;
	virtual int GetCardType() = 0;
	virtual bool GetPlayed() = 0;
	virtual void Reset() = 0;
};

