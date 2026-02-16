/// Note: 
/// This is the entry point for your game, should you choose to build from this solution.
/// The files in Gamewell are included in the additional directories for you, for the Game project
/// so #include "Gamewell_api.h" for example should just work anywhere.

#include "Gamewell_api.h"
#include "Player.h"

int main()
{
	//TODO:
	//mouse class
	//enemy classes
	//game class
	//combat - death
	//deck class
	//class classes
	//card class


	GameScreen screen;
	if (!screen.CreateScreen("Turn Based Card Game"))
	{
		return -1;
	}
	
	//test
	Object* mouse = new Object("assets/Images/Wren_Bird.bmp", 0, 0, 32, 32, true); //create a child class of Entity, override the mouseover function
	mouse->SetShouldCollide(true);
	
	Input inp;
	Player* test = new Player(30, 30, *mouse, 100, 10, "assets/Images/Wren_Bird.bmp");
	int x, y;


	while (screen.IsRunning())
	{
		inp.GetMousePos(x, y);
		mouse->SetPosition(x, y);

		mouse->Update();
		test->Update();

		screen.Update();
	}

	return 0;
}