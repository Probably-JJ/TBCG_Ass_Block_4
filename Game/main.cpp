/// Note: 
/// This is the entry point for your game, should you choose to build from this solution.
/// The files in Gamewell are included in the additional directories for you, for the Game project
/// so #include "Gamewell_api.h" for example should just work anywhere.

#include "Gamewell_api.h"
#include "Player.h"
#include "Enemy.h"

int main()
{
	//TODO:
	//target specific enemies -> enemies need to be stored in array, run check on all to see OnMouseClick(enemy[i]) then player->SetTarget(enemy[i])
	//combat - death
	//
	//game class
	//game - turn cycle
	// 
	// 
	//deck class
	//class classes
	//card class
	//convert player actions to cards


	GameScreen screen;
	if (!screen.CreateScreen("Turn Based Card Game"))
	{
		return -1;
	}
	
	//test
	Object* mouse = new Object("assets/Images/Wren_Bird.bmp", 0, 0, 32, 32, true); //create a child class of Entity, override the mouseover function
	mouse->SetShouldCollide(true);
	
	Input inp;
	//screen is 1280 x 720
	Enemy* testEnemy1 = new Enemy(954, 432, *mouse, 100, 10, "assets/Images/Wren_Evil.bmp", 256, Enemy::ATTACKER);
	Enemy* testEnemy2 = new Enemy(954, 32, *mouse, 100, 10, "assets/Images/Wren_Evil.bmp", 256, Enemy::ATTACKER);
	Player* testPlay = new Player(70, 232, *mouse, 100, 10, "assets/Images/Wren_Bird.bmp", 256);
	int x, y;


	testEnemy1->SetTarget(testPlay);
	testPlay->SetTarget(testEnemy1);

	while (screen.IsRunning())
	{
		inp.GetMousePos(x, y);
		mouse->SetPosition(x, y);

		mouse->Update();

		testPlay->Update();
		testEnemy1->Update();
		testEnemy2->Update();

		if (inp.GetKeyDown('t'))
		{
			testEnemy1->TurnAction(testEnemy1->GetTarget());
		}

		if (inp.GetKeyDown('#'))
		{
			screen.CloseScreen();
		}

		screen.Update();
	}

	return 0;
}