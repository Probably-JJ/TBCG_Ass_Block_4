#pragma once
#include "Entity.h"
#include "Combat.h"


class AttackerEnemy : public Entity, public Combat
{
	AttackerEnemy(int X, int Y, Object mouse, int health, int damage, const char* imagePath);

};

