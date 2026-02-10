/// Note: 
/// This is the entry point for your game, should you choose to build from this solution.
/// The files in Gamewell are included in the additional directories for you, for the Game project
/// so #include "Gamewell_api.h" for example should just work anywhere.

#include "Gamewell_api.h"

int main()
{
	GameScreen screen;
	if (!screen.CreateScreen("Test Game"))
	{
		return -1;
	}
	
	while (screen.IsRunning())
	{
		screen.Update();
	}

	return 0;
}