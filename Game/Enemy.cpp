#include "Enemy.h"
#include "TextObject.h"

Enemy::Enemy(int X, int Y, Object mouse, int health, int damage, const char* imagePath, int size) : Entity(X, Y, mouse, imagePath, size), Combat(health, damage)
{
	Init();
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
	GetDrawn()->Update();
	showHealth();
}

void Enemy::TurnAction()
{
}

void Enemy::TakeDamage(int damage)
{
}

void Enemy::SetDamage(int damage)
{
}

void Enemy::showHealth()
{
	textData = "Health: " + std::to_string(GetCurrentHealth());
	healthObj->SetText(textData.c_str());
	healthObj->Update();
}


