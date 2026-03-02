#pragma once

class Combat;
class ICard
{
public:
	virtual void Init() = 0;
	virtual void Apply(Combat* target) = 0;
};

