#pragma once
#include <iostream>
#include <string.h>


class Object;
class Input;

class Entity
{
public:
	Entity(int X, int Y, const Object& mouseObj, const char* imagePath, int size);
	virtual ~Entity();

	virtual void Init();

	//check if the mouse is over the object, allow for displaying extra data or extra functionality
	bool OnMouseClick(Object* other);
	bool OnMouseRelease();
	virtual void Update();

	int GetPosX();
	int GetPosY();

	//returns the visual object on screen
	Object* GetDrawn();

	//input values change the X and Y to the input positions
	void SetPos(int X, int Y);
	

protected:
	virtual Object* CreateVisual(const char* filepath);
	int posX;
	int posY;
	int objSize;
	const Object& mouse;
	Object* visualComponent;
	const char* filePath;
	Input* userInp;

};