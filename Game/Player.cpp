#include "Player.h"

Player::Player(int X, int Y, const Object& mouse, int health, int damage, const char* imagePath) : Entity(X, Y, mouse, imagePath), Combat(health, damage)
{
	Init();
}

void Player::Init()
{
	visualComponent = CreateVisual(filePath);
	visualComponent->SetShouldCollide(true);
	//space for setting card class and deck
}

Object* Player::CreateVisual(const char* filepath)
{
	return new Object(filepath, GetPosX(), GetPosY(), 128, 128, true);
}

void Player::TurnAction()
{
	//cards need to be built first
}

void Player::OnMouse()
{
	if (GetDrawn()->IsOverlapping(mouse))
	{
		std::cout << "Mouse on player" << std::endl;
	}
}

void Player::Update()
{
	GetDrawn()->Update();
	OnMouse();
}
