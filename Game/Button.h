#pragma once
#include "Entity.h"


class Button : public Entity
{
public:
	Button(int X, int Y, const Object& mouse, const char* imagePath, int size);

	void Update() override;

	bool GetClicked();

private:
	void Init() override;
	bool clicked;
};

