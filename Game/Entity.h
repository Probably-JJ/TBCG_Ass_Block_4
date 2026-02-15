#pragma once
#include <iostream>
#include <string.h>
#include "Object.h"
#include "Input.h"

class Entity
{
public:
	Entity(int X, int Y, Object mouseObj, const char* imagePath);
	~Entity();

	virtual void Init();
	virtual Object* CreateVisual(const char* filepath);

	//check if the mouse is over the object, allow for displaying extra data or extra functionality
	virtual void OnMouse();
	virtual void Update();

	int GetPosX();
	int GetPosY();

	//returns a pointer to the Object component
	Object* GetDrawn();

	//input values change the X and Y to the input positions
	void SetPos(int X, int Y);
	

protected:
	int posX;
	int posY;
	Object mouse;
	Object* visualComponent;
	Input userInp;
	const char* filePath;

};