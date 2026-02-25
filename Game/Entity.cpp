#include "Entity.h"
#include "Object.h"
#include "Input.h"

Entity::Entity(int X, int Y, const Object& mouseObj, const char* imagePath, int size) : posX(X), posY(Y), mouse(mouseObj), filePath (imagePath), objSize(size), userInp(nullptr), visualComponent(nullptr)
{
	//dont automatically create visual component, would cause issues within child classes
}

Entity::~Entity()
{
	if (visualComponent != nullptr)
	{
		delete visualComponent;
	}
	if (userInp != nullptr)
	{
		delete userInp;
	}
}

Object* Entity::CreateVisual(const char* filepath)
{
	return visualComponent = new Object(filepath, GetPosX(), GetPosY(), objSize, objSize, true);
}

void Entity::Init()
{
	//exists to be overriden with intial data for each entity
}

void Entity::Update()
{
	GetDrawn()->Update();
	OnMouseClick(GetDrawn());
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

bool Entity::OnMouseClick(Object* other)
{
	if(other->IsOverlapping(mouse) && userInp->GetMouseDown(LEFTMOUSEBUTTON))
	{
		std::cout << "Clicked" << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}


bool Entity::OnMouseRelease()
{
	if (userInp->GetMouseUp(LEFTMOUSEBUTTON))
	{
		std::cout << "Unclicked" << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}

