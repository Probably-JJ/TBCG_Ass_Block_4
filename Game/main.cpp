// Wren's note right before submission
// Just a quick notation about my thoughts of the end of this project: I'm extremely underwhelmed with how my final project turned out.
// I had to cut out one of my core systems as I just didnt have the time to finish it and that has resulted in my game feeling unfinished
// Additionally the structure of my systems has had me back tracking though files constantly and getting lost while programming.
// If I had the time I would have gone back to restructure everything to how it should have been in the first place.

#include "Gamewell_api.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"

//there is currently a bug that can cause the current round not to end despite all enemies being dead.
//I'm unsure as to the exact cause of this issue but from my testing it seems to be due to either:
//A: going too fast in the round
//B: all cards being used when the round ends

int main()
{


	GameScreen screen;
	if (!screen.CreateScreen("Turn Based Card Game"))
	{
		return -1;
	}

	Game game(screen);

	while (game.IsRunning())
	{
		game.Run();
	}

	return 0;
}