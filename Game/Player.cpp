#include "Player.h"
#include "TextObject.h"
#include "Input.h"

Player::Player(int X, int Y, const Object& mouse, int health, int damage, const char* imagePath, int size) : Entity(X, Y, mouse, imagePath, size), Combat(health, damage)
{
	Init();
}

void Player::Init()
{
	Colour white;
	white.r = 255;
	white.g = 255;
	white.b = 255;

	textData = "Health: " + std::to_string(GetCurrentHealth());
	healthObj = new TextObject(textData.c_str(), "assets/default.ttf", 10, GetPosX() + (objSize / 2), GetPosY() + (objSize + 10), white, false);

	textData = "Damage: " + std::to_string(GetAttackDamage());
	damageObj = new TextObject(textData.c_str(), "assets/default.ttf", 10, GetPosX() + (objSize / 2), GetPosY() + (objSize + 20), white, false);

	visualComponent = CreateVisual(filePath);
	visualComponent->SetShouldCollide(true);
	//space for setting card class and deck
}



void Player::Update()
{
	GetDrawn()->Update();
	healthObj->Update();
	damageObj->Update();

	//check if mouse is over player
	if (OnMouseClick(*GetDrawn()))
	{
		if (!showingData)
		{
			healthObj->SetShouldDraw(true);
			damageObj->SetShouldDraw(true);
			showingData = true;
		}
	}
	else if (OnMouseRelease())
	{
		if (showingData)
		{
			healthObj->SetShouldDraw(false);
			damageObj->SetShouldDraw(false);
			showingData = false;
		}
	}
}

void Player::TurnAction()
{
	//cards need to be built first
}

void Player::TakeDamage(int damage)
{
	Combat::TakeDamage(damage);
	textData = "Health: " + std::to_string(GetCurrentHealth());
	healthObj->SetText(textData.c_str());
}

void Player::SetDamage(int damage)
{
	Combat::SetDamage(damage);
	textData = "Damage: " + std::to_string(GetAttackDamage());
	damageObj->SetText(textData.c_str());
}



