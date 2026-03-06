#include "Button.h"
#include "Object.h"

Button::Button(int X, int Y, const Object& mouse, const char* imagePath, int size) : Entity(X, Y, mouse, imagePath, size)
{
	Init();
}

void Button::Update()
{
	GetDrawn()->Update();
	if (OnMouseClick(GetDrawn()))
	{
		clicked = true;
	}
	else if (OnMouseRelease())
	{
		clicked = false;
	}
}

bool Button::GetClicked()
{
	return clicked;
}

void Button::Init()
{
	visualComponent = CreateVisual(filePath);
	visualComponent->SetShouldCollide(true);
}

