#include "Player.h"
#include "TextObject.h"
#include "Input.h"

Player::Player(int X, int Y, const Object& mouse, int health, int damage, const char* imagePath, int size) : Entity(X, Y, mouse, imagePath, size), Combat(health, damage)
{
	Init();
}

Player::~Player()
{
	Entity::~Entity();
	delete healthObj;
	delete damageObj;
	delete testAction1;
	delete testAction2;
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

	testAction1 = new Object("assets/Images/Wren_Bird.bmp", GetPosX() + objSize, GetPosY() + (objSize / 2), 64, 64, true);
	testAction2 = new Object("assets/Images/Wren_Bird.bmp", GetPosX() + objSize, GetPosY() + (objSize / 1.25), 64, 64, true);

	//space for setting card class and deck

}



void Player::Update()
{
	GetDrawn()->Update();
	healthObj->Update();
	damageObj->Update();
	testAction1->Update();
	testAction2->Update();

	//check if mouse is over player
	if (OnMouseClick(GetDrawn()))
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

	if (OnMouseClick(testAction1))
	{
		GetTarget()->TakeDamage(GetAttackDamage()); //gets target, calls the take damage function and passes in damage of player
	}
	else if (OnMouseClick(testAction2))
	{
		TakeDamage(( -GetAttackDamage() / 2)); //heal PLACEHOLDER need a HEAL function becasue this reads like ASS
	}

}

void Player::TurnAction(Combat* other)
{
	


	//cards need to be built
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



