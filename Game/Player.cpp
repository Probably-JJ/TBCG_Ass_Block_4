#include "Player.h"

Player::Player(int X, int Y, Object mouse, int health, int damage, const char* imagePath) : Entity(X, Y, mouse, imagePath), Combat(health, damage)
{
	Init();
}

void Player::Init()
{
	CreateVisual(filePath);
	//space for setting card class and deck
}

Object* Player::CreateVisual(const char* filepath)
{
	return visualComponent = new Object(filepath, GetPosX(), GetPosY(), 128, 128, true);
}

void Player::TurnAction()
{
	//cards need to be built first
}

void Player::OnMouse()
{
	//check if mouse is over
	//disply health and damage
}

void Player::Update()
{
	GetDrawn()->Update();
	OnMouse();
}
