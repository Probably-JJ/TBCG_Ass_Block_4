#include "Player.h"
#include "TextObject.h"
#include "Input.h"

Player::Player(int X, int Y, const Object& mouse, int health, int damage, const char* imagePath, int size) : Entity(X, Y, mouse, imagePath, size), Combat(health, damage)
{
	Init();
}

Player::~Player()
{
	if (healthDataObj != nullptr)
	{
		delete healthDataObj;
	}
	if (healthObj != nullptr)
	{
		delete healthObj;
	}
	if (damageObj != nullptr)
	{
		delete damageObj;
	}
	if (testAction1 != nullptr)
	{
		delete testAction1;
	}
	if (testAction2 != nullptr)
	{
		delete testAction2;
	}
}

void Player::Init()
{
	Colour white;
	white.r = 255;
	white.g = 255;
	white.b = 255;

	textData = "Health: " + std::to_string(GetCurrentHealth()) + "/" + std::to_string(GetMaxHealth());
	healthDataObj = new TextObject(textData.c_str(), "assets/default.ttf", 10, GetPosX() + (objSize / 2), GetPosY() + (objSize + 10), white, false);

	textData = "Health: " + std::to_string(GetCurrentHealth());
	healthObj = new TextObject(textData.c_str(), "assets/default.ttf", 20, GetPosX() + (objSize / 2), GetPosY() - (objSize * 0.1), white, true);


	textData = "Damage: " + std::to_string(GetAttackDamage());
	damageObj = new TextObject(textData.c_str(), "assets/default.ttf", 10, GetPosX() + (objSize / 2), GetPosY() + (objSize + 20), white, false);

	visualComponent = CreateVisual(filePath);
	visualComponent->SetShouldCollide(true);

	testAction1 = new Object("assets/Images/Attack.bmp", GetPosX() + objSize, GetPosY() + (objSize / 2), 64, 64, true);
	testAction2 = new Object("assets/Images/Heal.bmp", GetPosX() + objSize, GetPosY() + (objSize / 1.25), 64, 64, true);

	actionTaken = false;


	//space for setting card class and deck

}



void Player::Update()
{
	GetDrawn()->Update();
	healthDataObj->Update();
	healthObj->Update();
	damageObj->Update();
	testAction1->Update();
	testAction2->Update();

	//check if mouse is over player
	if (OnMouseClick(GetDrawn()))
	{
		if (!showingData)
		{
			healthDataObj->SetShouldDraw(true);
			damageObj->SetShouldDraw(true);
			showingData = true;
		}
	}
	else if (OnMouseRelease())
	{
		if (showingData)
		{
			healthDataObj->SetShouldDraw(false);
			damageObj->SetShouldDraw(false);
			showingData = false;
		}
	}

}

void Player::SelectAction()
{
	if (OnMouseClick(testAction1))
	{
		selectedAction = ACTION1;
		actionTaken = true;
	}
	else if (OnMouseClick(testAction2))
	{
		selectedAction = ACTION2;
		actionTaken = true;
	}
}

void Player::TurnAction(Combat* other)
{
	if (selectedAction == ACTION1)
	{
		GetTarget()->TakeDamage(GetAttackDamage()); //gets target, calls the take damage function and passes in damage of player
	}
	else if (selectedAction == ACTION2)
	{
		TakeDamage(( -GetAttackDamage() / 2)); //heal PLACEHOLDER need a HEAL function becasue this reads like ASS
	}

	//cards need to be built
}

void Player::TakeDamage(int damage)
{
	Combat::TakeDamage(damage);
	textData = "Health: " + std::to_string(GetCurrentHealth()) + "/" + std::to_string(GetMaxHealth());
	healthDataObj->SetText(textData.c_str());

	textData = "Health: " + std::to_string(GetCurrentHealth());
	healthObj->SetText(textData.c_str());
}

void Player::SetDamage(int damage)
{
	Combat::SetDamage(damage);
	textData = "Damage: " + std::to_string(GetAttackDamage());
	damageObj->SetText(textData.c_str());
}

bool Player::GetActionMade()
{
	return actionTaken;
}

void Player::ResetActionMade()
{
	actionTaken = false;
	selectedAction = NA;
}

void Player::Hide()
{
	GetDrawn()->SetShouldCollide(false);
	GetDrawn()->SetShouldDraw(false);
	damageObj->SetShouldDraw(false);
	healthDataObj->SetShouldDraw(false);

}



