#include "Entity.h"

Entity::Entity(int X, int Y, Object mouseObj, const char* imagePath) : posX(X), posY(Y), mouse(mouseObj), filePath (imagePath)
{
	
}

Entity::~Entity()
{
	delete visualComponent;
}

Object* Entity::CreateVisual(const char* filepath)
{
	return visualComponent = new Object(filepath, GetPosX(), GetPosY(), 1, 1, false);
}

void Entity::Init()
{

}

void Entity::Update()
{
	visualComponent->Update();
	OnMouse();

}

int Entity::GetPosX()
{
	return posX;
}

int Entity::GetPosY()
{
	return posY;
}

Object* Entity::GetDrawn()
{
	return visualComponent;
}

void Entity::SetPos(int X, int Y)
{
	posX = X;
	posY = Y;
}

void Entity::OnMouse()
{
	if(visualComponent->IsOverlapping(mouse))
	{
		std::cout << "Mouse is over an Entity" << std::endl;
	}
}

