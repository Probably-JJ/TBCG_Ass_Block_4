/// Note: 
/// This is the entry point for your game, should you choose to build from this solution.
/// The files in Gamewell are included in the additional directories for you, for the Game project
/// so #include "Gamewell_api.h" for example should just work anywhere.

#include "Gamewell_api.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"

int main()
{
	//TODO:
	//target specific enemies -> enemies need to be stored in array, run check on all to see OnMouseClick(enemy[i]) then player->SetTarget(enemy[i])
	//combat - death
	//
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

	Game game(screen);
	game.Initialise();
	while (game.IsRunning())
	{
		game.Run();
	}

	return 0;
}