#include "Enemy.h"
#include "TextObject.h"

Enemy::Enemy(int X, int Y, const Object& mouse, int health, int damage, const char* imagePath, int size, TYPE enemyType) : Entity(X, Y, mouse, imagePath, size), Combat(health, damage), tag(enemyType)
{
	Init();
}

Enemy::~Enemy()
{
	Entity::~Entity();
	delete healthObj;
}

void Enemy::Init()
{
	Colour white;
	white.r = 255;
	white.g = 128;
	white.b = 128;

	textData = "Health: " + std::to_string(GetCurrentHealth());
	healthObj = new TextObject(textData.c_str(), "assets/default.ttf", 10, GetPosX() + (objSize / 2), GetPosY() + objSize + 10, white, true);

	visualComponent = CreateVisual(filePath);
	visualComponent->SetShouldCollide(true);
}

void Enemy::Update()
{
	Entity::Update();
	healthObj->Update();
}

void Enemy::TurnAction(Combat* other)
{
	switch (tag)
	{
	case ATTACKER:
		other->TakeDamage(GetAttackDamage()); //basic attack, just deals damage
			break;

	case HEALER:
		//logic
		break;

	case BOSS:
		//logic
		break;

	default:
		std::cout << "ERROR: NO ENEMY TAG DATA FOUND" << std::endl; //should be impossible due to a tag being required in constructor
		TakeDamage(GetCurrentHealth()); //kills the enemy if tag data is lost
		break;
	}
}

void Enemy::TakeDamage(int damage)
{
	Combat::TakeDamage(damage);
	textData = "Health: " + std::to_string(GetCurrentHealth());
	healthObj->SetText(textData.c_str());
}


